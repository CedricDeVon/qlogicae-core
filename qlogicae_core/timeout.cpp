#include "pch.hpp"

#include "timeout.hpp"

namespace QLogicaeCore
{
    Timeout::Timeout(
        std::function<void()> function,
        std::chrono::milliseconds delay,
        bool execute_immediately
    )
        : _function(std::move(function)),
        _delay(delay),
        _execute_immediately(execute_immediately)
    {
        _start_thread();
    }

    Timeout::~Timeout()
    {
        cancel();
    }

    void Timeout::_start_thread()
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

                }
            }
        });
    }

    void Timeout::setup(
        Result<void>& result,
        std::function<void()> function,
        std::chrono::milliseconds delay,
        bool execute_immediately
    )
    {
        _function = std::move(function);
        _delay = delay;
        _execute_immediately =execute_immediately;

        _start_thread();

        result.set_to_success();
    }

    void Timeout::cancel()
    {
        try
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Timeout::cancel(): " + exception.what());
        }
    }

    void Timeout::restart()
    {
        try
        {
            cancel();

            _stop_flag.store(false);
            _is_cancelled.store(false);

            _start_thread();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Timeout::restart(): " + exception.what());
        }
    }

    bool Timeout::is_cancelled() const
    {
        try
        {
            return _is_cancelled.load();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Timeout::is_cancelled(): " + exception.what());
        }
    }

    void Timeout::cancel(
        Result<void>& result)
    {
        if (_thread.joinable())
        {
            _stop_flag.store(true);
            _thread.request_stop();
            _thread.join();
        }

        _stop_flag.store(true);
        _is_cancelled.store(true);

        result.set_to_success();
    }

    void Timeout::restart(
        Result<void>& result)
    {
        cancel();

        _stop_flag.store(false);
        _is_cancelled.store(false);

        _start_thread();

        result.set_to_success();
    }

    void Timeout::is_cancelled(
        Result<bool>& result) const
    {
        result.set_to_success(
            _is_cancelled.load()
        );
    }
}
