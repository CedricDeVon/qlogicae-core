#pragma once

#include "result.hpp"
#include "instance_manager.hpp"

namespace QLogicaeCppCore
{
    class FileSystemManager
    {
    public:
        FileSystemManager();

        ~FileSystemManager();

        FileSystemManager(
            const FileSystemManager& instance
        ) = delete;

        FileSystemManager(
            FileSystemManager&& instance
        ) noexcept = delete;

        FileSystemManager& operator = (
            FileSystemManager&& instance
        ) = delete;

        FileSystemManager& operator = (
            const FileSystemManager& instance
        ) = delete;

        void get_executable_folder_path(
            Result<std::string>& result
        );

        void get_executed_folder_path(
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

        void is_file_or_folder_path_found(
            Result<bool>& result,
            const std::string& path
        );

        void replace_file_if_found(
            Result<bool>& result,
            const std::string& folder_path,
            const std::string& file_path
        );

        void copy_file_or_folder(
            Result<bool>& result,
            const std::string& from_path,
            const std::string& to_path
        );

        void remove_file_or_folder_if_found(
            Result<bool>& result,
            const std::string& path
        );

        void create_folder_path(
            Result<bool>& result,
            const std::string& path,
            const bool& is_enabled = true
        );

        void clear_files(
            Result<bool>& result,
            const std::string& root_path
        );
    };

    inline static FileSystemManager& FILE_SYSTEM_MANAGER =
        INSTANCE_MANAGER.get_instance<FileSystemManager>();
}
