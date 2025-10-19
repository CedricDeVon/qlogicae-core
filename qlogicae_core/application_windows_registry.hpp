#pragma once

#include "result.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationWindowsRegistry :
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

        static ApplicationWindowsRegistry& get_instance();

        static void get_instance(
            Result<ApplicationWindowsRegistry*>& result
        );

    protected:
        ApplicationWindowsRegistry();

        ~ApplicationWindowsRegistry();

        ApplicationWindowsRegistry(
            const ApplicationWindowsRegistry& instance
        ) = default;

        ApplicationWindowsRegistry(
            ApplicationWindowsRegistry&& instance
        ) noexcept = delete;

        ApplicationWindowsRegistry& operator = (
            ApplicationWindowsRegistry&& instance
            ) = default;

        ApplicationWindowsRegistry& operator = (
            const ApplicationWindowsRegistry& instance
            ) = delete;
    };

    inline static ApplicationWindowsRegistry& QLOGICAE_APPLICATION_WINDOWS_REGISTRY =
        ApplicationWindowsRegistry::get_instance();
}
