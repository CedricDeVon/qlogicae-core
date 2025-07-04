#pragma once

#include "pch.h"

#include "dot_env.hpp"
#include "encoder.hpp"

namespace QLogicaeCore
{
	bool DotEnv::set(const wchar_t* key, const wchar_t* value)
	{
		try
		{
			if (key == nullptr || value == nullptr)
			{
				return false;
			}

			return SetEnvironmentVariableW(key, value) != 0;
		}
		catch (...)
		{
			return false;
		}
	}

	bool DotEnv::remove(const wchar_t* key)
	{
		try
		{
			if (key == nullptr)
			{
				return false;
			}

			return SetEnvironmentVariableW(key, nullptr) != 0;
		}
		catch (...)
		{
			return false;
		}
	}

	std::optional<std::wstring> DotEnv::get(const wchar_t* key)
	{
		try
		{
			if (key == nullptr)
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
		catch (...)
		{
			return L"";
		}
	}

	DotEnv& DotEnv::instance()
	{
		static DotEnv singleton;

		return singleton;
	}

	DotEnv::DotEnv()
	{

	}
}
