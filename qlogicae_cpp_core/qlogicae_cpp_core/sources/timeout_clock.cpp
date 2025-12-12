#include "pch.hpp"

#include "../includes/timeout_clock.hpp"

namespace QLogicaeCppCore
{
    TimeoutClock::TimeoutClock()
    {
        Result<bool> result;
        construct(result);
    }

    TimeoutClock::TimeoutClock(
        const TimeoutClockConfigurations& initial_configurations
    )
    {
        Result<bool> result;
        construct(result, initial_configurations);
    }

    TimeoutClock::~TimeoutClock()
    {
        Result<bool> result;
        destruct(result);
    }

    void TimeoutClock::construct(
        Result<bool>& result
    )
    {
        TimeoutClockConfigurations default_config;
        construct(result, default_config);
    }

    void TimeoutClock::construct(
        Result<bool>& result,
        const TimeoutClockConfigurations& initial_configurations
    )
    {        
        configurations = initial_configurations;
        _is_executed_immediately_async.store(configurations.is_executed_immediately);
        _is_flag_stopped_async.store(false);
        _is_cancelled_async.store(false);

        _start_thread(result);

        result.set_to_good_status_with_value(true);
    }

    void TimeoutClock::destruct(
        Result<bool>& result
    )
    {
        cancel(result);
        result.set_to_good_status_with_value(true);
    }

    void TimeoutClock::_start_thread(Result<bool>& result)
    {
        std::unique_lock<std::mutex> lock(_thread_mutex);

        if (_thread.joinable())
        {
            _thread.request_stop();
            _thread.join();
        }

        auto local_callback = configurations.callback;
        auto local_delay = configurations.delay_in_milliseconds;
        bool execute_immediately = configurations.is_executed_immediately || local_delay.count() == 0;

        _thread = std::jthread([local_callback, local_delay, execute_immediately](std::stop_token stop_token)
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

        result.set_to_good_status_with_value(true);
    }

    void TimeoutClock::cancel(
        Result<bool>& result
    )
    {        
        std::lock_guard<std::mutex> lock(_thread_mutex);

        _is_flag_stopped_async.store(true);

        if (_thread.joinable())
        {
            _thread.request_stop();
            _thread.join();
        }

        _is_cancelled_async.store(true);
        result.set_to_good_status_with_value(true);
    }

    void TimeoutClock::restart(
        Result<bool>& result
    )
    {
        cancel(result);
     
        _is_flag_stopped_async.store(false);
        _is_cancelled_async.store(false);
        _is_executed_immediately_async.store(configurations.is_executed_immediately);

        _start_thread(result);
        result.set_to_good_status_with_value(true);
    }

    void TimeoutClock::is_cancelled(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(_is_cancelled_async.load());
    }
}
