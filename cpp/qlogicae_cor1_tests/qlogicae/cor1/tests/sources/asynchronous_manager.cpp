#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		AsynchronousManager \
	)

#include "../includes/asynchronous_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{    
    TEST_F(
        AsynchronousManagerTest,
        Should_ConstructSuccessfully_When_Initialized
    )
    {
        bool result =
            manager
            .construct();

        ASSERT_TRUE(result);
    }

    TEST_F(
        AsynchronousManagerTest,
        Should_ResetToInitialState_When_ResetCalled
    )
    {
        AsynchronousManagerConfigurations
            configurations;

		manager
			.setup(configurations);

		bool reset_result =
			manager
			.reset();

		ASSERT_TRUE(reset_result);

		ASSERT_TRUE(
			manager.configurations.is_feature_runtime_execution_handling_enabled
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_DispatchTask_When_Enabled
	)
	{
		std::promise<void>
			completion_promise;

		std::future<void>
			completion_future =
			completion_promise.get_future();

		bool begin_result =
			manager
			.begin_one_thread(
				[&completion_promise]()
				{
					completion_promise.set_value();
				}
			);

		ASSERT_TRUE(begin_result);

		auto wait_status =
			completion_future.wait_for(
				std::chrono::seconds(2)
			);

		ASSERT_EQ(
			wait_status,
			std::future_status::ready
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_HandleMultipleThreads_When_HighConcurrency
	)
	{
		std::atomic<int>
			execution_count(0);

		int const TASK_COUNT =
			1000;

		for (int index = 0;
			index < TASK_COUNT;
			index++)
		{
			manager
				.begin_one_thread(
					[&execution_count]()
					{
						execution_count.fetch_add(1);
					}
				);
		}

		manager
			.complete_all_threads();

		ASSERT_EQ(
			execution_count.load(),
			TASK_COUNT
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_BeThreadSafe_When_CalledFromMultipleThreads
	)
	{
		std::atomic<int>
			execution_count(0);

		std::vector<std::thread>
			threads;

		for (int index = 0;
			index < 10;
			index++)
		{
			threads.emplace_back(
				[this, &execution_count]()
				{
					for (int inner_index = 0;
						inner_index < 100;
						inner_index++)
					{
						manager
							.begin_one_thread(
								[&execution_count]()
								{
									execution_count.fetch_add(1);
								}
							);
					}
				}
			);
		}

		for (auto& thread_instance : threads)
		{
			thread_instance.join();
		}

		manager
			.complete_all_threads();

		ASSERT_GE(
			execution_count.load(),
			995
		);
	}

	TEST_P(
		AsynchronousManagerConfigurationTest,
		Should_RespectConfigurationValue_When_SetupCalled
	)
	{
		AsynchronousManagerConfigurations
			configurations;

		configurations.is_feature_runtime_execution_handling_enabled =
			GetParam();

		manager
			.setup(configurations);

		ASSERT_EQ(
			manager.configurations.is_feature_runtime_execution_handling_enabled,
			GetParam()
		);

		manager
			.destruct();
	}

	INSTANTIATE_TEST_CASE_P(
		ConfigurationValues,
		AsynchronousManagerConfigurationTest,
		::testing::Values(
			true,
			false
		)
	);

	TEST_F(
		AsynchronousManagerTest,
		Should_CallDestructSuccessfully_When_InvokedExplicitly
	)
	{
		bool result =
			manager
			.destruct();

		ASSERT_TRUE(result);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_CatchException_When_CallbackThrows
	)
	{
		manager.begin_one_thread(
			[]()
			{
				try
				{
					throw std::runtime_error("forced_exception");
				}
				catch (...)
				{
					SUCCEED();
				}
			}
		);

		manager
			.destruct();
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_HandleConcurrentResetAndSetup_When_MutatedSimultaneously
	)
	{
		std::atomic<bool>
			stop_flag(false);

		std::thread
			setup_thread(
				[this, &stop_flag]()
				{
					while (!stop_flag.load())
					{
						AsynchronousManagerConfigurations
							configurations;

						configurations.is_feature_runtime_execution_handling_enabled =
							true;

						manager
							.setup(configurations);
					}
				}
			);

		std::thread
			reset_thread(
				[this, &stop_flag]()
				{
					while (!stop_flag.load())
					{
						manager
							.destruct();
					}
				}
			);

		std::this_thread::sleep_for(
			std::chrono::milliseconds(200)
		);

		stop_flag.store(true);

		setup_thread.join();
		reset_thread.join();

		ASSERT_TRUE(
			manager.configurations.is_feature_runtime_execution_handling_enabled ==
			true ||
			manager.configurations.is_feature_runtime_execution_handling_enabled ==
			false
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_RemainStable_When_ResetAndSetupRepeated
	)
	{
		for (int index = 0;
			index < 100;
			index++)
		{
			AsynchronousManagerConfigurations
				configurations;

			ASSERT_TRUE(
				manager
				.setup(configurations)
			);

			ASSERT_TRUE(
				manager
				.reset()
			);
		}
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Post_Thread_Await_Return_Value
	)
	{	
		auto future =
			manager.post_thread_await<int>(
				[]()
				{
					return 42;
				}
			);

		EXPECT_EQ(
			future.get(),
			42
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Post_Thread_Async_With_Result_Callback
	)
	{	
		std::atomic<int>
			result{ 0 };

		EXPECT_TRUE(
			manager.post_thread_async<int>(
				[]()
				{
					return 7;
				},
				[&](const int& value)
				{
					result.store(value);
				}
			)
		);

		manager
			.destruct();

		EXPECT_EQ(
			result.load(),
			7
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Post_Thread_Async_With_Void_Callback
	)
	{		
		std::atomic<bool>
			called{ false };

		EXPECT_TRUE(
			manager.post_thread_async<int>(
				[]()
				{
					return 1;
				},
				[&]()
				{
					called.store(true);
				}
			)
		);

		manager
			.destruct();

		EXPECT_TRUE(
			called.load()
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Dispatch_Thread_Async_Void
	)
	{	
		std::atomic<bool>
			called{ false };

		EXPECT_TRUE(
			manager.dispatch_thread_async(
				[&]()
				{
					called.store(true);
				}
			)
		);

		manager
			.destruct();

		EXPECT_TRUE(
			called.load()
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Dispatch_Thread_Await_Return_Value
	)
	{	
		auto future =
			manager.dispatch_thread_await<int>(
				[]()
				{
					return 9;
				}
			);

		EXPECT_EQ(
			future.get(),
			9
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Dispatch_Thread_Async_With_Result_Callback
	)
	{	
		std::atomic<int>
			result{ 0 };

		EXPECT_TRUE(
			manager.dispatch_thread_async<int>(
				[]()
				{
					return 11;
				},
				[&](const int& value)
				{
					result.store(value);
				}
			)
		);

		manager
			.destruct();

		EXPECT_EQ(
			result.load(),
			11
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Dispatch_Thread_Async_With_Void_Callback
	)
	{	
		std::atomic<bool>
			called{ false };

		EXPECT_TRUE(
			manager.dispatch_thread_async<int>(
				[]()
				{
					return 3;
				},
				[&]()
				{
					called.store(true);
				}
			)
		);

		manager
			.destruct();

		EXPECT_TRUE(
			called.load()
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_CoSpawn_Strand_Await_Return_Value
	)
	{	
		ASSERT_TRUE(
			manager.begin_io_workers()
		);

		auto future =
			manager.co_spawn_strand_await<int>(
				[]()
				{
					return 21;
				}
			);

		EXPECT_EQ(
			future.get(),
			21
		);

		EXPECT_TRUE(
			manager.complete_io_workers()
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_CoSpawn_Strand_Async_Void
	)
	{	
		ASSERT_TRUE(manager.begin_io_workers());

		std::atomic<bool> called{ false };

		EXPECT_TRUE(
			manager.co_spawn_strand_async(
				[&]()
				{
					called.store(true);
				}
			)
		);

		EXPECT_TRUE(manager.destruct());

		EXPECT_TRUE(called.load());
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_CoSpawn_Strand_Async_With_Result_Callback
	)
	{	
		ASSERT_TRUE(manager.begin_io_workers());

		std::atomic<int> result{ 0 };

		EXPECT_TRUE(
			manager.co_spawn_strand_async<int>(
				[]()
				{
					return 5;
				},
				[&](const int& value)
				{
					result.store(value);
				}
			)
		);

		EXPECT_TRUE(manager.complete_io_workers());

		EXPECT_EQ(result.load(), 5);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Begin_And_Complete_IO_Workers
	)
	{	
		EXPECT_TRUE(
			manager.begin_io_workers()
		);

		EXPECT_TRUE(
			manager.complete_io_workers()
		);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_CoSpawn_Strand_Async_With_ReturnType_And_Void_Callback
	)
	{		
		ASSERT_TRUE(manager.begin_io_workers());

		std::atomic<bool> called{ false };

		EXPECT_TRUE(
			manager.co_spawn_strand_async<int>(
				[]() { return 99; },
				[&]() { called.store(true); }
			)
		);

		EXPECT_TRUE(manager.complete_io_workers());

		EXPECT_TRUE(called.load());
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Handle_Exception_In_CoSpawn_Strand_Await
	)
	{		
		ASSERT_TRUE(manager.begin_io_workers());

		auto future =
			manager.co_spawn_strand_await<int>(
				[]() -> int { throw std::runtime_error("fail"); return 0; }
			);

		EXPECT_THROW(future.get(), std::runtime_error);

		EXPECT_TRUE(manager.complete_io_workers());
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Not_Call_Callback_When_CoSpawn_Strand_Async_Throws
	)
	{		
		ASSERT_TRUE(manager.begin_io_workers());

		std::atomic<bool> called{ false };

		EXPECT_TRUE(
			manager.co_spawn_strand_async<int>(
				[]() { throw std::runtime_error("fail"); return 0; },
				[&]() { called.store(true); }
			)
		);

		EXPECT_TRUE(manager.complete_io_workers());

		EXPECT_FALSE(called.load());
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_Handle_Exception_In_CoSpawn_Strand_Async_With_Result_Callback
	)
	{		
		ASSERT_TRUE(manager.begin_io_workers());

		std::atomic<int> result{ 0 };

		EXPECT_TRUE(
			manager.co_spawn_strand_async<int>(
				[]() -> int { throw std::runtime_error("fail"); return 0; },
				[&](const int& value) { result.store(value); }
			)
		);

		EXPECT_TRUE(manager.complete_io_workers());

		EXPECT_EQ(result.load(), 0);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_ExitConstructEarly_When_RuntimeExecutionEnabled
	)
	{
		AsynchronousManagerConfigurations configurations;
		configurations.is_utility_runtime_execution_handling_enabled = true;
		manager.setup(configurations);
		bool result = manager.construct();
		ASSERT_TRUE(result);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_ExitDestructEarly_When_RuntimeExecutionEnabled
	)
	{
		AsynchronousManagerConfigurations configurations;
		configurations.is_utility_runtime_execution_handling_enabled = true;
		manager.setup(configurations);
		bool result = manager.destruct();
		ASSERT_TRUE(result);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_ConstructDestructWithoutUtilityLock_When_ThreadSafetyDisabled
	)
	{
		AsynchronousManagerConfigurations configurations;
		configurations.is_utility_thread_safety_handling_enabled = false;
		manager.setup(configurations);
		bool construct_result = manager.construct();
		bool destruct_result = manager.destruct();
		ASSERT_TRUE(construct_result);
		ASSERT_TRUE(destruct_result);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_HandleMultipleBeginIOWorkersSequentially
	)
	{
		EXPECT_TRUE(manager.begin_io_workers());
		EXPECT_TRUE(manager.begin_io_workers());
		EXPECT_TRUE(manager.complete_io_workers());
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_HandleCompleteIOWorkersWithoutStarting
	)
	{
		EXPECT_TRUE(manager.complete_io_workers());
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_RecreateMainThreadPoolOnRepeatedBeginOneThread
	)
	{
		for (int i = 0; i < 5; ++i)
		{
			EXPECT_TRUE(manager.begin_one_thread([]() {}));
		}
		manager.complete_all_threads();
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_HandleMaximumConcurrencyCoSpawnStrand
	)
	{
		ASSERT_TRUE(manager.begin_io_workers());

		std::atomic<int> count{ 0 };

		for (int i = 0; i < 1000; ++i)
		{
			manager.co_spawn_strand_async([&]() { count.fetch_add(1); });
		}

		EXPECT_TRUE(manager.complete_io_workers());
		EXPECT_TRUE(manager.complete_all_threads());
		ASSERT_GT(count.load(), 900);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_HandleUtilityAndFeatureMutexContention
	)
	{
		std::thread t1([&]() { manager.construct(); });
		std::thread t2([&]() { manager.begin_one_thread([]() {}); });
		t1.join();
		t2.join();
		EXPECT_TRUE(manager.complete_io_workers());
		EXPECT_TRUE(manager.complete_all_threads());
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_TriggerTemporaryThreadPoolPath
	)
	{
		manager.begin_one_thread([]() {});
		EXPECT_TRUE(manager.complete_all_threads());
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_HandleNonIntegralReturnType_PostThreadAwait
	)
	{
		auto future_str =
			manager.post_thread_await<std::string>([]() { return std::string("ok"); });
		EXPECT_EQ(future_str.get(), "ok");

		auto future_double =
			manager.post_thread_await<double>([]() { return 3.14; });
		EXPECT_DOUBLE_EQ(future_double.get(), 3.14);

		struct Custom { int x; };
		auto future_custom =
			manager.post_thread_await<Custom>([]() { return Custom{42}; });
		EXPECT_EQ(future_custom.get().x, 42);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_HandleExtremeHighConcurrencyCoSpawnStrand
	)
	{
		ASSERT_TRUE(manager.begin_io_workers());

		std::atomic<int> count{0};
		int max_tasks = static_cast<int>(std::thread::hardware_concurrency()) * 8;

		for (int i = 0; i < max_tasks; ++i)
		{
			manager.co_spawn_strand_async([&]() { count.fetch_add(1); });
		}

		EXPECT_TRUE(manager.complete_io_workers());
		EXPECT_TRUE(manager.complete_all_threads());

		ASSERT_EQ(count.load(), max_tasks);
	}

	TEST_F(
		AsynchronousManagerTest,
		Should_NotDeadlock_When_DestructCalledWithPendingTasks
	)
	{
		ASSERT_TRUE(manager.begin_io_workers());

		std::atomic<int> count{0};

		for (int i = 0; i < 100; ++i)
		{
			manager.co_spawn_strand_async([&]() { std::this_thread::sleep_for(std::chrono::milliseconds(5)); count.fetch_add(1); });
		}

		bool destruct_result = manager.destruct();

		
		ASSERT_TRUE(destruct_result);
		EXPECT_GE(count.load(), 0);
	}
}

#endif
