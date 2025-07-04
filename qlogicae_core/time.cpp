#pragma once

#include "pch.h"

#include "time.hpp"

namespace QLogicaeCore {
    Time& Time::instance()
    {
        static Time singleton;

        return singleton;
    }

    std::tm Time::_get_time_zone(const TimeZone& zone) const
    {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        std::tm tm{};
        if (zone == TimeZone::UTC)
        {
            gmtime_s(&tm, &time);
        }
        else
        {
            localtime_s(&tm, &time);
        }

        return tm;
    }

    const char* Time::_get_format_string(const TimeFormat& format) const
    {
        switch (format)
        {
            case TimeFormat::ISO8601:
            {
                return Constants::TIME_FORMAT_ISO_8601;
            }
            case TimeFormat::FullTimestamp:
            {
                return Constants::TIME_FORMAT_FULL_TIMESTAMP;
            }
            case TimeFormat::Hour12:
            {
                return Constants::TIME_FORMAT_HOUR_12;
            }
            case TimeFormat::Hour24:
            {
                return Constants::TIME_FORMAT_HOUR_24;
            }
            case TimeFormat::DateDashed:
            {
                return Constants::TIME_FORMAT_DATE_DASHED;
            }
            case TimeFormat::DateMDYSlashed:
            {
                return Constants::TIME_FORMAT_DATE_MDY_SLASHED;
            }
            case TimeFormat::DateDMYSlashed:
            {
                return Constants::TIME_FORMAT_DATE_DMY_SLASHED;
            }
            case TimeFormat::DateDMYSpaced:
            {
                return Constants::TIME_FORMAT_DATE_DMY_SPACED;
            }
            case TimeFormat::DateVerbose:
            {
                return Constants::TIME_FORMAT_DATE_VERBOSE;
            }
            default:
            {
                return Constants::TIME_FORMAT_DATE_VERBOSE;
            }
        }
    }

    std::string Time::now(
        const TimeFormat& format, const TimeZone& zone) const
    {
        std::ostringstream oss;
        std::tm tm = _get_time_zone(zone);
        std::chrono::system_clock::duration duration =
            std::chrono::system_clock::now().time_since_epoch();

        oss << std::setfill(Constants::TIME_FORMAT_PART_6);
        
        switch (format)
        {
            case TimeFormat::Unix:
            {
                return std::to_string(
                    std::chrono::duration_cast<std::chrono::seconds>(
                        duration).count());
            }

            case TimeFormat::ISO8601:
            {
                oss << std::put_time(&tm, _get_format_string(format));

                break;
            }

            case TimeFormat::FullTimestamp:
            {
                oss << std::put_time(&tm, _get_format_string(format))
                    << Constants::TIME_FORMAT_PART_4
                    << std::setw(
                        Constants::TIME_FORMAT_MIL_MIC_NAN_STREAM_SIZE)
                    << static_cast<int>(
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                            duration).count() % Constants::NUMBER_THOUSAND)
                    << Constants::TIME_FORMAT_PART_5
                    << std::setw(
                        Constants::TIME_FORMAT_MIL_MIC_NAN_STREAM_SIZE)
                    << static_cast<int>(
                        std::chrono::duration_cast<std::chrono::microseconds>(
                            duration).count() % Constants::NUMBER_THOUSAND)
                    << Constants::TIME_FORMAT_PART_5
                    << std::setw(
                        Constants::TIME_FORMAT_MIL_MIC_NAN_STREAM_SIZE)
                    << static_cast<int>(
                        std::chrono::duration_cast<std::chrono::nanoseconds>(
                            duration).count() % Constants::NUMBER_THOUSAND);
                break;
            }
            case TimeFormat::Hour12:
            {
                oss << std::put_time(&tm, _get_format_string(format));

                break;
            }
            case TimeFormat::Hour24:
            {
                oss << std::put_time(&tm, _get_format_string(format));
            
                break;
            }
            case TimeFormat::MillisMicrosNanos:
            {
                oss << Constants::TIME_FORMAT_PART_1
                    << std::chrono::duration_cast<std::chrono::milliseconds>(
                        duration).count()
                    << Constants::TIME_FORMAT_PART_2
                    << std::chrono::duration_cast<std::chrono::microseconds>(
                        duration).count()
                    << Constants::TIME_FORMAT_PART_3
                    << std::chrono::duration_cast<std::chrono::nanoseconds>(
                        duration).count();
                return oss.str();
            }
            case TimeFormat::DateDashed:
            {
                oss << std::put_time(
                    &tm, _get_format_string(format));

                break;
            }
            case TimeFormat::DateMDYSlashed:
            {
                oss << std::put_time(
                    &tm, _get_format_string(format));

                break;
            }
            case TimeFormat::DateDMYSlashed:
            {
                oss << std::put_time(
                    &tm, _get_format_string(format));

                break;
            }
            case TimeFormat::DateDMYSpaced:
            {
                oss << std::put_time(
                    &tm, _get_format_string(format));

                break;
            }
            case TimeFormat::DateVerbose:
            {
                oss << std::put_time(
                    &tm, _get_format_string(format));

                break;
            }
            default:
            {
                return Constants::TIME_FORMAT_INVALID;
            }
        }

        return oss.str();
    }

    int Time::year(const TimeZone& zone) const
    {
        return _get_time_zone(zone).tm_year +
            Constants::UNIX_START_YEAR_OFFSET;
    }

    int Time::month(const TimeZone& zone) const
    {
        return _get_time_zone(zone).tm_mon +
            Constants::NUMBER_ONE;
    }
    
    int Time::day(const TimeZone& zone) const
    { 
        return _get_time_zone(zone).tm_mday;
    }
    
    int Time::hour(const TimeZone& zone) const
    { 
        return _get_time_zone(zone).tm_hour;
    }
    
    int Time::minute(const TimeZone& zone) const
    { 
        return _get_time_zone(zone).tm_min;
    }
    
    int Time::second(const TimeZone& zone) const
    {
        return _get_time_zone(zone).tm_sec;
    }

    int Time::millisecond() const
    {
        return static_cast<int>(
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now()
                    .time_since_epoch())
                        .count() % Constants::NUMBER_THOUSAND);
    }

    int Time::microsecond() const
    {
        return static_cast<int>(
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::system_clock::now()
                    .time_since_epoch())
                        .count() % Constants::NUMBER_MILLION);
    }

    int Time::nanosecond() const
    {
        return static_cast<int>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now()
                    .time_since_epoch())
                        .count() % Constants::NUMBER_BILLION);
    }
} 

