#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsEnvironmentVariableManager \
	)

#include "../includes/windows_environment_variable_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{	
    WindowsEnvironmentVariableManager
		::WindowsEnvironmentVariableManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<WindowsEnvironmentVariableManagerConfigurations>()
	{
			
	}

	std::wstring
		WindowsEnvironmentVariableManager
			::get_value(
				const std::wstring&
					key
			)
	{
		try
        {				
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				key.empty()
			);

			DWORD size = GetEnvironmentVariableW(key.c_str(), nullptr, 0);
			if (size == 0)
			{
				return L"";
			}

			std::wstring result(size - 1, L'\0');
			if (GetEnvironmentVariableW(key.c_str(), &result[0], size) == 0)
			{
				return L"";
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
		WindowsEnvironmentVariableManager
			::set_value(
				const std::wstring&
					key,
				const std::wstring&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				key.empty() ||
				value.empty()
			);			

			return
				SetEnvironmentVariableW(
					key.c_str(),
					value.c_str()
				) != 0;
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
		WindowsEnvironmentVariableManager
			::remove_value(
				const std::wstring&
					key
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				key.empty()
			);		

			return
				SetEnvironmentVariableW(
					key.c_str(),
					nullptr
				) != 0;
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
		WindowsEnvironmentVariableManager
			::get_value(
				const std::string&
					key
			)
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>().convert_text<std::wstring, std::string>(
				get_value(
					QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>().convert_text<std::string, std::wstring>(
						key
					)
				)
			);
	}

	bool
		WindowsEnvironmentVariableManager
			::set_value(
				const std::string&
					key,
				const std::string&
					value
			)
	{
		return
			set_value(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>().convert_text<std::string, std::wstring>(
					key
				),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>().convert_text<std::string, std::wstring>(
					value
				)
			);
	}

	bool
		WindowsEnvironmentVariableManager
			::remove_value(
				const std::string&
					key
			)
	{
		return
			remove_value(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>().convert_text<std::string, std::wstring>(
					key
				)
			);
	}
}

#endif
