#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeFormat \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    enum class
		TimeFormat :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {
        UNIX,
        
        ISO8601,
        
        SECOND_LEVEL_TIMESTAMP,
        
        MILLISECOND_LEVEL_TIMESTAMP,
        
        MICROSECOND_LEVEL_TIMESTAMP,
        
        FULL_TIMESTAMP,
        
        FULL_DASHED_TIMESTAMP,
        
        HOUR_12,
        
        HOUR_24,
        
        MILLISECOND_MICROSECOND_NANOSECOND,
        
        DATE_DASHED,
        
        DATE_MDY_SLASHED,
        
        DATE_DMY_SLASHED,
        
        DATE_DMY_SPACED,
        
        DATE_VERBOSE,
		
		QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };
}

#endif

