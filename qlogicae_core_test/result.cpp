#include "pch.hpp"

#include "result.hpp"

namespace QLogicaeCoreTest
{
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

    TEST_F(ResultStringTest, Should_SetAndGetSuccess_When_UsingSetToSuccess)
    {
        result.set_to_success();
        EXPECT_TRUE(result.get_is_successful());

        std::string sample_data = "test";
        result.set_to_success(sample_data);

        std::string retrieved_data;
        result.get_data(retrieved_data);
        EXPECT_EQ(retrieved_data, sample_data);
    }

    TEST_F(ResultStringTest, Should_SetAndGetFailure_When_UsingSetToFailure)
    {
        result.set_to_failure();
        EXPECT_FALSE(result.get_is_successful());

        std::string sample_data = "fail";
        result.set_to_failure(sample_data);

        std::string retrieved_data;
        result.get_data(retrieved_data);
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
        auto async_task = std::async(std::launch::async, [this]()
            {
                result.set_to_failure();
                return result.get_is_successful();
            });

        EXPECT_FALSE(async_task.get());
    }

    TEST_F(ResultStringTest, Should_BeThreadSafe_UnderConcurrentModification)
    {
        std::atomic<int> success_count = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < 50; ++i)
        {
            threads.emplace_back([this, &success_count]()
                {
                    result.set_to_success();
                    if (result.get_is_successful())
                        success_count.fetch_add(1);
                });
        }

        for (auto& thread : threads)
            thread.join();

        EXPECT_EQ(success_count.load(), 50);
    }

    TEST_F(ResultStringTest, Should_PerformUnderStress)
    {
        auto start_time = std::chrono::steady_clock::now();
        std::vector<std::thread> threads;

        for (int i = 0; i < 200; ++i)
        {
            threads.emplace_back([this]()
                {
                    result.set_to_success();
                    result.set_to_failure();
                });
        }

        for (auto& t : threads)
            t.join();

        auto end_time = std::chrono::steady_clock::now();
        EXPECT_LE(
            std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time)
            .count(), 2
        );
    }

    TEST_F(ResultStringTest, Should_HandleEdgeCase_When_EmptyData)
    {
        std::string empty_data;
        result.set_to_success(empty_data);

        std::string retrieved_data;
        result.get_data(retrieved_data);
        EXPECT_EQ(retrieved_data, empty_data);
    }

    TEST_F(ResultIntTest, Should_SetAndGetSuccess_When_UsingSetToSuccess)
    {
        result.set_to_success();
        EXPECT_TRUE(result.get_is_successful());

        result.set_to_success(42);
        int value;
        result.get_data(value);
        EXPECT_EQ(value, 42);
    }

    TEST_F(ResultIntTest, Should_SetAndGetFailure_When_UsingSetToFailure)
    {
        result.set_to_failure();
        EXPECT_FALSE(result.get_is_successful());

        result.set_to_failure(7);
        int value;
        result.get_data(value);
        EXPECT_EQ(value, 7);
    }

    TEST_F(ResultIntTest, Should_HandleAsyncOperations)
    {
        auto async_task = std::async(std::launch::async, [this]()
            {
                result.set_to_failure();
                return result.get_is_successful();
            });
        EXPECT_FALSE(async_task.get());
    }

    TEST_F(ResultIntTest, Should_PerformUnderStress)
    {
        auto start_time = std::chrono::steady_clock::now();
        std::vector<std::thread> threads;
        for (int i = 0; i < 200; ++i)
        {
            threads.emplace_back([this]()
                {
                    result.set_to_success();
                    result.set_to_failure();
                });
        }
        for (auto& t : threads)
            t.join();

        auto end_time = std::chrono::steady_clock::now();
        EXPECT_LE(
            std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time)
            .count(), 2
        );
    }

    TEST_F(ResultDoubleTest, Should_SetAndGetSuccess_When_UsingSetToSuccess)
    {
        result.set_to_success();
        EXPECT_TRUE(result.get_is_successful());

        result.set_to_success(3.14);
        double value;
        result.get_data(value);
        EXPECT_DOUBLE_EQ(value, 3.14);
    }

    TEST_F(ResultDoubleTest, Should_SetAndGetFailure_When_UsingSetToFailure)
    {
        result.set_to_failure();
        EXPECT_FALSE(result.get_is_successful());

        result.set_to_failure(2.71);
        double value;
        result.get_data(value);
        EXPECT_DOUBLE_EQ(value, 2.71);
    }

    TEST_F(ResultDoubleTest, Should_HandleAsyncOperations)
    {
        auto async_task = std::async(std::launch::async, [this]()
            {
                result.set_to_failure();
                return result.get_is_successful();
            });
        EXPECT_FALSE(async_task.get());
    }

    TEST_F(ResultVoidTest, Should_SetAndGetSuccess)
    {
        result.set_to_success();
        EXPECT_TRUE(result.get_is_successful());

        result.set_to_failure();
        EXPECT_FALSE(result.get_is_successful());
    }

    TEST_F(ResultVoidTest, Should_HandleAsyncOperations)
    {
        auto async_task = std::async(std::launch::async, [this]()
            {
                result.set_to_failure();
                return result.get_is_successful();
            });
        EXPECT_FALSE(async_task.get());
    }
}
