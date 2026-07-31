#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		IntervalClockConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		IntervalClockConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<IntervalClockConfigurations>
    {
	public:
		std::function<bool(const size_t& current_iteration)>
			callback =
				[](const size_t& current_iteration) { return true; };

		size_t
			maximum_interval_count =
				1;

		std::chrono::milliseconds
			delay_in_milliseconds =
				std::chrono::milliseconds{ 1000 };

		bool
			is_executed_immediately =
				true;

		IntervalClockConfigurations();
    };
}

#endif
