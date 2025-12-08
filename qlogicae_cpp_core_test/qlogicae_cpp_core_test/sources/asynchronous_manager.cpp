#include "pch.hpp"

#include "qlogicae_cpp_core/includes/asynchronous_manager.hpp"

namespace QLogicaeCppCoreTest
{
    static bool wait_for_condition_for_ms(
        const std::function<bool()>& condition,
        const std::uint64_t timeout_ms
    )
    {
        const std::chrono::milliseconds poll_interval(5);
        const auto start_time = std::chrono::steady_clock::now();
        while (true)
        {
            if (condition())
            {
                return true;
            }
            const auto elapsed_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - start_time
                )
                .count();
            if (static_cast<std::uint64_t>(elapsed_ms) >= timeout_ms)
            {
                return false;
            }
            std::this_thread::sleep_for(poll_interval);
        }
    }

    class AsynchronousManagerTest : public ::testing::Test
    {
    public:
        AsynchronousManagerTest()
        {
        }

        ~AsynchronousManagerTest()
        {
        }
    };

    class AsynchronousManagerParamTest :
        public ::testing::TestWithParam<int>
    {
    public:
        AsynchronousManagerParamTest()
        {
        }

        ~AsynchronousManagerParamTest()
        {
        }
    };

    TEST(AsynchronousManagerTest, Should_ExecuteCallback_When_PostedOnce)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<bool> callback_executed(false);
        asynchronous_manager.begin_one_thread(
            result,
            [&callback_executed]()
            {
                callback_executed.store(true);
            }
        );
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_TRUE(callback_executed.load());
    }

    TEST(AsynchronousManagerTest,
        Should_ExecuteMultipleCallbacks_When_PostedConcurrently)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<int> counter(0);
        const int task_count = 32;
        for (int index = 0; index < task_count; ++index)
        {
            asynchronous_manager.begin_one_thread(
                result,
                [&counter]()
                {
                    counter.fetch_add(1);
                }
            );
        }
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_EQ(counter.load(), task_count);
    }

    TEST(AsynchronousManagerTest,
        Should_HandleAsyncCallsFromMultipleThreads_When_CalledConcurrently)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<int> counter(0);
        const int thread_callers = 8;
        const int posts_per_thread = 16;
        std::vector<std::thread> caller_threads;
        for (int caller_index = 0; caller_index < thread_callers;
            ++caller_index)
        {
            caller_threads.emplace_back(
                [&asynchronous_manager, &counter, posts_per_thread, &result]()
                {
                    for (int post_index = 0; post_index < posts_per_thread;
                        ++post_index)
                    {
                        asynchronous_manager.begin_one_thread(
                            result,
                            [&counter]()
                            {
                                counter.fetch_add(1);
                            }
                        );
                    }
                }
            );
        }
        for (auto& caller_thread : caller_threads)
        {
            caller_thread.join();
        }
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_EQ(counter.load(), thread_callers * posts_per_thread);
    }

    TEST(AsynchronousManagerTest,
        Should_CompleteStressWorkload_UnderTimeLimit)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<int> counter(0);
        const int stress_tasks = 512;
        for (int task_index = 0; task_index < stress_tasks; ++task_index)
        {
            asynchronous_manager.begin_one_thread(
                result,
                [&counter]()
                {
                    for (int inner = 0; inner < 10; ++inner)
                    {
                        counter.fetch_add(1);
                    }
                }
            );
        }
        const bool finished_before_timeout =
            wait_for_condition_for_ms(
                [&counter, stress_tasks]()
                {
                    return counter.load() >= stress_tasks * 10;
                },
                1800
            );
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_TRUE(finished_before_timeout);
        ASSERT_EQ(counter.load(), stress_tasks * 10);
    }

    TEST(AsynchronousManagerTest,
        Should_NotLeak_When_CallbackCapturesLargeObject)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        struct LargeObject
        {
            std::vector<int> buffer;
            LargeObject()
            {
                buffer.resize(1024);
            }
        };
        std::shared_ptr<LargeObject> large_shared =
            std::make_shared<LargeObject>();
        std::weak_ptr<LargeObject> weak_reference = large_shared;
        asynchronous_manager.begin_one_thread(
            result,
            [large_shared]()
            {
                volatile int tmp = 0;
                tmp = static_cast<int>(large_shared->buffer.size());
                (void)tmp;
            }
        );
        large_shared.reset();
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_TRUE(weak_reference.expired());
    }

    TEST(AsynchronousManagerTest,
        Should_CatchUserHandledExceptions_When_CallbackThrows)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<bool> caught_flag(false);
        asynchronous_manager.begin_one_thread(
            result,
            [&caught_flag]()
            {
                try
                {
                    throw std::runtime_error("intentional");
                }
                catch (const std::exception&)
                {
                    caught_flag.store(true);
                }
            }
        );
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_TRUE(caught_flag.load());
    }

    TEST_P(AsynchronousManagerParamTest,
        Should_ProcessParameterizedNumberOfTasks_When_VariousCounts)
    {
        QLogicaeCppCore::Result<bool> result;

        const int task_count = GetParam();
        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<int> counter(0);
        for (int index = 0; index < task_count; ++index)
        {
            asynchronous_manager.begin_one_thread(
                result,
                [&counter]()
                {
                    counter.fetch_add(1);
                }
            );
        }
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_EQ(counter.load(), task_count);
    }

    INSTANTIATE_TEST_CASE_P(BasicCounts,
        AsynchronousManagerParamTest,
        ::testing::Values(0, 1, 8, 64));

    TEST(AsynchronousManagerTest, Should_NotHang_When_NoTasksPosted)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_TRUE(true);
    }

    TEST(AsynchronousManagerTest,
        Should_ReturnImmediately_When_TaskIsLongRunning)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<bool> task_started(false);
        std::atomic<bool> task_finished(false);
        const std::chrono::milliseconds simulated_work(300);
        asynchronous_manager.begin_one_thread(
            result,
            [&task_started, &task_finished, simulated_work]()
            {
                task_started.store(true);
                std::this_thread::sleep_for(simulated_work);
                task_finished.store(true);
            }
        );
        const auto start_time = std::chrono::steady_clock::now();
        const auto mid_duration_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start_time
            )
            .count();
        const bool callback_started =
            wait_for_condition_for_ms(
                [&task_started]()
                {
                    return task_started.load();
                },
                1000
            );
        asynchronous_manager.complete_all_threads(
            result
        );
        const auto total_duration_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start_time
            )
            .count();
        ASSERT_TRUE(callback_started);
        ASSERT_LT(mid_duration_ms, 50);
        ASSERT_GT(total_duration_ms, 0);
        ASSERT_TRUE(task_finished.load());
    }

    TEST(AsynchronousManagerTest,
        Should_Allow_MultipleCompleteAllThreads_Calls)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<int> counter(0);
        for (int index = 0; index < 16; ++index)
        {
            asynchronous_manager.begin_one_thread(
                result,
                [&counter]()
                {
                    counter.fetch_add(1);
                }
            );
        }
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_EQ(counter.load(), 16);
        ASSERT_NO_THROW(asynchronous_manager.complete_all_threads(result));
    }

    TEST(AsynchronousManagerTest,
        Should_Allow_BeginAfterComplete_When_NoActiveTasks)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<int> counter(0);
        asynchronous_manager.begin_one_thread(
            result,
            [&counter]()
            {
                counter.fetch_add(1);
            }
        );
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_EQ(counter.load(), 1);
        asynchronous_manager.begin_one_thread(
            result,
            [&counter]()
            {
                counter.fetch_add(1);
            }
        );
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_EQ(counter.load(), 2);
    }

    TEST(AsynchronousManagerTest, Should_Support_MultiplePostJoinCycles)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<int> counter(0);
        const int cycles = 8;
        const int posts_per_cycle = 64;
        for (int cycle_index = 0; cycle_index < cycles; ++cycle_index)
        {
            for (int post_index = 0; post_index < posts_per_cycle;
                ++post_index)
            {
                asynchronous_manager.begin_one_thread(
                    result,
                    [&counter]()
                    {
                        counter.fetch_add(1);
                    }
                );
            }
            asynchronous_manager.complete_all_threads(
                result
            );
        }
        ASSERT_EQ(counter.load(), cycles * posts_per_cycle);
    }

    TEST(AsynchronousManagerTest,
        Should_Handle_HeavyConcurrentStress_Correctly)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager asynchronous_manager;
        std::atomic<int> counter(0);
        const int caller_threads = 64;
        const int posts_each = 128;
        std::vector<std::thread> callers;
        for (int thread_index = 0; thread_index < caller_threads;
            ++thread_index)
        {
            callers.emplace_back(
                [&asynchronous_manager, &counter, posts_each, &result]()
                {
                    for (int post_index = 0; post_index < posts_each;
                        ++post_index)
                    {
                        asynchronous_manager.begin_one_thread(
                            result,
                            [&counter]()
                            {
                                counter.fetch_add(1);
                            }
                        );
                    }
                }
            );
        }
        for (auto& th : callers)
        {
            th.join();
        }
        const bool finished_before_timeout =
            wait_for_condition_for_ms(
                [&counter, caller_threads, posts_each]()
                {
                    return counter.load() >= caller_threads * posts_each;
                },
                1800
            );
        asynchronous_manager.complete_all_threads(
            result
        );
        ASSERT_TRUE(finished_before_timeout);
        ASSERT_EQ(counter.load(), caller_threads * posts_each);
    }

    TEST(AsynchronousManagerTest, Should_WorkWith_GlobalSingletonInstance)
    {
        QLogicaeCppCore::Result<bool> result;

        std::atomic<int> counter(0);
        QLogicaeCppCore::ASYNCHRONOUS_MANAGER.begin_one_thread(
            result,
            [&counter]()
            {
                counter.fetch_add(1);
            }
        );
        QLogicaeCppCore::ASYNCHRONOUS_MANAGER.complete_all_threads(
            result
        );
        ASSERT_EQ(counter.load(), 1);
    }

    TEST(AsynchronousManagerTest,
        Should_Handle_GlobalInstance_ConcurrentUsage)
    {
        QLogicaeCppCore::Result<bool> result;

        std::atomic<int> counter(0);
        const int caller_threads = 16;
        const int posts_each = 32;
        std::vector<std::thread> callers;
        for (int thread_index = 0; thread_index < caller_threads;
            ++thread_index)
        {
            callers.emplace_back(
                [&counter, posts_each, &result]()
                {
                    for (int post_index = 0; post_index < posts_each;
                        ++post_index)
                    {
                        QLogicaeCppCore::ASYNCHRONOUS_MANAGER.begin_one_thread(
                            result,
                            [&counter]()
                            {
                                counter.fetch_add(1);
                            }
                        );
                    }
                }
            );
        }
        for (auto& th : callers)
        {
            th.join();
        }
        const bool finished_before_timeout =
            wait_for_condition_for_ms(
                [&counter, caller_threads, posts_each]()
                {
                    return counter.load() >= caller_threads * posts_each;
                },
                1800
            );
        QLogicaeCppCore::ASYNCHRONOUS_MANAGER.complete_all_threads(
            result
        );
        ASSERT_TRUE(finished_before_timeout);
        ASSERT_EQ(counter.load(), caller_threads * posts_each);
    }

    TEST(AsynchronousManagerTest,
        Should_Handle_ConcurrentInitialization_RaceSafe)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager mgr;
        std::atomic<int> counter(0);

        std::vector<std::thread> threads;

        for (int i = 0; i < 32; ++i)
        {
            threads.emplace_back(
                [&mgr, &counter, &result]()
                {
                    mgr.begin_one_thread(
                        result,
                        [&counter]()
                        {
                            counter.fetch_add(1);
                        }
                    );
                }
            );
        }

        for (auto& t : threads)
        {
            t.join();
        }

        mgr.complete_all_threads(
            result
        );

        ASSERT_EQ(counter.load(), 32);
    }

    TEST(AsynchronousManagerTest,
        Should_NotCrash_When_PostingDuringJoin)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager mgr;
        std::atomic<int> counter(0);

        std::thread joiner(
            [&mgr, &result]()
            {
                mgr.complete_all_threads(
                    result
                );
            }
        );

        std::thread poster(
            [&mgr, &counter, &result]()
            {
                for (int i = 0; i < 100; ++i)
                {
                    mgr.begin_one_thread(
                        result,
                        [&counter]()
                        {
                            counter.fetch_add(1);
                        }
                    );
                }
            }
        );

        joiner.join();
        poster.join();

        SUCCEED();  
    }

    TEST(AsynchronousManagerTest,
        Destruction_WithActiveTasks_DoesNotCrash)
    {
        QLogicaeCppCore::Result<bool> result;

        std::atomic<bool> started(false);

        {
            QLogicaeCppCore::AsynchronousManager mgr;

            mgr.begin_one_thread(
                result,
                [&started]()
                {
                    started.store(true);
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(150)
                    );
                }
            );
        }

        ASSERT_TRUE(started.load());
    }

    TEST(AsynchronousManagerTest,
        Singleton_PostJoin_PostJoin_CycleWorks)
    {
        QLogicaeCppCore::Result<bool> result;

        auto& mgr = QLogicaeCppCore::ASYNCHRONOUS_MANAGER;

        mgr.begin_one_thread(result, []() {});
        mgr.complete_all_threads(result);

        mgr.begin_one_thread(result, []() {});
        mgr.complete_all_threads(result);

        SUCCEED();
    }

    TEST(AsynchronousManagerTest,
        Should_NotDeadlock_When_PostAndJoinInterleave_Intensely)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager mgr;

        std::atomic<int> counter(0);
        const int iterations = 50;

        std::vector<std::thread> threads;

        for (int i = 0; i < iterations; ++i)
        {
            threads.emplace_back(
                [&mgr, &counter, &result]()
                {
                    mgr.begin_one_thread(
                        result,
                        [&counter]()
                        {
                            counter.fetch_add(1);
                        }
                    );
                }
            );

            threads.emplace_back(
                [&mgr, &result]()
                {
                    mgr.complete_all_threads(
                        result
                    );
                }
            );
        }

        for (auto& t : threads)
        {
            t.join();
        }

        SUCCEED();
    }

    TEST(AsynchronousManagerTest,
        Should_Handle_PostAfterJoin_When_PoolRecreated)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager mgr;

        std::atomic<int> counter(0);

        mgr.begin_one_thread(result, [&counter]() {
            counter.fetch_add(1);
            });

        mgr.complete_all_threads(result);

        mgr.begin_one_thread(result, [&counter]() {
            counter.fetch_add(1);
            });

        mgr.complete_all_threads(result);

        ASSERT_EQ(counter.load(), 2);
    }

    TEST(AsynchronousManagerTest,
        Should_NotLeakPool_When_NoTasksPostedAndJoinCalledRepeatedly)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager mgr;

        for (int i = 0; i < 20; ++i)
        {
            ASSERT_NO_THROW(mgr.complete_all_threads(result));
        }

        SUCCEED();
    }

    TEST(AsynchronousManagerTest,
        Should_Allow_LongRunningTask_And_PostDuringExecution)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager mgr;

        std::atomic<bool> started(false);
        std::atomic<int> counter(0);

        mgr.begin_one_thread(
            result,
            [&started]()
            {
                started.store(true);
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(200)
                );
            }
        );

        bool posted = wait_for_condition_for_ms(
            [&started]() { return started.load(); },
            500
        );

        ASSERT_TRUE(posted);

        mgr.begin_one_thread(
            result,
            [&counter]()
            {
                counter.fetch_add(1);
            }
        );

        mgr.complete_all_threads(
            result
        );

        ASSERT_EQ(counter.load(), 1);
    }

    TEST(AsynchronousManagerTest,
        Should_Handle_MultipleConcurrentJoiners)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager mgr;

        std::atomic<int> counter(0);

        for (int i = 0; i < 20; ++i)
        {
            mgr.begin_one_thread(
                result,
                [&counter]() { counter.fetch_add(1); }
            );
        }

        std::vector<std::thread> joiners;

        for (int j = 0; j < 10; ++j)
        {
            joiners.emplace_back(
                [&mgr, &result]()
                {
                    mgr.complete_all_threads(
                        result
                    );
                }
            );
        }

        for (auto& t : joiners)
        {
            t.join();
        }

        ASSERT_EQ(counter.load(), 20);
    }

    TEST(AsynchronousManagerTest,
        Should_CompleteAllTasks_When_PostsHappenDuringJoinPhase)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::AsynchronousManager mgr;

        std::atomic<int> counter(0);

        std::thread joiner(
            [&mgr, &result]()
            {
                mgr.complete_all_threads(
                    result
                );
            }
        );

        std::thread poster(
            [&mgr, &counter, &result]()
            {
                for (int i = 0; i < 50; ++i)
                {
                    mgr.begin_one_thread(
                        result,
                        [&counter]()
                        {
                            counter.fetch_add(1);
                        }
                    );
                }
            }
        );

        joiner.join();
        poster.join();

        
        mgr.complete_all_threads(
            result
        );

        ASSERT_EQ(counter.load(), 50);
    }

}
/*
"東京"
*/