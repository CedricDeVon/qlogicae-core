#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConsoleLogManagerConfigurations \
	)

#include "log_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		ConsoleLogManagerConfigurations :
			LogManagerConfigurations<ConsoleLogManagerConfigurations>
    {
	public:
		ConsoleLogManagerConfigurations();
    };
}

#endif
