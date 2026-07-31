#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		AbstractClass \
	)

#include "../includes/abstract_class.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		AbstractConfigurationsTest,
		Should_EnableUtilityThreadSafety_When_OverrideDisabled
	)
	{
		ASSERT_TRUE(
			configurations
				.is_thread_safety_enabled_for_utility_handling()
		);
	}

	TEST_F(
		AbstractConfigurationsTest,
		Should_EnableFeatureThreadSafety_When_OverrideDisabled
	)
	{
		configurations
			.is_feature_thread_safety_handling_enabled = false;

		ASSERT_FALSE(
			configurations
				.is_thread_safety_enabled_for_feature_handling()
		);
	}

	TEST_F(
		AbstractConfigurationsTest,
		Should_EnableErrorThreadSafety_When_OverrideDisabled
	)
	{
		ASSERT_TRUE(
			configurations
				.is_thread_safety_enabled_for_error_handling()
		);
	}

	TEST_P(
		AbstractConfigurationsParameterizedTest,
		Should_OverrideAllThreadSafety_When_OverrideEnabled
	)
	{
		bool param = GetParam();

		configurations
			.is_thread_safety_handling_override_enabled =
				param;

		configurations
			.is_thread_safety_handling_enabled =
				param;

		ASSERT_EQ(
			configurations
				.is_thread_safety_enabled_for_utility_handling(),
			GetParam() ||
			configurations
				.is_utility_thread_safety_handling_enabled
		);

		ASSERT_EQ(
			configurations
				.is_thread_safety_enabled_for_feature_handling(),
			GetParam() ||
			configurations
				.is_feature_thread_safety_handling_enabled
		);

		ASSERT_EQ(
			configurations
				.is_thread_safety_enabled_for_error_handling(),
			GetParam() ||
			configurations
				.is_error_thread_safety_handling_enabled
		);
	}

	INSTANTIATE_TEST_CASE_P(
		OverrideValues,
		AbstractConfigurationsParameterizedTest,
		::testing::Values(
			false,
			true
		)
	);

	TEST_F(
		AbstractClassTest,
		Should_ConstructSuccessfully_When_DefaultConfiguration
	)
	{
		ASSERT_TRUE(
			instance.construct()
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_DestructSuccessfully_When_DefaultConfiguration
	)
	{
		ASSERT_TRUE(
			instance.destruct()
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_ResetConfigurations_When_ResetCalled
	)
	{
		ASSERT_TRUE(
			instance.reset()
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_SetupConfigurations_When_NewConfigurationProvided
	)
	{
		TestConfigurations
			new_configurations;

		new_configurations
			.is_thread_safety_handling_override_enabled =
				true;

		ASSERT_TRUE(
			instance.setup(
				new_configurations
			)
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_HandleException_When_ExceptionThrown
	)
	{
		try
		{
			instance.throwing_method();
		}
		catch
		(
			const std::exception&
		)
		{
			EXPECT_THROW(
				instance.handle_error_outputs(
					std::string("error")
				),
				std::runtime_error
			);
		}
	}

	TEST_F(
		AbstractClassTest,
		Should_SupportAsynchronousConstruction_When_UsedWithAsync
	)
	{
		auto
			future_result =
				std::async(
					std::launch::async,
					[this]()
					{
						return
							instance.construct();
					}
				);

		ASSERT_TRUE(
			future_result.get()
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_HandleMultithreadedAccess_When_StressTested
	)
	{
		std::atomic<bool>
			is_successful =
				true;

		std::vector<std::thread>
			threads;

		for
		(
			std::size_t
				thread_index =
					0;
			thread_index <
				8;
			thread_index++
		)
		{
			threads.emplace_back(
				[this, &is_successful]()
				{
					for
					(
						std::size_t
							iteration_index =
								0;
						iteration_index <
							1000;
						iteration_index++
					)
					{
						if
						(
							!instance.construct()
						)
						{
							is_successful =
								false;
						}
					}
				}
			);
		}

		for
		(
			auto&
				thread_instance :
					threads
		)
		{
			thread_instance.join();
		}

		ASSERT_TRUE(
			is_successful.load()
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_CompleteStressTest_When_UnderLoad
	)
	{
		for
		(
			std::size_t
				iteration_index =
					0;
			iteration_index <
				50000;
			iteration_index++
		)
		{
			ASSERT_TRUE(
				instance.construct()
			);
		}
	}

	TEST(
		AbstractClassAsyncTest,
		Should_SynchronizeUsingPromise_When_AsynchronouslyConstructed
	)
	{
		std::promise<bool>
			promise_value;

		std::future<bool>
			future_value =
				promise_value.get_future();

		std::thread
			worker_thread(
				[&promise_value]()
				{
					TestClass
						instance;

					promise_value.set_value(
						instance.construct()
					);
				}
			);

		ASSERT_TRUE(
			future_value.get()
		);

		worker_thread.join();
	}

	TEST(
		AbstractClassThreadingTest,
		Should_CoordinateThreadsUsingConditionVariable_When_Contended
	)
	{
		std::mutex
			synchronization_mutex;

		std::condition_variable
			condition_variable_instance;

		bool
			is_ready =
				false;

		TestClass
			instance;

		std::thread
			waiting_thread(
				[&]()
				{
					std::unique_lock<std::mutex>
						lock(
							synchronization_mutex
						);

					condition_variable_instance.wait(
						lock,
						[&]()
						{
							return
								is_ready;
						}
					);

					instance.construct();
				}
			);

		{
			std::lock_guard<std::mutex>
				lock(
					synchronization_mutex
				);

			is_ready =
				true;
		}

		condition_variable_instance.notify_one();

		waiting_thread.join();

		ASSERT_TRUE(
			instance.destruct()
		);
	}

	TEST(
		AbstractConfigurationsEdgeCaseTest,
		Should_DisableAllThreadSafety_When_AllFlagsFalse
	)
	{
		TestConfigurations
			configurations;

		configurations
			.is_thread_safety_handling_override_enabled =
				false;

		configurations
			.is_utility_thread_safety_handling_enabled =
				false;

		configurations
			.is_feature_thread_safety_handling_enabled =
				false;

		configurations
			.is_error_thread_safety_handling_enabled =
				false;

		ASSERT_FALSE(
			configurations
				.is_thread_safety_enabled_for_utility_handling()
		);

		ASSERT_FALSE(
			configurations
				.is_thread_safety_enabled_for_feature_handling()
		);

		ASSERT_FALSE(
			configurations
				.is_thread_safety_enabled_for_error_handling()
		);
	}

	TEST_F(
		AbstractConfigurationsTest,
		Should_DisableUtilityRuntimeExecution_When_FlagFalse
	)
	{
		configurations
			.is_utility_runtime_execution_handling_enabled =
				false;

		ASSERT_TRUE(
			configurations
				.is_runtime_execution_disabled_for_utility_handling()
		);
	}

	TEST_F(
		AbstractConfigurationsTest,
		Should_DisableFeatureRuntimeExecution_When_FlagFalse
	)
	{
		configurations
			.is_feature_runtime_execution_handling_enabled =
				false;

		ASSERT_TRUE(
			configurations
				.is_runtime_execution_disabled_for_feature_handling()
		);
	}

	TEST_F(
		AbstractConfigurationsTest,
		Should_DisableErrorRuntimeExecution_When_FlagFalse
	)
	{
		configurations
			.is_error_runtime_execution_handling_enabled =
				false;

		ASSERT_TRUE(
			configurations
				.is_runtime_execution_disabled_for_error_handling()
		);
	}

	TEST_P(
		AbstractConfigurationsParameterizedTest,
		Should_OverrideRuntimeExecution_When_OverrideEnabled
	)
	{
		configurations
			.is_runtime_execution_handling_override_enabled =
				GetParam();

		ASSERT_EQ(
			configurations
				.is_runtime_execution_enabled_for_utility_handling(),
			GetParam() ||
			configurations
				.is_utility_runtime_execution_handling_enabled
		);

		ASSERT_EQ(
			configurations
				.is_runtime_execution_enabled_for_feature_handling(),
			GetParam() ||
			configurations
				.is_feature_runtime_execution_handling_enabled
		);

		ASSERT_EQ(
			configurations
				.is_runtime_execution_enabled_for_error_handling(),
			GetParam() ||
			configurations
				.is_error_runtime_execution_handling_enabled
		);
	}

	INSTANTIATE_TEST_CASE_P(
		RuntimeOverrideValues,
		AbstractConfigurationsParameterizedTest,
		::testing::Values(
			false,
			true
		)
	);

	TEST_F(
		AbstractConfigurationsTest,
		Should_EnableEdgeCase_When_OverrideEnabled
	)
	{
		configurations
			.is_edge_case_handling_override_enabled =
				true;

		configurations
			.is_edge_case_handling_enabled =
				true;

		ASSERT_TRUE(
			configurations
				.is_edge_case_enabled_for_utility_handling()
		);

		ASSERT_TRUE(
			configurations
				.is_edge_case_enabled_for_feature_handling()
		);

		ASSERT_TRUE(
			configurations
				.is_edge_case_enabled_for_error_handling()
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_Not_Construct_When_RuntimeExecutionDisabled
	)
	{
		instance
			.configurations
			.is_feature_runtime_execution_handling_enabled =
				false;

		ASSERT_FALSE(
			instance.construct()
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_Not_Destruct_When_RuntimeExecutionDisabled
	)
	{
		instance
			.configurations
			.is_feature_runtime_execution_handling_enabled =
				false;

		ASSERT_FALSE(
			instance.destruct()
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_Not_Reset_When_RuntimeExecutionDisabled
	)
	{
		instance
			.configurations
			.is_feature_runtime_execution_handling_enabled =
				false;

		ASSERT_FALSE(
			instance.reset()
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_Not_Setup_When_RuntimeExecutionDisabled
	)
	{
		TestConfigurations
			new_configurations;

		instance
			.configurations
			.is_feature_runtime_execution_handling_enabled =
				false;

		ASSERT_FALSE(
			instance.setup(
				new_configurations
			)
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_Handle_Null_Callback_When_EdgeCaseEnabled
	)
	{
		instance
			.configurations
				.is_edge_case_handling_override_enabled =
					true;

		instance
			.configurations
				.is_edge_case_handling_enabled =
					true;

		ASSERT_THROW(
			instance.handle_callback_wrapper<void>(
				nullptr
			),
			std::runtime_error
		);
	}

	TEST_F(
		AbstractClassTest,
		Should_Invoke_Callback_When_Valid
	)
	{
		std::atomic<bool>
			called =
				false;

		instance.handle_callback_wrapper<void>(
			[&called]()
			{
				called =
					true;
			}
		);

		ASSERT_TRUE(
			called.load()
		);
	}

	TEST(
		AbstractClassFailureTest,
		Should_ReturnFalse_When_ErrorHandlerFails
	)
	{
		FailingTestClass
			instance;

		ASSERT_THROW(
			{
				instance.handle_callback_wrapper<bool>(
					[]()
					{
						throw std::runtime_error(
							"failure"
						);
					}
				);
			},
			std::runtime_error
		);
	}

	TEST(
		AbstractClassDestructorTest,
		Should_Not_Throw_When_DestructThrows
	)
	{
		ASSERT_NO_THROW(
			{
				class LocalClass :
					public AbstractClass<TestConfigurations>
				{
				public:
					bool
						destruct()
					{
						throw std::runtime_error(
							"destruct"
						);
					}
				} instance;
			}
		);
	}

}

#endif

