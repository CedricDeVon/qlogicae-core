#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "abstract_application.hpp"
#include "application_cache.hpp"
#include "application_logger.hpp"
#include "application_file_io.hpp"
#include "application_language.hpp"
#include "application_utilities.hpp"
#include "application_cryptographer.hpp"
#include "application_startup_inputs.hpp"
#include "application_windows_registry.hpp"

namespace QLogicaeCore
{
    class Application :
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

        bool is_qlogicae_project_found();

        void is_qlogicae_project_found(
            Result<void>& result
        );

        static Application& get_instance();

        static void get_instance(
            Result<Application*>& result
        );

    protected:
        Application();

        ~Application();

        Application(
            const Application& instance
        ) = default;

        Application(
            Application&& instance
        ) noexcept = delete;

        Application& operator = (
            Application&& instance
        ) = default;

        Application& operator = (
            const Application& instance
        ) = delete;
    };

    inline static Application& QLOGICAE_APPLICATION =
        Application::get_instance();
}
