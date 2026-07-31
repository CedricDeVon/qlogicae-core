#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeZoneEnumManager \
	)

#include "time_zone.hpp"
#include "time_zone_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TimeZoneEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TimeZoneEnumManagerConfigurations>
    {
    public:
		TimeZoneEnumManager();

		std::string
			convert_enum_to_string(
				const TimeZone&
					value
			);

		std::string
			convert_enum_to_string();

		TimeZone
			convert_string_to_enum(
				const std::string&
					value
			);

		TimeZone
			convert_string_to_enum();
    };
}

#endif
