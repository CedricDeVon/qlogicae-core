#include "pch.hpp"

#include "application_cache.hpp"

namespace QLogicaeCore
{
    ApplicationCache::ApplicationCache() :
        AbstractApplication()
    {

    }

    ApplicationCache::~ApplicationCache()
    {

    }

    bool ApplicationCache::setup()
    {
        Result<void> void_result;

        setup(void_result);

        return void_result.is_status_safe();
    }

    void ApplicationCache::setup(
        Result<void>& result
    )
    {
        try
        {
            if (_is_enabled)
            {
                return result.set_to_bad_status_without_value(
                    "Exception at ApplicationCache::setup() - Can only be called once"
                );
            }

            set_is_enabled(true);

            result.set_to_good_status_without_value();
        }
        catch (const std::exception& exception)
        {
            result.set_to_bad_status_without_value(
                std::string("Exception at ApplicationCache::setup() - ") +
                exception.what()
            );
        }
    }

    std::future<bool> ApplicationCache::setup_async()
    {
        return std::async(
            std::launch::async,
            [this]() -> bool
            {
                return setup();
            }
        );
    }

    void ApplicationCache::setup_async(
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

    ApplicationCache& ApplicationCache::get_instance()
    {
        static ApplicationCache instance;

        return instance;
    }

    void ApplicationCache::get_instance(
        Result<ApplicationCache*>& result
    )
    {
        static ApplicationCache instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}

