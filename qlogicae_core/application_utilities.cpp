#include "pch.hpp"

#include "application_utilities.hpp"

namespace QLogicaeCore
{
    ApplicationUtilities::ApplicationUtilities() :
        AbstractApplication()
    {
        CONFIGURATIONS_APPLICATION_ID = "";

        CONFIGURATIONS_APPLICATION_NAME = "";

        CONFIGURATIONS_APPLICATION_VERSION = "";

        CONFIGURATIONS_APPLICATION_COMPANY = "";

        CONFIGURATIONS_APPLICATION_AUTHORS = "";

        CONFIGURATIONS_APPLICATION_DESCRIPTION = "";

        CONFIGURATIONS_APPLICATION_URL = "";

        CONFIGURATIONS_APPLICATION_ARCHITECTURE = "";

        CONFIGURATIONS_ENVIRONMENT_ID = "";

        CONFIGURATIONS_ENVIRONMENT_NAME = "";

        CONFIGURATIONS_ENVIRONMENT_LOG_FORMAT =
            TimeFormat::FULL_TIMESTAMP;

        CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED = false;

        CONFIGURATIONS_ENVIRONMENT_LOG_IS_SIMPLIFIED = false;

        CONFIGURATIONS_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED = false;

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_ENABLED = false;
        
        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_COLLECTIVIZATION_ENABLED = false;

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_FRAGMENTATION_ENABLED = false;

        CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM =
            LogMedium::ALL;

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_FORMAT =
            TimeFormat::DATE_DMY_SLASHED;

        CONFIGURATIONS_ENVIRONMENT_LANGUAGE_SELECTED = "";
    }

    ApplicationUtilities::~ApplicationUtilities()
    {

    }

    bool ApplicationUtilities::setup()
    {
        Result<void> result;

        setup(result);

        return result.is_status_safe();
    }

    void ApplicationUtilities::setup(
        Result<void>& result
    )
    {
        if (_is_enabled)
        {
            return result.set_to_bad_status_without_value();
        }

        /*
        if (!QLOGICAE_APPLICATION_FILE_IO.get_is_enabled())
        {
            return result.set_to_bad_status_without_value();
        }
        */

        // JSON Extraction
        JSON_FILE_IO.set_file_path(
            UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_QLOGICAE_FILE_PATH
        );

        CONFIGURATIONS_APPLICATION_ID = JSON_FILE_IO.get_string(
            {
                "id"
            }
        );

        CONFIGURATIONS_APPLICATION_NAME = JSON_FILE_IO.get_string(
            {
                "name"
            }
        );

        CONFIGURATIONS_APPLICATION_VERSION = JSON_FILE_IO.get_string(
            {
                "version"
            }
        );

        CONFIGURATIONS_APPLICATION_COMPANY = JSON_FILE_IO.get_string(
            {
                "company"
            }
        );

        CONFIGURATIONS_APPLICATION_AUTHORS = JSON_FILE_IO.get_string(
            {
                "authors"
            }
        );

        CONFIGURATIONS_APPLICATION_DESCRIPTION = JSON_FILE_IO.get_string(
            {
                "description"
            }
        );

        CONFIGURATIONS_APPLICATION_URL = JSON_FILE_IO.get_string(
            {
                "url"
            }
        );

        CONFIGURATIONS_APPLICATION_ARCHITECTURE = JSON_FILE_IO.get_string(
            {
                "architecture"
            }
        );

        JSON_FILE_IO.set_file_path(
            UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_ENVIRONMENT_FILE_PATH
        );

        CONFIGURATIONS_ENVIRONMENT_ID = JSON_FILE_IO.get_string(
            {
                "id"
            }
        );

        CONFIGURATIONS_ENVIRONMENT_NAME = JSON_FILE_IO.get_string(
            {
                "name"
            }
        );

        CONFIGURATIONS_ENVIRONMENT_LOG_NAME = JSON_FILE_IO.get_string(
            {
                "log", "name"
            }
        );

        CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED = JSON_FILE_IO.get_bool(
            {
                "log", "is_enabled"
            }
        );

        CONFIGURATIONS_ENVIRONMENT_LOG_IS_SIMPLIFIED = JSON_FILE_IO.get_bool(
            {
                "log", "is_simplified"
            }
        );
        
        CONFIGURATIONS_ENVIRONMENT_LOG_FORMAT = UTILITIES.TIME_FORMAT_STRINGS_1.at(
            JSON_FILE_IO.get_string(
                {
                    "log", "format"
                }
            )
        );

        CONFIGURATIONS_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED = JSON_FILE_IO.get_bool(
            {
                "log", "console", "is_enabled"
            }
        );

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_ENABLED = JSON_FILE_IO.get_bool(
            {
                "log", "file", "is_enabled"
            }
        );

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_COLLECTIVIZATION_ENABLED = JSON_FILE_IO.get_bool(
            {
                "log", "file", "is_collectivization_enabled"
            }
        );

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_FRAGMENTATION_ENABLED = JSON_FILE_IO.get_bool(
            {
                "log", "file", "is_fragmentation_enabled"
            }
        );

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_FORMAT = UTILITIES.TIME_FORMAT_STRINGS_1.at(
            JSON_FILE_IO.get_string(
                {
                    "log", "file", "fragmentation_file_format"
                }
            )
        );

        std::vector<std::any> extracted_output_paths =
            JSON_FILE_IO.get_array(
                {
                    "log", "file", "output_paths"
                }
            );
        
        CONFIGURATIONS_ENVIRONMENT_LANGUAGE_SELECTED = JSON_FILE_IO.get_string(
            {
                "language", "selected"
            }
        );

        // Post JSON Extraction
        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_ALL_PATH =
            UTILITIES.FULL_ROAMING_APPDATA_FOLDER_PATH +
            "\\" + UTILITIES.RELATIVE_QLOGICAE_FOLDER_PATH_3 +
            "\\" + CONFIGURATIONS_APPLICATION_ID +
            "\\" + CONFIGURATIONS_ENVIRONMENT_ID +
            "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FOLDER_PATH_1 +
            "\\" + UTILITIES.RELATIVE_QLOGICAE_ALL_LOGS_FILE_PATH;

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_OUTPUT_FOLDER_PATH =
            UTILITIES.FULL_ROAMING_APPDATA_FOLDER_PATH +
            "\\" + UTILITIES.RELATIVE_QLOGICAE_FOLDER_PATH_3 +
            "\\" + CONFIGURATIONS_APPLICATION_ID +
            "\\" + CONFIGURATIONS_ENVIRONMENT_ID +
            "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FOLDER_PATH_1 +
            "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FRAGMENTS_FOLDER_PATH_1;

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_OUTPUT_PATHS =
        {
            CONFIGURATIONS_ENVIRONMENT_LOG_FILE_ALL_PATH            
        };
        for (const auto& output_path : extracted_output_paths)
        {
            CONFIGURATIONS_ENVIRONMENT_LOG_FILE_OUTPUT_PATHS.push_back(
                std::any_cast<std::string>(output_path)
            );
        }

        if (
            CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED &&
            CONFIGURATIONS_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED &&
            CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_ENABLED
        )
        {
            CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM = LogMedium::ALL;
        }
        else if (
            CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED &&
            CONFIGURATIONS_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED
        )
        {
            CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM = LogMedium::CONSOLE;
        }
        else if (
            CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED &&
            CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_ENABLED
            )
        {
            CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM = LogMedium::FILE;
        }
        else
        {
            CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM = LogMedium::NONE;
        }       

        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationUtilities::setup_async()
    {
        return std::async(
            std::launch::async,
            [this]() -> bool
            {
                return setup();
            }
        );
    }

    void ApplicationUtilities::setup_async(
        Result<std::future<void>>& result
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async,
                [this]() -> void
                {
                    Result<void> result;

                    setup(result);
                }
            )
        );
    }


    ApplicationUtilities& ApplicationUtilities::get_instance()
    {
        static ApplicationUtilities instance;

        return instance;
    }

    void ApplicationUtilities::get_instance(
        Result<ApplicationUtilities*>& result
    )
    {
        static ApplicationUtilities instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}

/*
    std::string ApplicationUtilities::get_configuration_application_id()
    {
        Result<std::string> result;

        get_configuration_application_id(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_application_id(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_APPLICATION_ID
        );
    }

    std::string ApplicationUtilities::get_configuration_application_name()
    {
        Result<std::string> result;

        get_configuration_application_name(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_application_name(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_APPLICATION_NAME
        );
    }

    std::string ApplicationUtilities::get_configuration_application_version()
    {
        Result<std::string> result;

        get_configuration_application_version(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_application_version(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_APPLICATION_VERSION
        );
    }

    std::string ApplicationUtilities::get_configuration_application_company()
    {
        Result<std::string> result;

        get_configuration_application_company(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_application_company(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_APPLICATION_COMPANY
        );
    }

    std::string ApplicationUtilities::get_configuration_application_authors()
    {
        Result<std::string> result;

        get_configuration_application_authors(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_application_authors(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_APPLICATION_AUTHORS
        );
    }

    std::string ApplicationUtilities::get_configuration_application_description()
    {
        Result<std::string> result;

        get_configuration_application_description(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_application_description(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_APPLICATION_DESCRIPTION
        );
    }

    std::string ApplicationUtilities::get_configuration_application_url()
    {
        Result<std::string> result;

        get_configuration_application_url(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_application_url(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_APPLICATION_URL
        );
    }

    std::string ApplicationUtilities::get_configuration_application_architecture()
    {
        Result<std::string> result;

        get_configuration_application_architecture(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_application_architecture(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_APPLICATION_ARCHITECTURE
        );
    }

    std::string ApplicationUtilities::get_configuration_environment_id()
    {
        Result<std::string> result;

        get_configuration_environment_id(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_environment_id(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_ENVIRONMENT_ID
        );
    }

    std::string ApplicationUtilities::get_configuration_environment_name()
    {
        Result<std::string> result;

        get_configuration_environment_name(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_environment_name(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_ENVIRONMENT_NAME
        );
    }

    bool ApplicationUtilities::get_configuration_environment_log_is_enabled()
    {
        Result<bool> result;

        get_configuration_environment_log_is_enabled(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_environment_log_is_enabled(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED
        );
    }

    bool ApplicationUtilities::get_configuration_environment_log_console_is_enabled()
    {
        Result<bool> result;

        get_configuration_environment_log_console_is_enabled(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_environment_log_console_is_enabled(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED
        );
    }

    bool ApplicationUtilities::get_configuration_environment_log_file_is_enabled()
    {
        Result<bool> result;

        get_configuration_environment_log_file_is_enabled(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_environment_log_file_is_enabled(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_ENABLED
        );
    }

    bool ApplicationUtilities::get_configuration_environment_log_file_is_collectivization_enabled()
    {
        Result<bool> result;

        get_configuration_environment_log_file_is_collectivization_enabled(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_environment_log_file_is_collectivization_enabled(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_COLLECTIVIZATION_ENABLED
        );
    }

    bool ApplicationUtilities::get_configuration_environment_log_file_is_fragmentation_enabled()
    {
        Result<bool> result;

        get_configuration_environment_log_file_is_fragmentation_enabled(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_environment_log_file_is_fragmentation_enabled(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_FRAGMENTATION_ENABLED
        );
    }

    TimeFormat ApplicationUtilities::get_configuration_environment_log_file_fragmentation_file_format()
    {
        Result<TimeFormat> result;

        get_configuration_environment_log_file_fragmentation_file_format(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_environment_log_file_fragmentation_file_format(
        Result<TimeFormat>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_FORMAT
        );
    }

    std::string ApplicationUtilities::get_configuration_environment_language_selected()
    {
        Result<std::string> result;

        get_configuration_environment_language_selected(result);

        return result.get_value();
    }

    void ApplicationUtilities::get_configuration_environment_language_selected(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            CONFIGURATIONS_ENVIRONMENT_LANGUAGE_SELECTED
        );
    }

*/