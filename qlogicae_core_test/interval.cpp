#pragma once

#include "pch.h"

#include "interval.hpp"

namespace QLogicaeCoreTest
{
    class IntervalTest : public ::testing::TestWithParam<int> {};

    TEST_F(IntervalTest, Should_Execute_Repeatedly_When_Active)
    {
        std::atomic<int> ticks = 0;
        QLogicaeCore::Interval interval([&](size_t) {
            ticks++;
            return ticks < 3;
            }, std::chrono::milliseconds(100));
        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        EXPECT_GE(ticks.load(), 3);
    }

    TEST_F(IntervalTest, Should_Pause_And_Resume)
    {
        std::atomic<int> ticks = 0;
        QLogicaeCore::Interval interval([&](size_t) {
            ticks++;
            return true;
            }, std::chrono::milliseconds(50));
        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
        interval.pause();
        auto paused_ticks = ticks.load();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        EXPECT_EQ(ticks.load(), paused_ticks);
        interval.resume();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_GT(ticks.load(), paused_ticks);
    }

    TEST_F(IntervalTest, Should_Stop_When_Max_Executions_Reached)
    {
        QLogicaeCore::Interval interval([](size_t) {
            return true;
            }, std::chrono::milliseconds(50), 3);
        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        EXPECT_EQ(interval.get_execution_count(), 3);
    }

    TEST_F(IntervalTest, Should_Cancel_Correctly)
    {
        QLogicaeCore::Interval interval([](size_t) {
            return true;
            }, std::chrono::milliseconds(50));
        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        interval.cancel();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_TRUE(interval.is_cancelled());
    }

    TEST_F(IntervalTest, Should_Handle_2s_Interval)
    {
        std::atomic<bool> ran = false;
        QLogicaeCore::Interval interval([&](size_t) {
            ran = true;
            return false;
            }, std::chrono::seconds(2));
        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(2100));
        EXPECT_TRUE(ran.load());
    }

    TEST_P(IntervalTest, Should_Run_Multiple_Instances_In_Parallel)
    {
        const int threads = GetParam();
        std::vector<std::jthread> runners;
        std::atomic<int> total_ticks = 0;

        for (int i = 0; i < threads; ++i)
        {
            runners.emplace_back([&] {
                QLogicaeCore::Interval interval([&](size_t) {
                    total_ticks++;
                    return total_ticks < 10 * threads;
                    }, std::chrono::milliseconds(10));
                interval.start();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                });
        }

        for (auto& t : runners) t.join();
        EXPECT_GE(total_ticks.load(), threads);
    }

    TEST_F(IntervalTest, Should_Handle_Callback_Returning_False_Immediately)
    {
        std::atomic<int> calls = 0;
        QLogicaeCore::Interval interval([&](size_t) {
            calls++;
            return false;
            }, std::chrono::milliseconds(50));
        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        EXPECT_EQ(calls.load(), 1);
    }

    TEST_F(IntervalTest, Should_Allow_Callback_Change_During_Execution)
    {
        std::atomic<int> counter = 0;
        QLogicaeCore::Interval interval([&](size_t) {
            counter++;
            return true;
            }, std::chrono::milliseconds(50));
        interval.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        interval.set_callback([&](size_t) {
            counter += 2;
            return counter < 10;
            });
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        EXPECT_GE(counter.load(), 10);
    }

    INSTANTIATE_TEST_CASE_P(MultithreadedTests, IntervalTest, ::testing::Values(2, 4, 8));
}
