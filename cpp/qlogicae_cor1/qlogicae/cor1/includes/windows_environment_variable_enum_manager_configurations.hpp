#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsEnvironmentVariableEnumManagerConfigurations \
	)

#include "windows_environment_variable.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		WindowsEnvironmentVariableEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<WindowsEnvironmentVariableEnumManagerConfigurations>
	{
	public:	
		WindowsEnvironmentVariable
			type =
				WindowsEnvironmentVariable
					::USER;

		WindowsEnvironmentVariableEnumManagerConfigurations();
	};
}

#endif
