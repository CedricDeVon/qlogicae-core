#include "pch.hpp"

#include "../includes/application_utilities.hpp"

namespace QLogicaeCore
{
    ApplicationUtilities::ApplicationUtilities() :
        AbstractApplication()
    {
        CONFIGURATIONS_ENVIRONMENT_LOGGER =
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



            CONFIGURATIONS_ENVIRONMENT_LOGGER.name = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "logger", "name"
                }
            );

            string_output = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "logger", "format"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.format = UTILITIES.TIME_FORMAT_STRINGS_1.at(
                UTILITIES.TIME_FORMAT_STRINGS_1.contains(string_output) ? string_output : UTILITIES.TIME_FORMAT_FULL_TIMESTAMP_1
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "is_format_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_console_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "console", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "console", "is_format_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_file_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "file", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_file_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "file", "is_format_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_file_collectivization_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "file", "collectivization", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_file_collectivization_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "file", "collectivization", "is_format_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.file_collectivization_file_name = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "logger", "file", "collectivization", "file_name"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_file_fragmentation_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "file", "fragmentation", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_file_fragmentation_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "file", "fragmentation", "is_format_enabled"
                }
            );

            string_output = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_string(
                {
                    "logger", "file", "fragmentation", "file_name_format"
                }
            );
            CONFIGURATIONS_ENVIRONMENT_LOGGER.file_fragmentation_file_name_format = UTILITIES.TIME_FORMAT_STRINGS_1.at(
                UTILITIES.TIME_FORMAT_STRINGS_1.contains(string_output) ? string_output : UTILITIES.TIME_FORMAT_DATE_DASHED_1
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_file_custom_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "file", "custom", "is_enabled"
                }
            );

            CONFIGURATIONS_ENVIRONMENT_LOGGER.is_file_custom_format_enabled = QLOGICAE_APPLICATION_FILE_IO.JSON_FILE_IO.get_bool(
                {
                    "logger", "file", "custom", "is_format_enabled"
                }
            );

            // Post JSON Extraction        
            std::vector<std::any> log_file_output_paths = {};
            
            CONFIGURATIONS_ROAMING_APPDATA_APPLICTION_FOLDER =
                UTILITIES.FULL_ROAMING_APPDATA_FOLDER_PATH +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_FOLDER_PATH_3 +
                "\\" + CONFIGURATIONS_APPLICATION_ID +
                "\\" + CONFIGURATIONS_ENVIRONMENT_ID;

            CONFIGURATIONS_ENVIRONMENT_LOGGER.relative_root_folder_path =
                CONFIGURATIONS_ROAMING_APPDATA_APPLICTION_FOLDER +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FOLDER_PATH_1;

            CONFIGURATIONS_ENVIRONMENT_CACHES.relative_root_folder_path =
                CONFIGURATIONS_ROAMING_APPDATA_APPLICTION_FOLDER +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_CACHES_FOLDER_PATH_1;



            CONFIGURATIONS_ENVIRONMENT_LOGGER.file_collectivization_folder_path =
                CONFIGURATIONS_ENVIRONMENT_LOGGER.relative_root_folder_path;

            CONFIGURATIONS_ENVIRONMENT_LOGGER.file_fragmentation_folder_path =
                CONFIGURATIONS_ENVIRONMENT_LOGGER.relative_root_folder_path +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_LOGS_FRAGMENTS_FOLDER_PATH_1;

            CONFIGURATIONS_ENVIRONMENT_LOGGER.file_custom_output_paths = {};
            for (const auto& output_path : log_file_output_paths)
            {
                CONFIGURATIONS_ENVIRONMENT_LOGGER.file_custom_output_paths.push_back(
                    std::any_cast<std::string>(output_path)
                );
            }

            std::filesystem::create_directories(
                CONFIGURATIONS_ROAMING_APPDATA_APPLICTION_FOLDER
            );

            std::filesystem::create_directories(
                CONFIGURATIONS_ENVIRONMENT_LOGGER.file_collectivization_folder_path
            );

            std::filesystem::create_directories(
                CONFIGURATIONS_ENVIRONMENT_LOGGER.file_fragmentation_folder_path
            );



            
            CONFIGURATIONS_ENVIRONMENT_CACHES.relative_main_folder_path =
                CONFIGURATIONS_ENVIRONMENT_CACHES.relative_root_folder_path +
                "\\" + UTILITIES.RELATIVE_QLOGICAE_CACHES_MAIN_FOLDER_PATH_1;

            std::filesystem::create_directories(
                CONFIGURATIONS_ENVIRONMENT_CACHES.relative_root_folder_path
            );

            std::filesystem::create_directories(
                CONFIGURATIONS_ENVIRONMENT_CACHES.relative_main_folder_path
            );

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

    bool ApplicationUtilities::terminate()
    {
        try
        {
            Result<void> void_result;

            terminate(void_result);

            return void_result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::ApplicationUtilities::terminate()",
                exception.what()
            );

            return false;
        }
    }

    void ApplicationUtilities::terminate(
        Result<void>& result
    )
    {
        UTILITIES.BOOST_ASIO_POOL.join();

        set_is_enabled(false);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationUtilities::terminate_async(
        const std::function<void(const bool& value)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                bool value = terminate();

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

    void ApplicationUtilities::terminate_async(
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

                terminate(result);

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
