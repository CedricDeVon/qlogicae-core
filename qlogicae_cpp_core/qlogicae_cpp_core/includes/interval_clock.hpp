#pragma once

#include "result.hpp"
#include "interval_clock_configurations.hpp"

namespace QLogicaeCppCore
{
    class IntervalClock
    {
    public:
        IntervalClock();

        IntervalClock(
            const IntervalClockConfigurations& initial_configurations
        );

        ~IntervalClock();

        IntervalClock(
            const IntervalClock& instance
        ) = delete;

        IntervalClock(
            IntervalClock&& instance
        ) noexcept = delete;

        IntervalClock& operator = (
            IntervalClock&& instance
        ) = delete;

        IntervalClock& operator = (
            const IntervalClock& instance
        ) = delete;

        void construct(
            Result<bool>& result
        );

        void construct(
            Result<bool>& result,
            const IntervalClockConfigurations& initial_configurations
        );

        void destruct(
            Result<bool>& result
        );

        void start(
            Result<bool>& result
        );

        void stop(
            Result<bool>& result
        );

        void pause(
            Result<bool>& result
        );

        void resume(
            Result<bool>& result
        );

        void cancel(
            Result<bool>& result
        );

        void restart(
            Result<bool>& result
        );

        void is_paused(
            Result<bool>& result
        );

        void is_running(
            Result<bool>& result
        );

        void is_cancelled(
            Result<bool>& result
        );

        void get_execution_count(
            Result<size_t>& result
        );

        IntervalClockConfigurations configurations;

    protected:
        std::thread _thread;
        
        mutable std::mutex _mutex;
        
        std::condition_variable _condition_variable;
        
        std::atomic<size_t> _execution_count { 0 };
        
        std::atomic<bool> _is_paused { false };
        
        std::atomic<bool> _is_running { false };
        
        std::atomic<bool> _is_cancelled { false };
        
        void _run_interval(
            Result<bool>& result
        );
    };
}

