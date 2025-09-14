#include "pch.h"

#include "statistician.hpp"

namespace QLogicaeCore
{
    bool Statistician::is_valid_data(std::vector<std::vector<double>>& data)
    {
        if (data.empty()) return false;

        for (const auto& row : data)
        {
            if (row.empty()) return false;

            for (double value : row)
            {
                if (!std::isfinite(value)) return false;
            }
        }

        return true;
    }

    std::vector<double> Statistician::flatten_data(std::vector<std::vector<double>>& data)
    {
        std::size_t total = 0;
        for (const auto& row : data) total += row.size();

        std::vector<double> flat;
        flat.reserve(total);

        for (const auto& row : data)
        {
            flat.insert(flat.end(), row.begin(), row.end());
        }

        return flat;
    }

    double Statistician::compute_median(std::vector<double>& values)
    {
        const std::size_t size = values.size();
        if (size == 0)
        {
            return std::numeric_limits<double>::quiet_NaN();
        }

        std::ranges::sort(values);

        if (size % 2 == 0)
        {
            return (values[size / 2 - 1] + values[size / 2]) / 2.0;
        }

        return values[size / 2];
    }

    double Statistician::compute_mean(std::vector<double>& values)
    {
        if (values.empty())
        {
            return std::numeric_limits<double>::quiet_NaN();
        }

        return std::accumulate(values.begin(), values.end(), 0.0) /
            static_cast<double>(values.size());
    }

    double Statistician::compute_standard_deviation(std::vector<double>& values, double mean)
    {
        if (values.empty())
        {
            return std::numeric_limits<double>::quiet_NaN();
        }

        double sum = 0.0;
        for (double value : values)
        {
            sum += std::pow(value - mean, 2);
        }

        return std::sqrt(sum / static_cast<double>(values.size()));
    }

    bool Statistician::remove_outliers_via_median_absolute_deviation(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        if (!is_valid_data(data)) return false;
        if (options.factor <= 0.0 || options.threshold <= 0.0) return false;

        size_t index_a, size_a = data.size();
        for (index_a = 0; index_a < size_a; ++index_a)
        {
            std::vector<double> flat_data = data[index_a];
            const double median = compute_median(flat_data);

            std::vector<double> deviations;
            deviations.reserve(flat_data.size());

            for (const double value : flat_data)
            {
                deviations.push_back(std::abs(value - median));
            }

            const double mad = compute_median(deviations);
            if (mad < Constants::EPSILON) return false;

            const double modified_z_threshold = options.threshold;
            std::vector<double> filtered;
            filtered.reserve(flat_data.size());

            for (const double value : flat_data)
            {
                const double modified_z = 0.6745 * (value - median) / mad;
                if (std::abs(modified_z) <= modified_z_threshold)
                {
                    filtered.push_back(value);
                }
            }

            if (filtered.empty()) return false;

            data[index_a] = filtered;
        }

        return true;
    }

    bool Statistician::remove_outliers_via_inter_quartile_range(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        if (!is_valid_data(data)) return false;

        std::vector<double> flat_data = flatten_data(data);
        std::ranges::sort(flat_data);

        if (flat_data.size() < 4) return false;

        auto lower_half = std::vector<double>(flat_data.begin(), flat_data.begin() + flat_data.size() / 2);
        auto upper_half = std::vector<double>(flat_data.begin() + (flat_data.size() + 1) / 2, flat_data.end());

        double q1 = compute_median(lower_half);
        double q3 = compute_median(upper_half);
        double iqr = q3 - q1;

        if (iqr < Constants::EPSILON) return false;

        double lower_bound = q1 - options.factor * iqr;
        double upper_bound = q3 + options.factor * iqr;

        std::vector<double> filtered;
        for (double value : flat_data)
        {
            if (value >= lower_bound && value <= upper_bound)
            {
                filtered.push_back(value);
            }
        }

        if (filtered.empty()) return false;

        data = { filtered };
        return true;
    }

    bool Statistician::remove_outliers_via_z_score(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        if (!is_valid_data(data)) return false;

        std::vector<double> flat_data = flatten_data(data);
        double mean = compute_mean(flat_data);
        double stddev = compute_standard_deviation(flat_data, mean);

        if (stddev < Constants::EPSILON) return false;

        std::vector<double> filtered;
        for (double value : flat_data)
        {
            double z = (value - mean) / stddev;
            if (std::abs(z) <= options.threshold)
            {
                filtered.push_back(value);
            }
        }

        if (filtered.empty()) return false;

        data = { filtered };
        return true;
    }

    bool Statistician::remove_outliers_via_winsorizing(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        if (!is_valid_data(data)) return false;

        std::vector<double> flat_data = flatten_data(data);
        std::ranges::sort(flat_data);

        const std::size_t total_size = flat_data.size();
        if (total_size < 4) return false;

        std::size_t trim_count = static_cast<std::size_t>(options.proportion * total_size);
        trim_count = std::min(trim_count, total_size / 2 - 1);

        double lower = flat_data[trim_count];
        double upper = flat_data[total_size - trim_count - 1];

        std::vector<double> winsorized;
        bool modified = false;

        for (double value : flat_data)
        {
            if (value < lower)
            {
                winsorized.push_back(lower);
                modified = true;
            }
            else if (value > upper)
            {
                winsorized.push_back(upper);
                modified = true;
            }
            else
            {
                winsorized.push_back(value);
            }
        }

        if (!modified) return false;

        data = { winsorized };
        return true;
    }

    bool Statistician::remove_outliers_via_trimmed_mean(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        if (!is_valid_data(data)) return false;

        std::vector<double> flat_data = flatten_data(data);
        std::ranges::sort(flat_data);

        const std::size_t total_size = flat_data.size();
        if (total_size < 4) return false;

        std::size_t trim_count = static_cast<std::size_t>(options.proportion * total_size);
        trim_count = std::min(trim_count, total_size / 2 - 1);

        std::vector<double> trimmed(
            flat_data.begin() + trim_count,
            flat_data.end() - trim_count
        );

        double trimmed_mean = compute_mean(trimmed);
        double original_mean = compute_mean(flat_data);

        if (!std::isfinite(trimmed_mean) ||
            std::abs(trimmed_mean - original_mean) <= Constants::EPSILON)
        {
            return false;
        }

        data = { trimmed };
        return true;
    }

    bool Statistician::remove_outliers_via_grubbs_test(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        if (!is_valid_data(data)) return false;

        std::vector<double> flat_data = flatten_data(data);
        double mean = compute_mean(flat_data);
        double stddev = compute_standard_deviation(flat_data, mean);

        if (stddev < Constants::EPSILON) return false;

        double max_deviation = 0.0;
        for (double value : flat_data)
        {
            max_deviation = std::max(max_deviation, std::abs(value - mean));
        }

        double grubbs_statistic = max_deviation / stddev;

        if (grubbs_statistic > options.threshold) return false;

        data = { flat_data };
        return true;
    }

    bool Statistician::remove_outliers_via_tukey(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        return remove_outliers_via_inter_quartile_range(data, options);
    }

    bool Statistician::remove_outliers_via_modified_z_score(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        return remove_outliers_via_median_absolute_deviation(data, options);
    }

    std::future<bool> Statistician::is_valid_data_async(std::vector<std::vector<double>>& data)
    {
        return std::async(std::launch::async, [this, &data]() {
            return is_valid_data(data);
            });
    }

    std::future<std::vector<double>> Statistician::flatten_data_async(std::vector<std::vector<double>>& data)
    {
        return std::async(std::launch::async, [this, &data]() {
            return flatten_data(data);
            });
    }

    std::future<double> Statistician::compute_median_async(std::vector<double>& values)
    {
        return std::async(std::launch::async, [this, &values]() {
            return compute_median(values);
            });
    }

    std::future<double> Statistician::compute_mean_async(std::vector<double>& values)
    {
        return std::async(std::launch::async, [this, &values]() {
            return compute_mean(values);
            });
    }

    std::future<double> Statistician::compute_standard_deviation_async(std::vector<double>& values, double mean)
    {
        return std::async(std::launch::async, [this, &values, mean]() {
            return compute_standard_deviation(values, mean);
            });
    }

    std::future<bool> Statistician::remove_outliers_via_median_absolute_deviation_async(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        return std::async(std::launch::async, [this, &data, &options]() -> bool
            {
                return this->remove_outliers_via_median_absolute_deviation(data, options);
            });
    }

    std::future<bool> Statistician::remove_outliers_via_inter_quartile_range_async(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        return std::async(std::launch::async, [this, &data, &options]() -> bool
            {
                return this->remove_outliers_via_inter_quartile_range(data, options);
            });
    }

    std::future<bool> Statistician::remove_outliers_via_z_score_async(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        return std::async(std::launch::async, [this, &data, &options]() -> bool
            {
                return this->remove_outliers_via_z_score(data, options);
            });
    }

    std::future<bool> Statistician::remove_outliers_via_winsorizing_async(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        return std::async(std::launch::async, [this, &data, &options]() -> bool
            {
                return this->remove_outliers_via_winsorizing(data, options);
            });
    }

    std::future<bool> Statistician::remove_outliers_via_trimmed_mean_async(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        return std::async(std::launch::async, [this, &data, &options]() -> bool
            {
                return this->remove_outliers_via_trimmed_mean(data, options);
            });
    }

    std::future<bool> Statistician::remove_outliers_via_grubbs_test_async(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        return std::async(std::launch::async, [this, &data, &options]() -> bool
            {
                return this->remove_outliers_via_grubbs_test(data, options);
            });
    }

    std::future<bool> Statistician::remove_outliers_via_tukey_async(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        return std::async(std::launch::async, [this, &data, &options]() -> bool
            {
                return this->remove_outliers_via_tukey(data, options);
            });
    }

    std::future<bool> Statistician::remove_outliers_via_modified_z_score_async(
        std::vector<std::vector<double>>& data,
        const OutlierRemovalOptions& options)
    {
        return std::async(std::launch::async, [this, &data, &options]() -> bool
            {
                return this->remove_outliers_via_modified_z_score(data, options);
            });
    }

    Statistician& Statistician::get_instance()
    {
        static Statistician instance;

        return instance;
    }
}
