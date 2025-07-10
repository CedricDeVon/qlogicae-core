#pragma once

#include "pch.h"

#include "interval.hpp"

namespace QLogicaeCoreTest
{
    class IntervalTest : public ::testing::TestWithParam<int> {};

    TEST_F(IntervalTest, Should_ExecuteRepeatedly_When_Active)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCore::Interval interval(
            [&](size_t)
            {
                execution_count++;
                return execution_count < 3;
            },
            std::chrono::milliseconds(100)
        );

        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        EXPECT_GE(execution_count.load(), 3);
    }

    TEST_F(IntervalTest, Should_PauseAndResume_When_Requested)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCore::Interval interval(
            [&](size_t)
            {
                execution_count++;
                return true;
            },
            std::chrono::milliseconds(50)
        );

        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(120));

        interval.pause();
        int count_when_paused = execution_count.load();

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        EXPECT_EQ(execution_count.load(), count_when_paused);

        interval.resume();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        EXPECT_GT(execution_count.load(), count_when_paused);
    }

    TEST_F(IntervalTest, Should_Stop_When_MaxCountIsReached)
    {
        QLogicaeCore::Interval interval(
            [](size_t)
            {
                return true;
            },
            std::chrono::milliseconds(50),
            3
        );

        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        EXPECT_EQ(interval.get_execution_count(), 3);
    }

    TEST_F(IntervalTest, Should_CancelExecution_When_Requested)
    {
        QLogicaeCore::Interval interval(
            [](size_t)
            {
                return true;
            },
            std::chrono::milliseconds(50)
        );

        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        interval.cancel();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        EXPECT_TRUE(interval.is_cancelled());
    }

    TEST_F(IntervalTest, Should_TriggerExecution_When_IntervalIsTwoSeconds)
    {
        std::atomic<bool> did_run = false;

        QLogicaeCore::Interval interval(
            [&](size_t)
            {
                did_run = true;
                return false;
            },
            std::chrono::seconds(2)
        );

        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(2100));

        EXPECT_TRUE(did_run.load());
    }

    TEST_P(IntervalTest, Should_RunMultipleInstances_When_InParallel)
    {
        int thread_count = GetParam();
        std::vector<std::jthread> runners;
        std::atomic<int> total_executions = 0;

        for (int i = 0; i < thread_count; ++i)
        {
            runners.emplace_back([&]
                {
                    QLogicaeCore::Interval interval(
                        [&](size_t)
                        {
                            total_executions++;
                            return total_executions < thread_count * 10;
                        },
                        std::chrono::milliseconds(10)
                    );

                    interval.start();
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                });
        }

        for (auto& runner : runners)
        {
            runner.join();
        }

        EXPECT_GE(total_executions.load(), thread_count);
    }

    TEST_F(IntervalTest, Should_ExecuteOnce_When_CallbackReturnsFalseImmediately)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCore::Interval interval(
            [&](size_t)
            {
                execution_count++;
                return false;
            },
            std::chrono::milliseconds(50)
        );

        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        EXPECT_EQ(execution_count.load(), 1);
    }

    TEST_F(IntervalTest, Should_ApplyNewCallback_When_ChangedDuringExecution)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCore::Interval interval(
            [&](size_t)
            {
                execution_count++;
                return true;
            },
            std::chrono::milliseconds(50)
        );

        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        interval.set_callback(
            [&](size_t)
            {
                execution_count += 2;
                return execution_count < 10;
            }
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        EXPECT_GE(execution_count.load(), 10);
    }

    TEST_F(IntervalTest, Should_AccelerateExecution_When_IntervalIsShortened)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCore::Interval interval(
            [&](size_t)
            {
                execution_count++;
                return execution_count < 10;
            },
            std::chrono::milliseconds(100)
        );

        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        int count_after_first_phase = execution_count.load();

        interval.set_interval(std::chrono::milliseconds(10));
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        int final_count = execution_count.load();

        EXPECT_LT(count_after_first_phase, final_count);
        EXPECT_GE(final_count, 10);
    }

    TEST_P(IntervalTest, Should_RunWithIsolatedCounters_When_Multithreaded)
    {
        int thread_count = GetParam();
        std::vector<std::jthread> threads;
        std::vector<std::shared_ptr<std::atomic<int>>> counters(thread_count);

        for (int i = 0; i < thread_count; ++i)
        {
            counters[i] = std::make_shared<std::atomic<int>>(0);

            threads.emplace_back([counter = counters[i]]
                {
                    QLogicaeCore::Interval interval(
                        [counter](size_t)
                        {
                            (*counter)++;
                            return *counter < 10;
                        },
                        std::chrono::milliseconds(10)
                    );

                    interval.start();
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        for (const auto& counter : counters)
        {
            EXPECT_GE(counter->load(), 5);
            EXPECT_LE(counter->load(), 10);
        }
    }

    TEST_F(IntervalTest, Should_ReflectCorrectFlags_When_LifecycleChanges)
    {
        QLogicaeCore::Interval interval(
            [](size_t)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                return true;
            },
            std::chrono::milliseconds(10)
        );

        EXPECT_FALSE(interval.is_running());
        EXPECT_FALSE(interval.is_paused());
        EXPECT_FALSE(interval.is_cancelled());

        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        EXPECT_TRUE(interval.is_running());
        EXPECT_FALSE(interval.is_paused());
        EXPECT_FALSE(interval.is_cancelled());

        interval.pause();
        EXPECT_TRUE(interval.is_paused());

        interval.resume();
        EXPECT_FALSE(interval.is_paused());

        interval.cancel();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        EXPECT_TRUE(interval.is_cancelled());
    }

    TEST_F(IntervalTest, Should_ResetExecutionCount_When_Restarted)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCore::Interval interval(
            [&](size_t)
            {
                execution_count++;
                return execution_count < 3;
            },
            std::chrono::milliseconds(50)
        );

        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        size_t first_phase = interval.get_execution_count();
        EXPECT_EQ(first_phase, 3);

        execution_count.store(0);
        interval.restart();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        size_t second_phase = interval.get_execution_count();
        EXPECT_EQ(second_phase, 3);
    }

    INSTANTIATE_TEST_CASE_P(
        MultithreadedTests,
        IntervalTest,
        ::testing::Values(2, 4, 8)
    );

}
