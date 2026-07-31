#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsRegistryManager \
	)

#include "../includes/windows_registry_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    WindowsRegistryManager
		::WindowsRegistryManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<WindowsRegistryManagerConfigurations>()
	{
				
	}

	std::wstring
		WindowsRegistryManager
			::get_value(
				const HKEY&
					root_key,
				const std::wstring&
					sub_key,
				const std::wstring&
					name_key
			)
	{
		try
        {						
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				sub_key.empty() ||
				name_key.empty()
			);

			HKEY hKey = nullptr;
			if (RegOpenKeyExW(root_key, sub_key.c_str(), 0, KEY_READ, &hKey)
				!= ERROR_SUCCESS)
				return L"";

			std::unique_ptr<std::remove_pointer<HKEY>::type, RegularKeyDeleteHandler>
				key_ptr(hKey);

			DWORD type = 0, size = 0;
			if (RegQueryValueExW(hKey, name_key.c_str(), nullptr, &type, nullptr, &size)
				!= ERROR_SUCCESS || type != REG_SZ)
				return L"";

			std::vector<wchar_t> buffer(size / sizeof(wchar_t));
			if (RegQueryValueExW(hKey, name_key.c_str(), nullptr, &type,
				reinterpret_cast<BYTE*>(buffer.data()), &size) != ERROR_SUCCESS)
				return L"";

			if (!buffer.empty() && buffer.back() == L'\0') buffer.pop_back();
			return std::wstring(buffer.data(), buffer.size());
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
		WindowsRegistryManager
			::set_value(
				const HKEY&
					root_key,
				const std::wstring&
					sub_key,
				const std::wstring&
					name_key,
				const std::wstring&
					value
		)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				sub_key.empty() ||
				name_key.empty() ||
				value.empty()
			);
			
			HKEY hKey = nullptr;
			if (RegCreateKeyExW(root_key, sub_key.c_str(), 0, nullptr, 0,
				KEY_WRITE, nullptr, &hKey, nullptr) != ERROR_SUCCESS)
				return false;

			std::unique_ptr<std::remove_pointer<HKEY>::type, RegularKeyDeleteHandler>
				key_ptr(hKey);

			return RegSetValueExW(hKey, name_key.c_str(), 0, REG_SZ,
				reinterpret_cast<const BYTE*>(value.c_str()),
				static_cast<DWORD>((value.size() + 1) * sizeof(wchar_t))) == ERROR_SUCCESS;
		}
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::unordered_map<std::wstring, std::wstring>
		WindowsRegistryManager
			::get_values(
				const HKEY&
					root_key,
				const std::wstring&
					sub_key
			)
	{
		try
        {							
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				sub_key.empty()
			);
	
			std::unordered_map<std::wstring, std::wstring> result;
			HKEY hKey = nullptr;
			if (RegOpenKeyExW(root_key, sub_key.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
				return result;

			std::unique_ptr<std::remove_pointer<HKEY>::type, ValueEnumKeyDeleteHandler>
				key_ptr(hKey);

			DWORD index = 0;
			while (true)
			{
				wchar_t name[32767] = {};
				DWORD name_len = 32767;
				DWORD type = 0;
				BYTE data[65535] = {};
				DWORD data_len = 65535;

				LONG ret = RegEnumValueW(hKey, index++, name, &name_len, nullptr, &type, data, &data_len);
				if (ret == ERROR_NO_MORE_ITEMS) break;

				if (ret == ERROR_SUCCESS && type == REG_SZ)
				{
					std::wstring key_name(name, name_len);
					std::wstring key_value(reinterpret_cast<wchar_t*>(data), data_len / sizeof(wchar_t));
					if (!key_value.empty() && key_value.back() == L'\0') key_value.pop_back();
					result.emplace(key_name, key_value);
				}
			}

			return result;
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
		WindowsRegistryManager
			::remove_value(
				const HKEY&
					root_key,
				const std::wstring&
					sub_key,
				const std::wstring&
					name_key
			)
	{
		try
        {								
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				sub_key.empty() ||
				name_key.empty()
			);

			HKEY hKey = nullptr;
			if (RegOpenKeyExW(root_key, sub_key.c_str(), 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS)
				return false;

			std::unique_ptr<std::remove_pointer<HKEY>::type, RegularKeyDeleteHandler>
				key_ptr(hKey);

			return RegDeleteValueW(hKey, name_key.c_str()) == ERROR_SUCCESS;
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
		WindowsRegistryManager
			::is_path_found(
				const HKEY&
					root_key,
				const std::wstring&
					sub_key,
				const std::wstring&
					name_key
			)
	{
		return
			!get_value(
				root_key,
				sub_key,
				name_key
			).empty();
	}

	std::string
		WindowsRegistryManager
			::get_value(
				const HKEY&
					root_key,
				const std::string&
					sub_key,
				const std::string&
					name_key
			)
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_value(
						root_key,
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::string, std::wstring>(
								sub_key
							),
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::string, std::wstring>(
								name_key
							)					
					)
				);
	}

	bool
		WindowsRegistryManager
			::set_value(
				const HKEY&
					root_key,
				const std::string&
					sub_key,
				const std::string&
					name_key,
				const std::string&
					value
		)
	{
		return
			set_value(
				root_key,
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						sub_key
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						name_key
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						value
					)					
			);
	}

	std::unordered_map<std::string, std::string>
		WindowsRegistryManager
			::get_values(
				const HKEY&
					root_key,
				const std::string&
					sub_key
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				sub_key.empty()
			);

			std::unordered_map<std::string, std::string> result;
			std::wstring wstring_sub_key =
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						sub_key
					);

			HKEY raw_key = nullptr;
			if (RegOpenKeyExW(root_key, wstring_sub_key.data(), 0, KEY_READ, &raw_key) != ERROR_SUCCESS)
			{
				return result;
			}

			std::unique_ptr<std::remove_pointer<HKEY>::type, ValueEnumKeyDeleteHandler> hkey(raw_key);

			DWORD index = 0;
			wchar_t value_name[32767] = { 0 };
			DWORD value_name_size = 32767;
			DWORD value_type = 0;
			BYTE value_data[65535] = { 0 };
			DWORD value_data_size = 65535;

			while (true)
			{
				value_name_size = 32767;
				value_data_size = 65535;

				LONG enum_result = RegEnumValueW(
					hkey.get(),
					index++,
					value_name,
					&value_name_size,
					nullptr,
					&value_type,
					value_data,
					&value_data_size);

				if (enum_result == ERROR_NO_MORE_ITEMS)
				{
					break;
				}

				if (enum_result == ERROR_SUCCESS && value_type == REG_SZ)
				{
					std::wstring name(value_name, value_name_size);
					std::wstring value(reinterpret_cast<wchar_t*>(value_data));
					result.emplace(
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::wstring, std::string>(
								name
							),
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::wstring, std::string>(
								value
							)						
					);
				}
			}

			return
				result;
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
		WindowsRegistryManager
			::remove_value(
				const HKEY&
					root_key,
				const std::string&
					sub_key,
				const std::string&
					name_key
			)
	{
		return
			remove_value(
				root_key,
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						sub_key
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						name_key
					)			
			);
	}

	bool
		WindowsRegistryManager
			::is_path_found(
				const HKEY&
					root_key,
				const std::string&
					sub_key,
				const std::string&
					name_key
			)
	{
		return
			is_path_found(
				root_key,
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						sub_key
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						name_key
					)					
			);
	}

	std::wstring
		WindowsRegistryManager
			::get_value_via_wstring()
	{
		return
			get_value(
				configurations
					.root_key,
				configurations
					.sub_key,
				configurations
					.name_key
			);
	}

	bool
		WindowsRegistryManager
			::set_value_via_wstring(
				const std::wstring&
					value
		)
	{
		return
			set_value(
				configurations
					.root_key,
				configurations
					.sub_key,
				configurations
					.name_key,
				value
			);
	}

	std::unordered_map<std::wstring, std::wstring>
		WindowsRegistryManager
			::get_values_via_wstring()
	{
		return
			get_values(
				configurations
					.root_key,
				configurations
					.sub_key
			);
	}

	bool
		WindowsRegistryManager
			::remove_value_via_wstring()
	{
		return
			remove_value(
				configurations
					.root_key,
				configurations
					.sub_key,
				configurations
					.name_key
			);
	}

	bool
		WindowsRegistryManager
			::is_path_found_via_wstring()
	{
		return
			is_path_found(
				configurations
					.root_key,
				configurations
					.sub_key,
				configurations
					.name_key
			);
	}



	std::string
		WindowsRegistryManager
			::get_value_via_string()
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_value(
						configurations
				.root_key,
						configurations
				.sub_key,
						configurations
				.name_key
					)
				);
	}

	bool
		WindowsRegistryManager
			::set_value_via_string(
				const std::string&
					value
		)
	{
		return
			set_value(
				configurations
					.root_key,
				configurations
					.sub_key,
				configurations
					.name_key,
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						value
					)					
			);
	}

	std::unordered_map<std::string, std::string>
		WindowsRegistryManager
			::get_values_via_string()
	{
		return
			get_values(
				configurations.root_key,
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::wstring, std::string>(
						configurations.sub_key
					)					
			);		
	}

	bool
		WindowsRegistryManager
			::remove_value_via_string()
	{
		return
			remove_value(
				configurations
					.root_key,
				configurations
					.sub_key,
				configurations
					.name_key
			);
	}

	bool
		WindowsRegistryManager
			::is_path_found_via_string()
	{
		return
			is_path_found(
				configurations
					.root_key,
				configurations
					.sub_key,
				configurations
					.name_key
			);
	}
}

#endif
