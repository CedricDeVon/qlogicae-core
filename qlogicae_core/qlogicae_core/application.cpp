#include "pch.h"

#include "application.hpp"

namespace QLogicaeCore
{    
    Application::Application()
    {
        
    }

    bool Application::setup()
    {
        try
        {
            _load_qlogicae_file();
            _load_environment_file();

            return true;
        }
        catch (...)
        {
            return false;
        }        
    }

    Application& Application::get_instance()
    {
        static Application instance;

        return instance;
    }

    std::string Application::get_qlogicae_id()
    {
        return _qlogicae_id;
    }

    std::string Application::get_qlogicae_name()
    {
        return _qlogicae_name;
    }

    std::string Application::get_qlogicae_version()
    {
        return _qlogicae_version;
    }

    std::string Application::get_qlogicae_company()
    {
        return _qlogicae_company;
    }

    std::string Application::get_qlogicae_authors()
    {
        return _qlogicae_authors;
    }

    std::string Application::get_qlogicae_description()
    {
        return _qlogicae_description;
    }

    std::string Application::get_qlogicae_url()
    {
        return _qlogicae_url;
    }

    std::string Application::get_qlogicae_architecture()
    {
        return _qlogicae_architecture;
    }

    std::string Application::get_environment_id()
    {
        return _environment_id;
    }

    std::string Application::get_environment_name()
    {
        return _environment_name;
    }

    std::string Application::get_hkcu_windows_registry_value(
        const std::string& key
    )
    {
        return WindowsRegistry::hkcu().get_value_via_utf8(
            _get_full_windows_registry_sub_path(), key
        ).value();
    }

    std::string Application::get_hklm_windows_registry_value(
        const std::string& key
    )
    {
        return WindowsRegistry::hklm().get_value_via_utf8(
            _get_full_windows_registry_sub_path(), key
        ).value();
    }

    std::string Application::_get_full_windows_registry_sub_path()
    {
        return absl::StrCat(
            UTILITIES.RELATIVE_QLOGICAE_WINDOWS_REGISTRY_SUB_PATH, "\\",
            _qlogicae_id, "\\",
            _environment_id
        );
    }

    void Application::_load_qlogicae_file()
    {
        _qlogicae_file.set_file_path(
            UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_QLOGICAE_FILE_PATH
        );

        _qlogicae_id = _qlogicae_file.get_string({
            "id"
        });

        _qlogicae_name = _qlogicae_file.get_string({
            "name"
        });

        _qlogicae_version = _qlogicae_file.get_string({
            "version"
        });

        _qlogicae_company = _qlogicae_file.get_string({
            "company"
        });

        _qlogicae_authors = _qlogicae_file.get_string({
            "authors"
        });

        _qlogicae_description = _qlogicae_file.get_string({
            "description"
        });

        _qlogicae_url = _qlogicae_file.get_string({
            "url"
        });

        _qlogicae_architecture = _qlogicae_file.get_string({
            "architecture"
        });
    }

    void Application::_load_environment_file()
    {
        _environment_file.set_file_path(
            UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_ENVIRONMENT_FILE_PATH
        );

        _environment_id = _environment_file.get_string({
            "id"
        });

        _environment_name = _environment_file.get_string({
            "name"
        });
    }
}
