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
        double now() const;
        
        double nanosecond() const;
        
        double millisecond() const;
        
        double microsecond() const;
        
        double day(
            const TimeZone& time_zone_type = TimeZone::LOCAL
        ) const;
        
        double hour(
            const TimeZone& time_zone_type = TimeZone::LOCAL
        ) const;
        
        double year(
            const TimeZone& time_zone_type = TimeZone::LOCAL
        ) const;
        
        double month(
            const TimeZone& time_zone_type = TimeZone::LOCAL
        ) const;
        
        double second(
            const TimeZone& time_zone_type = TimeZone::LOCAL
        ) const;
        
        double minute(
            const TimeZone& time_zone_type = TimeZone::LOCAL
        ) const;
        
        std::string now(
            const TimeFormat& time_format,
            const TimeZone& time_zone_type = TimeZone::LOCAL
        ) const;
        
        std::string_view get_time_unit_full_name(
            const TimeScaleUnit& format
        ) const;
        
        std::string_view get_time_unit_abbreviation(
            const TimeScaleUnit& format
        ) const;
        
        TimeScaleUnit get_time_unit_abbreviation(
            const std::string& format
        ) const;
        
        double convert_seconds(
            const double& time,
            const TimeScaleUnit& format
        ) const;
        
        double convert_nanoseconds(
            const double& time,
            const TimeScaleUnit& format
        ) const;

        static Time& get_instance();

        void now(Result<double>& result) const;

        void nanosecond(Result<double>& result) const;        

        void millisecond(Result<double>& result) const;

        void microsecond(Result<double>& result) const;

        void day(Result<double>& result,
            const TimeZone& time_zone_type = TimeZone::LOCAL) const;

        void hour(Result<double>& result,
            const TimeZone& time_zone_type = TimeZone::LOCAL) const;

        void year(Result<double>& result,
            const TimeZone& time_zone_type = TimeZone::LOCAL) const;

        void month(Result<double>& result,
            const TimeZone& time_zone_type = TimeZone::LOCAL) const;

        void second(Result<double>& result,
            const TimeZone& time_zone_type = TimeZone::LOCAL) const;

        void minute(Result<double>& result,
            const TimeZone& time_zone_type = TimeZone::LOCAL) const;

        void now(Result<std::string>& result,
            const TimeFormat& time_format,
            const TimeZone& time_zone_type = TimeZone::LOCAL) const;

        void get_time_unit_full_name(Result<std::string>& result,
            const TimeScaleUnit& format) const;

        void get_time_unit_abbreviation(Result<std::string>& result,
            const TimeScaleUnit& format) const;

        void get_time_unit_abbreviation(Result<TimeScaleUnit>& result,
            const std::string& format) const;

        void convert_seconds(Result<double>& result,
            const double& time,
            const TimeScaleUnit& format) const;

        void convert_nanoseconds(Result<double>& result,
            const double& time,
            const TimeScaleUnit& format) const;

        static void get_instance(Result<Time*>& result);

    protected:
        Time() = default;
        
        ~Time() = default;
        
        Time(const Time& time) = delete;
        
        Time(Time&& time) noexcept = delete;
        
        Time& operator = (Time&& time) = delete;
        
        Time& operator = (const Time& time) = delete;

        std::string _pad3(int value) const;
        
        std::tm _get_time_zone(const TimeZone&) const;
        
        std::string _format_time(
            const std::tm& tm,
            const char* fmt
        ) const;
        
        const char* _get_format_string(
            const TimeFormat& time_format
        ) const;
        
        std::string _format_millisecond_level(
            absl::Duration since_epoch,
            const std::string& sep
        ) const;

        std::string _format_microsecond_level(
            absl::Duration since_epoch,
            const std::string& sep
        ) const;

        std::string _format_nanosecond_level(
            absl::Duration since_epoch,
            const std::string& sep
        ) const;

    };

    inline Time& TIME = Time::get_instance();
}
