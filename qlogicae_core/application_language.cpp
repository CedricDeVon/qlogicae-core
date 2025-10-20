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
        Result<void> void_result;

        setup(void_result);

        return void_result.is_status_safe();
    }

    void ApplicationLanguage::setup(
        Result<void>& result
    )
    {
        try
        {
            if (_is_enabled)
            {
                return result.set_to_bad_status_without_value(
                    "Exception at ApplicationLanguage::setup() - Can only be called once"
                );
            }

            set_is_enabled(true);

            result.set_to_good_status_without_value();
        }
        catch (const std::exception& exception)
        {
            result.set_to_bad_status_without_value(
                std::string("Exception at ApplicationLanguage::setup() - ") +
                exception.what()
            );
        }
    }

    std::future<bool> ApplicationLanguage::setup_async()
    {
        return std::async(
            std::launch::async,
            [this]() -> bool
            {
                return setup();
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
                    Result<void> void_result;

                    setup(void_result);
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
