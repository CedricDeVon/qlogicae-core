#pragma once

#include "pch.h"

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
		const bool is_simplified)
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
		const bool is_simplified)
	{
		_name = name;
		_medium = medium;
		_output_paths = output_paths;
		_is_simplified = is_simplified;
	}

	LogMedium Logger::get_medium() const
	{
		return _medium;
	}
	
	bool Logger::get_is_simplified() const
	{
		return _is_simplified;
	}

	void Logger::set_is_simplified(const bool& value)
	{
		_is_simplified = value;
	}

	std::string Logger::get_name() const
	{
		return _name;
	}

	std::vector<std::string> Logger::get_output_paths() const
	{
		return _output_paths;
	}

	void Logger::log(
		const std::string_view& message,
		const LogLevel& log_level,
		const bool is_simplified) const
	{
		try
		{
			std::scoped_lock lock(_mutex);

			CliIO::get_instance().print(
				(is_simplified) ?
				message :
				Transformer::get_instance()
					.to_log_format(message, log_level));
		}
		catch (...)
		{
			CliIO::get_instance().builtin_print(message);
		}
	}

	std::future<void> Logger::log_async(
		const std::string_view& message,
		const LogLevel& log_level,
		const bool is_simplified) const
	{
		return std::async(std::launch::async,
			[this, message, log_level, is_simplified]()
		{
			try
			{
				log(message, log_level, is_simplified);
			}
			catch (...)
			{
				std::scoped_lock lock(_mutex);
			}
		});
	}
}

