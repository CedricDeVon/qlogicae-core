#include "pch.hpp"

#include "qlogicae_cpp_core/includes/network_ping_manager.hpp"

namespace QLogicaeCppCoreTest
{
    class NetworkPingManagerTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            configurations.host_address = "www.google.com";
            configurations.is_listening = true;
            configurations.name = "ping-manager-instance";
            configurations.callback = [this](const QLogicaeCppCore::NetworkPingManagerResponse& response)
                {
                    std::lock_guard<std::mutex> lock(callbackMutex);
                    latestResponse = response.delay_in_milliseconds;
                    callbackCondition.notify_all();
                };
        }

        void WaitForCallback()
        {
            std::unique_lock<std::mutex> lock(callbackMutex);
            callbackCondition.wait(lock, [&]() { return latestResponse >= 0; });
        }

        QLogicaeCppCore::NetworkPingManagerConfigurations configurations;
        std::condition_variable callbackCondition;
        std::mutex callbackMutex;
        std::atomic<int64_t> latestResponse{ -1 };
    };

    TEST_F(NetworkPingManagerTest, Should_Expect_Callback_When_PingSucceeds)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::NetworkPingManager manager(configurations);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        EXPECT_GE(latestResponse.load(), 0);
    }

    TEST_F(NetworkPingManagerTest, Should_Expect_NoCallback_When_InvalidHost)
    {
        configurations.host_address = "invalid.host.invalid";
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::NetworkPingManager manager(configurations);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        EXPECT_EQ(latestResponse.load(), -1);
    }

    TEST_F(NetworkPingManagerTest, Should_Expect_PauseAndContinueListening)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::NetworkPingManager manager(configurations);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        manager.pause_listening(result);
        int64_t pausedValue = latestResponse.load();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        manager.continue_listening(result);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_TRUE(result.get_status() == QLogicaeCppCore::ResultStatus::GOOD);
    }

    TEST_F(NetworkPingManagerTest, Should_Expect_SetIsListening)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::NetworkPingManager manager(configurations);
        manager.set_is_listening(result, true);
        EXPECT_TRUE(configurations.is_listening);
    }

    TEST_F(NetworkPingManagerTest, Should_Expect_ConstructAndDestruct)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::NetworkPingManager manager;
        configurations.is_listening = false;
        manager.construct(result, configurations);
        EXPECT_TRUE(result.get_status() == QLogicaeCppCore::ResultStatus::GOOD);
        manager.destruct(result);
        EXPECT_TRUE(result.get_status() == QLogicaeCppCore::ResultStatus::GOOD);
    }

    TEST_F(NetworkPingManagerTest, Should_Expect_GetIsListening)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::NetworkPingManager manager(configurations);
        manager.get_is_listening(result);
        bool isListening = false;
        result.get_value(isListening);
        EXPECT_TRUE(isListening);
    }

    class NetworkPingManagerEdgeTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            configurations.host_address = "test.host";
            configurations.is_listening = true;
            configurations.name = "edge-instance";
            configurations.callback = [&](const QLogicaeCppCore::NetworkPingManagerResponse& response)
                {
                    latestResponse = response.delay_in_milliseconds;
                    callbackCondition.notify_all();
                };
        }

        void WaitForCallback()
        {
            std::unique_lock<std::mutex> lock(callbackMutex);
            callbackCondition.wait(lock, [&]() { return latestResponse >= 0; });
        }

        QLogicaeCppCore::NetworkPingManagerConfigurations configurations;
        std::condition_variable callbackCondition;
        std::mutex callbackMutex;
        std::atomic<int64_t> latestResponse{ -1 };
    };

    TEST_F(NetworkPingManagerEdgeTest, Should_Expect_SetIsListeningFalse)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::NetworkPingManager manager(configurations);
        manager.set_is_listening(result, false);
        EXPECT_FALSE(manager.configurations.is_listening);
        EXPECT_EQ(result.get_status(), QLogicaeCppCore::ResultStatus::GOOD);
    }

    TEST_F(NetworkPingManagerEdgeTest, Should_Expect_RapidPauseAndResume)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::NetworkPingManager manager(configurations);
        for (int i = 0; i < 5; ++i)
        {
            manager.pause_listening(result);
            EXPECT_EQ(result.get_status(), QLogicaeCppCore::ResultStatus::GOOD);
            manager.continue_listening(result);
            EXPECT_EQ(result.get_status(), QLogicaeCppCore::ResultStatus::GOOD);
        }
    }

    TEST_F(NetworkPingManagerEdgeTest, Should_Expect_DelayEdgeCases)
    {
        QLogicaeCppCore::Result<bool> result;

        configurations.delay_in_milliseconds = std::chrono::milliseconds(0);
        QLogicaeCppCore::NetworkPingManager managerZero(configurations);
        EXPECT_EQ(managerZero.configurations.delay_in_milliseconds.count(), 0);

        configurations.delay_in_milliseconds = std::chrono::milliseconds(10000);
        QLogicaeCppCore::NetworkPingManager managerLarge(configurations);
        EXPECT_EQ(managerLarge.configurations.delay_in_milliseconds.count(), 10000);
    }

    TEST_F(NetworkPingManagerEdgeTest, Should_Expect_MultiInstanceStress)
    {
        auto totalCallbacks = std::make_shared<std::atomic<int>>(0);
        std::vector<std::unique_ptr<QLogicaeCppCore::NetworkPingManager>> managers;

        for (int i = 0; i < 5; ++i)
        {
            QLogicaeCppCore::NetworkPingManagerConfigurations cfg;
            cfg.name = "stress-instance-" + std::to_string(i);
            cfg.callback = [totalCallbacks](const QLogicaeCppCore::NetworkPingManagerResponse&)
                {
                    totalCallbacks->fetch_add(1);
                };
            cfg.is_listening = true;

            auto manager = std::make_unique<QLogicaeCppCore::NetworkPingManager>(cfg);
            managers.push_back(std::move(manager));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        EXPECT_GT(totalCallbacks->load(), 0);
    }
}
