#pragma once

#include "result.hpp"
#include "utilities.hpp"
#include "time_zone.hpp"
#include "time_format.hpp"

namespace QLogicaeCore
{
    class Time
    {
    public:
        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            Result<std::future<void>>& result
        );

        double now();

        void now(
            Result<double>& result
        );

        double nanosecond();

        void nanosecond(
            Result<double>& result
        );

        double millisecond();

        void millisecond(
            Result<double>& result
        );

        double microsecond();

        void microsecond(
            Result<double>& result
        );

        double day(
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        void day(
            Result<double>& result,
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        double hour(
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        void hour(
            Result<double>& result,
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        double year(
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        void year(
            Result<double>& result,
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        double month(
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        void month(
            Result<double>& result,
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        double second(
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        void second(
            Result<double>& result,
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        double minute(
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        void minute(
            Result<double>& result,
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        std::string now(
            const TimeFormat& time_format,
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        void now(
            Result<std::string>& result,
            const TimeFormat& time_format,
            const TimeZone& time_zone =
                TimeZone::LOCAL
        );

        std::string_view get_time_unit_full_name(
            const TimeScaleUnit& format
        );

        void get_time_unit_full_name(
            Result<std::string>& result,
            const TimeScaleUnit& format
        );

        std::string_view get_time_unit_abbreviation(
            const TimeScaleUnit& format
        );

        void get_time_unit_abbreviation(
            Result<std::string>& result,
            const TimeScaleUnit& format
        );

        TimeScaleUnit get_time_unit_abbreviation(
            const std::string& format
        );

        void get_time_unit_abbreviation(
            Result<TimeScaleUnit>& result,
            const std::string& format
        );

        double convert_seconds(
            const double& time,
            const TimeScaleUnit& format
        );

        void convert_seconds(
            Result<double>& result,
            const double& time,
            const TimeScaleUnit& format
        );

        double convert_nanoseconds(
            const double& time,
            const TimeScaleUnit& format
        );

        void convert_nanoseconds(
            Result<double>& result,
            const double& time,
            const TimeScaleUnit& format
        );

        static Time& get_instance();

        static void get_instance(
            Result<Time*>& result
        );

    protected:
        Time() = default;
        
        ~Time() = default;
        
        Time(
            const Time& time
        ) = delete;
        
        Time(
            Time&& time
        ) noexcept = delete;
        
        Time& operator = (
            Time&& time
        ) = delete;
        
        Time& operator = (
            const Time& time
        ) = delete;

        std::string _pad3(
            int value
        );
        
        std::tm _get_time_zone(
            const TimeZone&
        );
        
        std::string _format_time(
            const std::tm& tm,
            const char* fmt
        );
        
        const char* _get_format_string(
            const TimeFormat& time_format
        );
        
        std::string _format_millisecond_level(
            absl::Duration since_epoch,
            const std::string& sep
        );

        std::string _format_microsecond_level(
            absl::Duration since_epoch,
            const std::string& sep
        );

        std::string _format_nanosecond_level(
            absl::Duration since_epoch,
            const std::string& sep
        );
    };

    inline static Time& TIME =
        Time::get_instance();
}
