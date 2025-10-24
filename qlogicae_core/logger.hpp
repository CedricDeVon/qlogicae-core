#pragma once

#include "time.hpp"
#include "result.hpp"
#include "cli_io.hpp"
#include "utilities.hpp"
#include "log_medium.hpp"
#include "time_format.hpp"
#include "transformer.hpp"
#include "text_file_io.hpp"
#include "log_configurations.hpp"
#include "logger_configurations.hpp"

namespace QLogicaeCore
{	
	class Logger
	{
	public:
		Logger();

		~Logger() = default;

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

		void log(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		std::future<void> log_async(
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log(
			Result<void>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogConfigurations& configurations =
				DEFAULT_LOG_CONFIGURATIONS
		);

		void log(
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		std::future<void> log_async(
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		void log_async(
			const std::function<void()>& callback,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		void log(
			Result<void>& result,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		void log_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		void log_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const LogLevel& log_level,
			const bool& is_enabled = true,
			const bool& is_simplified = false
		);

		void log_info(
			const std::string& text,
			const InfoLogConfigurations& configurations =
				DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_info(
			Result<void>& result,
			const std::string& text,
			const InfoLogConfigurations& configurations =
				DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		std::future<void> log_info_async(
			const std::string& text,
			const InfoLogConfigurations& configurations =
				DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_info_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const InfoLogConfigurations& configurations =
				DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_info_async(
			const std::function<void()>& callback,
			const std::string& text,
			const InfoLogConfigurations& configurations =
				DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_info_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const InfoLogConfigurations& configurations =
				DEFAULT_INFO_LOG_CONFIGURATIONS
		);

		void log_success(
			const std::string& text,
			const SuccessLogConfigurations& configurations =
				DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_success(
			Result<void>& result,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
				DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		std::future<void> log_success_async(
			const std::string& text,
			const SuccessLogConfigurations& configurations =
				DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_success_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
				DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_success_async(
			const std::function<void()>& callback,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
				DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_success_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const SuccessLogConfigurations& configurations =
				DEFAULT_SUCCESS_LOG_CONFIGURATIONS
		);

		void log_warning(
			const std::string& text,
			const WarningLogConfigurations& configurations =
				DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_warning(
			Result<void>& result,
			const std::string& text,
			const WarningLogConfigurations& configurations =
				DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		std::future<void> log_warning_async(
			const std::string& text,
			const WarningLogConfigurations& configurations =
				DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_warning_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const WarningLogConfigurations& configurations =
				DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_warning_async(
			const std::function<void()>& callback,
			const std::string& text,
			const WarningLogConfigurations& configurations =
				DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_warning_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const WarningLogConfigurations& configurations =
				DEFAULT_WARNING_LOG_CONFIGURATIONS
		);

		void log_exception(
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
				DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_exception(
			Result<void>& result,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
				DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		std::future<void> log_exception_async(
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
				DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_exception_async(
			Result<std::future<void>>& result,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
				DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_exception_async(
			const std::function<void()>& callback,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
				DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void log_exception_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& text,
			const ExceptionLogConfigurations& configurations =
				DEFAULT_EXCEPTION_LOG_CONFIGURATIONS
		);

		void force_log_to_console_and_file(
			const std::string& origin,
			const std::exception& exception
		);

		std::future<void> force_log_to_console_and_file_async(
			const std::string& origin,
			const std::exception& exception
		);

		void force_log_to_console_and_file_async(
			const std::function<void()>& callback,
			const std::string& origin,
			const std::exception& exception
		);

		void force_log_to_console_and_file(
			Result<void>& result,
			const std::string& origin,
			const std::exception& exception
		);

		void force_log_to_console_and_file_async(
			Result<std::future<void>>& result,
			const std::string& origin,
			const std::exception& exception
		);

		void force_log_to_console_and_file_async(
			const std::function<void(Result<void>& result)>& callback,
			const std::string& origin,
			const std::exception& exception
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

		TextFileIO _text_file_io;

		mutable std::shared_mutex _mutex;

		std::vector<std::string> _output_paths;

		bool _is_log_file_fragmentation_enabled;

		TimeFormat _log_file_fragmentation_format;

		bool _is_log_file_collectivization_enabled;

		std::string _log_file_fragmentation_output_folder_path;
		
		std::string _log_file_collectivization_output_file_name;

		std::string _log_file_collectivization_output_file_path;
		
		std::string _log_file_collectivization_output_folder_path;		

		void _log_to_collectivization_file(
			const std::string& text
		);
		
		void _log_to_collectivization_file(
			Result<void>& result,
			const std::string& text
		);

		std::future<void> _log_to_collectivization_file_async(
			const std::string& text
		);

		void _log_to_collectivization_file_async(
			Result<std::future<void>>& result,
			const std::string& text
		);

		void _log_to_fragmentation_file(
			const std::string& text
		);
		
		void _log_to_fragmentation_file(
			Result<void>& result,
			const std::string& text
		);

		std::future<void> _log_to_fragmentation_file_async(
			const std::string& text
		);
		
		void _log_to_fragmentation_file_async(
			Result<std::future<void>>& result,
			const std::string& text
		);

		void _log_to_file(
			const std::string& path,
			const std::string& text
		);

		void _log_to_file(
			Result<void>& result,
			const std::string& path,
			const std::string& text
		);

		std::future<void> _log_to_file_async(
			const std::string& path,
			const std::string& text
		);

		void _log_to_output_files(
			const std::string& text
		);

		std::future<void> _log_to_output_files_async(
			const std::string& text
		);
		
		void _log_to_output_files(
			Result<void>& result,
			const std::string& text
		);

		std::future<void> _log_to_output_files_async(
			Result<std::future<void>>& result,
			const std::string& text
		);

		std::string _generate_log_fragmentation_file_path();

		void _generate_log_fragmentation_file_path(
			Result<std::string>& result
		);

		std::string _generate_log_collectivization_file_path();

		void _generate_log_collectivization_file_path(
			Result<std::string>& result
		);
	};

	inline static Logger& LOGGER =
		Logger::get_instance();
}
