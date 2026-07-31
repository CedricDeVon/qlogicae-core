#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RuntimeExecutionManager \
	)

#include "../includes/runtime_execution_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	RuntimeExecutionManager
		::RuntimeExecutionManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RuntimeExecutionManagerConfigurations>()
	{
		construct();	
	}

	RuntimeExecutionManager
		::~RuntimeExecutionManager()
	{
		destruct();	
	}
    
    bool
        RuntimeExecutionManager
			::construct()
    {
        try
        {						
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			cycles_per_microsecond =
				0.0;

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

    bool
        RuntimeExecutionManager
			::destruct()
    {
        try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			cycles_per_microsecond =
				0.0;

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }
	
	bool
		RuntimeExecutionManager
			::delay_execution(			
				const double&
					value,
				const TimeScaleUnit&
					time_scale_unit
		)
	{
		try
        {										
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				time_scale_unit == TimeScaleUnit::NONE
			);
		
			switch (time_scale_unit)
			{	
				case (TimeScaleUnit::YEARS):
					return
						delay_execution_in_years(
							value
						);
				
				case (TimeScaleUnit::MONTHS):
					return
						delay_execution_in_months(
							value
						);
				
				case (TimeScaleUnit::WEEKS):
					return
						delay_execution_in_weeks(
							value
						);
				
				case (TimeScaleUnit::DAYS):
					return
						delay_execution_in_days(
							value
						);
				
				case (TimeScaleUnit::HOURS):
					return
						delay_execution_in_hours(
							value
						);
				
				case (TimeScaleUnit::MINUTES):
					return
						delay_execution_in_minutes(
							value
						);
				
				case (TimeScaleUnit::SECONDS):
					return
						delay_execution_in_seconds(
							value
						);
				
				case (TimeScaleUnit::MILLISECONDS):
					return
						delay_execution_in_milliseconds(
							value
						);

				case (TimeScaleUnit::MICROSECONDS):
					return
						delay_execution_in_microseconds(
							value
						);
				
				case (TimeScaleUnit::NANOSECONDS):
					return
						delay_execution_in_nanoseconds(
							value
						);

				default:
					return
						false;
			}

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RuntimeExecutionManager
			::delay_execution_in_years(
				const double&
					value
		)
	{
		return
			delay_execution_in_days(
				value * 365.25
			);
	}

	bool
		RuntimeExecutionManager
			::delay_execution_in_months(
				const double&
					value
		)
	{
		return
			delay_execution_in_days(
				value * 30.44
			);
	}
	
	bool
		RuntimeExecutionManager
			::delay_execution_in_weeks(
				const double&
					value
		)
	{
		return
			delay_execution_in_days(
				value * 7
			);
	}

	bool
		RuntimeExecutionManager
			::delay_execution_in_days(
				const double&
					value
		)
	{
		return
			delay_execution_in_hours(
				value * 24.0
			);
	}

	bool
		RuntimeExecutionManager
			::delay_execution_in_hours(
				const double&
					value
		)
	{
		return
			delay_execution_in_minutes(
				value * 60.0
			);
	}

	bool
		RuntimeExecutionManager
			::delay_execution_in_minutes(
				const double&
					value
		)
	{
		return
			delay_execution_in_seconds(
				value * 60.0
			);
	}

	bool
		RuntimeExecutionManager
			::delay_execution_in_seconds(
				const double&
					value
		)
	{
		return
			delay_execution_in_microseconds(
				value * 1'000'000.0
			);
	}

	bool
		RuntimeExecutionManager
			::delay_execution_in_milliseconds(
				const double&
					value
		)
	{
		return
			delay_execution_in_microseconds(
				value * 1'000.0
			);
	}

	bool
		RuntimeExecutionManager
			::delay_execution_in_microseconds(
				const double&
					value
		)
	{
		try
        {				
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				value <= 0.0 ||
				value > 1e12
			);
		
			LARGE_INTEGER frequency;
			LARGE_INTEGER start;
			LARGE_INTEGER current;

			QueryPerformanceFrequency(&frequency);
			QueryPerformanceCounter(&start);

			double elapsed = 0.0;
			while (elapsed < value)
			{
				QueryPerformanceCounter(&current);
				elapsed = static_cast<double>(
					current.QuadPart - start.QuadPart
					) * 1'000'000.0 / static_cast<double>(frequency.QuadPart);
			}

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RuntimeExecutionManager
			::delay_execution_in_nanoseconds(
				const double&
					value
		)
	{
		return
			delay_execution_in_microseconds(
				value / 1'000.0
			);
	}

	bool
		RuntimeExecutionManager
			::calibrate()
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			is_calibrated =
				false;

			cached_frequency =
				0.0;

			if (is_calibrated.load())
			{
				cycles_per_microsecond =
					cached_frequency;

				return
					true;
			}

			LARGE_INTEGER
				frequency;
			
			LARGE_INTEGER
				start;
			
			LARGE_INTEGER
				end;

			QueryPerformanceFrequency(&frequency);
			QueryPerformanceCounter(&start);

			unsigned long long tsc_start = __rdtsc();
			std::this_thread::sleep_for(std::chrono::microseconds(100));
			unsigned long long tsc_end = __rdtsc();

			QueryPerformanceCounter(&end);

			const double elapsed_seconds =
				static_cast<double>(end.QuadPart - start.QuadPart) /
				static_cast<double>(frequency.QuadPart);

			const double cpu_frequency_hz =
				(tsc_end - tsc_start) / elapsed_seconds;

			cycles_per_microsecond = cpu_frequency_hz / 1'000'000.0;
			cached_frequency = cycles_per_microsecond;
			is_calibrated.store(true);

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RuntimeExecutionManager
			::real_time_stamp_counter(
				const double&
					microseconds
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				microseconds <= 0.0 ||
				microseconds > 1e12
			);		

			if (cycles_per_microsecond == 0.0)
			{
				calibrate();
			}

			unsigned __int64 start =
				__rdtsc();
			unsigned __int64 target =
				static_cast<unsigned __int64>(
					microseconds * cycles_per_microsecond
				);

			while ((__rdtsc() - start) < target)
			{
				_mm_pause();
			}

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RuntimeExecutionManager
			::query_performance_counter(
				const double&
					microseconds
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				microseconds <= 0.0 ||
				microseconds > 1e12
			);

			LARGE_INTEGER frequency;
			LARGE_INTEGER start;
			LARGE_INTEGER current;

			QueryPerformanceFrequency(&frequency);
			QueryPerformanceCounter(&start);

			double elapsed = 0.0;

			do
			{
				QueryPerformanceCounter(&current);
				elapsed = (current.QuadPart - start.QuadPart) *
					1'000'000.0 / frequency.QuadPart;
			}
			while
			(
				elapsed < microseconds
			);

			return
				true;
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
