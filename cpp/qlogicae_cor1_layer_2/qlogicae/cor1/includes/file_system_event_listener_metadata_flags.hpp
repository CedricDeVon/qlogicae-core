#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerMetadataFlags \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	enum class
        FileSystemEventListenerMetadataFlags :
            QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {
        PERMISSIONS = 1 << 0,

        TIMESTAMP = 1 << 1,

        OWNERSHIP = 1 << 2,

        QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };  

}

#endif

