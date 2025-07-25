#pragma once

#include "pch.h"

#include "time.hpp"

namespace QLogicaeCore
{
    Time& Time::get_instance()
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
            case TimeFormat::FULL_TIMESTAMP:
            {
                return Constants::TIME_FORMAT_FULL_TIMESTAMP;
            }
            case TimeFormat::FULL_DASHED_TIMESTAMP:
            {
                return Constants::TIME_FORMAT_FULL_DASHED_TIMESTAMP;
            }
            case TimeFormat::HOUR_12:
            {
                return Constants::TIME_FORMAT_HOUR_12;
            }
            case TimeFormat::HOUR_24:
            {
                return Constants::TIME_FORMAT_HOUR_24;
            }
            case TimeFormat::DATE_DASHED:
            {
                return Constants::TIME_FORMAT_DATE_DASHED;
            }
            case TimeFormat::DATE_MDY_SLASHED:
            {
                return Constants::TIME_FORMAT_DATE_MDY_SLASHED;
            }
            case TimeFormat::DATE_DMY_SLASHED:
            {
                return Constants::TIME_FORMAT_DATE_DMY_SLASHED;
            }
            case TimeFormat::DATE_DMY_SPACED:
            {
                return Constants::TIME_FORMAT_DATE_DMY_SPACED;
            }
            case TimeFormat::DATE_VERBOSE:
            {
                return Constants::TIME_FORMAT_DATE_VERBOSE;
            }
            default:
            {
                return Constants::TIME_FORMAT_DATE_VERBOSE;
            }
        }
    }

    double Time::now() const
    {
        return static_cast<double>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now()
                    .time_since_epoch()).count()
            );
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
            case TimeFormat::UNIX:
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

            case TimeFormat::FULL_TIMESTAMP:
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

            case TimeFormat::FULL_DASHED_TIMESTAMP:
            {
                oss << std::put_time(&tm, _get_format_string(format))
                    << "-"
                    << std::setw(
                        Constants::TIME_FORMAT_MIL_MIC_NAN_STREAM_SIZE)
                    << static_cast<int>(
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                            duration).count() % Constants::NUMBER_THOUSAND)
                    << "-"
                    << std::setw(
                        Constants::TIME_FORMAT_MIL_MIC_NAN_STREAM_SIZE)
                    << static_cast<int>(
                        std::chrono::duration_cast<std::chrono::microseconds>(
                            duration).count() % Constants::NUMBER_THOUSAND)
                    << "-"
                    << std::setw(
                        Constants::TIME_FORMAT_MIL_MIC_NAN_STREAM_SIZE)
                    << static_cast<int>(
                        std::chrono::duration_cast<std::chrono::nanoseconds>(
                            duration).count() % Constants::NUMBER_THOUSAND);
                break;
            }

            case TimeFormat::HOUR_12:
            {
                oss << std::put_time(&tm, _get_format_string(format));

                break;
            }

            case TimeFormat::HOUR_24:
            {
                oss << std::put_time(&tm, _get_format_string(format));
            
                break;
            }

            case TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND:
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

            case TimeFormat::DATE_DASHED:
            {
                oss << std::put_time(
                    &tm, _get_format_string(format));

                break;
            }

            case TimeFormat::DATE_MDY_SLASHED:
            {
                oss << std::put_time(
                    &tm, _get_format_string(format));

                break;
            }

            case TimeFormat::DATE_DMY_SLASHED:
            {
                oss << std::put_time(
                    &tm, _get_format_string(format));

                break;
            }

            case TimeFormat::DATE_DMY_SPACED:
            {
                oss << std::put_time(
                    &tm, _get_format_string(format));

                break;
            }

            case TimeFormat::DATE_VERBOSE:
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

    double Time::year(const TimeZone& zone) const
    {
        return static_cast<double>(_get_time_zone(zone).tm_year )+
            Constants::UNIX_START_YEAR_OFFSET;
    }

    double Time::month(const TimeZone& zone) const
    {
        return static_cast<double>(_get_time_zone(zone).tm_mon )+
            Constants::NUMBER_ONE;
    }

    double Time::day(const TimeZone& zone) const
    {
        return static_cast<double>(_get_time_zone(zone).tm_mday);
    }

    double Time::hour(const TimeZone& zone) const
    {
        return static_cast<double>(_get_time_zone(zone).tm_hour);
    }

    double Time::minute(const TimeZone& zone) const
    {
        return static_cast<double>(_get_time_zone(zone).tm_min);
    }

    double Time::second(const TimeZone& zone) const
    {
        return static_cast<double>(_get_time_zone(zone).tm_sec);
    }

    double Time::millisecond() const
    {
        return static_cast<double>(
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now()
                .time_since_epoch())
            .count() % Constants::NUMBER_THOUSAND);
    }

    double Time::microsecond() const
    {
        return static_cast<double>(
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::system_clock::now()
                .time_since_epoch())
            .count() % Constants::NUMBER_MILLION);
    }

    double Time::nanosecond() const
    {
        return static_cast<double>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now()
                    .time_since_epoch())
                        .count() % Constants::NUMBER_BILLION);
    }

    std::string_view Time::get_time_unit_full_name(
        const TimeScaleUnit& format) const
    {
        switch (format)
        {
        case (TimeScaleUnit::NANOSECONDS):
            return Constants::TIME_SCALE_UNIT_FULL_NAME_NANOSECONDS;

        case (TimeScaleUnit::MICROSECONDS):
            return Constants::TIME_SCALE_UNIT_FULL_NAME_MICROSECONDS;

        case (TimeScaleUnit::MILLISECONDS):
            return Constants::TIME_SCALE_UNIT_FULL_NAME_MILLISECONDS;

        case (TimeScaleUnit::SECONDS):
            return Constants::TIME_SCALE_UNIT_FULL_NAME_SECONDS;

        case (TimeScaleUnit::MINUTES):
            return Constants::TIME_SCALE_UNIT_FULL_NAME_MINUTES;

        case (TimeScaleUnit::HOURS):
            return Constants::TIME_SCALE_UNIT_FULL_NAME_HOURS;

        case (TimeScaleUnit::DAYS):
            return Constants::TIME_SCALE_UNIT_FULL_NAME_DAYS;

        case (TimeScaleUnit::WEEKS):
            return Constants::TIME_SCALE_UNIT_FULL_NAME_WEEKS;

        case (TimeScaleUnit::MONTHS):
            return Constants::TIME_SCALE_UNIT_FULL_NAME_MONTHS;

        case (TimeScaleUnit::YEARS):
            return Constants::TIME_SCALE_UNIT_FULL_NAME_YEARS;
        }

        return Constants::TIME_SCALE_UNIT_FULL_NAME_SECONDS;
    }

    std::string_view Time::get_time_unit_abbreviation(
        const TimeScaleUnit& format) const
    {
        switch (format)
        {
        case (TimeScaleUnit::NANOSECONDS):
            return Constants::TIME_SCALE_UNIT_ABBREVIATION_NANOSECONDS;

        case (TimeScaleUnit::MICROSECONDS):
            return Constants::TIME_SCALE_UNIT_ABBREVIATION_MICROSECONDS;

        case (TimeScaleUnit::MILLISECONDS):
            return Constants::TIME_SCALE_UNIT_ABBREVIATION_MILLISECONDS;

        case (TimeScaleUnit::SECONDS):
            return Constants::TIME_SCALE_UNIT_ABBREVIATION_SECONDS;

        case (TimeScaleUnit::MINUTES):
            return Constants::TIME_SCALE_UNIT_ABBREVIATION_MINUTES;

        case (TimeScaleUnit::HOURS):
            return Constants::TIME_SCALE_UNIT_ABBREVIATION_HOURS;

        case (TimeScaleUnit::DAYS):
            return Constants::TIME_SCALE_UNIT_ABBREVIATION_DAYS;

        case (TimeScaleUnit::WEEKS):
            return Constants::TIME_SCALE_UNIT_ABBREVIATION_WEEKS;

        case (TimeScaleUnit::MONTHS):
            return Constants::TIME_SCALE_UNIT_ABBREVIATION_MONTHS;

        case (TimeScaleUnit::YEARS):
            return Constants::TIME_SCALE_UNIT_ABBREVIATION_YEARS;
        }

        return Constants::TIME_SCALE_UNIT_ABBREVIATION_SECONDS;
    }

    double Time::convert_seconds(
        const double& time, const TimeScaleUnit& format) const
    {
        switch (format)
        {
        case (TimeScaleUnit::NANOSECONDS):
            return time / Constants::SECONDS_OVER_NANOSECONDS;

        case (TimeScaleUnit::MICROSECONDS):
            return time / Constants::SECONDS_OVER_MICROSECONDS;

        case (TimeScaleUnit::MILLISECONDS):
            return time / Constants::SECONDS_OVER_MILLISECONDS;

        case (TimeScaleUnit::SECONDS):
            return time;

        case (TimeScaleUnit::MINUTES):
            return time * Constants::SECONDS_PER_MINUTE;

        case (TimeScaleUnit::HOURS):
            return time * Constants::SECONDS_PER_HOUR;

        case (TimeScaleUnit::DAYS):
            return time * Constants::SECONDS_PER_DAY;

        case (TimeScaleUnit::WEEKS):
            return time * Constants::SECONDS_PER_WEEK;

        case (TimeScaleUnit::MONTHS):
            return time * Constants::SECONDS_PER_MONTH;

        case (TimeScaleUnit::YEARS):
            return time * Constants::SECONDS_PER_YEAR;

        }

        return time;
    }
} 

