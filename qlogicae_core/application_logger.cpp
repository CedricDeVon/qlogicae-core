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
                return result.set_to_bad_status_without_value(
                    "Exception at ApplicationLogger::setup() - Can only be called once"
                );
            }

            MAIN_LOGGER.setup(
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
            result.set_to_bad_status_without_value(
                std::string("Exception at ApplicationLogger::setup() - ") +
                exception.what()
            );
        }        
    }

    std::future<bool> ApplicationLogger::setup_async(
        const LoggerConfigurations& logger_configurations
    )
    {
        return std::async(
            std::launch::async,
            [this, logger_configurations]() -> bool
            {
                return setup(
                    logger_configurations
                );
            }
        );
    }

    void ApplicationLogger::setup_async(
        Result<std::future<void>>& result,
        const LoggerConfigurations& logger_configurations
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async,
                [this, logger_configurations]() -> void
                {
                    Result<void> result;

                    setup(
                        result,
                        logger_configurations
                    );
                }
            )
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
