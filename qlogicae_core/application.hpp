#pragma once

#include "result.hpp"
#include "abstract_application.hpp"
#include "application_io.hpp"
#include "application_cache.hpp"
#include "application_logger.hpp"
#include "application_language.hpp"
#include "application_utilities.hpp"
#include "application_cryptographer.hpp"
#include "application_startup_inputs.hpp"
#include "application_windows_registry.hpp"

namespace QLogicaeCore
{
    class Application :
        public AbstractApplication
    {
    public:        
        bool setup();
        
        void setup(
            Result<void>& result
        );
        
        std::future<bool> setup_async();

        void setup_async(
            Result<std::future<void>>& result
        );

        static Application& get_instance();

        static void get_instance(
            Result<Application*>& result
        );

    protected:
        Application();

        ~Application();

        Application(
            const Application& instance
        ) = default;

        Application(
            Application&& instance
        ) noexcept = delete;

        Application& operator = (
            Application&& instance
        ) = default;

        Application& operator = (
            const Application& instance
        ) = delete;
    };

    inline static Application& QLOGICAE_APPLICATION =
        Application::get_instance();
}

/*

std::string get_configuration_application_id();

        void get_configuration_application_id(
            Result<std::string>& result
        );

        std::string get_configuration_application_name();

        void get_configuration_application_name(
            Result<std::string>& result
        );

        std::string get_configuration_application_version();

        void get_configuration_application_version(
            Result<std::string>& result
        );

        std::string get_configuration_application_company();

        void get_configuration_application_company(
            Result<std::string>& result
        );

        std::string get_configuration_application_authors();

        void get_configuration_application_authors(
            Result<std::string>& result
        );

        std::string get_configuration_application_description();

        void get_configuration_application_description(
            Result<std::string>& result
        );

        std::string get_configuration_application_url();

        void get_configuration_application_url(
            Result<std::string>& result
        );

        std::string get_configuration_application_architecture();

        void get_configuration_application_architecture(
            Result<std::string>& result
        );

        std::string get_configuration_environment_id();

        void get_configuration_environment_id(
            Result<std::string>& result
        );

        std::string get_configuration_environment_name();

        void get_configuration_environment_name(
            Result<std::string>& result
        );


        std::string _CONFIGURATION_APPLICATION_ID;

        std::string _CONFIGURATION_APPLICATION_NAME;

        std::string _CONFIGURATION_APPLICATION_VERSION;

        std::string _CONFIGURATION_APPLICATION_COMPANY;

        std::string _CONFIGURATION_APPLICATION_AUTHORS;

        std::string _CONFIGURATION_APPLICATION_DESCRIPTION;

        std::string _CONFIGURATION_APPLICATION_URL;

        std::string _CONFIGURATION_APPLICATION_ARCHITECTURE;

        std::string _CONFIGURATION_ENVIRONMENT_ID;

        std::string _CONFIGURATION_ENVIRONMENT_NAME;
        void _get_full_windows_registry_sub_path(
            Result<std::string>& result
        );

    class Application
    {
    public:
        void get_configuration_application_id(
            Result<std::string>& result
        );

        void get_configuration_application_name(
            Result<std::string>& result
        );

        void get_configuration_application_version(
            Result<std::string>& result
        );

        void get_configuration_application_company(
            Result<std::string>& result
        );

        void get_configuration_application_authors(
            Result<std::string>& result
        );

        void get_configuration_application_description(
            Result<std::string>& result
        );

        void get_configuration_application_url(
            Result<std::string>& result
        );

        void get_configuration_application_architecture(
            Result<std::string>& result
        );

        void get_configuration_environment_id(
            Result<std::string>& result
        );

        void get_configuration_environment_name(
            Result<std::string>& result
        );

        void get_configuration_environment_log_medium(
            Result<LogMedium>& result
        );

        void get_configuration_environment_log_is_enabled(
            Result<bool>& result
        );

        void get_configuration_environment_log_console_is_enabled(
            Result<bool>& result
        );

        void get_configuration_environment_log_file_is_enabled(
            Result<bool>& result
        );

        void get_configuration_environment_log_file_is_collectivization_enabled(
            Result<bool>& result
        );

        void get_configuration_environment_log_file_is_fragmentation_enabled(
            Result<bool>& result
        );

        void get_configuration_environment_log_file_fragmentation_file_format(
            Result<std::string>& result
        );

        void get_configuration_environment_log_file_additional_output_paths(
            Result<std::vector<std::string>>& result
        );

        void get_hkcu_windows_registry_value(
            Result<std::string>& result,
            const std::string& key
        );

        void get_hklm_windows_registry_value(
            Result<std::string>& result,
            const std::string& key
        );



        void setup(
            Result<void>& result
        );

        static Application& get_instance();

        static void get_instance(
            Result<Application*>& result
        );

    protected:
        Application();

        ~Application() = default;

        Application(
            const Application&
        ) = default;

        Application(
            Application&&
        ) noexcept = delete;

        Application& operator = (
            Application&&
        ) = default;

        Application& operator = (
            const Application&
        ) = delete;

        std::mutex _mutex;

        std::string _CONFIGURATION_APPLICATION_ID;

        std::string _CONFIGURATION_APPLICATION_NAME;

        std::string _CONFIGURATION_APPLICATION_VERSION;

        std::string _CONFIGURATION_APPLICATION_COMPANY;

        std::string _CONFIGURATION_APPLICATION_AUTHORS;

        std::string _CONFIGURATION_APPLICATION_DESCRIPTION;

        std::string _CONFIGURATION_APPLICATION_URL;

        std::string _CONFIGURATION_APPLICATION_ARCHITECTURE;

        std::string _CONFIGURATION_ENVIRONMENT_ID;

        std::string _CONFIGURATION_ENVIRONMENT_NAME;

        LogMedium _CONFIGURATION_ENVIRONMENT_LOG_MEDIUM;

        bool _CONFIGURATION_ENVIRONMENT_LOG_IS_ENABLED;

        bool _CONFIGURATION_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED;

        bool _CONFIGURATION_ENVIRONMENT_LOG_FILE_IS_ENABLED;

        bool _CONFIGURATION_ENVIRONMENT_LOG_FILE_IS_COLLECTIVIZATION_ENABLED;

        bool _CONFIGURATION_ENVIRONMENT_LOG_FILE_IS_FRAGMENTATION_ENABLED;

        std::string _CONFIGURATION_ENVIRONMENT_LOG_FILE_FRAGMENTATION_FILE_FORMAT;

        std::vector<std::string> _CONFIGURATION_ENVIRONMENT_LOG_FILE_ADDITIONAL_OUTPUT_PATHS;

        Logger _LOGGER;



        JsonFileIO _CONFIGURATION_APPLICATION_IO_FILE;

        JsonFileIO _CONFIGURATION_ENVIRONMENT_IO_FILE;

        WindowsRegistry* _HKCU_WINDOWS_REGISTRY;

        WindowsRegistry* _HKLM_WINDOWS_REGISTRY;

        void _get_full_windows_registry_sub_path(
            Result<std::string>& result
        );

        void _setup_application_file_data(
            Result<void>& result
        );

        void _setup_environment_file_data(
            Result<void>& result
        );

        void _setup_windows_registry(
            Result<void>& result
        );
    };

    inline static Application& QLOGICAE =
        Application::get_instance();
    */