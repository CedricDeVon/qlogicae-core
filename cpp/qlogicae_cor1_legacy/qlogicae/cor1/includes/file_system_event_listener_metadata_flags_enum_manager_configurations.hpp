#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerMetadataFlagsEnumManagerConfigurations \
	)

#include "file_system_event_listener_metadata_flags.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		FileSystemEventListenerMetadataFlagsEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<FileSystemEventListenerMetadataFlagsEnumManagerConfigurations>
	{
	public:	
		FileSystemEventListenerMetadataFlags
			type =
				FileSystemEventListenerMetadataFlags
					::PERMISSIONS;

		FileSystemEventListenerMetadataFlagsEnumManagerConfigurations();
	};
}

#endif
