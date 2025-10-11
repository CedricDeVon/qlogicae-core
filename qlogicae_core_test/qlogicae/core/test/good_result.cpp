#include "pch.hpp"

#include "qlogicae/core/good_result.hpp"

namespace QLogicaeCoreTest
{
    using QLogicaeCore::GoodResult;

    class GoodResultTest : public ::testing::TestWithParam<
        std::tuple<std::optional<int>, std::optional<std::string>>>
    {
    };

    class GoodResultPerformanceTest : public ::testing::Test
    {
    };

    TEST_P(GoodResultTest, Should_Expect_CorrectState_When_Initialized)
    {
        const std::optional<int>& value = std::get<0>(GetParam());
        const std::optional<std::string>& metadata = std::get<1>(GetParam());

        GoodResult<int, std::string> good_result(value, metadata);

        EXPECT_TRUE(good_result.is_status_good());
        EXPECT_EQ(good_result.get_value(), value);
        EXPECT_EQ(good_result.get_metadata(), metadata);
        EXPECT_EQ(good_result.has_value(), value.has_value());
        EXPECT_EQ(good_result.has_metadata(), metadata.has_value());
    }

    INSTANTIATE_TEST_CASE_P(
        GoodResultTest,
        GoodResultTest,
        ::testing::Values(
            std::make_tuple(std::nullopt, std::nullopt),
            std::make_tuple(42, std::nullopt),
            std::make_tuple(std::nullopt, std::string("info")),
            std::make_tuple(42, std::string("info"))
        )
    );

    TEST(GoodResultTest, Should_Expect_CorrectBehavior_When_Multithreaded)
    {
        std::vector<std::thread> thread_pool;
        std::vector<GoodResult<int>> results;
        results.reserve(100);

        for (int index = 0; index < 100; ++index)
        {
            results.emplace_back(index, "meta_" + std::to_string(index));
        }

        for (std::thread& thread_instance : thread_pool) {
            thread_instance.join();
        }

        for (int index = 0; index < 100; ++index) {
            EXPECT_TRUE(results[index].has_value());
            EXPECT_TRUE(results[index].has_metadata());
            EXPECT_EQ(results[index].get_value().value(), index);
            EXPECT_EQ(results[index].get_metadata().value(), "meta_" + std::to_string(index));
        }
    }

    TEST(GoodResultTest, Should_Expect_CorrectBehavior_When_StressTested)
    {
        constexpr int iteration_count = 100000;
        for (int index = 0; index < iteration_count; ++index) {
            GoodResult<int> good_result(index, "meta");
            ASSERT_TRUE(good_result.has_value());
            ASSERT_EQ(good_result.get_value().value(), index);
        }
    }

    TEST(GoodResultTest, Should_Expect_NoThrow_When_ConstructingEdgeCases)
    {
        EXPECT_NO_THROW((GoodResult<int>()));
        EXPECT_NO_THROW((GoodResult<int>(std::nullopt, std::nullopt)));
        EXPECT_NO_THROW((GoodResult<int>(std::nullopt, "edge")));
        EXPECT_NO_THROW((GoodResult<int>(100, std::nullopt)));
    }

    TEST_F(GoodResultPerformanceTest, Should_Expect_CompleteUnderLimit_When_PerformanceTested)
    {
        auto start_time = std::chrono::high_resolution_clock::now();

        for (int index = 0; index < 500000; ++index) {
            GoodResult<int> good_result(index, "perf");
            ASSERT_TRUE(good_result.has_value());
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;

        ASSERT_LT(duration.count(), 2.0);
    }
}
