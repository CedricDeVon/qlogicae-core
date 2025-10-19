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
        set_is_enabled(true);

        return true;
    }

    void ApplicationCache::setup(
        Result<void>& result
    )
    {
        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationCache::setup_async()
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

    void ApplicationCache::setup_async(
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
