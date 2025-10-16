#include "pch.hpp"

#include "interval.hpp"

namespace QLogicaeCore
{
    Interval::Interval(
        const std::function<bool(size_t)>& callback,
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
        try
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::start(): " +
                exception.what()
            );
        }
    }

    void Interval::run()
    {
        try
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
                auto elapsed =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        end - start
                    );
                auto delay =
                    _interval > elapsed ?
                    _interval - elapsed :
                    std::chrono::milliseconds(0);
                std::this_thread::sleep_for(delay);
            }
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::run(): " +
                exception.what()
            )
                ;
        }
    }

    void Interval::pause()
    {
        try
        {
            _paused.store(true);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::pause(): " +
                exception.what()
            );
        }
    }

    void Interval::resume()
    {
        try
        {
            if (_paused.load())
            {
                _paused.store(false);
                _cv.notify_all();
            }
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::resume(): " +
                exception.what()
            );
        }
    }

    void Interval::stop()
    {
        try
        {
            _running.store(false);
            _paused.store(false);
            _cv.notify_all();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::stop(): " +
                exception.what()
            );
        }
    }

    void Interval::cancel()
    {
        try
        {
            _cancelled.store(true);
            _cv.notify_all();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::cancel(): " +
                exception.what()
            );
        }
    }

    void Interval::restart()
    {
        try
        {
            cancel();
            if (_thread.joinable())
            {
                _thread.join();
            }
            start();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::restart(): " +
                exception.what()
            );
        }
    }

    bool Interval::is_running() const
    {
        try
        {
            return _running.load();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::is_running(): " +
                exception.what()
            );
        }
    }

    bool Interval::is_paused() const
    {
        try
        {
            return _paused.load();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::is_paused(): " +
                exception.what()
            );
        }
    }

    bool Interval::is_cancelled() const
    {
        try
        {
            return _cancelled.load();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::is_cancelled(): " +
                exception.what()
            );
        }
    }

    void Interval::set_interval(std::chrono::milliseconds interval)
    {
        try
        {
            std::lock_guard lock(_mutex);

            _interval = interval;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::set_interval(): " +
                exception.what()
            );
        }
    }

    std::chrono::milliseconds Interval::get_interval() const
    {
        try
        {
            std::lock_guard lock(_mutex);

            return _interval;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::get_interval(): " +
                exception.what()
            );
        }
    }

    void Interval::set_callback(std::function<bool(size_t)> cb)
    {
        try
        {
            std::lock_guard lock(_mutex);

            _callback = std::move(cb);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::set_callback(): " +
                exception.what()
            );
        }
    }

    size_t Interval::get_execution_count() const
    {
        try
        {
            return _count.load();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at Interval::get_execution_count(): " +
                exception.what())
                ;
        }
    }

    void Interval::setup(
        Result<void>& result,
        const std::function<bool(size_t)>& callback,
        std::chrono::milliseconds interval,
        std::optional<size_t> max_count,
        bool execute_now
    )
    {
        _callback = callback;
        _interval = interval;
        _max_count = max_count;
        _execute_now = execute_now;

        result.set_to_good_status_without_value();
    }

    void Interval::start(
        Result<void>& result
    )
    {
        if (_thread.joinable())
        {            
            return result.set_to_bad_status_without_value();
        }

        _cancelled.store(false);
        _paused.store(false);
        _running.store(true);
        _count.store(0);

        _thread = std::thread(&Interval::run, this);

        result.set_to_good_status_without_value();
    }

    void Interval::stop(
        Result<void>& result
    )
    {
        _running.store(false);
        _paused.store(false);
        _cv.notify_all();

        result.set_to_good_status_without_value();
    }

    void Interval::pause(
        Result<void>& result
    )
    {
        _paused.store(true);

        result.set_to_good_status_without_value();
    }

    void Interval::resume(
        Result<void>& result
    )
    {
        if (_paused.load())
        {
            _paused.store(false);
            _cv.notify_all();
        }

        result.set_to_good_status_without_value();
    }

    void Interval::cancel(
        Result<void>& result
    )
    {
        _cancelled.store(true);
        _cv.notify_all();

        result.set_to_good_status_without_value();
    }

    void Interval::restart(
        Result<void>& result
    )
    {
        cancel();
        if (_thread.joinable())
        {
            _thread.join();
        }
        start();

        result.set_to_good_status_without_value();
    }

    void Interval::is_paused(
        Result<bool>& result
    ) const
    {
        result.set_to_good_status_with_value(
            _paused.load()
        );
    }

    void Interval::is_running(
        Result<bool>& result
    ) const
    {
        result.set_to_good_status_with_value(
            _running.load()
        );
    }

    void Interval::is_cancelled(
        Result<bool>& result
    ) const
    {
        result.set_to_good_status_with_value(
            _cancelled.load()
        );
    }

    void Interval::get_execution_count(
        Result<size_t>& result
    ) const
    {
        result.set_to_good_status_with_value(
            _count.load()
        );
    }

    void Interval::get_interval(
        Result<std::chrono::milliseconds>& result
    ) const
    {
        std::lock_guard lock(_mutex);

        result.set_to_good_status_with_value(_interval);        
    }

    void Interval::set_interval(
        Result<void>& result,
        std::chrono::milliseconds interval
    )
    {
        std::lock_guard lock(_mutex);

        _interval = interval;

        result.set_to_good_status_without_value();
    }

    void Interval::set_callback(
        Result<void>& result,
        std::function<bool(size_t)> callback
    )
    {
        std::lock_guard lock(_mutex);

        _callback = std::move(callback);

        result.set_to_good_status_without_value();
    }
}
