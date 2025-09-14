#include "pch.h"

#include "abstract_result.hpp"

namespace QLogicaeCoreTest
{
    using QLogicaeCore::AbstractResult;

    template <typename ValueType, typename MetaDataType = std::string>
    class MockResult : public AbstractResult<ValueType, MetaDataType>
    {
    public:
        MockResult(
            bool state,
            std::optional<ValueType> value = std::nullopt,
            std::optional<MetaDataType> metadata = std::nullopt
        ) : AbstractResult<ValueType, MetaDataType>(state, value, metadata)
        {
        }

        MockResult(MockResult&&) noexcept = default;
        MockResult& operator=(MockResult&&) noexcept = default;

        MockResult(const MockResult&) = delete;
        MockResult& operator=(const MockResult&) = delete;
    };

    class AbstractResultTest : public ::testing::TestWithParam<
        std::tuple<bool, std::optional<int>, std::optional<std::string>>>
    {
    };

    TEST_P(AbstractResultTest, Should_Expect_CorrectValues_When_Constructed)
    {
        const bool status = std::get<0>(GetParam());
        const std::optional<int>& value = std::get<1>(GetParam());
        const std::optional<std::string>& metadata = std::get<2>(GetParam());

        MockResult<int> result(status, value, metadata);

        EXPECT_EQ(result.is_status_good(), status);
        EXPECT_EQ(result.has_value(), value.has_value());
        EXPECT_EQ(result.has_metadata(), metadata.has_value());
        EXPECT_EQ(result.get_value(), value);
        EXPECT_EQ(result.get_metadata(), metadata);
    }

    INSTANTIATE_TEST_CASE_P(
        AbstractResultTest,
        AbstractResultTest,
        ::testing::Values(
            std::make_tuple(false, std::nullopt, std::nullopt),
            std::make_tuple(true, std::nullopt, std::nullopt),
            std::make_tuple(false, 123, std::nullopt),
            std::make_tuple(true, std::nullopt, std::string("meta")),
            std::make_tuple(true, 456, std::string("meta"))
        )
    );

    TEST(AbstractResultTest, Should_Expect_CorrectBehavior_When_Asynchronous)
    {
        std::promise<MockResult<int>> promise;
        std::future<MockResult<int>> future = promise.get_future();

        std::thread thread_instance([&promise]() {
            MockResult<int> result(true, 999, "async_metadata");
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            promise.set_value(std::move(result));
            });

        MockResult<int> result = future.get();

        EXPECT_TRUE(result.is_status_good());
        EXPECT_TRUE(result.has_value());
        EXPECT_TRUE(result.has_metadata());
        EXPECT_EQ(result.get_value().value(), 999);
        EXPECT_EQ(result.get_metadata().value(), "async_metadata");

        thread_instance.join();
    }

    TEST(AbstractResultTest, Should_Expect_CorrectBehavior_When_Multithreaded)
    {
        constexpr int thread_count = 64;
        std::vector<std::thread> threads;
        std::vector<std::optional<MockResult<int>>> results(thread_count);

        for (int index = 0; index < thread_count; ++index)
        {
            threads.emplace_back([index, &results]() {
                MockResult<int> result(true, index, "meta_" + std::to_string(index));
                results[index].emplace(true, index, "meta_" + std::to_string(index));
                });
        }

        for (std::thread& thread : threads)
        {
            thread.join();
        }

        for (int index = 0; index < thread_count; ++index)
        {
            ASSERT_TRUE(results[index].has_value());
            const MockResult<int>& result = results[index].value();
            EXPECT_TRUE(result.is_status_good());
            EXPECT_TRUE(result.has_value());
            EXPECT_TRUE(result.has_metadata());
            EXPECT_EQ(result.get_value().value(), index);
            EXPECT_EQ(result.get_metadata().value(),
                "meta_" + std::to_string(index));
        }
    }

    TEST(AbstractResultTest, Should_Expect_ValidState_When_StressTested)
    {
        constexpr int limit = 100000;
        for (int index = 0; index < limit; ++index)
        {
            MockResult<int> result(index % 2 == 0, index, "meta");
            EXPECT_EQ(result.get_value().value(), index);
        }
    }

    TEST(AbstractResultTest, Should_Expect_NoThrow_When_ConstructedWithEdgeCases)
    {
        EXPECT_NO_THROW((MockResult<int>(false)));
        EXPECT_NO_THROW((MockResult<int>(true)));
        EXPECT_NO_THROW((MockResult<int>(true, std::nullopt, std::nullopt)));
        EXPECT_NO_THROW((MockResult<int>(false, -1, "negative")));
    }

    TEST(AbstractResultTest, Should_Expect_CompleteUnderLimit_When_PerformanceTested)
    {
        auto start_time = std::chrono::high_resolution_clock::now();

        for (int index = 0; index < 500000; ++index)
        {
            MockResult<int> result(true, index, "perf");
            EXPECT_TRUE(result.has_value());
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;

        ASSERT_LT(elapsed.count(), 2.0);
    }
}

