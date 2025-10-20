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
        Result<void> result;

        setup(result);

        return result.is_status_safe();
    }

    void ApplicationWindowsRegistry::setup(
        Result<void>& result
    )
    {
        if (_is_enabled)
        {
            return result.set_to_bad_status_without_value();
        }

        WindowsRegistry::hkcu().setup(result);
        if (result.is_status_unsafe())
        {
            return result.set_to_bad_status_without_value();
        }

        WindowsRegistry::hklm().setup(result);
        if (result.is_status_unsafe())
        {
            return result.set_to_bad_status_without_value();
        }

        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationWindowsRegistry::setup_async()
    {
        return std::async(
            std::launch::async,
            [this]() -> bool
            {                
                return setup();
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
                    Result<void> result;

                    setup(result);
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
