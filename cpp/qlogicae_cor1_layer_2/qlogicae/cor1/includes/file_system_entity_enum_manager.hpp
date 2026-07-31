#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEntityEnumManager \
	)

#include "file_system_entity.hpp"
#include "file_system_entity_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		FileSystemEntityEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemEntityEnumManagerConfigurations>
    {
    public:
		FileSystemEntityEnumManager();

		std::string
			convert_enum_to_string(
				const FileSystemEntity&
					value
			);

		std::string
			convert_enum_to_string();

		FileSystemEntity
			convert_string_to_enum(
				const std::string&
					value
			);

		FileSystemEntity
			convert_string_to_enum();
    };
}

#endif
