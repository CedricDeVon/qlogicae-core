#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeScaleUnit \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    enum class
		TimeScaleUnit :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {
        YEARS,

        MONTHS,

        WEEKS,

        DAYS,
        
        HOURS,
        
        MINUTES,              
        
        SECONDS,
        
        MILLISECONDS,
        
        MICROSECONDS,
        
        NANOSECONDS,        

		QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };
}

#endif

