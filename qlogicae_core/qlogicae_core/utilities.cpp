#include "pch.hpp"

#include "utilities.hpp"

namespace QLogicaeCore
{
    Utilities::Utilities() :
		BOOST_ASIO_POOL(std::thread::hardware_concurrency())
    {
		FULL_EXECUTABLE_FOLDER_PATH =
			SYSTEM_ACCESS.get_executable_folder();

		FULL_EXECUTED_FOLDER_PATH =
			SYSTEM_ACCESS.get_executed_folder();

		FULL_ROAMING_APPDATA_FOLDER_PATH =
			SYSTEM_ACCESS.get_roaming_appdata_folder_path();

		FULL_LOCAL_APPDATA_FOLDER_PATH =
			SYSTEM_ACCESS.get_local_appdata_folder_path();

		FULL_PROGRAMDATA_FOLDER_PATH =
			SYSTEM_ACCESS.get_programdata_folder_path();

		FULL_APPLICATION_QLOGICAE_FOLDER_PATH =
			FULL_EXECUTABLE_FOLDER_PATH;

		FULL_APPLICATION_QLOGICAE_PRIVATE_FOLDER_PATH =
			FULL_APPLICATION_QLOGICAE_FOLDER_PATH +
			"\\" + RELATIVE_DOT_QLOGICAE_FOLDER_PATH_1;

		FULL_APPLICATION_QLOGICAE_PUBLIC_FOLDER_PATH =
			FULL_APPLICATION_QLOGICAE_FOLDER_PATH +
			"\\" + RELATIVE_QLOGICAE_FOLDER_PATH_1;

		FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_FOLDER_PATH =
			FULL_APPLICATION_QLOGICAE_PUBLIC_FOLDER_PATH +
			"\\" + RELATIVE_APPLICATION_FOLDER_PATH;

		FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_FOLDER_PATH =
			FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_FOLDER_PATH +
			"\\" + RELATIVE_CONFIGURATIONS_FOLDER_PATH;

		FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_QLOGICAE_FILE_PATH =
			FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_FOLDER_PATH +
			"\\" + RELATIVE_QLOGICAE_FILE_PATH;

		FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_ENVIRONMENT_FILE_PATH =
			FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_FOLDER_PATH +
			"\\" + RELATIVE_ENVIRONMENT_FILE_PATH;

		FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_ASSETS_FOLDER_PATH =
			FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_FOLDER_PATH +
			"\\" + RELATIVE_ASSETS_FOLDER_PATH;

		FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_ASSETS_APPLICATION_ICON_FILE_PATH =
			FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_ASSETS_FOLDER_PATH +
			"\\" + RELATIVE_APPLICATION_ICON_FILE_PATH;

		FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_DOCUMENTATION_FOLDER_PATH =
			FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_FOLDER_PATH +
			"\\" + RELATIVE_DOCUMENTATION_FOLDER_PATH;

		FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_DOCUMENTATION_LICENSE_FILE_PATH =
			FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_DOCUMENTATION_FOLDER_PATH +
			"\\" + RELATIVE_LICENSE_FILE_PATH;
    }

	Utilities::~Utilities()
	{
		
	}

    bool Utilities::setup()
    {
		try
		{
			Result<void> result;

			setup(result);

			return result.is_status_safe();
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("Utilities::setup()") + exception.what()
			);
		}
    }

    void Utilities::setup(
        Result<void>& result
    )
    {        
		result.set_to_good_status_without_value();
    }

    std::future<bool> Utilities::setup_async(
		const std::function<void(const bool& value)>& callback
	)
    {
		std::promise<bool> promise;
		auto future = promise.get_future();
		
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, promise = std::move(promise)]() mutable
			{				
				bool value = setup();

				promise.set_value(
					value
				);

				if (callback)
				{
					callback(
						value
					);
				}
			}
		);

		return future;
    }

    void Utilities::setup_async(
        Result<std::future<void>>& result,
		const std::function<void(Result<void>& result)>& callback
    )
    {
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, promise = std::move(promise)]() mutable
			{
				Result<void> result;

				setup(result);

				promise.set_value();

				callback(
					result
				);
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
    }

	const char* Utilities::get_format_string(
		const TimeFormat& format
	)
	{
		try
		{
			Result<const char*> result;

			get_format_string(
				result,
				format			
			);

			return result.get_value();
		}
		catch (const std::exception& exception)
		{			
			throw std::runtime_error(
				std::string("Utilities::get_format_string()") + exception.what()
			);
		}
	}

	void Utilities::get_format_string(
		Result<const char*>& result,
		const TimeFormat& format
	)
	{
		switch (format)
		{
			case TimeFormat::ISO8601:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_ISO_8601);
				break;
			}
			case TimeFormat::FULL_TIMESTAMP:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_FULL_TIMESTAMP);
				break;
			}
			case TimeFormat::FULL_DASHED_TIMESTAMP:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_FULL_DASHED_TIMESTAMP);
				break;
			}
			case TimeFormat::HOUR_12:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_HOUR_12);
				break;
			}
			case TimeFormat::HOUR_24:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_HOUR_24);
				break;
			}
			case TimeFormat::DATE_DASHED:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_DATE_DASHED);
				break;
			}
			case TimeFormat::DATE_MDY_SLASHED:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_DATE_MDY_SLASHED);
				break;
			}
			case TimeFormat::DATE_DMY_SLASHED:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_DATE_DMY_SLASHED);
				break;
			}
			case TimeFormat::DATE_DMY_SPACED:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_DATE_DMY_SPACED);
				break;
			}
			case TimeFormat::DATE_VERBOSE:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_DATE_VERBOSE);
				break;
			}
			default:
			{
				result.set_to_good_status_with_value(UTILITIES.TIME_FORMAT_DATE_VERBOSE);
				break;
			}
		}
	}

    Utilities& Utilities::get_instance()
    {
        static Utilities instance;

        return instance;
    }

	void Utilities::get_instance(
		Result<Utilities*>& result
	)
	{
		static Utilities instance;

		result.set_to_good_status_with_value(
			&instance
		);
	}
}
