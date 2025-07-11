#pragma once

#include "pch.h"

#include "globals.hpp"
#include "thread_pool.hpp"

namespace QLogicaeCoreTest
{
    class ThreadPoolTest : public ::testing::TestWithParam<int>
    {
    protected:
        QLogicaeCore::ThreadPool thread_pool{ 4, 64 };

        void SetUp() override {}
        void TearDown() override {}
    };

    class ThreadPoolPriorityTest : public ::testing::Test
    {
    protected:
        void SetUp() override {}

        void TearDown() override {}
    };
    class ThreadPoolAsyncTest : public ::testing::Test
    {
    protected:
        void SetUp() override {}

        void TearDown() override {}
    };

    class ThreadPoolStressTest : public ::testing::Test
    {
    protected:
        void SetUp() override {}

        void TearDown() override {}
    };

    class ThreadPoolLimitTest : public ::testing::Test
    {
    protected:
        void SetUp() override {}

        void TearDown() override {}
    };

    class ThreadPoolBlockingTest : public ::testing::Test
    {
    protected:
        void SetUp() override {}

        void TearDown() override {}
    };

    TEST_P(ThreadPoolTest, Should_Execute_Task_When_Enqueued)
    {
        QLogicaeCore::ThreadPool thread_pool(GetParam());

        std::promise<void> signal;
        std::future<void> wait = signal.get_future();

        bool enqueued = thread_pool.enqueue([&signal]()
            {
                signal.set_value();
            });

        ASSERT_TRUE(enqueued);
        EXPECT_EQ(wait.wait_for(std::chrono::seconds(1)),
            std::future_status::ready);
    }

    TEST_P(ThreadPoolTest, Should_Return_Future_When_Task_Enqueued)
    {
        QLogicaeCore::ThreadPool thread_pool(GetParam());

        std::optional<std::future<void>> result =
            thread_pool.enqueue_task([]() {});

        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result->wait_for(std::chrono::seconds(1)),
            std::future_status::ready);
    }

    TEST_P(ThreadPoolTest, Should_Not_Enqueue_After_Shutdown)
    {
        QLogicaeCore::ThreadPool* pool = new QLogicaeCore::ThreadPool(GetParam());
        delete pool;

        std::optional<std::future<void>> result =
            pool->enqueue_task([]() {});

        ASSERT_FALSE(result.has_value());
    }

    TEST_P(ThreadPoolTest, Should_Execute_Thousands_Of_Tasks_Concurrently)
    {
        const int task_count = 5000;
        QLogicaeCore::ThreadPool thread_pool(GetParam(), task_count + 100);

        std::atomic<int> counter = 0;

        for (int i = 0; i < task_count; ++i)
        {
            ASSERT_TRUE(thread_pool.enqueue([&counter]()
                {
                    counter.fetch_add(1, std::memory_order_relaxed);
                }));
        }

        while (counter.load() < task_count)
        {
            std::this_thread::yield();
        }

        ASSERT_EQ(counter.load(), task_count);
    }

    TEST_P(ThreadPoolTest, Should_Handle_Exceptions_In_Enqueued_Tasks)
    {
        QLogicaeCore::ThreadPool thread_pool(GetParam());

        std::optional<std::future<void>> result =
            thread_pool.enqueue_task([]()
                {
                    throw std::runtime_error("failure");
                });

        ASSERT_TRUE(result.has_value());
        EXPECT_THROW(result->get(), std::runtime_error);
    }

    TEST_P(ThreadPoolTest, Should_Handle_Empty_Enqueue_Correctly)
    {
        QLogicaeCore::ThreadPool thread_pool(GetParam());

        bool enqueued = thread_pool.enqueue([]() {});

        ASSERT_TRUE(enqueued);
    }

    TEST_P(ThreadPoolTest, Should_Report_Worker_Count)
    {
        QLogicaeCore::ThreadPool thread_pool(GetParam());
        EXPECT_EQ(thread_pool.worker_count(), GetParam());
    }

    TEST_P(ThreadPoolTest, Should_Report_Total_Pending_Tasks)
    {
        QLogicaeCore::ThreadPool thread_pool(GetParam());

        for (int i = 0; i < 100; ++i)
        {
            ASSERT_TRUE(thread_pool.enqueue([]()
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }));
        }

        EXPECT_GT(thread_pool.total_pending_tasks(), 0);
    }

    INSTANTIATE_TEST_CASE_P(
        AllWorkerCounts,
        ThreadPoolTest,
        ::testing::Values(1, 2, 4, 8)
    );

    TEST_F(ThreadPoolPriorityTest, Should_Execute_High_Priority_Before_Low)
    {
        std::vector<int> execution_order;
        std::mutex result_mutex;

        QLogicaeCore::ThreadPool thread_pool(1, 10);

        thread_pool.enqueue([&]()
            {
                std::lock_guard<std::mutex> lock(result_mutex);
                execution_order.push_back(2);
            }, QLogicaeCore::TaskPriority::Low);

        thread_pool.enqueue([&]()
            {
                std::lock_guard<std::mutex> lock(result_mutex);
                execution_order.push_back(1);
            }, QLogicaeCore::TaskPriority::High);

        while (execution_order.size() < 2)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        EXPECT_EQ(execution_order[0], 1);
        EXPECT_EQ(execution_order[1], 2);
    }

    TEST_F(ThreadPoolPriorityTest, Should_Drop_Task_When_Queue_Is_Full)
    {
        QLogicaeCore::ThreadPool thread_pool(1, 5);

        std::atomic<int> executed_count{ 0 };

        for (int i = 0; i < 5; ++i)
        {
            bool accepted = thread_pool.enqueue([&]()
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    executed_count.fetch_add(1);
                });

            EXPECT_TRUE(accepted);
        }

        bool overflow_result = thread_pool.enqueue([]() {});
        EXPECT_FALSE(overflow_result);
    }

    TEST_F(ThreadPoolPriorityTest, Should_Accept_After_Queue_Has_Space)
    {
        QLogicaeCore::ThreadPool thread_pool(1, 3);

        std::atomic<int> counter{ 0 };

        for (int i = 0; i < 3; ++i)
        {
            thread_pool.enqueue([&]()
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    counter.fetch_add(1);
                });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        bool accepted = thread_pool.enqueue([&]() { counter.fetch_add(1); });

        EXPECT_TRUE(accepted);
    }

    TEST_F(ThreadPoolAsyncTest, Should_Execute_Async_Task_And_Return_Result)
    {
        QLogicaeCore::ThreadPool thread_pool(2);

        std::promise<int> result_promise;
        std::future<int> result_future = result_promise.get_future();

        auto future = thread_pool.enqueue_task([&]()
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                result_promise.set_value(42);
            });

        ASSERT_TRUE(future.has_value());
        future.value().get();
        EXPECT_EQ(result_future.get(), 42);
    }

    TEST_F(ThreadPoolAsyncTest, Should_Propagate_Exception_From_Async_Task)
    {
        QLogicaeCore::ThreadPool thread_pool(1);

        auto future = thread_pool.enqueue_task([]()
            {
                throw std::runtime_error("failure");
            });

        ASSERT_TRUE(future.has_value());
        EXPECT_THROW(future.value().get(), std::runtime_error);
    }

    TEST_F(ThreadPoolAsyncTest, Should_Report_Correct_Pending_Task_Count)
    {
        QLogicaeCore::ThreadPool thread_pool(1, 10);

        std::atomic<int> processed_count{ 0 };

        for (int i = 0; i < 5; ++i)
        {
            bool accepted = thread_pool.enqueue([&processed_count]()
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    processed_count.fetch_add(1);
                });

            EXPECT_TRUE(accepted);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        std::size_t pending = thread_pool.total_pending_tasks();

        EXPECT_GT(pending, 0);
        EXPECT_LE(pending, 5);
    }

    TEST_F(ThreadPoolStressTest, Should_Complete_All_Tasks_Under_Stress_Quickly)
    {
        constexpr std::size_t task_count = 10000;
        QLogicaeCore::ThreadPool thread_pool(8, task_count);

        std::atomic<int> completed{ 0 };
        auto start = std::chrono::steady_clock::now();

        for (std::size_t i = 0; i < task_count; ++i)
        {
            thread_pool.enqueue([&]()
                {
                    completed.fetch_add(1);
                });
        }

        while (completed.load() < task_count)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start);

        EXPECT_EQ(completed.load(), task_count);
        EXPECT_LE(duration.count(), 2000); 
    }

    TEST_F(ThreadPoolPriorityTest, Should_Distribute_Load_Fairly_Across_Threads)
    {
        constexpr std::size_t thread_count = 4;
        constexpr std::size_t task_count = 400;

        QLogicaeCore::ThreadPool thread_pool(thread_count, task_count);

        std::vector<std::atomic<int>> hit_counts(thread_count);
        for (auto& count : hit_counts)
        {
            count.store(0);
        }

        std::atomic<int> completed{ 0 };
        std::mutex wait_mutex;
        std::condition_variable wait_condition;

        for (std::size_t i = 0; i < task_count; ++i)
        {
            thread_pool.enqueue([&]()
                {
                    std::size_t index = QLogicaeCore::ThreadPool::current_worker_index();
                    if (index < thread_count)
                    {
                        hit_counts[index]++;
                    }

                    if (++completed == task_count)
                    {
                        wait_condition.notify_one();
                    }
                });
        }

        std::unique_lock<std::mutex> lock(wait_mutex);
        wait_condition.wait_for(lock, std::chrono::seconds(2),
            [&]() { return completed == task_count; });

        int total = 0;
        for (std::size_t i = 0; i < thread_count; ++i)
        {
            int hits = hit_counts[i].load();
            EXPECT_GT(hits, 0) << "Worker " << i << " did no work";
            total += hits;
        }

        EXPECT_EQ(total, static_cast<int>(task_count));
    }

    TEST_F(ThreadPoolLimitTest, Should_Reject_Enqueue_When_Queue_Is_Full)
    {
        const std::size_t max_queue_size = 8;
        QLogicaeCore::ThreadPool thread_pool(1, max_queue_size);

        std::atomic<int> counter{ 0 };
        for (std::size_t i = 0; i < max_queue_size; ++i)
        {
            bool accepted = thread_pool.enqueue([&]()
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    counter++;
                });
            EXPECT_TRUE(accepted);
        }

        bool overflow_rejected = !thread_pool.enqueue([]() {});
        EXPECT_TRUE(overflow_rejected);
    }

    TEST_F(ThreadPoolLimitTest, Should_Recover_After_Idle_And_Process_New_Tasks)
    {
        QLogicaeCore::ThreadPool thread_pool(2, 64);
        std::atomic<int> first_wave{ 0 };
        std::atomic<int> second_wave{ 0 };

        for (int i = 0; i < 10; ++i)
        {
            thread_pool.enqueue([&]()
                {
                    first_wave.fetch_add(1);
                });
        }

        while (first_wave.load() < 10)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        for (int i = 0; i < 10; ++i)
        {
            thread_pool.enqueue([&]()
                {
                    second_wave.fetch_add(1);
                });
        }

        while (second_wave.load() < 10)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        EXPECT_EQ(first_wave.load(), 10);
        EXPECT_EQ(second_wave.load(), 10);
    }

    TEST_F(ThreadPoolPriorityTest, Should_Respect_Strict_Priority_Order)
    {
        QLogicaeCore::ThreadPool thread_pool(1, 64);

        std::vector<int> execution_order;
        std::mutex order_mutex;

        thread_pool.enqueue([&]() {
            std::lock_guard<std::mutex> lock(order_mutex);
            execution_order.push_back(1);
            }, QLogicaeCore::TaskPriority::Low);

        thread_pool.enqueue([&]() {
            std::lock_guard<std::mutex> lock(order_mutex);
            execution_order.push_back(2);
            }, QLogicaeCore::TaskPriority::Normal);

        thread_pool.enqueue([&]() {
            std::lock_guard<std::mutex> lock(order_mutex);
            execution_order.push_back(3);
            }, QLogicaeCore::TaskPriority::High);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        ASSERT_EQ(execution_order.size(), 3);
        EXPECT_EQ(execution_order[0], 3);
        EXPECT_EQ(execution_order[1], 2);
        EXPECT_EQ(execution_order[2], 1);
    }

    TEST_F(ThreadPoolPriorityTest, Should_Propagate_Exceptions_From_Enqueued_Tasks)
    {
        QLogicaeCore::ThreadPool thread_pool(1, 16);

        auto future = thread_pool.enqueue_task([]() {
            throw std::runtime_error("Intentional failure");
            });

        ASSERT_TRUE(future.has_value());

        EXPECT_THROW({
            future->get();
            }, std::runtime_error);
    }

    TEST_F(ThreadPoolBlockingTest, Should_Defer_Low_Priority_When_High_Priority_Queued)
    {
        QLogicaeCore::ThreadPool thread_pool(1, 64);

        std::vector<int> order;
        std::mutex order_mutex;

        thread_pool.enqueue([&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::lock_guard<std::mutex> lock(order_mutex);
            order.push_back(1);
            }, QLogicaeCore::TaskPriority::High);

        thread_pool.enqueue([&]() {
            std::lock_guard<std::mutex> lock(order_mutex);
            order.push_back(2);
            }, QLogicaeCore::TaskPriority::Low);

        thread_pool.enqueue([&]() {
            std::lock_guard<std::mutex> lock(order_mutex);
            order.push_back(3);
            }, QLogicaeCore::TaskPriority::High);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        ASSERT_EQ(order.size(), 3);
        EXPECT_EQ(order[0], 1);
        EXPECT_EQ(order[1], 3);
        EXPECT_EQ(order[2], 2);
    }

    TEST_F(ThreadPoolBlockingTest, Should_Block_Get_Until_Long_Task_Completes)
    {
        QLogicaeCore::ThreadPool thread_pool(1, 8);

        auto future = thread_pool.enqueue_task([]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            });

        ASSERT_TRUE(future.has_value());

        auto start_time = std::chrono::steady_clock::now();
        future->get();
        auto end_time = std::chrono::steady_clock::now();

        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time).count();

        EXPECT_GE(elapsed_ms, 150);
    }


    TEST_F(ThreadPoolTest, Should_Report_Pending_Tasks_When_Loaded)
    {
        std::atomic<std::size_t> counter = 0;

        for (int i = 0; i < 32; ++i)
        {
            thread_pool.enqueue([&counter]()
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    ++counter;
                });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        std::size_t pending = thread_pool.total_pending_tasks();
        EXPECT_GT(pending, 0);
    }

    TEST_F(ThreadPoolTest, Should_Invoke_All_Task_Types_Successfully)
    {
        std::atomic<int> result_lambda = 0;
        std::atomic<int> result_bind = 0;
        std::atomic<int> result_callable = 0;

        struct CallableObject
        {
            std::atomic<int>* counter;

            void operator()()
            {
                ++(*counter);
            }
        };

        auto bound_function = std::bind([](std::atomic<int>* counter)
            {
                ++(*counter);
            }, &result_bind);

        thread_pool.enqueue([&result_lambda]()
            {
                ++result_lambda;
            });

        thread_pool.enqueue(bound_function);

        thread_pool.enqueue(CallableObject{ &result_callable });

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        EXPECT_EQ(result_lambda.load(), 1);
        EXPECT_EQ(result_bind.load(), 1);
        EXPECT_EQ(result_callable.load(), 1);
    }

    TEST(ThreadPoolSingletonTest, Should_Return_Same_Instance)
    {
        QLogicaeCore::ThreadPool& pool1 =
            QLogicaeCore::ThreadPool::get_instance();

        QLogicaeCore::ThreadPool& pool2 =
            QLogicaeCore::ThreadPool::get_instance();

        EXPECT_EQ(&pool1, &pool2);

        std::atomic<int> counter{ 0 };

        for (int i = 0; i < 10; ++i)
        {
            bool ok = pool1.enqueue([&]()
                {
                    counter.fetch_add(1);
                });

            EXPECT_TRUE(ok);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_EQ(counter.load(), 10);
    }
}
