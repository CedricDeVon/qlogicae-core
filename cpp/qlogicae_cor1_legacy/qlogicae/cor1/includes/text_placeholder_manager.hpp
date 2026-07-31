#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextPlaceholderManager \
	)

#include "text_placeholder_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TextPlaceholderManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextPlaceholderManagerConfigurations>
    {
    public:        
		TextPlaceholderManager();

		std::string
			convert_text(
				const std::string&
					text,
				const std::string&
					placeholder
			);
		
		std::string
			convert_text(
				const std::string&
					text
			);
    };    
}

#endif
