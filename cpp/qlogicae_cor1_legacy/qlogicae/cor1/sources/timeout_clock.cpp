#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeoutClock \
	)

#include "../includes/timeout_clock.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    TimeoutClock
		::TimeoutClock() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TimeoutClockConfigurations>()
	{
		construct();	
	}

	TimeoutClock
		::~TimeoutClock()
	{
		destruct();	
	}
    
    bool
        TimeoutClock
			::construct()
    {
        try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			is_executed_immediately_async.store(configurations.is_executed_immediately);
			is_flag_stopped_async.store(false);
			is_cancelled_async.store(false);

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
        TimeoutClock
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

			return
				cancel();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			return
				handle_error_outputs(
					exception
				);
        }
    }


	bool
		TimeoutClock
			::start()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);
			
			if (thread_1.joinable())
			{
				thread_1.request_stop();
				thread_1.join();
			}

			auto local_callback = configurations.callback;
			auto local_delay = configurations.delay_in_milliseconds;
			bool execute_immediately = configurations.is_executed_immediately || local_delay.count() == 0;

			thread_1 = std::jthread([local_callback, local_delay, execute_immediately](std::stop_token stop_token)
				{
					if (!execute_immediately)
					{
						std::this_thread::sleep_for(local_delay);
					}

					if (stop_token.stop_requested())
					{
						return;
					}

					try
					{
						local_callback();
					}
					catch (...)
					{
					}
				});

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
		TimeoutClock
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
			is_flag_stopped_async.store(true);

			if (thread_1.joinable())
			{
				thread_1.request_stop();
				if (std::this_thread::get_id() != thread_1.get_id())
				{
					thread_1.join();
				}
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
		TimeoutClock
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

			is_flag_stopped_async
				.store(false);
			is_cancelled_async
				.store(false);
			is_executed_immediately_async
				.store(
					configurations.is_executed_immediately
				);
			
			return
				start();
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
		TimeoutClock
			::is_cancelled()
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			
			
			return
				is_cancelled_async.load();
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
