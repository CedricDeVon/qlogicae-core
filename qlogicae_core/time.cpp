#include "pch.hpp"

#include "time.hpp"

namespace QLogicaeCore
{
    Time::Time()
    {
        
    }

    Time::~Time()
    {

    }

    bool Time::setup()
    {
        try
        {
            Result<void> void_result;

            setup(void_result);

            return void_result.is_status_safe();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    std::future<bool> Time::setup_async(
        const std::function<void(const bool& value)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                bool value = setup();

                promise.set_value(
                    value
                );

                if (callback)
                {
                    callback(
                        value
                    );
                }
            }
        );

        return future;
    }

    void Time::setup_async(
        Result<std::future<void>>& result,
        const std::function<void(Result<void>& result)>& callback
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                Result<void> void_result;

                setup(void_result);

                promise.set_value();

                callback(
                    void_result
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    double Time::now()
    {
        try
        {
            Result<double> result;

            now(result);

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::now(
        Result<double>& result
    )
    {
        result.set_to_good_status_with_value(
            static_cast<double>(
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now()
                    .time_since_epoch())
                .count()));
    }

    double Time::month(const TimeZone& zone)
    {
        try
        {
            Result<double> result;

            month(
                result,
                zone
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::month(
        Result<double>& result,
        const TimeZone& zone
    )
    {
        result.set_to_good_status_with_value(
            static_cast<double>(_get_time_zone(zone).tm_mon) + 1
        );
    }

    double Time::day(const TimeZone& zone)
    {
        try
        {
            Result<double> result;

            day(
                result,
                zone
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::day(
        Result<double>& result,
        const TimeZone& zone
    )
    {
        result.set_to_good_status_with_value(
            static_cast<double>(_get_time_zone(zone).tm_mday)
        );
    }

    double Time::minute(
        const TimeZone& zone
    )
    {
        try
        {
            Result<double> result;

            minute(
                result,
                zone
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::minute(
        Result<double>& result,
        const TimeZone& zone
    )
    {
        result.set_to_good_status_with_value(
            static_cast<double>(_get_time_zone(zone).tm_min)
        );
    }

    double Time::second(
        const TimeZone& zone
    )
    {
        try
        {
            Result<double> result;

            second(
                result,
                zone
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::second(
        Result<double>& result,
        const TimeZone& zone
    )
    {
        result.set_to_good_status_with_value(
            static_cast<double>(_get_time_zone(zone).tm_sec)
        );
    }

    double Time::millisecond()
    {
        try
        {
            Result<double> result;

            millisecond(
                result
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::millisecond(
        Result<double>& result
    )
    {
        result.set_to_good_status_with_value(
            static_cast<double>(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now()
                    .time_since_epoch())
                .count() % 1'000));
    }

    double Time::microsecond()
    {
        try
        {
            Result<double> result;

            microsecond(
                result
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::microsecond(
        Result<double>& result
    )
    {
        result.set_to_good_status_with_value(
            static_cast<double>(
                std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::system_clock::now()
                    .time_since_epoch())
                .count() % 1'000'000));
    }

    double Time::nanosecond()
    {
        try
        {
            Result<double> result;

            nanosecond(
                result
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::nanosecond(
        Result<double>& result
    )
    {
        result.set_to_good_status_with_value(
            static_cast<double>(
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now()
                    .time_since_epoch())
                .count() % 1'000'000'000));
    }

    double Time::hour(
        const TimeZone& zone
    )
    {
        try
        {
            Result<double> result;

            hour(
                result,
                zone
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::hour(
        Result<double>& result,
        const TimeZone& zone
    )
    {
        result.set_to_good_status_with_value
        (static_cast<double>(_get_time_zone(zone).tm_hour)
        );
    }

    double Time::year(
        const TimeZone& zone
    )
    {
        try
        {
            Result<double> result;

            year(
                result,
                zone
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::year(
        Result<double>& result,
        const TimeZone& zone
    )
    {
        result.set_to_good_status_with_value(
            static_cast<double>(_get_time_zone(zone).tm_year) +
                UTILITIES.UNIX_START_YEAR_OFFSET);
    }

    std::string Time::now(
        const TimeFormat& format,
        const TimeZone& zone
    )
    {
        try
        {
            Result<std::string> result;

            now(
                result,
                format,
                zone
            );

            return result.get_value();            
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::now(
        Result<std::string>& result,
        const TimeFormat& format,
        const TimeZone& zone
    )
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

        result.set_to_good_status_with_value(str);
    }

    std::string_view Time::get_time_unit_full_name(
        const TimeScaleUnit& format
    )
    {
        try
        {
            Result<std::string> result;

            get_time_unit_full_name(
                result,
                format
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::get_time_unit_full_name(
        Result<std::string>& result,
        const TimeScaleUnit& format
    )
    {
        switch (format)
        {
            case TimeScaleUnit::NANOSECONDS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_NANOSECONDS); break;
            case TimeScaleUnit::MICROSECONDS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MICROSECONDS); break;
            case TimeScaleUnit::MILLISECONDS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MILLISECONDS); break;
            case TimeScaleUnit::SECONDS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_SECONDS); break;
            case TimeScaleUnit::MINUTES: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MINUTES); break;
            case TimeScaleUnit::HOURS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_HOURS); break;
            case TimeScaleUnit::DAYS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_DAYS); break;
            case TimeScaleUnit::WEEKS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_WEEKS); break;
            case TimeScaleUnit::MONTHS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_MONTHS); break;
            case TimeScaleUnit::YEARS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_YEARS); break;
            default: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_FULL_NAME_SECONDS); break;
        }
    }

    std::string_view Time::get_time_unit_abbreviation(
        const TimeScaleUnit& format
    )
    {
        try
        {
            Result<std::string> result;

            get_time_unit_abbreviation(
                result,
                format
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::get_time_unit_abbreviation(
        Result<std::string>& result,
        const TimeScaleUnit& format
    )
    {
        switch (format)
        {
            case TimeScaleUnit::NANOSECONDS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_NANOSECONDS); break;
            case TimeScaleUnit::MICROSECONDS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MICROSECONDS); break;
            case TimeScaleUnit::MILLISECONDS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MILLISECONDS); break;
            case TimeScaleUnit::SECONDS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_SECONDS); break;
            case TimeScaleUnit::MINUTES: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MINUTES); break;
            case TimeScaleUnit::HOURS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_HOURS); break;
            case TimeScaleUnit::DAYS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_DAYS); break;
            case TimeScaleUnit::WEEKS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_WEEKS); break;
            case TimeScaleUnit::MONTHS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_MONTHS); break;
            case TimeScaleUnit::YEARS: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_YEARS); break;
            default: result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_SECONDS); break;
        }
    }

    TimeScaleUnit Time::get_time_unit_abbreviation(
        const std::string& format
    )
    {
        try
        {
            Result<TimeScaleUnit> result;

            get_time_unit_abbreviation(
                result,
                format
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::get_time_unit_abbreviation(
        Result<TimeScaleUnit>& result,
        const std::string& format
    )
    {
        if (UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_STRINGS.contains(format))
            result.set_to_good_status_with_value(UTILITIES.TIME_SCALE_UNIT_ABBREVIATION_STRINGS.at(format));
        else
            result.set_to_good_status_with_value(TimeScaleUnit::NANOSECONDS);
    }

    double Time::convert_seconds(
        const double& time,
        const TimeScaleUnit& format
    )
    {
        try
        {
            Result<double> result;

            convert_seconds(
                result,
                time,
                format
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::convert_seconds(
        Result<double>& result,
        const double& time,
        const TimeScaleUnit& format
    )
    {
        switch (format)
        {
            case TimeScaleUnit::NANOSECONDS: result.set_to_good_status_with_value(time / UTILITIES.SECONDS_OVER_NANOSECONDS); break;
            case TimeScaleUnit::MICROSECONDS: result.set_to_good_status_with_value(time / UTILITIES.SECONDS_OVER_MICROSECONDS); break;
            case TimeScaleUnit::MILLISECONDS: result.set_to_good_status_with_value(time / UTILITIES.SECONDS_OVER_MILLISECONDS); break;
            case TimeScaleUnit::SECONDS: result.set_to_good_status_with_value(time); break;
            case TimeScaleUnit::MINUTES: result.set_to_good_status_with_value(time * UTILITIES.SECONDS_PER_MINUTE); break;
            case TimeScaleUnit::HOURS: result.set_to_good_status_with_value(time * UTILITIES.SECONDS_PER_HOUR); break;
            case TimeScaleUnit::DAYS: result.set_to_good_status_with_value(time * UTILITIES.SECONDS_PER_DAY); break;
            case TimeScaleUnit::WEEKS: result.set_to_good_status_with_value(time * UTILITIES.SECONDS_PER_WEEK); break;
            case TimeScaleUnit::MONTHS: result.set_to_good_status_with_value(time * UTILITIES.SECONDS_PER_MONTH); break;
            case TimeScaleUnit::YEARS: result.set_to_good_status_with_value(time * UTILITIES.SECONDS_PER_YEAR); break;
            default: result.set_to_good_status_with_value(time); break;
        }
    }

    double Time::convert_nanoseconds(
        const double& time,
        const TimeScaleUnit& format
    )
    {
        try
        {
            Result<double> result;

            convert_nanoseconds(
                result,
                time,
                format
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Time::convert_nanoseconds(
        Result<double>& result,
        const double& time,
        const TimeScaleUnit& format
    )
    {
        switch (format)
        {
            case TimeScaleUnit::NANOSECONDS: result.set_to_good_status_with_value(time); break;
            case TimeScaleUnit::MICROSECONDS: result.set_to_good_status_with_value(time / UTILITIES.SECONDS_OVER_MILLISECONDS); break;
            case TimeScaleUnit::MILLISECONDS: result.set_to_good_status_with_value(time / UTILITIES.SECONDS_OVER_MICROSECONDS); break;
            case TimeScaleUnit::SECONDS: result.set_to_good_status_with_value(time / UTILITIES.SECONDS_OVER_NANOSECONDS); break;
            case TimeScaleUnit::MINUTES: result.set_to_good_status_with_value(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_MINUTE)); break;
            case TimeScaleUnit::HOURS: result.set_to_good_status_with_value(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_HOUR)); break;
            case TimeScaleUnit::DAYS: result.set_to_good_status_with_value(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_DAY)); break;
            case TimeScaleUnit::WEEKS: result.set_to_good_status_with_value(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_WEEK)); break;
            case TimeScaleUnit::MONTHS: result.set_to_good_status_with_value(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_MONTH)); break;
            case TimeScaleUnit::YEARS: result.set_to_good_status_with_value(time / (UTILITIES.SECONDS_OVER_NANOSECONDS * UTILITIES.SECONDS_PER_YEAR)); break;
            default: result.set_to_good_status_with_value(time); break;
        }
    }

    std::string Time::_pad3(
        int value
    )
    {
        try
        {
            char buf[4];
            std::snprintf(buf, sizeof(buf), "%03d", value);

            return std::string(buf);
        }
        catch (const std::exception& exception)
        {

        }
    }

    std::string Time::_format_millisecond_level(
        absl::Duration since_epoch,
        const std::string& sep
    )
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

        }
    }

    std::string Time::_format_microsecond_level(
        absl::Duration since_epoch,
        const std::string& sep
    )
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

        }
    }

    std::string Time::_format_nanosecond_level(
        absl::Duration since_epoch,
        const std::string& sep
    )
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

        }
    }

    std::string Time::_format_time(
        const std::tm& tm,
        const char* fmt
    )
    {
        try
        {
            char buffer[64];
            if (std::strftime(buffer, sizeof(buffer), fmt, &tm))
            {
                return std::string(buffer);
            }

            return {};
        }
        catch (const std::exception& exception)
        {

        }
    }

    std::tm Time::_get_time_zone(
        const TimeZone& zone
    )
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

        }
    }

    const char* Time::_get_format_string(
        const TimeFormat& format
    )
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

        }
    }

    Time& Time::get_instance()
    {
        static Time singleton;

        return singleton;
    }

    void Time::get_instance(
        Result<Time*>& result
    )
    {
        static Time instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
} 
