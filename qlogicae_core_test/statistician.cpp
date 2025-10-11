#include "pch.h"

#include "qlogicae_core/statistician.hpp"

namespace QLogicaeCoreTest
{
    class StatisticianIsValidDataTest
        : public ::testing::TestWithParam<std::pair<std::vector<std::vector<double>>, bool>>
    {
    protected:
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();
    };

    class StatisticianMedianTest
        : public ::testing::TestWithParam<std::pair<std::vector<double>, double>>
    {
    protected:
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();
    };

    class StatisticianOutlierPresentTest : public
        ::testing::TestWithParam<std::vector<std::vector<double>>>
    {
    protected:
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();

        QLogicaeCore::OutlierRemovalOptions valid_options{
            .factor = 1.5,
            .threshold = 3.0,
            .proportion = 0.26,
            .significance_level = 0.05
        };
    };

    class StatisticianNoOutlierTest :
        public ::testing::TestWithParam<std::vector<std::vector<double>>>
    {
    protected:
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();

        QLogicaeCore::OutlierRemovalOptions valid_options{
            .factor = 1.5,
            .threshold = 3.0,
            .proportion = 0.26,
            .significance_level = 0.05
        };
    };

    class StatisticianAsyncTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();

        QLogicaeCore::OutlierRemovalOptions options{
            .factor = 1.5,
            .threshold = 2.5,
            .proportion = 0.25,
            .significance_level = 0.05
        };
    };

    class StatisticianAsyncHelpersTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();
    };

    class StatisticianAsyncBenchmarkTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();
    };

    TEST_F(StatisticianAsyncHelpersTest, IsValidDataAsync_Valid)
    {
        std::vector<std::vector<double>> data = { {1.0, 2.0}, {3.0, 4.0} };
        auto result = statistician.is_valid_data_async(data);
        EXPECT_TRUE(result.get());
    }

    TEST_F(StatisticianAsyncHelpersTest, IsValidDataAsync_Empty)
    {
        std::vector<std::vector<double>> data;
        auto result = statistician.is_valid_data_async(data);
        EXPECT_FALSE(result.get());
    }

    TEST_F(StatisticianAsyncHelpersTest, IsValidDataAsync_NaN)
    {
        std::vector<std::vector<double>> data =
        { {1.0, std::numeric_limits<double>::quiet_NaN()} };
        auto result = statistician.is_valid_data_async(data);
        EXPECT_FALSE(result.get());
    }

    TEST_F(StatisticianAsyncHelpersTest, ComputeMedianAsync_Odd)
    {
        std::vector<double> values = { 3.0, 1.0, 2.0 };
        auto future = statistician.compute_median_async(values);
        EXPECT_DOUBLE_EQ(future.get(), 2.0);
    }

    TEST_F(StatisticianAsyncHelpersTest, ComputeMedianAsync_Even)
    {
        std::vector<double> values = { 4.0, 2.0, 1.0, 3.0 };
        auto future = statistician.compute_median_async(values);
        EXPECT_DOUBLE_EQ(future.get(), 2.5);
    }

    TEST_F(StatisticianAsyncHelpersTest, ComputeMedianAsync_Empty)
    {
        std::vector<double> values = {};
        auto future = statistician.compute_median_async(values);
        EXPECT_TRUE(std::isnan(future.get()));
    }

    TEST_F(StatisticianAsyncHelpersTest, ComputeMeanAsync_Valid)
    {
        std::vector<double> values = { 1.0, 2.0, 3.0 };
        auto future = statistician.compute_mean_async(values);
        EXPECT_DOUBLE_EQ(future.get(), 2.0);
    }

    TEST_F(StatisticianAsyncHelpersTest, ComputeMeanAsync_Empty)
    {
        std::vector<double> values;
        auto future = statistician.compute_mean_async(values);
        EXPECT_TRUE(std::isnan(future.get()));
    }

    TEST_F(StatisticianAsyncHelpersTest, ComputeStandardDeviationAsync_Valid)
    {
        std::vector<double> values = { 1.0, 2.0, 3.0 };
        double mean = 2.0;
        auto future =
            statistician.compute_standard_deviation_async(values, mean);
        EXPECT_NEAR(future.get(), std::sqrt(2.0 / 3.0), 1e-6);
    }

    TEST_F(StatisticianAsyncHelpersTest, ComputeStandardDeviationAsync_Empty)
    {
        std::vector<double> values;
        auto future =
            statistician.compute_standard_deviation_async(values, 0.0);
        EXPECT_TRUE(std::isnan(future.get()));
    }

    TEST_F(StatisticianAsyncBenchmarkTest, Async_ShouldExecuteConcurrently)
    {
        std::vector<std::vector<double>> data1(
            1000, std::vector<double>(100, 1.0));
        std::vector<std::vector<double>> data2(
            1000, std::vector<double>(100, 2.0));
        std::vector<std::vector<double>> data3(
            1000, std::vector<double>(100, 3.0));
        std::vector<double> flat(100000, 4.0);

        auto start = std::chrono::high_resolution_clock::now();

        auto f1 = statistician.is_valid_data_async(data1);
        auto f2 = statistician.flatten_data_async(data2);
        auto f3 = statistician.compute_mean_async(flat);
        auto f4 = statistician.compute_standard_deviation_async(flat, 4.0);

        f1.get();
        f2.get();
        f3.get();
        f4.get();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start).count();

        EXPECT_LT(duration_ms, 100);  
    }

    TEST_F(StatisticianAsyncBenchmarkTest, RepeatedAsyncCalls_ShouldRemainStable)
    {
        for (int i = 0; i < 100; ++i)
        {
            std::vector<std::vector<double>> data = { {1.0 * i, 2.0, 3.0, 100.0} };
            auto f1 = statistician.is_valid_data_async(data);
            auto f2 = statistician.flatten_data_async(data);

            EXPECT_TRUE(f1.get());
            EXPECT_EQ(f2.get().size(), 4);
        }
    }

    TEST_F(StatisticianAsyncBenchmarkTest, ComputeAsync_LargeInputAccuracy)
    {
        std::vector<double> values(100000, 5.0);
        values.push_back(1000.0);  

        auto f_median = statistician.compute_median_async(values);
        auto f_mean = statistician.compute_mean_async(values);
        auto f_stddev = statistician.compute_standard_deviation_async(values, 5.0);

        EXPECT_NEAR(f_median.get(), 5.0, 1e-6);
        EXPECT_NEAR(f_mean.get(), 5.009995, 1e-3);
        EXPECT_GT(f_stddev.get(), 0.0);
    }

    TEST_F(StatisticianAsyncBenchmarkTest, ComputeAsync_ShouldHandleInvalidInputGracefully)
    {
        std::vector<double> empty;
        auto f1 = statistician.compute_median_async(empty);
        auto f2 = statistician.compute_mean_async(empty);
        auto f3 = statistician.compute_standard_deviation_async(empty, 0.0);

        EXPECT_TRUE(std::isnan(f1.get()));
        EXPECT_TRUE(std::isnan(f2.get()));
        EXPECT_TRUE(std::isnan(f3.get()));
    }

    TEST_P(StatisticianIsValidDataTest, Should_Return_Correct_Validity)
    {
        auto [input, expected] = GetParam();
        EXPECT_EQ(statistician.is_valid_data(input), expected);
    }

    INSTANTIATE_TEST_CASE_P(
        StatisticianValidityCases,
        StatisticianIsValidDataTest,
        ::testing::Values(
            std::make_pair(std::vector<std::vector<double>>{}, false),
            std::make_pair(std::vector<std::vector<double>>{{}}, false),
            std::make_pair(std::vector<std::vector<double>>{{1.0, 2.0}, {}}, false),
            std::make_pair(std::vector<std::vector<double>>{{1.0, NAN}}, false),
            std::make_pair(std::vector<std::vector<double>>{{INFINITY}}, false),
            std::make_pair(std::vector<std::vector<double>>{{1.0, 2.0, 3.0}}, true)
        )
    );

    TEST(StatisticianFlattenDataTest, Should_Flatten_Matrix_Correctly)
    {
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();

        std::vector<std::vector<double>> input = {
            {1.0, 2.0},
            {3.0},
            {4.0, 5.0}
        };

        std::vector<double> expected = { 1.0, 2.0, 3.0, 4.0, 5.0 };

        EXPECT_EQ(statistician.flatten_data(input), expected);
    }

    TEST_P(StatisticianMedianTest, Should_Compute_Median_Correctly)
    {
        auto [values, expected] = GetParam();
        double result = statistician.compute_median(values);

        if (std::isnan(expected))
        {
            EXPECT_TRUE(std::isnan(result));
        }
        else
        {
            EXPECT_NEAR(result, expected, 1e-9);
        }
    }

    INSTANTIATE_TEST_CASE_P(
        StatisticianMedianCases,
        StatisticianMedianTest,
        ::testing::Values(
            std::make_pair(std::vector<double>{}, NAN),
            std::make_pair(std::vector<double>{5.0}, 5.0),
            std::make_pair(std::vector<double>{5.0, 3.0}, 4.0),
            std::make_pair(std::vector<double>{1.0, 2.0, 3.0}, 2.0),
            std::make_pair(std::vector<double>{3.0, 1.0, 4.0, 2.0}, 2.5)
        )
    );

    TEST(StatisticianMeanTest, Should_Compute_Mean_Correctly)
    {
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();

        std::vector<double> values = { 1.0, 2.0, 3.0 };
        double expected = 2.0;

        EXPECT_NEAR(statistician.compute_mean(values), expected, 1e-9);
    }

    TEST(StatisticianMeanTest, Should_Return_NaN_On_Empty_Input)
    {
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();
        std::vector<double> values;
        EXPECT_TRUE(std::isnan(statistician.compute_mean(values)));
    }

    TEST(StatisticianStdDevTest, Should_Compute_StdDev_Correctly)
    {
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();

        std::vector<double> values = { 2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0 };
        double mean = statistician.compute_mean(values);
        double expected = 2.0;

        EXPECT_NEAR(statistician.compute_standard_deviation(values, mean), expected, 1e-9);
    }

    TEST(StatisticianStdDevTest, Should_Return_NaN_On_Empty)
    {
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();
        std::vector<double> values;
        EXPECT_TRUE(std::isnan(statistician.compute_standard_deviation(values, 0.0)));
    }

    INSTANTIATE_TEST_CASE_P(
        WinsorizingCases,
        StatisticianOutlierPresentTest,
        ::testing::Values(
            std::vector<std::vector<double>>{{10.0, 10.1, 10.2, 100.0}},
            std::vector<std::vector<double>>{{-5.0, -4.0, -3.0, 20.0}}
        )
    );

    INSTANTIATE_TEST_CASE_P(
        NoOutlierCases,
        StatisticianNoOutlierTest,
        ::testing::Values(
            std::vector<std::vector<double>>{{1.0, 2.0, 3.0}}
        )
    );

    TEST_P(StatisticianOutlierPresentTest,
        Should_Return_True_When_Winsorizing_OutlierPresent)
    {
        auto data = GetParam();
        EXPECT_TRUE(
            statistician.remove_outliers_via_winsorizing(data, valid_options)
        );
    }

    TEST_P(StatisticianOutlierPresentTest,
        Should_Return_True_When_Trimmed_Mean_OutlierPresent)
    {
        auto data = GetParam();
        EXPECT_TRUE(
            statistician.remove_outliers_via_trimmed_mean(data, valid_options)
        );
    }

    TEST_P(StatisticianOutlierPresentTest,
        Should_Return_True_When_Median_Absolute_Deviation_Valid)
    {
        auto data = GetParam();
        EXPECT_TRUE(
            statistician.remove_outliers_via_median_absolute_deviation(
                data, valid_options
            )
        );
    }

    TEST_P(StatisticianOutlierPresentTest,
        Should_Return_True_When_IQR_Valid)
    {
        auto data = GetParam();
        EXPECT_TRUE(
            statistician.remove_outliers_via_inter_quartile_range(
                data, valid_options
            )
        );
    }

    TEST_P(StatisticianOutlierPresentTest,
        Should_Return_True_When_ZScore_Valid)
    {
        auto data = GetParam();
        EXPECT_TRUE(
            statistician.remove_outliers_via_z_score(data, valid_options)
        );
    }

    TEST_P(StatisticianOutlierPresentTest,
        Should_Return_True_When_Grubbs_Valid)
    {
        auto data = GetParam();
        EXPECT_TRUE(
            statistician.remove_outliers_via_grubbs_test(data, valid_options)
        );
    }

    TEST_P(StatisticianOutlierPresentTest,
        Should_Return_True_When_Tukey_Valid)
    {
        auto data = GetParam();
        EXPECT_TRUE(
            statistician.remove_outliers_via_tukey(data, valid_options)
        );
    }

    TEST_P(StatisticianOutlierPresentTest,
        Should_Return_True_When_Modified_ZScore_Valid)
    {
        auto data = GetParam();
        EXPECT_TRUE(
            statistician.remove_outliers_via_modified_z_score(data, valid_options)
        );
    }

    TEST_P(StatisticianNoOutlierTest,
        Should_Return_False_When_Winsorizing_NoOutlier)
    {
        auto data = GetParam();
        EXPECT_FALSE(
            statistician.remove_outliers_via_winsorizing(data, valid_options)
        );
    }

    TEST_P(StatisticianNoOutlierTest,
        Should_Return_False_When_Trimmed_Mean_NoOutlier)
    {
        auto data = GetParam();
        EXPECT_FALSE(
            statistician.remove_outliers_via_trimmed_mean(data, valid_options)
        );
    }

    TEST_F(StatisticianAsyncTest, MedianAbsoluteDeviationAsync)
    {
        std::vector<std::vector<double>> data = { {10, 10, 11, 100} };
        auto future = statistician.remove_outliers_via_median_absolute_deviation_async(data, options);

        EXPECT_TRUE(future.get());
        EXPECT_LT(data[0].size(), 4);
        EXPECT_TRUE(std::all_of(data[0].begin(), data[0].end(), [](double v) { return v != 100.0; }));
    }
    
    TEST_F(StatisticianAsyncTest, IQRAsync)
    {
        std::vector<std::vector<double>> data = { {1, 2, 3, 100} };
        options.factor = 0.5;
        
        auto future = statistician.remove_outliers_via_inter_quartile_range_async(data, options);        

        EXPECT_TRUE(future.get());
        EXPECT_LT(data[0].size(), 4);
        EXPECT_TRUE(std::find(data[0].begin(), data[0].end(), 100.0) == data[0].end());
    }
    
    TEST_F(StatisticianAsyncTest, ZScoreAsync)
    {
        std::vector<std::vector<double>> data = { {1.0, 1.1, 1.2, 20.0} };

        options.threshold = 1.5;
        auto future = statistician.remove_outliers_via_z_score_async(data, options);

        EXPECT_TRUE(future.get());
        EXPECT_LT(data[0].size(), 4);
        EXPECT_TRUE(std::none_of(data[0].begin(), data[0].end(), [](double v) { return v == 20.0; }));
    }
    
    TEST_F(StatisticianAsyncTest, WinsorizingAsync_ExpectedOutput)
    {
        std::vector<std::vector<double>> data = { {1.0, 2.0, 3.0, 100.0} };
        auto future = statistician.remove_outliers_via_winsorizing_async(data, options);

        EXPECT_TRUE(future.get());
        std::vector<double> expected = { 2.0, 2.0, 3.0, 3.0 };  
        EXPECT_EQ(data[0], expected);
    }
    
    TEST_F(StatisticianAsyncTest, TrimmedMeanAsync)
    {
        std::vector<std::vector<double>> data = { {1.0, 2.0, 3.0, 100.0} };
        auto future = statistician.remove_outliers_via_trimmed_mean_async(data, options);

        EXPECT_TRUE(future.get());
        EXPECT_EQ(data[0], std::vector<double>({ 2.0, 3.0 }));
    }
    
    TEST_F(StatisticianAsyncTest, GrubbsTestAsync)
    {
        std::vector<std::vector<double>> data = { {1.0, 1.1, 1.2, 10.0} };
        auto future = statistician.remove_outliers_via_grubbs_test_async(data, options);

        EXPECT_TRUE(future.get());
        
        EXPECT_EQ(data[0].size(), 4);
    }

    TEST_F(StatisticianAsyncTest, TukeyAsync)
    {
        std::vector<std::vector<double>> data = {
            {1.0, 1.1, 1.2, 1.3, 100.0}
        };

        options.factor = 0.5;

        auto future = statistician.remove_outliers_via_tukey_async(data, options);

        EXPECT_TRUE(future.get());
        EXPECT_LT(data[0].size(), 5);
        EXPECT_FALSE(std::any_of(data[0].begin(), data[0].end(),
            [](double v) { return v == 100.0; }));
    }

    TEST_F(StatisticianAsyncTest, ModifiedZScoreAsync)
    {
        std::vector<std::vector<double>> data = { {10.0, 10.2, 10.3, 50.0} };
        auto future = statistician.remove_outliers_via_modified_z_score_async(data, options);

        EXPECT_TRUE(future.get());
        EXPECT_LT(data[0].size(), 4);
        EXPECT_TRUE(std::none_of(data[0].begin(), data[0].end(), [](double v) { return v == 50.0; }));
    }

    TEST(StatisticianEdgeTest, Should_Return_False_On_Empty)
    {
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();
        QLogicaeCore::OutlierRemovalOptions options{ 1.5, 3.0, 0.1, 0.05 };
        std::vector<std::vector<double>> empty_data;

        ASSERT_FALSE(statistician.remove_outliers_via_z_score(
            empty_data, options
        ));
    }

    TEST_F(StatisticianAsyncTest, ZScoreAsync_EmptyData_ShouldFail)
    {
        std::vector<std::vector<double>> data;

        auto future = statistician.remove_outliers_via_z_score_async(
            data, options
        );

        EXPECT_FALSE(future.get());
    }

    TEST_F(StatisticianAsyncTest, MADAsync_InvalidThreshold_ShouldFail)
    {
        std::vector<std::vector<double>> data = {
            {10.0, 12.0, 14.0, 100.0}
        };

        QLogicaeCore::OutlierRemovalOptions bad_options = options;
        bad_options.threshold = 0.0;

        auto future =
            statistician.remove_outliers_via_median_absolute_deviation_async(
                data, bad_options
            );

        EXPECT_FALSE(future.get());
    }

    TEST_F(StatisticianAsyncTest, TrimmedMeanAsync_NoOutliers_ShouldFail)
    {
        std::vector<std::vector<double>> data = {
            {10.0, 10.1, 10.2, 10.3}
        };

        auto future = statistician.remove_outliers_via_trimmed_mean_async(
            data, options
        );

        EXPECT_FALSE(future.get());
    }

    TEST_F(StatisticianAsyncTest, MADAsync_ShouldNotThrow)
    {
        std::vector<std::vector<double>> data = {
            {10.0, 20.0, 30.0, 100.0}
        };

        EXPECT_NO_THROW({
            auto future = statistician
                .remove_outliers_via_median_absolute_deviation_async(
                    data, options
                );
            future.get();
            });
    }

    TEST_F(StatisticianAsyncTest, AsyncMethods_ShouldRunConcurrently)
    {
        options.threshold = 1.5; 
        options.factor = 0.5;
        options.proportion = 0.25;

        std::vector<std::vector<double>> d1 = { {1, 1.5, 2, 100} }; 
        std::vector<std::vector<double>> d2 = { {1, 2, 3, 100} };   
        std::vector<std::vector<double>> d3 = { {1, 1, 1, 100} };
        std::vector<std::vector<double>> d4 = { {1, 2, 3, 100} };   

        auto f1 = statistician.remove_outliers_via_median_absolute_deviation_async(d1, options);
        auto f2 = statistician.remove_outliers_via_trimmed_mean_async(d2, options);
        auto f3 = statistician.remove_outliers_via_inter_quartile_range_async(d3, options);
        auto f4 = statistician.remove_outliers_via_z_score_async(d4, options);

        EXPECT_TRUE(f1.get());
        EXPECT_TRUE(f2.get());
        EXPECT_TRUE(f3.get());
        EXPECT_TRUE(f4.get());

        EXPECT_LT(d1[0].size(), 4);
        EXPECT_LT(d2[0].size(), 4);
        EXPECT_LT(d3[0].size(), 4);
        EXPECT_LT(d4[0].size(), 4);

        EXPECT_TRUE(std::none_of(d1[0].begin(), d1[0].end(), [](double v) { return v == 100.0; }));
        EXPECT_TRUE(std::none_of(d4[0].begin(), d4[0].end(), [](double v) { return v == 100.0; }));
    }

    TEST_F(StatisticianAsyncTest, MADAsync_RemovesOutlier)
    {
        std::vector<std::vector<double>> data = {
            {10.0, 10.2, 10.3, 50.0}
        };

        auto future =
            statistician.remove_outliers_via_median_absolute_deviation_async(
                data, options
            );

        EXPECT_TRUE(future.get());
    }

    TEST_F(StatisticianAsyncTest, Should_Complete_Async_Methods_Under_2s)
    {
        QLogicaeCore::Statistician& statistician =
            QLogicaeCore::Statistician::get_instance();
        std::vector<std::vector<double>> input{ {1.0, 2.0, 3.0, 100.0} };
        QLogicaeCore::OutlierRemovalOptions options{ 1.5, 3.0, 0.1, 0.05 };

        auto start = std::chrono::steady_clock::now();

        std::future<bool> future = statistician
            .remove_outliers_via_grubbs_test_async(
                input, options
            );

        ASSERT_TRUE(future.wait_for(
            std::chrono::seconds(2)) != std::future_status::timeout);
        ASSERT_TRUE(future.get());

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        ASSERT_LT(elapsed.count(), 2.0);
    }
}
