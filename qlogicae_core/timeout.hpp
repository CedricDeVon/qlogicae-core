#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class Timeout
    {
    public:
        ~Timeout();
        Timeout() = default;
        Timeout(std::function<void()>,
            std::chrono::milliseconds,
            bool = false);
        Timeout(const Timeout&) = delete;
        Timeout(Timeout&&) noexcept = delete;
        Timeout& operator = (Timeout&&) = delete;
        Timeout& operator = (const Timeout&) = delete;

        void cancel();
        void restart();
        bool is_cancelled() const;

    protected:
        std::jthread _thread;
        std::function<void()> _function;
        std::chrono::milliseconds _delay;
        std::atomic<bool> _stop_flag{ false };
        std::atomic<bool> _is_cancelled{ false };
        std::atomic<bool> _execute_immediately{ false };
        
        void start_thread();
    };
}

