#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "windows_registry.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationWindowsRegistry :
        public AbstractApplication
    {
    public:
        bool setup();

        std::future<bool> setup_async();

        void setup(
            Result<void>& result
        );

        void setup_async(
            Result<std::future<void>>& result
        );

        bool terminate();

        std::future<bool> terminate_async(
            const std::function<void(const bool& result)>& callback =
            [](const bool& result) {}
        );

        void terminate(
            Result<void>& result
        );

        void terminate_async(
            Result<std::future<void>>& result,
            const std::function<void(Result<void>& result)>& callback =
            [](Result<void>& result) {}
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

