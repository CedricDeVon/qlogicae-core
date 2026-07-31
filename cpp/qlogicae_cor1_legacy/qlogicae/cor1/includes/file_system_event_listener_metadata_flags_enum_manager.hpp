#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerMetadataFlagsEnumManager \
	)

#include "file_system_event_listener_metadata_flags.hpp"
#include "file_system_event_listener_metadata_flags_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		FileSystemEventListenerMetadataFlagsEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemEventListenerMetadataFlagsEnumManagerConfigurations>
    {
    public:
		FileSystemEventListenerMetadataFlagsEnumManager();

		std::string
			convert_enum_to_string(
				const FileSystemEventListenerMetadataFlags&
					value
			);

		std::string
			convert_enum_to_string();

		FileSystemEventListenerMetadataFlags
			convert_string_to_enum(
				const std::string&
					value
			);

		FileSystemEventListenerMetadataFlags
			convert_string_to_enum();
    };
}

#endif
