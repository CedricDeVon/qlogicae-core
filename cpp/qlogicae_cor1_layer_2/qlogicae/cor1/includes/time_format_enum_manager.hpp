#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeFormatEnumManager \
	)

#include "time_format.hpp"
#include "time_format_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TimeFormatEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TimeFormatEnumManagerConfigurations>
    {
    public:
		TimeFormatEnumManager();

		std::string
			convert_enum_to_string(
				const TimeFormat&
					value
			);

		std::string
			convert_enum_to_string();

		TimeFormat
			convert_string_to_enum(
				const std::string&
					value
			);

		TimeFormat
			convert_string_to_enum();
    };
}

#endif
