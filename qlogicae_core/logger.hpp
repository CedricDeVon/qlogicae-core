#pragma once

#include "time.hpp"
#include "result.hpp"
#include "cli_io.hpp"
#include "utilities.hpp"
#include "log_medium.hpp"
#include "time_format.hpp"
#include "transformer.hpp"
#include "text_file_io.hpp"
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

		Logger(
			const std::string& name,
			const LogMedium& medium = LogMedium::CONSOLE,
			const std::vector<std::string>& output_paths = {},
			const bool& is_simplified = false
		);

		Logger(
			const LoggerConfigurations& configurations
		);

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

		LogMedium get_medium();

		std::string get_name();

		bool get_is_simplified();

		void set_is_simplified(
			const bool& value
		);

		std::vector<std::string> get_output_paths();

		void log(
			const std::string& message,
			const LogLevel& log_level = LogLevel::INFO,
			const bool& is_simplified = false
		);

		std::future<void> log_async(
			const std::string& message,
			const LogLevel& log_level = LogLevel::INFO,
			const bool& is_simplified = false
		);

		void get_medium(
			Result<LogMedium>& result
		);

		void get_name(
			Result<std::string>& result
		);

		void get_is_simplified(
			Result<bool>& result
		);

		void set_is_simplified(
			Result<void>& result,
			const bool& value
		);

		void get_output_paths(
			Result<std::vector<std::string>>& result
		);

		void log(
			Result<void>& result,
			const std::string& message,
			const LogLevel& log_level = LogLevel::INFO,
			const bool& is_simplified = false
		);

		void log_async(
			Result<std::future<void>>& result,
			const std::string& message,
			const LogLevel& log_level = LogLevel::INFO,
			const bool& is_simplified = false
		);

	protected:
		TextFileIO _log_file_io;

		LogMedium _log_medium;

		TimeFormat _log_format;

		TimeFormat _log_file_fragmentation_format;

		std::string _log_file_fragmentation_output_folder;
		
		std::string _name;
		
		bool _is_simplified;

		bool _is_log_file_fragmentation_enabled;
		
		std::string _log_file_fragmentation_output_folder_path;

		mutable std::shared_mutex _mutex;

		std::vector<std::string> _output_paths;
	};

	static inline Logger LOGGER;
}
