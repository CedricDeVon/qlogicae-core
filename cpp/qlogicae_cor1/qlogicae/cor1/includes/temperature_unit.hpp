#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TemperatureUnit \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    enum class
		TemperatureUnit :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {
        CELSIUS,

        FAHRENHEIT,
        
        KELVIN,
        
        QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };
}

#endif

