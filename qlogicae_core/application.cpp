#include "pch.hpp"

#include "application.hpp"

namespace QLogicaeCore
{   
    void Application::get_application_id(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _application_id
        );
    }

    void Application::get_application_name(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _application_name
        );
    }

    void Application::get_application_version(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _application_version
        );
    }

    void Application::get_application_company(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _application_company
        );
    }

    void Application::get_application_authors(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _application_authors
        );
    }

    void Application::get_application_description(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _application_description
        );
    }

    void Application::get_application_url(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _application_url
        );
    }

    void Application::get_application_architecture(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _application_architecture
        );
    }

    void Application::get_environment_id(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _environment_id
        );
    }

    void Application::get_environment_name(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _environment_name
        );
    }

    void Application::get_hkcu_windows_registry_value(
        Result<std::string>& result,
        const std::string& key
    )
    {
        _get_full_windows_registry_sub_path(
            result
        );
        

        WindowsRegistry::hkcu().get_value_via_utf8(
            result,
            result.get_value(),
            key
        );
    }

    void Application::get_hklm_windows_registry_value(
        Result<std::string>& result,
        const std::string& key
    )
    {
        _get_full_windows_registry_sub_path(
            result
        );
        WindowsRegistry::hklm().get_value_via_utf8(
            result,
            result.get_value(),
            key
        );        
    }

    void Application::setup(
        Result<void>& result
    )
    {
        _setup_windows_registry(result);
        _setup_application_file_data(result);
        _setup_environment_file_data(result);
    }

    Application& Application::get_instance()
    {
        static Application instance;

        return instance;
    }

    void Application::get_instance(
        Result<Application*>& result
    )
    {
        static Application instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }

    Application::Application()        
    {
        
    }

    void Application::_get_full_windows_registry_sub_path(
        Result<std::string>& result
    )
    {        
        result.set_to_good_status_with_value(
            UTILITIES.RELATIVE_QLOGICAE_WINDOWS_REGISTRY_SUB_PATH +
            "\\" + _application_id +
            "\\" + _environment_id            
        );
    }

    void Application::_setup_application_file_data(
        Result<void>& result
    )
    {
        _application_file.set_file_path(
            UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_QLOGICAE_FILE_PATH
        );

        _application_id = _application_file.get_string(
            {
                "id"
            }
        );

        _application_name = _application_file.get_string(
            {
                "name"
            }
        );

        _application_version = _application_file.get_string(
            {
                "version"
            }
        );

        _application_company = _application_file.get_string(
            {
                "company"
            }
        );

        _application_authors = _application_file.get_string(
            {
                "authors"
            }
        );

        _application_description = _application_file.get_string(
            {
                "description"
            }
        );

        _application_url = _application_file.get_string(
            {
                "url"
            }
        );

        _application_architecture = _application_file.get_string(
            {
                "architecture"
            }
        );

        result.set_to_good_status_without_value();
    }

    void Application::_setup_environment_file_data(
        Result<void>& result
    )
    {
        _environment_file.set_file_path(
            UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_ENVIRONMENT_FILE_PATH
        );

        _environment_id = _environment_file.get_string(
            {
                "id"
            }
        );

        _environment_name = _environment_file.get_string(
            {
                "name"
            }
        );

        result.set_to_good_status_without_value();
    }

    void Application::_setup_windows_registry(
        Result<void>& result
    )
    {
        _hkcu = &WindowsRegistry::hkcu();
        _hkcu->setup(result);

        _hklm = &WindowsRegistry::hklm();
        _hklm->setup(result);
    }
}
