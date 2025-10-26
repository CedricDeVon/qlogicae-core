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
                {
                    .name = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_NAME,

                    .log_medium = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM,
                
                    .log_time_zone = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_TIME_ZONE,

                    .log_format = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_FORMAT,

                    .is_simplified = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_IS_SIMPLIFIED,

                    .output_paths = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_FILE_OUTPUT_PATHS,

                    .is_log_file_fragmentation_enabled = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_FRAGMENTATION_ENABLED,

                    .log_file_fragmentation_output_folder_path = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_OUTPUT_FOLDER_PATH,

                    .log_file_fragmentation_format = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_FORMAT,

                    .is_log_file_collectivization_enabled = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_COLLECTIVIZATION_ENABLED,

                    .log_file_collectivization_output_file_name = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_FILE_COLLECTIVIZATION_FILE_NAME,

                    .log_file_collectivization_output_folder_path = QLOGICAE_APPLICATION_UTILITIES
                        .CONFIGURATIONS_ENVIRONMENT_LOG_FILE_COLLECTIVIZATION_OUTPUT_FOLDER_PATH,
                }
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
