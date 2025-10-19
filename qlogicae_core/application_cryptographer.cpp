#include "pch.hpp"

#include "application_cryptographer.hpp"

namespace QLogicaeCore
{
    ApplicationCryptographer::ApplicationCryptographer() :
        AbstractApplication()
    {

    }

    ApplicationCryptographer::~ApplicationCryptographer()
    {

    }

    bool ApplicationCryptographer::setup()
    {
        set_is_enabled(true);

        return true;
    }

    void ApplicationCryptographer::setup(
        Result<void>& result
    )
    {
        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationCryptographer::setup_async()
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

    void ApplicationCryptographer::setup_async(
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

    ApplicationCryptographer& ApplicationCryptographer::get_instance()
    {
        static ApplicationCryptographer instance;

        return instance;
    }

    void ApplicationCryptographer::get_instance(
        Result<ApplicationCryptographer*>& result
    )
    {
        static ApplicationCryptographer instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
