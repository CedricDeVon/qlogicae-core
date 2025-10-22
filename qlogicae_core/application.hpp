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
        
        void setup(
            Result<void>& result
        );
        
        std::future<bool> setup_async();

        void setup_async(
            Result<std::future<void>>& result
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





/*

    void _get_full_windows_registry_sub_path(
        Result<std::string>& result
    );

    class Application
    {
    public:
        

        void get_hkcu_windows_registry_value(
            Result<std::string>& result,
            const std::string& key
        );

        void get_hklm_windows_registry_value(
            Result<std::string>& result,
            const std::string& key
        );



        void setup(
            Result<void>& result
        );

        static Application& get_instance();

        static void get_instance(
            Result<Application*>& result
        );

        void _get_full_windows_registry_sub_path(
            Result<std::string>& result
        );

        void _setup_application_file_data(
            Result<void>& result
        );

        void _setup_environment_file_data(
            Result<void>& result
        );

        void _setup_windows_registry(
            Result<void>& result
        );
    };

    inline static Application& QLOGICAE =
        Application::get_instance();
    */
