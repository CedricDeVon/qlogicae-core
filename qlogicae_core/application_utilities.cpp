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

        CONFIGURATIONS_ENVIRONMENT_LANGUAGE_SELECTED = "";


        CONFIGURATIONS_ENVIRONMENT_LOG_NAME = "";

        CONFIGURATIONS_ENVIRONMENT_LOG_FORMAT =
            TimeFormat::FULL_TIMESTAMP;
        
        CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED = false;

        CONFIGURATIONS_ENVIRONMENT_LOG_IS_SIMPLIFIED = false;

        CONFIGURATIONS_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED = false;

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_ENABLED = false;
        
        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_COLLECTIVIZATION_ENABLED = false;

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_FRAGMENTATION_ENABLED = false;

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_FORMAT =
            TimeFormat::DATE_DMY_SLASHED;


        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_OUTPUT_PATHS = {};

        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_COLLECTIVIZATION_PATH = "";
        
        CONFIGURATIONS_ENVIRONMENT_LOG_FILE_FRAGMENTATION_OUTPUT_FOLDER_PATH = "";
                
        CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM =
            LogMedium::ALL;
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
        try
        {
            if (_is_enabled)
            {
                return result.set_to_bad_status_without_value(
                    "Exception at ApplicationUtilities::setup() - Can only be called once"
                );
            }

            if (!QLOGICAE_APPLICATION_FILE_IO.get_is_enabled())
            {
                return result.set_to_bad_status_without_value(
                    "Exception at ApplicationUtilities::setup() - QLOGICAE_APPLICATION_FILE_IO is currently disabled"
                );
            }

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

            CONFIGURATIONS_ENVIRONMENT_LANGUAGE_SELECTED = JSON_FILE_IO.get_string(
                {
                    "language", "selected"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG_NAME = JSON_FILE_IO.get_string(
                {
                    "log", "name"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG_FORMAT = UTILITIES.TIME_FORMAT_STRINGS_1.at(
                JSON_FILE_IO.get_string(
                    {
                        "log", "format"
                    }
                )
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
                        "log", "file", "fragmentation_format"
                    }
                )
            );

            std::vector<std::any> log_file_output_paths =
                JSON_FILE_IO.get_array(
                    {
                        "log", "file", "output_paths"
                    }
                );

            // Post JSON Extraction
            CONFIGURATIONS_ENVIRONMENT_LOG_FILE_OUTPUT_PATHS =
            {
                CONFIGURATIONS_ENVIRONMENT_LOG_FILE_COLLECTIVIZATION_PATH
            };
            for (const auto& output_path : log_file_output_paths)
            {
                CONFIGURATIONS_ENVIRONMENT_LOG_FILE_OUTPUT_PATHS.push_back(
                    std::any_cast<std::string>(output_path)
                );
            }

            CONFIGURATIONS_ENVIRONMENT_LOG_FILE_COLLECTIVIZATION_PATH =
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
            
            if (CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED &&
                CONFIGURATIONS_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED &&
                CONFIGURATIONS_ENVIRONMENT_LOG_FILE_IS_ENABLED
            )
            {
                CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM = LogMedium::ALL;
            }
            else if (CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED &&
                CONFIGURATIONS_ENVIRONMENT_LOG_CONSOLE_IS_ENABLED
            )
            {
                CONFIGURATIONS_ENVIRONMENT_LOG_MEDIUM = LogMedium::CONSOLE;
            }
            else if (CONFIGURATIONS_ENVIRONMENT_LOG_IS_ENABLED &&
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
        catch (const std::exception& exception)
        {
            result.set_to_bad_status_without_value(
                std::string("Exception at ApplicationUtilities::setup() - ") +
                exception.what()
            );
        }        
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
