#include "pch.hpp"

#include "application_logger.hpp"

namespace QLogicaeCore
{
    ApplicationLogger::ApplicationLogger() :
        AbstractApplication()
    {

    }

    ApplicationLogger::~ApplicationLogger()
    {

    }

    bool ApplicationLogger::setup(
        const LoggerConfigurations& logger_configurations
    )
    {
        Result<void> result;

        setup(
            result,
            logger_configurations
        );

        return result.is_status_safe();
    }

    void ApplicationLogger::setup(
        Result<void>& result,
        const LoggerConfigurations& logger_configurations
    )
    {
        try
        {
            if (_is_enabled)
            {
                LOGGER.handle_exception_async(
                    "QLogicaeCore::ApplicationLogger::setup()",
                    "Can only be called once"
                );

                return result.set_to_bad_status_without_value(
                    "QLogicaeCore::ApplicationLogger::setup() - Can only be called once"
                );
            }

            LOGGER.setup(
                result,
                logger_configurations
            );
            if (result.is_status_unsafe())
            {
                return result.set_to_bad_status_without_value();
            }

            set_is_enabled(true);

            result.set_to_good_status_without_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::ApplicationLogger::setup()",
                exception.what()
            );

            result.set_to_bad_status_without_value(
                std::string("QLogicaeCore::ApplicationLogger::setup() - ") +
                exception.what()
            );
        }        
    }

    std::future<bool> ApplicationLogger::setup_async(
        const LoggerConfigurations& logger_configurations,
        const std::function<void(const bool& value)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, logger_configurations, callback, promise = std::move(promise)]() mutable
            {
                bool value = setup(
                    logger_configurations
                );

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

    void ApplicationLogger::setup_async(
        Result<std::future<void>>& result,
        const LoggerConfigurations& logger_configurations,
        const std::function<void(Result<void>& result)>& callback
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, logger_configurations, callback, promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(
                    result,
                    logger_configurations
                );

                promise.set_value();

                callback(
                    result
                );
            }
        );
    }

    bool ApplicationLogger::terminate()
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
                "QLogicaeCore::ApplicationLogger::terminate()",
                exception.what()
            );

            return false;
        }
    }

    void ApplicationLogger::terminate(
        Result<void>& result
    )
    {
        set_is_enabled(false);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationLogger::terminate_async(
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

    void ApplicationLogger::terminate_async(
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

    ApplicationLogger& ApplicationLogger::get_instance()
    {
        static ApplicationLogger instance;

        return instance;
    }

    void ApplicationLogger::get_instance(
        Result<ApplicationLogger*>& result
    )
    {
        static ApplicationLogger instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
