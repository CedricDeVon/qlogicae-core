#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsRegistryManager \
	)

#include "windows_registry_root_path.hpp"
#include "windows_registry_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	class
		WindowsRegistryManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<WindowsRegistryManagerConfigurations>
	{
	public:
		WindowsRegistryManager();

		std::wstring
			get_value(
				const HKEY&
					root_key,
				const std::wstring&
					sub_key,
				const std::wstring&
					name_key
			);

		bool
			set_value(
				const HKEY&
					root_key,
				const std::wstring&
					sub_key,
				const std::wstring&
					name_key,
				const std::wstring&
					value
			);

		std::unordered_map<std::wstring, std::wstring>
			get_values(
				const HKEY&
					root_key,
				const std::wstring&
					sub_key
			);

		bool
			remove_value(
				const HKEY&
					root_key,
				const std::wstring&
					sub_key,
				const std::wstring&
					name_key
			);

		bool
			is_path_found(
				const HKEY&
					root_key,
				const std::wstring&
					sub_key,
				const std::wstring&
					name_key
			);

		std::string
			get_value(
				const HKEY&
					root_key,
				const std::string&
					sub_key,
				const std::string&
					name_key
			);

		bool
			set_value(
				const HKEY&
					root_key,
				const std::string&
					sub_key,
				const std::string&
					name_key,
				const std::string&
					value
			);

		std::unordered_map<std::string, std::string>
			get_values(
				const HKEY&
					root_key,
				const std::string&
					sub_key
			);

		bool
			remove_value(
				const HKEY&
					root_key,
				const std::string&
					sub_key,
				const std::string&
					name_key
			);

		bool
			is_path_found(
				const HKEY&
					root_key,
				const std::string&
					sub_key,
				const std::string&
					name_key
			);

		std::wstring
			get_value_via_wstring();

		bool
			set_value_via_wstring(
				const std::wstring&
					value
			);

		std::unordered_map<std::wstring, std::wstring>
			get_values_via_wstring();

		bool
			remove_value_via_wstring();

		bool
			is_path_found_via_wstring();

		std::string
			get_value_via_string();

		bool
			set_value_via_string(
				const std::string&
					value
			);

		std::unordered_map<std::string, std::string>
			get_values_via_string();

		bool
			remove_value_via_string();

		bool
			is_path_found_via_string();
	};
}

#endif
