#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "time_zone.hpp"
#include "log_medium.hpp"
#include "time_format.hpp"
#include "application_file_io.hpp"
#include "abstract_application.hpp"
#include "logger_configurations.hpp"

#include <filesystem>

namespace QLogicaeCore
{
    class ApplicationUtilities :
        public AbstractApplication
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

        TimeZone CONFIGURATIONS_ENVIRONMENT_TIME_ZONE;
        
        std::string CONFIGURATIONS_ENVIRONMENT_LANGUAGE_SELECTED;

        LoggerConfigurations CONFIGURATIONS_ENVIRONMENT_LOG;

        bool setup();

        std::future<bool> setup_async(
            const std::function<void(const bool& result)>& callback =
                [](const bool& result) {}
        );

        void setup(
            Result<void>& result
        );

        void setup_async(
            Result<std::future<void>>& result,
            const std::function<void(Result<void>& result)>& callback =
                [](Result<void>& result) {}
        );

        bool terminate();

        std::future<bool> terminate_async(
            const std::function<void(const bool& result)>& callback =
            [](const bool& result) {}
        );

        void terminate(
            Result<void>& result
        );

        void terminate_async(
            Result<std::future<void>>& result,
            const std::function<void(Result<void>& result)>& callback =
            [](Result<void>& result) {}
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
