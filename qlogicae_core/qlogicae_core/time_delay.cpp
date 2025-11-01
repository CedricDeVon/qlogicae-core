#include "pch.hpp"

#include "time_delay.hpp"

namespace QLogicaeCore
{
    TimeDelay::TimeDelay()
    {
        _cycles_per_microsecond = 0.0;
    }

    TimeDelay::~TimeDelay()
    {
        
    }

    bool TimeDelay::setup()
    {
        try
        {
            Result<void> result;

            setup(
                result
            );

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::TimeDelay::setup()",
                exception.what()
            );

            return false;
        }
    }

    void TimeDelay::setup(
        Result<void>& result
    )
    {
        _cycles_per_microsecond = 0.0;

        result.set_to_good_status_without_value();
    }

    std::future<bool> TimeDelay::setup_async()
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup()
                );
            }
        );

        return future;
    }

    void TimeDelay::setup_async(
        Result<std::future<void>>& result
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(
                    result
                );

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void TimeDelay::setup_async(
        const std::function<void(const bool& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                callback(
                    setup()
                );
            }
        );
    }

    void TimeDelay::setup_async(
        const std::function<void(Result<void>& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;

                setup(
                    result
                );

                callback(
                    result
                );
            }
        );
    }

    void TimeDelay::calibrate(
        Result<void>& result
    )
    {
        static std::atomic<bool> calibrated = false;
        static std::atomic<double> cached_frequency = 0.0;

        if (calibrated.load())
        {
            _cycles_per_microsecond = cached_frequency;
            result.set_to_good_status_without_value();
            return;
        }

        LARGE_INTEGER frequency;
        LARGE_INTEGER start;
        LARGE_INTEGER end;

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        unsigned long long tsc_start = __rdtsc();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        unsigned long long tsc_end = __rdtsc();

        QueryPerformanceCounter(&end);

        const double elapsed_seconds =
            static_cast<double>(end.QuadPart - start.QuadPart) /
            static_cast<double>(frequency.QuadPart);

        const double cpu_frequency_hz =
            (tsc_end - tsc_start) / elapsed_seconds;

        _cycles_per_microsecond = cpu_frequency_hz / 1'000'000.0;
        cached_frequency = _cycles_per_microsecond;
        calibrated.store(true);

        result.set_to_good_status_without_value();
    }

    void TimeDelay::calibrate()
    {
        try
        {
            Result<void> result;
            calibrate(result);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::calibrate()",
                exception.what()
            );
        }
    }

    void TimeDelay::query_performance_counter(
        Result<void>& result,
        const double& microseconds
    )
    {
        LARGE_INTEGER frequency;
        LARGE_INTEGER start;
        LARGE_INTEGER current;

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        double elapsed = 0.0;

        do
        {
            QueryPerformanceCounter(&current);
            elapsed = (current.QuadPart - start.QuadPart) *
                1'000'000.0 / frequency.QuadPart;
        } while (elapsed < microseconds);

        result.set_to_good_status_without_value();
    }

    void TimeDelay::query_performance_counter(
        const double& microseconds
    )
    {
        try
        {
            Result<void> result;
            query_performance_counter(result, microseconds);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::query_performance_counter()",
                exception.what()
            );
        }
    }

    void TimeDelay::real_time_stamp_counter(
        Result<void>& result,
        const double& microseconds
    )
    {
        if (_cycles_per_microsecond == 0.0)
        {
            calibrate(result);
        }

        unsigned __int64 start = __rdtsc();
        unsigned __int64 target =
            static_cast<unsigned __int64>(
                microseconds * _cycles_per_microsecond);

        while ((__rdtsc() - start) < target)
        {
            _mm_pause();
        }

        result.set_to_good_status_without_value();
    }

    void TimeDelay::real_time_stamp_counter(
        const double& microseconds
    )
    {
        try
        {
            Result<void> result;
            real_time_stamp_counter(result, microseconds);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::real_time_stamp_counter()",
                exception.what()
            );
        }
    }

    void TimeDelay::in_nanoseconds(
        Result<void>& result,
        const double& value
    )
    {
        in_microseconds(result, value / 1'000.0);
    }

    void TimeDelay::in_nanoseconds(
        const double& value
    )
    {
        try
        {
            Result<void> result;
            in_nanoseconds(result, value);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::in_nanoseconds()",
                exception.what()
            );
        }
    }

    void TimeDelay::in_microseconds(
        Result<void>& result,
        const double& value
    )
    {
        if (value <= 0.0)
        {
            result.set_to_good_status_without_value();
            return;
        }

        LARGE_INTEGER frequency;
        LARGE_INTEGER start;
        LARGE_INTEGER current;

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        double elapsed = 0.0;
        while (elapsed < value)
        {
            QueryPerformanceCounter(&current);
            elapsed = static_cast<double>(
                current.QuadPart - start.QuadPart
                ) * 1'000'000.0 / static_cast<double>(frequency.QuadPart);
        }

        result.set_to_good_status_without_value();
    }

    void TimeDelay::in_microseconds(
        const double& value
    )
    {
        try
        {
            Result<void> result;
            in_microseconds(result, value);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::in_microseconds()",
                exception.what()
            );
        }
    }

    void TimeDelay::in_milliseconds(
        Result<void>& result,
        const double& value
    )
    {
        in_microseconds(result, value * 1'000.0);
    }

    void TimeDelay::in_milliseconds(
        const double& value
    )
    {
        try
        {
            Result<void> result;
            in_milliseconds(result, value);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::in_milliseconds()",
                exception.what()
            );
        }
    }

    void TimeDelay::in_seconds(
        Result<void>& result,
        const double& value
    )
    {
        in_microseconds(result, value * 1'000'000.0);
    }

    void TimeDelay::in_seconds(
        const double& value
    )
    {
        try
        {
            Result<void> result;
            in_seconds(result, value);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::in_seconds()",
                exception.what()
            );
        }
    }

    void TimeDelay::in_minutes(
        Result<void>& result,
        const double& value
    )
    {
        in_seconds(result, value * 60.0);
    }

    void TimeDelay::in_minutes(
        const double& value
    )
    {
        try
        {
            Result<void> result;
            in_minutes(result, value);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::in_minutes()",
                exception.what()
            );
        }
    }

    void TimeDelay::in_hours(
        Result<void>& result,
        const double& value
    )
    {
        in_minutes(result, value * 60.0);
    }

    void TimeDelay::in_hours(
        const double& value
    )
    {
        try
        {
            Result<void> result;
            in_hours(result, value);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::in_hours()",
                exception.what()
            );
        }
    }

    void TimeDelay::in_days(
        Result<void>& result,
        const double& value
    )
    {
        in_hours(result, value * 24.0);
    }

    void TimeDelay::in_days(
        const double& value
    )
    {
        try
        {
            Result<void> result;
            in_days(result, value);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::in_days()",
                exception.what()
            );
        }
    }

    void TimeDelay::in_months(
        Result<void>& result,
        const double& value
    )
    {
        in_days(result, value * 30.44);
    }

    void TimeDelay::in_months(
        const double& value
    )
    {
        try
        {
            Result<void> result;
            in_months(result, value);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::in_months()",
                exception.what()
            );
        }
    }

    void TimeDelay::in_years(
        Result<void>& result,
        const double& value
    )
    {
        in_days(result, value * 365.25);
    }

    void TimeDelay::in_years(
        const double& value
    )
    {
        try
        {
            Result<void> result;
            in_years(result, value);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TimeDelay::in_years()",
                exception.what()
            );
        }
    }

    std::future<void> TimeDelay::in_microseconds_async(
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;

                in_microseconds(result, value);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::in_microseconds_async(
        Result<std::future<void>>& result,
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;

                in_microseconds(result, value);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::in_microseconds_async(
        const std::function<void(const bool&)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_microseconds(result, value);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::in_microseconds_async(
        const std::function<void(Result<void>&)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_microseconds(result, value);
                
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::in_years_async(
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_years(result, value);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::in_years_async(
        Result<std::future<void>>& result,
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_years(result, value);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::in_years_async(
        const std::function<void(const bool& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_years(result, value);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::in_years_async(
        const std::function<void(Result<void>& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_years(result, value);
                
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::in_months_async(
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_months(result, value);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::in_months_async(
        Result<std::future<void>>& result,
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_months(result, value);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::in_months_async(
        const std::function<void(const bool& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_months(result, value);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::in_months_async(
        const std::function<void(Result<void>& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_months(result, value);
                
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::in_days_async(
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_days(result, value);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::in_days_async(
        Result<std::future<void>>& result,
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_days(result, value);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::in_days_async(
        const std::function<void(const bool& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_days(result, value);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::in_days_async(
        const std::function<void(Result<void>& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_days(result, value);
                
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::in_hours_async(
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_hours(result, value);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::in_hours_async(
        Result<std::future<void>>& result,
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_hours(result, value);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::in_hours_async(
        const std::function<void(const bool& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_hours(result, value);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::in_hours_async(
        const std::function<void(Result<void>& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_hours(result, value);
                
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::in_minutes_async(
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_minutes(result, value);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::in_minutes_async(
        Result<std::future<void>>& result,
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_minutes(result, value);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::in_minutes_async(
        const std::function<void(const bool& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_minutes(result, value);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::in_minutes_async(
        const std::function<void(Result<void>& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_minutes(result, value);
             
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::in_seconds_async(
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_seconds(result, value);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::in_seconds_async(
        Result<std::future<void>>& result,
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_seconds(result, value);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::in_seconds_async(
        const std::function<void(const bool& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_seconds(result, value);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::in_seconds_async(
        const std::function<void(Result<void>& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_seconds(result, value);
                
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::in_milliseconds_async(
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_milliseconds(result, value);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::in_milliseconds_async(
        Result<std::future<void>>& result,
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_milliseconds(result, value);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::in_milliseconds_async(
        const std::function<void(const bool& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_milliseconds(result, value);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::in_milliseconds_async(
        const std::function<void(Result<void>& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_milliseconds(result, value);
                
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::in_nanoseconds_async(
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_nanoseconds(result, value);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::in_nanoseconds_async(
        Result<std::future<void>>& result,
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                in_nanoseconds(result, value);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::in_nanoseconds_async(
        const std::function<void(const bool& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_nanoseconds(result, value);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::in_nanoseconds_async(
        const std::function<void(Result<void>& result)>& callback,
        const double& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, value]() mutable
            {
                Result<void> result;
                
                in_nanoseconds(result, value);
                
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::calibrate_async(
        const double& /*value*/
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise)]() mutable
            {
                Result<void> result;
                
                calibrate(result);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::calibrate_async(
        Result<std::future<void>>& result,
        const double& /*microseconds*/
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise)]() mutable
            {
                Result<void> result;
                
                calibrate(result);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::calibrate_async(
        const std::function<void(const bool& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;
               
                calibrate(result);
               
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::calibrate_async(
        const std::function<void(Result<void>& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;
                
                calibrate(result);
                
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::real_time_stamp_counter_async(
        const double& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), value]() mutable
            {
                Result<void> result;
                
                real_time_stamp_counter(result, value);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::real_time_stamp_counter_async(
        Result<std::future<void>>& result,
        const double& microseconds
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), microseconds]() mutable
            {
                Result<void> result;

                real_time_stamp_counter(result, microseconds);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::real_time_stamp_counter_async(
        const std::function<void(const bool& result)>& callback,
        const double& microseconds
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, microseconds]() mutable
            {
                Result<void> result;
                
                real_time_stamp_counter(result, microseconds);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::real_time_stamp_counter_async(
        const std::function<void(Result<void>& result)>& callback,
        const double& microseconds
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, microseconds]() mutable
            {
                Result<void> result;
                
                real_time_stamp_counter(result, microseconds);
                
                callback(result);
            }
        );
    }

    std::future<void> TimeDelay::query_performance_counter_async(
        const double& microseconds
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), microseconds]() mutable
            {
                Result<void> result;
                
                query_performance_counter(result, microseconds);
                
                promise.set_value();
            }
        );

        return future;
    }

    void TimeDelay::query_performance_counter_async(
        Result<std::future<void>>& result,
        const double& microseconds
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise), microseconds]() mutable
            {
                Result<void> result;

                query_performance_counter(result, microseconds);
                
                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(std::move(future));
    }

    void TimeDelay::query_performance_counter_async(
        const std::function<void(const bool& result)>& callback,
        const double& microseconds
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, microseconds]() mutable
            {
                Result<void> result;
              
                query_performance_counter(result, microseconds);
                
                callback(result.is_status_safe());
            }
        );
    }

    void TimeDelay::query_performance_counter_async(
        const std::function<void(Result<void>& result)>& callback,
        const double& microseconds
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, microseconds]() mutable
            {
                Result<void> result;
                
                query_performance_counter(result, microseconds);
                
                callback(result);
            }
        );
    }

    TimeDelay& TimeDelay::get_instance()
    {
        static TimeDelay singleton;

        return singleton;
    }

    void TimeDelay::get_instance(
        Result<TimeDelay*>& result
    )
    {
        static TimeDelay instance;

        result.set_to_good_status_with_value(&instance);
    }
}
