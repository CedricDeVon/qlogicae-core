#pragma once

#include "result.hpp"
#include "utilities.hpp"
#include "json_file_io.hpp"
#include "windows_registry.hpp"

namespace QLogicaeCore
{
    class Application
    {
    public:                               
        void get_application_id(
            Result<std::string>& result
        );
        
        void get_application_name(
            Result<std::string>& result
        );

        void get_application_version(
            Result<std::string>& result
        );

        void get_application_company(
            Result<std::string>& result
        );

        void get_application_authors(
            Result<std::string>& result
        );

        void get_application_description(
            Result<std::string>& result
        );

        void get_application_url(
            Result<std::string>& result
        );

        void get_application_architecture(
            Result<std::string>& result
        );

        void get_environment_id(
            Result<std::string>& result
        );

        void get_environment_name(
            Result<std::string>& result
        );

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

    protected:
        Application();

        ~Application() = default;

        Application(const Application&) = default;

        Application(Application&&) noexcept = delete;

        Application& operator = (Application&&) = default;

        Application& operator = (const Application&) = delete;

        std::mutex _mutex;
        
        std::string _application_id;

        std::string _application_name;

        std::string _application_version;

        std::string _application_company;

        std::string _application_authors;

        std::string _application_description;

        std::string _application_url;

        std::string _application_architecture;

        std::string _environment_id;

        std::string _environment_name;

        JsonFileIO _application_file;

        JsonFileIO _environment_file;
             
        WindowsRegistry& _hkcu;

        WindowsRegistry& _hklm;

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
}
