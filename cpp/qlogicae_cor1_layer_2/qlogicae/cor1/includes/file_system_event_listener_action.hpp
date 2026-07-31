#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerAction \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	enum class
        FileSystemEventListenerAction :
            QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {
        CREATED,

        DELETED,

        MODIFIED,

        RENAMED,

        MOVED,

        METADATA_CHANGED,

        UNKNOWN,

        QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };
}

#endif

