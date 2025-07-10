#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class Interval {
    public:
        ~Interval();
        Interval() = default;
        Interval(const Interval&) = delete;
        Interval(Interval&&) noexcept = delete;
        Interval& operator=(Interval&&) = delete;
        Interval& operator=(const Interval&) = delete;
        Interval(const std::function<bool(size_t)>& callback,
            std::chrono::milliseconds interval,
            std::optional<size_t> max_count = std::nullopt,
            bool execute_now = false);

        void start();
        void stop();
        void pause();
        void resume();
        void cancel();
        void restart();

        bool is_paused() const;
        bool is_running() const;
        bool is_cancelled() const;
        size_t get_execution_count() const;
        void set_interval(std::chrono::milliseconds);
        void set_callback(std::function<bool(size_t)>);
        std::chrono::milliseconds get_interval() const;

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

