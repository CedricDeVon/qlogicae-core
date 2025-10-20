#include "pch.hpp"

#include "logger.hpp"

namespace QLogicaeCore
{
	Logger::Logger()
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_is_simplified = false;
		_output_paths = {};
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
	}

	Logger::Logger(
		const bool& is_simplified
	)
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_is_simplified = is_simplified;
		_output_paths = {};
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
	}

	Logger::Logger(
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		_name = name;
		_log_medium = medium;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_is_simplified = is_simplified;
		_output_paths = output_paths;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
	}

	Logger::Logger(
		const LoggerConfigurations& configurations
	)
	{
		_name = configurations.name;
		_log_medium = configurations.log_medium;
		_log_format = configurations.log_format;
		_is_simplified = configurations.is_simplified;
		_output_paths = configurations.output_paths;
		_is_log_file_fragmentation_enabled = configurations.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = configurations.log_file_fragmentation_output_folder_path;
		_log_file_fragmentation_format = configurations.log_file_fragmentation_format;
	}

	bool Logger::setup(
		const LoggerConfigurations& configurations
	)
	{
		_name = configurations.name;
		_log_medium = configurations.log_medium;
		_log_format = configurations.log_format;
		_is_simplified = configurations.is_simplified;
		_output_paths = configurations.output_paths;
		_is_log_file_fragmentation_enabled = configurations.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = configurations.log_file_fragmentation_output_folder_path;
		_log_file_fragmentation_format = configurations.log_file_fragmentation_format;
	}

	void Logger::setup(
		Result<void>& result,
		const LoggerConfigurations& configurations
	)
	{
		_name = configurations.name;
		_log_medium = configurations.log_medium;
		_log_format = configurations.log_format;
		_is_simplified = configurations.is_simplified;
		_output_paths = configurations.output_paths;
		_is_log_file_fragmentation_enabled = configurations.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = configurations.log_file_fragmentation_output_folder_path;
		_log_file_fragmentation_format = configurations.log_file_fragmentation_format;

		result.set_to_good_status_without_value();
	}

	LogMedium Logger::get_medium()
	{
		return _log_medium;
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
		const bool& is_simplified
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			if (_log_medium == LogMedium::NONE)
			{
				return;
			}

			std::string assumed_message =
				(_is_simplified || is_simplified) ?
					message :
					TRANSFORMER.to_log_format(
						message,
						log_level,
						_log_format
					);
			
			switch (_log_medium)
			{
			case LogMedium::ALL:
			{
				CLI_IO.print_async(
					assumed_message
				);

				for (const auto& output_path :
					_output_paths)
				{
					_log_file_io.set_file_path(
						output_path
					);

					_log_file_io.append(
						assumed_message
					);
				}
				if (_is_log_file_fragmentation_enabled)
				{
					_log_file_io.set_file_path(
						_log_file_fragmentation_output_folder_path +
						"\\" + TIME.now(_log_file_fragmentation_format) + ".log"
					);

					_log_file_io.append(
						assumed_message
					);
				}

				break;
			}
			case LogMedium::CONSOLE:
			{
				CLI_IO.print_async(
					assumed_message
				);
				break;
			}
			case LogMedium::FILE:
			{
				for (const auto& output_path :
					_output_paths)
				{
					_log_file_io.set_file_path(
						output_path
					);

					_log_file_io.append(
						assumed_message
					);
				}
				if (_is_log_file_fragmentation_enabled)
				{
					_log_file_io.set_file_path(
						_log_file_fragmentation_output_folder_path +
						"\\" + TIME.now(_log_file_fragmentation_format) + ".log"
					);

					_log_file_io.append(
						assumed_message
					);
				}
				break;
			}
			default:
				return;
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
		const bool& is_simplified
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
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_is_simplified = false;
		_output_paths = {};
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;

		result.set_to_good_status_without_value();
	}

	void Logger::setup(
		Result<void>& result,
		const bool& is_simplified
	)
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_is_simplified = is_simplified;
		_output_paths = {};
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;

		result.set_to_good_status_without_value();
	}

	void Logger::setup(
		Result<void>& result,
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		_name = name;
		_log_medium = medium;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_is_simplified = is_simplified;
		_output_paths = output_paths;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;

		result.set_to_good_status_without_value();
	}

	bool Logger::setup()
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_is_simplified = false;
		_output_paths = {};
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;

		return true;
	}

	bool Logger::setup(
		const bool& is_simplified
	)
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_is_simplified = is_simplified;
		_output_paths = {};
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;

		return true;
	}

	bool Logger::setup(
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		_name = name;
		_log_medium = medium;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_is_simplified = is_simplified;
		_output_paths = output_paths;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;

		return true;
	}

	void Logger::get_medium(
		Result<LogMedium>& result
	)
	{
		result.set_to_good_status_with_value(_log_medium);
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
		const bool& is_simplified
	)
	{
		std::scoped_lock lock(_mutex);

		/*
		if (_log_medium == LogMedium::NONE)
		{
			return result.set_to_good_status_without_value();
		}

		Result<std::string> string_result;
		if (is_simplified)
		{
			string_result.set_value(
				message
			);
		}
		else
		{
			TRANSFORMER.to_log_format(
				string_result,
				message,
				log_level
			);
		}
		if (string_result.is_status_unsafe())
		{
			return result.set_to_bad_status_without_value();
		}

		Result<std::future<void>> future_void_result;
		Result<std::future<bool>> future_boolean_result;
		switch (_log_medium)
		{
		case LogMedium::ALL:
		{
			CLI_IO.print_async(
				future_void_result,
				string_result.get_value()
			);

			for (const auto& output_path : _output_paths)
			{
				_log_file_io.set_file_path(
					result,
					output_path
				);

				_log_file_io.append_async(
					future_boolean_result,
					string_result.get_value()
				);
			}
			break;
		}
		case LogMedium::CONSOLE:
		{
			CLI_IO.print_async(
				future_void_result,
				string_result.get_value()
			);
			break;
		}
		case LogMedium::FILE:
		{
			for (const auto& output_path : _output_paths)
			{
				_log_file_io.set_file_path(
					result,
					output_path
				);

				_log_file_io.append_async(
					future_boolean_result,
					string_result.get_value()
				);
			}
			break;
		}
		default:
			return;
		}
		*/

		result.set_to_good_status_without_value();
	}

	void Logger::log_async(
		Result<std::future<void>>& result,
		const std::string& message,
		const LogLevel& log_level,
		const bool& is_simplified
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
