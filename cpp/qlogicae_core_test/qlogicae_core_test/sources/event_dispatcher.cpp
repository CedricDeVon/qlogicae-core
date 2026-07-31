#include "pch.hpp"

#include "qlogicae_core/includes/event_dispatcher.hpp"

namespace QLogicaeCoreTest
{
    struct EventAlpha
    {
        int value;
    };

    struct EventBeta
    {
        std::string message;
    };

    using Dispatcher = QLogicaeCore::EventDispatcher<EventAlpha, EventBeta>;

    class EventDispatcherTest : public ::testing::TestWithParam<int>
    {
    protected:
        Dispatcher dispatcher;
    };

    TEST_P(EventDispatcherTest, Should_Expect_CorrectDispatch_When_EventAlphaDispatched)
    {
        std::atomic<int> sum{ 0 };

        auto handle = dispatcher.subscribe<EventAlpha>([&](const EventAlpha& event)
            {
                sum += event.value;
            });

        dispatcher.dispatch(EventAlpha{ GetParam() });

        ASSERT_EQ(sum.load(), GetParam());
    }

    TEST_P(EventDispatcherTest, Should_Expect_CorrectDispatch_When_EventBetaDispatched)
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        auto handle = dispatcher.subscribe<EventBeta>([&](const EventBeta& event)
            {
                promise.set_value(event.message);
            });

        dispatcher.dispatch(EventBeta{ std::to_string(GetParam()) });

        ASSERT_EQ(future.get(), std::to_string(GetParam()));
    }

    TEST_P(EventDispatcherTest, Should_Expect_CallbackInvoked_When_AsyncEventAlphaDispatched)
    {
        std::promise<int> promise;
        auto future = promise.get_future();

        auto handle = dispatcher.subscribe<EventAlpha>([&](const EventAlpha& event)
            {
                promise.set_value(event.value);
            });

        dispatcher.dispatch_async(EventAlpha{ GetParam() });

        ASSERT_EQ(future.get(), GetParam());
    }

    TEST_P(EventDispatcherTest, Should_Expect_CallbackInvoked_When_AsyncEventBetaDispatched)
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        auto handle = dispatcher.subscribe<EventBeta>([&](const EventBeta& event)
            {
                promise.set_value(event.message);
            });

        dispatcher.dispatch_async(EventBeta{ std::to_string(GetParam()) });

        ASSERT_EQ(future.get(), std::to_string(GetParam()));
    }

    TEST_P(EventDispatcherTest, Should_Expect_NoInvocation_When_EventAlphaUnsubscribed)
    {
        std::atomic<int> count{ 0 };

        {
            auto handle = dispatcher.subscribe<EventAlpha>([&](const EventAlpha&)
                {
                    count++;
                });

            handle.unsubscribe();
        }

        dispatcher.dispatch(EventAlpha{ GetParam() });

        ASSERT_EQ(count.load(), 0);
    }

    TEST_P(EventDispatcherTest, Should_Expect_MultithreadedDispatch_When_EventAlphaUsed)
    {
        std::atomic<int> total{ 0 };

        auto handle = dispatcher.subscribe<EventAlpha>([&](const EventAlpha& event)
            {
                total += event.value;
            });

        std::vector<std::thread> threads;
        for (int index = 0; index < 32; ++index)
        {
            threads.emplace_back([&]()
                {
                    dispatcher.dispatch(EventAlpha{ GetParam() });
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        ASSERT_EQ(total.load(), 32 * GetParam());
    }

    TEST_P(EventDispatcherTest, Should_Expect_PerformanceWithinLimit_When_EventAlphaStress)
    {
        std::atomic<int> count{ 0 };

        auto handle = dispatcher.subscribe<EventAlpha>([&](const EventAlpha&)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(10));
                count++;
            });

        auto start = std::chrono::steady_clock::now();

        for (int index = 0; index < 100; ++index)
        {
            dispatcher.dispatch(EventAlpha{ 1 });
        }

        auto stop = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        ASSERT_EQ(count.load(), 100);

        ASSERT_LE(duration.count(), 2000);
    }

    TEST_P(EventDispatcherTest, Should_Expect_PerformanceWithinLimit_When_EventBetaStress)
    {
        std::atomic<int> count{ 0 };

        auto handle = dispatcher.subscribe<EventBeta>([&](const EventBeta&)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(10));
                count++;
            });

        auto start = std::chrono::steady_clock::now();

        for (int index = 0; index < 100; ++index)
        {
            dispatcher.dispatch(EventBeta{ "x" });
        }

        auto stop = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        ASSERT_EQ(count.load(), 100);

        ASSERT_LE(duration.count(), 2000);
    }

    TEST_P(EventDispatcherTest, Should_Expect_CorrectResult_When_AsyncStressAlpha)
    {
        std::atomic<int> count{ 0 };

        auto handle = dispatcher.subscribe<EventAlpha>([&](const EventAlpha&)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(10));
                count++;
            });

        for (int index = 0; index < 1000; ++index)
        {
            dispatcher.dispatch_async(EventAlpha{ 1 });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        ASSERT_GE(count.load(), 900);
    }

    TEST_P(EventDispatcherTest, Should_Expect_CorrectResult_When_AsyncStressBeta)
    {
        std::atomic<int> count{ 0 };

        auto handle = dispatcher.subscribe<EventBeta>([&](const EventBeta&)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(10));
                count++;
            });

        for (int index = 0; index < 1000; ++index)
        {
            dispatcher.dispatch_async(EventBeta{ "x" });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        ASSERT_GE(count.load(), 900);
    }

    TEST_P(EventDispatcherTest, Should_Expect_CorrectTransfer_When_MoveSubscriptionAlpha)
    {
        std::atomic<int> count{ 0 };

        auto handle_one = dispatcher.subscribe<EventAlpha>([&](const EventAlpha&) { count++; });
        auto handle_two = std::move(handle_one);

        dispatcher.dispatch(EventAlpha{ 1 });

        ASSERT_EQ(count.load(), 1);
    }

    TEST_P(EventDispatcherTest, Should_Expect_CorrectTransfer_When_MoveAssignmentAlpha)
    {
        std::atomic<int> count{ 0 };

        auto handle_one = dispatcher.subscribe<EventAlpha>([&](const EventAlpha&) { count++; });
        auto handle_two = dispatcher.subscribe<EventAlpha>([&](const EventAlpha&) { count++; });

        handle_one = std::move(handle_two);

        dispatcher.dispatch(EventAlpha{ 1 });

        ASSERT_EQ(count.load(), 1);
    }

    TEST_P(EventDispatcherTest, Should_Expect_OnlyOneCallback_When_DoubleUnsubscribed)
    {
        std::atomic<int> count{ 0 };

        auto handle = dispatcher.subscribe<EventAlpha>([&](const EventAlpha&) { count++; });

        handle.unsubscribe();
        handle.unsubscribe();

        dispatcher.dispatch(EventAlpha{ 1 });

        ASSERT_EQ(count.load(), 0);
    }

    INSTANTIATE_TEST_CASE_P(
        EventDispatcherTestParam,
        EventDispatcherTest,
        ::testing::Values(
            -1000,
            -1,
            0,
            1,
            2,
            3,
            5,
            7,
            10,
            100,
            1000,
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::min()
        )
    );
}

