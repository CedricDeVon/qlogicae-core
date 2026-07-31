#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		AsynchronousBatchManager \
	)

#include "../includes/asynchronous_batch_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_ReturnEmpty_When_EmptyValuesForAwait
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_TRUE
		(
			result
				.empty()
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_ReturnEmpty_When_EmptyValuesForAsync
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		auto
			result =
				asynchronous_batch_manager
					.execute_async_batch
					(
						values
					);

		EXPECT_TRUE
		(
			result
				.empty()
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_ReturnValue_When_SingleAwaitTask
	)
	{
		auto
			values =
				create_single_value_batch();

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_EQ
		(
			result.size(),
			static_cast<std::size_t>(1)
		);

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				result["task"]
			),
			5
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_ReturnFuture_When_SingleAsyncTask
	)
	{
		auto
			values =
				create_single_value_batch();

		auto
			result =
				asynchronous_batch_manager
					.execute_async_batch
					(
						values
					);

		EXPECT_EQ
		(
			result.size(),
			static_cast<std::size_t>(1)
		);

		auto
			value =
				result["task"]
					.get();

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				value
			),
			5
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_SkipNullCallback_When_CallbackIsNull
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		values["null_task"] =
			std::function<std::any()>();

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_TRUE
		(
			result
				.empty()
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_HandleException_When_CallbackThrows
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		values["throw_task"] =
			[]
			()
			{
				try
				{
					throw
						std::runtime_error
						(
							"error"
						);

					return
						std::any();
				}
				catch (...)
				{
					SUCCEED();

					return
						std::any();
				}				
			};

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_FALSE
		(
			result
				.empty()
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_HandleAsyncException_When_FutureGetThrows
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		values["throw_task"] =
			[]
			()
			{
				throw
					std::runtime_error
					(
						"async_error"
					);
				return
					std::any();
			};

		auto
			result =
				asynchronous_batch_manager
					.execute_async_batch
					(
						values
					);

		EXPECT_EQ
		(
			result.size(),
			static_cast<std::size_t>(1)
		);

		EXPECT_THROW
		(
			result["throw_task"]
				.get(),
			std::runtime_error
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_RunConcurrentCalls_When_MultipleThreadsExecute
	)
	{
		std::atomic<int>
			counter =
				0;

		std::mutex
			mutex;

		std::condition_variable
			condition;

		bool
			ready =
				false;

		auto
			thread_function =
				[
					&
				]
				()
				{
					std::unique_lock
					<
						std::mutex
					>
						lock
						(
							mutex
						);

					condition
						.wait
						(
							lock,
							[
								&
							]
							()
							{
								return
									ready;
							}
						);

					auto
						values =
							create_single_value_batch();

					auto
						result =
							asynchronous_batch_manager
								.execute_await_batch
								(
									values
								);

					if
					(
						!result
							.empty()
					)
					{
						counter
							.fetch_add
							(
								1
							);
					}
				};

		std::thread
			thread_one
			(
				thread_function
			);

		std::thread
			thread_two
			(
				thread_function
			);

		{
			std::lock_guard
			<
				std::mutex
			>
				lock
				(
					mutex
				);

			ready =
				true;
		}

		condition
			.notify_all();

		thread_one
			.join();

		thread_two
			.join();

		EXPECT_EQ
		(
			counter
				.load(),
			2
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_HandleStressLoad_When_ManyTasksExecute
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		const int
			task_count =
				100;

		for
		(
			int
				index =
					0;
			index <
				task_count;
			index++
		)
		{
			values
				[
					std::to_string
					(
						index
					)
				] =
				[
					index
				]
				()
				{
					return
						std::any
						(
							index
						);
				};
		}

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_EQ
		(
			result.size(),
			static_cast<std::size_t>
			(
				task_count
			)
		);
	}

	INSTANTIATE_TEST_CASE_P
	(
		AsynchronousBatchManagerBatchSizes,
		AsynchronousBatchManagerParameterizedTest,
		::testing::Values
		(
			1,
			5,
			10,
			50
		)
	);

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_HandleMixedSuccessAndFailure_When_BatchContainsThrowingTask
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		values["success_one"] =
			[]
			()
			{
				return
					std::any(1);
			};

		values["failure"] =
			[]
			()
			{
				try
				{
					throw
						std::runtime_error
						(
							"failure"
						);
					return
						std::any();
				}
				catch (...)
				{
					SUCCEED();

					return
						std::any();
				}				
			};

		values["success_two"] =
			[]
			()
			{
				return
					std::any(2);
			};

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_EQ
		(
			result.size(),
			static_cast<std::size_t>
			(
				3
			)
		);

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				result["success_one"]
			),
			1
		);

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				result["success_two"]
			),
			2
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_ExecuteAsyncConcurrently_When_MultipleThreadsCallAsync
	)
	{
		std::atomic<int>
			counter =
				0;

		auto
			thread_function =
				[
					&
				]
				()
				{
					auto
						values =
							create_single_value_batch();

					auto
						result =
							asynchronous_batch_manager
								.execute_async_batch
								(
									values
								);

					auto
						value =
							result["task"]
								.get();

					if
					(
						std::any_cast<int>
						(
							value
						)
						==
						5
					)
					{
						counter
							.fetch_add
							(
								1
							);
					}
				};

		std::thread
			thread_one
			(
				thread_function
			);

		std::thread
			thread_two
			(
				thread_function
			);

		thread_one
			.join();

		thread_two
			.join();

		EXPECT_EQ
		(
			counter.load(),
			2
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_HandleMixedAwaitAndAsync_When_ConcurrentCallsOccur
	)
	{
		std::atomic<int>
			counter =
				0;

		auto
			await_thread =
				[
					&
				]
				()
				{
					auto
						values =
							create_single_value_batch();

					auto
						result =
							asynchronous_batch_manager
								.execute_await_batch
								(
									values
								);

					if
					(
						std::any_cast<int>
						(
							result["task"]
						)
						==
						5
					)
					{
						counter
							.fetch_add
							(
								1
							);
					}
				};

		auto
			async_thread =
				[
					&
				]
				()
				{
					auto
						values =
							create_single_value_batch();

					auto
						result =
							asynchronous_batch_manager
								.execute_async_batch
								(
									values
								);

					auto
						value =
							result["task"]
								.get();

					if
					(
						std::any_cast<int>
						(
							value
						)
						==
						5
					)
					{
						counter
							.fetch_add
							(
								1
							);
					}
				};

		std::thread
			thread_one
			(
				await_thread
			);

		std::thread
			thread_two
			(
				async_thread
			);

		thread_one
			.join();

		thread_two
			.join();

		EXPECT_EQ
		(
			counter.load(),
			2
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_SkipNullAndExecuteValid_When_BatchContainsNullAndValid
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		values["null_task"] =
			std::function<std::any()>();

		values["valid_task"] =
			[]
			()
			{
				return
					std::any(10);
			};

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_EQ
		(
			result.size(),
			static_cast<std::size_t>
			(
				1
			)
		);

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				result["valid_task"]
			),
			10
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_ReturnCorrectKeys_When_MultipleNamedTasksExecute
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		values["alpha"] =
			[]
			()
			{
				return
					std::any(1);
			};

		values["beta"] =
			[]
			()
			{
				return
					std::any(2);
			};

		values["gamma"] =
			[]
			()
			{
				return
					std::any(3);
			};

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_TRUE
		(
			result.contains
			(
				"alpha"
			)
		);

		EXPECT_TRUE
		(
			result.contains
			(
				"beta"
			)
		);

		EXPECT_TRUE
		(
			result.contains
			(
				"gamma"
			)
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_HandleAsyncStress_When_ManyAsyncTasksExecute
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		const int
			task_count =
				100;

		for
		(
			int
				index =
					0;
			index <
				task_count;
			index++
		)
		{
			values
				[
					std::to_string
					(
						index
					)
				] =
				[
					index
				]
				()
				{
					return
						std::any
						(
							index
						);
				};
		}

		auto
			result =
				asynchronous_batch_manager
					.execute_async_batch
					(
						values
					);

		EXPECT_EQ
		(
			result.size(),
			static_cast<std::size_t>
			(
				task_count
			)
		);

		for
		(
			int
				index =
					0;
			index <
				task_count;
			index++
		)
		{
			auto
				value =
					result
						[
							std::to_string
							(
								index
							)
						]
							.get();

			EXPECT_EQ
			(
				std::any_cast<int>
				(
					value
				),
				index
			);
		}
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_HandleSlowTasks_When_ExecutionOverlaps
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		values["slow_one"] =
			[]
			()
			{
				std::this_thread::sleep_for
				(
					std::chrono::milliseconds
					(
						50
					)
				);

				return
					std::any(1);
			};

		values["slow_two"] =
			[]
			()
			{
				std::this_thread::sleep_for
				(
					std::chrono::milliseconds
					(
						50
					)
				);

				return
					std::any(2);
			};

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_EQ
		(
			result.size(),
			static_cast<std::size_t>
			(
				2
			)
		);

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				result["slow_one"]
			),
			1
		);

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				result["slow_two"]
			),
			2
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_HandleEmptyKey_When_TaskKeyIsEmptyString
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		values[""] =
			[]
			()
			{
				return
					std::any(42);
			};

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_EQ
		(
			result.size(),
			static_cast<std::size_t>
			(
				1
			)
		);

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				result[""]
			),
			42
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_HandleUncaughtException_When_CallbackThrowsInAwait
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		values["throw_task"] =
			[]
			()
			{
				throw
					std::runtime_error
					(
						"error"
					);
				return
					std::any();
			};

		EXPECT_THROW
		(
			asynchronous_batch_manager
				.execute_await_batch
				(
					values
				),
			std::runtime_error
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_ReturnValidFuture_When_AsyncTaskCreated
	)
	{
		auto
			values =
				create_single_value_batch();

		auto
			result =
				asynchronous_batch_manager
					.execute_async_batch
					(
						values
					);

		EXPECT_TRUE
		(
			result["task"]
				.valid()
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_ThrowFutureError_When_FutureGetCalledTwice
	)
	{
		auto
			values =
				create_single_value_batch();

		auto
			result =
				asynchronous_batch_manager
					.execute_async_batch
					(
						values
					);

		auto
			future =
				std::move
				(
					result["task"]
				);

		future
			.get();

		EXPECT_THROW
		(
			future
				.get(),
			std::future_error
		);
	}

	TEST_F
	(
		AsynchronousBatchManagerTest,
		Should_ReturnCorrectValues_When_MultipleNamedTasksExecute
	)
	{
		std::unordered_map
		<
			std::string,
			std::function<std::any()>
		>
			values;

		values["alpha"] =
			[]
			()
			{
				return
					std::any(1);
			};

		values["beta"] =
			[]
			()
			{
				return
					std::any(2);
			};

		values["gamma"] =
			[]
			()
			{
				return
					std::any(3);
			};

		auto
			result =
				asynchronous_batch_manager
					.execute_await_batch
					(
						values
					);

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				result["alpha"]
			),
			1
		);

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				result["beta"]
			),
			2
		);

		EXPECT_EQ
		(
			std::any_cast<int>
			(
				result["gamma"]
			),
			3
		);
	}
}

#endif
