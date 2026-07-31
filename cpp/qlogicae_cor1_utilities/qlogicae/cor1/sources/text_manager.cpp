#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextManager \
	)

#include "../includes/text_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    TextManager
		::TextManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextManagerConfigurations>()
	{
		construct();		
	}

	TextManager
		::~TextManager()
	{
		destruct();		
	}
    
    bool
        TextManager
			::construct()
    {
        try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			return
				!(sodium_init() > 1);
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
        TextManager
			::destruct()
    {
        try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
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

	std::string
		TextManager
			::replace_text_tokens(
				const std::string&
					text,
				const std::unordered_map<std::string, std::string>&
					dictionary
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				text,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				text.empty() ||
				dictionary.size() == 0
			);		

			return
				absl::StrReplaceAll(
					text,
					dictionary
				);
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
		TextManager
			::replace_text_tokens(
				const std::string&
					text
			)
	{
		return
			replace_text_tokens(
				text,
				configurations
					.replace_text_tokens_dictionary
			);
	}

	std::vector<std::string>
		TextManager
			::split_text(
				const std::string&
					text,
				const std::string&
					delimeter
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				text.empty()
			);	

			return
				absl::StrSplit(
					text,
					delimeter
				);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();				
        }
	}

	std::vector<std::string>
		TextManager
			::split_text(
				const std::string&
					text
			)
	{
		return
			split_text(
				text,
				configurations
					.split_text_delimeter
			);
	}
}

#endif

