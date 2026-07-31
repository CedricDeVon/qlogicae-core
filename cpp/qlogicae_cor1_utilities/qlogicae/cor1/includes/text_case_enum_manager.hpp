#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextCaseEnumManager \
	)

#include "abstract_class.hpp"
#include "text_case_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TextCaseEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextCaseEnumManagerConfigurations>
    {
    public:        
		TextCaseEnumManager();

		std::string
			convert_enum_to_string(
				const TextCase&
					value
			);

		std::string
			convert_enum_to_string();

		TextCase
			convert_string_to_enum(
				const std::string&
					value
			);

		TextCase
			convert_string_to_enum();
    };    
}

#endif
