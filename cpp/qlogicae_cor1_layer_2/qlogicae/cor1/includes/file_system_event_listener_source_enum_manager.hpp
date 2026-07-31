#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerSourceEnumManagerConfigurations \
	)

#include "file_system_event_listener_source.hpp"
#include "file_system_event_listener_source_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		FileSystemEventListenerSourceEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemEventListenerSourceEnumManagerConfigurations>
    {
    public:
		FileSystemEventListenerSourceEnumManager();

		std::string
			convert_enum_to_string(
				const FileSystemEventListenerSource&
					value
			);

		std::string
			convert_enum_to_string();

		FileSystemEventListenerSource
			convert_string_to_enum(
				const std::string&
					value
			);

		FileSystemEventListenerSource
			convert_string_to_enum();
    };
}

#endif
