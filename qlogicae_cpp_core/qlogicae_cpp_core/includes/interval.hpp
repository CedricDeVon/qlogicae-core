#pragma once

#include "result.hpp"
#include "interval_configurations.hpp"

namespace QLogicaeCppCore
{
    class Interval
    {
    public:
        Interval();

        Interval(
            const IntervalConfigurations& initial_configurations
        );

        ~Interval();

        Interval(
            const Interval& instance
        ) = delete;

        Interval(
            Interval&& instance
        ) noexcept = delete;

        Interval& operator = (
            Interval&& instance
        ) = delete;

        Interval& operator = (
            const Interval& instance
        ) = delete;

        void construct(
            Result<bool>& result
        );

        void construct(
            Result<bool>& result,
            const IntervalConfigurations& initial_configurations
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

        IntervalConfigurations configurations;

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

