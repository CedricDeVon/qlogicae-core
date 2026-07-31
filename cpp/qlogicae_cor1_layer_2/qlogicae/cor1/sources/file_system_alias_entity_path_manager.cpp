#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemAliasEntityPathManager \
	)

#include "../includes/file_system_alias_entity_path_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{    
	FileSystemAliasEntityPathManager
		::FileSystemAliasEntityPathManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemAliasEntityPathManagerConfigurations>()
    {
        construct();
    }

    FileSystemAliasEntityPathManager
		::~FileSystemAliasEntityPathManager()
    {
        destruct();
    }

    bool
        FileSystemAliasEntityPathManager
			::construct()
    {
        try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);
		
			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

    bool
        FileSystemAliasEntityPathManager
			::destruct()
    {
        try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

    std::wstring
		FileSystemAliasEntityPathManager
			::get_static_entity_path(
				const std::wstring&
					alias
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				alias.empty() ||
				!alias_entity_paths.contains(alias)
			);

			return
				alias_entity_paths.at(alias);
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	bool
		FileSystemAliasEntityPathManager
			::set_static_entity_path(
				const std::wstring&
					alias,
				const std::wstring&
					target_entity_file_path
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				alias.empty() ||
				target_entity_file_path.empty()
			);

			alias_entity_paths[alias] =
				target_entity_file_path;

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	std::wstring
		FileSystemAliasEntityPathManager
			::get_dynamic_entity_path(
				const std::wstring&
					alias
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				alias.empty() ||
				!alias_entity_paths.contains(alias)
			);

			const std::wstring
				target_entity_file_path =
					alias_entity_paths.at(alias);

			const std::filesystem::path
				entity_path =
					target_entity_file_path;

			const std::wstring
				target_filename =
					entity_path
						.filename()
						.wstring();

			const std::wstring
				target_folder_path =
					entity_path
						.parent_path()
						.wstring();

			if
			(
				target_filename.empty() ||
				target_folder_path.empty()
			)
			{
				return
					L"";
			}

			std::function<std::wstring(const std::wstring&)>
				search_directory;

			search_directory =
				[
					&,
					this
				]
				(
					const std::wstring&
						current_folder_path
				)
				-> std::wstring
				{
					const std::wstring
						search_pattern =
							current_folder_path +
							L"\\*";

					WIN32_FIND_DATAW
						find_file_data;

					const HANDLE
						find_handle =
							FindFirstFileW(
								search_pattern.c_str(),
								&find_file_data
							);

					if
					(
						find_handle ==
						INVALID_HANDLE_VALUE
					)
					{
						return
							L"";
					}

					do
					{
						const std::wstring
							current_name =
								find_file_data
									.cFileName;

						if
						(
							current_name == L"." ||
							current_name == L".."
						)
						{
							continue;
						}

						const std::wstring
							current_path =
								current_folder_path +
								L"\\" +
								current_name;

						const bool
							is_directory =
								(
									find_file_data
										.dwFileAttributes &
									FILE_ATTRIBUTE_DIRECTORY
								) != 0;

						if
						(
							!is_directory &&
							current_name ==
							target_filename
						)
						{
							FindClose(
								find_handle
							);

							return
								current_path;
						}

						if
						(
							is_directory &&
							configurations
								.is_recursive_search_enabled
						)
						{
							const std::wstring
								result =
									search_directory(
										current_path
									);

							if
							(
								!result.empty()
							)
							{
								FindClose(
									find_handle
								);

								return
									result;
							}
						}
					}
					while
					(
						FindNextFileW(
							find_handle,
							&find_file_data
						)
					);

					FindClose(
						find_handle
					);

					return
						L"";
				};

			return
				search_directory(
					target_folder_path
				);
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	bool
		FileSystemAliasEntityPathManager
			::set_dynamic_entity_path(
				const std::wstring&
					alias,
				const std::wstring&
					target_entity_file_path,
				const std::wstring&
					target_folder_path
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				alias.empty() ||
				target_entity_file_path.empty() ||
				target_folder_path.empty()
			);

			const DWORD
				folder_attributes =
					GetFileAttributesW(
						target_folder_path
							.c_str()
					);

			if
			(
				folder_attributes ==
				INVALID_FILE_ATTRIBUTES ||
				!(
					folder_attributes &
					FILE_ATTRIBUTE_DIRECTORY
				)
			)
			{
				return
					false;
			}

			const std::filesystem::path
				entity_path =
					target_entity_file_path;

			const std::wstring
				normalized_entity_path =
					(
						std::filesystem::path(
							target_folder_path
						) /
						entity_path
							.filename()
					)
					.wstring();

			alias_entity_paths[alias] =
				normalized_entity_path;

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	bool
		FileSystemAliasEntityPathManager
			::remove_entity_path(
				const std::wstring&
					alias
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				alias.empty() ||
				!alias_entity_paths.contains(alias)
			);

			alias_entity_paths.erase(
				alias
			);

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	
	bool
		FileSystemAliasEntityPathManager
			::is_alias_found(
				const std::wstring&
					alias
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				alias.empty()
			);

			return
				alias_entity_paths.contains(alias);
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	std::string
		FileSystemAliasEntityPathManager
			::get_static_entity_path(
				const std::string&
					alias
			)
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_static_entity_path(
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::string, std::wstring>(
								alias
							)
					)
				);
	}

	std::string
		FileSystemAliasEntityPathManager
			::get_dynamic_entity_path(
				const std::string&
					alias
			)
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_dynamic_entity_path(
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::string, std::wstring>(
								alias
							)
					)
				);
	}

	bool
		FileSystemAliasEntityPathManager
			::set_static_entity_path(
				const std::string&
					alias,
				const std::string&
					target_entity_file_path
			)
	{
		return
			set_static_entity_path(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						alias
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						target_entity_file_path
					)
			);
	}

	bool
		FileSystemAliasEntityPathManager
			::set_dynamic_entity_path(
				const std::string&
					alias,
				const std::string&
					target_entity_file_path,
				const std::string&
					target_folder_path
			)
	{
		return
			set_dynamic_entity_path(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						alias
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						target_entity_file_path
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						target_folder_path
					)
			);
	}

	bool
		FileSystemAliasEntityPathManager
			::remove_entity_path(
				const std::string&
					alias
			)
	{
		return
			remove_entity_path(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						alias
					)
			);
	}

	bool
		FileSystemAliasEntityPathManager
			::is_alias_found(
				const std::string&
					alias
			)
	{
		return
			is_alias_found(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						alias
					)
			);
	}
}

#endif
