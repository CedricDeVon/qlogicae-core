#pragma once

#include "log_level.hpp"

namespace QLogicaeCore
{
	struct LogConfigurations
	{
		LogLevel log_level = LogLevel::INFO;
		bool is_enabled = true;
		bool is_simplified = false;
	};

	inline static LogConfigurations DEFAULT_LOG_CONFIGURATIONS;

	struct InfoLogConfigurations :
		public LogConfigurations
	{
		LogLevel log_level = LogLevel::INFO;
	};

	inline static InfoLogConfigurations DEFAULT_INFO_LOG_CONFIGURATIONS;

	struct SuccessLogConfigurations :
		public LogConfigurations
	{
		LogLevel log_level = LogLevel::SUCCESS;
	};

	inline static SuccessLogConfigurations DEFAULT_SUCCESS_LOG_CONFIGURATIONS;

	struct WarningLogConfigurations :
		public LogConfigurations
	{
		LogLevel log_level = LogLevel::WARNING;
	};

	inline static WarningLogConfigurations DEFAULT_WARNING_LOG_CONFIGURATIONS;

	struct ExceptionLogConfigurations :
		public LogConfigurations
	{
		LogLevel log_level = LogLevel::EXCEPTION;
	};

	inline static ExceptionLogConfigurations DEFAULT_EXCEPTION_LOG_CONFIGURATIONS;
}
