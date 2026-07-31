#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemManager \
	)

#include "text_manager.hpp"
#include "file_system_entity.hpp"
#include "file_system_manager_configurations.hpp"

#include <Shlwapi.h>

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		FileSystemManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemManagerConfigurations>
    {
    public:       
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

        FileSystemManager();

		~FileSystemManager();

        bool
            construct();

		bool
			destruct();

		std::wstring
			get_executable_folder_wstring_path();

        std::wstring
            get_executable_file_wstring_path();

		std::wstring
			get_executed_folder_wstring_path();

		std::wstring
			get_program_data_folder_wstring_path();

		std::wstring
			get_local_app_data_folder_wstring_path();

		std::wstring
			get_roaming_app_data_folder_wstring_path();

		size_t
			get_line_count( //
				const std::wstring&
					origin_path
			);

		size_t
			get_column_count( //
				const std::wstring&
					origin_path,
				const size_t&
					line_number
			);

		size_t
			get_character_count( //
				const std::wstring&
					origin_path
			);

        size_t
            get_file_byte_size(            
                const std::wstring&
                    origin_path
			);

        size_t
            get_folder_byte_size(            
				const std::wstring&
                    origin_path
			);

        std::wstring
            get_absolute_path(
				const std::wstring&
                    origin_path
			);

        std::wstring
            get_relative_path(
				const std::wstring&
                    origin_path,
				const std::wstring&
                    target_path
			);

        std::wstring
            get_file_extension(
				const std::wstring&
                    origin_path
			);

		std::wstring
            get_file_stem(
                const std::wstring&
                    origin_path
			);

        bool
            is_path_found(
                const std::wstring&
                    origin_path
			);

        bool
            is_entity(
                const std::wstring&
                    origin_path
			);

        bool
            is_file(
                const std::wstring&
                    origin_path
			);

        bool
            is_folder(
                const std::wstring&
                    origin_path
			);

        bool
            is_entity_user_permission_level_valid(
				const std::wstring&
                    origin_path,
                const std::filesystem::perms&
                    permission_level
			);

        bool
            set_entity_read_status(
                const std::wstring&
                    origin_path,
                const bool&
                    value
			);

        bool
            set_entity_write_status(
				const std::wstring&
                    origin_path,
                const bool&
                    value
			);

        bool
            set_entity_visibility(
				const std::wstring&
                    origin_path,
                const bool&
                    value
			);

        bool
            create_folder(
				const std::wstring&
                    origin_path
			);

        bool
            copy_file(
                const std::wstring&
                    origin_path,
                const std::wstring&
                    target_path
			);

        bool
            copy_folder(
                const std::wstring&
                    origin_path,
                const std::wstring&
                    target_path
			);

        bool
            move_entity(
                const std::wstring&
                    origin_path,
                const std::wstring&
                    target_path
			);

        bool
            move_file(
                const std::wstring&
                    origin_path,
                const std::wstring&
                    target_path
			);

        bool
            move_folder(
                const std::wstring&
                    origin_path,
                const std::wstring&
                    target_path
			);

        bool
            rename_entity(
                const std::wstring&
                    origin_path,
                const std::wstring&
                    name
			);

        bool
            rename_file(
                const std::wstring&
                    origin_path,
                const std::wstring&
                    name
			);

        bool
            rename_folder(
                const std::wstring&
                    origin_path,
                const std::wstring&
                    name
			);

        bool
            remove_file(
				const std::wstring
                    origin_path
			);

        bool
            remove_folder(
				const std::wstring
                    origin_path
			);

        bool
            remove_folder_sub_files(
				const std::wstring
                    origin_path
			);

		std::string
			get_executable_folder_path();

        std::string
			get_executable_file_path();

		std::string
			get_executed_folder_path();

		std::string
			get_program_data_folder_path();

		std::string
			get_local_app_data_folder_path();

		std::string
			get_roaming_app_data_folder_path();

		size_t
			get_line_count( //
				const std::string&
					origin_path
			);

		size_t
			get_column_count( //
				const std::string&
					origin_path,
				const size_t&
					line_number
			);

		size_t
			get_character_count( //
				const std::string&
					origin_path
			);

        size_t
            get_file_byte_size(            
                const std::string&
                    origin_path
			);

        size_t
            get_folder_byte_size(            
                const std::string&
                    origin_path
			);

        std::string
            get_absolute_path(
                const std::string&
                    origin_path
			);

        std::string
            get_relative_path(
                const std::string&
                    origin_path,
                const std::string&
                    target_path
			);

        std::string
            get_file_extension(
                const std::string&
                    origin_path
			);

        std::string
            get_file_stem(
                const std::string&
                    origin_path
			);

        bool
            is_path_found(
                const std::string&
                    origin_path
			);

        bool
            is_entity(
                const std::string&
                    origin_path
			);

        bool
            is_file(
                const std::string&
                    origin_path
			);

        bool
            is_folder(
                const std::string&
                    origin_path
			);

        bool
            is_entity_user_permission_level_valid(
                const std::string&
                    origin_path,
                const std::filesystem::perms&
                    permission_level
			);

        bool
            set_entity_read_status(
                const std::string&
                    origin_path,
                const bool&
                    value
			);

        bool
            set_entity_write_status(
                const std::string&
                    origin_path,
                const bool&
                    value
			);

        bool
            set_entity_visibility(
                const std::string&
                    origin_path,
                const bool&
                    value
			);

        bool
            create_folder(
                const std::string&
                    origin_path
			);

        bool
            copy_file(
                const std::string&
                    origin_path,
                const std::string&
                    target_path
			);

        bool
            copy_folder(
                const std::string&
                    origin_path,
                const std::string&
                    target_path
			);

        bool
            move_entity(
                const std::string&
                    origin_path,
                const std::string&
                    target_path
			);

        bool
            move_file(
                const std::string&
                    origin_path,
                const std::string&
                    target_path
			);

        bool
            move_folder(
                const std::string&
                    origin_path,
                const std::string&
                    target_path
			);

        bool
            rename_entity(
                const std::string&
                    origin_path,
                const std::string&
                    name
			);

        bool
            rename_file(
                const std::string&
                    origin_path,
                const std::string&
                    name
			);

        bool
            rename_folder(
                const std::string&
                    origin_path,
                const std::string&
                    name
			);

        bool
            remove_file(
                const std::string&
                    origin_path
			);

        bool
            remove_folder(
                const std::string&
                    origin_path
			);

        bool
            remove_folder_sub_files(
                const std::string&
                    origin_path
			);   

		std::vector<std::filesystem::path>
			enumerate(
				const std::filesystem::path&
					origin_path,
				const std::function<bool()>&
					pattern,
				const bool&
					include_files,
				const bool&
					include_folders
        );

		std::vector<std::wstring>	
			get_entity_paths(
				const std::wstring&
					origin_path,
				const std::function<bool()>&
					pattern
			);

		std::vector<std::wstring>
			get_file_paths(
				const std::wstring&
					origin_path,
				const std::function<bool()>&
					pattern
			);

		std::vector<std::wstring>
			get_folder_paths(
				const std::wstring&
					origin_path,
				const std::function<bool()>&
					pattern
			);

		std::vector<std::wstring>	
			get_entity_paths(
				const std::wstring&
					origin_path
			);

		std::vector<std::wstring>
			get_file_paths(
				const std::wstring&
					origin_path
			);

		std::vector<std::wstring>
			get_folder_paths(
				const std::wstring&
					origin_path
			);

		std::vector<std::string>	
			get_entity_paths(
				const std::string&
					origin_path,
				const std::function<bool()>&
					pattern
			);

		std::vector<std::string>
			get_file_paths(
				const std::string&
					origin_path,
				const std::function<bool()>&
					pattern
			);

		std::vector<std::string>
			get_folder_paths(
				const std::string&
					origin_path,
				const std::function<bool()>&
					pattern
			);

		std::vector<std::string>	
			get_entity_paths(
				const std::string&
					origin_path
			);

		std::vector<std::string>
			get_file_paths(
				const std::string&
					origin_path
			);

		std::vector<std::string>
			get_folder_paths(
				const std::string&
					origin_path
			);

		// Additional Unit Testing Required
		bool
			clear_file_text(
				const std::wstring&
					file_path
			);

		bool
			clear_file_text(
				const std::string&
					file_path
			);
    };
}

#endif
