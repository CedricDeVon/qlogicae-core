#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextLogManager \
	)

#include "log_level.hpp"
#include "log_format.hpp"
#include "time_format.hpp"
#include "time_manager.hpp"
#include "log_level_enum_manager.hpp"
#include "log_format_enum_manager.hpp"
#include "text_log_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TextLogManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextLogManagerConfigurations>
    {
    public:        
		TextLogManager();

		std::string
			convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level,
				const std::string&
					time_format,
				const LogFormat&
					log_format
			);

		std::string
			convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level,
				const TimeFormat&
					time_format,
				const LogFormat&
					log_format
			);

		std::string
			convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level,
				const std::string&
					time_format
			);

		std::string
			convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level,
				const TimeFormat&
					time_format
			);

		std::string
			convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level,
				const LogFormat&
					log_format
			);

		std::string
			convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level
			);

		std::string
			convert_text(	
				const std::string&
					message
			);

		std::string
			convert_text();

    };    
}

#endif
