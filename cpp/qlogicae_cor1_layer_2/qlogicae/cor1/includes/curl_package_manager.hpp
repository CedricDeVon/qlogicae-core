#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CurlPackageManager \
	)

#include "curl_package_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		CurlPackageManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<CurlPackageManagerConfigurations>
    {
    public:        
		CurlPackageManager();

		bool
			setup();
    };
}

#endif
