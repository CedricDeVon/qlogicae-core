#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "encoder.hpp"

#include <windows.h>
#include <filesystem>

namespace QLogicaeCore
{
    class FileSystem
    {
    public:
        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            const std::function<void(const bool& result)>& callback
        );

        void setup_async(
            Result<std::future<void>>& result
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback
        );

        std::string get_executable_dir();

        std::string get_executable_folder();

        std::string get_executed_folder();

        std::string get_programdata_folder_path();

        std::string get_local_appdata_folder_path();

        std::string get_roaming_appdata_folder_path();

        void get_executable_dir(
            Result<std::string>& result
        );

        void get_executable_folder(
            Result<std::string>& result
        );

        void get_executed_folder(
            Result<std::string>& result
        );

        void get_programdata_folder_path(
            Result<std::string>& result
        );

        void get_local_appdata_folder_path(
            Result<std::string>& result
        );

        void get_roaming_appdata_folder_path(
            Result<std::string>& result
        );

        bool is_file_or_folder_path_found(
            const std::string& path
        );

        bool replace_file_if_found(
            const std::string& folder_path,
            const std::string& file_path
        );

        bool copy_file_or_folder(
            const std::string& from_path,
            const std::string& to_path
        );

        bool remove_file_or_folder_if_found(
            const std::string& path
        );

        bool create_folder_path(
            const std::string& path,
            const bool& is_enabled = true
        );

        bool clear_files(
            const std::string& root_path
        );

        void clear_files(
            Result<void>& result,
            const std::string& root_path
        );

        std::future<bool> clear_files_async(
            const std::string& root_path
        );

        void clear_files_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& root_path
        );

        void clear_files_async(
            Result<std::future<bool>>& result,
            const std::string& root_path
        );

        void clear_files_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string& root_path
        );

        bool terminate();

        void terminate(
            Result<void>& result
        );

        std::future<bool> terminate_async();

        void terminate_async(
            const std::function<void(const bool& result)>& callback
        );

        void terminate_async(
            Result<std::future<void>>& result
        );

        void terminate_async(
            const std::function<void(Result<void>& result)>& callback
        );

        static FileSystem& get_instance();

        static void get_instance(
            Result<FileSystem*>& results
        );

    protected:
        FileSystem();

        ~FileSystem();

        FileSystem(
            const FileSystem& instance
        ) = delete;

        FileSystem(
            FileSystem&& instance
        ) noexcept = delete;

        FileSystem& operator = (
            FileSystem&& instance
            ) = delete;

        FileSystem& operator = (
            const FileSystem& instance
            ) = delete;
    };

    inline static FileSystem& FILE_SYSTEM =
        FileSystem::get_instance();
}
