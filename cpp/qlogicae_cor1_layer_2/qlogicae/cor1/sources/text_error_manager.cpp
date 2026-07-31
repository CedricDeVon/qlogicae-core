#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextErrorManager \
	)

#include "../includes/text_error_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    TextErrorManager
		::TextErrorManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextErrorManagerConfigurations>()
	{
			
	}

	std::string
		TextErrorManager
			::convert_text(
				const std::string&
					origin,
				const std::string&
					message
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			if (configurations.is_specified_length_enabled)
			{
				std::string text;
				text.resize(configurations.specified_length);

				text = 
					configurations.title +
					(origin.empty() ? "" : (" at " + origin)) +
					" " +
					configurations.separator +
					" " +
					message;

				return
					text;
			}
			else

			{
				return
					configurations.title +
					(origin.empty() ? "" : (" at " + origin)) +
					" " +
					configurations.separator +
					" " +
					message;
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::string
		TextErrorManager
			::convert_text(
				const std::string&
					message
			)
	{
		return
			convert_text(
				configurations
					.origin,
				message
			);
	}
}

#endif
