#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogOutputEnumManager \
	)

#include "log_output.hpp"
#include "log_output_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		LogOutputEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<LogOutputEnumManagerConfigurations>
    {
    public:
		LogOutputEnumManager();

		std::string
			convert_enum_to_string(
				const LogOutput&
					value
			);

		std::string
			convert_enum_to_string();

		LogOutput
			convert_string_to_enum(
				const std::string&
					value
			);

		LogOutput
			convert_string_to_enum();
    };
}

#endif
