#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "application_logger.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationLogger :
        public AbstractApplication
    {
    public:
        bool setup(
            const LoggerConfigurations& logger_configurations
        );

        void setup(
            Result<void>& result,
            const LoggerConfigurations& logger_configurations
        );

        std::future<bool> setup_async(
            const LoggerConfigurations& logger_configurations
        );

        void setup_async(
            Result<std::future<void>>& result,
            const LoggerConfigurations& logger_configurations
        );

        static ApplicationLogger& get_instance();

        static void get_instance(
            Result<ApplicationLogger*>& result
        );

    protected:
        ApplicationLogger();

        ~ApplicationLogger();

        ApplicationLogger(
            const ApplicationLogger& instance
        ) = default;

        ApplicationLogger(
            ApplicationLogger&& instance
        ) noexcept = delete;

        ApplicationLogger& operator = (
            ApplicationLogger&& instance
        ) = default;

        ApplicationLogger& operator = (
            const ApplicationLogger& instance
        ) = delete;
    };

    inline static ApplicationLogger& QLOGICAE_APPLICATION_LOGGER =
        ApplicationLogger::get_instance();
}

