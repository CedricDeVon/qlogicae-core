#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextCaseManager \
	)

#include "text_case.hpp"
#include "text_case_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TextCaseManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextCaseManagerConfigurations>
    {
    public:        
		TextCaseManager();

		std::string
			convert_text(
				const std::string&
					text,
				const TextCase&
					target_type
			);

		std::string
			convert_text(
				const std::string&
					text
			);	
    };    
}

#endif
