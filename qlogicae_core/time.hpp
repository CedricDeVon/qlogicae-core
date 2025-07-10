#pragma once

#include "pch.h"

#include "globals.hpp"

namespace QLogicaeCore
{
    class Time
    {
    public:
        int nanosecond() const;
        int millisecond() const;
        int microsecond() const;
        int day(const TimeZone& = TimeZone::Local) const;
        int hour(const TimeZone& = TimeZone::Local) const;
        int year(const TimeZone& = TimeZone::Local) const;
        int month(const TimeZone& = TimeZone::Local) const;
        int second(const TimeZone& = TimeZone::Local) const;
        int minute(const TimeZone& = TimeZone::Local) const;
        std::string now(const TimeFormat&, const TimeZone& = TimeZone::Local) const;

        static Time& instance();

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

