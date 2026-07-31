#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ValueEnumKeyDeleteHandler \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		ValueEnumKeyDeleteHandler
    {
        void operator()(HKEY handler) const
        {
            if (handler)
            {
                RegCloseKey(handler);
            }
        }
    };
}

#endif
