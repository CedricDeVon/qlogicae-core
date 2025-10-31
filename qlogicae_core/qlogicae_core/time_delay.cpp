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
