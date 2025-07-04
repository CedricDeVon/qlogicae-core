#pragma once

#include "pch.h"

#include "timeout.hpp"

namespace QLogicaeCore
{
    Timeout::Timeout(std::function<void()> func,
        std::chrono::milliseconds delay,
        bool execute_immediately)
        : _func(std::move(func)), _delay(delay), _execute_immediately(execute_immediately) {
        _thread = std::jthread([this](std::stop_token token) {
            run(token);
            });
    }

    Timeout::~Timeout()
    {
        cancel();
    }

    void Timeout::run(std::stop_token token)
    {
        if (_execute_immediately.load())
        {
            try
            {
                _func();
            }
            catch (...)
            {
                std::cerr << "Timeout callback threw an exception.\n";
            }
        }
        else
        {
            if (std::this_thread::sleep_for(_delay); !token.stop_requested())
            {
                try
                {
                    _func();
                }
                catch (...)
                {
                    std::cerr << "Timeout callback threw an exception.\n";
                }
            }
        }
    }

    void Timeout::cancel()
    {
        _is_cancelled.store(true);
        if (_thread.joinable())
        {
            _thread.request_stop();
        }
    }

    void Timeout::restart()
    {
        cancel();
        _thread = std::jthread([this](std::stop_token token)
            {
            run(token);
            });
    }

    bool Timeout::is_cancelled() const
    {
        return _is_cancelled.load();
    }
}
