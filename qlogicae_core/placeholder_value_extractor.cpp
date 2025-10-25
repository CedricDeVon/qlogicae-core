#include "pch.hpp"

#include "placeholder_value_extractor.hpp"

namespace QLogicaeCore
{
    PlaceholderValueExtractor::PlaceholderValueExtractor()
    {

    }

    PlaceholderValueExtractor::~PlaceholderValueExtractor()
    {

    }

    PlaceholderValueExtractor::PlaceholderValueExtractor(
        const std::string& value
    ) :
            _value(value)
    {

    }

    bool PlaceholderValueExtractor::setup()
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

        }
    }

    bool PlaceholderValueExtractor::setup(
        const std::string& value
    )
    {
        try
        {
            Result<void> result;

            setup(
                result,
                value
            );

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void PlaceholderValueExtractor::setup(
        Result<void>& result
    )
    {
        _value = "";

        result.set_to_good_status_without_value();
    }

    void PlaceholderValueExtractor::setup(
        Result<void>& result,
        const std::string& value
    )
    {
        _value = value;

        result.set_to_good_status_without_value();
    }

    std::future<bool> PlaceholderValueExtractor::setup_async()
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

    void PlaceholderValueExtractor::setup_async(
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

    void PlaceholderValueExtractor::setup_async(
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

    void PlaceholderValueExtractor::setup_async(
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

    std::future<bool> PlaceholderValueExtractor::setup_async(
        const std::string& value
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, value,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup(
                        value
                    )
                );
            }
        );

        return future;
    }

    void PlaceholderValueExtractor::setup_async(
        const std::function<void(const bool& result)>& callback,
        const std::string& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, value, callback]() mutable
            {
                callback(
                    setup(
                        value
                    )
                );
            }
        );
    }

    void PlaceholderValueExtractor::setup_async(
        Result<std::future<void>>& result,
        const std::string& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, value,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(
                    result,
                    value
                );

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void PlaceholderValueExtractor::setup_async(
        const std::function<void(Result<void>& result)>& callback,
        const std::string& value
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, value, callback]() mutable
            {
                Result<void> result;

                setup(
                    result,
                    value
                );

                callback(
                    result
                );
            }
        );
    }

    std::optional<std::string> PlaceholderValueExtractor::get_value()
    {
        return _value;
    }

    void PlaceholderValueExtractor::get_value(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _value
        );
    }

    PlaceholderValueExtractor& PlaceholderValueExtractor::get_instance()
    {
        static PlaceholderValueExtractor instance;

        return instance;
    }

    void PlaceholderValueExtractor::get_instance(
        Result<PlaceholderValueExtractor*>& result
    )
    {
        static PlaceholderValueExtractor instance;

        result.set_to_good_status_with_value(&instance);
    }
}
