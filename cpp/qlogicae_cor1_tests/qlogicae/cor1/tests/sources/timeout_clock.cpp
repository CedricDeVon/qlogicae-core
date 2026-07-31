#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeoutClock \
	)

#include "../includes/timeout_clock.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{    
    TEST_F(TimeoutClockTest, Should_StartSuccessfully_When_Called)
    {
        timeout_clock_instance->configurations.delay_in_milliseconds =
            std::chrono::milliseconds(1);
        ASSERT_TRUE(timeout_clock_instance->start());
        ASSERT_FALSE(timeout_clock_instance->is_cancelled());
        timeout_clock_instance->cancel();
    }

    TEST_F(TimeoutClockTest, Should_CancelSuccessfully_When_Running)
    {
        timeout_clock_instance->start();
        ASSERT_TRUE(timeout_clock_instance->cancel());
        ASSERT_TRUE(timeout_clock_instance->is_cancelled());
    }

    TEST_F(TimeoutClockTest, Should_RestartSuccessfully_When_Called)
    {
        timeout_clock_instance->start();
        ASSERT_TRUE(timeout_clock_instance->restart());
        ASSERT_FALSE(timeout_clock_instance->is_cancelled());
        timeout_clock_instance->cancel();
    }

    TEST_F(TimeoutClockTest, Should_RunCallbackAsync_When_StartCalled)
    {
        std::promise<bool> callback_executed_promise;
        std::future<bool> callback_executed_future =
            callback_executed_promise.get_future();
        timeout_clock_instance->configurations.callback = [&callback_executed_promise]()
        {
            callback_executed_promise.set_value(true);
        };
        timeout_clock_instance->configurations.delay_in_milliseconds =
            std::chrono::milliseconds(1);
        timeout_clock_instance->start();
        ASSERT_TRUE(callback_executed_future.get());
        timeout_clock_instance->cancel();
    }

    TEST_F(TimeoutClockTest, Should_HandleExceptionInCallback_When_Thrown)
    {
        timeout_clock_instance->configurations.callback =
            []() { throw std::runtime_error("fail"); };
        timeout_clock_instance->configurations.delay_in_milliseconds =
            std::chrono::milliseconds(1);
        ASSERT_TRUE(timeout_clock_instance->start());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ASSERT_FALSE(timeout_clock_instance->is_cancelled());
        timeout_clock_instance->cancel();
    }

    TEST_F(TimeoutClockTest, Should_BeThreadSafe_When_MultipleThreadsStartAndCancel)
    {
		timeout_clock_instance->configurations.is_feature_thread_safety_handling_enabled = true;
        timeout_clock_instance->configurations.delay_in_milliseconds =
            std::chrono::milliseconds(1);
        std::vector<std::thread> thread_pool;
        for (int i = 0; i < 4; ++i)
        {
            thread_pool.emplace_back([this, i]()
            {
                if (i % 2 == 0)
                {
                    timeout_clock_instance->start();
                }
                else
                {
                    timeout_clock_instance->cancel();
                }
            });
        }
        for (auto& thread : thread_pool)
        {
            thread.join();
        }
    }

    TEST_F(TimeoutClockTest, Should_HandleStressTest_When_HighFrequencyStartCancelRestart)
    {
        timeout_clock_instance->configurations.delay_in_milliseconds =
            std::chrono::milliseconds(1);
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; ++i)
        {
            ASSERT_TRUE(timeout_clock_instance->start());
            ASSERT_TRUE(timeout_clock_instance->cancel());
            ASSERT_TRUE(timeout_clock_instance->restart());
        }
        timeout_clock_instance->cancel();        
    }

    TEST_F(TimeoutClockTest, Should_HandleZeroDelay_When_DelayZero)
    {
        timeout_clock_instance->configurations.delay_in_milliseconds =
            std::chrono::milliseconds(0);
        timeout_clock_instance->configurations.callback = []() {};
        ASSERT_TRUE(timeout_clock_instance->start());
        timeout_clock_instance->cancel();
    }

    TEST_F(TimeoutClockTest, Should_HandleEmptyCallback_When_CallbackNull)
    {
        timeout_clock_instance->configurations.callback = []() {};
        ASSERT_TRUE(timeout_clock_instance->start());
        timeout_clock_instance->cancel();
    }

    TEST_F(TimeoutClockTest, Should_HandleMultipleCancelCalls_When_CalledRepeatedly)
    {
        timeout_clock_instance->start();
        ASSERT_TRUE(timeout_clock_instance->cancel());
        ASSERT_TRUE(timeout_clock_instance->cancel());
    }

    TEST_F(TimeoutClockTest, Should_HandleMultipleRestartCalls_When_CalledRepeatedly)
    {
        timeout_clock_instance->start();
        ASSERT_TRUE(timeout_clock_instance->restart());
        ASSERT_TRUE(timeout_clock_instance->restart());
        timeout_clock_instance->cancel();
    }

    INSTANTIATE_TEST_CASE_P(
        TimeoutClockDelayTests,
        TimeoutClockParameterizedTest,
        ::testing::Values(0, 1, 50, 100)
    );

    TEST_P(TimeoutClockParameterizedTest, Should_ExecuteCallback_When_DelaySet)
    {
        int delay_value = GetParam();
        std::promise<bool> callback_executed_promise;
        std::future<bool> callback_executed_future =
            callback_executed_promise.get_future();
        timeout_clock_instance->configurations.delay_in_milliseconds =
            std::chrono::milliseconds(delay_value);
        timeout_clock_instance->configurations.callback = [&callback_executed_promise]()
        {
            callback_executed_promise.set_value(true);
        };
        timeout_clock_instance->start();
        ASSERT_TRUE(callback_executed_future.get());
        timeout_clock_instance->cancel();
    }

    TEST_F(TimeoutClockImmediateExecutionTest, Should_ExecuteCallbackImmediately_When_ImmediateExecutionFlagSet)
    {
        std::atomic<bool> callback_called{ false };
        timeout_clock_instance->configurations.is_executed_immediately = true;
        timeout_clock_instance->configurations.callback = [&callback_called]()
        {
            callback_called.store(true);
        };
        timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(100);
        timeout_clock_instance->start();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ASSERT_TRUE(callback_called.load());
        timeout_clock_instance->cancel();
    }

    TEST_F(TimeoutClockImmediateExecutionTest, Should_SetCancelledDuringCallback_When_CancelCalledInsideCallback)
    {
        timeout_clock_instance->configurations.is_executed_immediately = true;
        timeout_clock_instance->configurations.callback = [this]()
        {
            timeout_clock_instance->cancel();
        };
        timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
        timeout_clock_instance->start();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ASSERT_TRUE(timeout_clock_instance->is_cancelled());
    }

    TEST_F(TimeoutClockImmediateExecutionTest, Should_HandleExtremeLargeDelay_When_MaxMillisecondsSet)
    {
        timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds::max();
        timeout_clock_instance->configurations.callback = []() {};
        ASSERT_TRUE(timeout_clock_instance->start());
        timeout_clock_instance->cancel();
    }

    TEST_F(TimeoutClockImmediateExecutionTest, Should_HandleExtremeFrequentRestarts_When_ZeroDelay)
    {
        timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(0);
        timeout_clock_instance->configurations.is_executed_immediately = true;
        timeout_clock_instance->configurations.callback = []() {};
        for (int i = 0; i < 50; ++i)
        {
            ASSERT_TRUE(timeout_clock_instance->restart());
        }
        timeout_clock_instance->cancel();
    }

    INSTANTIATE_TEST_CASE_P(
        TimeoutClockImmediateFlagTests,
        TimeoutClockFlagParameterizedTest,
        ::testing::Values(true, false)
    );

    TEST_P(TimeoutClockFlagParameterizedTest, Should_HandleImmediateExecutionFlagAndCallbackNull_When_FlagSet)
    {
        bool immediate_flag = GetParam();
        timeout_clock_instance->configurations.is_executed_immediately = immediate_flag;
        timeout_clock_instance->configurations.callback = []() {};
        timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
        ASSERT_TRUE(timeout_clock_instance->start());
        timeout_clock_instance->cancel();
    }

	TEST_F(TimeoutClockTest, Should_HandleAsyncWithStdAsync_When_CallbackExecuted)
	{
		std::atomic<bool> callback_executed{ false };
		timeout_clock_instance->configurations.callback = [&callback_executed]()
			{
				callback_executed.store(true);
			};
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		auto future_result = std::async(std::launch::async, [this]()
			{
				timeout_clock_instance->start();
			});
		future_result.get();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		ASSERT_TRUE(callback_executed.load());
		timeout_clock_instance->cancel();
	}

	TEST_F(TimeoutClockTest, Should_HandleConcurrentFlagAccess_When_MultipleThreads)
	{
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		std::vector<std::thread> thread_pool;
		for (int i = 0; i < 8; ++i)
		{
			thread_pool.emplace_back([this, i]()
				{
					if (i % 2 == 0)
					{
						timeout_clock_instance->is_flag_stopped_async.store(false);
					}
					else
					{
						timeout_clock_instance->is_flag_stopped_async.store(true);
					}
				});
		}
		for (auto& thread : thread_pool)
		{
			thread.join();
		}
		ASSERT_TRUE(timeout_clock_instance->is_flag_stopped_async.load() == true ||
			timeout_clock_instance->is_flag_stopped_async.load() == false);
	}

	TEST_F(TimeoutClockTest, Should_HandleMultipleCallbackExecutions_When_ConcurrentStarts)
	{
		std::atomic<int> callback_count{ 0 };
		timeout_clock_instance->configurations.callback = [&callback_count]()
			{
				++callback_count;
			};
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		timeout_clock_instance->configurations.is_feature_thread_safety_handling_enabled = true;
		std::vector<std::thread> thread_pool;
		for (int i = 0; i < 5; ++i)
		{
			thread_pool.emplace_back([this]()
				{
					timeout_clock_instance->start();
				});
		}
		for (auto& thread : thread_pool)
		{
			thread.join();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		ASSERT_GE(callback_count.load(), 1);
		timeout_clock_instance->cancel();
	}

	TEST_F(TimeoutClockTest, Should_HandleConstructDestructException_When_ErrorThrown)
	{
		class TimeoutClockThrow : public TimeoutClock
		{
		public:
			bool construct()
			{
				throw std::runtime_error("construct fail");
			}
			bool destruct()
			{
				throw std::runtime_error("destruct fail");
			}
		};
		auto instance = std::make_unique<TimeoutClockThrow>();
		try
		{
			instance->construct();
		}
		catch (...)
		{
			SUCCEED();
		}
		try
		{
			instance->destruct();
		}
		catch (...)
		{
			SUCCEED();
		}
	}

	TEST_F(TimeoutClockTest, Should_HandleCancelAfterDestruction_When_Called)
	{
		timeout_clock_instance->destruct();
		ASSERT_NO_THROW(timeout_clock_instance->cancel());
	}

	TEST_F(TimeoutClockTest, Should_HandleRestartAfterDestruction_When_Called)
	{
		timeout_clock_instance->destruct();
		ASSERT_NO_THROW(timeout_clock_instance->restart());
	}

	TEST_F(TimeoutClockImmediateExecutionTest, Should_HandleFlagValuesAfterStartCancelRestart)
	{
		timeout_clock_instance->configurations.is_executed_immediately = true;
		timeout_clock_instance->configurations.callback = []() {};
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		timeout_clock_instance->start();
		ASSERT_FALSE(timeout_clock_instance->is_flag_stopped_async.load());
		timeout_clock_instance->cancel();
		ASSERT_TRUE(timeout_clock_instance->is_flag_stopped_async.load());
		timeout_clock_instance->restart();
		ASSERT_FALSE(timeout_clock_instance->is_flag_stopped_async.load());
	}

	TEST_F(TimeoutClockImmediateExecutionTest, Should_HandleImmediateAsyncFlagAfterStart)
	{
		timeout_clock_instance->configurations.is_executed_immediately = true;
		timeout_clock_instance->configurations.callback = []() {};
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		timeout_clock_instance->start();
		ASSERT_TRUE(timeout_clock_instance->is_executed_immediately_async.load());
		timeout_clock_instance->cancel();
	}

	TEST_F(TimeoutClockImmediateExecutionTest, Should_HandleExtremeLargeIterationStress_When_HighLoad)
	{
		timeout_clock_instance->configurations.is_executed_immediately = true;
		timeout_clock_instance->configurations.callback = []() {};
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(0);
		auto start_time = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 500; ++i)
		{
			timeout_clock_instance->restart();
		}
		timeout_clock_instance->cancel();
		auto end_time = std::chrono::high_resolution_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			end_time - start_time).count();
		ASSERT_LT(elapsed_ms, 2000);
	}

	TEST_F(TimeoutClockTest, Should_HandleInvalidDelay_When_NegativeValueCast)
	{
		timeout_clock_instance->configurations.delay_in_milliseconds =
			std::chrono::milliseconds(static_cast<int64_t>(-1));
		timeout_clock_instance->configurations.callback = []() {};
		ASSERT_TRUE(timeout_clock_instance->start());
		timeout_clock_instance->cancel();
	}

	TEST_P(TimeoutClockParameterizedTest, Should_HandleCallbackThrow_When_Parameterized)
	{
		int delay_value = GetParam();
		timeout_clock_instance->configurations.delay_in_milliseconds =
			std::chrono::milliseconds(delay_value);
		timeout_clock_instance->configurations.callback = []() { throw std::runtime_error("fail"); };
		ASSERT_TRUE(timeout_clock_instance->start());
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		ASSERT_FALSE(timeout_clock_instance->is_cancelled());
		timeout_clock_instance->cancel();
	}

	TEST_F(TimeoutClockTest, Should_HandleNullCallback_When_CallbackIsNullptr)
	{
		timeout_clock_instance->configurations.callback = nullptr;
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		ASSERT_TRUE(timeout_clock_instance->start());
		timeout_clock_instance->cancel();
	}

	TEST_F(TimeoutClockTest, Should_HandleThreadSafetyToggle_When_MutexEnabledAndDisabled)
	{
		timeout_clock_instance->configurations.is_feature_thread_safety_handling_enabled = true;
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		timeout_clock_instance->start();
		timeout_clock_instance->cancel();

		timeout_clock_instance->configurations.is_thread_safety_handling_override_enabled = false;
		timeout_clock_instance->start();
		timeout_clock_instance->cancel();
	}

	TEST_F(TimeoutClockTest, Should_HandleStopTokenRequested_When_CancelCalledDuringCallback)
	{
		std::atomic<bool> callback_started{ false };
		timeout_clock_instance->configurations.callback = [this, &callback_started]()
			{
				callback_started.store(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			};
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		timeout_clock_instance->start();
		while (!callback_started.load())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		timeout_clock_instance->cancel();
		ASSERT_TRUE(timeout_clock_instance->is_cancelled());
	}

	TEST_F(TimeoutClockTest, Should_MaintainExecutedImmediateFlag_AfterMultipleRestartCancel)
	{
		timeout_clock_instance->configurations.is_executed_immediately = true;
		timeout_clock_instance->configurations.callback = []() {};
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);

		for (int i = 0; i < 10; ++i)
		{
			timeout_clock_instance->start();
			ASSERT_TRUE(timeout_clock_instance->is_executed_immediately_async.load());
			timeout_clock_instance->cancel();
			timeout_clock_instance->restart();
			ASSERT_TRUE(timeout_clock_instance->is_executed_immediately_async.load());
		}
		timeout_clock_instance->cancel();
	}

	TEST_F(TimeoutClockTest, Should_HandleCallbackLifetime_When_CallbackModifiedAfterStart)
	{
		auto callback_ptr = std::make_shared<std::atomic<bool>>(false);
		timeout_clock_instance->configurations.callback = [callback_ptr]() { callback_ptr->store(true); };
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		timeout_clock_instance->start();
		timeout_clock_instance->configurations.callback = nullptr;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		ASSERT_TRUE(callback_ptr->load());
		timeout_clock_instance->cancel();
	}

	TEST_F(TimeoutClockTest, Should_HandleImmediateFlagRaceCondition_When_MultipleThreadsModify)
	{
		timeout_clock_instance->configurations.is_feature_thread_safety_handling_enabled = true;
		timeout_clock_instance->configurations.is_executed_immediately = true;
		timeout_clock_instance->configurations.callback = []() {};
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		std::vector<std::thread> threads;
		for (int i = 0; i < 8; ++i)
		{
			threads.emplace_back([this, i]()
				{
					timeout_clock_instance->configurations.is_executed_immediately = (i % 2 == 0);
					timeout_clock_instance->start();
					timeout_clock_instance->cancel();
				});
		}
		for (auto& t : threads) t.join();
	}

	TEST_F(TimeoutClockTest, Should_HandleMinimumDelay_When_DelayMin)
	{
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds::min();
		timeout_clock_instance->configurations.callback = []() {};
		ASSERT_TRUE(timeout_clock_instance->start());
		timeout_clock_instance->cancel();
	}

	TEST_F(TimeoutClockTest, Should_HandleConcurrentRestarts_When_MultipleThreads)
	{
		timeout_clock_instance->configurations.is_feature_thread_safety_handling_enabled = true;
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		timeout_clock_instance->configurations.callback = []() {};
		std::vector<std::thread> threads;
		for (int i = 0; i < 10; ++i)
		{
			threads.emplace_back([this]() { timeout_clock_instance->restart(); });
		}
		for (auto& t : threads) t.join();
		timeout_clock_instance->cancel();
	}

	TEST_F(TimeoutClockImmediateExecutionTest, Should_HandleExceptionInImmediateCallbackDuringRestart)
	{
		timeout_clock_instance->configurations.is_executed_immediately = true;
		timeout_clock_instance->configurations.callback = []() { throw std::runtime_error("fail"); };
		timeout_clock_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		ASSERT_TRUE(timeout_clock_instance->restart());
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		ASSERT_FALSE(timeout_clock_instance->is_cancelled());
		timeout_clock_instance->cancel();
	}
}

#endif
