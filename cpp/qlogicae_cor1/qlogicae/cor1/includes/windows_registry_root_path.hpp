#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsRegistryRootPath \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    enum class
		WindowsRegistryRootPath :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {
        HKCU,

        HKLM,

		QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };
}

#endif

