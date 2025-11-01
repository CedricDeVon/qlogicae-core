#include "pch.hpp"

#include "application_windows_registry.hpp"

namespace QLogicaeCore
{
    ApplicationWindowsRegistry::ApplicationWindowsRegistry() :
        AbstractApplication()
    {

    }

    ApplicationWindowsRegistry::~ApplicationWindowsRegistry()
    {

    }

    bool ApplicationWindowsRegistry::setup()
    {
        Result<void> result;

        setup(result);

        return result.is_status_safe();
    }

    void ApplicationWindowsRegistry::setup(
        Result<void>& result
    )
    {
        try
        {
            if (_is_enabled)
            {
                LOGGER.handle_exception_async(
                    "QLogicaeCore::ApplicationWindowsRegistry::setup()",
                    "Can only be called once"
                );

                return result.set_to_bad_status_without_value(
                    "QLogicaeCore::ApplicationWindowsRegistry::setup() - Can only be called once"
                );
            }

            WindowsRegistry::hkcu().setup(result);
            if (result.is_status_unsafe())
            {
                return;
            }

            WindowsRegistry::hklm().setup(result);
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
                "QLogicaeCore::ApplicationWindowsRegistry::setup()",
                exception.what()
            );

            result.set_to_bad_status_without_value(
                std::string("QLogicaeCore::ApplicationWindowsRegistry::setup() - ") +
                exception.what()
            );
        }
    }

    std::future<bool> ApplicationWindowsRegistry::setup_async()
    {
        return std::async(
            std::launch::async,
            [this]() -> bool
            {                
                return setup();
            }
        );
    }

    void ApplicationWindowsRegistry::setup_async(
        Result<std::future<void>>& result
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async,
                [this]() -> void
                {
                    Result<void> result;

                    setup(result);
                }
            )
        );
    }

    bool ApplicationWindowsRegistry::terminate()
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
                "QLogicaeCore::ApplicationWindowsRegistry::terminate()",
                exception.what()
            );

            return false;
        }
    }

    void ApplicationWindowsRegistry::terminate(
        Result<void>& result
    )
    {
        set_is_enabled(false);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationWindowsRegistry::terminate_async(
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

    void ApplicationWindowsRegistry::terminate_async(
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

    ApplicationWindowsRegistry& ApplicationWindowsRegistry::get_instance()
    {
        static ApplicationWindowsRegistry instance;

        return instance;
    }

    void ApplicationWindowsRegistry::get_instance(
        Result<ApplicationWindowsRegistry*>& result
    )
    {
        static ApplicationWindowsRegistry instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}

