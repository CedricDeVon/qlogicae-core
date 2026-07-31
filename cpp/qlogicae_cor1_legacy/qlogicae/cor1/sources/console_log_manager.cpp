#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConsoleLogManager \
	)

#include "../includes/console_log_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	ConsoleLogManager
		::ConsoleLogManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ConsoleLogManagerConfigurations>()
    {

    }

	bool
		ConsoleLogManager
			::log_formatted_text(
				const std::string&
					text,
				const LogLevel&
					log_level
			)
	{
		return
			log_raw_text(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextLogManager>()					
					.convert_text(
						text,
						log_level
					)
			);
	}

	bool
		ConsoleLogManager
			::log_formatted_text(
				const std::string&
					text
			)
	{
		return
			log_formatted_text(
				text,
				configurations
					.log_level
			);
	}

	bool
		ConsoleLogManager
			::log_formatted_text()
	{
		return
			log_formatted_text(
				configurations
					.text,
				configurations
					.log_level
			);
	}
	
	bool
		ConsoleLogManager
			::log_raw_text(
				const std::string&
					text
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				text.empty()
			);

			fast_io::io::print(
				fast_io::out(),
				text
			);

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {				
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		ConsoleLogManager
			::log_raw_text()
	{
		return
			log_raw_text(
				configurations
					.text
			);
	}
}

#endif
