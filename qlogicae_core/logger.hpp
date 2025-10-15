#pragma once

#include "result.hpp"
#include "utilities.hpp"
#include "cli_io.hpp"
#include "log_medium.hpp"
#include "transformer.hpp"

namespace QLogicaeCore
{
	class Logger
	{
	public:
		Logger();
		
		~Logger() = default;
		
		Logger(
			const bool is_simplified
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
			const bool is_simplified = false
		);

		LogMedium get_medium() const;

		std::string get_name() const;

		bool get_is_simplified() const;

		void set_is_simplified(
			const bool& value
		);

		std::vector<std::string> get_output_paths() const;

		void log(
			const std::string& message,
			const LogLevel& log_level = LogLevel::INFO,
			const bool is_simplified = false
		) const;

		std::future<void> log_async(
			const std::string& message,
			const LogLevel& log_level = LogLevel::INFO,
			const bool is_simplified = false
		) const;

		void setup(
			Result<void>& result,
			const bool& is_simplified
		);

		void get_medium(
			Result<LogMedium>& result
		) const;

		void get_name(
			Result<std::string>& result
		) const;

		void get_is_simplified(
			Result<void>& result
		) const;

		void set_is_simplified(
			Result<void>& result,
			const bool& value
		);

		void get_output_paths(
			Result<std::vector<std::string>>& result
		) const;

		void log(
			Result<void>& result,
			const std::string& message,
			const LogLevel& log_level = LogLevel::INFO,
			const bool is_simplified = false
		) const;

		void log_async(
			Result<std::future<void>>& result,
			const std::string& message,
			const LogLevel& log_level = LogLevel::INFO,
			const bool is_simplified = false
		) const;

	protected:
		LogMedium _medium;
		
		std::string _name;
		
		bool _is_simplified;
		
		mutable std::shared_mutex _mutex;

		std::vector<std::string> _output_paths;
	};
}
