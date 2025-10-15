#include "pch.hpp"

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
        try
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::_get_time_zone(): " + exception.what());
        }
    }

    const char* Time::_get_format_string(const TimeFormat& format) const
    {
        try
        {
            switch (format)
            {
            case TimeFormat::ISO8601:
            {
                return UTILITIES.TIME_FORMAT_ISO_8601;
            }
            case TimeFormat::FULL_TIMESTAMP:
            {
                return UTILITIES.TIME_FORMAT_FULL_TIMESTAMP;
            }
            case TimeFormat::FULL_DASHED_TIMESTAMP:
            {
                return UTILITIES.TIME_FORMAT_FULL_DASHED_TIMESTAMP;
            }
            case TimeFormat::HOUR_12:
            {
                return UTILITIES.TIME_FORMAT_HOUR_12;
            }
            case TimeFormat::HOUR_24:
            {
                return UTILITIES.TIME_FORMAT_HOUR_24;
            }
            case TimeFormat::DATE_DASHED:
            {
                return UTILITIES.TIME_FORMAT_DATE_DASHED;
            }
            case TimeFormat::DATE_MDY_SLASHED:
            {
                return UTILITIES.TIME_FORMAT_DATE_MDY_SLASHED;
            }
            case TimeFormat::DATE_DMY_SLASHED:
            {
                return UTILITIES.TIME_FORMAT_DATE_DMY_SLASHED;
            }
            case TimeFormat::DATE_DMY_SPACED:
            {
                return UTILITIES.TIME_FORMAT_DATE_DMY_SPACED;
            }
            case TimeFormat::DATE_VERBOSE:
            {
                return UTILITIES.TIME_FORMAT_DATE_VERBOSE;
            }
            default:
            {
                return UTILITIES.TIME_FORMAT_DATE_VERBOSE;
            }
            }
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::_get_format_string(): " + exception.what());
        }
    }

    double Time::now() const
    {
        try
        {
            return static_cast<double>(
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now()
                    .time_since_epoch()).count()
                );
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::now(): " + exception.what());
        }
    }

    std::string Time::now(
        const TimeFormat& format,
        const TimeZone& zone) const
    {
        try
        {
            absl::Time now = absl::Now();
            absl::Duration since_epoch = now - absl::UnixEpoch();

            std::tm tm = _get_time_zone(zone);
            const char* fmt = _get_format_string(format);

            switch (format) {
            case TimeFormat::UNIX:
                return absl::StrCat(absl::ToUnixSeconds(now));

            case TimeFormat::ISO8601:
                return _format_time(tm, fmt);

            case TimeFormat::SECOND_LEVEL_TIMESTAMP:
                return _format_time(tm, fmt);

            case TimeFormat::MILLISECOND_LEVEL_TIMESTAMP:
                return _format_time(tm, fmt) +
                    "." + _format_millisecond_level(since_epoch, ":");

            case TimeFormat::MICROSECOND_LEVEL_TIMESTAMP:
                return _format_time(tm, fmt) +
                    "." + _format_microsecond_level(since_epoch, ":");

            case TimeFormat::FULL_TIMESTAMP:
                return _format_time(tm, fmt) +
                    "." + _format_nanosecond_level(since_epoch, ":");

            case TimeFormat::FULL_DASHED_TIMESTAMP:
                return _format_time(tm, fmt) + "-" +
                    _format_nanosecond_level(since_epoch, "-");

            case TimeFormat::HOUR_12:
            case TimeFormat::HOUR_24:
            case TimeFormat::DATE_DASHED:
            case TimeFormat::DATE_MDY_SLASHED:
            case TimeFormat::DATE_DMY_SLASHED:
            case TimeFormat::DATE_DMY_SPACED:
            case TimeFormat::DATE_VERBOSE:
                return _format_time(tm, fmt);

            case TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND:
                return absl::StrCat(
                    "ms: ",
                    absl::ToInt64Milliseconds(since_epoch),
                    ", us: ",
                    absl::ToInt64Microseconds(since_epoch),
                    ", ns: ",
                    absl::ToInt64Nanoseconds(since_epoch));

            default:
                return UTILITIES.TIME_FORMAT_INVALID;
            }
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::now(): " + exception.what());
        }
    }

    double Time::year(const TimeZone& zone) const
    {
        try
        {
            return static_cast<double>(_get_time_zone(zone).tm_year) +
                UTILITIES.UNIX_START_YEAR_OFFSET;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::year(): " + exception.what());
        }
    }

    double Time::month(const TimeZone& zone) const
    {
        try
        {
            return static_cast<double>(_get_time_zone(zone).tm_mon) +
                1;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::month(): " + exception.what());
        }
    }

    double Time::day(const TimeZone& zone) const
    {
        try
        {
            return static_cast<double>(_get_time_zone(zone).tm_mday);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::day(): " + exception.what());
        }
    }

    double Time::hour(const TimeZone& zone) const
    {
        try
        {
            return static_cast<double>(_get_time_zone(zone).tm_hour);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::hour(): " + exception.what());
        }
    }

    double Time::minute(const TimeZone& zone) const
    {
        try
        {
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::minute(): " + exception.what());
        }
        return static_cast<double>(_get_time_zone(zone).tm_min);
    }

    double Time::second(const TimeZone& zone) const
    {
        try
        {
            return static_cast<double>(_get_time_zone(zone).tm_sec);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::second(): " + exception.what());
        }
    }

    double Time::millisecond() const
    {
        try
        {
            return static_cast<double>(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now()
                    .time_since_epoch())
                .count() % 1'000);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::millisecond(): " + exception.what());
        }
    }

    double Time::microsecond() const
    {
        try
        {
            return static_cast<double>(
                std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::system_clock::now()
                    .time_since_epoch())
                .count() % 1'000'000);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::microsecond(): " + exception.what());
        }
    }

    double Time::nanosecond() const
    {
        try
        {
            return static_cast<double>(
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now()
                    .time_since_epoch())
                .count() % 1'000'000'000);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::nanosecond(): " + exception.what());
        }
    }

    std::string_view Time::get_time_unit_full_name(
        const TimeScaleUnit& format) const
    {
        try
        {
            switch (format)
            {
            case (TimeScaleUnit::NANOSECONDS):
                return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_NANOSECONDS;

            case (TimeScaleUnit::MICROSECONDS):
                return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MICROSECONDS;

            case (TimeScaleUnit::MILLISECONDS):
                return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MILLISECONDS;

            case (TimeScaleUnit::SECONDS):
                return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_SECONDS;

            case (TimeScaleUnit::MINUTES):
                return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MINUTES;

            case (TimeScaleUnit::HOURS):
                return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_HOURS;

            case (TimeScaleUnit::DAYS):
                return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_DAYS;

            case (TimeScaleUnit::WEEKS):
                return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_WEEKS;

            case (TimeScaleUnit::MONTHS):
                return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MONTHS;

            case (TimeScaleUnit::YEARS):
                return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_YEARS;
            }

            return UTILITIES.TIME_SCALE_UNIT_FULL_NAME_SECONDS;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::get_time_unit_full_name(): " + exception.what());
        }
    }

    std::string_view Time::get_time_unit_abbreviation(
        const TimeScaleUnit& format) const
    {
        try
        {
            switch (format)
            {
            case (TimeScaleUnit::NANOSECONDS):
                return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_NANOSECONDS;

            case (TimeScaleUnit::MICROSECONDS):
                return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MICROSECONDS;

            case (TimeScaleUnit::MILLISECONDS):
                return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MILLISECONDS;

            case (TimeScaleUnit::SECONDS):
                return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_SECONDS;

            case (TimeScaleUnit::MINUTES):
                return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MINUTES;

            case (TimeScaleUnit::HOURS):
                return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_HOURS;

            case (TimeScaleUnit::DAYS):
                return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_DAYS;

            case (TimeScaleUnit::WEEKS):
                return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_WEEKS;

            case (TimeScaleUnit::MONTHS):
                return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MONTHS;

            case (TimeScaleUnit::YEARS):
                return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_YEARS;
            }

            return UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_SECONDS;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::get_time_unit_abbreviation(): " + exception.what());
        }
    }

    TimeScaleUnit Time::get_time_unit_abbreviation(const std::string& format) const
    {
        try
        {
            return (UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_STRINGS.contains(format)) ?
                UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_STRINGS.at(format) :
                TimeScaleUnit::NANOSECONDS;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::get_time_unit_abbreviation(): " + exception.what());
        }
    }

    double Time::convert_seconds(
        const double& time, const TimeScaleUnit& format) const
    {
        try
        {
            switch (format)
            {
            case (TimeScaleUnit::NANOSECONDS):
                return time / UTILITIES.SECONDS_OVER_NANOSECONDS;

            case (TimeScaleUnit::MICROSECONDS):
                return time / UTILITIES.SECONDS_OVER_MICROSECONDS;

            case (TimeScaleUnit::MILLISECONDS):
                return time / UTILITIES.SECONDS_OVER_MILLISECONDS;

            case (TimeScaleUnit::SECONDS):
                return time;

            case (TimeScaleUnit::MINUTES):
                return time * UTILITIES.SECONDS_PER_MINUTE;

            case (TimeScaleUnit::HOURS):
                return time * UTILITIES.SECONDS_PER_HOUR;

            case (TimeScaleUnit::DAYS):
                return time * UTILITIES.SECONDS_PER_DAY;

            case (TimeScaleUnit::WEEKS):
                return time * UTILITIES.SECONDS_PER_WEEK;

            case (TimeScaleUnit::MONTHS):
                return time * UTILITIES.SECONDS_PER_MONTH;

            case (TimeScaleUnit::YEARS):
                return time * UTILITIES.SECONDS_PER_YEAR;
            }

            return time;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::convert_seconds(): " + exception.what());
        }
    }

    double Time::convert_nanoseconds(
        const double& time, const TimeScaleUnit& format) const
    {
        try
        {
            switch (format)
            {
            case (TimeScaleUnit::NANOSECONDS):
                return time;

            case (TimeScaleUnit::MICROSECONDS):
                return time / UTILITIES.SECONDS_OVER_MILLISECONDS;

            case (TimeScaleUnit::MILLISECONDS):
                return time / UTILITIES.SECONDS_OVER_MICROSECONDS;

            case (TimeScaleUnit::SECONDS):
                return time / UTILITIES.SECONDS_OVER_NANOSECONDS;

            case (TimeScaleUnit::MINUTES):
                return time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_MINUTE);

            case (TimeScaleUnit::HOURS):
                return time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_HOUR);

            case (TimeScaleUnit::DAYS):
                return time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_DAY);

            case (TimeScaleUnit::WEEKS):
                return time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_WEEK);

            case (TimeScaleUnit::MONTHS):
                return time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_MONTH);

            case (TimeScaleUnit::YEARS):
                return time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_YEAR);

            }

            return time;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::convert_nanoseconds(): " + exception.what());
        }
    }

    std::string Time::_pad3(int value) const
    {
        try
        {
            char buf[4];
            std::snprintf(buf, sizeof(buf), "%03d", value);

            return std::string(buf);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::_pad3(): " + exception.what());
        }
    }

    std::string Time::_format_millisecond_level(
        absl::Duration since_epoch, const std::string& sep) const
    {
        try
        {
            return absl::StrCat(
                _pad3(static_cast<int>(
                    absl::ToInt64Milliseconds(since_epoch) % 1000)),
                sep
            );
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::_format_millisecond_level(): " + exception.what());
        }
    }

    std::string Time::_format_microsecond_level(
        absl::Duration since_epoch, const std::string& sep) const
    {
        try
        {
            return absl::StrCat(
                _pad3(static_cast<int>(
                    absl::ToInt64Milliseconds(since_epoch) % 1000)),
                sep,
                _pad3(static_cast<int>(
                    absl::ToInt64Microseconds(since_epoch) % 1000)),
                sep
            );
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::_format_microsecond_level(): " + exception.what());
        }
    }

    std::string Time::_format_nanosecond_level(
        absl::Duration since_epoch, const std::string& sep) const
    {
        try
        {
            return absl::StrCat(
                _pad3(static_cast<int>(
                    absl::ToInt64Milliseconds(since_epoch) % 1000)),
                sep,
                _pad3(static_cast<int>(
                    absl::ToInt64Microseconds(since_epoch) % 1000)),
                sep,
                _pad3(static_cast<int>(
                    absl::ToInt64Nanoseconds(since_epoch) % 1000)));
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::_format_nanosecond_level(): " + exception.what());
        }
    }

    std::string Time::_format_time(
        const std::tm& tm, const char* fmt) const
    {
        try
        {
            char buffer[128];
            if (std::strftime(buffer, sizeof(buffer), fmt, &tm))
            {
                return std::string(buffer);
            }

            return {};
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Time::_format_time(): " + exception.what());
        }
    }

    void Time::setup(
        Result<void>& result
    )
    {
        result.set_to_success();
    }

    void Time::now(Result<double>& result) const
    {
        result.set_to_success(
            static_cast<double>(
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now()
                    .time_since_epoch())
                .count()));
    }

    void Time::nanosecond(Result<double>& result) const
    {
        result.set_to_success(
            static_cast<double>(
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now()
                    .time_since_epoch())
                .count() % 1'000'000'000));
    }

    void Time::millisecond(Result<double>& result) const
    {
        result.set_to_success(
            static_cast<double>(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now()
                    .time_since_epoch())
                .count() % 1'000));
    }

    void Time::microsecond(Result<double>& result) const
    {
        result.set_to_success(
            static_cast<double>(
                std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::system_clock::now()
                    .time_since_epoch())
                .count() % 1'000'000));
    }

    void Time::day(Result<double>& result,
        const TimeZone& zone) const
    {
        result.set_to_success(static_cast<double>(_get_time_zone(zone).tm_mday));
    }

    void Time::hour(Result<double>& result,
        const TimeZone& zone) const
    {
        result.set_to_success(static_cast<double>(_get_time_zone(zone).tm_hour));
    }

    void Time::year(Result<double>& result,
        const TimeZone& zone) const
    {
        result.set_to_success(static_cast<double>(_get_time_zone(zone).tm_year) +
            UTILITIES.UNIX_START_YEAR_OFFSET);
    }

    void Time::month(Result<double>& result,
        const TimeZone& zone) const
    {
        result.set_to_success(static_cast<double>(_get_time_zone(zone).tm_mon) + 1);
    }

    void Time::second(Result<double>& result,
        const TimeZone& zone) const
    {
        result.set_to_success(static_cast<double>(_get_time_zone(zone).tm_sec));
    }

    void Time::minute(Result<double>& result,
        const TimeZone& zone) const
    {
        result.set_to_success(static_cast<double>(_get_time_zone(zone).tm_min));
    }

    void Time::now(Result<std::string>& result,
        const TimeFormat& format,
        const TimeZone& zone) const
    {
        absl::Time now_time = absl::Now();
        absl::Duration since_epoch = now_time - absl::UnixEpoch();
        std::tm tm = _get_time_zone(zone);
        const char* fmt = _get_format_string(format);
        std::string str;

        switch (format)
        {
        case TimeFormat::UNIX:
            str = absl::StrCat(absl::ToUnixSeconds(now_time));
            break;

        case TimeFormat::ISO8601:
        case TimeFormat::SECOND_LEVEL_TIMESTAMP:
        case TimeFormat::HOUR_12:
        case TimeFormat::HOUR_24:
        case TimeFormat::DATE_DASHED:
        case TimeFormat::DATE_MDY_SLASHED:
        case TimeFormat::DATE_DMY_SLASHED:
        case TimeFormat::DATE_DMY_SPACED:
        case TimeFormat::DATE_VERBOSE:
            str = _format_time(tm, fmt);
            break;

        case TimeFormat::MILLISECOND_LEVEL_TIMESTAMP:
            str = _format_time(tm, fmt) + "." +
                _format_millisecond_level(since_epoch, ":");
            break;

        case TimeFormat::MICROSECOND_LEVEL_TIMESTAMP:
            str = _format_time(tm, fmt) + "." +
                _format_microsecond_level(since_epoch, ":");
            break;

        case TimeFormat::FULL_TIMESTAMP:
            str = _format_time(tm, fmt) + "." +
                _format_nanosecond_level(since_epoch, ":");
            break;

        case TimeFormat::FULL_DASHED_TIMESTAMP:
            str = _format_time(tm, fmt) + "-" +
                _format_nanosecond_level(since_epoch, "-");
            break;

        case TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND:
            str = absl::StrCat(
                "ms: ", absl::ToInt64Milliseconds(since_epoch),
                ", us: ", absl::ToInt64Microseconds(since_epoch),
                ", ns: ", absl::ToInt64Nanoseconds(since_epoch));
            break;

        default:
            str = UTILITIES.TIME_FORMAT_INVALID;
            break;
        }

        result.set_to_success(str);
    }

    void Time::get_time_unit_full_name(Result<std::string>& result,
        const TimeScaleUnit& format) const
    {
        switch (format)
        {
            case TimeScaleUnit::NANOSECONDS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_NANOSECONDS); break;
            case TimeScaleUnit::MICROSECONDS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MICROSECONDS); break;
            case TimeScaleUnit::MILLISECONDS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MILLISECONDS); break;
            case TimeScaleUnit::SECONDS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_SECONDS); break;
            case TimeScaleUnit::MINUTES: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MINUTES); break;
            case TimeScaleUnit::HOURS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_HOURS); break;
            case TimeScaleUnit::DAYS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_DAYS); break;
            case TimeScaleUnit::WEEKS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_WEEKS); break;
            case TimeScaleUnit::MONTHS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MONTHS); break;
            case TimeScaleUnit::YEARS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_YEARS); break;
            default: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_SECONDS); break;
        }
    }

    void Time::get_time_unit_abbreviation(Result<std::string>& result,
        const TimeScaleUnit& format) const
    {
        switch (format)
        {
            case TimeScaleUnit::NANOSECONDS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_NANOSECONDS); break;
            case TimeScaleUnit::MICROSECONDS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MICROSECONDS); break;
            case TimeScaleUnit::MILLISECONDS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MILLISECONDS); break;
            case TimeScaleUnit::SECONDS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_SECONDS); break;
            case TimeScaleUnit::MINUTES: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MINUTES); break;
            case TimeScaleUnit::HOURS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_HOURS); break;
            case TimeScaleUnit::DAYS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_DAYS); break;
            case TimeScaleUnit::WEEKS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_WEEKS); break;
            case TimeScaleUnit::MONTHS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MONTHS); break;
            case TimeScaleUnit::YEARS: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_YEARS); break;
            default: result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_SECONDS); break;
        }
    }

    void Time::get_time_unit_abbreviation(Result<TimeScaleUnit>& result,
        const std::string& format) const
    {
        if (UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_STRINGS.contains(format))
            result.set_to_success(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_STRINGS.at(format));
        else
            result.set_to_success(TimeScaleUnit::NANOSECONDS);
    }

    void Time::convert_seconds(Result<double>& result,
        const double& time,
        const TimeScaleUnit& format) const
    {
        switch (format)
        {
            case TimeScaleUnit::NANOSECONDS: result.set_to_success(time / UTILITIES.SECONDS_OVER_NANOSECONDS); break;
            case TimeScaleUnit::MICROSECONDS: result.set_to_success(time / UTILITIES.SECONDS_OVER_MICROSECONDS); break;
            case TimeScaleUnit::MILLISECONDS: result.set_to_success(time / UTILITIES.SECONDS_OVER_MILLISECONDS); break;
            case TimeScaleUnit::SECONDS: result.set_to_success(time); break;
            case TimeScaleUnit::MINUTES: result.set_to_success(time * UTILITIES.SECONDS_PER_MINUTE); break;
            case TimeScaleUnit::HOURS: result.set_to_success(time * UTILITIES.SECONDS_PER_HOUR); break;
            case TimeScaleUnit::DAYS: result.set_to_success(time * UTILITIES.SECONDS_PER_DAY); break;
            case TimeScaleUnit::WEEKS: result.set_to_success(time * UTILITIES.SECONDS_PER_WEEK); break;
            case TimeScaleUnit::MONTHS: result.set_to_success(time * UTILITIES.SECONDS_PER_MONTH); break;
            case TimeScaleUnit::YEARS: result.set_to_success(time * UTILITIES.SECONDS_PER_YEAR); break;
            default: result.set_to_success(time); break;
        }
    }

    void Time::convert_nanoseconds(Result<double>& result,
        const double& time,
        const TimeScaleUnit& format) const
    {
        switch (format)
        {
            case TimeScaleUnit::NANOSECONDS: result.set_to_success(time); break;
            case TimeScaleUnit::MICROSECONDS: result.set_to_success(time / UTILITIES.SECONDS_OVER_MILLISECONDS); break;
            case TimeScaleUnit::MILLISECONDS: result.set_to_success(time / UTILITIES.SECONDS_OVER_MICROSECONDS); break;
            case TimeScaleUnit::SECONDS: result.set_to_success(time / UTILITIES.SECONDS_OVER_NANOSECONDS); break;
            case TimeScaleUnit::MINUTES: result.set_to_success(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_MINUTE)); break;
            case TimeScaleUnit::HOURS: result.set_to_success(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_HOUR)); break;
            case TimeScaleUnit::DAYS: result.set_to_success(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_DAY)); break;
            case TimeScaleUnit::WEEKS: result.set_to_success(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_WEEK)); break;
            case TimeScaleUnit::MONTHS: result.set_to_success(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_MONTH)); break;
            case TimeScaleUnit::YEARS: result.set_to_success(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_YEAR)); break;
            default: result.set_to_success(time); break;
        }
    }

    void Time::get_instance(Result<Time*>& result)
    {
        static Time singleton;

        result.set_to_success(&singleton);
    }
} 
