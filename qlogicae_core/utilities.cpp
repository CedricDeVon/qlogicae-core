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

    bool Utilities::setup()
    {
		try
		{
			Result<void> void_result;

			setup(void_result);

			return void_result.is_status_safe();
		}
		catch (const std::exception& exception)
		{

		}
    }

    void Utilities::setup(
        Result<void>& result
    )
    {        
		result.set_to_good_status_without_value();
    }

    std::future<bool> Utilities::setup_async()
    {
		std::promise<bool> promise;
		auto future = promise.get_future();
		
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{				
				promise.set_value(
					setup()
				);
			}
		);

		return future;
    }

    void Utilities::setup_async(
        Result<std::future<void>>& result
    )
    {
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{
				Result<void> void_result;

				setup(void_result);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
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
