#include "pch.hpp"

#include "qlogicae_cpp_core/includes/timeout_clock.hpp"

namespace QLogicaeCppCoreTest
{
    class TimeoutClockTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
    };

    struct TimeoutParamTestData
    {
        bool is_executed_immediately;
        std::chrono::milliseconds delay_in_milliseconds;
    };

    class TimeoutParamTest : public ::testing::TestWithParam<TimeoutParamTestData> {};

    TEST_F(TimeoutClockTest, Should_ExecuteCallbackImmediately_When_IsExecutedImmediatelyTrue)
    {
        std::atomic<bool> callback_executed{ false };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = true;
        config.callback = [&]()
            {
                callback_executed.store(true);
            };

        QLogicaeCppCore::TimeoutClock timeout(config);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_TRUE(callback_executed.load());
    }

    TEST_F(TimeoutClockTest, Should_ExecuteCallbackAfterDelay_When_IsExecutedImmediatelyFalse)
    {
        std::atomic<bool> callback_executed{ false };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = false;
        config.delay_in_milliseconds = std::chrono::milliseconds(100);
        config.callback = [&]()
            {
                callback_executed.store(true);
            };

        QLogicaeCppCore::TimeoutClock timeout(config);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        EXPECT_FALSE(callback_executed.load());

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_TRUE(callback_executed.load());
    }

    TEST_F(TimeoutClockTest, Should_NotExecuteCallback_When_CancelledBeforeExecution)
    {
        std::atomic<bool> callback_executed{ false };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = false;
        config.delay_in_milliseconds = std::chrono::milliseconds(100);
        config.callback = [&]()
            {
                callback_executed.store(true);
            };

        QLogicaeCppCore::TimeoutClock timeout(config);
        QLogicaeCppCore::Result<bool> result;
        timeout.cancel(result);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        EXPECT_FALSE(callback_executed.load());
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(TimeoutClockTest, Should_SetCancelledFlag_When_Cancelled)
    {
        QLogicaeCppCore::TimeoutClockConfigurations config;
        QLogicaeCppCore::TimeoutClock timeout(config);
        QLogicaeCppCore::Result<bool> result;

        timeout.cancel(result);

        QLogicaeCppCore::Result<bool> is_cancelled_result;
        timeout.is_cancelled(is_cancelled_result);
        EXPECT_TRUE(is_cancelled_result.get_value());
    }

    TEST_F(TimeoutClockTest, Should_RestartTimeout_When_RestartCalled)
    {
        std::atomic<int> callback_counter{ 0 };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = false;
        config.delay_in_milliseconds = std::chrono::milliseconds(50);
        config.callback = [&]()
            {
                callback_counter.fetch_add(1);
            };

        QLogicaeCppCore::TimeoutClock timeout(config);
        QLogicaeCppCore::Result<bool> result;
        timeout.restart(result);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_EQ(callback_counter.load(), 1);
    }

    TEST_F(TimeoutClockTest, Should_HandleExceptionsInCallbackGracefully)
    {
        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.callback = []()
            {
                throw std::runtime_error("callback exception");
            };
        config.is_executed_immediately = true;

        QLogicaeCppCore::TimeoutClock timeout(config);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    TEST_F(TimeoutClockTest, Should_WorkUnderHighConcurrencyStress)
    {
        constexpr int iterations = 50;
        std::atomic<int> callback_counter{ 0 };

        std::vector<std::unique_ptr<QLogicaeCppCore::TimeoutClock>> timeouts;
        for (int i = 0; i < iterations; ++i)
        {
            QLogicaeCppCore::TimeoutClockConfigurations config;
            config.is_executed_immediately = true;
            config.callback = [&]()
                {
                    callback_counter.fetch_add(1);
                };
            timeouts.push_back(std::make_unique<QLogicaeCppCore::TimeoutClock>(config));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_EQ(callback_counter.load(), iterations);
    }

    TEST_F(TimeoutClockTest, Should_HandleZeroDelayEdgeCase)
    {
        std::atomic<bool> callback_executed{ false };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = false;
        config.delay_in_milliseconds = std::chrono::milliseconds(0);
        config.callback = [&]()
            {
                callback_executed.store(true);
            };

        QLogicaeCppCore::TimeoutClock timeout(config);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_TRUE(callback_executed.load());
    }

    TEST_F(TimeoutClockTest, Should_HandleReentrantConstructCallsGracefully)
    {
        std::atomic<int> callback_counter{ 0 };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = true;
        config.callback = [&]()
            {
                callback_counter.fetch_add(1);
            };

        QLogicaeCppCore::TimeoutClock timeout(config);
        QLogicaeCppCore::Result<bool> result1;
        timeout.construct(result1, config);

        QLogicaeCppCore::Result<bool> result2;
        timeout.construct(result2, config);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        EXPECT_GE(callback_counter.load(), 1);
        EXPECT_TRUE(result1.get_value());
        EXPECT_TRUE(result2.get_value());
    }

    TEST_F(TimeoutClockTest, Should_RespectUpdatedIsExecutedImmediately_OnRestart)
    {
        std::atomic<int> callback_counter{ 0 };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = false;
        config.delay_in_milliseconds = std::chrono::milliseconds(50);
        config.callback = [&]()
            {
                callback_counter.fetch_add(1);
            };

        QLogicaeCppCore::TimeoutClock timeout(config);
        QLogicaeCppCore::Result<bool> result1;
        timeout.restart(result1);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_EQ(callback_counter.load(), 1);

        config.is_executed_immediately = true;
        timeout.configurations = config;
        QLogicaeCppCore::Result<bool> result2;
        timeout.restart(result2);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_EQ(callback_counter.load(), 2);
    }

    TEST_F(TimeoutClockTest, Should_HandleRapidSuccessiveCancelAndRestart)
    {
        std::atomic<int> callback_counter{ 0 };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = false;
        config.delay_in_milliseconds = std::chrono::milliseconds(20);
        config.callback = [&]()
            {
                callback_counter.fetch_add(1);
            };

        QLogicaeCppCore::TimeoutClock timeout(config);

        for (int i = 0; i < 10; ++i)
        {
            QLogicaeCppCore::Result<bool> cancel_result;
            timeout.cancel(cancel_result);

            QLogicaeCppCore::Result<bool> restart_result;
            timeout.restart(restart_result);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        EXPECT_GE(callback_counter.load(), 1);
    }

    TEST_P(TimeoutParamTest, Should_ExecuteCallbackAccordingToConfig)
    {
        std::atomic<bool> callback_executed{ false };

        TimeoutParamTestData param = GetParam();
        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = param.is_executed_immediately;
        config.delay_in_milliseconds = param.delay_in_milliseconds;
        config.callback = [&]() { callback_executed.store(true); };

        QLogicaeCppCore::TimeoutClock timeout(config);

        std::this_thread::sleep_for(param.delay_in_milliseconds + std::chrono::milliseconds(50));
        EXPECT_TRUE(callback_executed.load());
    }

    INSTANTIATE_TEST_CASE_P(
        TimeoutCombinations,
        TimeoutParamTest,
        ::testing::Values(
            TimeoutParamTestData{ true, std::chrono::milliseconds(0) },
            TimeoutParamTestData{ true, std::chrono::milliseconds(100) },
            TimeoutParamTestData{ false, std::chrono::milliseconds(0) },
            TimeoutParamTestData{ false, std::chrono::milliseconds(50) }
        )
    );

    TEST_F(TimeoutClockTest, Should_NotExecuteCallbackAfterDestruction)
    {
        std::atomic<bool> callback_executed{ false };

        {
            QLogicaeCppCore::TimeoutClockConfigurations config;
            config.is_executed_immediately = false;
            config.delay_in_milliseconds = std::chrono::milliseconds(100);
            config.callback = [&]() { callback_executed.store(true); };

            QLogicaeCppCore::TimeoutClock timeout(config);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        EXPECT_FALSE(callback_executed.load());
    }

    TEST_F(TimeoutClockTest, Should_TreatNegativeDelayAsZero)
    {
        std::atomic<bool> callback_executed{ false };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = false;
        config.delay_in_milliseconds = std::chrono::milliseconds(-100);
        config.callback = [&]() { callback_executed.store(true); };

        QLogicaeCppCore::TimeoutClock timeout(config);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        EXPECT_TRUE(callback_executed.load());
    }

    TEST_F(TimeoutClockTest, Should_HandleSimultaneousConstructAndRestart)
    {
        std::atomic<int> callback_counter{ 0 };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = false;
        config.delay_in_milliseconds = std::chrono::milliseconds(20);
        config.callback = [&]() { callback_counter.fetch_add(1); };

        QLogicaeCppCore::TimeoutClock timeout(config);

        std::thread t1([&]() {
            QLogicaeCppCore::Result<bool> result1;
            timeout.construct(result1, config);
            });

        std::thread t2([&]() {
            QLogicaeCppCore::Result<bool> result2;
            timeout.restart(result2);
            });

        t1.join();
        t2.join();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        EXPECT_GE(callback_counter.load(), 1);
    }

    TEST_F(TimeoutClockTest, Should_ExecuteCallbackWithPromise)
    {
        std::promise<void> callback_done;
        auto callback_future = callback_done.get_future();

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = false;
        config.delay_in_milliseconds = std::chrono::milliseconds(50);
        config.callback = [&]() { callback_done.set_value(); };

        QLogicaeCppCore::TimeoutClock timeout(config);

        auto status = callback_future.wait_for(std::chrono::milliseconds(100));
        EXPECT_EQ(status, std::future_status::ready);
    }

    TEST_F(TimeoutClockTest, Should_HandleCallbackThrowingNonStdException)
    {
        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = true;
        config.callback = []() { throw 42; };

        QLogicaeCppCore::TimeoutClock timeout(config);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        SUCCEED();
    }

    TEST_F(TimeoutClockTest, Should_SafelyDestroyDuringCallbackExecution)
    {
        std::atomic<bool> callback_started{ false };
        std::atomic<bool> callback_finished{ false };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = true;
        config.delay_in_milliseconds = std::chrono::milliseconds(50);
        config.callback = [&]()
            {
                callback_started.store(true);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                callback_finished.store(true);
            };

        auto timeout = std::make_unique<QLogicaeCppCore::TimeoutClock>(config);

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        timeout.reset();

        EXPECT_TRUE(callback_started.load());
    }

    TEST_F(TimeoutClockTest, Should_WorkWithVeryLongDelay)
    {
        std::atomic<bool> callback_executed{ false };

        QLogicaeCppCore::TimeoutClockConfigurations config;
        config.is_executed_immediately = false;
        config.delay_in_milliseconds = std::chrono::milliseconds(1000);
        config.callback = [&]() { callback_executed.store(true); };

        QLogicaeCppCore::TimeoutClock timeout(config);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        EXPECT_FALSE(callback_executed.load());
    }

    TEST_F(TimeoutClockTest, Should_WorkWithMultipleInstancesSharingCallback)
    {
        std::atomic<int> callback_counter{ 0 };

        auto shared_callback = [&]() { callback_counter.fetch_add(1); };

        constexpr int instances = 5;
        std::vector<std::unique_ptr<QLogicaeCppCore::TimeoutClock>> timeouts;

        for (int i = 0; i < instances; ++i)
        {
            QLogicaeCppCore::TimeoutClockConfigurations config;
            config.is_executed_immediately = true;
            config.callback = shared_callback;
            timeouts.push_back(std::make_unique<QLogicaeCppCore::TimeoutClock>(config));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        EXPECT_EQ(callback_counter.load(), instances);
    }
}
