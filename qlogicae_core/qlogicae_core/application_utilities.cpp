#include "pch.hpp"

#include "application_utilities.hpp"

namespace QLogicaeCore
{
    ApplicationUtilities::ApplicationUtilities() :
        AbstractApplication()
    {
        CONFIGURATIONS_ENVIRONMENT_LOG =
            DEFAULT_LOGGER_CONFIGURATIONS;
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
            std::string string_output;

            if (_is_enabled)
            {
                LOGGER.handle_exception_async(
                    "QLogicaeCore::ApplicationUtilities::setup()",
                    "Can only be called once"
                );

                return result.set_to_bad_status_without_value(
                    "QLogicaeCore::ApplicationUtilities::setup() - Can only be called once"
                );
            }

            if (!QLOGICAE_APPLICATION_FILE_IO.get_is_enabled())
            {
                LOGGER.handle_exception_async(
                    "QLogicaeCore::ApplicationUtilities::setup()",
                    "QLOGICAE_APPLICATION_FILE_IO is currently disabled"
                );

                return result.set_to_bad_status_without_value(
                    "QLogicaeCore::ApplicationUtilities::setup() - QLOGICAE_APPLICATION_FILE_IO is currently disabled"
                );
            }

            // JSON Extraction
            QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.set_file_path(
                UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_QLOGICAE_FILE_PATH
            );

            CONFIGURATIONS_APPLICATION_ID = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "id"
                }
            );

            CONFIGURATIONS_APPLICATION_NAME = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "name"
                }
            );

            CONFIGURATIONS_APPLICATION_VERSION = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "version"
                }
            );

            CONFIGURATIONS_APPLICATION_COMPANY = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "company"
                }
            );

            CONFIGURATIONS_APPLICATION_AUTHORS = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "authors"
                }
            );

            CONFIGURATIONS_APPLICATION_DESCRIPTION = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "description"
                }
            );

            CONFIGURATIONS_APPLICATION_URL = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "url"
                }
            );

            CONFIGURATIONS_APPLICATION_ARCHITECTURE = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "architecture"
                }
            );



            QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.set_file_path(
                UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_ENVIRONMENT_FILE_PATH
            );

            CONFIGURATIONS_ENVIRONMENT_ID = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "id"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_NAME = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "name"
                }
            );

            string_output = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "time", "zone"
                }
            );
            CONFIGURATIONS_ENVIRONMENT_TIME_ZONE = UTILITIES.TIME_ZONE_STRINGS_1.at(
                UTILITIES.TIME_ZONE_STRINGS_1.contains(string_output) ? string_output : UTILITIES.TIME_ZONE_LOCAL_1
            );

            CONFIGURATIONS_ENVIRONMENT_LANGUAGE_SELECTED = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "language", "selected"
                }
            );



            CONFIGURATIONS_ENVIRONMENT_LOG.name = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "log", "name"
                }
            );

            string_output = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "log", "format"
                }
            );
            CONFIGURATIONS_ENVIRONMENT_LOG.log_format = UTILITIES.TIME_FORMAT_STRINGS_1.at(
                UTILITIES.TIME_FORMAT_STRINGS_1.contains(string_output) ? string_output : UTILITIES.TIME_FORMAT_FULL_TIMESTAMP_1
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_log_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "is_log_format_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_console_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "console", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_log_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "console", "is_log_format_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_file_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "file", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_file_log_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "file", "is_log_format_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_file_collectivization_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "file", "collectivization", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_file_collectivization_log_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "file", "collectivization", "is_log_format_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.file_collectivization_file_name = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "log", "file", "collectivization", "file_name"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_file_fragmentation_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "file", "fragmentation", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_file_fragmentation_log_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "file", "fragmentation", "is_log_format_enabled"
                }
            );

            string_output = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "log", "file", "fragmentation", "file_name_format"
                }
            );
            CONFIGURATIONS_ENVIRONMENT_LOG.file_fragmentation_file_name_format = UTILITIES.TIME_FORMAT_STRINGS_1.at(
                UTILITIES.TIME_FORMAT_STRINGS_1.contains(string_output) ? string_output : UTILITIES.TIME_FORMAT_DATE_DASHED_1
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_file_custom_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "file", "custom", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOG.is_file_custom_log_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "log", "file", "custom", "is_log_format_enabled"
                }
            );

            std::vector<std::any> log_file_output_paths = {};
            // Post JSON Extraction        

            CONFIGURATIONS_ENVIRONMENT_LOG.file_collectivization_folder_path =
                UTILITIES.FULL_ROAMING_APPDATA_FOLDER_PATH +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_FOLDER_PATH_3 +
                "\\" + CONFIGURATIONS_APPLICATION_ID +
                "\\" + CONFIGURATIONS_ENVIRONMENT_ID +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FOLDER_PATH_1;

            CONFIGURATIONS_ENVIRONMENT_LOG.file_fragmentation_folder_path =
                UTILITIES.FULL_ROAMING_APPDATA_FOLDER_PATH +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_FOLDER_PATH_3 +
                "\\" + CONFIGURATIONS_APPLICATION_ID +
                "\\" + CONFIGURATIONS_ENVIRONMENT_ID +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FOLDER_PATH_1 +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FRAGMENTS_FOLDER_PATH_1;

            CONFIGURATIONS_ENVIRONMENT_LOG.file_custom_output_paths = {};
            for (const auto& output_path : log_file_output_paths)
            {
                CONFIGURATIONS_ENVIRONMENT_LOG.file_custom_output_paths.push_back(
                    std::any_cast<std::string>(output_path)
                );
            }

            std::filesystem::create_directories(
                UTILITIES.FULL_ROAMING_APPDATA_FOLDER_PATH +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_FOLDER_PATH_3 +
                "\\" + CONFIGURATIONS_APPLICATION_ID +
                "\\" + CONFIGURATIONS_ENVIRONMENT_ID
            );
            std::filesystem::create_directories(
                UTILITIES.FULL_ROAMING_APPDATA_FOLDER_PATH +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_FOLDER_PATH_3 +
                "\\" + CONFIGURATIONS_APPLICATION_ID +
                "\\" + CONFIGURATIONS_ENVIRONMENT_ID +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FOLDER_PATH_1
            );
            std::filesystem::create_directories(
                UTILITIES.FULL_ROAMING_APPDATA_FOLDER_PATH +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_FOLDER_PATH_3 +
                "\\" + CONFIGURATIONS_APPLICATION_ID +
                "\\" + CONFIGURATIONS_ENVIRONMENT_ID +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FOLDER_PATH_1 +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FRAGMENTS_FOLDER_PATH_1
            );

            if (CONFIGURATIONS_ENVIRONMENT_LOG.is_enabled &&
                CONFIGURATIONS_ENVIRONMENT_LOG.is_console_enabled &&
                CONFIGURATIONS_ENVIRONMENT_LOG.is_file_enabled
                )
            {
                CONFIGURATIONS_ENVIRONMENT_LOG.medium = LogMedium::ALL;
            }
            else if (CONFIGURATIONS_ENVIRONMENT_LOG.is_enabled &&
                CONFIGURATIONS_ENVIRONMENT_LOG.is_console_enabled
                )
            {
                CONFIGURATIONS_ENVIRONMENT_LOG.medium = LogMedium::CONSOLE;
            }
            else if (CONFIGURATIONS_ENVIRONMENT_LOG.is_enabled &&
                CONFIGURATIONS_ENVIRONMENT_LOG.is_file_enabled
                )
            {
                CONFIGURATIONS_ENVIRONMENT_LOG.medium = LogMedium::FILE;
            }
            else
            {
                CONFIGURATIONS_ENVIRONMENT_LOG.medium = LogMedium::NONE;
            }

            set_is_enabled(true);

            result.set_to_good_status_without_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::ApplicationUtilities::setup()",
                exception.what()
            );

            result.set_to_bad_status_without_value(
                std::string("QLogicaeCore::ApplicationUtilities::setup() - ") +
                exception.what()
            );
        }        
    }

    std::future<bool> ApplicationUtilities::setup_async(
        const std::function<void(const bool& value)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                bool value = setup();

                promise.set_value(
                    value
                );

                if (callback)
                {
                    callback(
                        value
                    );
                }
            }
        );

        return future;
    }

    void ApplicationUtilities::setup_async(
        Result<std::future<void>>& result,
        const std::function<void(Result<void>& result)>& callback
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(result);

                promise.set_value();

                callback(
                    result
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
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
