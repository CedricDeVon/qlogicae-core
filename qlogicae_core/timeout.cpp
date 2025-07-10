#pragma once

#include "pch.h"

#include "timeout.hpp"

namespace QLogicaeCore
{
    Timeout::Timeout(std::function<void()> function,
        std::chrono::milliseconds delay,
        bool execute_immediately)
        : _function(std::move(function)),
        _delay(delay),
        _execute_immediately(execute_immediately)
    {
        start_thread();
    }

    Timeout::~Timeout()
    {
        cancel();
    }

    void Timeout::start_thread()
    {
        _thread = std::jthread([this](std::stop_token stop_token)
        {
            if (_execute_immediately.load())
            {
                if (_stop_flag.load() || stop_token.stop_requested()) return;
                try
                {
                    _function();
                }
                catch (...)
                {
                    std::cerr << "Timeout exception\n";
                }
            }
            else
            {
                std::this_thread::sleep_for(_delay);
                if (_stop_flag.load() || stop_token.stop_requested()) return;

                try
                {
                    _function();
                }
                catch (...)
                {
                    std::cerr << "Timeout exception\n";
                }
            }
        });
    }

    void Timeout::cancel()
    {
        if (_thread.joinable())
        {
            _stop_flag.store(true);
            _thread.request_stop();
            _thread.join();
        }

        _stop_flag.store(true);
        _is_cancelled.store(true);
    }

    void Timeout::restart()
    {
        cancel();

        _stop_flag.store(false);
        _is_cancelled.store(false);

        start_thread();
    }

    bool Timeout::is_cancelled() const
    {
        return _is_cancelled.load();
    }
}
