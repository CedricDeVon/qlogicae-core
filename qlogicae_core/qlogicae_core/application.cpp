#include "pch.hpp"

#include "application.hpp"

namespace QLogicaeCore
{   
    Application::Application() :
        AbstractApplication()
    {
        
    }

    Application::~Application()
    {

    }

    bool Application::setup()
    {       
        Result<void> void_result;

        setup(void_result);

        return void_result.is_status_safe();
    }

    void Application::setup(
        Result<void>& result
    )
    {
        try
        {  
            QLOGICAE_APPLICATION_FILE_IO.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            QLOGICAE_APPLICATION_UTILITIES.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            QLOGICAE_APPLICATION_LOGGER.setup(
                result,
                QLOGICAE_APPLICATION_UTILITIES.CONFIGURATIONS_ENVIRONMENT_LOG
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            QLOGICAE_APPLICATION_WINDOWS_REGISTRY.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            QLOGICAE_APPLICATION_CRYPTOGRAPHER.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            QLOGICAE_APPLICATION_CACHE.setup(
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
                "QLogicaeCore::Application::setup()",
                exception.what()
            );

            result.set_to_bad_status_without_value(
                std::string("QLogicaeCore::Application::setup() - ") +
                exception.what()
            );
        }
    }

    std::future<bool> Application::setup_async(
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

    void Application::setup_async(
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

    bool Application::is_qlogicae_project_found()
    {
        Result<void> result;

        is_qlogicae_project_found(result);

        return result.is_status_safe();
    }

    void Application::is_qlogicae_project_found(
        Result<void>& result
    )
    {
        if (!std::filesystem::exists(
            UTILITIES.RELATIVE_QLOGICAE_FOLDER_PATH_1
        ))
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Application::is_qlogicae_project_found()",
                "QLogicae based applications must be run ajacent with a 'qlogicae' folder at their root path"
            );

            return result.set_to_bad_status_without_value(
                "QLogicaeCore::Application::is_qlogicae_project_found() - QLogicae based applications must be run ajacent with a 'qlogicae' folder at their root path"
            );
        }

        result.set_to_good_status_without_value();
    }

    bool Application::terminate()
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
                "QLogicaeCore::Application::terminate()",
                exception.what()
            );

            return false;
        }
    }

    void Application::terminate(
        Result<void>& result
    )
    {       
        QLOGICAE_APPLICATION_CACHE.terminate(
            result
        );
        if (result.is_status_unsafe())
        {
            return;
        }

        QLOGICAE_APPLICATION_CRYPTOGRAPHER.terminate(
            result
        );
        if (result.is_status_unsafe())
        {
            return;
        }

        QLOGICAE_APPLICATION_WINDOWS_REGISTRY.terminate(
            result
        );
        if (result.is_status_unsafe())
        {
            return;
        }

        QLOGICAE_APPLICATION_LOGGER.terminate(
            result
        );
        if (result.is_status_unsafe())
        {
            return;
        }
        
        QLOGICAE_APPLICATION_UTILITIES.terminate(
            result
        );
        if (result.is_status_unsafe())
        {
            return;
        }

        QLOGICAE_APPLICATION_FILE_IO.terminate(
            result
        );
        if (result.is_status_unsafe())
        {
            return;
        }
        
        set_is_enabled(false);

        result.set_to_good_status_without_value();
    }

    std::future<bool> Application::terminate_async(
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

    void Application::terminate_async(
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

    Application& Application::get_instance()
    {
        static Application instance;

        return instance;
    }

    void Application::get_instance(
        Result<Application*>& result
    )
    {
        static Application instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
