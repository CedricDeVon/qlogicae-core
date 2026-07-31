#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogMediumEnumManager \
	)

#include "log_medium.hpp"
#include "log_medium_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		LogMediumEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<LogMediumEnumManagerConfigurations>
    {
    public:
		LogMediumEnumManager();

		std::string
			convert_enum_to_string(
				const LogMedium&
					value
			);

		std::string
			convert_enum_to_string();

		LogMedium
			convert_string_to_enum(
				const std::string&
					value
			);

		LogMedium
			convert_string_to_enum();
    };
}

#endif
