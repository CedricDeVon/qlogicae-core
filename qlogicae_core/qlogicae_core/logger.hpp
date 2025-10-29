#pragma once

#include "utilities.hpp"

#include "result.hpp"
#include "time_zone.hpp"
#include "time_format.hpp"
#include "log_configurations.hpp"
#include "logger_configurations.hpp"

namespace QLogicaeCore
{	
	class Logger
	{
	public:
		Logger();

		~Logger();

		Logger(
			const bool& is_simplified
		);

		Logger(
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_simplified = false
		);

		Logger(
			const LoggerConfigurations& configurations
		);

		Logger(
			const Logger& logger
		) = delete;

		Logger(
			Logger&& logger
		) noexcept = default;

		Logger& operator = (
			const Logger& logger
		) = delete;

		Logger& operator = (
			Logger&& logger
		) noexcept = default;

		bool setup();

		void setup(
			Result<void>& result
		);

		bool setup(
			const bool& is_simplified
		);

		void setup(
			Result<void>& result,
			const bool& is_simplified
		);

		bool setup(
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_simplified = false
		);

		void setup(
			Result<void>& result,
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_simplified = false
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
			const bool& is_simplified
		);

		void setup_async(
			const std::function<void(const bool& result)>& callback,
			const bool& is_simplified
		);

		void setup_async(
			Result<std::future<void>>& result,
			const bool& is_simplified
		);

		void setup_async(
			const std::function<void(Result<void>& result)>& callback,
			const bool& is_simplified
		);

		std::future<bool> setup_async(
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_simplified = false
		);

		void setup_async(
			const std::function<void(const bool& result)>& callback,
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_simplified = false
		);

		void setup_async(
			Result<std::future<void>>& result,
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_simplified = false
		);

		void setup_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_simplified = false
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

		bool get_is_simplified();

		void get_is_simplified(
			Result<bool>& result
		);

		void set_is_simplified(
			const bool& value
		);

		void set_is_simplified(
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

		std::vector<std::string> get_output_paths();

		void get_output_paths(
			Result<std::vector<std::string>>& result
		);

		void log_timestamp(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		std::future<void> log_timestamp_async(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp(
			Result<void>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp(
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		std::future<void> log_timestamp_async(
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		void log_timestamp_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		void log_timestamp(
			Result<void>& result,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		void log_timestamp_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		void log_timestamp_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		void log_timestamp_info(
			const std::string& text,
			const InfoLogConfigurations& configurations =
			DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_timestamp_info(
			Result<void>& result,
			const std::string& text,
			const InfoLogConfigurations& configurations =
			DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		std::future<void> log_timestamp_info_async(
			const std::string& text,
			const InfoLogConfigurations& configurations =
			DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_timestamp_info_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const InfoLogConfigurations& configurations =
			DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_timestamp_info_async(
			const std::function<void()>& callback,
			const std::string& text,
			const InfoLogConfigurations& configurations =
			DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_timestamp_info_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const InfoLogConfigurations& configurations =
				DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_timestamp_success(
			const std::string& text,
			const SuccessLogConfigurations& configurations =
			DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_timestamp_success(
			Result<void>& result,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
			DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		std::future<void> log_timestamp_success_async(
			const std::string& text,
			const SuccessLogConfigurations& configurations =
			DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_timestamp_success_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
			DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_timestamp_success_async(
			const std::function<void()>& callback,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
			DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_timestamp_success_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
				DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_timestamp_warning(
			const std::string& text,
			const WarningLogConfigurations& configurations =
			DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_timestamp_warning(
			Result<void>& result,
			const std::string& text,
			const WarningLogConfigurations& configurations =
			DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		std::future<void> log_timestamp_warning_async(
			const std::string& text,
			const WarningLogConfigurations& configurations =
			DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_timestamp_warning_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const WarningLogConfigurations& configurations =
			DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_timestamp_warning_async(
			const std::function<void()>& callback,
			const std::string& text,
			const WarningLogConfigurations& configurations =
			DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_timestamp_warning_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const WarningLogConfigurations& configurations =
				DEFAULT_WARNING_LOG_CONFIGURATIONS
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

		void log_timestamp_exception(
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
			DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_timestamp_exception(
			Result<void>& result,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
			DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		std::future<void> log_timestamp_exception_async(
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
			DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_timestamp_exception_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
			DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_timestamp_exception_async(
			const std::function<void()>& callback,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
			DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_timestamp_exception_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
				DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_console_and_file(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		std::future<void> log_timestamp_to_console_and_file_async(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_console_and_file_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_console_and_file(
			Result<void>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_console_and_file_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_console_and_file_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_console(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		std::future<void> log_timestamp_to_console_async(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_console_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_console(
			Result<void>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_console_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_console_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_files(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		std::future<void> log_timestamp_to_files_async(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_files_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_files(
			Result<void>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_files_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_timestamp_to_files_async(
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

		static Logger& get_instance();

		void get_instance(
			Result<Logger*>& result
		);

	protected:		
		bool _is_enabled;
		
		std::string _name;

		bool _is_simplified;

		LogMedium _log_medium;

		TimeFormat _log_format;

		TimeZone _log_time_zone;

		mutable std::shared_mutex _mutex;

		std::vector<std::string> _output_paths;

		bool _is_log_console_enabled;

		bool _is_log_file_fragmentation_enabled;

		TimeFormat _log_file_fragmentation_format;

		bool _is_log_file_collectivization_enabled;

		std::string _log_file_fragmentation_output_folder_path;
		
		std::string _log_file_collectivization_output_file_name;

		std::string _log_file_collectivization_output_file_path;
		
		std::string _log_file_collectivization_output_folder_path;		

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
			const LogLevel& log_level
		);

		void _to_log_format(
			Result<std::string>& result,
			const std::string& text,
			const LogLevel& log_level
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
