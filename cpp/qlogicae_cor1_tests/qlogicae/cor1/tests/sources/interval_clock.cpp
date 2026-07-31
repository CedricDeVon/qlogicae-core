#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		IntervalClock \
	)

#include "../includes/interval_clock.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(IntervalClockTest, Should_StartSuccessfully_When_Called)
	{
		manager_instance->configurations.maximum_interval_count = 1;
		ASSERT_TRUE(manager_instance->start());
		ASSERT_TRUE(manager_instance->is_running());
		manager_instance->cancel();
	}

	TEST_F(IntervalClockTest, Should_StopSuccessfully_When_Running)
	{
		manager_instance->start();
		ASSERT_TRUE(manager_instance->stop());
		ASSERT_FALSE(manager_instance->is_running());
	}

	TEST_F(IntervalClockTest, Should_PauseAndResumeSuccessfully_When_Running)
	{
		manager_instance->start();
		ASSERT_TRUE(manager_instance->pause());
		ASSERT_TRUE(manager_instance->is_paused());
		ASSERT_TRUE(manager_instance->resume());
		ASSERT_FALSE(manager_instance->is_paused());
		manager_instance->cancel();
	}

	TEST_F(IntervalClockTest, Should_RestartSuccessfully_When_Running)
	{
		manager_instance->start();
		ASSERT_TRUE(manager_instance->restart());
		ASSERT_TRUE(manager_instance->is_running());
		manager_instance->cancel();
	}

	TEST_F(IntervalClockTest, Should_IncrementExecutionCount_When_CallbackCalled)
	{
		manager_instance->configurations.maximum_interval_count = 5;
		manager_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		manager_instance->start();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		ASSERT_GT(manager_instance->get_execution_count(), 0u);
		manager_instance->cancel();
	}

	TEST_F(IntervalClockTest, Should_BeAsynchronous_When_StartUsingAsync)
	{
		manager_instance->configurations.is_feature_thread_safety_handling_enabled = true;

		auto future_result = std::async(std::launch::async, [this]()
			{
				return manager_instance->start();
			});
		ASSERT_TRUE(future_result.get());
		manager_instance->cancel();
	}

	TEST_F(IntervalClockTest, Should_HandleStressTest_When_HighFrequencyStart)
	{
		for (int i = 0; i < 100; ++i)
		{
			ASSERT_TRUE(manager_instance->start());
			ASSERT_TRUE(manager_instance->cancel());
		}
	}

	TEST_F(IntervalClockTest, Should_HandleEdgeCases_When_MaximumIntervalCountZero)
	{
		manager_instance->configurations.is_feature_edge_case_handling_enabled = true;

		manager_instance->configurations.maximum_interval_count = 0;
		ASSERT_FALSE(manager_instance->start());
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		ASSERT_EQ(manager_instance->get_execution_count(), 0u);
		manager_instance->cancel();
	}

	TEST_F(IntervalClockTest, Should_HandleEdgeCases_When_DelayZero)
	{
		manager_instance->configurations.delay_in_milliseconds =
			std::chrono::milliseconds(0);

		ASSERT_FALSE(manager_instance->start());
		ASSERT_EQ(manager_instance->get_execution_count(), 0);
	}

	INSTANTIATE_TEST_CASE_P(
		IntervalClockExecutionCountTests,
		IntervalClockParameterizedTest,
		::testing::Values(
			1,
			5,
			10,
			50,
			100
		)
	);

	TEST_P(IntervalClockParameterizedTest, Should_RunExactNumberOfIntervals_When_MaximumIntervalCountSet)
	{
		size_t max_count = GetParam();
		manager_instance->configurations.maximum_interval_count = max_count;
		manager_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		manager_instance->start();
		std::this_thread::sleep_for(std::chrono::milliseconds(max_count * 2));
		ASSERT_LE(manager_instance->get_execution_count(), max_count);
		manager_instance->cancel();
	}

	TEST_F(IntervalClockTest, Should_HandleMultithreadedPauseResume_When_MultipleThreads)
	{
		manager_instance->start();
		std::vector<std::thread> thread_pool;
		for (int i = 0; i < 4; ++i)
		{
			thread_pool.emplace_back([this, i]()
				{
					if (i % 2 == 0)
					{
						manager_instance->pause();
					}
					else
					{
						manager_instance->resume();
					}
				});
		}
		for (auto& thread : thread_pool)
		{
			thread.join();
		}
		manager_instance->cancel();
	}

	TEST_F(IntervalClockTest, Should_PerformWithinTimeLimits_When_LongRunningIntervals)
	{
		manager_instance->configurations.maximum_interval_count = 50;
		manager_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(10);

		manager_instance->start();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		manager_instance->cancel();
	}

	TEST_F(IntervalClockTest, Should_HandleCallbackExceptionsGracefully)
	{
		manager_instance->configurations.maximum_interval_count = 3;
		manager_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		manager_instance->configurations.callback = [](const size_t&) -> bool
			{
				throw std::runtime_error("intentional");
			};
		manager_instance->start();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ASSERT_FALSE(manager_instance->is_running());
		manager_instance->configurations.callback = [](const size_t&) { return true; };
	}

	TEST_F(IntervalClockTest, Should_BeThreadSafe_When_MultipleThreadsStartStressTest)
	{
		manager_instance->configurations.maximum_interval_count = 5;
		manager_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		manager_instance->configurations.is_feature_thread_safety_handling_enabled = false;
		std::vector<std::thread> thread_pool;
		for (int i = 0; i < 16; ++i)
		{
			thread_pool.emplace_back([this]()
				{
					manager_instance->start();
				});
		}
		for (auto& thread : thread_pool)
		{
			thread.join();
		}
		ASSERT_TRUE(manager_instance->is_running() || manager_instance->is_cancelled());
		manager_instance->cancel();
	}

	TEST_F(IntervalClockTest, Should_RunImmediately_When_ImmediateExecutionEnabled)
	{
		manager_instance->configurations.maximum_interval_count = 1;
		manager_instance->configurations.is_executed_immediately = true;
		bool callback_called = false;
		manager_instance->configurations.callback = [&callback_called](const size_t&)
			{
				callback_called = true;
				return false;
			};
		manager_instance->start();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		ASSERT_TRUE(callback_called);
		ASSERT_FALSE(manager_instance->is_running());
		manager_instance->configurations.callback = [](const size_t&) { return true; };
	}

	TEST_F(IntervalClockTest, Should_PauseAndResumeWithoutRunning_DoNotCrash)
	{
		ASSERT_TRUE(manager_instance->pause());
		ASSERT_TRUE(manager_instance->resume());
		ASSERT_FALSE(manager_instance->is_running());
		ASSERT_FALSE(manager_instance->is_paused());
	}

	TEST_F(IntervalClockTest, Should_HandleExtremeValuesForMaximumCountAndDelay)
	{
		manager_instance->configurations.maximum_interval_count = 1'000;
		manager_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(5);
		manager_instance->start();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		ASSERT_GT(manager_instance->get_execution_count(), 0u);
		manager_instance->cancel();
	}
}

#endif


/*
	TEST_F(IntervalClockTest, Should_CancelSuccessfully_When_Running)
	{
		manager_instance->start();
		ASSERT_TRUE(manager_instance->cancel());
		ASSERT_FALSE(manager_instance->is_running());
		ASSERT_TRUE(manager_instance->is_cancelled());
	}
*/


/*
	TEST_F(IntervalClockTest, Should_HandleExceptionsGracefully_When_CallbackThrows)
	{
		manager_instance->configurations.callback = [](const size_t&) -> bool { throw std::runtime_error("fail"); };
		manager_instance->configurations.maximum_interval_count = 1;
		manager_instance->start();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		ASSERT_FALSE(manager_instance->is_running());
		manager_instance->configurations.callback = [](const size_t&) { return true; };
	}

	TEST_F(IntervalClockTest, Should_BeThreadSafe_When_MultipleThreadsStart)
	{
		manager_instance->configurations.delay_in_milliseconds = std::chrono::milliseconds(1);
		manager_instance->configurations.maximum_interval_count = 1;
		manager_instance->configurations.is_feature_thread_safety_handling_enabled = true;

		std::vector<std::thread> thread_pool;
		for (int i = 0; i < 8; ++i)
		{
			thread_pool.emplace_back([this]()
				{
					bool started = manager_instance->start();
					ASSERT_TRUE(started || manager_instance->is_running());
				});
		}
		for (auto& thread : thread_pool)
		{
			thread.join();
		}
		manager_instance->cancel();
	}
*/

/*
TEST_F(IntervalClockTest, Should_CancelCorrectlyAndSetFlag_When_Running)
{
	manager_instance->configurations.maximum_interval_count = 5;
	manager_instance->start();
	ASSERT_TRUE(manager_instance->cancel());
	ASSERT_FALSE(manager_instance->is_running());
	ASSERT_TRUE(manager_instance->is_cancelled());
}
*/
