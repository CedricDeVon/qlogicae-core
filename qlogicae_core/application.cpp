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
            QLOGICAE_APPLICATION_UTILITIES.setup(
                result
            );
            if (result.is_status_unsafe())
            {
                return;
            }

            QLOGICAE_APPLICATION_FILE_IO.setup(
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
                        .CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_FORMAT
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
            result.set_to_bad_status_without_value(
                std::string("Exception at Application::setup() - ") +
                exception.what()
            );
        }
    }

    std::future<bool> Application::setup_async()
    {
        return std::async(
            std::launch::async,
            [this]() -> bool
            {
                return setup();
            }
        );
    }

    void Application::setup_async(
        Result<std::future<void>>& result
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async,
                [this]() -> void
                {
                    Result<void> void_result;

                    setup(void_result);
                }
            )
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

/*
    void Application::get_configuration_application_id(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _configuration_application_id
        );
    }

    void Application::get_configuration_application_name(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _configuration_application_name
        );
    }

    void Application::get_configuration_application_version(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _configuration_application_version
        );
    }

    void Application::get_configuration_application_company(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _configuration_application_company
        );
    }

    void Application::get_configuration_application_authors(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _configuration_application_authors
        );
    }

    void Application::get_configuration_application_description(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _configuration_application_description
        );
    }

    void Application::get_configuration_application_url(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _configuration_application_url
        );
    }

    void Application::get_configuration_application_architecture(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _configuration_application_architecture
        );
    }

    void Application::get_configuration_environment_id(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _configuration_environment_id
        );
    }

    void Application::get_configuration_environment_name(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _configuration_environment_name
        );
    }

    void Application::get_hkcu_windows_registry_value(
        Result<std::string>& result,
        const std::string& key
    )
    {
        _get_full_windows_registry_sub_path(
            result
        );


        WindowsRegistry::hkcu().get_value_via_utf8(
            result,
            result.get_value(),
            key
        );
    }

    void Application::get_hklm_windows_registry_value(
        Result<std::string>& result,
        const std::string& key
    )
    {
        _get_full_windows_registry_sub_path(
            result
        );
        WindowsRegistry::hklm().get_value_via_utf8(
            result,
            result.get_value(),
            key
        );
    }

    void Application::setup(
        Result<void>& result
    )
    {
        _setup_windows_registry(result);
        _setup_application_file_data(result);
        _setup_environment_file_data(result);
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

    void Application::_get_full_windows_registry_sub_path(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            UTILITIES.RELATIVE_QLOGICAE_WINDOWS_REGISTRY_SUB_PATH +
            "\\" + _configuration_application_id +
            "\\" + _configuration_environment_id
        );
    }

    void Application::_setup_application_file_data(
        Result<void>& result
    )
    {
        _CONFIGURATION_APPLICATION_IO_FILE.set_file_path(
            UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_QLOGICAE_FILE_PATH
        );

        _configuration_application_id = _CONFIGURATION_APPLICATION_IO_FILE.get_string(
            {
                "id"
            }
        );

        _configuration_application_name = _CONFIGURATION_APPLICATION_IO_FILE.get_string(
            {
                "name"
            }
        );

        _configuration_application_version = _CONFIGURATION_APPLICATION_IO_FILE.get_string(
            {
                "version"
            }
        );

        _configuration_application_company = _CONFIGURATION_APPLICATION_IO_FILE.get_string(
            {
                "company"
            }
        );

        _configuration_application_authors = _CONFIGURATION_APPLICATION_IO_FILE.get_string(
            {
                "authors"
            }
        );

        _configuration_application_description = _CONFIGURATION_APPLICATION_IO_FILE.get_string(
            {
                "description"
            }
        );

        _configuration_application_url = _CONFIGURATION_APPLICATION_IO_FILE.get_string(
            {
                "url"
            }
        );

        _configuration_application_architecture = _CONFIGURATION_APPLICATION_IO_FILE.get_string(
            {
                "architecture"
            }
        );

        result.set_to_good_status_without_value();
    }

    void Application::_setup_environment_file_data(
        Result<void>& result
    )
    {
        _CONFIGURATION_ENVIRONMENT_IO_FILE.set_file_path(
            UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_ENVIRONMENT_FILE_PATH
        );

        _configuration_environment_id = _CONFIGURATION_ENVIRONMENT_IO_FILE.get_string(
            {
                "id"
            }
        );

        _configuration_environment_name = _CONFIGURATION_ENVIRONMENT_IO_FILE.get_string(
            {
                "name"
            }
        );

        result.set_to_good_status_without_value();
    }

    void Application::_setup_windows_registry(
        Result<void>& result
    )
    {
        _HKCU_WINDOWS_REGISTRY = &WindowsRegistry::hkcu();
        _HKCU_WINDOWS_REGISTRY->setup(result);

        _HKLM_WINDOWS_REGISTRY = &WindowsRegistry::hklm();
        _HKLM_WINDOWS_REGISTRY->setup(result);
    }
    */