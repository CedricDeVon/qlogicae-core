#include "pch.hpp"

#include "qlogicae_core/includes/timeout.hpp"

namespace QLogicaeCoreTest
{
    class TimeoutTest : public ::testing::TestWithParam<bool> {};

    TEST_P(TimeoutTest,
        Should_Expect_CallbackExecution_When_DelayedOrImmediate)
    {
        std::atomic<bool> callback_invoked = false;

        {
            QLogicaeCore::Timeout timeout(
                [&]() { callback_invoked.store(true); },
                std::chrono::milliseconds(100),
                GetParam()
            );

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        EXPECT_TRUE(callback_invoked.load());
    }

    TEST_P(TimeoutTest,
        Should_Expect_CancelledCallback_When_CancelBeforeExecution)
    {
        std::atomic<bool> callback_invoked = false;

        QLogicaeCore::Timeout timeout(
            [&]() { callback_invoked.store(true); },
            std::chrono::milliseconds(500),
            GetParam()
        );

        timeout.cancel();

        std::this_thread::sleep_for(std::chrono::milliseconds(600));

        EXPECT_FALSE(callback_invoked.load());
        EXPECT_TRUE(timeout.is_cancelled());
    }

    TEST_P(TimeoutTest, Should_Expect_RestartExecutesCallback_When_Called)
    {
        std::atomic<bool> callback_invoked = false;

        QLogicaeCore::Timeout timeout(
            [&]() { callback_invoked.store(true); },
            std::chrono::milliseconds(500),
            GetParam()
        );

        timeout.cancel();
        callback_invoked.store(false);
        timeout.restart();

        std::this_thread::sleep_for(std::chrono::milliseconds(600));

        EXPECT_TRUE(callback_invoked.load());
    }

    TEST_P(TimeoutTest, Should_Expect_ThrowHandling_When_CallbackThrows)
    {
        std::atomic<bool> executed = false;

        QLogicaeCore::Timeout timeout(
            [&]() {
                executed.store(true);
                throw std::runtime_error("Timeout failure");
            },
            std::chrono::milliseconds(100),
            GetParam()
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        EXPECT_TRUE(executed.load());
    }

    TEST_P(TimeoutTest, Should_Expect_Stable_When_StressUnder2Seconds)
    {
        std::atomic<int> invocation_count = 0;
        std::vector<std::unique_ptr<QLogicaeCore::Timeout>> timeouts;

        auto start_time = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - start_time
            < std::chrono::seconds(2))
        {
            timeouts.emplace_back(std::make_unique<QLogicaeCore::Timeout>(
                [&]() { invocation_count.fetch_add(1); },
                std::chrono::milliseconds(10),
                GetParam()
            ));
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        EXPECT_GT(invocation_count.load(), 50);
    }

    TEST_P(TimeoutTest, Should_Expect_ThreadSafeExecution_When_Concurrent)
    {
        constexpr int thread_count = 16;
        std::atomic<int> completed = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&]()
                {
                    QLogicaeCore::Timeout timeout(
                        [&]() { completed.fetch_add(1); },
                        std::chrono::milliseconds(50),
                        GetParam()
                    );
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(100));
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(completed.load(), thread_count);
    }

    TEST_P(TimeoutTest, Should_Expect_SkipExecution_When_NullLambda)
    {
        std::function<void()> function_empty;
        EXPECT_NO_THROW({
            QLogicaeCore::Timeout timeout(
                function_empty,
                std::chrono::milliseconds(100),
                GetParam()
            );
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            });
    }

    TEST_P(TimeoutTest, Should_Expect_CorrectlyExecute_When_LongLivedTimeout)
    {
        std::atomic<bool> callback_invoked = false;

        QLogicaeCore::Timeout timeout(
            [&]() { callback_invoked.store(true); },
            std::chrono::seconds(1),
            GetParam()
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(1200));

        EXPECT_TRUE(callback_invoked.load());
    }

    TEST_P(TimeoutTest, Should_Expect_NestedCallback_When_CalledInsideAnother)
    {
        std::atomic<bool> inner_invoked = false;
        std::atomic<bool> outer_invoked = false;

        QLogicaeCore::Timeout timeout_outer(
            [&]()
            {
                outer_invoked.store(true);

                QLogicaeCore::Timeout timeout_inner(
                    [&]() { inner_invoked.store(true); },
                    std::chrono::milliseconds(100),
                    GetParam()
                );

                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            },
            std::chrono::milliseconds(100),
            GetParam()
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        EXPECT_TRUE(outer_invoked.load());
        EXPECT_TRUE(inner_invoked.load());
    }

    TEST_P(TimeoutTest, Should_Expect_OnlyLastExecution_When_ChainedRestarts)
    {
        std::atomic<int> call_counter = 0;

        QLogicaeCore::Timeout timeout(
            [&]() { ++call_counter; },
            std::chrono::milliseconds(200),
            false
        );

        for (int index = 0; index < 5; index++)
        {
            timeout.restart();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        EXPECT_EQ(call_counter.load(), 1);
    }

    TEST_P(TimeoutTest, Should_Expect_InnerSkipped_When_CancelledDuringNested)
    {
        std::atomic<bool> inner_executed = false;

        QLogicaeCore::Timeout* timeout_inner = nullptr;

        QLogicaeCore::Timeout timeout_outer(
            [&]()
            {
                timeout_inner = new QLogicaeCore::Timeout(
                    [&]() { inner_executed.store(true); },
                    std::chrono::milliseconds(200)
                );

                timeout_inner->cancel();
            },
            std::chrono::milliseconds(100),
            false
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        EXPECT_FALSE(inner_executed.load());

        if (timeout_inner != nullptr)
        {
            delete timeout_inner;
        }
    }

    TEST_P(TimeoutTest, Should_Expect_NestedExecution_When_CrossThreadTimeouts)
    {
        std::atomic<bool> callback_executed = false;

        std::thread thread_outer([&]()
            {
                QLogicaeCore::Timeout timeout(
                    [&]() { callback_executed.store(true); },
                    std::chrono::milliseconds(100)
                );

                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            });

        thread_outer.join();
        EXPECT_TRUE(callback_executed.load());
    }

    TEST_P(TimeoutTest, Should_Expect_DeferredSchedule_When_UsingFutureValue)
    {
        std::promise<int> promise_value;
        std::future<int> future_value = promise_value.get_future();

        std::atomic<int> observed = -1;

        QLogicaeCore::Timeout timeout(
            [&]()
            {
                observed.store(future_value.get());
            },
            std::chrono::milliseconds(200),
            false
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        promise_value.set_value(42);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        EXPECT_EQ(observed.load(), 42);
    }

    TEST_P(TimeoutTest, Should_Expect_LimitedRecursion_When_SelfRescheduling)
    {
        std::atomic<int> trigger_count = 0;
        std::shared_ptr<QLogicaeCore::Timeout> timeout_ptr;
        std::weak_ptr<QLogicaeCore::Timeout> weak_timeout_ptr;

        timeout_ptr = std::make_shared<QLogicaeCore::Timeout>(
            [&]()
            {
                if (trigger_count.fetch_add(1) < 5)
                {
                    std::thread restart_thread([weak_timeout_ptr]() {
                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(1));
                        if (auto timeout = weak_timeout_ptr.lock())
                        {
                            timeout->restart();
                        }
                        });
                    restart_thread.detach();
                }
            },
            std::chrono::milliseconds(50),
            false
        );

        weak_timeout_ptr = timeout_ptr;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        EXPECT_EQ(trigger_count.load(), 6);
    }

    TEST_P(TimeoutTest, Should_Expect_AllNestedToExecute_When_MassiveNesting)
    {
        static constexpr int total_nested = 128;

        std::atomic<int> execution_count = 0;
        std::vector<std::unique_ptr<QLogicaeCore::Timeout>> timeouts;

        for (int index = 0; index < total_nested; index++)
        {
            timeouts.emplace_back(std::make_unique<QLogicaeCore::Timeout>(
                [&]() { execution_count.fetch_add(1); },
                std::chrono::milliseconds(10 + index)
            ));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        EXPECT_EQ(execution_count.load(), total_nested);
    }

    TEST_P(TimeoutTest, Should_Expect_OuterToSurvive_When_InnerThrows)
    {
        std::atomic<bool> outer_executed = false;
        std::atomic<bool> inner_caught = false;

        QLogicaeCore::Timeout timeout_outer(
            [&]()
            {
                outer_executed.store(true);

                try
                {
                    QLogicaeCore::Timeout timeout_inner(
                        [&]() { throw std::runtime_error("Inner crash"); },
                        std::chrono::milliseconds(50)
                    );

                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                catch (...)
                {
                    inner_caught.store(true);
                }
            },
            std::chrono::milliseconds(50)
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        EXPECT_TRUE(outer_executed.load());
        EXPECT_FALSE(inner_caught.load());
    }

    INSTANTIATE_TEST_CASE_P(
        TimeoutVariants,
        TimeoutTest,
        ::testing::Values(true, false)
    );
}
