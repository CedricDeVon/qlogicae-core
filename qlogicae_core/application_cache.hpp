#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationCache :
        public AbstractApplication
    {
    public:
        bool setup();

        std::future<bool> setup_async(
            const std::function<void(const bool& result)>& callback =
            [](const bool& result) {}
        );

        void setup(
            Result<void>& result
        );
        
        void setup_async(
            Result<std::future<void>>& result,
            const std::function<void(Result<void>& result)>& callback =
            [](Result<void>& result) {}
        );

        static ApplicationCache& get_instance();

        static void get_instance(
            Result<ApplicationCache*>& result
        );

    protected:
        ApplicationCache();

        ~ApplicationCache();

        ApplicationCache(
            const ApplicationCache& instance
        ) = default;

        ApplicationCache(
            ApplicationCache&& instance
        ) noexcept = delete;

        ApplicationCache& operator = (
            ApplicationCache&& instance
        ) = default;

        ApplicationCache& operator = (
            const ApplicationCache& instance
        ) = delete;
    };

    inline static ApplicationCache& QLOGICAE_APPLICATION_CACHE =
        ApplicationCache::get_instance();
}
