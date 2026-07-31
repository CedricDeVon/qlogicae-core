#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RegularKeyDeleteHandler \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		RegularKeyDeleteHandler
    {
        void operator() (HKEY handler)
        {
            if (handler)
            {
                RegCloseKey(handler);
            }
        }
    };
}

#endif
