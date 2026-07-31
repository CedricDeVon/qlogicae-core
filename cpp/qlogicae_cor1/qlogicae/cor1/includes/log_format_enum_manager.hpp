#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogFormatEnumManager \
	)

#include "log_format.hpp"
#include "log_format_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		LogFormatEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<LogFormatEnumManagerConfigurations>
    {
    public:
		LogFormatEnumManager();

		std::string
			convert_enum_to_string(
				const LogFormat&
					value
			);

		std::string
			convert_enum_to_string();

		LogFormat
			convert_string_to_enum(
				const std::string&
					value
			);

		LogFormat
			convert_string_to_enum();
    };
}

#endif
