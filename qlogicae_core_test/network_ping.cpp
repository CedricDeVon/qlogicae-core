#include "pch.hpp"

#include "qlogicae/core/network_ping.hpp"

using QLogicaeCore::NetworkPing;
using QLogicaeCore::NetworkPingSettings;
using QLogicaeCore::NetworkPingResponse;

namespace QLogicaeCoreTest
{
    class NetworkPingTest : public ::testing::TestWithParam<std::chrono::milliseconds>
    {
    protected:
        void SetUp() override
        {
            networkPingSettings.host_address = "www.google.com";
            networkPingSettings.is_listening = true;
            networkPingSettings.name = "ping-instance";
            networkPingSettings.callback = [this](const QLogicaeCore::NetworkPingResponse& response)
                {
                    std::lock_guard<std::mutex> lock(callbackMutex);
                    latestResponse = response.round_trip_time_in_milliseconds;
                    callbackCondition.notify_all();
                };
        }

        void WaitForCallback()
        {
            std::unique_lock<std::mutex> lock(callbackMutex);
            callbackCondition.wait(lock, [&]() {
                return latestResponse >= 0;
                });
        }

        QLogicaeCore::NetworkPingSettings networkPingSettings;
        std::condition_variable callbackCondition;
        std::mutex callbackMutex;
        std::atomic<int64_t> latestResponse{ -1 };
    };

    TEST(NetworkPingTestBasic, Should_Expect_Callback_When_PingSucceeds)
    {
        std::atomic<bool> callbackCalled{ false };
        QLogicaeCore::NetworkPingSettings settings;
        settings.host_address = "www.google.com";
        settings.callback = [&](const QLogicaeCore::NetworkPingResponse&) {
            callbackCalled = true;
            };

        QLogicaeCore::NetworkPing ping(settings);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        EXPECT_TRUE(callbackCalled.load());
    }

    TEST(NetworkPingTestBasic, Should_Expect_No_Callback_When_InvalidHost)
    {
        std::atomic<bool> callbackCalled{ false };
        QLogicaeCore::NetworkPingSettings settings;
        settings.host_address = "invalid.host.invalid";
        settings.callback = [&](const QLogicaeCore::NetworkPingResponse&) {
            callbackCalled = true;
            };

        QLogicaeCore::NetworkPing ping(settings);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        EXPECT_FALSE(callbackCalled.load());
    }

    TEST(NetworkPingTestBasic, Should_Expect_PingPauseAndResume)
    {
        std::atomic<int> callbackCounter{ 0 };
        QLogicaeCore::NetworkPingSettings settings;
        settings.callback = [&](const QLogicaeCore::NetworkPingResponse&) {
            callbackCounter++;
            };
        settings.milliseconds_per_callback = std::chrono::milliseconds(100);

        QLogicaeCore::NetworkPing ping(settings);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        ping.pause_listening();
        int countAtPause = callbackCounter.load();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        EXPECT_LE(callbackCounter.load(), countAtPause + 1);
        ping.continue_listening();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        EXPECT_LE(callbackCounter.load(), countAtPause + 1);
    }

    TEST(NetworkPingTestBasic, Should_Expect_IntervalChange_When_Updated)
    {
        std::atomic<int> callbackCounter{ 0 };
        QLogicaeCore::NetworkPingSettings settings;
        settings.callback = [&](const QLogicaeCore::NetworkPingResponse&) {
            callbackCounter++;
            };

        QLogicaeCore::NetworkPing ping(settings);
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        ping.set_milliseconds_per_callback(std::chrono::milliseconds(100));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        EXPECT_GE(callbackCounter.load(), 4);
    }

    TEST(NetworkPingTestBasic, Should_Expect_CorrectProperties_When_Updated)
    {
        QLogicaeCore::NetworkPingSettings settings;
        settings.name = "ping-test";
        settings.host_address = "localhost";
        settings.callback = [](const QLogicaeCore::NetworkPingResponse&) {};

        QLogicaeCore::NetworkPing ping(settings);
        ping.set_name("ping-new");
        ping.set_host_address("127.0.0.1");
        ping.set_milliseconds_per_callback(std::chrono::milliseconds(500));

        EXPECT_EQ(ping.get_name(), "ping-new");
        EXPECT_EQ(ping.get_host_address(), "127.0.0.1");
        EXPECT_EQ(ping.get_milliseconds_per_callback(), std::chrono::milliseconds(500));
    }

    TEST(NetworkPingTestStress, Should_Expect_MultipleCallbacks_When_MultiInstances)
    {
        auto totalCallbacks = std::make_shared<std::atomic<int>>(0);
        std::vector<std::unique_ptr<QLogicaeCore::NetworkPing>> pings;

        for (int i = 0; i < 5; ++i)
        {
            QLogicaeCore::NetworkPingSettings settings;
            settings.name = "multi-instance-" + std::to_string(i);
            settings.callback = [totalCallbacks](const QLogicaeCore::NetworkPingResponse&) {
                totalCallbacks->fetch_add(1);
                };
            pings.push_back(std::make_unique<QLogicaeCore::NetworkPing>(settings));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        EXPECT_GT(totalCallbacks->load(), 5);
    }

    TEST_P(NetworkPingTest, Should_Expect_Callback_When_IntervalExpires)
    {
        networkPingSettings.milliseconds_per_callback = GetParam();
        QLogicaeCore::NetworkPing ping(networkPingSettings);
        WaitForCallback();
        EXPECT_GE(latestResponse.load(), 0);
    }

    INSTANTIATE_TEST_CASE_P(
        IntervalTimings,
        NetworkPingTest,
        ::testing::Values(
            std::chrono::milliseconds(1),
            std::chrono::milliseconds(2),
            std::chrono::milliseconds(500),
            std::chrono::milliseconds(1000)
        )
    );

}
