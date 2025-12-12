#pragma once

#include "result.hpp"
#include "timeout_clock_configurations.hpp"

namespace QLogicaeCppCore
{    
    class TimeoutClock
    {
    public:
        ~TimeoutClock();
        
        TimeoutClock();
        
        TimeoutClock(
            const TimeoutClockConfigurations& initial_configurations
        );
        
        TimeoutClock(
            const TimeoutClock& instance
        ) = delete;
        
        TimeoutClock(
            TimeoutClock&& instance
        ) noexcept = delete;
        
        TimeoutClock& operator = (
            TimeoutClock&& instance
        ) = delete;
        
        TimeoutClock& operator = (
            const TimeoutClock& instance
        ) = delete;

        void construct(
            Result<bool>& result
        );

        void construct(
            Result<bool>& result,
            const TimeoutClockConfigurations& initial_configurations
        );

        void destruct(
            Result<bool>& result
        );

        void cancel(
            Result<bool>& result
        );

        void restart(
            Result<bool>& result
        );

        void is_cancelled(
            Result<bool>& result
        );

        TimeoutClockConfigurations configurations;

    protected:
        std::jthread _thread;

        std::mutex _thread_mutex;

        std::atomic<bool> _is_flag_stopped_async { false };

        std::atomic<bool> _is_cancelled_async { false };

        std::atomic<bool> _is_executed_immediately_async { false };

        void _start_thread(
            Result<bool>& result
        );
    };
}
