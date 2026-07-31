#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogMediumEnumManagerConfigurations \
	)

#include "log_medium.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{ 
	struct
		LogMediumEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<LogMediumEnumManagerConfigurations>
	{
	public:	
		LogMedium
			type =
				LogMedium
					::ALL;

		LogMediumEnumManagerConfigurations();
	};
}

#endif
