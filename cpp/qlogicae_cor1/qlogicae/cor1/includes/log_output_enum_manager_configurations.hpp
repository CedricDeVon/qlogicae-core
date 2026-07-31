#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogOutputEnumManagerConfigurations \
	)

#include "log_output.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		LogOutputEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<LogOutputEnumManagerConfigurations>
	{
	public:	
		LogOutput
			type =
				LogOutput
					::ALL;

		LogOutputEnumManagerConfigurations();
	};
}

#endif
