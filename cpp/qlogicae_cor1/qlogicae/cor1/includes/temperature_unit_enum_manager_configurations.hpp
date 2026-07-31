#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TemperatureUnitEnumManagerConfigurations \
	)

#include "temperature_unit.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		TemperatureUnitEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TemperatureUnitEnumManagerConfigurations>
	{
	public:	
		TemperatureUnit
			type =
				TemperatureUnit
					::CELSIUS;

		TemperatureUnitEnumManagerConfigurations();
	};
}

#endif
