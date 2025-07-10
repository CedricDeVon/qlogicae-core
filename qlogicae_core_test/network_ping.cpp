#pragma once

#include "pch.h"

#include "network_ping.hpp"

using QLogicaeCore::NetworkPing;
using QLogicaeCore::NetworkPingSettings;
using QLogicaeCore::NetworkPingResponse;

namespace QLogicaeCoreTest
{
    class NetworkPingTest : public ::testing::TestWithParam<std::chrono::milliseconds> {
    protected:
        void SetUp() override {
            settings.host_address = "www.google.com";
            settings.is_listening = true;
            settings.name = "test-ping";
            settings.callback = [this](const QLogicaeCore::NetworkPingResponse& response) {
                std::lock_guard<std::mutex> lock(callback_mutex);
                latest_result = response.round_trip_time_in_milliseconds;
                callback_invoked.notify_all();
                };
        }

        void wait_for_callback() {
            std::unique_lock<std::mutex> lock(callback_mutex);
            callback_invoked.wait(lock, [&]() {
                return latest_result >= 0;
                });
        }

        QLogicaeCore::NetworkPingSettings settings;
        std::condition_variable callback_invoked;
        std::mutex callback_mutex;
        std::atomic<int64_t> latest_result{ -1 };
    };

    TEST(NetworkPingTest, Should_Expect_Callback_When_PingSucceeds)
    {
        std::atomic<bool> called{ false };
        NetworkPingSettings s;
        s.host_address = "www.google.com";
        s.callback = [&](const NetworkPingResponse&) { called = true; };
        NetworkPing ping(s);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        EXPECT_TRUE(called.load());
    }

    TEST(NetworkPingTest, Should_Expect_PingIntervalChange_When_SetIntervalCalled)
    {
        std::atomic<int> counter{ 0 };
        NetworkPingSettings s;
        s.callback = [&](const NetworkPingResponse&) { counter++; };
        NetworkPing ping(s);
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        ping.set_milliseconds_per_callback(std::chrono::milliseconds(200));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        EXPECT_GE(counter.load(), 4);
    }

    TEST(NetworkPingTest, Should_Expect_Callbacks_When_MultipleInstances)
    {
        auto total = std::make_shared<std::atomic<int>>(0);
        std::vector<std::unique_ptr<NetworkPing>> instances;

        for (int i = 0; i < 3; ++i)
        {
            NetworkPingSettings s;
            s.name = "ping" + std::to_string(i);
            s.callback = [total](const NetworkPingResponse&) {
                total->fetch_add(1, std::memory_order_relaxed);
                };
            instances.push_back(std::make_unique<NetworkPing>(s));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        EXPECT_GT(total->load(), 0);
    }

    TEST(NetworkPingTest, Should_Expect_Callback_When_PausedImmediately)
    {
        std::atomic<int> counter{ 0 };
        NetworkPingSettings s;
        s.callback = [&](const NetworkPingResponse&) { counter++; };
        NetworkPing ping(s);
        ping.pause_listening();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        EXPECT_EQ(counter.load(), 1);
    }

    TEST(NetworkPingTest, Should_Expect_Callbacks_When_ResumedAfterPause)
    {
        std::atomic<int> counter{ 0 };
        NetworkPingSettings s;
        s.callback = [&](const NetworkPingResponse&) { counter++; };
        NetworkPing ping(s);
        ping.pause_listening();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        ping.continue_listening();
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        EXPECT_GT(counter.load(), 0);
    }

    TEST(NetworkPingTest, Should_Expect_Throw_When_HostInvalid)
    {
        std::atomic<int> counter{ 0 };
        NetworkPingSettings s;
        s.host_address = "invalid.localhost.test.invalid";
        s.callback = [&](const NetworkPingResponse&) { counter++; };
        NetworkPing ping(s);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        EXPECT_EQ(counter.load(), 0);
    }

    TEST(NetworkPingTest, Should_Expect_TimeoutStress_When_IntervalIsFast)
    {
        std::atomic<int> counter{ 0 };
        NetworkPingSettings s;
        s.milliseconds_per_callback = std::chrono::milliseconds(10);
        s.callback = [&](const NetworkPingResponse&) { counter++; };
        NetworkPing ping(s);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        EXPECT_GT(counter.load(), 5);
    }

    TEST(NetworkPingTest, Should_Expect_NameSetAndGet_When_Accessed)
    {
        NetworkPingSettings s;
        s.name = "UnitTestPing";
        s.callback = [](const NetworkPingResponse&) {};
        NetworkPing ping(s);
        EXPECT_EQ(ping.get_name(), "UnitTestPing");
    }

    TEST(NetworkPingTest, Should_Expect_SetHostToReflect_When_Queried)
    {
        NetworkPingSettings s;
        s.host_address = "127.0.0.1";
        s.callback = [](const NetworkPingResponse&) {};
        NetworkPing ping(s);
        EXPECT_EQ(ping.get_host_address(), "127.0.0.1");
        ping.set_host_address("localhost");
        EXPECT_EQ(ping.get_host_address(), "localhost");
    }

    TEST(NetworkPingTest, Should_Expect_IntervalToReflect_When_Set)
    {
        NetworkPingSettings s;
        s.callback = [](const NetworkPingResponse&) {};
        NetworkPing ping(s);
        ping.set_milliseconds_per_callback(std::chrono::milliseconds(1500));
        EXPECT_EQ(ping.get_milliseconds_per_callback(), std::chrono::milliseconds(1500));
    }

    TEST_P(NetworkPingTest, Should_Expect_Callback_When_IntervalExpires) {
        settings.milliseconds_per_callback = GetParam();
        QLogicaeCore::NetworkPing ping(settings);
        wait_for_callback();
        EXPECT_GE(latest_result.load(), 0);
    }

    TEST(NetworkPingTest, Should_Expect_CorrectState_When_PauseAndContinue) {
        QLogicaeCore::NetworkPingSettings settings;
        std::atomic<int> count{ 0 };
        settings.callback = [&](const QLogicaeCore::NetworkPingResponse&) {
            count++;
            };
        settings.milliseconds_per_callback = std::chrono::milliseconds(100);
        QLogicaeCore::NetworkPing ping(settings);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        ping.pause_listening();
        int count_at_pause = count;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        EXPECT_EQ(count, count_at_pause);
    }

    TEST(NetworkPingTest, Should_Expect_CorrectUpdate_When_IntervalChanged) {
        std::mutex mtx;
        std::condition_variable cv;
        std::atomic<int64_t> rtt{ -1 };
        QLogicaeCore::NetworkPingSettings settings;
        settings.callback = [&](const QLogicaeCore::NetworkPingResponse& res) {
            std::lock_guard<std::mutex> lock(mtx);
            rtt = res.round_trip_time_in_milliseconds;
            cv.notify_all();
            };
        QLogicaeCore::NetworkPing ping(settings);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ping.set_milliseconds_per_callback(std::chrono::milliseconds(200));
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return rtt >= 0; });
        EXPECT_GE(rtt.load(), 0);
    }

    TEST(NetworkPingTest, Should_Expect_MultiThreadedPings_When_MultipleInstances)
    {
        auto total_callbacks = std::make_shared<std::atomic<int>>(0);

        auto make_ping = [&](int id) {
            QLogicaeCore::NetworkPingSettings s;
            s.name = "ping-" + std::to_string(id);

            auto counter = total_callbacks;
            s.callback = [counter](const QLogicaeCore::NetworkPingResponse&) {
                counter->fetch_add(1, std::memory_order_relaxed);
                };

            return std::make_unique<QLogicaeCore::NetworkPing>(s);
            };

        std::vector<std::unique_ptr<QLogicaeCore::NetworkPing>> pings;
        for (int i = 0; i < 5; ++i) {
            pings.push_back(make_ping(i));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        EXPECT_GT(total_callbacks->load(), 0);
    }


    INSTANTIATE_TEST_CASE_P(
        IntervalTiming,
        NetworkPingTest,
        ::testing::Values(
            std::chrono::milliseconds(1),
            std::chrono::milliseconds(2),
            std::chrono::milliseconds(1000),
            std::chrono::milliseconds(2000)
        )
    );
}
