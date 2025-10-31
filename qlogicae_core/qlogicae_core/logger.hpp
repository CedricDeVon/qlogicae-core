#pragma once

#include "utilities.hpp"

#include "result.hpp"
#include "time_zone.hpp"
#include "time_format.hpp"
#include "log_configurations.hpp"
#include "logger_configurations.hpp"

namespace QLogicaeCore
{	
	void delay_microseconds(
		double microseconds
	);

	class Logger
	{
	public:
		Logger();

		~Logger();

		Logger(
			const bool& is_log_format_enabled
		);

		Logger(
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_log_format_enabled = false
		);

		Logger(
			const LoggerConfigurations& configurations
		);

		Logger(
			const Logger& instance
		) = delete;

		Logger(
			Logger&& instance
		) noexcept = default;

		Logger& operator = (
			const Logger& instance
		) = delete;

		Logger& operator = (
			Logger&& instance
		) noexcept = default;

		bool setup();

		void setup(
			Result<void>& result
		);

		bool setup(
			const bool& is_log_format_enabled
		);

		void setup(
			Result<void>& result,
			const bool& is_log_format_enabled
		);

		bool setup(
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_log_format_enabled = false
		);

		void setup(
			Result<void>& result,
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_log_format_enabled = false
		);

		bool setup(
			const LoggerConfigurations& configurations
		);

		void setup(
			Result<void>& result,
			const LoggerConfigurations& configurations
		);

		std::future<bool> setup_async();

		void setup_async(
			const std::function<void(const bool& result)>& callback
		);

		void setup_async(
			Result<std::future<void>>& result
		);

		void setup_async(
			const std::function<void(Result<void>& result)>& callback
		);

		std::future<bool> setup_async(
			const bool& is_log_format_enabled
		);

		void setup_async(
			const std::function<void(const bool& result)>& callback,
			const bool& is_log_format_enabled
		);

		void setup_async(
			Result<std::future<void>>& result,
			const bool& is_log_format_enabled
		);

		void setup_async(
			const std::function<void(Result<void>& result)>& callback,
			const bool& is_log_format_enabled
		);

		std::future<bool> setup_async(
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_log_format_enabled = false
		);

		void setup_async(
			const std::function<void(const bool& result)>& callback,
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_log_format_enabled = false
		);

		void setup_async(
			Result<std::future<void>>& result,
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_log_format_enabled = false
		);

		void setup_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_log_format_enabled = false
		);

		std::future<bool> setup_async(
			const LoggerConfigurations& configurations
		);

		void setup_async(
			const std::function<void(const bool& result)>& callback,
			const LoggerConfigurations& configurations
		);

		void setup_async(
			Result<std::future<void>>& result,
			const LoggerConfigurations& configurations
		);		

		void setup_async(
			const std::function<void(Result<void>& result)>& callback,
			const LoggerConfigurations& configurations
		);


		bool get_is_log_format_enabled();

		void get_is_log_format_enabled(
			Result<bool>& result
		);

		void set_is_log_format_enabled(
			const bool& value
		);

		void set_is_log_format_enabled(
			Result<void>& result,
			const bool& value
		);

		bool get_is_enabled();

		void get_is_enabled(
			Result<bool>& result
		);

		void set_is_enabled(
			const bool& value
		);

		void set_is_enabled(
			Result<void>& result,
			const bool& value
		);

		LogMedium get_medium();

		void get_medium(
			Result<LogMedium>& result
		);

		std::string get_name();

		void get_name(
			Result<std::string>& result
		);

		std::vector<std::string> get_file_custom_output_paths();

		void get_file_custom_output_paths(
			Result<std::vector<std::string>>& result
		);

		void log_with_timestamp(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		std::future<void> log_with_timestamp_async(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp(
			Result<void>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp(
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_log_format_enabled = false
		);

		std::future<void> log_with_timestamp_async(
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_log_format_enabled = false
		);

		void log_with_timestamp_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_log_format_enabled = false
		);

		void log_with_timestamp(
			Result<void>& result,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_log_format_enabled = false
		);

		void log_with_timestamp_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_log_format_enabled = false
		);

		void log_with_timestamp_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_log_format_enabled = false
		);

		void log_with_timestamp_to_console_and_file(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		std::future<void> log_with_timestamp_to_console_and_file_async(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_console_and_file_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_console_and_file(
			Result<void>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_console_and_file_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_console_and_file_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_console(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		std::future<void> log_with_timestamp_to_console_async(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_console_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_console(
			Result<void>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_console_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_console_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_files(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		std::future<void> log_with_timestamp_to_files_async(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_files_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_files(
			Result<void>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_files_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_to_files_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_to_console(
			const std::string& text
		);

		std::future<void> log_to_console_async(
			const std::string& text
		);

		void log_to_console_async(
			const std::function<void()>& callback,
			const std::string& text
		);

		void log_to_console(
			Result<void>& result,
			const std::string& text
		);

		void log_to_console_async(
			Result<std::future<void>>& result,
			const std::string& text
		);

		void log_to_console_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text
		);

		void log_to_files(
			const std::string& text
		);

		std::future<void> log_to_files_async(
			const std::string& text
		);

		void log_to_files_async(
			const std::function<void()>& callback,
			const std::string& text
		);

		void log_to_files(
			Result<void>& result,
			const std::string& text
		);

		void log_to_files_async(
			Result<std::future<void>>& result,
			const std::string& text
		);

		void log_to_files_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text
		);
		
		void log_to_collectivization_file(
			const std::string& text
		);

		std::future<void> log_to_collectivization_file_async(
			const std::string& text
		);

		void log_to_collectivization_file_async(
			const std::function<void()>& callback,
			const std::string& text
		);

		void log_to_collectivization_file(
			Result<void>& result,
			const std::string& text
		);

		void log_to_collectivization_file_async(
			Result<std::future<void>>& result,
			const std::string& text
		);

		void log_to_collectivization_file_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text
		);

		void log_to_fragmentation_file(
			const std::string& text
		);

		std::future<void> log_to_fragmentation_file_async(
			const std::string& text
		);

		void log_to_fragmentation_file_async(
			const std::function<void()>& callback,
			const std::string& text
		);

		void log_to_fragmentation_file(
			Result<void>& result,
			const std::string& text
		);

		void log_to_fragmentation_file_async(
			Result<std::future<void>>& result,
			const std::string& text
		);

		void log_to_fragmentation_file_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text
		);

		void log_to_file(
			const std::string& path,
			const std::string& text
		);

		std::future<void> log_to_file_async(
			const std::string& path,
			const std::string& text
		);

		void log_to_file_async(
			const std::function<void()>& callback,
			const std::string& path,
			const std::string& text
		);

		void log_to_file(
			Result<void>& result,
			const std::string& path,
			const std::string& text
		);

		void log_to_file_async(
			Result<std::future<void>>& result,
			const std::string& path,
			const std::string& text
		);

		void log_to_file_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& path,
			const std::string& text
		);

		void log_to_output_files(
			const std::string& text
		);

		std::future<void> log_to_output_files_async(
			const std::string& text
		);

		void log_to_output_files_async(
			const std::function<void()>& callback,
			const std::string& text
		);

		void log_to_output_files(
			Result<void>& result,
			const std::string& text
		);

		void log_to_output_files_async(
			Result<std::future<void>>& result,
			const std::string& text
		);

		void log_to_output_files_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text
		);

		void handle_exception(
			const std::string& origin,
			const std::string& message
		);

		void handle_exception(
			Result<void>& result,
			const std::string& origin,
			const std::string& message
		);

		std::future<void> handle_exception_async(
			const std::string& origin,
			const std::string& message
		);

		void handle_exception_async(
			Result<std::future<void>>& result,
			const std::string& origin,
			const std::string& message
		);

		void handle_exception_async(
			const std::function<void()>& callback,
			const std::string& origin,
			const std::string& message
		);

		void handle_exception_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& origin,
			const std::string& message
		);

		static Logger& get_instance();

		void get_instance(
			Result<Logger*>& result
		);

	protected:		
		std::string _name;

		bool _is_enabled;

		bool _is_log_format_enabled;
		
		LogMedium _log_medium;

		TimeZone _log_time_zone;		

		TimeFormat _log_format;



		bool _is_console_enabled;

		bool _is_console_log_format_enabled;

		bool _is_file_enabled;

		bool _is_file_log_format_enabled;

		bool _is_file_collectivization_enabled;

		bool _is_file_collectivization_log_format_enabled;

		std::string _file_collectivization_file_name;

		std::string _file_collectivization_file_path;
		
		std::string _file_collectivization_folder_path;		

		bool _is_file_fragmentation_enabled;

		bool _is_file_fragmentation_log_format_enabled;
		
		TimeFormat _file_fragmentation_file_name_format;

		std::string _file_fragmentation_folder_path;				

		bool _is_file_custom_enabled;

		bool _is_file_custom_log_format_enabled;

		std::vector<std::string> _file_custom_output_paths;

		mutable std::shared_mutex _mutex;

		std::string _generate_log_fragmentation_file_path();

		void _generate_log_fragmentation_file_path(
			Result<std::string>& result
		);

		std::string _generate_log_collectivization_file_path();

		void _generate_log_collectivization_file_path(
			Result<std::string>& result
		);

		std::string _to_log_format(
			const std::string& text,
			const LogLevel& log_level,
			const TimeFormat& log_format
		);

		void _to_log_format(
			Result<std::string>& result,
			const std::string& text,
			const LogLevel& log_level,
			const TimeFormat& log_format
		);

		std::string _time_now(
			const TimeFormat& time_format
		);

		void _time_now(
			Result<std::string>& result,
			const TimeFormat& time_format
		);
	};

	inline static Logger& LOGGER =
		Logger::get_instance();
}



/*

		void log_with_timestamp_exception(
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
			DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_exception(
			Result<void>& result,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
			DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		std::future<void> log_with_timestamp_exception_async(
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
			DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_exception_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
			DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_exception_async(
			const std::function<void()>& callback,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
			DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_exception_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
				DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);



		void log_with_timestamp_info(
			const std::string& text,
			const InfoLogConfigurations& configurations =
			DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_info(
			Result<void>& result,
			const std::string& text,
			const InfoLogConfigurations& configurations =
			DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		std::future<void> log_with_timestamp_info_async(
			const std::string& text,
			const InfoLogConfigurations& configurations =
			DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_info_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const InfoLogConfigurations& configurations =
			DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_info_async(
			const std::function<void()>& callback,
			const std::string& text,
			const InfoLogConfigurations& configurations =
			DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_info_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const InfoLogConfigurations& configurations =
				DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_success(
			const std::string& text,
			const SuccessLogConfigurations& configurations =
			DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_success(
			Result<void>& result,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
			DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		std::future<void> log_with_timestamp_success_async(
			const std::string& text,
			const SuccessLogConfigurations& configurations =
			DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_success_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
			DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_success_async(
			const std::function<void()>& callback,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
			DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_success_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
				DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_warning(
			const std::string& text,
			const WarningLogConfigurations& configurations =
			DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_warning(
			Result<void>& result,
			const std::string& text,
			const WarningLogConfigurations& configurations =
			DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		std::future<void> log_with_timestamp_warning_async(
			const std::string& text,
			const WarningLogConfigurations& configurations =
			DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_warning_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const WarningLogConfigurations& configurations =
			DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_warning_async(
			const std::function<void()>& callback,
			const std::string& text,
			const WarningLogConfigurations& configurations =
			DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_with_timestamp_warning_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const WarningLogConfigurations& configurations =
				DEFAULT_WARNING_LOG_CONFIGURATIONS
		);


*/




/*


	void Logger::log_timestamp_info(
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		log_timestamp(
			text,
			configurations
		);
	}

	void Logger::log_timestamp_info(
		Result<void>& result,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		log_timestamp(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_timestamp_info_async(
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		if (!_is_enabled)
		{
			return future;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
			promise = std::move(promise)]() mutable
			{
				log_timestamp_info(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_info_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
			promise = std::move(promise)]() mutable
			{
				Result<void> result;

				log_timestamp_info(
					result,
					text,
					configurations
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::log_timestamp_info_async(
		const std::function<void()>& callback,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_info(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_info_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations, callback]() mutable
			{
				Result<void> result;

				log_timestamp_info(
					result,
					text,
					configurations
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_timestamp_success(
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		log_timestamp(
			text,
			configurations
		);
	}

	void Logger::log_timestamp_success(
		Result<void>& result,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		log_timestamp(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_timestamp_success_async(
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();
		if (!_is_enabled)
		{
			return future;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
			promise = std::move(promise)]() mutable
			{
				log_timestamp_success(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_success_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
			promise = std::move(promise)]() mutable
			{
				Result<void> result;

				log_timestamp_success(
					result,
					text,
					configurations
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::log_timestamp_success_async(
		const std::function<void()>& callback,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_success(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_success_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations, callback]() mutable
			{
				Result<void> result;

				log_timestamp_success(
					result,
					text,
					configurations
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_timestamp_warning(
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		log_timestamp(
			text,
			configurations
		);
	}

	void Logger::log_timestamp_warning(
		Result<void>& result,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		log_timestamp(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_timestamp_warning_async(
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();
		if (!_is_enabled)
		{
			return future;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
			promise = std::move(promise)]() mutable
			{
				log_timestamp_warning(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_warning_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
			promise = std::move(promise)]() mutable
			{
				Result<void> result;

				log_timestamp_warning(
					result,
					text,
					configurations
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::log_timestamp_warning_async(
		const std::function<void()>& callback,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_warning(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_warning_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations, callback]() mutable
			{
				Result<void> result;

				log_timestamp_warning(
					result,
					text,
					configurations
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_timestamp_exception(
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		log_timestamp(
			text,
			configurations
		);
	}

	void Logger::log_timestamp_exception(
		Result<void>& result,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		log_timestamp(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_timestamp_exception_async(
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();
		if (!_is_enabled)
		{
			return future;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
			promise = std::move(promise)]() mutable
			{
				log_timestamp_exception(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_exception_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
			promise = std::move(promise)]() mutable
			{
				Result<void> result;

				log_timestamp_exception(
					result,
					text,
					configurations
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::log_timestamp_exception_async(
		const std::function<void()>& callback,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_exception(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_exception_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		if (!_is_enabled)
		{
			return;
		}

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations, callback]() mutable
			{
				Result<void> result;

				log_timestamp_exception(
					result,
					text,
					configurations
				);

				callback(
					result
				);
			}
		);
	}


*/