#include "pch.hpp"

#include "dot_env.hpp"
#include "encoder.hpp"

namespace QLogicaeCore
{
	DotEnv::DotEnv()
	{

	}

	bool DotEnv::set(const wchar_t* key, const wchar_t* value)
	{
		try
		{
			if (key == nullptr ||
				key[0] == L'\0' ||
				value == nullptr)
			{
				return false;
			}

			return SetEnvironmentVariableW(key, value) != 0;
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(std::string() + "Exception at DotEnv::set(): " + exception.what());
		}
	}

	bool DotEnv::remove(const wchar_t* key)
	{
		try
		{
			if (key == nullptr ||
				key[0] == L'\0')
			{
				return false;
			}

			return SetEnvironmentVariableW(key, nullptr) != 0;
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(std::string() + "Exception at DotEnv::remove(): " + exception.what());
		}
	}

	std::optional<std::wstring> DotEnv::get(const wchar_t* key)
	{
		try
		{
			if (key == nullptr || key[0] == L'\0')
			{
				return L"";
			}

			DWORD size = GetEnvironmentVariableW(key, nullptr, 0);
			if (size == 0)
			{
				if (GetLastError() == ERROR_ENVVAR_NOT_FOUND)
				{
					return L"";
				}

				return L"";
			}

			std::wstring result(size - 1, L'\0');
			if (GetEnvironmentVariableW(key, &result[0], size) == 0)
			{
				return L"";
			}

			return result;
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(std::string() + "Exception at DotEnv::get(): " + exception.what());
		}
	}

	DotEnv& DotEnv::get_instance()
	{
		static DotEnv singleton;

		return singleton;
	}

	void DotEnv::remove(Result<bool> result, const wchar_t* key)
	{
		

		if (key == nullptr ||
			key[0] == L'\0')
		{
			result.set_to_failure();
		}

		result.set_is_successful(SetEnvironmentVariableW(key, nullptr) != 0);
	}

	void DotEnv::set(Result<bool> result, const wchar_t* key, const wchar_t* value)
	{
		if (key == nullptr ||
			key[0] == L'\0' ||
			value == nullptr)
		{
			result.set_to_failure();
		}

		result.set_is_successful(SetEnvironmentVariableW(key, value) != 0);
	}

	void DotEnv::get(Result<std::optional<std::wstring>> result, const wchar_t* key)
	{
		if (key == nullptr || key[0] == L'\0')
		{
			result.set_to_failure(L"");
		}

		DWORD size = GetEnvironmentVariableW(key, nullptr, 0);
		if (size == 0)
		{
			if (GetLastError() == ERROR_ENVVAR_NOT_FOUND)
			{
				result.set_to_failure(L"");
			}

			result.set_to_failure(L"");
		}

		std::wstring content(size - 1, L'\0');
		if (GetEnvironmentVariableW(key, &content[0], size) == 0)
		{
			result.set_to_failure(L"");
		}

		result.set_to_success(content);
	}

	void DotEnv::get_instance(Result<DotEnv*> result)
	{
		static DotEnv singleton;

		result.set_to_success(&singleton);
	}
}
