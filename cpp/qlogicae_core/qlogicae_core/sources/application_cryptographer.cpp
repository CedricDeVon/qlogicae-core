#include "pch.hpp"

#include "../includes/application_cryptographer.hpp"

namespace QLogicaeCore
{
    ApplicationCryptographer::ApplicationCryptographer() :
        AbstractApplication()
    {
        
    }

    ApplicationCryptographer::~ApplicationCryptographer()
    {

    }

    bool ApplicationCryptographer::setup()
    {
        Result<void> void_result;

        setup(void_result);

        return void_result.is_status_safe();
    }

    void ApplicationCryptographer::setup(
        Result<void>& result
    )
    {
        try
        {
            if (_is_enabled)
            {
                LOGGER.handle_exception_async(
                    "QLogicaeCore::ApplicationCryptographer::setup()",
                    "Can only be called once"
                );

                return result.set_to_bad_status_without_value(
                    "QLogicaeCore::ApplicationCryptographer::setup() - Can only be called once"
                );
            }

            AES256_CIPHER_CRYPTOGRAPHER.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            AES256_SIGNATURE_CRYPTOGRAPHER.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            ARGON2ID_HASH_CRYPTOGRAPHER.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            BCRYPT_HASH_CRYPTOGRAPHER.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            SHA256_HASH_CRYPTOGRAPHER.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            XCHACHA20_POLY1305_CIPHER_CRYPTOGRAPHER.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            JSONWEBTOKEN_CRYPTOGRAPHER.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            set_is_enabled(true);

            result.set_to_good_status_without_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::ApplicationCryptographer::setup()",
                exception.what()
            );

            result.set_to_bad_status_without_value(
                std::string("QLogicaeCore::ApplicationCryptographer::setup() - ") +
                exception.what()
            );
        }
    }

    std::future<bool> ApplicationCryptographer::setup_async(
        const std::function<void(const bool& value)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                bool value = setup();

                promise.set_value(
                    value
                );

                if (callback)
                {
                    callback(
                        value
                    );
                }
            }
        );

        return future;
    }

    void ApplicationCryptographer::setup_async(
        Result<std::future<void>>& result,
        const std::function<void(Result<void>& result)>& callback
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(result);

                promise.set_value();

                callback(
                    result
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    bool ApplicationCryptographer::terminate()
    {
        try
        {
            Result<void> void_result;

            terminate(void_result);

            return void_result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::ApplicationCryptographer::terminate()",
                exception.what()
            );

            return false;
        }
    }

    void ApplicationCryptographer::terminate(
        Result<void>& result
    )
    {
        set_is_enabled(false);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationCryptographer::terminate_async(
        const std::function<void(const bool& value)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                bool value = terminate();

                promise.set_value(
                    value
                );

                if (callback)
                {
                    callback(
                        value
                    );
                }
            }
        );

        return future;
    }

    void ApplicationCryptographer::terminate_async(
        Result<std::future<void>>& result,
        const std::function<void(Result<void>& result)>& callback
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                Result<void> result;

                terminate(result);

                promise.set_value();

                callback(
                    result
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    ApplicationCryptographer& ApplicationCryptographer::get_instance()
    {
        static ApplicationCryptographer instance;

        return instance;
    }

    void ApplicationCryptographer::get_instance(
        Result<ApplicationCryptographer*>& result
    )
    {
        static ApplicationCryptographer instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}

