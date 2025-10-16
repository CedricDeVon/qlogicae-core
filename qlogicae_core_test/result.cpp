#include "pch.hpp"

#include "result.hpp"

namespace QLogicaeCoreTest
{
    /*
    class ResultStringTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::Result<std::string> result;
    };

    class ResultIntTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::Result<int> result;
    };

    class ResultDoubleTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::Result<double> result;
    };

    class ResultVoidTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::Result<void> result;
    };

    class ResultStringParamTest :
        public ::testing::TestWithParam<std::string>
    {
    protected:
        QLogicaeCore::Result<std::string> result;
    };

    struct ThrowOnCopy
    {
        ThrowOnCopy() = default;
        ThrowOnCopy(const ThrowOnCopy&)
        {
            throw std::runtime_error("copy error");
        }
        ThrowOnCopy(ThrowOnCopy&&) noexcept = default;
        ThrowOnCopy& operator=(const ThrowOnCopy&)
        {
            throw std::runtime_error("assign copy error");
        }
        ThrowOnCopy& operator=(ThrowOnCopy&&) noexcept = default;
    };

    class ResultThrowTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::Result<ThrowOnCopy> result;
    };

    class ResultIntParamTest :
        public ::testing::TestWithParam<int>
    {
    protected:
        QLogicaeCore::Result<int> result;
    };

    class ResultDoubleParamTest :
        public ::testing::TestWithParam<double>
    {
    protected:
        QLogicaeCore::Result<double> result;
    };

    TEST_F(ResultStringTest, Should_SetAndGetSuccess_When_UsingSetToSuccess)
    {
        result.set_to_good_status_with_value();
        EXPECT_TRUE(result.get_status());

        std::string sample_data = "test";
        result.set_to_good_status_with_value(sample_data);

        std::string retrieved_data;
        result.get_value(retrieved_data);
        EXPECT_EQ(retrieved_data, sample_data);
    }

    TEST_F(ResultStringTest, Should_SetAndGetFailure_When_UsingSetToFailure)
    {
        result.set_to_bad_status_with_value();
        EXPECT_FALSE(result.get_status());

        std::string sample_data = "fail";
        result.set_to_bad_status_with_value(sample_data);

        std::string retrieved_data;
        result.get_value(retrieved_data);
        EXPECT_EQ(retrieved_data, sample_data);
    }

    TEST_F(ResultStringTest, Should_SetAndGetMessage_When_UsingSetMessage)
    {
        std::string test_message = "message";
        result.set_message(test_message);
        EXPECT_EQ(result.get_message(), test_message);

        std::string retrieved_message;
        result.get_message(retrieved_message);
        EXPECT_EQ(retrieved_message, test_message);
    }

    TEST_F(ResultStringTest, Should_HandleAsyncOperations)
    {
        std::promise<void> start_promise;
        std::future<void> start_future = start_promise.get_future();
        std::future<bool> worker_future =
            std::async(std::launch::async,
                [this, &start_future]()
                {
                    start_future.get();
                    result.set_to_bad_status_with_value();
                    return result.get_status();
                });

        start_promise.set_value();
        EXPECT_FALSE(worker_future.get());
    }

    TEST_F(ResultStringTest, Should_BeThreadSafe_UnderConcurrentModification)
    {
        std::atomic<int> success_count = 0;
        std::vector<std::thread> threads;
        for (int index = 0; index < 50; ++index)
        {
            threads.emplace_back([this, &success_count]()
                {
                    result.set_to_good_status_with_value();
                    if (result.get_status())
                        success_count.fetch_add(1);
                });
        }
        for (std::thread& thread : threads)
            thread.join();

        EXPECT_EQ(success_count.load(), 50);
    }

    TEST_F(ResultStringTest, Should_PerformUnderStress)
    {
        auto start_time = std::chrono::steady_clock::now();
        std::vector<std::thread> threads;
        for (int index = 0; index < 200; ++index)
        {
            threads.emplace_back([this]()
                {
                    for (int inner = 0; inner < 50; ++inner)
                    {
                        result.set_to_good_status_with_value();
                        result.set_to_bad_status_with_value();
                    }
                });
        }
        for (std::thread& t : threads)
            t.join();

        auto end_time = std::chrono::steady_clock::now();
        long long elapsed_seconds =
            std::chrono::duration_cast<std::chrono::seconds>(end_time
                - start_time).count();
        EXPECT_LE(elapsed_seconds, 2);
    }

    TEST_F(ResultStringTest, Should_HandleEdgeCase_When_EmptyData)
    {
        std::string empty_data;
        result.set_to_good_status_with_value(empty_data);

        std::string retrieved_data;
        result.get_value(retrieved_data);
        EXPECT_EQ(retrieved_data, empty_data);
    }

    TEST_P(ResultStringParamTest, Should_HandleParameterizedData_When_SetToSuccess)
    {
        const std::string param_value = GetParam();
        result.set_to_good_status_with_value(param_value);

        std::string retrieved_value;
        result.get_value(retrieved_value);
        EXPECT_EQ(retrieved_value, param_value);
    }

    TEST_F(ResultIntTest, Should_SetAndGetSuccess_When_UsingSetToSuccess)
    {
        result.set_to_good_status_with_value();
        EXPECT_TRUE(result.get_status());

        result.set_to_good_status_with_value(42);
        int value;
        result.get_value(value);
        EXPECT_EQ(value, 42);
    }

    TEST_F(ResultIntTest, Should_HandleAsyncOperations)
    {
        std::future<bool> async_task =
            std::async(std::launch::async,
                [this]()
                {
                    result.set_to_bad_status_with_value();
                    return result.get_status();
                });
        EXPECT_FALSE(async_task.get());
    }

    TEST_F(ResultIntTest, Should_PerformUnderStress)
    {
        auto start_time = std::chrono::steady_clock::now();
        std::vector<std::thread> threads;
        for (int index = 0; index < 200; ++index)
        {
            threads.emplace_back([this]()
                {
                    for (int inner = 0; inner < 20; ++inner)
                    {
                        result.set_to_good_status_with_value();
                        result.set_to_bad_status_with_value();
                    }
                });
        }
        for (std::thread& t : threads)
            t.join();

        auto end_time = std::chrono::steady_clock::now();
        long long elapsed_seconds =
            std::chrono::duration_cast<std::chrono::seconds>(end_time
                - start_time).count();
        EXPECT_LE(elapsed_seconds, 2);
    }

    TEST_F(ResultDoubleTest, Should_SetAndGetSuccess_When_UsingSetToSuccess)
    {
        result.set_to_good_status_with_value();
        EXPECT_TRUE(result.get_status());

        result.set_to_good_status_with_value(3.14);
        double value;
        result.get_value(value);
        EXPECT_DOUBLE_EQ(value, 3.14);
    }

    TEST_F(ResultDoubleTest, Should_HandleAsyncOperations)
    {
        std::future<bool> async_task =
            std::async(std::launch::async,
                [this]()
                {
                    result.set_to_bad_status_with_value();
                    return result.get_status();
                });
        EXPECT_FALSE(async_task.get());
    }

    TEST_F(ResultVoidTest, Should_SetAndGetSuccess)
    {
        result.set_to_good_status_with_value();
        EXPECT_TRUE(result.get_status());

        result.set_to_bad_status_with_value();
        EXPECT_FALSE(result.get_status());
    }

    TEST_F(ResultVoidTest, Should_HandleAsyncOperations)
    {
        std::future<bool> async_task =
            std::async(std::launch::async,
                [this]()
                {
                    result.set_to_bad_status_with_value();
                    return result.get_status();
                });
        EXPECT_FALSE(async_task.get());
    }

    TEST_F(ResultThrowTest, Should_Throw_OnCopyAssignment_When_CopyProvided)
    {
        ThrowOnCopy value;
        EXPECT_THROW(result.set_to_good_status_with_value(value), std::runtime_error);
    }

    TEST_F(ResultThrowTest, Should_NotThrow_OnMoveAssignment_When_MoveProvided)
    {
        ThrowOnCopy value;
        EXPECT_NO_THROW(result.set_to_good_status_with_value(std::move(value)));
    }

    TEST_F(ResultStringTest,
        Should_UsePromiseAndConditionVariable_ForCoordinatedThreads)
    {
        std::mutex mutex;
        std::condition_variable condition;
        std::atomic<int> completed_count = 0;
        std::promise<void> start_promise;
        std::future<void> start_future = start_promise.get_future();
        std::atomic<int> success_increment = 0;
        const int THREAD_COUNT = 30;
        std::vector<std::thread> threads;

        for (int index = 0; index < THREAD_COUNT; ++index)
        {
            threads.emplace_back([this, &start_future, &mutex,
                &condition, &completed_count, &success_increment]()
                {
                    start_future.wait();
                    {
                        std::lock_guard<std::mutex> guard(mutex);
                        result.set_to_good_status_with_value();
                        if (result.get_status())
                            success_increment.fetch_add(1);
                    }
                    completed_count.fetch_add(1);
                    condition.notify_one();
                });
        }

        start_promise.set_value();

        {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait_for(lock, std::chrono::seconds(2),
                [&completed_count, THREAD_COUNT]()
                {
                    return completed_count.load() == THREAD_COUNT;
                });
        }

        for (auto& thread : threads)
            thread.join();

        EXPECT_EQ(success_increment.load(), THREAD_COUNT);
    }

    TEST_F(ResultIntTest, Should_HandleEdgeCases_MinMax_When_SetToSuccess)
    {
        int min_value = std::numeric_limits<int>::min();
        int max_value = std::numeric_limits<int>::max();
        result.set_to_good_status_with_value(min_value);
        int retrieved_min;
        result.get_value(retrieved_min);
        EXPECT_EQ(retrieved_min, min_value);

        result.set_to_good_status_with_value(max_value);
        int retrieved_max;
        result.get_value(retrieved_max);
        EXPECT_EQ(retrieved_max, max_value);
    }

    TEST_F(ResultStringTest, Should_CompleteHighIterationStressWithinTime)
    {
        auto start_time = std::chrono::steady_clock::now();
        for (int index = 0; index < 1000; ++index)
        {
            result.set_to_good_status_with_value("x");
            result.set_to_bad_status_with_value();
        }
        auto end_time = std::chrono::steady_clock::now();
        long long elapsed_millis =
            std::chrono::duration_cast<std::chrono::milliseconds>(end_time
                - start_time).count();
        EXPECT_LE(elapsed_millis, 2000);
    }

    TEST_P(ResultIntParamTest,
        Should_HandleParameterizedValues_When_SetToSuccess)
    {
        const int param_value = GetParam();
        result.set_to_good_status_with_value(param_value);
        int retrieved_value;
        result.get_value(retrieved_value);
        EXPECT_EQ(retrieved_value, param_value);
    }

    TEST_P(ResultDoubleParamTest,
        Should_HandleParameterizedValues_When_SetToSuccess)
    {
        const double param_value = GetParam();
        result.set_to_good_status_with_value(param_value);
        double retrieved_value;
        result.get_value(retrieved_value);
        EXPECT_DOUBLE_EQ(retrieved_value, param_value);
    }

    TEST_F(ResultIntTest, Should_HandleEdgeCases_NegativeAndZero_When_Set)
    {
        result.set_to_good_status_with_value(0);
        int zero_value;
        result.get_value(zero_value);
        EXPECT_EQ(zero_value, 0);

        result.set_to_good_status_with_value(-123);
        int negative_value;
        result.get_value(negative_value);
        EXPECT_EQ(negative_value, -123);
    }

    TEST_F(ResultDoubleTest, Should_HandleEdgeCases_SpecialFloatingPoints)
    {
        double inf = std::numeric_limits<double>::infinity();
        double nan = std::numeric_limits<double>::quiet_NaN();
        result.set_to_good_status_with_value(inf);
        double retrieved_inf;
        result.get_value(retrieved_inf);
        EXPECT_TRUE(std::isinf(retrieved_inf));

        result.set_to_good_status_with_value(nan);
        double retrieved_nan;
        result.get_value(retrieved_nan);
        EXPECT_TRUE(std::isnan(retrieved_nan));
    }

    TEST_F(ResultVoidTest,
        Should_PerformUnderStress_When_ConcurrentSuccessFailure)
    {
        std::vector<std::thread> threads;
        std::atomic<int> success_counter = 0;
        auto start_time = std::chrono::steady_clock::now();
        for (int i = 0; i < 150; ++i)
        {
            threads.emplace_back([this, &success_counter]()
                {
                    result.set_to_good_status_with_value();
                    if (result.get_status())
                        success_counter.fetch_add(1);
                    result.set_to_bad_status_with_value();
                });
        }
        for (std::thread& t : threads)
            t.join();
        auto end_time = std::chrono::steady_clock::now();
        long long elapsed_seconds =
            std::chrono::duration_cast<std::chrono::seconds>(end_time
                - start_time).count();
        EXPECT_LE(elapsed_seconds, 2);
        EXPECT_GE(success_counter.load(), 0);
    }

    TEST_F(ResultVoidTest, Should_HandleMultipleAsyncCallsWithinTwoSeconds)
    {
        auto start_time = std::chrono::steady_clock::now();
        std::vector<std::future<bool>> futures;
        for (int i = 0; i < 100; ++i)
        {
            futures.push_back(std::async(std::launch::async, [this]()
                {
                    result.set_to_good_status_with_value();
                    return result.get_status();
                }));
        }
        for (std::future<bool>& f : futures)
            EXPECT_TRUE(f.get());
        auto end_time = std::chrono::steady_clock::now();
        long long elapsed_seconds =
            std::chrono::duration_cast<std::chrono::seconds>(end_time
                - start_time).count();
        EXPECT_LE(elapsed_seconds, 2);
    }

    TEST_F(ResultIntTest, Should_DefaultToSuccess_When_Uninitialized)
    {
        EXPECT_TRUE(result.get_status());
    }

    TEST_F(ResultIntTest, Should_AllowReuse_BetweenStates)
    {
        result.set_to_good_status_with_value(10);
        EXPECT_TRUE(result.get_status());

        result.set_to_bad_status_with_value();
        EXPECT_FALSE(result.get_status());

        result.set_to_good_status_with_value(42);
        int value;
        result.get_value(value);
        EXPECT_EQ(value, 42);
    }

    TEST_F(ResultIntTest, Should_PreserveData_When_Moved)
    {
        result.set_to_good_status_with_value(99);
        QLogicaeCore::Result<int> moved_result(std::move(result));

        int value;
        moved_result.get_value(value);
        EXPECT_EQ(value, 99);
    }

    TEST_F(ResultIntTest, Should_CopyCorrectly_When_Copied)
    {
        result.set_to_good_status_with_value(7);
        QLogicaeCore::Result<int> copy_result = result;

        int value;
        copy_result.get_value(value);
        EXPECT_EQ(value, 7);
    }

    TEST_F(ResultVoidTest, Should_RemainStable_When_ConcurrentSetCalls)
    {
        std::atomic<int> success_count = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < 100; ++i)
        {
            threads.emplace_back([this, &success_count, i]()
                {
                    if (i % 2 == 0) result.set_to_good_status_with_value();
                    else result.set_to_bad_status_with_value();

                    if (result.get_status())
                        success_count.fetch_add(1);
                });
        }

        for (auto& t : threads) t.join();
        EXPECT_GE(success_count.load(), 0);
    }

    TEST_F(ResultStringTest, Should_HandleComplexTypes_Correctly)
    {
        std::string text = "TestValue";
        result.set_to_good_status_with_value(text);

        std::string retrieved;
        result.get_value(retrieved);
        EXPECT_EQ(retrieved, "TestValue");
    }

    TEST_F(ResultVoidTest, Should_HandleAsyncFailureState)
    {
        auto fut = std::async(std::launch::async, [this]()
            {
                result.set_to_bad_status_with_value();
                return result.get_status();
            });

        EXPECT_FALSE(fut.get());
    }

    TEST_F(ResultStringTest, Should_ReturnDefaultMessage_When_NotSet)
    {
        std::string retrieved_message;
        result.get_message(retrieved_message);
        EXPECT_TRUE(retrieved_message.empty());
    }

    TEST_F(ResultStringTest, Should_AllowMessageOverwrite)
    {
        result.set_message("first");
        EXPECT_EQ(result.get_message(), "first");

        result.set_message("second");
        EXPECT_EQ(result.get_message(), "second");
    }

    TEST_F(ResultStringTest, Should_HandleEmptyMessageSet)
    {
        result.set_message("");
        std::string retrieved_message;
        result.get_message(retrieved_message);
        EXPECT_TRUE(retrieved_message.empty());
    }

    TEST_F(ResultStringTest, Should_HandleGetDataBeforeAnySet)
    {
        std::string retrieved;
        result.get_value(retrieved);
        EXPECT_TRUE(retrieved.empty());
    }

    TEST_F(ResultIntTest, Should_HandleGetDataBeforeAnySet)
    {
        int value = 12345;
        EXPECT_NO_THROW(result.get_value(value));
        EXPECT_TRUE(result.get_status());
    }

    TEST_F(ResultStringTest, Should_PreserveMessage_When_SwitchingStates)
    {
        result.set_message("info");
        result.set_to_good_status_with_value("data");
        result.set_to_bad_status_with_value("fail");
        EXPECT_EQ(result.get_message(), "info");
    }

    TEST_F(ResultStringTest, Should_PreserveData_When_SwitchingStates)
    {
        result.set_to_good_status_with_value("success");
        result.set_to_bad_status_with_value("failure");
        std::string retrieved;
        result.get_value(retrieved);
        EXPECT_EQ(retrieved, "failure");
    }

    TEST_F(ResultStringTest, Should_NotThrow_When_GetDataAfterFailure)
    {
        result.set_to_bad_status_with_value("error_data");
        std::string retrieved;
        EXPECT_NO_THROW(result.get_value(retrieved));
    }

    TEST_F(ResultThrowTest, Should_NotCorruptState_AfterException)
    {
        ThrowOnCopy value;
        bool exception_thrown = false;

        try
        {
            result.set_to_good_status_with_value(value);
        }
        catch (...)
        {
            exception_thrown = true;
        }

        EXPECT_TRUE(exception_thrown);
        EXPECT_TRUE(result.get_status());
    }

    TEST_F(ResultStringTest, Should_HandleLargePayloads)
    {
        std::string large_data(1000000, 'A');
        result.set_to_good_status_with_value(large_data);

        std::string retrieved;
        result.get_value(retrieved);
        EXPECT_EQ(retrieved.size(), large_data.size());
        EXPECT_EQ(retrieved.front(), 'A');
        EXPECT_EQ(retrieved.back(), 'A');
    }

    INSTANTIATE_TEST_CASE_P(
        NonEmptyStringCases,
        ResultStringParamTest,
        ::testing::Values(std::string("alpha"), std::string("beta"),
            std::string("gamma"))
    );

    INSTANTIATE_TEST_CASE_P(
        EmptyStringCase,
        ResultStringParamTest,
        ::testing::Values(std::string())
    );

    INSTANTIATE_TEST_CASE_P(
        IntegerParameterizedCases,
        ResultIntParamTest,
        ::testing::Values(0, 1, -1, std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max())
    );

    INSTANTIATE_TEST_CASE_P(
        DoubleParameterizedCases,
        ResultDoubleParamTest,
        ::testing::Values(0.0, -1.5, 3.14159,
            std::numeric_limits<double>::infinity(),
            -std::numeric_limits<double>::infinity())
    );
    */
}
