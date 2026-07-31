#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		IntervalClock \
	)

#include "../includes/interval_clock.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    IntervalClock
		::IntervalClock() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<IntervalClockConfigurations>()
    {
        construct();
    }

    IntervalClock
		::~IntervalClock()
    {
        destruct();
    }

    bool
        IntervalClock
			::construct()
    {
        try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			is_cancelled_async.store(false);
			is_paused_async.store(false);
			is_running_async.store(false);
			execution_count_async.store(0);

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
        IntervalClock
			::destruct()
    {
        try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			cancel();

			if (thread_1.joinable())
			{
				thread_1.join();
			}

			is_cancelled_async.store(false);
			is_paused_async.store(false);
			is_running_async.store(false);
			execution_count_async.store(0);

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
		IntervalClock
			::start()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				configurations.maximum_interval_count == 0 ||
				configurations.delay_in_milliseconds.count() == 0
			);			

			if (is_running_async.load())
			{
				return true;
			}


			if (thread_1.joinable())
			{
				thread_1.join();
			}

			is_cancelled_async.store(false);
			is_paused_async.store(false);
			is_running_async.store(true);
			execution_count_async.store(0);

			thread_1 = std::thread(
				&IntervalClock::run_interval,
				this
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

	bool
		IntervalClock
			::stop()
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			is_cancelled_async.store(true);
			is_running_async.store(false);
			is_paused_async.store(false);
			condition_variable.notify_all();

			if (thread_1.joinable() && !is_running_async.load())
			{
				thread_1.join();
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
		IntervalClock
			::pause()
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			is_paused_async.store(true);

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
		IntervalClock
			::resume()
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			if (is_paused_async.load())
			{
				is_paused_async.store(false);
				condition_variable.notify_all();
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
		IntervalClock
			::cancel()
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			is_cancelled_async.store(true);
			is_paused_async.store(false);
			is_running_async.store(false);
			condition_variable.notify_all();

			if (thread_1.joinable())
			{
				thread_1.join();
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
		IntervalClock
			::restart()
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			cancel();

			execution_count_async.store(0);
			is_cancelled_async.store(false);
			is_paused_async.store(false);
			is_running_async.store(true);

			start();

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
		IntervalClock
			::is_paused()
	{
		return
			is_paused_async
				.load();
	}

	bool
		IntervalClock
			::is_running()
	{
		return
			is_running_async
				.load();
	}

	bool
		IntervalClock
			::is_cancelled()
	{
		return
			is_cancelled_async
				.load();
	}

	size_t
		IntervalClock
			::get_execution_count()
	{
		return
			execution_count_async
				.load();
	}

	bool
		IntervalClock
			::run_interval()
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			if (!is_running_async.load())
			{
				is_running_async.store(true);
				is_cancelled_async.store(false);
			}

			if (configurations.is_executed_immediately &&
				!is_cancelled_async.load())
			{
				size_t current = ++execution_count_async;

				bool should_continue = false;
				try
				{
					should_continue = configurations.callback(current);
				}
				catch (...)
				{
					should_continue = false;
				}

				if (!should_continue)
				{
					is_running_async.store(false);
					condition_variable.notify_all();

					return
						true;
				}

				if (configurations.maximum_interval_count &&
					execution_count_async.load() >= configurations.maximum_interval_count)
				{
					is_running_async.store(false);
					condition_variable.notify_all();

					return
						true;
				}
			}

			while (!is_cancelled_async.load() && is_running_async.load())
			{
				std::unique_lock<std::mutex> lock(
					mutex_1
				);

				if (is_paused_async.load())
				{
					condition_variable.wait(lock, [this]() {
						return !is_paused_async.load() || is_cancelled_async.load();
						});
				}

				if (is_cancelled_async.load() || !is_running_async.load())
				{
					break;
				}

				auto start = std::chrono::steady_clock::now();
				lock.unlock();

				size_t current = ++execution_count_async;

				bool should_continue = false;
				try
				{
					should_continue = configurations.callback(current);
				}
				catch (...)
				{
					should_continue = false;
				}

				if (!should_continue)
				{
					is_running_async.store(false);
					condition_variable.notify_all();

					return
						true;
				}

				if (configurations.maximum_interval_count &&
					execution_count_async.load() >= configurations.maximum_interval_count)
				{
					is_running_async.store(false);
					condition_variable.notify_all();

					return
						true;
				}

				auto end = std::chrono::steady_clock::now();
				auto elapsed =
					std::chrono::duration_cast<std::chrono::milliseconds>(
						end - start
					);
				auto delay =
					configurations.delay_in_milliseconds > elapsed ?
					configurations.delay_in_milliseconds - elapsed :
					std::chrono::milliseconds(0);

				for (std::chrono::milliseconds waited(0);
					waited < delay && !is_cancelled_async.load() && is_running_async.load();
					)
				{
					auto to_wait = std::min<std::chrono::milliseconds>(
						std::chrono::milliseconds(50),
						delay - waited
					);

					std::this_thread::sleep_for(to_wait);
					waited += to_wait;
				}
			}

			is_running_async.store(false);
			condition_variable.notify_all();

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

