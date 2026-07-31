#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TemperatureUnitEnumManager \
	)

#include "temperature_unit.hpp"
#include "temperature_unit_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TemperatureUnitEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TemperatureUnitEnumManagerConfigurations>
    {
    public:
		TemperatureUnitEnumManager();

		std::string
			convert_enum_to_string(
				const TemperatureUnit&
					value
			);

		std::string
			convert_enum_to_string();

		TemperatureUnit
			convert_string_to_enum(
				const std::string&
					value
			);

		TemperatureUnit
			convert_string_to_enum();
    };
}

#endif
