#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeoutClock \
	)

#include "timeout_clock_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	class
		TimeoutClock :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TimeoutClockConfigurations>
	{
	public:
		std::jthread
			thread_1;

		std::mutex
			mutex_1;

		std::atomic<bool>
			is_flag_stopped_async
				{ false };

		std::atomic<bool>
			is_cancelled_async
				{ false };

		std::atomic<bool>
			is_executed_immediately_async
				{ false };

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		TimeoutClock();

		~TimeoutClock();

		bool
			construct();

		bool
			destruct();

		bool
			start();

		bool
			cancel();

		bool
			restart();

		bool
			is_cancelled();
	};
}

#endif
