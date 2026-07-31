#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextLogManager \
	)

#include "../includes/text_log_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        
	TextLogManager
		::TextLogManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextLogManagerConfigurations>()
    {
        
    }

	std::string
		TextLogManager
			::convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level,
				const std::string&
					time_format,
				const LogFormat&
					log_format
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				message,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				log_format == LogFormat::NONE
			);

			std::string 
				output;
	
			std::string
				log_level_text =
					QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<LogLevelEnumManager>()						
							.convert_enum_to_string(
								log_level
							);

			switch (log_format)
			{
				case (LogFormat::STANDARD):
				{
					output =
						(time_format.empty() ? "" : time_format + " - ") +
						(log_level_text.empty() ? "" : log_level_text + " - ") +
						message;

					break;
				}
				case (LogFormat::CUSTOM):
				{
					output =
						message;

					break;
				}
				case (LogFormat::NONE):
				{
					output =
						message;

					break;
				}
				default:
				{
					output =
						message;
			
					break;
				}
			}

			if
			(
				configurations
					.is_specified_length_enabled
			)
			{
				if (output.size() > configurations.specified_length)
					output.resize(configurations.specified_length);
				else if (output.size() < configurations.specified_length)
					output.append(configurations.specified_length - output.size(), ' ');
			}

			return
				output;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				message
			);
        }
	}

	std::string
		TextLogManager
			::convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level,
				const TimeFormat&
					time_format,
				const LogFormat&
					log_format
			)
	{
		return
			convert_text(
				message,
				log_level,
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TimeManager>()					
						.get_now(
							time_format
						),
				log_format
			);
	}

	std::string
		TextLogManager
			::convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level,
				const TimeFormat&
					time_format
			)
	{
		return
			convert_text(
				message,
				log_level,
				time_format,
				configurations
					.log_format
			);
	}

	std::string
		TextLogManager
			::convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level,
				const std::string&
					time_format
			)
	{
		return
			convert_text(
				message,
				log_level,
				time_format,
				configurations
					.log_format
			);
	}

	std::string
		TextLogManager
			::convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level,
				const LogFormat&
					log_format
			)
	{
		return
			convert_text(
				message,
				log_level,
				configurations
					.time_format,
				log_format
			);
	}

	std::string
		TextLogManager
			::convert_text(
				const std::string&
					message,
				const LogLevel&
					log_level
			)
	{
		return
			convert_text(
				message,
				log_level,
				configurations
					.time_format,
				configurations
					.log_format
			);
	}

	std::string
		TextLogManager
			::convert_text(
				const std::string&
					message
			)
	{
		return
			convert_text(
				message,
				configurations
					.log_level,
				configurations
					.time_format,
				configurations
					.log_format
			);
	}

	std::string
		TextLogManager
			::convert_text()
	{
		return
			convert_text(
				configurations
					.message,
				configurations
					.log_level,
				configurations
					.time_format,
				configurations
					.log_format
			);
	}
}

#endif
