#include "pch.hpp"

#include "qlogicae_core/includes/bad_result.hpp"

namespace QLogicaeCoreTest
{
    using QLogicaeCore::BadResult;

    class BadResultTest : public ::testing::TestWithParam<
        std::tuple<std::optional<int>, std::optional<std::string>>>
    {
    };

    class BadResultPerformanceTest : public ::testing::Test
    {
    };

    TEST_P(BadResultTest, Should_Expect_CorrectState_When_Initialized)
    {
        const std::optional<int>& value = std::get<0>(GetParam());
        const std::optional<std::string>& metadata = std::get<1>(GetParam());

        BadResult<int, std::string> bad_result(value, metadata);

        EXPECT_FALSE(bad_result.is_status_good());
        EXPECT_EQ(bad_result.get_value(), value);
        EXPECT_EQ(bad_result.get_metadata(), metadata);
        EXPECT_EQ(bad_result.has_value(), value.has_value());
        EXPECT_EQ(bad_result.has_metadata(), metadata.has_value());
    }

    INSTANTIATE_TEST_CASE_P(
        BadResultTest,
        BadResultTest,
        ::testing::Values(
            std::make_tuple(std::nullopt, std::nullopt),
            std::make_tuple(0, std::nullopt),
            std::make_tuple(std::nullopt, std::string("error")),
            std::make_tuple(-1, std::string("invalid"))
        )
    );

    TEST(BadResultTest, Should_Expect_CorrectBehavior_When_Multithreaded)
    {
        constexpr int thread_count = 100;
        std::vector<std::thread> thread_pool;
        std::vector<std::optional<BadResult<int>>> results(thread_count);

        for (int index = 0; index < thread_count; ++index)
        {
            thread_pool.emplace_back([index, &results]() {
                results[index].emplace(index, "error_" + std::to_string(index));
                });
        }

        for (std::thread& thread_instance : thread_pool)
        {
            thread_instance.join();
        }

        for (int index = 0; index < thread_count; ++index)
        {
            ASSERT_TRUE(results[index].has_value());
            BadResult<int>& result = results[index].value();
            EXPECT_FALSE(result.is_status_good());
            EXPECT_TRUE(result.has_value());
            EXPECT_TRUE(result.has_metadata());
            EXPECT_EQ(result.get_value().value(), index);
            EXPECT_EQ(result.get_metadata().value(),
                "error_" + std::to_string(index));
        }
    }

    TEST(BadResultTest, Should_Expect_CorrectBehavior_When_StressTested)
    {
        constexpr int iteration_count = 100000;
        for (int index = 0; index < iteration_count; ++index)
        {
            BadResult<int> bad_result(index, "stress");
            ASSERT_FALSE(bad_result.is_status_good());
            ASSERT_EQ(bad_result.get_value().value(), index);
        }
    }

    TEST(BadResultTest, Should_Expect_NoThrow_When_ConstructingEdgeCases)
    {
        EXPECT_NO_THROW((BadResult<int>()));
        EXPECT_NO_THROW((BadResult<int>(std::nullopt, std::nullopt)));
        EXPECT_NO_THROW((BadResult<int>(std::nullopt, "edge")));
        EXPECT_NO_THROW((BadResult<int>(-100, std::nullopt)));
    }

    TEST_F(BadResultPerformanceTest, Should_Expect_CompleteUnderLimit_When_PerformanceTested)
    {
        auto start_time = std::chrono::high_resolution_clock::now();

        for (int index = 0; index < 500000; ++index)
        {
            BadResult<int> bad_result(index, "perf");
            ASSERT_FALSE(bad_result.is_status_good());
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;

        ASSERT_LT(duration.count(), 2.0);
    }
}

