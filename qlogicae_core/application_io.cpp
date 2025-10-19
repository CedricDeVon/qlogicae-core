#include "pch.hpp"

#include "application_io.hpp"

namespace QLogicaeCore
{
    ApplicationIO::ApplicationIO() :
        AbstractApplication()
    {

    }

    ApplicationIO::~ApplicationIO()
    {

    }

    bool ApplicationIO::setup()
    {
        set_is_enabled(true);

        return true;
    }

    void ApplicationIO::setup(
        Result<void>& result
    )
    {
        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationIO::setup_async()
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

    void ApplicationIO::setup_async(
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

    ApplicationIO& ApplicationIO::get_instance()
    {
        static ApplicationIO instance;

        return instance;
    }

    void ApplicationIO::get_instance(
        Result<ApplicationIO*>& result
    )
    {
        static ApplicationIO instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
