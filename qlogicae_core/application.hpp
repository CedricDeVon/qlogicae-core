#pragma once

#include "utilities.hpp"
#include "json_file_io.hpp"
#include "windows_registry.hpp"

namespace QLogicaeCore
{
    class Application
    {
    public:                        
        std::string get_qlogicae_id();

        std::string get_qlogicae_name();

        std::string get_qlogicae_version();

        std::string get_qlogicae_company();

        std::string get_qlogicae_authors();

        std::string get_qlogicae_description();

        std::string get_qlogicae_url();

        std::string get_qlogicae_architecture();

        std::string get_environment_id();

        std::string get_hkcu_windows_registry_value(
            const std::string& key
        );

        std::string get_hklm_windows_registry_value(
            const std::string& key
        );

        static Application& get_instance();

        bool setup();

    protected:
        Application();

        ~Application() = default;

        Application(const Application&) = default;

        Application(Application&&) noexcept = delete;

        Application& operator = (Application&&) = default;

        Application& operator = (const Application&) = delete;

        std::mutex _mutex;
        
        std::string _qlogicae_id;

        std::string _qlogicae_name;

        std::string _qlogicae_version;

        std::string _qlogicae_company;

        std::string _qlogicae_authors;

        std::string _qlogicae_description;

        std::string _qlogicae_url;

        std::string _qlogicae_architecture;

        std::string _environment_id;

        QLogicaeCore::JsonFileIO _qlogicae_file;

        QLogicaeCore::JsonFileIO _environment_file;

        std::string _get_full_windows_registry_sub_path();

        void _load_qlogicae_file();

        void _load_environment_file();
    };    

    inline static Application& APPLICATION =
        Application::get_instance();
}
