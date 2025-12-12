#pragma once

#include "result.hpp"
#include "instance_manager.hpp"

namespace QLogicaeCppCore
{
    class TimeDelayClock
    {
    public:
        TimeDelayClock();

        ~TimeDelayClock();

        TimeDelayClock(
            const TimeDelayClock& instance
        ) = delete;

        TimeDelayClock(
            TimeDelayClock&& instance
        ) noexcept = delete;

        TimeDelayClock& operator = (
            TimeDelayClock&& instance
        ) = delete;

        TimeDelayClock& operator = (
            const TimeDelayClock& instance
        ) = delete;

        void construct(
            Result<bool>& result
        );

        void destruct(
            Result<bool>& result
        );

        void in_years(
            Result<bool>& result,
            const double& value
        );

        void in_months(
            Result<bool>& result,
            const double& value
        );

        void in_days(
            Result<bool>& result,
            const double& value
        );
        
        void in_hours(
            Result<bool>& result,
            const double& value
        );

        void in_minutes(
            Result<bool>& result,
            const double& value
        );

        void in_seconds(
            Result<bool>& result,
            const double& value
        );

        void in_milliseconds(
            Result<bool>& result,
            const double& value
        );

        void in_microseconds(
            Result<bool>& result,
            const double& value
        );

        void in_nanoseconds(
            Result<bool>& result,
            const double& value
        );

        void calibrate(
            Result<bool>& result
        );

        void real_time_stamp_counter(
            Result<bool>& result,
            const double& microseconds
        );

        void query_performance_counter(
            Result<bool>& result,
            const double& microseconds
        );

        double cycles_per_microsecond;
    };

    inline static TimeDelayClock& TIME_DELAY_CLOCK =
        INSTANCE_MANAGER.get_instance<TimeDelayClock>();
}
