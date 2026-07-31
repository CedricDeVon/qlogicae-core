#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextEncodingEnumManager \
	)

#include "text_encoding.hpp"
#include "text_encoding_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TextEncodingEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextEncodingEnumManagerConfigurations>
    {
    public:        
		TextEncodingEnumManager();

		std::string
			convert_enum_to_string(
				const TextEncoding&
					value
			);

		std::string
			convert_enum_to_string();

		TextEncoding
			convert_string_to_enum(
				const std::string&
					value
			);

		TextEncoding
			convert_string_to_enum();
    };    
}

#endif
