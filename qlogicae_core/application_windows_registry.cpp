#include "pch.hpp"

#include "application_windows_registry.hpp"

namespace QLogicaeCore
{
    ApplicationWindowsRegistry::ApplicationWindowsRegistry() :
        AbstractApplication()
    {

    }

    ApplicationWindowsRegistry::~ApplicationWindowsRegistry()
    {

    }

    bool ApplicationWindowsRegistry::setup()
    {
        set_is_enabled(true);

        return true;
    }

    void ApplicationWindowsRegistry::setup(
        Result<void>& result
    )
    {
        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationWindowsRegistry::setup_async()
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

    void ApplicationWindowsRegistry::setup_async(
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

    ApplicationWindowsRegistry& ApplicationWindowsRegistry::get_instance()
    {
        static ApplicationWindowsRegistry instance;

        return instance;
    }

    void ApplicationWindowsRegistry::get_instance(
        Result<ApplicationWindowsRegistry*>& result
    )
    {
        static ApplicationWindowsRegistry instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
