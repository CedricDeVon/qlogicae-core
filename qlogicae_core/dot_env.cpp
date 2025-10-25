#include "pch.hpp"

#include "dot_env.hpp"
#include "encoder.hpp"

namespace QLogicaeCore
{
	DotEnv::DotEnv()
	{

	}

	DotEnv::~DotEnv()
	{

	}

	bool DotEnv::setup()
	{
		try
		{
			Result<void> result;

			setup(result);

			return result.is_status_safe();
		}
		catch (const std::exception& exception)
		{

		}
	}

	void DotEnv::setup(
		Result<void>& result
	)
	{
		result.set_to_good_status_without_value();
	}

	std::future<bool> DotEnv::setup_async()
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this,
			promise = std::move(promise)]() mutable
			{
				promise.set_value(
					setup()
				);
			}
		);

		return future;
	}

	void DotEnv::setup_async(
		const std::function<void(const bool& result)>& callback
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback]() mutable
			{
				callback(
					setup()
				);
			}
		);
	}

	void DotEnv::setup_async(
		Result<std::future<void>>& result
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this,
			promise = std::move(promise)]() mutable
			{
				Result<void> result;

				setup(result);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void DotEnv::setup_async(
		const std::function<void(Result<void>& result)>& callback
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback]() mutable
			{
				Result<void> result;

				setup(result);

				callback(
					result
				);
			}
		);
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
			throw std::runtime_error(
				std::string() +
				"Exception at DotEnv::set(): " +
				exception.what()
			);
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
			throw std::runtime_error(
				std::string() +
				"Exception at DotEnv::remove(): " +
				exception.what()
			);
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
			throw std::runtime_error(
				std::string() +
				"Exception at DotEnv::get(): " +
				exception.what()
			);
		}
	}

	void DotEnv::remove(Result<bool>& result, const wchar_t* key)
	{
		if (key == nullptr ||
			key[0] == L'\0')
		{			
			return result.set_to_bad_status_without_value(
				"Empty key"
			);
		}

		result.set_to_good_status_with_value(
			SetEnvironmentVariableW(key, nullptr) != 0
		);
	}

	void DotEnv::set(
		Result<bool>& result,
		const wchar_t* key,
		const wchar_t* value
	)
	{
		if (key == nullptr ||
			key[0] == L'\0' ||
			value == nullptr)
		{
			return result.set_to_bad_status_without_value(
				"Empty key and value"
			);
		}

		result.set_to_good_status_with_value(
			SetEnvironmentVariableW(key, value) != 0
		);
	}

	void DotEnv::get(
		Result<std::wstring>& result,
		const wchar_t* key
	)
	{
		if (key == nullptr || key[0] == L'\0')
		{
			return result.set_to_bad_status_without_value(
				"Empty key"
			);
		}

		DWORD size = GetEnvironmentVariableW(key, nullptr, 0);
		if (size == 0)
		{
			if (GetLastError() == ERROR_ENVVAR_NOT_FOUND)
			{
				return result.set_to_bad_status_without_value(
					"Environment variable not found"
				);
			}

			return result.set_to_bad_status_without_value(
				"Environment variable not found"
			);
		}

		std::wstring content(size - 1, L'\0');
		if (GetEnvironmentVariableW(key, &content[0], size) == 0)
		{
			return result.set_to_bad_status_without_value(
				"Environment variable not found"
			);
		}

		result.set_to_good_status_with_value(

			content);
	}

	DotEnv& DotEnv::get_instance()
	{
		static DotEnv singleton;

		return singleton;
	}

	void DotEnv::get_instance(
		Result<DotEnv*>& result
	)
	{
		static DotEnv singleton;

		result.set_to_good_status_with_value(
			&singleton
		);
	}
}
