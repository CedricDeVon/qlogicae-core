#pragma once

#include "pch.h"

#include "globals.hpp"

namespace QLogicaeCore
{
    struct OutlierRemovalOptions
    {
        double factor;
        double threshold;
        double proportion;
        double significance_level;
    };

    class Statistician
    {
    public:
        bool is_valid_data(std::vector<std::vector<double>>& data);
        
        std::vector<double> flatten_data(std::vector<std::vector<double>>& data);
        
        double compute_median(std::vector<double>& values);
        
        double compute_mean(std::vector<double>& values);
        
        double compute_standard_deviation(
            std::vector<double>& values, double mean);

        bool remove_outliers_via_median_absolute_deviation(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        bool remove_outliers_via_inter_quartile_range(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        bool remove_outliers_via_z_score(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        bool remove_outliers_via_winsorizing(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        bool remove_outliers_via_trimmed_mean(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        bool remove_outliers_via_grubbs_test(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        bool remove_outliers_via_tukey(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        bool remove_outliers_via_modified_z_score(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        std::future<bool> is_valid_data_async(
            std::vector<std::vector<double>>& data);

        std::future<std::vector<double>> flatten_data_async(
            std::vector<std::vector<double>>& data);

        std::future<double> compute_median_async(
            std::vector<double>& values);

        std::future<double> compute_mean_async(
            std::vector<double>& values);

        std::future<double> compute_standard_deviation_async(
            std::vector<double>& values, double mean);

        std::future<bool> remove_outliers_via_median_absolute_deviation_async(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        std::future<bool> remove_outliers_via_inter_quartile_range_async(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        std::future<bool> remove_outliers_via_z_score_async(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        std::future<bool> remove_outliers_via_winsorizing_async(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        std::future<bool> remove_outliers_via_trimmed_mean_async(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        std::future<bool> remove_outliers_via_grubbs_test_async(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        std::future<bool> remove_outliers_via_tukey_async(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        std::future<bool> remove_outliers_via_modified_z_score_async(
            std::vector<std::vector<double>>& data,
            const OutlierRemovalOptions& options);

        static Statistician& get_instance();

    protected:
        Statistician() = default;
        ~Statistician() = default;
        Statistician(const Statistician&) = delete;
        Statistician(Statistician&&) noexcept = delete;
        Statistician& operator = (Statistician&&) = delete;
        Statistician& operator = (const Statistician&) = delete;
    };

    inline static Statistician& STATISTICIAN =
        Statistician::get_instance();
}
