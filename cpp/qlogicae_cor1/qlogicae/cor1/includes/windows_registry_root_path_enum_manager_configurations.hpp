#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsRegistryRootPathEnumManagerConfigurations \
	)

#include "windows_registry_root_path.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		WindowsRegistryRootPathEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<WindowsRegistryRootPathEnumManagerConfigurations>
	{
	public:	
		WindowsRegistryRootPath
			type =
				WindowsRegistryRootPath
					::HKCU;

		WindowsRegistryRootPathEnumManagerConfigurations();
	};
}

#endif
