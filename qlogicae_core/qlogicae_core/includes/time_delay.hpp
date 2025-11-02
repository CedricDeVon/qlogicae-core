#pragma once

#include "result.hpp"
#include "logger.hpp"

#include <future>

namespace QLogicaeCore
{
    class TimeDelay
    {
    public:
        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            const std::function<void(const bool& result)>& callback
        );

        void setup_async(
            Result<std::future<void>>& result
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback
        );

        void in_years(
            const double& value
        );

        std::future<void> in_years_async(
            const double& value
        );

        void in_years_async(
            const std::function<void(const bool& result)>& callback,
            const double& value
        );

        void in_years(
            Result<void>& result,
            const double& value
        );

        void in_years_async(
            Result<std::future<void>>& result,
            const double& value
        );

        void in_years_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& value
        );

        void in_months(
            const double& value
        );

        std::future<void> in_months_async(
            const double& value
        );

        void in_months_async(
            const std::function<void(const bool& result)>& callback,
            const double& value
        );

        void in_months(
            Result<void>& result,
            const double& value
        );

        void in_months_async(
            Result<std::future<void>>& result,
            const double& value
        );

        void in_months_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& value
        );

        void in_days(
            const double& value
        );

        std::future<void> in_days_async(
            const double& value
        );

        void in_days_async(
            const std::function<void(const bool& result)>& callback,
            const double& value
        );

        void in_days(
            Result<void>& result,
            const double& value
        );

        void in_days_async(
            Result<std::future<void>>& result,
            const double& value
        );

        void in_days_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& value
        );

        void in_hours(
            const double& value
        );

        std::future<void> in_hours_async(
            const double& value
        );

        void in_hours_async(
            const std::function<void(const bool& result)>& callback,
            const double& value
        );
        
        void in_hours(
            Result<void>& result,
            const double& value
        );

        void in_hours_async(
            Result<std::future<void>>& result,
            const double& value
        );

        void in_hours_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& value
        );

        void in_minutes(
            const double& value
        );

        std::future<void> in_minutes_async(
            const double& value
        );

        void in_minutes_async(
            const std::function<void(const bool& result)>& callback,
            const double& value
        );

        void in_minutes(
            Result<void>& result,
            const double& value
        );

        void in_minutes_async(
            Result<std::future<void>>& result,
            const double& value
        );

        void in_minutes_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& value
        );

        void in_seconds(
            const double& value
        );

        std::future<void> in_seconds_async(
            const double& value
        );

        void in_seconds_async(
            const std::function<void(const bool& result)>& callback,
            const double& value
        );

        void in_seconds(
            Result<void>& result,
            const double& value
        );

        void in_seconds_async(
            Result<std::future<void>>& result,
            const double& value
        );

        void in_seconds_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& value
        );

        void in_milliseconds(
            const double& value
        );

        std::future<void> in_milliseconds_async(
            const double& value
        );

        void in_milliseconds_async(
            const std::function<void(const bool& result)>& callback,
            const double& value
        );

        void in_milliseconds(
            Result<void>& result,
            const double& value
        );

        void in_milliseconds_async(
            Result<std::future<void>>& result,
            const double& value
        );

        void in_milliseconds_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& value
        );

        void in_microseconds(
            const double& value
        );

        std::future<void> in_microseconds_async(
            const double& value
        );

        void in_microseconds_async(
            const std::function<void(const bool& result)>& callback,
            const double& value
        );

        void in_microseconds(
            Result<void>& result,
            const double& value
        );

        void in_microseconds_async(
            Result<std::future<void>>& result,
            const double& value
        );

        void in_microseconds_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& value
        );

        void in_nanoseconds(
            const double& value
        );

        std::future<void> in_nanoseconds_async(
            const double& value
        );

        void in_nanoseconds_async(
            const std::function<void(const bool& result)>& callback,
            const double& value
        );

        void in_nanoseconds(
            Result<void>& result,
            const double& value
        );

        void in_nanoseconds_async(
            Result<std::future<void>>& result,
            const double& value
        );

        void in_nanoseconds_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& value
        );

        void calibrate();

        std::future<void> calibrate_async(
            const double& microseconds
        );

        void calibrate_async(
            const std::function<void(const bool& result)>& callback
        );

        void calibrate(
            Result<void>& result
        );

        void calibrate_async(
            Result<std::future<void>>& result,
            const double& microseconds
        );

        void calibrate_async(
            const std::function<void(Result<void>& result)>& callback
        );

        void real_time_stamp_counter(
            const double& microseconds
        );

        std::future<void> real_time_stamp_counter_async(
            const double& microseconds
        );

        void real_time_stamp_counter_async(
            const std::function<void(const bool& result)>& callback,
            const double& microseconds
        );

        void real_time_stamp_counter(
            Result<void>& result,
            const double& microseconds
        );

        void real_time_stamp_counter_async(
            Result<std::future<void>>& result,
            const double& microseconds
        );

        void real_time_stamp_counter_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& microseconds
        );

        void query_performance_counter(
            const double& microseconds
        );

        std::future<void> query_performance_counter_async(
            const double& microseconds
        );

        void query_performance_counter_async(
            const std::function<void(const bool& result)>& callback,
            const double& microseconds
        );

        void query_performance_counter(
            Result<void>& result,
            const double& microseconds
        );

        void query_performance_counter_async(
            Result<std::future<void>>& result,
            const double& microseconds
        );

        void query_performance_counter_async(
            const std::function<void(Result<void>& result)>& callback,
            const double& microseconds
        );

        static TimeDelay& get_instance();

        static void get_instance(
            Result<TimeDelay*>& result
        );

    protected:
        TimeDelay();

        ~TimeDelay();

        TimeDelay(
            const TimeDelay& instance
        ) = delete;

        TimeDelay(
            TimeDelay&& instance
        ) noexcept = delete;

        TimeDelay& operator = (
            TimeDelay&& instance
        ) = delete;

        TimeDelay& operator = (
            const TimeDelay& instance
        ) = delete;

        double _cycles_per_microsecond;
    };

    inline static TimeDelay& TIME_DELAY =
        TimeDelay::get_instance();
}
