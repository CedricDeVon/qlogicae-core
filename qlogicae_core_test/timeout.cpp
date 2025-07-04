#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{
    class TimeoutTest : public ::testing::Test {};

    TEST_F(TimeoutTest, Should_Execute_Callback_When_Delay_Expires)
    {
        std::atomic<bool> called = false;
        QLogicaeCore::Timeout timeout([&] { called = true; }, std::chrono::milliseconds(200));
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        EXPECT_TRUE(called.load());
    }

    TEST_F(TimeoutTest, Should_Cancel_Timeout_When_Requested)
    {
        std::atomic<bool> called = false;
        QLogicaeCore::Timeout timeout([&] { called = true; }, std::chrono::milliseconds(200));
        timeout.cancel();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        EXPECT_FALSE(called.load());
        EXPECT_TRUE(timeout.is_cancelled());
    }

    TEST_F(TimeoutTest, Should_Restart_Timeout_When_Invoked)
    {
        std::atomic<int> calls = 0;
        QLogicaeCore::Timeout timeout([&] { calls++; }, std::chrono::milliseconds(100));
        timeout.restart();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        EXPECT_EQ(calls.load(), 1);
    }

    TEST_F(TimeoutTest, Should_Throw_In_Callback_When_Exception_Occurs)
    {
        EXPECT_NO_THROW({
            QLogicaeCore::Timeout timeout([] { throw std::runtime_error("failure"); }, std::chrono::milliseconds(100));
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            });
    }

    TEST_F(TimeoutTest, Should_Handle_Performance_When_Delay_Is_2s)
    {
        std::atomic<bool> fired = false;
        QLogicaeCore::Timeout timeout([&] { fired = true; }, std::chrono::seconds(2));
        std::this_thread::sleep_for(std::chrono::milliseconds(2100));
        EXPECT_TRUE(fired.load());
    }

    TEST_F(TimeoutTest, Should_Trigger_Immediately_When_Duration_Is_Zero)
    {
        std::atomic<bool> fired = false;
        QLogicaeCore::Timeout timeout([&] { fired = true; }, std::chrono::milliseconds(0));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        EXPECT_TRUE(fired.load());
    }

    TEST_F(TimeoutTest, Should_Only_Trigger_Once)
    {
        std::atomic<int> fired = 0;
        QLogicaeCore::Timeout timeout([&] { fired++; }, std::chrono::milliseconds(50));
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        EXPECT_EQ(fired.load(), 1);
    }

    TEST_F(TimeoutTest, Should_Be_Thread_Safe_When_Cancelled_Concurrently)
    {
        std::atomic<bool> fired = false;
        QLogicaeCore::Timeout timeout([&] { fired = true; }, std::chrono::milliseconds(100));
        std::jthread t1([&] { timeout.cancel(); });
        std::jthread t2([&] { timeout.cancel(); });
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        EXPECT_FALSE(fired.load());
    }
}
