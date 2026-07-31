#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EntityActivationManager \
	)

#include "../includes/entity_activation_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnNone_When_GetStatusWithNullPointer
	)
	{
		EntityActivationStatus
			status =
				manager.get_entity_status(
					nullptr
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::NONE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnFalse_When_SetStatusWithNullPointer
	)
	{
		bool
			result =
				manager.set_entity_status(
					nullptr,
					EntityActivationStatus::ACTIVE
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_SetStatus_When_ValidPointerProvided
	)
	{
		bool
			result =
				manager.set_entity_status(
					&entity_value_one,
					EntityActivationStatus::ACTIVE
				);

		EXPECT_TRUE(
			result
		);

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_one
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::ACTIVE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_RemoveEntity_When_EntityExists
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		bool
			result =
				manager.remove_entity(
					&entity_value_one
				);

		EXPECT_TRUE(
			result
		);

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_one
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::NONE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ClearEntities_When_ClearCalled
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		manager.set_entity_status(
			&entity_value_two,
			EntityActivationStatus::INACTIVE
		);

		bool
			result =
				manager.clear_entities();

		EXPECT_TRUE(
			result
		);

		EXPECT_EQ(
			manager.get_entity_status(
				&entity_value_one
			),
			EntityActivationStatus::NONE
		);

		EXPECT_EQ(
			manager.get_entity_status(
				&entity_value_two
			),
			EntityActivationStatus::NONE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_CompareStatus_When_StatusMatches
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		bool
			result =
				manager.is_entity_status_equal(
					&entity_value_one,
					EntityActivationStatus::ACTIVE
				);

		EXPECT_TRUE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnFalse_When_StatusMismatch
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		bool
			result =
				manager.is_entity_status_equal(
					&entity_value_one,
					EntityActivationStatus::INACTIVE
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleAsyncStatusSet_When_UsingFuture
	)
	{
		std::future<bool>
			async_result =
				std::async(
					std::launch::async,
					[this]()
					{
						return
							manager
								.set_entity_status(
									&entity_value_one,
									EntityActivationStatus
										::ACTIVE
								);
					}
				);

		bool
			result =
				async_result.get();

		EXPECT_TRUE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandlePromiseBasedAsyncUpdate_When_FutureResolved
	)
	{
		std::promise<bool>
			update_promise;

		std::future<bool>
			update_future =
				update_promise.get_future();

		std::thread
			worker_thread(
				[this, &update_promise]()
				{
					bool
						result =
							manager
								.set_entity_status(
									&entity_value_two,
									EntityActivationStatus
										::ACTIVE
								);

					update_promise.set_value(
						result
					);
				}
			);

		bool
			result =
				update_future.get();

		worker_thread.join();

		EXPECT_TRUE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_RemainConsistent_When_MultithreadedAccessOccurs
	)
	{
		std::atomic<bool>
			finished_flag =
				false;

		std::thread
			thread_one(
				[this, &finished_flag]()
				{
					for
					(
						std::size_t iteration =
							0;
						iteration < 5000;
						++iteration
					)
					{
						manager
							.set_entity_status(
								&entity_value_one,
								EntityActivationStatus
									::ACTIVE
							);
					}

					finished_flag =
						true;
				}
			);

		std::thread
			thread_two(
				[this, &finished_flag]()
				{
					while
					(
						!finished_flag.load()
					)
					{
						manager
							.get_entity_status(
								&entity_value_one
							);
					}
				}
			);

		thread_one.join();
		thread_two.join();

		EXPECT_TRUE(
			true
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_SustainHighLoad_When_StressTesting
	)
	{
		for
		(
			std::size_t iteration =
				0;
			iteration < 20000;
			++iteration
		)
		{
			manager.set_entity_status(
				&entity_value_three,
				EntityActivationStatus::ACTIVE
			);

			manager.get_entity_status(
				&entity_value_three
			);
		}

		EXPECT_EQ(
			manager.get_entity_status(
				&entity_value_three
			),
			EntityActivationStatus::ACTIVE
		);
	}

	TEST_P(
		EntityActivationManagerParameterizedStatusTest,
		Should_SetStatus_When_UsingParameterizedValues
	)
	{
		EntityActivationStatus
			status =
				GetParam();

		bool
			result =
				manager.set_entity_status(
					&entity_value,
					status
				);

		if
		(
			status ==
			EntityActivationStatus::NONE
		)
		{
			EXPECT_FALSE(
				result
			);
		}
		else
		{
			EXPECT_TRUE(
				result
			);
		}
	}

	INSTANTIATE_TEST_CASE_P(
		EntityActivationManagerTestStatuses,
		EntityActivationManagerParameterizedStatusTest,
		::testing::Values(
			EntityActivationStatus::ACTIVE,
			EntityActivationStatus::INACTIVE,
			EntityActivationStatus::PENDING,
			EntityActivationStatus::NONE
		)
	);

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnFalse_When_SetStatusWithNoneStatus
	)
	{
		bool
			result =
				manager.set_entity_status(
					&entity_value_one,
					EntityActivationStatus::NONE
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnFalse_When_StatusComparedWithNullPointer
	)
	{
		bool
			result =
				manager.is_entity_status_equal(
					nullptr,
					EntityActivationStatus::ACTIVE
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnTrue_When_RemoveNonExistingEntity
	)
	{
		bool
			result =
				manager.remove_entity(
					&entity_value_two
				);

		EXPECT_TRUE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnFalse_When_StatusComparedForMissingEntity
	)
	{
		bool
			result =
				manager.is_entity_status_equal(
					&entity_value_three,
					EntityActivationStatus::ACTIVE
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_SetStatusAgain_When_PointerReusedAfterRemoval
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		manager.remove_entity(
			&entity_value_one
		);

		bool
			result =
				manager.set_entity_status(
					&entity_value_one,
					EntityActivationStatus::INACTIVE
				);

		EXPECT_TRUE(
			result
		);

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_one
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::INACTIVE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleMultipleEntities_When_InsertedConcurrently
	)
	{
		std::vector<int>
			values(
				1000
			);

		for
		(
			std::size_t iteration =
				0;
			iteration < values.size();
			++iteration
		)
		{
			values[iteration] =
				static_cast<int>(iteration);
		}

		std::vector<std::thread>
			thread_collection;

		for
		(
			std::size_t iteration =
				0;
			iteration < values.size();
			++iteration
		)
		{
			thread_collection.emplace_back(
				[this, &values, iteration]()
				{
					manager.set_entity_status(
						&values[iteration],
						EntityActivationStatus::ACTIVE
					);
				}
			);
		}

		for
		(
			std::thread&
				thread :
				thread_collection
		)
		{
			thread.join();
		}

		std::size_t
			active_count =
				0;

		for
		(
			std::size_t iteration =
				0;
			iteration < values.size();
			++iteration
		)
		{
			if
			(
				manager.get_entity_status(
					&values[iteration]
				) ==
				EntityActivationStatus::ACTIVE
			)
			{
				++active_count;
			}
		}

		EXPECT_EQ(
			active_count,
			values.size()
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleConcurrentRemoval_When_MultipleThreadsRemove
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		std::thread
			thread_one(
				[this]()
				{
					manager.remove_entity(
						&entity_value_one
					);
				}
			);

		std::thread
			thread_two(
				[this]()
				{
					manager.remove_entity(
						&entity_value_one
					);
				}
			);

		thread_one.join();
		thread_two.join();

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_one
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::NONE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleConcurrentClear_When_ReadOperationsOccur
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		std::atomic<bool>
			stop_flag =
				false;

		std::thread
			reader_thread(
				[this, &stop_flag]()
				{
					while
					(
						!stop_flag.load()
					)
					{
						manager.get_entity_status(
							&entity_value_one
						);
					}
				}
			);

		std::thread
			clear_thread(
				[this, &stop_flag]()
				{
					manager.clear_entities();
					stop_flag =
						true;
				}
			);

		reader_thread.join();
		clear_thread.join();

		EXPECT_EQ(
			manager.get_entity_status(
				&entity_value_one
			),
			EntityActivationStatus::NONE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleAsyncGetStatus_When_UsingFuture
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		std::future<EntityActivationStatus>
			future_status =
				std::async(
					std::launch::async,
					[this]()
					{
						return
							manager.get_entity_status(
								&entity_value_one
							);
					}
				);

		EntityActivationStatus
			status =
				future_status.get();

		EXPECT_EQ(
			status,
			EntityActivationStatus::ACTIVE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleAsyncRemove_When_UsingFuture
	)
	{
		manager.set_entity_status(
			&entity_value_two,
			EntityActivationStatus::ACTIVE
		);

		std::future<bool>
			future_result =
				std::async(
					std::launch::async,
					[this]()
					{
						return
							manager.remove_entity(
								&entity_value_two
							);
					}
				);

		bool
			result =
				future_result.get();

		EXPECT_TRUE(
			result
		);

		EXPECT_EQ(
			manager.get_entity_status(
				&entity_value_two
			),
			EntityActivationStatus::NONE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleStressWithMultipleEntities_When_HighIterationLoad
	)
	{
		std::vector<int>
			entity_collection(
				500
			);

		for
		(
			std::size_t iteration =
				0;
			iteration < entity_collection.size();
			++iteration
		)
		{
			entity_collection[iteration] =
				static_cast<int>(iteration);
		}

		for
		(
			std::size_t iteration =
				0;
			iteration < 10000;
			++iteration
		)
		{
			std::size_t
				index =
					iteration %
					entity_collection.size();

			manager.set_entity_status(
				&entity_collection[index],
				EntityActivationStatus::ACTIVE
			);

			manager.get_entity_status(
				&entity_collection[index]
			);
		}

		std::size_t
			active_count =
				0;

		for
		(
			std::size_t iteration =
				0;
			iteration < entity_collection.size();
			++iteration
		)
		{
			if
			(
				manager.get_entity_status(
					&entity_collection[iteration]
				) ==
				EntityActivationStatus::ACTIVE
			)
			{
				++active_count;
			}
		}

		EXPECT_GT(
			active_count,
			static_cast<std::size_t>(0)
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnTrue_When_ClearCalledOnEmptyCollection
	)
	{
		bool
			result =
				manager.clear_entities();

		EXPECT_TRUE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_UpdateStatus_When_StatusChanges
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		bool
			result =
				manager.set_entity_status(
					&entity_value_one,
					EntityActivationStatus::INACTIVE
				);

		EXPECT_TRUE(
			result
		);

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_one
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::INACTIVE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_UpdateStatus_When_TransitionPendingToActive
	)
	{
		manager.set_entity_status(
			&entity_value_two,
			EntityActivationStatus::PENDING
		);

		bool
			result =
				manager.set_entity_status(
					&entity_value_two,
					EntityActivationStatus::ACTIVE
				);

		EXPECT_TRUE(
			result
		);

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_two
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::ACTIVE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnFalse_When_ComparingWithNoneStatus
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		bool
			result =
				manager.is_entity_status_equal(
					&entity_value_one,
					EntityActivationStatus::NONE
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_NotThrow_When_AllMethodsInvoked
	)
	{
		EXPECT_NO_THROW(
			manager.get_entity_status(
				&entity_value_one
			)
		);

		EXPECT_NO_THROW(
			manager.set_entity_status(
				&entity_value_one,
				EntityActivationStatus::ACTIVE
			)
		);

		EXPECT_NO_THROW(
			manager.remove_entity(
				&entity_value_one
			)
		);

		EXPECT_NO_THROW(
			manager.clear_entities()
		);

		EXPECT_NO_THROW(
			manager.is_entity_status_equal(
				&entity_value_one,
				EntityActivationStatus::ACTIVE
			)
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleConcurrentClearAndInsert
	)
	{
		std::atomic<bool>
			stop_flag =
				false;

		std::thread
			insert_thread(
				[this, &stop_flag]()
				{
					while
					(
						!stop_flag.load()
					)
					{
						manager.set_entity_status(
							&entity_value_one,
							EntityActivationStatus::ACTIVE
						);
					}
				}
			);

		std::thread
			clear_thread(
				[this, &stop_flag]()
				{
					for
					(
						std::size_t iteration =
							0;
						iteration < 2000;
						++iteration
					)
					{
						manager.clear_entities();
					}

					stop_flag =
						true;
				}
			);

		insert_thread.join();
		clear_thread.join();

		EXPECT_TRUE(
			true
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleLargeEntityVolume
	)
	{
		std::vector<int>
			entity_collection(
				2000
			);

		for
		(
			std::size_t iteration =
				0;
			iteration < entity_collection.size();
			++iteration
		)
		{
			entity_collection[iteration] =
				static_cast<int>(
					iteration
				);
		}

		for
		(
			std::size_t iteration =
				0;
			iteration < entity_collection.size();
			++iteration
		)
		{
			manager.set_entity_status(
				&entity_collection[iteration],
				EntityActivationStatus::ACTIVE
			);
		}

		std::size_t
			active_count =
				0;

		for
		(
			std::size_t iteration =
				0;
			iteration < entity_collection.size();
			++iteration
		)
		{
			if
			(
				manager.get_entity_status(
					&entity_collection[iteration]
				) ==
				EntityActivationStatus::ACTIVE
			)
			{
				++active_count;
			}
		}

		EXPECT_EQ(
			active_count,
			entity_collection.size()
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleAsyncClear_When_UsingFuture
	)
	{
		manager.set_entity_status(
			&entity_value_one,
			EntityActivationStatus::ACTIVE
		);

		std::future<bool>
			future_result =
				std::async(
					std::launch::async,
					[this]()
					{
						return
							manager.clear_entities();
					}
				);

		bool
			result =
				future_result.get();

		EXPECT_TRUE(
			result
		);

		EXPECT_EQ(
			manager.get_entity_status(
				&entity_value_one
			),
			EntityActivationStatus::NONE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleMultipleAsyncSetOperations
	)
	{
		std::vector<std::future<bool>>
			future_collection;

		for
		(
			std::size_t iteration =
				0;
			iteration < 50;
			++iteration
		)
		{
			future_collection.push_back(
				std::async(
					std::launch::async,
					[this]()
					{
						return
							manager.set_entity_status(
								&entity_value_two,
								EntityActivationStatus::ACTIVE
							);
					}
				)
			);
		}

		for
		(
			std::future<bool>&
				future :
				future_collection
		)
		{
			EXPECT_TRUE(
				future.get()
			);
		}
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleConcurrentStatusTransitions
	)
	{
		manager.set_entity_status(
			&entity_value_three,
			EntityActivationStatus::PENDING
		);

		std::thread
			thread_one(
				[this]()
				{
					for
					(
						std::size_t iteration =
							0;
						iteration < 3000;
						++iteration
					)
					{
						manager.set_entity_status(
							&entity_value_three,
							EntityActivationStatus::ACTIVE
						);
					}
				}
			);

		std::thread
			thread_two(
				[this]()
				{
					for
					(
						std::size_t iteration =
							0;
						iteration < 3000;
						++iteration
					)
					{
						manager.set_entity_status(
							&entity_value_three,
							EntityActivationStatus::INACTIVE
						);
					}
				}
			);

		thread_one.join();
		thread_two.join();

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_three
				);

		EXPECT_TRUE(
			status ==
			EntityActivationStatus::ACTIVE ||
			status ==
			EntityActivationStatus::INACTIVE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnNone_When_RuntimeDisabledDuringGet
	)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			false;

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_one
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::NONE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnFalse_When_RuntimeDisabledDuringSet
	)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			false;

		bool
			result =
				manager.set_entity_status(
					&entity_value_one,
					EntityActivationStatus::ACTIVE
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnFalse_When_RuntimeDisabledDuringRemove
	)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			false;

		bool
			result =
				manager.remove_entity(
					&entity_value_one
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnFalse_When_RuntimeDisabledDuringClear
	)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			false;

		bool
			result =
				manager.clear_entities();

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_ReturnFalse_When_RuntimeDisabledDuringCompare
	)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			false;

		bool
			result =
				manager.is_entity_status_equal(
					&entity_value_one,
					EntityActivationStatus::ACTIVE
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_HandleNullPointer_When_EdgeHandlingDisabled
	)
	{
		manager.configurations
			.is_feature_edge_case_handling_enabled =
				false;

		bool
			set_result =
				manager.set_entity_status(
					nullptr,
					EntityActivationStatus::ACTIVE
				);

		EntityActivationStatus
			status =
				manager.get_entity_status(
					nullptr
				);

		EXPECT_TRUE(
			set_result
		);

		EXPECT_EQ(
			status,
			EntityActivationStatus::ACTIVE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_Operate_When_ThreadSafetyDisabled
	)
	{
		manager.configurations
			.is_feature_thread_safety_handling_enabled =
				false;

		bool
			result =
				manager.set_entity_status(
					&entity_value_two,
					EntityActivationStatus::ACTIVE
				);

		EXPECT_TRUE(
			result
		);

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_two
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::ACTIVE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_UpdateStatus_When_TransitionInactiveToActive
	)
	{
		manager.set_entity_status(
			&entity_value_three,
			EntityActivationStatus::INACTIVE
		);

		bool
			result =
				manager.set_entity_status(
					&entity_value_three,
					EntityActivationStatus::ACTIVE
				);

		EXPECT_TRUE(
			result
		);

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_three
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::ACTIVE
		);
	}

	TEST_F(
		EntityActivationManagerTest,
		Should_UpdateStatus_When_TransitionInactiveToPending
	)
	{
		manager.set_entity_status(
			&entity_value_three,
			EntityActivationStatus::INACTIVE
		);

		bool
			result =
				manager.set_entity_status(
					&entity_value_three,
					EntityActivationStatus::PENDING
				);

		EXPECT_TRUE(
			result
		);

		EntityActivationStatus
			status =
				manager.get_entity_status(
					&entity_value_three
				);

		EXPECT_EQ(
			status,
			EntityActivationStatus::PENDING
		);
	}
}

#endif
