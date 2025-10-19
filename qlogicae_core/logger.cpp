#include "pch.hpp"

#include "logger.hpp"

namespace QLogicaeCore
{
	Logger::Logger()
	{
		_name = "";
		_output_paths = std::vector<std::string>();
		_medium = LogMedium::CONSOLE;
		_is_simplified = false;
	}

	Logger::Logger(
		const bool is_simplified
	)
	{
		_name = "";
		_output_paths = std::vector<std::string>();
		_medium = LogMedium::CONSOLE;
		_is_simplified = is_simplified;
	}

	Logger::Logger(
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool is_simplified
	)
	{
		_name = name;
		_medium = medium;
		_output_paths = output_paths;
		_is_simplified = is_simplified;
	}

	LogMedium Logger::get_medium()
	{
		return _medium;
	}
	
	bool Logger::get_is_simplified()
	{
		return _is_simplified;
	}

	void Logger::set_is_simplified(
		const bool& value
	)
	{
		_is_simplified = value;
	}

	std::string Logger::get_name()
	{
		return _name;
	}

	std::vector<std::string> Logger::get_output_paths()
	{
		return _output_paths;
	}

	void Logger::log(
		const std::string& message,
		const LogLevel& log_level,
		const bool is_simplified
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			std::string assumed_message =
				(is_simplified) ?
					message :
					TRANSFORMER.to_log_format(message, log_level);

			if (_medium == LogMedium::CONSOLE)
			{
				CLI_IO.print(
					assumed_message
				);
			}
			if (_medium == LogMedium::FILE)
			{
				for (const auto& output_path : _output_paths)
				{
					_log_file_io.set_file_path(output_path);

					_log_file_io.append_async(
						assumed_message
					);
				}
			}
		}
		catch (const std::exception& exception)
		{
			CLI_IO.print_with_new_line_async(
				std::string("Exception at Logger::log(): ") +
				exception.what()
			);
		}
	}

	std::future<void> Logger::log_async(
		const std::string& message,
		const LogLevel& log_level,
		const bool is_simplified
	)
	{
		return std::async(std::launch::async,
			[this, message, log_level, is_simplified]()
			{
				log(message, log_level, is_simplified);
			}
		);
	}

	void Logger::setup(
		Result<void>& result
	)
	{
		_name = "";
		_output_paths = std::vector<std::string>();
		_medium = LogMedium::CONSOLE;
		_is_simplified = false;

		result.set_to_good_status_without_value();
	}

	void Logger::setup(
		Result<void>& result,
		const bool& is_simplified
	)
	{
		_name = "";
		_output_paths = std::vector<std::string>();
		_medium = LogMedium::CONSOLE;
		_is_simplified = is_simplified;

		result.set_to_good_status_without_value();
	}

	void Logger::setup(
		Result<void>& result,
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool is_simplified
	)
	{
		_name = name;
		_medium = medium;
		_output_paths = output_paths;
		_is_simplified = is_simplified;

		result.set_to_good_status_without_value();
	}

	bool Logger::setup()
	{
		_name = "";
		_output_paths = std::vector<std::string>();
		_medium = LogMedium::CONSOLE;
		_is_simplified = false;

		return true;
	}

	bool Logger::setup(
		const bool& is_simplified
	)
	{
		_name = "";
		_output_paths = std::vector<std::string>();
		_medium = LogMedium::CONSOLE;
		_is_simplified = is_simplified;

		return true;
	}

	bool Logger::setup(
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool is_simplified
	)
	{
		_name = name;
		_medium = medium;
		_output_paths = output_paths;
		_is_simplified = is_simplified;

		return true;
	}

	void Logger::get_medium(
		Result<LogMedium>& result
	)
	{
		result.set_to_good_status_with_value(_medium);
	}

	void Logger::get_name(
		Result<std::string>& result
	)
	{
		result.set_to_good_status_with_value(_name);
	}

	void Logger::get_is_simplified(
		Result<bool>& result
	)
	{
		result.set_to_good_status_with_value(_is_simplified);
	}

	void Logger::set_is_simplified(
		Result<void>& result,
		const bool& value
	)
	{
		_is_simplified = value;

		result.set_to_good_status_without_value();
	}

	void Logger::get_output_paths(
		Result<std::vector<std::string>>& result
	)
	{
		result.set_to_good_status_with_value(_output_paths);
	}

	void Logger::log(
		Result<void>& result,
		const std::string& message,
		const LogLevel& log_level,
		const bool is_simplified
	)
	{
		std::scoped_lock lock(_mutex);

		if (is_simplified)
		{
			CLI_IO.print(
				result, message
			);
		}
		else
		{
			Result<std::string> string_result;

			TRANSFORMER.to_log_format(string_result, message, log_level);
			CLI_IO.print(result, string_result.get_value());
		}		

		result.set_to_good_status_without_value();
	}

	void Logger::log_async(
		Result<std::future<void>>& result,
		const std::string& message,
		const LogLevel& log_level,
		const bool is_simplified
	)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
			[this, message, log_level, is_simplified]()
				{
					Result<void> result;

					log(result, message, log_level, is_simplified);
				}
			)
		);
	}
}

