#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		IntervalClock \
	)

#include "interval_clock_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		IntervalClock :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<IntervalClockConfigurations>
    {
    public:
		std::thread
			thread_1;

		mutable std::mutex
			mutex_1;

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3
		);

		std::atomic<bool>
			is_paused_async { false };

		std::atomic<bool>
			is_running_async { false };

		std::atomic<bool>
			is_cancelled_async { false };

		std::atomic<size_t>
			execution_count_async { 0 };

		std::condition_variable
			condition_variable;

		IntervalClock();

		~IntervalClock();

		bool
			construct();

		bool
			destruct();

		bool
			start();

		bool
			stop();

		bool
			pause();

		bool
			resume();

		bool
			cancel();

		bool
			restart();

		bool
			is_paused();

		bool
			is_running();

		bool
			is_cancelled();

		size_t
			get_execution_count();

		bool
			run_interval();
		
	};
}

#endif
