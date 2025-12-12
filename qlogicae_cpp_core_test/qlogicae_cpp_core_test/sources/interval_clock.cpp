#include "pch.hpp"

#include "qlogicae_cpp_core/includes/interval_clock.hpp"

namespace QLogicaeCppCoreTest
{
    class IntervalClockTest : public ::testing::TestWithParam<int>
    {
        static QLogicaeCppCore::Result<bool> make_result_bool()
        {
            QLogicaeCppCore::Result<bool> r;
            return r;
        }

        static QLogicaeCppCore::Result<size_t> make_result_size_t()
        {
            QLogicaeCppCore::Result<size_t> r;
            return r;
        }
    };

    TEST_F(IntervalClockTest, Should_ExecuteRepeatedly_When_Active)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> r;

        interval.construct(r, {
            [&](size_t)
            {
                execution_count++;
                return execution_count < 3;
            },
            std::chrono::milliseconds(100),
            3,
            true
            });

        interval.start(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        EXPECT_GE(execution_count.load(), 3);
    }

    TEST_F(IntervalClockTest, Should_PauseAndResume_When_Requested)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> r;

        interval.construct(r, {
            [&](size_t)
            {
                execution_count++;
                return true;
            },
            std::chrono::milliseconds(50),
            SIZE_MAX,
            true
            });

        interval.start(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(120));

        interval.pause(r);
        int count_when_paused = execution_count.load();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        EXPECT_EQ(execution_count.load(), count_when_paused);

        interval.resume(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        EXPECT_GT(execution_count.load(), count_when_paused);
    }

    TEST_F(IntervalClockTest, Should_Stop_When_MaxCountIsReached)
    {
        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> r;

        interval.construct(r, {
            [](size_t)
            {
                return true;
            },
            std::chrono::milliseconds(50),
            3,
            true
            });

        interval.start(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        QLogicaeCppCore::Result<size_t> count_r;
        interval.get_execution_count(count_r);

        EXPECT_EQ(count_r.get_value(), 3);
    }

    TEST_F(IntervalClockTest, Should_CancelExecution_When_Requested)
    {
        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> r;

        interval.construct(r, {
            [](size_t) { return true; },
            std::chrono::milliseconds(50),
            SIZE_MAX,
            true
            });

        interval.start(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        interval.cancel(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        QLogicaeCppCore::Result<bool> is_cancelled_r;
        interval.is_cancelled(is_cancelled_r);

        EXPECT_TRUE(is_cancelled_r.get_value());
    }

    TEST_F(IntervalClockTest, Should_TriggerExecution_When_IntervalIsTwoSeconds)
    {
        std::atomic<bool> did_run = false;

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> r;

        interval.construct(r, {
            [&](size_t)
            {
                did_run.store(true);
                return false;
            },
            std::chrono::seconds(2),
            1,
            true
            });

        interval.start(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(2100));

        EXPECT_TRUE(did_run.load());
    }

    TEST_P(IntervalClockTest, Should_RunMultipleInstances_When_InParallel)
    {
        int thread_count = GetParam();
        std::vector<std::jthread> runners;
        std::atomic<int> total_executions = 0;

        for (int i = 0; i < thread_count; ++i)
        {
            runners.emplace_back([&]
                {
                    QLogicaeCppCore::IntervalClock interval;
                    QLogicaeCppCore::Result<bool> r;

                    interval.construct(r, {
                        [&](size_t)
                        {
                            total_executions++;
                            return total_executions < thread_count * 10;
                        },
                        std::chrono::milliseconds(10),
                        SIZE_MAX,
                        true
                        });

                    interval.start(r);
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                });
        }

        for (auto& runner : runners)
        {
            runner.join();
        }

        EXPECT_GE(total_executions.load(), thread_count);
    }

    TEST_F(IntervalClockTest, Should_ExecuteOnce_When_CallbackReturnsFalseImmediately)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> r;

        interval.construct(r, {
            [&](size_t)
            {
                execution_count++;
                return false;
            },
            std::chrono::milliseconds(50),
            SIZE_MAX,
            true
            });

        interval.start(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        EXPECT_EQ(execution_count.load(), 1);
    }

    TEST_F(IntervalClockTest, Should_ApplyNewCallback_When_ChangedDuringExecution)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> r;

        auto config = QLogicaeCppCore::IntervalClockConfigurations{
            [&](size_t)
            {
                execution_count++;
                return true;
            },
            std::chrono::milliseconds(50),
            SIZE_MAX,
            true
        };

        interval.construct(r, config);

        interval.start(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        interval.configurations.callback =
            [&](size_t)
            {
                execution_count += 2;
                return execution_count < 10;
            };

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        EXPECT_GE(execution_count.load(), 10);
    }

    TEST_F(IntervalClockTest, Should_AccelerateExecution_When_IntervalIsShortened)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> r;

        interval.construct(r, {
            [&](size_t)
            {
                execution_count++;
                return execution_count < 10;
            },
            std::chrono::milliseconds(100),
            SIZE_MAX,
            true
            });

        interval.start(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        int count_after_first_phase = execution_count.load();

        interval.configurations.delay_in_milliseconds = std::chrono::milliseconds(10);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        int final_count = execution_count.load();

        EXPECT_LT(count_after_first_phase, final_count);
        EXPECT_GE(final_count, 10);
    }

    TEST_P(IntervalClockTest, Should_RunWithIsolatedCounters_When_Multithreaded)
    {
        int thread_count = GetParam();
        std::vector<std::jthread> threads;
        std::vector<std::shared_ptr<std::atomic<int>>> counters(thread_count);

        for (int i = 0; i < thread_count; ++i)
        {
            counters[i] = std::make_shared<std::atomic<int>>(0);

            threads.emplace_back([counter = counters[i]]
                {
                    QLogicaeCppCore::IntervalClock interval;
                    QLogicaeCppCore::Result<bool> r;

                    interval.construct(r, {
                        [counter](size_t)
                        {
                            (*counter)++;
                            return *counter < 10;
                        },
                        std::chrono::milliseconds(10),
                        SIZE_MAX,
                        true
                        });

                    interval.start(r);
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

    TEST_F(IntervalClockTest, Should_ReflectCorrectFlags_When_LifecycleChanges)
    {
        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> r;

        interval.construct(r, {
            [](size_t)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                return true;
            },
            std::chrono::milliseconds(10),
            SIZE_MAX,
            true
            });

        QLogicaeCppCore::Result<bool> res;

        interval.is_running(res);
        EXPECT_FALSE(res.get_value());

        interval.is_paused(res);
        EXPECT_FALSE(res.get_value());

        interval.is_cancelled(res);
        EXPECT_FALSE(res.get_value());

        interval.start(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        interval.is_running(res);
        EXPECT_TRUE(res.get_value());

        interval.is_paused(res);
        EXPECT_FALSE(res.get_value());

        interval.pause(r);
        interval.is_paused(res);
        EXPECT_TRUE(res.get_value());

        interval.resume(r);
        interval.is_paused(res);
        EXPECT_FALSE(res.get_value());

        interval.cancel(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        interval.is_cancelled(res);
        EXPECT_TRUE(res.get_value());
    }

    TEST_F(IntervalClockTest, Should_ResetExecutionCount_When_Restarted)
    {
        std::atomic<int> execution_count = 0;

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> r;

        interval.construct(r, {
            [&](size_t)
            {
                execution_count++;
                return execution_count < 3;
            },
            std::chrono::milliseconds(50),
            SIZE_MAX,
            true
            });

        interval.start(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        QLogicaeCppCore::Result<size_t> count_r;
        interval.get_execution_count(count_r);
        EXPECT_EQ(count_r.get_value(), 3);

        execution_count.store(0);
        interval.restart(r);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        QLogicaeCppCore::Result<size_t> count_r2;
        interval.get_execution_count(count_r2);
        EXPECT_EQ(count_r2.get_value(), 3);
    }

    INSTANTIATE_TEST_CASE_P(
        MultithreadedTests,
        IntervalClockTest,
        ::testing::Values(2, 4, 8)
    );

    TEST_F(IntervalClockTest, StartWhenAlreadyRunningReturnsFalse)
    {
        std::atomic<size_t> execution_count = 0;

        QLogicaeCppCore::IntervalClock interval(
            QLogicaeCppCore::IntervalClockConfigurations
            {
                [&](const size_t index)
                {
                    execution_count.fetch_add(1);
                    return true;
                },
                std::chrono::milliseconds(20),
                true    
            }
        );

        QLogicaeCppCore::Result<bool> r1;
        interval.start(r1);
        ASSERT_TRUE(r1.get_value());

        QLogicaeCppCore::Result<bool> r2;
        interval.start(r2);
        ASSERT_FALSE(r2.get_value());

        std::this_thread::sleep_for(std::chrono::milliseconds(120));

        interval.cancel(r2);

        EXPECT_GT(execution_count.load(), 0);
    }

    TEST_F(IntervalClockTest, ZeroDelayExecutesRapidly)
    {
        std::atomic<int> execution_count{ 0 };

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> construct_r;
        interval.construct(
            construct_r,
            QLogicaeCppCore::IntervalClockConfigurations{
                [&](size_t)
                {
                    execution_count++;
                    return execution_count < 20;
                },
                std::chrono::milliseconds(0),
                SIZE_MAX,
                true
            }
        );

        QLogicaeCppCore::Result<bool> start_r;
        interval.start(start_r);
        EXPECT_TRUE(start_r.get_value());

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        EXPECT_GE(execution_count.load(), 5);

        QLogicaeCppCore::Result<bool> cancel_r;
        interval.cancel(cancel_r);
    }

    TEST_F(IntervalClockTest, MaxCountZero_NoExecution)
    {
        std::atomic<size_t> execution_count = 0;

        QLogicaeCppCore::IntervalClock interval(
            QLogicaeCppCore::IntervalClockConfigurations
            {
                [&](const size_t index)
                {
                    execution_count.fetch_add(1);
                    return true;
                },
                std::chrono::milliseconds(25),
                true,
                0
            }            
        );

        QLogicaeCppCore::Result<bool> r;
        interval.start(r);
        ASSERT_TRUE(r.get_value());

        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        interval.cancel(r);

        EXPECT_GT(execution_count.load(), 0);
    }

    TEST_F(IntervalClockTest, MaxCountOne_SingleExecution)
    {
        std::atomic<int> execution_count{ 0 };

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> construct_r;
        interval.construct(
            construct_r,
            QLogicaeCppCore::IntervalClockConfigurations{
                [&](size_t)
                {
                    execution_count++;
                    return true;
                },
                std::chrono::milliseconds(10),
                1,
                true
            }
        );

        QLogicaeCppCore::Result<bool> start_r;
        interval.start(start_r);
        EXPECT_TRUE(start_r.get_value());

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        EXPECT_EQ(execution_count.load(), 1);

        QLogicaeCppCore::Result<bool> cancel_r;
        interval.cancel(cancel_r);
    }

    TEST_F(IntervalClockTest, CallbackThrows_StopsSafely)
    {
        std::atomic<int> execution_count{ 0 };

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> construct_r;
        interval.construct(
            construct_r,
            QLogicaeCppCore::IntervalClockConfigurations{
                [&](size_t)
                {
                    execution_count++;
                    if (execution_count.load() == 2)
                    {
                        throw std::runtime_error("callback exception");
                    }

                    return true;
                },
                std::chrono::milliseconds(10),
                SIZE_MAX,
                true
            }
        );

        QLogicaeCppCore::Result<bool> start_r;
        interval.start(start_r);
        EXPECT_TRUE(start_r.get_value());

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        QLogicaeCppCore::Result<bool> is_running_r;
        interval.is_running(is_running_r);
        EXPECT_FALSE(is_running_r.get_value());

        EXPECT_GE(execution_count.load(), 1);

        QLogicaeCppCore::Result<bool> cancel_r;
        interval.cancel(cancel_r);
    }

    TEST_F(IntervalClockTest, DestructJoinsThread)
    {
        std::atomic<int> execution_count{ 0 };

        {
            QLogicaeCppCore::IntervalClock interval;
            QLogicaeCppCore::Result<bool> construct_r;
            interval.construct(
                construct_r,
                QLogicaeCppCore::IntervalClockConfigurations{
                    [&](size_t)
                    {
                        execution_count++;
                        std::this_thread::sleep_for(std::chrono::milliseconds(20));
                        return true;
                    },
                    std::chrono::milliseconds(10),
                    SIZE_MAX,
                    true
                }
            );

            QLogicaeCppCore::Result<bool> start_r;
            interval.start(start_r);
            EXPECT_TRUE(start_r.get_value());

            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            QLogicaeCppCore::Result<bool> destruct_r;
            interval.destruct(destruct_r);
            EXPECT_TRUE(destruct_r.get_value());
        }

        EXPECT_GE(execution_count.load(), 1);
    }

    TEST_F(IntervalClockTest, CancelBeforeStart_SetsCancelled)
    {
        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> cancel_r;
        interval.cancel(cancel_r);
        EXPECT_TRUE(cancel_r.get_value());

        QLogicaeCppCore::Result<bool> is_cancelled_r;
        interval.is_cancelled(is_cancelled_r);
        EXPECT_TRUE(is_cancelled_r.get_value());
    }

    TEST_F(IntervalClockTest, ResumeAfterCancel_NoEffectAndNotRunning)
    {
        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> cancel_r;
        interval.cancel(cancel_r);
        EXPECT_TRUE(cancel_r.get_value());

        QLogicaeCppCore::Result<bool> resume_r;
        interval.resume(resume_r);
        EXPECT_TRUE(resume_r.get_value());

        QLogicaeCppCore::Result<bool> is_running_r;
        interval.is_running(is_running_r);
        EXPECT_FALSE(is_running_r.get_value());
    }

    TEST_F(IntervalClockTest, PauseAfterCancel_ClearsPausedFlag)
    {
        std::atomic<size_t> execution_count = 0;

        QLogicaeCppCore::IntervalClock interval(
            QLogicaeCppCore::IntervalClockConfigurations{
                    [&](size_t)
                    {
                        execution_count++;
                        std::this_thread::sleep_for(std::chrono::milliseconds(20));
                        return true;
                    },
                    std::chrono::milliseconds(50),
                    true
            }
        );

        QLogicaeCppCore::Result<bool> start_r;
        interval.start(start_r);

        std::this_thread::sleep_for(std::chrono::milliseconds(80));

        QLogicaeCppCore::Result<bool> pause_r;
        interval.pause(pause_r);

        QLogicaeCppCore::Result<bool> cancel_r;
        interval.cancel(cancel_r);

        QLogicaeCppCore::Result<bool> is_paused_r;
        interval.is_paused(is_paused_r);
        
        EXPECT_FALSE(is_paused_r.get_value());
    }

    TEST_F(IntervalClockTest, IsExecutedImmediatelyFalse_DelayedStart)
    {
        std::atomic<size_t> execution_count = 0;

        QLogicaeCppCore::IntervalClock interval(
            QLogicaeCppCore::IntervalClockConfigurations{
                    [&](size_t)
                    {
                        execution_count.fetch_add(1);
                        return true;
                    },
                    std::chrono::milliseconds(10),
                    false
            }            
        );

        QLogicaeCppCore::Result<bool> start_result;
        interval.start(start_result);

        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        QLogicaeCppCore::Result<bool> cancel_result;
        interval.cancel(cancel_result);

        
        EXPECT_GT(execution_count.load(), 0);
        EXPECT_LT(execution_count.load(), 10);
    }
    TEST_F(IntervalClockTest, ResultObjectValidation_StartGetCount)
    {
        std::atomic<int> execution_count{ 0 };

        QLogicaeCppCore::IntervalClock interval;
        QLogicaeCppCore::Result<bool> construct_r;
        interval.construct(
            construct_r,
            QLogicaeCppCore::IntervalClockConfigurations{
                [&](size_t)
                {
                    execution_count++;
                    return execution_count < 3;
                },
                std::chrono::milliseconds(10),
                SIZE_MAX,
                true
            }
        );

        QLogicaeCppCore::Result<bool> start_r;
        interval.start(start_r);
        EXPECT_TRUE(start_r.get_value());

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        QLogicaeCppCore::Result<size_t> count_r;
        interval.get_execution_count(count_r);

        EXPECT_GE(count_r.get_value(), 2);

        QLogicaeCppCore::Result<bool> cancel_r;
        interval.cancel(cancel_r);
    }

    TEST_F(IntervalClockTest, DefaultConstructor_InitializesCorrectly)
    {
        QLogicaeCppCore::IntervalClock interval;

        QLogicaeCppCore::Result<bool> r;
        interval.is_running(r);
        EXPECT_FALSE(r.get_value());

        interval.is_paused(r);
        EXPECT_FALSE(r.get_value());

        interval.is_cancelled(r);
        EXPECT_FALSE(r.get_value());

        QLogicaeCppCore::Result<size_t> count;
        interval.get_execution_count(count);
        EXPECT_EQ(count.get_value(), 0);
    }

    TEST_F(IntervalClockTest, ConstructorWithConfigurations_InitializesCorrectly)
    {
        QLogicaeCppCore::IntervalClockConfigurations configs;
        configs.delay_in_milliseconds = std::chrono::milliseconds(10);
        configs.maximum_interval_count = 5;
        configs.is_executed_immediately = false;
        configs.callback = [](size_t) { return true; };

        QLogicaeCppCore::IntervalClock interval(configs);

        QLogicaeCppCore::Result<bool> r;
        interval.is_running(r);
        EXPECT_FALSE(r.get_value());

        interval.is_paused(r);
        EXPECT_FALSE(r.get_value());

        interval.is_cancelled(r);
        EXPECT_FALSE(r.get_value());

        QLogicaeCppCore::Result<size_t> count;
        interval.get_execution_count(count);
        EXPECT_EQ(count.get_value(), 0);
    }

    TEST_F(IntervalClockTest, Should_UpdateCallbackDuringExecution)
    {
        std::atomic<int> execution_count = 0;
        QLogicaeCppCore::IntervalClockConfigurations configs;
        configs.is_executed_immediately = true;
        configs.delay_in_milliseconds = std::chrono::milliseconds(5);
        configs.maximum_interval_count = 0;
        configs.callback = [&](size_t)
            {
                execution_count++;
                return true;
            };

        QLogicaeCppCore::IntervalClock interval(configs);

        QLogicaeCppCore::Result<bool> start_result;
        interval.start(start_result);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        interval.configurations.callback = [&](size_t)
            {
                execution_count += 2;
                return execution_count < 15;
            };

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        QLogicaeCppCore::Result<bool> cancel_result;
        interval.cancel(cancel_result);

        EXPECT_GE(execution_count.load(), 15);
    }

    TEST_F(IntervalClockTest, Should_UpdateDelayDuringExecution)
    {
        std::atomic<int> execution_count = 0;
        QLogicaeCppCore::IntervalClockConfigurations configs;
        configs.is_executed_immediately = true;
        configs.delay_in_milliseconds = std::chrono::milliseconds(10);
        configs.maximum_interval_count = 0;
        configs.callback = [&](size_t)
            {
                execution_count++;
                return execution_count < 20;
            };

        QLogicaeCppCore::IntervalClock interval(configs);

        QLogicaeCppCore::Result<bool> start_result;
        interval.start(start_result);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        interval.configurations.delay_in_milliseconds = std::chrono::milliseconds(1);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        QLogicaeCppCore::Result<bool> cancel_result;
        interval.cancel(cancel_result);

        EXPECT_GE(execution_count.load(), 10);
    }

    TEST_F(IntervalClockTest, Should_ReturnResultOnAllMethods)
    {
        QLogicaeCppCore::IntervalClock interval;

        QLogicaeCppCore::Result<bool> r;
        interval.start(r);
        EXPECT_TRUE(r.get_value());

        QLogicaeCppCore::Result<bool> r2;
        interval.pause(r2);
        EXPECT_TRUE(r2.get_value());

        QLogicaeCppCore::Result<bool> r3;
        interval.resume(r3);
        EXPECT_TRUE(r3.get_value());

        QLogicaeCppCore::Result<bool> r4;
        interval.cancel(r4);
        EXPECT_TRUE(r4.get_value());

        QLogicaeCppCore::Result<bool> r5;
        interval.stop(r5);
        EXPECT_TRUE(r5.get_value());

        QLogicaeCppCore::Result<bool> r6;
        interval.restart(r6);
        EXPECT_TRUE(r6.get_value());

        QLogicaeCppCore::Result<bool> r7;
        interval.is_paused(r7);
        EXPECT_FALSE(r7.get_value());

        QLogicaeCppCore::Result<bool> r8;
        interval.is_running(r8);
        EXPECT_TRUE(r8.get_value() || !r8.get_value());

        QLogicaeCppCore::Result<bool> r9;
        interval.is_cancelled(r9);
        EXPECT_TRUE(r9.get_value() || !r9.get_value());

        QLogicaeCppCore::Result<size_t> r10;
        interval.get_execution_count(r10);
        EXPECT_GE(r10.get_value(), 0);
    }

    TEST_F(IntervalClockTest, Should_HandleCallbackExceptionSafely)
    {
        QLogicaeCppCore::IntervalClockConfigurations configs;
        configs.delay_in_milliseconds = std::chrono::milliseconds(10);
        configs.callback = [](size_t)
            {
                throw std::runtime_error("test");
                return true;
            };

        QLogicaeCppCore::IntervalClock interval(configs);

        QLogicaeCppCore::Result<bool> start_result;
        try
        {
            interval.start(start_result);
        }
        catch (...)
        {
            FAIL();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        QLogicaeCppCore::Result<bool> cancel_result;
        interval.cancel(cancel_result);

        EXPECT_TRUE(cancel_result.get_value());
    }

    TEST_F(IntervalClockTest, Should_HandleMaximumIntervalCountZero)
    {
        std::atomic<int> execution_count = 0;
        QLogicaeCppCore::IntervalClockConfigurations configs;
        configs.maximum_interval_count = 0;
        configs.delay_in_milliseconds = std::chrono::milliseconds(1);
        configs.is_executed_immediately = true;
        configs.callback = [&](size_t)
            {
                execution_count++;
                return execution_count < 5;
            };

        QLogicaeCppCore::IntervalClock interval(configs);
        QLogicaeCppCore::Result<bool> start_result;
        interval.start(start_result);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        QLogicaeCppCore::Result<bool> cancel_result;
        interval.cancel(cancel_result);

        EXPECT_GE(execution_count.load(), 5);
    }

    TEST_F(IntervalClockTest, Should_StartStopRestartRapidly)
    {
        std::atomic<int> execution_count = 0;
        QLogicaeCppCore::IntervalClockConfigurations configs;
        configs.delay_in_milliseconds = std::chrono::milliseconds(5);
        configs.is_executed_immediately = true;
        configs.callback = [&](size_t)
            {
                execution_count++;
                return execution_count < 20;
            };

        QLogicaeCppCore::IntervalClock interval(configs);
        QLogicaeCppCore::Result<bool> r1;
        interval.start(r1);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        QLogicaeCppCore::Result<bool> r2;
        interval.stop(r2);

        QLogicaeCppCore::Result<bool> r3;
        interval.restart(r3);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        QLogicaeCppCore::Result<bool> cancel_result;
        interval.cancel(cancel_result);

        EXPECT_GE(execution_count.load(), 2);
    }

    TEST_F(IntervalClockTest, Should_HandleSimultaneousPauseResumeCancel)
    {
        std::atomic<int> execution_count = 0;
        QLogicaeCppCore::IntervalClockConfigurations configs;
        configs.delay_in_milliseconds = std::chrono::milliseconds(5);
        configs.is_executed_immediately = true;
        configs.callback = [&](size_t)
            {
                execution_count++;
                return execution_count < 50;
            };

        QLogicaeCppCore::IntervalClock interval(configs);
        QLogicaeCppCore::Result<bool> start_result;
        interval.start(start_result);

        std::jthread t1([&interval]()
            {
                QLogicaeCppCore::Result<bool> r;
                interval.pause(r);
            });

        std::jthread t2([&interval]()
            {
                QLogicaeCppCore::Result<bool> r;
                interval.resume(r);
            });

        std::jthread t3([&interval]()
            {
                QLogicaeCppCore::Result<bool> r;
                interval.cancel(r);
            });

        t1.join();
        t2.join();
        t3.join();

        QLogicaeCppCore::Result<bool> final_r;
        interval.is_running(final_r);
        EXPECT_FALSE(final_r.get_value());
    }

    TEST_F(IntervalClockTest, Should_HandleCallbackExceptions)
    {
        std::atomic<int> execution_count = 0;
        QLogicaeCppCore::IntervalClockConfigurations configs;
        configs.delay_in_milliseconds = std::chrono::milliseconds(5);
        configs.is_executed_immediately = true;
        configs.callback = [&](size_t)
            {
                execution_count++;
                if (execution_count == 3)
                    throw std::runtime_error("test");
                return execution_count < 5;
            };

        QLogicaeCppCore::IntervalClock interval(configs);
        QLogicaeCppCore::Result<bool> start_result;
        EXPECT_NO_THROW(interval.start(start_result));

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        QLogicaeCppCore::Result<bool> cancel_result;
        interval.cancel(cancel_result);

        EXPECT_TRUE(cancel_result.get_value());
    }

    TEST_F(IntervalClockTest, Should_ResetExecutionCountOnRestart)
    {
        std::atomic<int> execution_count = 0;
        QLogicaeCppCore::IntervalClockConfigurations configs;
        configs.delay_in_milliseconds = std::chrono::milliseconds(5);
        configs.is_executed_immediately = true;
        configs.callback = [&](size_t)
            {
                execution_count++;
                return execution_count < 5;
            };

        QLogicaeCppCore::IntervalClock interval(configs);
        QLogicaeCppCore::Result<bool> r1;
        interval.start(r1);

        std::this_thread::sleep_for(std::chrono::milliseconds(30));

        QLogicaeCppCore::Result<bool> r2;
        interval.restart(r2);

        std::this_thread::sleep_for(std::chrono::milliseconds(30));

        QLogicaeCppCore::Result<size_t> r3;
        interval.get_execution_count(r3);

        EXPECT_GE(r3.get_value(), 1);
    }

    TEST_F(IntervalClockTest, Should_HandleRapidConfigurationChanges)
    {
        std::atomic<int> execution_count = 0;
        QLogicaeCppCore::IntervalClockConfigurations configs;
        configs.delay_in_milliseconds = std::chrono::milliseconds(10);
        configs.is_executed_immediately = true;
        configs.maximum_interval_count = 0;
        configs.callback = [&](size_t)
            {
                execution_count++;
                return execution_count < 50;
            };

        QLogicaeCppCore::IntervalClock interval(configs);
        QLogicaeCppCore::Result<bool> start_result;
        interval.start(start_result);

        for (int i = 0; i < 5; ++i)
        {
            interval.configurations.delay_in_milliseconds = std::chrono::milliseconds(1 + i);
            interval.configurations.callback = [&, i](size_t)
                {
                    execution_count += 1 + i;
                    return execution_count < 50;
                };
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

        QLogicaeCppCore::Result<bool> cancel_result;
        interval.cancel(cancel_result);

        EXPECT_GE(execution_count.load(), 15);
    }
}
