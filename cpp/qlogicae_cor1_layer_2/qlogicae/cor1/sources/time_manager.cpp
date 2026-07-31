#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeManager \
	)

#include "../includes/time_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    TimeManager
		::TimeManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TimeManagerConfigurations>()
	{
				
	}

	std::string
		TimeManager
			::get_now(
				const TimeFormat&
					format
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				format == TimeFormat::NONE
			);

			absl::Time now_time = absl::Now();
			absl::Duration since_epoch = now_time - absl::UnixEpoch();
			std::tm tm = get_time_zone();
			const char* fmt = get_format_string(format);
			std::string str;

			switch (format)
			{
				case TimeFormat::UNIX:
				{
					str = absl::StrCat(absl::ToUnixSeconds(now_time));
					break;
				}
				case TimeFormat::ISO8601:
				case TimeFormat::SECOND_LEVEL_TIMESTAMP:
				case TimeFormat::HOUR_12:
				case TimeFormat::HOUR_24:
				case TimeFormat::DATE_DASHED:
				case TimeFormat::DATE_MDY_SLASHED:
				case TimeFormat::DATE_DMY_SLASHED:
				case TimeFormat::DATE_DMY_SPACED:
				case TimeFormat::DATE_VERBOSE:
				{
					str = format_time(tm, fmt);
					break;
				}
				case TimeFormat::MILLISECOND_LEVEL_TIMESTAMP:
				{
					str = format_time(tm, fmt) + "." +
						format_millisecond_level(since_epoch, ":");
					break;
				}
				case TimeFormat::MICROSECOND_LEVEL_TIMESTAMP:
				{
					str = format_time(tm, fmt) + "." +
						format_microsecond_level(since_epoch, ":");
					break;
				}
				case TimeFormat::FULL_TIMESTAMP:
				{
					str = format_time(tm, fmt) + "." +
						format_nanosecond_level(since_epoch, ":");
					break;
				}
				case TimeFormat::FULL_DASHED_TIMESTAMP:
				{
					str = format_time(tm, fmt) + "-" +
						format_nanosecond_level(since_epoch, "-");
					break;
				}
				case TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND:
				{
					int64_t ms = absl::ToInt64Milliseconds(since_epoch);
					int64_t us = absl::ToInt64Microseconds(since_epoch);
					int64_t ns = absl::ToInt64Nanoseconds(since_epoch);

					if (ms < 0 || us < 0 || ns < 0) {
						str = "";
						break;
					}

					str = absl::StrCat("ms: ", ms, ", us: ", us, ", ns: ", ns);
					break;
				}
				default:
				{
					str = "";
					break;
				}
			}

			return
				str;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	const char*
		TimeManager
			::get_format_string(
				const TimeFormat&
					time_format
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				time_format == TimeFormat::NONE
			);

			switch (time_format)
			{
				case TimeFormat::ISO8601:
				{
					return "%Y-%m-%dT%H:%M:%S";
				}
				case TimeFormat::FULL_TIMESTAMP:
				{
					return "%Y-%m-%d] [%H:%M:%S";
				}
				case TimeFormat::FULL_DASHED_TIMESTAMP:
				{
					return "%Y-%m-%d-%H-%M-%S";
				}
				case TimeFormat::HOUR_12:
				{
					return "%I:%M:%S %p";
				}
				case TimeFormat::HOUR_24:
				{
					return "%H:%M:%S";
				}
				case TimeFormat::DATE_DASHED:
				{
					return "%Y-%m-%d";
				}
				case TimeFormat::DATE_MDY_SLASHED:
				{
					return "%m/%d/%Y";
				}
				case TimeFormat::DATE_DMY_SLASHED:
				{
					"%d/%m/%Y";
				}
				case TimeFormat::DATE_DMY_SPACED:
				{
					return "%d %m %Y";
				}
				case TimeFormat::DATE_VERBOSE:
				{
					return "%A, %B %d, %Y";
				}
				default:
				{
					return "";
				}
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::tm
		TimeManager
			::get_time_zone()
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				std::tm {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			std::time_t time =
				std::chrono::system_clock::to_time_t(
					std::chrono::system_clock::now()
				);

			std::tm tm{};
			if (configurations.time_zone == TimeZone::UTC)
			{
				gmtime_s(&tm, &time);
			}
			else
			{
				localtime_s(&tm, &time);
			}

			return
				tm;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}
	
	std::string
		TimeManager
			::pad3(
				int value
			)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__EDGE_CASE_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			char buf[4];
			std::snprintf(buf, sizeof(buf), "%03d", value);

			return
				std::string(buf);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	double
		TimeManager
			::convert_seconds(
				const double&
					time,
				const TimeScaleUnit&
					format
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				time <= 0.0 ||
				format == TimeScaleUnit::NONE
			);

			switch (format)
			{
				case TimeScaleUnit::NANOSECONDS: return time / 1'000'000'000.0;
				case TimeScaleUnit::MICROSECONDS: return time / 1'000'000.0;
				case TimeScaleUnit::MILLISECONDS: return time / 1'000.0;
				case TimeScaleUnit::SECONDS: return time;
				case TimeScaleUnit::MINUTES: return time * 60.0;
				case TimeScaleUnit::HOURS: return time * 3'600.0;
				case TimeScaleUnit::DAYS: return time * 86'400.0;
				case TimeScaleUnit::WEEKS: return time * 604'800.0;
				case TimeScaleUnit::MONTHS: return time * 2'629'746.0;
				case TimeScaleUnit::YEARS: return time * 31'557'600.0;
				default: return 0.0;
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	double
		TimeManager
			::convert_nanoseconds(
				const double&
					time,
				const TimeScaleUnit&
					format
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				time <= 0.0 ||
				format == TimeScaleUnit::NONE
			);

			switch (format)
			{
				case TimeScaleUnit::NANOSECONDS: return time;
				case TimeScaleUnit::MICROSECONDS: return time / 1'000.0;
				case TimeScaleUnit::MILLISECONDS: return time / 1'000'000.0;
				case TimeScaleUnit::SECONDS: return time / 1'000'000'000.0;
				case TimeScaleUnit::MINUTES: return time / (1'000'000'000.0 * 60.0);
				case TimeScaleUnit::HOURS: return time / (1'000'000'000.0 * 3'600.0);
				case TimeScaleUnit::DAYS: return time / (1'000'000'000.0 * 86'400.0);
				case TimeScaleUnit::WEEKS: return time / (1'000'000'000.0 * 604'800.0);
				case TimeScaleUnit::MONTHS: return time / (1'000'000'000.0 * 2'629'746.0);
				case TimeScaleUnit::YEARS: return time / (1'000'000'000.0 * 31'557'600.0);
				default: return 0.0;
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::string
		TimeManager
			::format_millisecond_level(
				absl::Duration
					since_epoch,
				const std::string&
					sep
			)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			return
				absl::StrCat(
					pad3(static_cast<int>(
						absl::ToInt64Milliseconds(since_epoch) % 1000)),
					sep
				);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::string
		TimeManager
			::format_microsecond_level(
				absl::Duration
					since_epoch,
				const std::string&
					sep
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			return
				absl::StrCat(
					pad3(static_cast<int>(
						absl::ToInt64Milliseconds(since_epoch) % 1000)),
					sep,
					pad3(static_cast<int>(
						absl::ToInt64Microseconds(since_epoch) % 1000)),
					sep
				);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::string
		TimeManager
			::format_nanosecond_level(
				absl::Duration
					since_epoch,
				const std::string&
					sep
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			return
				absl::StrCat(
					pad3(static_cast<int>(
						absl::ToInt64Milliseconds(since_epoch) % 1000)),
					sep,
					pad3(static_cast<int>(
						absl::ToInt64Microseconds(since_epoch) % 1000)),
					sep,
					pad3(static_cast<int>(
						absl::ToInt64Nanoseconds(since_epoch) % 1000))
				);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::string
		TimeManager
			::format_time(
				const std::tm&
					tm,
				const char*
					fmt
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			char buffer[64];
			if (std::strftime(buffer, sizeof(buffer), fmt, &tm))
			{
				return std::string(buffer);
			}

			return {};
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}
} 

#endif

