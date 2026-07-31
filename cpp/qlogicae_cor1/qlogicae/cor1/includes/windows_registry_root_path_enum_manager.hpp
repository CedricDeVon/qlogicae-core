#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsRegistryRootPathEnumManager \
	)

#include "windows_registry_root_path.hpp"
#include "windows_registry_root_path_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		WindowsRegistryRootPathEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<WindowsRegistryRootPathEnumManagerConfigurations>
    {
    public:
		WindowsRegistryRootPathEnumManager();

		std::string
			convert_enum_to_string(
				const WindowsRegistryRootPath&
					value
			);

		std::string
			convert_enum_to_string();

		WindowsRegistryRootPath
			convert_string_to_enum(
				const std::string&
					value
			);

		WindowsRegistryRootPath
			convert_string_to_enum();
    };
}

#endif
