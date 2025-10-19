#include "pch.hpp"

#include "application_utilities.hpp"

namespace QLogicaeCore
{
    ApplicationUtilities::ApplicationUtilities() :
        AbstractApplication()
    {

    }

    ApplicationUtilities::~ApplicationUtilities()
    {

    }

    bool ApplicationUtilities::setup()
    {
        set_is_enabled(true);

        return true;
    }

    void ApplicationUtilities::setup(
        Result<void>& result
    )
    {
        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationUtilities::setup_async()
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

    void ApplicationUtilities::setup_async(
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

    ApplicationUtilities& ApplicationUtilities::get_instance()
    {
        static ApplicationUtilities instance;

        return instance;
    }

    void ApplicationUtilities::get_instance(
        Result<ApplicationUtilities*>& result
    )
    {
        static ApplicationUtilities instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
