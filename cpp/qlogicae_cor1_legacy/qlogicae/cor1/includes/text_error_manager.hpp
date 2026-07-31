#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextErrorManager \
	)

#include "text_error_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TextErrorManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextErrorManagerConfigurations>
    {
    public:        
		TextErrorManager();

		std::string
			convert_text(
				const std::string&
					origin,
				const std::string&
					message
			);

		std::string
			convert_text(
				const std::string&
					message
			);
    };    
}

#endif
