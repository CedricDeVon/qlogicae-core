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

        void construct(
            Result<bool>& result
        );

        void destruct(
            Result<bool>& result
        );

        void get_executable_folder_path(
            Result<std::string>& result
        );

        void get_executed_folder_path(
            Result<std::string>& result
        );

        void get_program_data_folder_path(
            Result<std::string>& result
        );

        void get_local_app_data_folder_path(
            Result<std::string>& result
        );

        void get_roaming_app_data_folder_path(
            Result<std::string>& result
        );
        
        void get_file_byte_size(
            Result<std::size_t>& result,
            const std::string_view& from_path
        );

        void get_folder_byte_size(
            Result<std::size_t>& result,
            const std::string_view& from_path,
            const bool& is_recursive
        );

        void get_absolute_path(
            Result<std::string_view>& result,
            const std::string_view& from_path
        );

        void get_relative_path(
            Result<std::string_view>& result,
            const std::string_view& from_path,
            const std::string_view& to_path
        );

        void get_file_extension(
            Result<std::string>& result,
            const std::string_view& from_path
        );

        void get_file_stem(
            Result<std::string>& result,
            const std::string_view& from_path
        );

        void get_entity_paths(
            Result<std::vector<std::string>>& result,
            const std::string_view& from_path,
            const bool& is_recursive
        );

        void get_file_paths(
            Result<std::vector<std::string>>& result,
            const std::string_view& from_path,
            const bool& is_recursive
        );

        void get_folder_paths(
            Result<std::vector<std::string>>& result,
            const std::string_view& from_path,
            const bool& is_recursive
        );

        void is_path_found(
            Result<bool>& result,
            const std::string_view& from_path
        );

        void is_entity(
            Result<bool>& result,
            const std::string_view& from_path
        );

        void is_file(
            Result<bool>& result,
            const std::string_view& from_path
        );

        void is_folder(
            Result<bool>& result,
            const std::string_view& from_path
        );

        void is_entity_user_permission_level_valid(
            Result<bool>& result,
            const std::string_view& from_path,
            const std::filesystem::perms& permission_level
        );

        void find_files_by_pattern(
            Result<std::vector<std::string>>& result,
            const std::string_view& from_path,
            const std::string_view& pattern,
            const bool& is_recursive
        );

        void set_entity_read_status(
            Result<bool>& result,
            const std::string_view& from_path,
            const bool& value
        );

        void set_entity_write_status(
            Result<bool>& result,
            const std::string_view& from_path,
            const bool& value
        );

        void set_entity_visibility(
            Result<bool>& result,
            const std::string_view& from_path,
            const bool& value
        );

        void create_folder(
            Result<bool>& result,
            const std::string_view& from_path
        );

        void copy_file(
            Result<bool>& result,
            const std::string_view& from_path,
            const std::string_view& to_path
        );

        void copy_folder(
            Result<bool>& result,
            const std::string_view& from_path,
            const std::string_view& to_path,
            const bool& is_recursive
        );

        void move_entity(
            Result<bool>& result,
            const std::string_view& from_path,
            const std::string_view& to_path
        );

        void move_file(
            Result<bool>& result,
            const std::string_view& from_path,
            const std::string_view& to_path
        );

        void move_folder(
            Result<bool>& result,
            const std::string_view& from_path,
            const std::string_view& to_path
        );

        void rename_entity(
            Result<bool>& result,
            const std::string_view& from_path,
            const std::string_view& name
        );

        void rename_file(
            Result<bool>& result,
            const std::string_view& from_path,
            const std::string_view& name
        );

        void rename_folder(
            Result<bool>& result,
            const std::string_view& from_path,
            const std::string_view& name
        );

        void remove_file(
            Result<bool>& result,
            const std::string_view& from_path
        );

        void remove_folder(
            Result<bool>& result,
            const std::string_view& from_path
        );

        void remove_folder_sub_files(
            Result<bool>& result,
            const std::string_view& from_path,
            const bool& is_recursive
        );

        void get_executable_folder_path(
            Result<std::wstring>& result
        );

        void get_executed_folder_path(
            Result<std::wstring>& result
        );

        void get_program_data_folder_path(
            Result<std::wstring>& result
        );

        void get_local_app_data_folder_path(
            Result<std::wstring>& result
        );

        void get_roaming_app_data_folder_path(
            Result<std::wstring>& result
        );

        void get_file_byte_size(
            Result<std::size_t>& result,
            const std::wstring_view& from_path
        );

        void get_folder_byte_size(
            Result<std::size_t>& result,
            const std::wstring_view& from_path,
            const bool& is_recursive
        );

        void get_absolute_path(
            Result<std::wstring_view>& result,
            const std::wstring_view& from_path
        );

        void get_relative_path(
            Result<std::wstring_view>& result,
            const std::wstring_view& from_path,
            const std::wstring_view& to_path
        );

        void get_file_extension(
            Result<std::wstring>& result,
            const std::wstring_view& from_path
        );

        void get_file_stem(
            Result<std::wstring>& result,
            const std::wstring_view& from_path
        );

        void get_entity_paths(
            Result<std::vector<std::wstring>>& result,
            const std::wstring_view& from_path,
            const bool& is_recursive
        );

        void get_file_paths(
            Result<std::vector<std::wstring>>& result,
            const std::wstring_view& from_path,
            const bool& is_recursive
        );

        void get_folder_paths(
            Result<std::vector<std::wstring>>& result,
            const std::wstring_view& from_path,
            const bool& is_recursive
        );

        void is_path_found(
            Result<bool>& result,
            const std::wstring_view& from_path
        );

        void is_entity(
            Result<bool>& result,
            const std::wstring_view& from_path
        );

        void is_file(
            Result<bool>& result,
            const std::wstring_view& from_path
        );

        void is_folder(
            Result<bool>& result,
            const std::wstring_view& from_path
        );

        void is_entity_user_permission_level_valid(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const std::filesystem::perms& permission_level
        );

        void find_files_by_pattern(
            Result<std::vector<std::wstring>>& result,
            const std::wstring_view& from_path,
            const std::wstring_view& pattern,
            const bool& is_recursive
        );

        void set_entity_read_status(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const bool& value
        );

        void set_entity_write_status(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const bool& value
        );

        void set_entity_visibility(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const bool& value
        );

        void create_folder(
            Result<bool>& result,
            const std::wstring_view& from_path
        );

        void copy_file(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const std::wstring_view& to_path
        );

        void copy_folder(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const std::wstring_view& to_path,
            const bool& is_recursive
        );

        void move_entity(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const std::wstring_view& to_path
        );

        void move_file(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const std::wstring_view& to_path
        );

        void move_folder(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const std::wstring_view& to_path
        );

        void rename_entity(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const std::wstring_view& name
        );

        void rename_file(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const std::wstring_view& name
        );

        void rename_folder(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const std::wstring_view& name
        );

        void remove_file(
            Result<bool>& result,
            const std::wstring_view& from_path
        );

        void remove_folder(
            Result<bool>& result,
            const std::wstring_view& from_path
        );

        void remove_folder_sub_files(
            Result<bool>& result,
            const std::wstring_view& from_path,
            const bool& is_recursive
        );
    };

    inline static FileSystemManager& FILE_SYSTEM_MANAGER =
        INSTANCE_MANAGER.get_instance<FileSystemManager>();
}


/*
void get_entity_last_modified_time(
    Result<std::filesystem::file_time_type>& result,
    const std::string_view& from_path
);

void get_entity_creation_time(
    Result<std::filesystem::file_time_type>& result,
    const std::string_view& from_path
);

void get_entity_last_access_time(
    Result<std::filesystem::file_time_type>& result,
    const std::string_view& from_path
);
*/

/*
void get_entity_last_modified_time(
    Result<std::filesystem::file_time_type>& result,
    const std::wstring_view& from_path
);

void get_entity_creation_time(
    Result<std::filesystem::file_time_type>& result,
    const std::wstring_view& from_path
);

void get_entity_last_access_time(
    Result<std::filesystem::file_time_type>& result,
    const std::wstring_view& from_path
);
*/
