#pragma once

#include "pch.h"

#include "globals.hpp"

namespace QLogicaeCore
{
    class Time
    {
    public:
        double now() const;
        double nanosecond() const;
        double millisecond() const;
        double microsecond() const;
        double day(const TimeZone& = TimeZone::LOCAL) const;
        double hour(const TimeZone& = TimeZone::LOCAL) const;
        double year(const TimeZone& = TimeZone::LOCAL) const;
        double month(const TimeZone& = TimeZone::LOCAL) const;
        double second(const TimeZone& = TimeZone::LOCAL) const;
        double minute(const TimeZone& = TimeZone::LOCAL) const;
        std::string now(const TimeFormat&, const TimeZone& = TimeZone::LOCAL) const;
        std::string_view get_time_unit_full_name(const TimeScaleUnit& format) const;
        std::string_view get_time_unit_abbreviation(const TimeScaleUnit& format) const;
        double convert_seconds(const double& time, const TimeScaleUnit& format) const;
        double convert_nanoseconds(const double& time, const TimeScaleUnit& format) const;

        static Time& get_instance();

    protected:
        Time() = default;
        ~Time() = default;
        Time(const Time&) = delete;
        Time(Time&&) noexcept = delete;
        Time& operator = (Time&&) = delete;
        Time& operator = (const Time&) = delete;

        std::tm _get_time_zone(const TimeZone&) const;
        const char* _get_format_string(const TimeFormat&) const;
    };
}
