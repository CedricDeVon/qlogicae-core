#pragma once

#include "pch.h"

#include "cli_io.hpp"
#include "globals.hpp"
#include "transformer.hpp"

namespace QLogicaeCore
{
	class Logger
	{
	public:
		Logger();
		~Logger() = default;
		Logger(const bool);
		Logger(const Logger&) = delete;
		Logger(Logger&&) noexcept = default;
		Logger& operator = (const Logger&) = delete;
		Logger& operator = (Logger&&) noexcept = default;
		Logger(const std::string&, const LogMedium & = LogMedium::CONSOLE, const std::vector<std::string>& = {}, const bool = false);

		LogMedium get_medium() const;
		std::string get_name() const;
		bool get_is_simplified() const;
		void set_is_simplified(const bool&);
		std::vector<std::string> get_output_paths() const;
		void log(const std::string_view&, const LogLevel & = LogLevel::INFO, const bool = false) const;

		std::future<void> log_async(const std::string_view&, const LogLevel & = LogLevel::INFO, const bool = false) const;

	protected:
		LogMedium _medium;
		std::string _name;
		bool _is_simplified;
		mutable std::shared_mutex _mutex;
		std::vector<std::string> _output_paths;
	};
}
