#include "pch.hpp"

#include "../includes/interval.hpp"

namespace QLogicaeCppCore
{
    Interval::Interval()
    {
        Result<bool> result;

        construct(result);
    }

    Interval::Interval(
        const IntervalConfigurations& initial_configurations
    )
    {
        Result<bool> result;

        construct(
            result,
            initial_configurations
        );
    }

    Interval::~Interval()
    {
        Result<bool> result;

        destruct(result);
    }

    void Interval::construct(
        Result<bool>& result
    )
    {
        IntervalConfigurations initial_configurations;

        construct(
            result,
            initial_configurations
        );
    }

    void Interval::construct(
        Result<bool>& result,
        const IntervalConfigurations& initial_configurations
    )
    {
        configurations = initial_configurations;

        _is_cancelled.store(false);
        _is_paused.store(false);
        _is_running.store(false);
        _execution_count.store(0);

        result.set_to_good_status_with_value(
            true
        );
    }

    void Interval::destruct(
        Result<bool>& result
    )
    {
        cancel(result);

        if (_thread.joinable())
        {
            _thread.join();
        }

        result.set_to_good_status_with_value(
            true
        );
    }

    void Interval::start(
        Result<bool>& result
    )
    {
        if (_thread.joinable())
        {
            if (!_is_running.load())
            {
                _thread.join();
            }
            else
            {
                result.set_to_good_status_with_value(
                    false
                );

                return;
            }
        }

        _is_cancelled.store(false);
        _is_paused.store(false);
        _is_running.store(true);
        _execution_count.store(0);

        _thread = std::thread(
            &Interval::_run_interval,
            this,
            std::ref(result)
        );

        result.set_to_good_status_with_value(
            true
        );
    }

    void Interval::stop(
        Result<bool>& result
    )
    {
        _is_running.store(false);
        _is_paused.store(false);
        _condition_variable.notify_all();

        if (_thread.joinable() && !_is_running.load())
        {
            _thread.join();
        }

        result.set_to_good_status_with_value(
            true
        );
    }

    void Interval::pause(
        Result<bool>& result
    )
    {
        _is_paused.store(true);

        result.set_to_good_status_with_value(
            true
        );
    }

    void Interval::resume(
        Result<bool>& result
    )
    {
        if (_is_paused.load())
        {
            _is_paused.store(false);
            _condition_variable.notify_all();
        }

        result.set_to_good_status_with_value(
            true
        );
    }

    void Interval::cancel(
        Result<bool>& result
    )
    {
        _is_cancelled.store(true);
        _is_paused.store(false);
        _is_running.store(false);
        _condition_variable.notify_all();

        if (_thread.joinable())
        {
            _thread.join();
        }

        result.set_to_good_status_with_value(
            true
        );
    }

    void Interval::restart(
        Result<bool>& result
    )
    {
        cancel(result);

        _execution_count.store(0);
        _is_cancelled.store(false);
        _is_paused.store(false);
        _is_running.store(false);

        start(result);

        result.set_to_good_status_with_value(
            true
        );
    }

    void Interval::is_paused(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            _is_paused.load()
        );
    }

    void Interval::is_running(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            _is_running.load()
        );
    }

    void Interval::is_cancelled(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            _is_cancelled.load()
        );
    }

    void Interval::get_execution_count(
        Result<size_t>& result
    )
    {
        result.set_to_good_status_with_value(
            _execution_count.load()
        );
    }

    void Interval::_run_interval(
        Result<bool>& result
    )
    {
        _is_running.store(true);
        _is_cancelled.store(false);

        if (configurations.is_executed_immediately &&
            !_is_cancelled.load())
        {
            size_t current = ++_execution_count;

            bool should_continue = false;
            try
            {
                should_continue = configurations.callback(current);
            }
            catch (...)
            {
                should_continue = false;
            }

            if (!should_continue)
            {
                _is_running.store(false);
                _condition_variable.notify_all();

                result.set_to_good_status_with_value(
                    true
                );

                return;
            }

            if (configurations.maximum_interval_count &&
                _execution_count.load() >= configurations.maximum_interval_count)
            {
                _is_running.store(false);
                _condition_variable.notify_all();

                result.set_to_good_status_with_value(
                    true
                );

                return;
            }
        }

        while (!_is_cancelled.load() && _is_running.load())
        {
            std::unique_lock<std::mutex> lock(_mutex);

            if (_is_paused.load())
            {
                _condition_variable.wait(lock, [this]() {
                    return !_is_paused.load() || _is_cancelled.load();
                    });
            }

            if (_is_cancelled.load() || !_is_running.load())
            {
                break;
            }

            auto start = std::chrono::steady_clock::now();
            lock.unlock();

            size_t current = ++_execution_count;

            bool should_continue = false;
            try
            {
                should_continue = configurations.callback(current);
            }
            catch (...)
            {
                should_continue = false;
            }

            if (!should_continue)
            {
                _is_running.store(false);
                _condition_variable.notify_all();

                result.set_to_good_status_with_value(
                    true
                );

                return;
            }

            if (configurations.maximum_interval_count &&
                _execution_count.load() >= configurations.maximum_interval_count)
            {
                _is_running.store(false);
                _condition_variable.notify_all();

                result.set_to_good_status_with_value(
                    true
                );

                return;
            }

            auto end = std::chrono::steady_clock::now();
            auto elapsed =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    end - start
                );
            auto delay =
                configurations.delay_in_milliseconds > elapsed ?
                configurations.delay_in_milliseconds - elapsed :
                std::chrono::milliseconds(0);

            for (std::chrono::milliseconds waited(0);
                waited < delay && !_is_cancelled.load() && _is_running.load();
                )
            {
                auto to_wait = std::min<std::chrono::milliseconds>(
                    std::chrono::milliseconds(50),
                    delay - waited
                );

                std::this_thread::sleep_for(to_wait);
                waited += to_wait;
            }
        }

        _is_running.store(false);
        _condition_variable.notify_all();

        result.set_to_good_status_with_value(
            true
        );
    }
}
