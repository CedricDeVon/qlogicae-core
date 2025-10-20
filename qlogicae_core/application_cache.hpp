#pragma once

#include "result.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationCache :
        public AbstractApplication
    {
    public:
        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            Result<std::future<void>>& result
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
