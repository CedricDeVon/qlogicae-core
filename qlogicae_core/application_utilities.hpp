#pragma once

#include "result.hpp"
#include "log_medium.hpp"
#include "time_format.hpp"
#include "application_file_io.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationUtilities :
        AbstractApplication
    {
    public:
        std::string CONFIGURATIONS_APPLICATION_ID;

        std::string CONFIGURATIONS_APPLICATION_NAME;

        std::string CONFIGURATIONS_APPLICATION_VERSION;

        std::string CONFIGURATIONS_APPLICATION_COMPANY;

        std::string CONFIGURATIONS_APPLICATION_AUTHORS;

        std::string CONFIGURATIONS_APPLICATION_DESCRIPTION;

        std::string CONFIGURATIONS_APPLICATION_URL;

        std::string CONFIGURATIONS_APPLICATION_ARCHITECTURE;

        std::string CONFIGURATIONS_ENVIRONMENT_ID;

        std::string CONFIGURATIONS_ENVIRONMENT_NAME;

        TimeFormat CONFIGURATIONS_ENVIRONMENT_LOG_FORMAT;

        std::string CONFIGURATIONS_ENVIRONMENT_LOG_NAME;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_IS_SIMPLIFIED;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_ENABLED;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_COLLECTIVIZATION_ENABLED;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_FRAGMENTATION_ENABLED;

        std::string CONFIGURATIONS_ENVIRONMENT_LOG_FILE_ALL_PATH;

        std::string CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_OUTPUT_FOLDER_PATH;

        TimeFormat CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_FORMAT;

        std::vector<std::string> CONFIGURATIONS_ENVIRONMENT_LOG_FILE_OUTPUT_PATHS;

        LogMedium CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM;

        std::string CONFIGURATIONS_ENVIRONMENT_LANGUAGE_SELECTED;

        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            Result<std::future<void>>& result
        );

        static ApplicationUtilities& get_instance();

        static void get_instance(
            Result<ApplicationUtilities*>& result
        );

    protected:
        ApplicationUtilities();

        ~ApplicationUtilities();

        ApplicationUtilities(
            const ApplicationUtilities& instance
        ) = default;

        ApplicationUtilities(
            ApplicationUtilities&& instance
        ) noexcept = delete;

        ApplicationUtilities& operator = (
            ApplicationUtilities&& instance
        ) = default;

        ApplicationUtilities& operator = (
            const ApplicationUtilities& instance
        ) = delete;
    };

    inline static ApplicationUtilities& QLOGICAE_APPLICATION_UTILITIES =
        ApplicationUtilities::get_instance();
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

        bool get_configuration_environment_log_is_enabled();

        void get_configuration_environment_log_is_enabled(
            Result<bool>& result
        );

        bool get_configuration_environment_log_console_is_enabled();

        void get_configuration_environment_log_console_is_enabled(
            Result<bool>& result
        );

        bool get_configuration_environment_log_file_is_enabled();

        void get_configuration_environment_log_file_is_enabled(
            Result<bool>& result
        );

        bool get_configuration_environment_log_file_is_collectivization_enabled();

        void get_configuration_environment_log_file_is_collectivization_enabled(
            Result<bool>& result
        );

        bool get_configuration_environment_log_file_is_fragmentation_enabled();

        void get_configuration_environment_log_file_is_fragmentation_enabled(
            Result<bool>& result
        );

        TimeFormat get_configuration_environment_log_file_fragmentation_file_format();

        void get_configuration_environment_log_file_fragmentation_file_format(
            Result<TimeFormat>& result
        );

        std::string get_configuration_environment_language_selected();

        void get_configuration_environment_language_selected(
            Result<std::string>& result
        );

*/