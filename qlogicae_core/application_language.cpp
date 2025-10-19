#include "pch.hpp"

#include "application_language.hpp"

namespace QLogicaeCore
{
    ApplicationLanguage::ApplicationLanguage() :
        AbstractApplication()
    {

    }

    ApplicationLanguage::~ApplicationLanguage()
    {

    }

    bool ApplicationLanguage::setup()
    {
        set_is_enabled(true);

        return true;
    }

    void ApplicationLanguage::setup(
        Result<void>& result
    )
    {
        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationLanguage::setup_async()
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

    void ApplicationLanguage::setup_async(
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

    ApplicationLanguage& ApplicationLanguage::get_instance()
    {
        static ApplicationLanguage instance;

        return instance;
    }

    void ApplicationLanguage::get_instance(
        Result<ApplicationLanguage*>& result
    )
    {
        static ApplicationLanguage instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
