#pragma once

#include "result.hpp"

namespace QLogicaeCore
{
    class Interval
    {
    public:
        ~Interval();

        Interval() = default;

        Interval(const Interval& interval) = delete;

        Interval(Interval&& interval) noexcept = delete;

        Interval& operator=(Interval&& interval) = delete;

        Interval& operator=(const Interval& interval) = delete;

        Interval(
            const std::function<bool(size_t)>& callback,
            std::chrono::milliseconds interval,
            std::optional<size_t> max_count = std::nullopt,
            bool execute_now = false
        );

        void start();

        void stop();

        void pause();

        void resume();

        void cancel();

        void restart();

        bool is_paused();

        bool is_running();

        bool is_cancelled();

        size_t get_execution_count();

        std::chrono::milliseconds get_interval();

        void set_interval(std::chrono::milliseconds time);

        void set_callback(std::function<bool(size_t)> callback);

        void setup(
            Result<void>& result,
            const std::function<bool(size_t)>& callback,
            std::chrono::milliseconds interval,
            std::optional<size_t> max_count = std::nullopt,
            bool execute_now = false
        );

        void start(
            Result<void>& result
        );

        void stop(
            Result<void>& result
        );

        void pause(
            Result<void>& result
        );

        void resume(
            Result<void>& result
        );

        void cancel(
            Result<void>& result
        );

        void restart(
            Result<void>& result
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

        void get_interval(
            Result<std::chrono::milliseconds>& result
        );

        void set_interval(
            Result<void>& result, std::chrono::milliseconds time
        );

        void set_callback(
            Result<void>& result, std::function<bool(size_t)> callback
        );

    protected:
        std::thread _thread;
        
        mutable std::mutex _mutex;
        
        std::condition_variable _cv;
        
        std::atomic<size_t> _count{ 0 };
        
        std::optional<size_t> _max_count;
        
        std::atomic<bool> _paused{ false };
        
        std::atomic<bool> _running{ false };
        
        std::function<bool(size_t)> _callback;
        
        std::atomic<bool> _cancelled{ false };
        
        std::atomic<bool> _execute_now{ false };
        
        std::chrono::milliseconds _interval{ 1000 };

        void run();
    };
}

