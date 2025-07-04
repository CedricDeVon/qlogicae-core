#pragma once

#include "pch.h"

#include "interval.hpp"

namespace QLogicaeCore
{
    Interval::Interval(const std::function<bool(size_t)>& callback,
        std::chrono::milliseconds interval,
        std::optional<size_t> max_count,
        bool execute_now) :
            _callback(callback),
            _interval(interval),
            _max_count(max_count),
            _execute_now(execute_now)
    {
    }

    Interval::~Interval()
    {
        cancel();
        if (_thread.joinable())
        {
            _thread.join();
        }
    }

    void Interval::start()
    {
        if (_thread.joinable())
        {
            return;
        }

        _cancelled.store(false);
        _paused.store(false);
        _running.store(true);
        _count.store(0);

        _thread = std::thread(&Interval::run, this);
    }

    void Interval::run()
    {
        if (_execute_now && !_cancelled.load())
        {
            if (!_callback(++_count))
            {
                stop();
                return;
            }
        }

        while (!_cancelled.load())
        {
            std::unique_lock lock(_mutex);

            if (_paused.load())
            {
                _cv.wait(lock, [this]() {
                    return !_paused.load() || _cancelled.load();
                    });
            }

            if (_cancelled.load())
            {
                return;
            }

            auto start = std::chrono::steady_clock::now();
            lock.unlock();

            if (!_callback(++_count))
            {
                stop();
                return;
            }

            if (_max_count && _count.load() >= *_max_count)
            {
                stop();
                return;
            }

            auto end = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            auto delay = _interval > elapsed ? _interval - elapsed : std::chrono::milliseconds(0);
            std::this_thread::sleep_for(delay);
        }
    }

    void Interval::pause()
    {
        _paused.store(true);
    }

    void Interval::resume()
    {
        if (_paused.load())
        {
            _paused.store(false);
            _cv.notify_all();
        }
    }

    void Interval::stop()
    {
        _running.store(false);
        _paused.store(false);
        _cv.notify_all();
    }

    void Interval::cancel()
    {
        _cancelled.store(true);
        _cv.notify_all();
    }

    void Interval::restart()
    {
        cancel();
        if (_thread.joinable())
        {
            _thread.join();
        }
        start();
    }

    bool Interval::is_running() const
    {
        return _running.load();
    }

    bool Interval::is_paused() const
    {
        return _paused.load();
    }

    bool Interval::is_cancelled() const
    {
        return _cancelled.load();
    }

    void Interval::set_interval(std::chrono::milliseconds interval)
    {
        std::lock_guard lock(_mutex);
        _interval = interval;
    }

    std::chrono::milliseconds Interval::get_interval() const
    {
        std::lock_guard lock(_mutex);

        return _interval;
    }

    void Interval::set_callback(std::function<bool(size_t)> cb)
    {
        std::lock_guard lock(_mutex);
        _callback = std::move(cb);
    }

    size_t Interval::get_execution_count() const
    {
        return _count.load();
    }
}
