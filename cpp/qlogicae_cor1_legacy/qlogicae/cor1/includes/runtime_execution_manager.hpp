#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RuntimeExecutionManager \
	)

#include "time_scale_unit.hpp"
#include "runtime_execution_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		RuntimeExecutionManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RuntimeExecutionManagerConfigurations>
    {
    public:
		double
			cycles_per_microsecond;

		std::atomic<bool>
			is_calibrated;

		std::atomic<double>
			cached_frequency;

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		RuntimeExecutionManager();

		~RuntimeExecutionManager();

		bool
			construct();

		bool
			destruct();

		bool
			delay_execution(			
				const double&
					value,
				const TimeScaleUnit&
					time_scale_unit
			);

		bool
			delay_execution_in_years(			
				const double&
					value
			);

		bool
			delay_execution_in_months(			
				const double&
					value
			);

		bool
			delay_execution_in_weeks(			
				const double&
					value
			);

		bool
			delay_execution_in_days(			
				const double&
					value
			);

		bool
			delay_execution_in_hours(			
				const double&
					value
			);

		bool
			delay_execution_in_minutes(			
				const double&
					value
			);

		bool
			delay_execution_in_seconds(
				const double&
					value
			);

		bool
			delay_execution_in_milliseconds(
				const double&
					value
			);

		bool
			delay_execution_in_microseconds(
				const double&
					value
			);

		bool
			delay_execution_in_nanoseconds(
				const double&
					value
			);

		bool
			calibrate();

		bool
			real_time_stamp_counter(			
				const double&
					microseconds
			);

		bool
			query_performance_counter(			
				const double&
					microseconds
			);
	};
}

#endif
