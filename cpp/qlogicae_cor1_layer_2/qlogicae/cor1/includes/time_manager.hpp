#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeManager \
	)

#include "time_zone.hpp"
#include "time_format.hpp"
#include "time_scale_unit.hpp"
#include "time_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TimeManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TimeManagerConfigurations>
    {
    public:
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		TimeManager();

		template <typename Type> Type
			get_now();

		template <typename Type> Type
			get_nanosecond();

		template <typename Type> Type
			get_millisecond();

		template <typename Type> Type
			get_microsecond();

		template <typename Type> Type
			get_day();

		template <typename Type> Type
			get_hour();

		template <typename Type> Type
			get_year();

		template <typename Type> Type
			get_month();

		template <typename Type> Type
			get_second();

		template <typename Type> Type
			get_minute();

		std::string
			get_now(
				const TimeFormat&
					time_format
			);

		std::string
			format_time(
				const std::tm&
					tm,
				const char*
					fmt
			);

		const char*
			get_format_string(
				const TimeFormat&
					time_format
			);

		std::tm
			get_time_zone();

		std::string
			pad3(
				int
					value
			);

		double
			convert_seconds(
				const double&
					time,
				const TimeScaleUnit&
					format
			);

		double
			convert_nanoseconds(
				const double&
					time,
				const TimeScaleUnit&
					format
			);

		std::string
			format_millisecond_level(
				absl::Duration
					since_epoch,
				const std::string&
					sep
			);

		std::string
			format_microsecond_level(
				absl::Duration
					since_epoch,
				const std::string&
					sep
			);

		std::string
			format_nanosecond_level(
				absl::Duration
					since_epoch,
				const std::string&
					sep
			);
	};

	template <typename Type> Type
		TimeManager
			::get_now()
	{
		try
		{			
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::high_resolution_clock::now().time_since_epoch()
			).count();

			if constexpr (std::is_same_v<Type, double>)
			{
				return static_cast<double>(ns);
			}			
			else if constexpr (std::is_same_v<Type, int64_t>)
			{
				return static_cast<int64_t>(ns);
			}			
			else if constexpr (std::is_same_v<Type, std::string>)
			{
				return absl::StrCat(ns);
			}			
			else if constexpr (std::is_same_v<Type, std::wstring>)
			{
				return std::to_wstring(ns);
			}			
			else
			{
				return Type{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}
	
	template <typename Type> Type
		TimeManager
			::get_nanosecond()
	{
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::system_clock::now().time_since_epoch()
			).count() % 1'000'000'000;

			if constexpr (std::is_same_v<Type, double>)
			{
				return static_cast<double>(ns);
			}			
			else if constexpr (std::is_same_v<Type, int64_t>)
			{
				return static_cast<int64_t>(ns);
			}			
			else if constexpr (std::is_same_v<Type, std::string>)
			{
				return absl::StrCat(ns);
			}			
			else if constexpr (std::is_same_v<Type, std::wstring>)
			{
				return std::to_wstring(ns);
			}			
			else
			{
				return Type{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}

	template <typename Type> Type
		TimeManager
			::get_microsecond()
	{
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto us = std::chrono::duration_cast<std::chrono::microseconds>(
				std::chrono::system_clock::now().time_since_epoch()
			).count() % 1'000'000;

			if constexpr (std::is_same_v<Type, double>)
			{
				return static_cast<double>(us);
			}			
			else if constexpr (std::is_same_v<Type, int64_t>)
			{
				return static_cast<int64_t>(us);
			}			
			else if constexpr (std::is_same_v<Type, std::string>)
			{
				return absl::StrCat(us);
			}			
			else if constexpr (std::is_same_v<Type, std::wstring>)
			{
				return std::to_wstring(us);
			}			
			else
			{
				return Type{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}

	template <typename Type> Type
		TimeManager
			::get_millisecond()
	{
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch()
			).count() % 1'000;

			if constexpr (std::is_same_v<Type, double>)
			{
				return static_cast<double>(ms);
			}			
			else if constexpr (std::is_same_v<Type, int64_t>)
			{
				return static_cast<int64_t>(ms);
			}			
			else if constexpr (std::is_same_v<Type, std::string>)
			{
				return absl::StrCat(ms);
			}			
			else if constexpr (std::is_same_v<Type, std::wstring>)
			{
				return std::to_wstring(ms);
			}			
			else
			{
				return Type{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}

	template <typename Type> Type
		TimeManager
			::get_second()
	{
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto sec = get_time_zone().tm_sec;

			if constexpr (std::is_same_v<Type, double>)
			{
				return static_cast<double>(sec);
			}			

			else if constexpr (std::is_same_v<Type, int>)
			{
				return static_cast<int>(sec);
			}			

			else if constexpr (std::is_same_v<Type, std::string>)
			{
				return absl::StrCat(sec);
			}			

			else if constexpr (std::is_same_v<Type, std::wstring>)
			{
				return std::to_wstring(sec);
			}			

			else
			{
				return Type{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}

	template <typename Type> Type
		TimeManager
			::get_minute()
	{
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto min = get_time_zone().tm_min;

			if constexpr (std::is_same_v<Type, double>)
			{
				return static_cast<double>(min);
			}			
			else if constexpr (std::is_same_v<Type, int>)
			{
				return static_cast<int>(min);
			}			
			else if constexpr (std::is_same_v<Type, std::string>)
			{
				return absl::StrCat(min);
			}			
			else if constexpr (std::is_same_v<Type, std::wstring>)
			{
				return std::to_wstring(min);
			}			
			else
			{
				return Type{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}

	template <typename Type> Type
		TimeManager
			::get_hour()
	{
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto h = get_time_zone().tm_hour;

			if constexpr (std::is_same_v<Type, double>)
			{
				return static_cast<double>(h);
			}			
			else if constexpr (std::is_same_v<Type, int>)
			{
				return h;
			}			
			else if constexpr (std::is_same_v<Type, std::string>)
			{
				return absl::StrCat(h);
			}			
			else if constexpr (std::is_same_v<Type, std::wstring>)
			{
				return std::to_wstring(h);
			}			
			else
			{
				return Type{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}

	template <typename Type> Type
		TimeManager
			::get_day()
	{
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto d = get_time_zone().tm_mday;

			if constexpr (std::is_same_v<Type, double>)
			{
				return static_cast<double>(d);
			}			
			else if constexpr (std::is_same_v<Type, int>)
			{
				return d;
			}			
			else if constexpr (std::is_same_v<Type, std::string>)
			{
				return absl::StrCat(d);
			}			
			else if constexpr (std::is_same_v<Type, std::wstring>)
			{
				return std::to_wstring(d);
			}			
			else
			{
				return Type{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}

	template <typename Type> Type
		TimeManager
			::get_month()
	{
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto m = get_time_zone().tm_mon + 1;

			if constexpr (std::is_same_v<Type, double>)
			{
				return static_cast<double>(m);
			}			
			else if constexpr (std::is_same_v<Type, int>)
			{
				return m;
			}			
			else if constexpr (std::is_same_v<Type, std::string>)
			{
				return absl::StrCat(m);
			}			
			else if constexpr (std::is_same_v<Type, std::wstring>)
			{
				return std::to_wstring(m);
			}			
			else
			{
				return Type{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}

	template <typename Type> Type
		TimeManager
			::get_year()
	{
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto y = get_time_zone().tm_year + 1900;

			if constexpr (std::is_same_v<Type, double>)
			{
				return static_cast<double>(y);
			}			
			else if constexpr (std::is_same_v<Type, int>)
			{
				return y;
			}			
			else if constexpr (std::is_same_v<Type, std::string>)
			{
				return absl::StrCat(y);
			}			
			else if constexpr (std::is_same_v<Type, std::wstring>)
			{
				return std::to_wstring(y);
			}			
			else
			{
				return Type{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}
}

#endif
