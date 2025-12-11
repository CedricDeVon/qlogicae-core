#pragma once

#include "result.hpp"
#include "timeout_configurations.hpp"

namespace QLogicaeCppCore
{    
    class Timeout
    {
    public:
        ~Timeout();
        
        Timeout();
        
        Timeout(
            const TimeoutConfigurations& initial_configurations
        );
        
        Timeout(
            const Timeout& instance
        ) = delete;
        
        Timeout(
            Timeout&& instance
        ) noexcept = delete;
        
        Timeout& operator = (
            Timeout&& instance
        ) = delete;
        
        Timeout& operator = (
            const Timeout& instance
        ) = delete;

        void construct(
            Result<bool>& result
        );

        void construct(
            Result<bool>& result,
            const TimeoutConfigurations& initial_configurations
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

        TimeoutConfigurations configurations;

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
