#include "pch.hpp"

#include "placeholder_value_extractor.hpp"

namespace QLogicaeCoreTest
{
    class PlaceholderValueExtractorTest : public ::testing::TestWithParam<std::string>
    {
    protected:
        void SetUp() override {}
        void TearDown() override {}
    };

    TEST_P(PlaceholderValueExtractorTest, Should_Return_Value_When_Constructed)
    {
        std::string inputValue = GetParam();
        QLogicaeCore::PlaceholderValueExtractor extractor(inputValue);
        std::optional<std::string> value = extractor.get_value();
        ASSERT_TRUE(value.has_value());
        ASSERT_EQ(value.value(), inputValue);
    }

    TEST_P(PlaceholderValueExtractorTest, Should_Work_Asynchronously_When_Called_In_Async)
    {
        std::string inputValue = GetParam();
        std::future<std::optional<std::string>> futureValue =
            std::async(std::launch::async, [inputValue]() -> std::optional<std::string>
                {
                    QLogicaeCore::PlaceholderValueExtractor extractor(inputValue);
                    return extractor.get_value();
                });

        std::optional<std::string> result = futureValue.get();
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value(), inputValue);
    }

    TEST_P(PlaceholderValueExtractorTest, Should_Work_Concurrent_Access_When_Multithreaded)
    {
        std::string inputValue = GetParam();
        QLogicaeCore::PlaceholderValueExtractor extractor(inputValue);
        std::mutex accessMutex;
        std::vector<std::thread> threads;
        std::atomic<bool> ready(false);
        std::condition_variable startCondition;
        std::mutex startMutex;

        for (int index = 0; index < 10; ++index)
        {
            threads.emplace_back([&]() {
                std::unique_lock<std::mutex> lock(startMutex);
                startCondition.wait(lock, [&] { return ready.load(); });
                std::optional<std::string> result;
                {
                    std::lock_guard<std::mutex> guard(accessMutex);
                    result = extractor.get_value();
                }
                ASSERT_TRUE(result.has_value());
                ASSERT_EQ(result.value(), inputValue);
                });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
            std::lock_guard<std::mutex> lock(startMutex);
            ready.store(true);
        }
        startCondition.notify_all();

        for (std::thread& thread : threads)
        {
            thread.join();
        }
    }

    TEST_P(PlaceholderValueExtractorTest, Should_Not_Throw_When_Empty)
    {
        std::string inputValue = GetParam();
        ASSERT_NO_THROW({
            QLogicaeCore::PlaceholderValueExtractor extractor(inputValue);
            std::optional<std::string> value = extractor.get_value();
            ASSERT_TRUE(value.has_value());
            });
    }

    TEST(PlaceholderValueExtractorStressTest, Should_Complete_Under_Load_Within_Deadline)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int index = 0; index < 100000; ++index)
        {
            QLogicaeCore::PlaceholderValueExtractor extractor("Test");
            std::optional<std::string> value = extractor.get_value();
            ASSERT_TRUE(value.has_value());
            ASSERT_EQ(value.value(), "Test");
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        ASSERT_LT(duration.count(), 2);
    }

    INSTANTIATE_TEST_CASE_P(
        PlaceholderValueExtractorTestParameters,
        PlaceholderValueExtractorTest,
        ::testing::Values(
            "",
            "value",
            std::string(1024, 'a'),
            "value with spaces",
            "\0binary\0value",
            std::string("longvalue") + std::string(1000, 'x')
        )
    );
}

