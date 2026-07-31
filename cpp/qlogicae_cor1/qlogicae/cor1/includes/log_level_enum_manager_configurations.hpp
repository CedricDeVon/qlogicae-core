#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogLevelEnumManagerConfigurations \
	)

#include "log_level.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		LogLevelEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<LogLevelEnumManagerConfigurations>
	{
	public:	
		LogLevel
			type =
				LogLevel
					::INFO;

		LogLevelEnumManagerConfigurations();
	};
}

#endif
