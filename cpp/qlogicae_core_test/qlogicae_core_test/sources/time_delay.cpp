#include "pch.hpp"

#include "qlogicae_core/includes/time_delay.hpp"

using namespace QLogicaeCore;

namespace QLogicaeCoreTest
{
    class TimeDelayTest
        : public ::testing::TestWithParam<double>
    {
    protected:
        TimeDelay& time_delay = TIME_DELAY;
    };

    INSTANTIATE_TEST_CASE_P(
        TimeDelayParameterTests,
        TimeDelayTest,
        ::testing::Values(
            0.0,
            0.000001,
            1.0,
            1000.0,
            1'000'000.0
        )
    );

    TEST_P(TimeDelayTest, Should_Expect_SynchronousBehavior_When_Invoked)
    {
        double duration = GetParam();
        Result<void> result;

        auto start = std::chrono::high_resolution_clock::now();
        time_delay.in_microseconds(result, duration);
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed =
            std::chrono::duration<double, std::micro>(end - start).count();

        EXPECT_GE(elapsed, duration * 0.9);
    }

    TEST_P(TimeDelayTest, Should_Expect_AsynchronousCompletion_When_CalledAsync)
    {
        double duration = GetParam();

        auto future = time_delay.in_microseconds_async(duration);
        auto status = future.wait_for(std::chrono::seconds(2));

        EXPECT_NE(status, std::future_status::timeout);
    }

    TEST_P(TimeDelayTest, Should_Expect_CallbackExecution_When_AsyncCalled)
    {
        double duration = GetParam();
        std::atomic<bool> callback_called = false;
        std::mutex mutex;
        std::condition_variable cv;

        time_delay.in_microseconds_async(
            [&](const bool& result)
            {
                std::unique_lock<std::mutex> lock(mutex);
                callback_called = true;
                cv.notify_one();
            },
            duration
        );

        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(lock, std::chrono::seconds(2),
            [&]() { return callback_called.load(); });

        EXPECT_TRUE(callback_called);
    }

    TEST_P(TimeDelayTest, Should_Expect_MultithreadedSafety_When_ParallelInvoked)
    {
        double duration = GetParam();
        std::atomic<int> completed = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back(
                [&]()
                {
                    Result<void> result;
                    time_delay.in_microseconds(result, duration);
                    completed.fetch_add(1);
                }
            );
        }

        for (auto& thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }

        EXPECT_EQ(completed.load(), 10);
    }

    TEST_P(TimeDelayTest, Should_Expect_NoExceptions_When_Handled)
    {
        double duration = GetParam();

        EXPECT_NO_THROW(
            {
                Result<void> result;
                time_delay.in_microseconds(result, duration);
            }
        );
    }

    TEST_F(TimeDelayTest, Should_Expect_ValidCalibration_When_Called)
    {
        Result<void> result;
        time_delay.calibrate(result);
        EXPECT_TRUE(result.is_status_safe());
    }

    TEST_F(TimeDelayTest, Should_Expect_QPCBehavior_When_Called)
    {
        Result<void> result;
        time_delay.query_performance_counter(result, 100.0);
        EXPECT_TRUE(result.is_status_safe());
    }

    TEST_F(TimeDelayTest, Should_Expect_RDTSCBehavior_When_Called)
    {
        Result<void> result;
        time_delay.real_time_stamp_counter(result, 100.0);
        EXPECT_TRUE(result.is_status_safe());
    }

    TEST_F(TimeDelayTest, Should_Expect_PerformanceCompletion_When_HeavyLoad)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000; ++i)
        {
            Result<void> result;
            TIME_DELAY.in_microseconds(result, 50.0);
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed =
            std::chrono::duration<double>(end - start).count();

        EXPECT_LE(elapsed, 2.0);
    }

    TEST_F(TimeDelayTest, Should_Expect_SafeHandling_When_InvalidValues)
    {
        Result<void> result;
        EXPECT_NO_THROW(time_delay.in_microseconds(result, -1.0));
        EXPECT_NO_THROW(time_delay.in_microseconds(result, 0.0));
    }

    TEST_F(TimeDelayTest, Should_Expect_AsyncFuturesResolved_When_Concurrent)
    {
        std::vector<std::future<void>> futures;

        for (int i = 0; i < 20; ++i)
        {
            futures.push_back(
                time_delay.in_microseconds_async(100.0)
            );
        }

        for (auto& f : futures)
        {
            EXPECT_NE(
                f.wait_for(std::chrono::seconds(2)),
                std::future_status::timeout
            );
        }
    }

    TEST_F(TimeDelayTest, Should_Expect_CallbackResult_When_ResultPassed)
    {
        std::atomic<bool> callback_called = false;

        time_delay.in_microseconds_async(
            [&](Result<void>& result)
            {
                callback_called.store(result.is_status_safe());
            },
            100.0
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayTest, Should_Expect_AsyncFutureResolved_When_CalibrateAsync)
    {
        auto future = time_delay.calibrate_async(100.0);
        auto status = future.wait_for(std::chrono::seconds(2));

        EXPECT_NE(status, std::future_status::timeout);
    }

    TEST_F(TimeDelayTest, Should_Expect_AsyncCallbackInvoked_When_CalibrateAsync)
    {
        std::atomic<bool> callback_called = false;
        std::mutex mutex;
        std::condition_variable cv;

        time_delay.calibrate_async(
            [&](const bool& result)
            {
                std::unique_lock<std::mutex> lock(mutex);
                callback_called = true;
                cv.notify_one();
            }
        );

        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(lock, std::chrono::seconds(2),
            [&]() { return callback_called.load(); });

        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayTest, Should_Expect_AsyncResultPassed_When_CalibrateAsync)
    {
        std::atomic<bool> callback_called = false;

        time_delay.calibrate_async(
            [&](Result<void>& result)
            {
                callback_called.store(result.is_status_safe());
            }
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayTest, Should_Expect_AsyncFutureResolved_When_RdtscAsync)
    {
        auto future = time_delay.real_time_stamp_counter_async(100.0);
        auto status = future.wait_for(std::chrono::seconds(2));

        EXPECT_NE(status, std::future_status::timeout);
    }

    TEST_F(TimeDelayTest, Should_Expect_AsyncCallbackInvoked_When_RdtscAsync)
    {
        std::atomic<bool> callback_called = false;
        std::mutex mutex;
        std::condition_variable cv;

        time_delay.real_time_stamp_counter_async(
            [&](const bool& result)
            {
                std::unique_lock<std::mutex> lock(mutex);
                callback_called = true;
                cv.notify_one();
            },
            100.0
        );

        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(lock, std::chrono::seconds(2),
            [&]() { return callback_called.load(); });

        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayTest, Should_Expect_AsyncResultPassed_When_RdtscAsync)
    {
        std::atomic<bool> callback_called = false;

        time_delay.real_time_stamp_counter_async(
            [&](Result<void>& result)
            {
                callback_called.store(result.is_status_safe());
            },
            100.0
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayTest, Should_Expect_AsyncFutureResolved_When_QpcAsync)
    {
        auto future = time_delay.query_performance_counter_async(100.0);
        auto status = future.wait_for(std::chrono::seconds(2));

        EXPECT_NE(status, std::future_status::timeout);
    }

    TEST_F(TimeDelayTest, Should_Expect_AsyncCallbackInvoked_When_QpcAsync)
    {
        std::atomic<bool> callback_called = false;
        std::mutex mutex;
        std::condition_variable cv;

        time_delay.query_performance_counter_async(
            [&](const bool& result)
            {
                std::unique_lock<std::mutex> lock(mutex);
                callback_called = true;
                cv.notify_one();
            },
            100.0
        );

        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(lock, std::chrono::seconds(2),
            [&]() { return callback_called.load(); });

        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayTest, Should_Expect_AsyncResultPassed_When_QpcAsync)
    {
        std::atomic<bool> callback_called = false;

        time_delay.query_performance_counter_async(
            [&](Result<void>& result)
            {
                callback_called.store(result.is_status_safe());
            },
            100.0
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        EXPECT_TRUE(callback_called);
    }
    TEST_F(TimeDelayTest, Should_Expect_MultiThreadedSafety_When_CalibrateAsync)
    {
        std::vector<std::future<void>> futures;
        std::atomic<int> completed = 0;

        for (int i = 0; i < 20; ++i)
        {
            futures.push_back(
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        auto future =
                            time_delay.calibrate_async(50.0);
                        future.wait();
                        completed.fetch_add(1);
                    }
                )
            );
        }

        for (auto& f : futures)
        {
            f.wait();
        }

        EXPECT_EQ(completed.load(), 20);
    }

    TEST_F(TimeDelayTest, Should_Expect_StressCompletion_When_CalibrateAsync)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; ++i)
        {
            auto future = time_delay.calibrate_async(10.0);
            future.wait();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration<double>(end - start).count();

        EXPECT_LE(elapsed, 2.0);
    }

    TEST_F(TimeDelayTest, Should_Expect_MultiThreadedSafety_When_RdtscAsync)
    {
        std::vector<std::future<void>> futures;
        std::atomic<int> completed = 0;

        for (int i = 0; i < 20; ++i)
        {
            futures.push_back(
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        auto future =
                            time_delay.real_time_stamp_counter_async(
                                100.0
                            );
                        future.wait();
                        completed.fetch_add(1);
                    }
                )
            );
        }

        for (auto& f : futures)
        {
            f.wait();
        }

        EXPECT_EQ(completed.load(), 20);
    }

    TEST_F(TimeDelayTest, Should_Expect_StressCompletion_When_RdtscAsync)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000; ++i)
        {
            auto future = time_delay.real_time_stamp_counter_async(
                50.0
            );
            future.wait();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration<double>(end - start).count();

        EXPECT_LE(elapsed, 2.0);
    }

    TEST_F(TimeDelayTest, Should_Expect_MultiThreadedSafety_When_QpcAsync)
    {
        std::vector<std::future<void>> futures;
        std::atomic<int> completed = 0;

        for (int i = 0; i < 20; ++i)
        {
            futures.push_back(
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        auto future =
                            time_delay.query_performance_counter_async(
                                100.0
                            );
                        future.wait();
                        completed.fetch_add(1);
                    }
                )
            );
        }

        for (auto& f : futures)
        {
            f.wait();
        }

        EXPECT_EQ(completed.load(), 20);
    }

    TEST_F(TimeDelayTest, Should_Expect_StressCompletion_When_QpcAsync)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000; ++i)
        {
            auto future =
                time_delay.query_performance_counter_async(50.0);
            future.wait();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration<double>(end - start).count();

        EXPECT_LE(elapsed, 2.0);
    }
}
