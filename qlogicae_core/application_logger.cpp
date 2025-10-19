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

    bool ApplicationLogger::setup()
    {
        set_is_enabled(true);

        return true;
    }

    void ApplicationLogger::setup(
        Result<void>& result
    )
    {
        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationLogger::setup_async()
    {
        return std::async(
            std::launch::async,
            [this]() -> bool
            {
                set_is_enabled(true);

                return true;
            }
        );
    }

    void ApplicationLogger::setup_async(
        Result<std::future<void>>& result
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async,
                [this]() -> void
                {
                    set_is_enabled(true);
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
