#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerSourceEnumManagerConfigurations \
	)

#include "file_system_event_listener_source.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		FileSystemEventListenerSourceEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<FileSystemEventListenerSourceEnumManagerConfigurations>
	{
	public:	
		FileSystemEventListenerSource
			type =
				FileSystemEventListenerSource
					::NATIVE;

		FileSystemEventListenerSourceEnumManagerConfigurations();
	};
}

#endif
