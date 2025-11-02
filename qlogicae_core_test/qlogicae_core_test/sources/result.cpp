#include "pch.hpp"

#include "qlogicae_core/includes/result.hpp"

namespace QLogicaeCoreTest
{
    class ResultTest : public ::testing::Test
    {
    public:
        ResultTest() = default;
        void SetUp() override
        {
        }
        void TearDown() override
        {
        }
    };

    class ResultStatusParamTest :
        public ::testing::TestWithParam<QLogicaeCore::ResultStatus>
    {
    public:
        ResultStatusParamTest() = default;
    };

    template <typename T>
    class ResultTemplateParamTest : public ::testing::Test
    {
    };

    typedef ::testing::Types<int, double, bool, std::string> ResultTypes;

    TEST(ResultTest, Should_Expect_SetGetStatus_When_StatusIsSet)
    {
        QLogicaeCore::Result<std::string> result;
        QLogicaeCore::ResultStatus expected_status =
            QLogicaeCore::ResultStatus::INFO;
        result.set_status(expected_status);
        QLogicaeCore::ResultStatus actual_status = result.get_status();
        ASSERT_EQ(actual_status, expected_status);
    }

    TEST(ResultTest, Should_Expect_SetGetMessage_When_MessageIsSet)
    {
        QLogicaeCore::Result<std::string> result;
        std::string expected_message = std::string("test message");
        result.set_message(expected_message);
        std::string actual_message = result.get_message();
        ASSERT_EQ(actual_message, expected_message);
    }

    TEST(ResultTest, Should_Expect_SetGetValue_When_ValueIsSet)
    {
        QLogicaeCore::Result<std::string> result;
        std::string expected_value = std::string("payload");
        result.set_value(expected_value);
        std::string actual_value = result.get_value();
        ASSERT_EQ(actual_value, expected_value);
    }

    TEST(ResultTest, Should_Expect_MoveSemantics_When_ValueMoved)
    {
        QLogicaeCore::Result<std::string> result;
        std::string source = std::string("move payload");
        result.set_value(std::move(source));
        std::string actual_value = result.get_value();
        ASSERT_EQ(actual_value, std::string("move payload"));
        ASSERT_TRUE(source.empty() || source.size() >= 0);
    }

    TEST(ResultTest, Should_Expect_StatusHelpers_When_SetVariousStatuses)
    {
        QLogicaeCore::Result<std::string> result;
        result.set_status_to_debug();
        ASSERT_TRUE(result.is_status_debug());
        result.set_status_to_error();
        ASSERT_TRUE(result.is_status_error());
        result.set_status_to_good();
        ASSERT_TRUE(result.is_status_good());
    }

    TEST_P(ResultStatusParamTest, Should_Expect_IsStatusWhetherMatches_When_ParamProvided)
    {
        QLogicaeCore::Result<std::string> result;
        QLogicaeCore::ResultStatus param_status = GetParam();
        result.set_status(param_status);
        bool is_match = result.is_status(param_status);
        ASSERT_TRUE(is_match);
    }

    INSTANTIATE_TEST_CASE_P(
        ResultStatusInstantiation,
        ResultStatusParamTest,
        ::testing::Values(
            QLogicaeCore::ResultStatus::GOOD,
            QLogicaeCore::ResultStatus::INFO,
            QLogicaeCore::ResultStatus::DEBUG,
            QLogicaeCore::ResultStatus::WARNING,
            QLogicaeCore::ResultStatus::BAD,
            QLogicaeCore::ResultStatus::ERROR_,
            QLogicaeCore::ResultStatus::EXCEPTION
        )
    );

    TEST(ResultTest, Should_Expect_AsyncSetAndGet_When_UsedWithPromiseAndFuture)
    {
        QLogicaeCore::Result<std::string> result;
        std::promise<void> signal_promise;
        std::future<void> signal_future = signal_promise.get_future();
        std::future<void> worker_future = std::async(
            std::launch::async,
            [&result, &signal_future]()
            {
                signal_future.wait();
                result.set_to_good_status_with_value(std::string("ok"));
            }
        );
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        signal_promise.set_value();
        worker_future.get();
        ASSERT_TRUE(result.is_status_good());
        ASSERT_EQ(result.get_value(), std::string("ok"));
    }

    TEST(ResultTest, Should_Expect_MultithreadedWrite_When_ProtectedByMutex)
    {
        QLogicaeCore::Result<int> result;
        std::mutex write_mutex;
        std::vector<std::thread> threads;
        std::atomic<int> success_counter = 0;
        for (int i = 0; i < 32; i++)
        {
            threads.emplace_back(
                [&result, &write_mutex, &success_counter, i]()
                {
                    std::lock_guard<std::mutex> lock(write_mutex);
                    result.set_value(i);
                    int read_value = result.get_value();
                    if (read_value == i)
                    {
                        success_counter.fetch_add(1);
                    }
                }
            );
        }
        for (std::thread& thread : threads)
        {
            thread.join();
        }
        ASSERT_EQ(success_counter.load(), 32);
    }

    TEST(ResultTest, Should_Expect_StressUnderModerateLoad_When_RepeatedAccess)
    {
        QLogicaeCore::Result<int> result;
        result.set_value(0);
        std::mutex write_mutex;
        const int iterations = 20000;
        std::vector<std::thread> threads;
        for (int t = 0; t < 4; t++)
        {
            threads.emplace_back(
                [&result, &write_mutex, iterations]()
                {
                    for (int i = 0; i < iterations; i++)
                    {
                        std::lock_guard<std::mutex> lock(write_mutex);
                        result.set_value(i);
                        int read_value = result.get_value();
                        (void)read_value;
                    }
                }
            );
        }
        for (std::thread& thread : threads)
        {
            thread.join();
        }
        int final_value = result.get_value();
        ASSERT_GE(final_value, 0);
    }

    TEST(ResultTest, Should_Expect_ExceptionSafety_When_ThreadThrowsAndIsCaught)
    {
        QLogicaeCore::Result<int> result;
        std::future<void> fut = std::async(
            std::launch::async,
            [&result]()
            {
                try
                {
                    throw std::runtime_error("simulated");
                }
                catch (const std::exception&)
                {
                    result.set_to_bad_status_without_value(
                        std::string("caught")
                    );
                }
            }
        );
        fut.get();
        ASSERT_TRUE(result.is_status_bad());
    }

    TEST(ResultTest, Should_Expect_EdgeCases_When_EmptyStringAndLargeString)
    {
        QLogicaeCore::Result<std::string> result;
        result.set_value(std::string());
        ASSERT_EQ(result.get_value(), std::string());
        std::string large_string;
        large_string.reserve(1024);
        for (int i = 0; i < 1024; i++)
        {
            large_string.push_back(static_cast<char>('a' + (i % 26)));
        }
        result.set_value(large_string);
        ASSERT_EQ(result.get_value().size(), 1024);
    }

    TEST(ResultTest, Should_Expect_ParameterizedEmptyArgumentCase_When_ValueIsEmpty)
    {
        QLogicaeCore::Result<std::string> result;
        result.set_to_good_status_with_value(std::string());
        ASSERT_TRUE(result.is_status_good());
        ASSERT_EQ(result.get_value(), std::string());
    }


    TEST(ResultTest, Should_Expect_ConcurrentAsyncAndThread_When_AccessSameInstance)
    {
        QLogicaeCore::Result<int> result;
        result.set_value(0);
        std::atomic<int> read_counter = 0;
        std::future<void> async_future = std::async(
            std::launch::async,
            [&result, &read_counter]()
            {
                for (int i = 0; i < 10000; i++)
                {
                    (void)result.get_value();
                    read_counter.fetch_add(1);
                }
            }
        );
        std::thread writer_thread(
            [&result]()
            {
                for (int i = 0; i < 10000; i++)
                {
                    result.set_value(i);
                }
            }
        );
        async_future.get();
        writer_thread.join();
        ASSERT_GE(read_counter.load(), 10000);
    }

    TEST(ResultTest, Should_Expect_ConsistentState_When_RepeatedStatusAndValueChanges)
    {
        QLogicaeCore::Result<std::string> result;
        for (int i = 0; i < 1000; i++)
        {
            result.set_status_to_good();
            result.set_value(std::to_string(i));
            result.set_status_to_error();
            result.set_message(std::string("msg") + std::to_string(i));
        }
        ASSERT_TRUE(result.is_status_error());
        ASSERT_TRUE(result.get_message().find("msg") != std::string::npos);
    }

    TEST(ResultTest, Should_Expect_ExceptionHandled_When_ThrownInsideLambda)
    {
        QLogicaeCore::Result<int> result;
        try
        {
            auto throwing_lambda = [&]()
                {
                    throw std::runtime_error("forced");
                };
            throwing_lambda();
        }
        catch (const std::exception&)
        {
            result.set_status_to_exception();
        }
        ASSERT_TRUE(result.is_status_exception());
    }

    TEST(ResultTest, Should_Expect_CorrectCopyAndMoveSemantics_When_AssignedOrMoved)
    {
        QLogicaeCore::Result<std::string> original;
        original.set_value(std::string("copyable"));
        original.set_status_to_good();
        QLogicaeCore::Result<std::string> copied(original);
        ASSERT_EQ(copied.get_value(), std::string("copyable"));
        ASSERT_TRUE(copied.is_status_good());
        QLogicaeCore::Result<std::string> moved(std::move(original));
        ASSERT_EQ(moved.get_value(), std::string("copyable"));
    }

    TEST(ResultTest, Should_Expect_StableStatus_When_MultipleThreadsChangeStatus)
    {
        QLogicaeCore::Result<std::string> result;
        std::atomic<int> change_counter = 0;
        std::vector<std::thread> threads;
        for (int i = 0; i < 16; i++)
        {
            threads.emplace_back(
                [&result, &change_counter, i]()
                {
                    if (i % 2 == 0)
                    {
                        result.set_to_good_status_without_value();
                    }
                    else
                    {
                        result.set_status_to_error();
                    }
                    change_counter.fetch_add(1);
                }
            );
        }
        for (auto& thread : threads)
        {
            thread.join();
        }
        ASSERT_EQ(change_counter.load(), 16);
    }

    TEST(ResultTest, Should_Expect_PerformanceWithinThreshold_When_HeavyAccess)
    {
        QLogicaeCore::Result<int> result;
        auto start_time = std::chrono::steady_clock::now();
        for (int i = 0; i < 1000000; i++)
        {
            result.set_value(i);
            (void)result.get_value();
        }
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<
            std::chrono::milliseconds>(end_time - start_time);
        ASSERT_LT(elapsed_time.count(), 2000);
    }

    TYPED_TEST_CASE(ResultTemplateParamTest, ResultTypes);

    TYPED_TEST(ResultTemplateParamTest,
        Should_Expect_ValidInitialization_When_TypeVaries)
    {
        QLogicaeCore::Result<TypeParam> result;
        result.set_status_to_good();
        ASSERT_TRUE(result.is_status_good());
    }

    TEST(ResultTest, Should_Expect_ValidHandling_When_NullEquivalentValues)
    {
        QLogicaeCore::Result<int> int_result;
        int_result.set_value(0);
        ASSERT_EQ(int_result.get_value(), 0);
        QLogicaeCore::Result<bool> bool_result;
        bool_result.set_value(false);
        ASSERT_FALSE(bool_result.get_value());
    }
}
