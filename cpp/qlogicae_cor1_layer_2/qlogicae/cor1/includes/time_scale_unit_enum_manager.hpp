#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeScaleUnitEnumManager \
	)

#include "time_scale_unit.hpp"
#include "time_scale_unit_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TimeScaleUnitEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TimeScaleUnitEnumManagerConfigurations>
    {
    public:
		TimeScaleUnitEnumManager();

		std::string
			convert_enum_to_string(
				const TimeScaleUnit&
					value
			);

		std::string
			convert_enum_to_string();

		TimeScaleUnit
			convert_string_to_enum(
				const std::string&
					value
			);

		TimeScaleUnit
			convert_string_to_enum();
    };
}

#endif
