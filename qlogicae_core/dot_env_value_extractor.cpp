#include "pch.hpp"

#include "dot_env_value_extractor.hpp"

namespace QLogicaeCore
{
    DotEnvValueExtractor::DotEnvValueExtractor()
    {

    }

    DotEnvValueExtractor::~DotEnvValueExtractor()
    {

    }

    DotEnvValueExtractor::DotEnvValueExtractor(
        const std::string& key
    ) :
            _key(
                ENCODER.from_utf8_to_utf16(key)
            )
    {

    }

    DotEnvValueExtractor::DotEnvValueExtractor(
        const std::wstring& key) :
            _key(key)
    {

    }

    bool DotEnvValueExtractor::setup()
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
                "QLogicaeCore::DotEnvValueExtractor::setup()",
                exception.what()
            );

            return false;
        }
    }

    void DotEnvValueExtractor::setup(
        Result<void>& result
    )
    {
        _key = L"";

        result.set_to_good_status_without_value();
    }

    bool DotEnvValueExtractor::setup(
        const std::string key
    )
    {
        try
        {
            Result<void> result;

            setup(
                result,
                key
            );

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::DotEnvValueExtractor::setup()",
                exception.what()
            );

            return false;
        }
    }

    bool DotEnvValueExtractor::setup(
        const std::wstring key
    )
    {
        try
        {
            Result<void> result;

            setup(
                result,
                key
            );

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::DotEnvValueExtractor::setup()",
                exception.what()
            );

            return false;
        }
    }

    void DotEnvValueExtractor::setup(
        Result<void>& result,
        const std::string key
    )
    {
        Result<std::wstring> r;

        ENCODER.from_utf8_to_utf16(r, key);

        _key = r.get_value();

        result.set_to_good_status_without_value();
    }

    void DotEnvValueExtractor::setup(
        Result<void>& result,
        const std::wstring key
    )
    {
        _key = key;

        result.set_to_good_status_without_value();
    }

    std::future<bool> DotEnvValueExtractor::setup_async()
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

    void DotEnvValueExtractor::setup_async(
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

    void DotEnvValueExtractor::setup_async(
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

                setup(result);

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void DotEnvValueExtractor::setup_async(
        const std::function<void(Result<void>& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;

                setup(result);

                callback(
                    result
                );
            }
        );
    }

    std::future<bool> DotEnvValueExtractor::setup_async(
        const std::string key
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, key,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup(
                        key
                    )
                );
            }
        );

        return future;
    }

    void DotEnvValueExtractor::setup_async(
        const std::function<void(const bool& result)>& callback,
        const std::string key
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

    void DotEnvValueExtractor::setup_async(
        Result<std::future<void>>& result,
        const std::string key
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

                setup(result);

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void DotEnvValueExtractor::setup_async(
        const std::function<void(Result<void>& result)>& callback,
        const std::string key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;

                setup(result);

                callback(
                    result
                );
            }
        );
    }

    std::future<bool> DotEnvValueExtractor::setup_async(
        const std::wstring key
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, key,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup(
                        key
                    )
                );
            }
        );

        return future;
    }

    void DotEnvValueExtractor::setup_async(
        const std::function<void(const bool& result)>& callback,
        const std::wstring key
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

    void DotEnvValueExtractor::setup_async(
        Result<std::future<void>>& result,
        const std::wstring key
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

                setup(result);

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void DotEnvValueExtractor::setup_async(
        const std::function<void(Result<void>& result)>& callback,
        const std::wstring key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;

                setup(result);

                callback(
                    result
                );
            }
        );
    }

    std::optional<std::wstring> DotEnvValueExtractor::get_key()
    {
        return _key;
    }

    std::optional<std::string> DotEnvValueExtractor::get_value()
    {
        try
        {
            return ENCODER
                .from_utf16_to_utf8(
                    DOT_ENV.get(_key.c_str()
                ).value()
            ); 
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::DotEnvValueExtractor::get_value()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::DotEnvValueExtractor::get_value() - " +
                exception.what()
            );
        }
    }

    void DotEnvValueExtractor::get_key(
        Result<std::optional<std::wstring>>& result
    )
    {
        result.set_to_good_status_with_value(_key);
    }

    void DotEnvValueExtractor::get_value(
        Result<std::string>& result
    )
    {
        Result<std::wstring> output;

        DOT_ENV.get(
            output, _key.c_str()
        );
        ENCODER.from_utf16_to_utf8(
            result, output.get_value()
        );        
    }

    DotEnvValueExtractor& DotEnvValueExtractor::get_instance()
    {
        static DotEnvValueExtractor instance;

        return instance;
    }

    void DotEnvValueExtractor::get_instance(
        QLogicaeCore::Result<DotEnvValueExtractor*>& result
    )
    {
        static DotEnvValueExtractor instance;

        result.set_to_good_status_with_value(&instance);
    }
}
