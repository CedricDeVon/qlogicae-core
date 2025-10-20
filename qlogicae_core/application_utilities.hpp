#pragma once

#include "result.hpp"
#include "log_medium.hpp"
#include "time_format.hpp"
#include "application_file_io.hpp"
#include "abstract_application.hpp"
#include "logger_configurations.hpp"

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

        std::string CONFIGURATIONS_ENVIRONMENT_LANGUAGE_SELECTED;

        std::string CONFIGURATIONS_ENVIRONMENT_LOG_NAME;

        TimeFormat CONFIGURATIONS_ENVIRONMENT_LOG_FORMAT;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_IS_SIMPLIFIED;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_ENABLED;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_COLLECTIVIZATION_ENABLED;

        bool CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_FRAGMENTATION_ENABLED;

        TimeFormat CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_FORMAT;


        std::vector<std::string> CONFIGURATIONS_ENVIRONMENT_LOG_FILE_OUTPUT_PATHS;

        std::string CONFIGURATIONS_ENVIRONMENT_LOG_FILE_COLLECTIVIZATION_PATH;

        std::string CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_OUTPUT_FOLDER_PATH;

        LogMedium CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM;

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
