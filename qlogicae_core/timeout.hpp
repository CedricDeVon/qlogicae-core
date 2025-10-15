#pragma once

#include "result.hpp"

namespace QLogicaeCore
{
    class Timeout
    {
    public:
        ~Timeout();
        
        Timeout() = default;
        
        Timeout(
            std::function<void()>,
            std::chrono::milliseconds,
            bool = false
        );
        
        Timeout(
            const Timeout&
        ) = delete;
        
        Timeout(
            Timeout&&) noexcept = delete;
        
        Timeout& operator = (
            Timeout&&
        ) = delete;
        
        Timeout& operator = (
            const Timeout&
        ) = delete;

        void cancel();
        
        void restart();
        
        bool is_cancelled() const;

        void setup(
            Result<void>& result,
            std::function<void()>,
            std::chrono::milliseconds,
            bool = false
        );

        void cancel(
            Result<void>& result
        );

        void restart(
            Result<void>& result
        );

        void is_cancelled(
            Result<bool>& result
        ) const;

    protected:
        std::jthread _thread;
        
        std::function<void()> _function;
        
        std::chrono::milliseconds _delay;
        
        std::atomic<bool> _stop_flag{ false };
        
        std::atomic<bool> _is_cancelled{ false };

        std::atomic<bool> _execute_immediately{ false };
        
        void _start_thread();
    };
}

