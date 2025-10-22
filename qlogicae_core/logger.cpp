#include "pch.hpp"

#include "logger.hpp"

namespace QLogicaeCore
{	
	Logger::Logger()
	{
		setup();
	}

	Logger::Logger(
		const bool& is_simplified
	)
	{
		setup(
			is_simplified
		);
	}

	Logger::Logger(
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		setup(
			name,
			medium,
			output_paths,
			is_simplified
		);
	}

	Logger::Logger(
		const LoggerConfigurations& configurations
	)
	{
		setup(
			configurations
		);
	}

	bool Logger::setup()
	{
		try
		{
			Result<void> void_result;

			setup(void_result);

			return void_result.is_status_safe();
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file(
				"Logger::setup()",
				exception
			);

			return false;
		}
	}

	void Logger::setup(
		Result<void>& result
	)
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
		_is_enabled = true;
		_is_simplified = false;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_collectivization_output_file_name = "";
		_is_log_file_collectivization_enabled = false;
		_log_file_collectivization_output_folder_path = "";
		_output_paths = {};

		result.set_to_good_status_without_value();
	}

	bool Logger::setup(
		const bool& is_simplified
	)
	{
		try
		{
			Result<void> void_result;

			setup(
				void_result,
				is_simplified
			);

			return void_result.is_status_safe();
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file(
				"Logger::setup()",
				exception
			);

			return false;
		}
	}

	void Logger::setup(
		Result<void>& result,
		const bool& is_simplified
	)
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
		_is_enabled = true;
		_is_simplified = is_simplified;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_is_log_file_collectivization_enabled = false;
		_log_file_collectivization_output_file_name = "";
		_log_file_collectivization_output_folder_path = "";
		_log_file_collectivization_output_file_path = "";
		_output_paths = {};

		result.set_to_good_status_without_value();
	}

	bool Logger::setup(
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		try
		{
			Result<void> void_result;

			setup(
				void_result,
				name,
				medium,
				output_paths,
				is_simplified
			);

			return void_result.is_status_safe();
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file(
				"Logger::setup()",
				exception
			);

			return false;
		}
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
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
		_is_enabled = true;
		_is_simplified = is_simplified;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_is_log_file_collectivization_enabled = false;
		_log_file_collectivization_output_file_name = "";
		_log_file_collectivization_output_folder_path = "";
		_log_file_collectivization_output_file_path = "";
		_output_paths = output_paths;

		result.set_to_good_status_without_value();
	}

	bool Logger::setup(
		const LoggerConfigurations& configurations
	)
	{
		try
		{
			Result<void> void_result;

			setup(
				void_result,
				configurations
			);

			return void_result.is_status_safe();
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file(
				"Logger::setup()",
				exception
			);

			return false;
		}
	}

	void Logger::setup(
		Result<void>& result,
		const LoggerConfigurations& configurations
	)
	{
		_name = configurations.name;
		_log_medium = configurations.log_medium;
		_log_format = configurations.log_format;
		_log_file_fragmentation_format = configurations.log_file_fragmentation_format;
		_is_enabled = configurations.is_enabled;
		_is_simplified = configurations.is_simplified;
		_is_log_file_fragmentation_enabled = configurations.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = configurations.log_file_fragmentation_output_folder_path;
		_is_log_file_collectivization_enabled = configurations.is_log_file_collectivization_enabled;
		_log_file_collectivization_output_file_name = configurations.log_file_collectivization_output_file_name;
		_log_file_collectivization_output_folder_path = configurations.log_file_collectivization_output_folder_path;		
		_output_paths = configurations.output_paths;

		if (_is_log_file_collectivization_enabled)
		{
			_log_file_collectivization_output_file_path =
				_generate_log_collectivization_file_path();
		}
		
		result.set_to_good_status_without_value();
	}

	bool Logger::get_is_simplified()
	{
		return _is_simplified;
	}

	void Logger::get_is_simplified(
		Result<bool>& result
	)
	{
		result.set_to_good_status_with_value(_is_simplified);
	}

	void Logger::set_is_simplified(
		const bool& value
	)
	{
		_is_simplified = value;
	}

	void Logger::set_is_simplified(
		Result<void>& result,
		const bool& value
	)
	{
		_is_simplified = value;

		result.set_to_good_status_without_value();
	}

	bool Logger::get_is_enabled()
	{
		return _is_enabled;
	}

	void Logger::get_is_enabled(
		Result<bool>& result
	)
	{
		result.set_to_good_status_with_value(_is_enabled);
	}

	void Logger::set_is_enabled(
		const bool& value
	)
	{
		_is_enabled = value;
	}

	void Logger::set_is_enabled(
		Result<void>& result,
		const bool& value
	)
	{
		_is_enabled = value;

		result.set_to_good_status_without_value();
	}

	std::string Logger::get_name()
	{
		return _name;
	}

	void Logger::get_name(
		Result<std::string>& result
	)
	{
		result.set_to_good_status_with_value(_name);
	}

	LogMedium Logger::get_medium()
	{
		return _log_medium;
	}

	void Logger::get_medium(
		Result<LogMedium>& result
	)
	{
		result.set_to_good_status_with_value(_log_medium);
	}

	std::vector<std::string> Logger::get_output_paths()
	{
		return _output_paths;
	}

	void Logger::get_output_paths(
		Result<std::vector<std::string>>& result
	)
	{
		result.set_to_good_status_with_value(_output_paths);
	}



	void Logger::log(
		const std::string& text,
		const LogLevel& log_level,
		const bool& is_enabled,
		const bool& is_simplified
	)
	{
		try
		{
			Result<void> result;
			
			log(
				result,
				text,
				log_level,
				is_enabled,
				is_simplified
			);
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file(
				"Logger::log()",
				exception
			);
		}
	}

	std::future<void> Logger::log_async(
		const std::string& text,
		const LogLevel& log_level,
		const bool& is_enabled,
		const bool& is_simplified
	)
	{
		return std::async(
			std::launch::async,
			[this, text, log_level, is_enabled, is_simplified]()
			{
				log(
					text,
					log_level,
					is_enabled,
					is_simplified
				);
			}
		);
	}

	void Logger::log(
		Result<void>& result,
		const std::string& text,
		const LogLevel& log_level,
		const bool& is_enabled,
		const bool& is_simplified
	)
	{
		if ((!is_enabled || !_is_enabled) ||
			_log_medium == LogMedium::NONE
		)
		{
			return result.set_to_good_status_without_value();
		}

		std::scoped_lock lock(_mutex);

		Result<std::string> string_result;
		Result<std::future<void>> future_void_result;
		
		if (is_simplified || _is_simplified)
		{
			string_result.set_value(
				text
			);
		}
		else
		{
			TRANSFORMER.to_log_format(
				string_result,
				text,
				log_level,
				_log_format
			);
		}

		switch (_log_medium)
		{
			case LogMedium::ALL:
			{
				CLI_IO.print_async(
					future_void_result,
					string_result.get_value()
				);

				_log_to_output_files_async(
					string_result.get_value()
				);
				if (_is_log_file_fragmentation_enabled)
				{
					_log_to_fragmentation_file_async(
						string_result.get_value()
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					_log_to_collectivization_file_async(
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
				_log_to_output_files_async(
					string_result.get_value()
				);
				if (_is_log_file_fragmentation_enabled)
				{
					_log_to_fragmentation_file_async(	
						string_result.get_value()
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					_log_to_collectivization_file_async(	
						string_result.get_value()
					);
				}
				break;
			}
		}

		result.set_to_good_status_without_value();
	}

	void Logger::log_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const LogLevel& log_level,
		const bool& is_enabled,
		const bool& is_simplified
	)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
			[this, text, log_level, is_enabled, is_simplified]()
				{
					Result<void> result;

					log(
						result,
						text,
						log_level,
						is_enabled,
						is_simplified
					);
				}
			)
		);
	}

	void Logger::log(
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		try
		{
			Result<void> result;

			log(
				result,
				text,
				configurations
			);
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file(
				"Logger::log()",
				exception
			);
		}
	}

	std::future<void> Logger::log_async(
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		return std::async(std::launch::async,
			[this, text, configurations]()
			{
				log(
					text,
					configurations
				);
			}
		);
	}

	void Logger::log(
		Result<void>& result,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		LogLevel log_level = configurations.log_level;
		bool is_enabled = configurations.is_enabled;
		bool is_simplified = configurations.is_simplified;

		if ((!is_enabled || !_is_enabled) ||
			_log_medium == LogMedium::NONE
			)
		{
			return result.set_to_good_status_without_value();
		}

		std::scoped_lock lock(_mutex);

		std::string transformed_text =
			(is_simplified || _is_simplified) ?
			text :
			TRANSFORMER.to_log_format(
				text,
				log_level,
				_log_format
			);

		switch (_log_medium)
		{
			case LogMedium::ALL:
			{
				CLI_IO.print_async(
					transformed_text
				);

				_log_to_output_files_async(
					transformed_text
				);
				if (_is_log_file_fragmentation_enabled)
				{
					_log_to_fragmentation_file_async(
						transformed_text
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					_log_to_collectivization_file_async(
						transformed_text
					);
				}

				break;
			}
			case LogMedium::CONSOLE:
			{
				CLI_IO.print_async(
					transformed_text
				);

				break;
			}
			case LogMedium::FILE:
			{
				_log_to_output_files_async(
					transformed_text
				);
				if (_is_log_file_fragmentation_enabled)
				{
					_log_to_fragmentation_file_async(
						transformed_text
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					_log_to_collectivization_file_async(
						transformed_text
					);
				}
				break;
			}
		}

		result.set_to_good_status_without_value();
	}

	void Logger::log_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
				[this, text, configurations]()
				{
					Result<void> result;

					log(
						result,
						text,
						configurations
					);
				}
			)
		);
	}

	void Logger::log_info(
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		log(
			text,
			configurations
		);
	}

	void Logger::log_info(
		Result<void>& result,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		log(
			result,
			text,
			configurations
		);
	}

	void Logger::log_success(
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		log(
			text,
			configurations
		);
	}

	void Logger::log_success(
		Result<void>& result,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		log(
			result,
			text,
			configurations
		);
	}

	void Logger::log_warning(
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		log(
			text,
			configurations
		);
	}

	void Logger::log_warning(
		Result<void>& result,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		log(
			result,
			text,
			configurations
		);
	}

	void Logger::log_exception(
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		log(
			text,
			configurations
		);
	}

	void Logger::log_exception(
		Result<void>& result,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		log(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_info_async(
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		return std::async(std::launch::async,
			[this, text, configurations]()
			{
				Result<std::future<void>> result;

				log_async(
					result,
					text,
					configurations
				);
			}
		);
	}

	void Logger::log_info_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
				[this, text, configurations]()
				{
					Result<void> result;

					log(
						result,
						text,
						configurations
					);
				}
			)
		);
	}

	std::future<void> Logger::log_success_async(
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		return std::async(std::launch::async,
			[this, text, configurations]()
			{
				Result<std::future<void>> result;

				log_async(
					result,
					text,
					configurations
				);
			}
		);
	}

	void Logger::log_success_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
				[this, text, configurations]()
				{
					Result<std::future<void>> result;

					log_async(
						result,
						text,
						configurations
					);
				}
			)
		);
	}

	std::future<void> Logger::log_warning_async(
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		return std::async(std::launch::async,
			[this, text, configurations]()
			{
				Result<std::future<void>> result;

				log_async(
					result,
					text,
					configurations
				);
			}
		);
	}

	void Logger::log_warning_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
				[this, text, configurations]()
				{
					Result<std::future<void>> result;

					log_async(
						result,
						text,
						configurations
					);
				}
			)
		);
	}

	std::future<void> Logger::log_exception_async(
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		return std::async(std::launch::async,
			[this, text, configurations]()
			{
				Result<std::future<void>> result;

				log_async(
					result,
					text,
					configurations
				);
			}
		);
	}

	void Logger::log_exception_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
				[this, text, configurations]()
				{
					Result<std::future<void>> result;

					log_async(
						result,
						text,
						configurations
					);
				}
			)
		);
	}

	void Logger::force_log_to_console_and_file(
		const std::string& origin,
		const std::exception& exception
	)
	{
		std::string full_text =
			TRANSFORMER.to_exception_text_format(
				origin,
				exception.what()
			);

		CLI_IO.print_with_new_line_async(
			full_text
		);
		_log_to_fragmentation_file_async(
			full_text
		);
		_log_to_collectivization_file_async(
			full_text
		);
	}

	std::future<void> Logger::force_log_to_console_and_file_async(
		const std::string& origin,
		const std::exception& exception
	)
	{
		return std::async(
			std::launch::async,
			[this, origin, exception]() -> void
			{
				force_log_to_console_and_file(
					origin,
					exception
				);
			}
		);
	}

	void Logger::_log_to_collectivization_file(
		const std::string& text
	)
	{
		TextFileIO text_file_io;

		text_file_io.set_file_path(
			_log_file_collectivization_output_file_path
		);
		text_file_io.append_async(
			text
		);
	}

	std::future<void> Logger::_log_to_collectivization_file_async(
		const std::string& text
	)
	{
		return std::async(
			std::launch::async,
			[this, text]() -> void
			{
				_log_to_collectivization_file(
					text
				);
			}
		);
	}

	void Logger::_log_to_fragmentation_file(
		const std::string& text
	)
	{
		TextFileIO text_file_io;

		text_file_io.set_file_path(
			_generate_log_fragmentation_file_path()
		);
		text_file_io.append_async(
			text
		);
	}

	std::future<void> Logger::_log_to_fragmentation_file_async(
		const std::string& text
	)
	{
		return std::async(
			std::launch::async,
			[this, text]() -> void
			{
				_log_to_fragmentation_file(
					text
				);
			}
		);
	}

	void Logger::_log_to_file(
		const std::string& path,
		const std::string& text
	)
	{
		TextFileIO text_file_io;

		text_file_io.set_file_path(
			path
		);
		text_file_io.append_async(
			text
		);
	}

	std::future<void> Logger::_log_to_file_async(
		const std::string& path,
		const std::string& text
	)
	{
		return std::async(
			std::launch::async,
			[this, path, text]() -> void
			{
				_log_to_file(
					path,
					text
				);
			}
		);		
	}

	void Logger::_log_to_output_files(
		const std::string& text
	)
	{
		for (const auto& output_path :
			_output_paths)
		{
			_log_to_file_async(
				output_path,
				text
			);
		}
	}

	std::future<void> Logger::_log_to_output_files_async(
		const std::string& text
	)
	{
		return std::async(
			std::launch::async,
			[this, text]() -> void
			{
				_log_to_output_files(
					text
				);
			}
		);
	}

	std::string Logger::_generate_log_fragmentation_file_path()
	{
		return _log_file_fragmentation_output_folder_path +
			"\\" + TIME.now(_log_file_fragmentation_format) + ".log";
	}

	std::string Logger::_generate_log_collectivization_file_path()
	{
		return _log_file_collectivization_output_folder_path +
			"\\" + _log_file_collectivization_output_file_name;
	}
}
