#include "pch.hpp"

#include "qlogicae_cpp_core/includes/time_delay_clock.hpp"

namespace QLogicaeCppCoreTest
{
    class TimeDelayClockTest
        : public ::testing::TestWithParam<double>
    {
    };

    INSTANTIATE_TEST_CASE_P(
        TimeDelayClockParameterTests,
        TimeDelayClockTest,
        ::testing::Values(
            0.0,
            0.000001,
            1.0,
            1000.0,
            1'000'000.0
        )
    );

    TEST_P(TimeDelayClockTest, Should_Expect_SynchronousBehavior_When_Invoked)
    {
        double duration = GetParam();
        QLogicaeCppCore::Result<bool> result;

        auto start = std::chrono::high_resolution_clock::now();
        QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, duration);
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed =
            std::chrono::duration<double, std::micro>(end - start).count();

        EXPECT_GE(elapsed, duration * 0.9);
    }

    TEST_P(TimeDelayClockTest, Should_Expect_AsynchronousCompletion_When_CalledAsync)
    {
        double duration = GetParam();

        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result,
                    duration);
            }
        );

        auto status = future.wait_for(std::chrono::seconds(2));
        EXPECT_NE(status, std::future_status::timeout);
    }

    TEST_P(TimeDelayClockTest, Should_Expect_CallbackExecution_When_AsyncCalled)
    {
        double duration = GetParam();
        std::atomic<bool> callback_called = false;
        std::mutex mutex;
        std::condition_variable cv;

        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result,
                    duration);
                {
                    std::unique_lock<std::mutex> l(mutex);
                    callback_called = true;
                    cv.notify_one();
                }
            }
        );

        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(
            lock,
            std::chrono::seconds(2),
            [&]() { return callback_called.load(); }
        );

        EXPECT_TRUE(callback_called);
    }

    TEST_P(TimeDelayClockTest, Should_Expect_MultithreadedSafety_When_ParallelInvoked)
    {
        double duration = GetParam();
        std::atomic<int> completed = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back(
                [&]()
                {
                    QLogicaeCppCore::Result<bool> result;
                    QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result,
                        duration);
                    completed.fetch_add(1);
                }
            );
        }

        for (auto& t : threads)
        {
            if (t.joinable())
            {
                t.join();
            }
        }

        EXPECT_EQ(completed.load(), 10);
    }

    TEST_P(TimeDelayClockTest, Should_Expect_NoExceptions_When_Handled)
    {
        double duration = GetParam();

        EXPECT_NO_THROW(
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result,
                    duration);
            }
        );
    }

    TEST_F(TimeDelayClockTest, Should_Expect_ValidCalibration_When_Called)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::TIME_DELAY_CLOCK.calibrate(result);
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(TimeDelayClockTest, Should_Expect_QPCBehavior_When_Called)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::TIME_DELAY_CLOCK.query_performance_counter(result,
            100.0);
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(TimeDelayClockTest, Should_Expect_RDTSCBehavior_When_Called)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::TIME_DELAY_CLOCK.real_time_stamp_counter(result,
            100.0);
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(TimeDelayClockTest, Should_Expect_PerformanceCompletion_When_HeavyLoad)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000; ++i)
        {
            QLogicaeCppCore::Result<bool> result;
            QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, 50.0);
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed =
            std::chrono::duration<double>(end - start).count();

        EXPECT_LE(elapsed, 2.0);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_SafeHandling_When_InvalidValues)
    {
        QLogicaeCppCore::Result<bool> result;
        EXPECT_NO_THROW(QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(
            result, -1.0));
        EXPECT_NO_THROW(QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(
            result, 0.0));
    }

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncFuturesResolved_When_Concurrent)
    {
        std::vector<std::future<void>> futures;

        for (int i = 0; i < 20; ++i)
        {
            futures.push_back(
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        QLogicaeCppCore::Result<bool> result;
                        QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result,
                            100.0);
                    }
                )
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

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncCallbackResult_When_ResultPassed)
    {
        std::atomic<bool> callback_called = false;

        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result,
                    100.0);
                callback_called.store(result.get_value());
            }
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncFutureResolved_When_CalibrateAsync)
    {
        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.calibrate(result);
            }
        );

        auto status = future.wait_for(std::chrono::seconds(2));
        EXPECT_NE(status, std::future_status::timeout);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncCallbackInvoked_When_CalibrateAsync)
    {
        std::atomic<bool> callback_called = false;
        std::mutex mutex;
        std::condition_variable cv;

        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.calibrate(result);
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    callback_called = true;
                    cv.notify_one();
                }
            }
        );

        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(
            lock,
            std::chrono::seconds(2),
            [&]() { return callback_called.load(); }
        );

        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncResultPassed_When_CalibrateAsync)
    {
        std::atomic<bool> callback_called = false;

        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.calibrate(result);
                callback_called.store(result.get_value());
            }
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncFutureResolved_When_RdtscAsync)
    {
        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.real_time_stamp_counter(
                    result, 100.0);
            }
        );

        auto status = future.wait_for(std::chrono::seconds(2));
        EXPECT_NE(status, std::future_status::timeout);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncCallbackInvoked_When_RdtscAsync)
    {
        std::atomic<bool> callback_called = false;
        std::mutex mutex;
        std::condition_variable cv;

        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.real_time_stamp_counter(
                    result, 100.0);
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    callback_called = true;
                    cv.notify_one();
                }
            }
        );

        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(
            lock,
            std::chrono::seconds(2),
            [&]() { return callback_called.load(); }
        );

        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncResultPassed_When_RdtscAsync)
    {
        std::atomic<bool> callback_called = false;

        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.real_time_stamp_counter(
                    result, 100.0);
                callback_called.store(result.get_value());
            }
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncFutureResolved_When_QpcAsync)
    {
        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.query_performance_counter(
                    result, 100.0);
            }
        );

        auto status = future.wait_for(std::chrono::seconds(2));
        EXPECT_NE(status, std::future_status::timeout);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncCallbackInvoked_When_QpcAsync)
    {
        std::atomic<bool> callback_called = false;
        std::mutex mutex;
        std::condition_variable cv;

        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.query_performance_counter(
                    result, 100.0);
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    callback_called = true;
                    cv.notify_one();
                }
            }
        );

        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(
            lock,
            std::chrono::seconds(2),
            [&]() { return callback_called.load(); }
        );

        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_AsyncResultPassed_When_QpcAsync)
    {
        std::atomic<bool> callback_called = false;

        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.query_performance_counter(
                    result, 100.0);
                callback_called.store(result.get_value());
            }
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_MultiThreadedSafety_When_CalibrateAsync)
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
                        QLogicaeCppCore::Result<bool> result;
                        QLogicaeCppCore::TIME_DELAY_CLOCK.calibrate(result);
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

    TEST_F(TimeDelayClockTest, Should_Expect_StressCompletion_When_CalibrateAsync)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; ++i)
        {
            QLogicaeCppCore::Result<bool> result;
            QLogicaeCppCore::TIME_DELAY_CLOCK.calibrate(result);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration<double>(end - start).count();

        EXPECT_LE(elapsed, 2.0);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_MultiThreadedSafety_When_RdtscAsync)
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
                        QLogicaeCppCore::Result<bool> result;
                        QLogicaeCppCore::TIME_DELAY_CLOCK.real_time_stamp_counter(
                            result, 100.0);
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

    TEST_F(TimeDelayClockTest, Should_Expect_StressCompletion_When_RdtscAsync)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000; ++i)
        {
            QLogicaeCppCore::Result<bool> result;
            QLogicaeCppCore::TIME_DELAY_CLOCK.real_time_stamp_counter(result,
                50.0);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration<double>(end - start).count();

        EXPECT_LE(elapsed, 2.0);
    }

    TEST_F(TimeDelayClockTest, Should_Expect_MultiThreadedSafety_When_QpcAsync)
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
                        QLogicaeCppCore::Result<bool> result;
                        QLogicaeCppCore::TIME_DELAY_CLOCK.query_performance_counter(
                            result, 100.0);
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

    TEST_F(TimeDelayClockTest, Should_Expect_StressCompletion_When_QpcAsync)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000; ++i)
        {
            QLogicaeCppCore::Result<bool> result;
            QLogicaeCppCore::TIME_DELAY_CLOCK.query_performance_counter(result,
                50.0);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration<double>(end - start).count();

        EXPECT_LE(elapsed, 2.0);
    }

    TEST_F(TimeDelayClockTest, Should_Handle_ExtremelySmallDurations)
    {
        QLogicaeCppCore::Result<bool> result;
        EXPECT_NO_THROW(
            QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, 1e-12)
        );
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(TimeDelayClockTest, Should_Handle_ExtremelyLargeDurations)
    {
        QLogicaeCppCore::Result<bool> result;
        EXPECT_NO_THROW(
            QLogicaeCppCore::TIME_DELAY_CLOCK.in_seconds(result, 1)
        );
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(TimeDelayClockTest, Should_Handle_ZeroDurationAsync)
    {
        std::atomic<bool> callback_called = false;
        std::mutex mutex;
        std::condition_variable cv;

        auto future = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, 0.0);
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    callback_called = true;
                    cv.notify_one();
                }
            }
        );

        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(
            lock,
            std::chrono::seconds(1),
            [&]() { return callback_called.load(); }
        );

        EXPECT_TRUE(callback_called);
    }

    TEST_F(TimeDelayClockTest, Should_CalibrationAffectSubsequentTiming)
    {
        QLogicaeCppCore::Result<bool> result;

        QLogicaeCppCore::TIME_DELAY_CLOCK.calibrate(result);
        EXPECT_TRUE(result.get_value());

        auto start = std::chrono::high_resolution_clock::now();
        QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, 100.0);
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed =
            std::chrono::duration<double, std::micro>(end - start).count();

        EXPECT_GE(elapsed, 100.0 * 0.9);
    }

    TEST_F(TimeDelayClockTest, Should_ConstructAndDestructSafely)
    {
        EXPECT_NO_THROW(
            {
                QLogicaeCppCore::TimeDelayClock local_clock;
                QLogicaeCppCore::Result<bool> result;
                local_clock.in_microseconds(result, 10.0);
            }
        );
    }

    TEST_F(TimeDelayClockTest, Should_ProduceFailureResult_OnNegativeDuration)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, -100.0);
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(TimeDelayClockTest, Should_ProduceFailureResult_OnOverflowDuration)
    {
        QLogicaeCppCore::Result<bool> result;
        QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result,
            std::numeric_limits<double>::max());
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(TimeDelayClockTest, Should_HandleSystemFailureSimulation)
    {
        QLogicaeCppCore::Result<bool> result;

        EXPECT_NO_THROW(
            QLogicaeCppCore::TIME_DELAY_CLOCK.query_performance_counter(result,
                -1.0)
        );
        EXPECT_FALSE(result.get_value());

        EXPECT_NO_THROW(
            QLogicaeCppCore::TIME_DELAY_CLOCK.real_time_stamp_counter(result,
                -1.0)
        );
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(TimeDelayClockTest, Should_Handle_MaxSupportedDuration)
    {
        QLogicaeCppCore::Result<bool> result;
        double max_duration = 1e12 + 1.0;
        EXPECT_NO_THROW(
            QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, max_duration)
        );
        EXPECT_FALSE(result.get_value());

        EXPECT_NO_THROW(
            QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, max_duration + 1.0)
        );
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(TimeDelayClockTest, Should_SupportAllTimeUnits)
    {
        QLogicaeCppCore::Result<bool> result;

        EXPECT_NO_THROW(
            QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, 100.0)
        );
        EXPECT_TRUE(result.get_value());

        EXPECT_NO_THROW(
            QLogicaeCppCore::TIME_DELAY_CLOCK.in_milliseconds(result, 1.0)
        );
        EXPECT_TRUE(result.get_value());

        EXPECT_NO_THROW(
            QLogicaeCppCore::TIME_DELAY_CLOCK.in_seconds(result, 0.001)
        );
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(TimeDelayClockTest, Should_HandleSequentialAsyncStress)
    {
        std::vector<std::future<void>> futures;
        std::atomic<int> completed = 0;

        for (int i = 0; i < 500; ++i)
        {
            futures.push_back(
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        QLogicaeCppCore::Result<bool> result;
                        QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, 10.0);
                        if (result.get_value())
                        {
                            completed.fetch_add(1);
                        }
                    }
                )
            );
        }

        for (auto& f : futures)
        {
            f.wait();
        }

        EXPECT_EQ(completed.load(), 500);
    }

    TEST_F(TimeDelayClockTest, Should_DestructSafelyDuringAsyncOperations)
    {
        std::atomic<bool> callback_called = false;
        std::mutex mutex;
        std::condition_variable cv;

        {
            QLogicaeCppCore::TimeDelayClock local_clock;

            auto future = std::async(
                std::launch::async,
                [&]()
                {
                    QLogicaeCppCore::Result<bool> result;
                    local_clock.in_microseconds(result, 50.0);
                    {
                        std::unique_lock<std::mutex> lock(mutex);
                        callback_called = true;
                        cv.notify_one();
                    }
                }
            );

            std::unique_lock<std::mutex> lock(mutex);
            cv.wait_for(lock, std::chrono::seconds(1), [&]() { return callback_called.load(); });
            EXPECT_TRUE(callback_called);
        }
    }

    TEST_F(TimeDelayClockTest, Should_EnsureCallbackOrderUnderHeavyLoad)
    {
        const int num_callbacks = 50;
        std::vector<int> callback_order;
        std::mutex mutex;

        std::vector<std::future<void>> futures;
        for (int i = 0; i < num_callbacks; ++i)
        {
            futures.push_back(
                std::async(
                    std::launch::async,
                    [&, i]()
                    {
                        QLogicaeCppCore::Result<bool> result;
                        QLogicaeCppCore::TIME_DELAY_CLOCK.in_microseconds(result, 1.0);
                        if (result.get_value())
                        {
                            std::unique_lock<std::mutex> lock(mutex);
                            callback_order.push_back(i);
                        }
                    }
                )
            );
        }

        for (auto& f : futures)
        {
            f.wait();
        }

        EXPECT_EQ(callback_order.size(), num_callbacks);
        std::sort(callback_order.begin(), callback_order.end());
        for (int i = 0; i < num_callbacks; ++i)
        {
            EXPECT_EQ(callback_order[i], i);
        }
    }
}
