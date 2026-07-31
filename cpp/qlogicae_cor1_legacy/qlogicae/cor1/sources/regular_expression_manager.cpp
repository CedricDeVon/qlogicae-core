#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RegularExpressionManager \
	)

#include "../includes/regular_expression_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{    
	RegularExpressionManager
		::RegularExpressionManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RegularExpressionManagerConfigurations>()
    {

	}        

	bool
		RegularExpressionManager
			::is_direct_pattern_matched(
				const std::string&
					value,
				const std::string&
					pattern
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty() ||
				pattern.empty() 
			);	

			int
				error_number;
			PCRE2_SIZE
				error_offset;

			pcre2_code*
				regular_expression =
					pcre2_compile(
						(PCRE2_SPTR)pattern.c_str(),
						PCRE2_ZERO_TERMINATED,
						0,
						&error_number,
						&error_offset,
						nullptr
					);

			if (!regular_expression)
			{
				return
					false;
			}

			bool
				result =
					is_pattern_matched(
						value,
						regular_expression
					);

			pcre2_code_free(
				regular_expression
			);

			return
				result;
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
		RegularExpressionManager
			::is_direct_pattern_matched(
				const std::string&
					value
			)
	{
		return
			is_direct_pattern_matched(
				value,
				configurations
					.pattern
			);
	}

	bool
		RegularExpressionManager
			::is_pattern_matched(
				const std::string&
					value,
				pcre2_code*
					error_code
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				value.empty()
			);

			pcre2_match_data*
				match_data =
					pcre2_match_data_create_from_pattern(
						error_code,
						nullptr
					);

			int
				result =
					pcre2_match(
						error_code,
						(PCRE2_SPTR)value.c_str(),
						value.length(),
						0,
						0,
						match_data,
						nullptr
					);

			pcre2_match_data_free(
				match_data
			);

			return
				result >= 0;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}
}

#endif
