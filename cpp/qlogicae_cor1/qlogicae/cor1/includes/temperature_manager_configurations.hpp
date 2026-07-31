#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TemperatureManagerConfigurations \
	)

#include "temperature_unit.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		TemperatureManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TemperatureManagerConfigurations>
	{
	public:
		TemperatureUnit
			original_unit =
				TemperatureUnit::FAHRENHEIT;

		TemperatureUnit
			target_unit =
				TemperatureUnit::CELSIUS;

		TemperatureManagerConfigurations();
	};
}

#endif
