#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemAliasEntityPathManager \
	)

#include "text_manager.hpp"
#include "file_system_alias_entity_path_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		FileSystemAliasEntityPathManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemAliasEntityPathManagerConfigurations>
    {
    public:		
		std::unordered_map<std::wstring, std::wstring>
			alias_entity_paths;

		FileSystemAliasEntityPathManager();

		~FileSystemAliasEntityPathManager();

		bool
			construct();

		bool
			destruct();

		std::wstring
			get_static_entity_path(
				const std::wstring&
					alias
			);

		std::wstring
			get_dynamic_entity_path(
				const std::wstring&
					alias
			);

		bool
			set_static_entity_path(
				const std::wstring&
					alias,
				const std::wstring&
					target_entity_file_path
			);

		bool
			set_dynamic_entity_path(
				const std::wstring&
					alias,
				const std::wstring&
					target_entity_file_path,
				const std::wstring&
					target_folder_path
			);

		bool
			remove_entity_path(
				const std::wstring&
					alias
			);
		
		bool
			is_alias_found(
				const std::wstring&
					alias
			);

		std::string
			get_static_entity_path(
				const std::string&
					alias
			);

		std::string
			get_dynamic_entity_path(
				const std::string&
					alias
			);

		bool
			set_static_entity_path(
				const std::string&
					alias,
				const std::string&
					target_entity_file_path
			);

		bool
			set_dynamic_entity_path(
				const std::string&
					alias,
				const std::string&
					target_entity_file_path,
				const std::string&
					target_folder_path
			);

		bool
			remove_entity_path(
				const std::string&
					alias
			);

		bool
			is_alias_found(
				const std::string&
					alias
			);
	};
}

#endif
