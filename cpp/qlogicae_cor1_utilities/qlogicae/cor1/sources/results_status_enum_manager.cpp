#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ResultsStatusEnumManager \
	)

#include "../includes/results_status_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	ResultsStatusEnumManager
		::ResultsStatusEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ResultsStatusEnumManagerConfigurations>()
    {

	}        


	std::string
		ResultsStatusEnumManager
			::convert_enum_to_string(
				const ResultsStatus&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				"NONE",
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			switch (value)
			{
				case (ResultsStatus::GOOD):
				{
					return
						"GOOD";
				}
				case (ResultsStatus::BAD):
				{
					return
						"BAD";
				}
				case (ResultsStatus::INFO):
				{
					return
						"INFO";
				}
				case (ResultsStatus::DEBUG):
				{
					return
						"DEBUG";
				}
				case (ResultsStatus::WARNING):
				{
					return
						"WARNING";
				}
				case (ResultsStatus::EXCEPTION):
				{
					return
						"EXCEPTION";
				}
				case (ResultsStatus::ERROR_TYPE):
				{
					return
						"ERROR_TYPE";
				}
				case (ResultsStatus::NONE):
				{
					return
						"NONE";
				}				
				default:
				{
					return
						"NONE";
				}
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {	
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				"NONE"
			);
        }
	}

	std::string
		ResultsStatusEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	ResultsStatus
		ResultsStatusEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				ResultsStatus::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			if
			(
				value == "GOOD"
			)
			{
				return
					ResultsStatus
						::GOOD;
			}
			else if
			(
				value == "BAD"
			)
			{
				return
					ResultsStatus
						::BAD;
			}
			else if
			(
				value == "INFO"
			)
			{
				return
					ResultsStatus
						::INFO;
			}			
			else if
			(
				value == "DEBUG"
			)
			{
				return
					ResultsStatus
						::DEBUG;
			}
			else if
			(
				value == "WARNING"
			)
			{
				return
					ResultsStatus
						::WARNING;
			}
			else if
			(
				value == "EXCEPTION"
			)
			{
				return
					ResultsStatus
						::EXCEPTION;
			}			
			else if
			(
				value == "ERROR_TYPE"
			)
			{
				return
					ResultsStatus
						::ERROR_TYPE;
			}
			else if
			(
				value == "NONE"
			)
			{
				return
					ResultsStatus
						::NONE;
			}
			else
			{
				return
					ResultsStatus
						::NONE;
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				ResultsStatus::NONE
			);		
        }
	}

	ResultsStatus
		ResultsStatusEnumManager
			::convert_string_to_enum()
	{
		return
			convert_string_to_enum(
				convert_enum_to_string(
					configurations
						.type
				)
			);
	}
}

#endif

