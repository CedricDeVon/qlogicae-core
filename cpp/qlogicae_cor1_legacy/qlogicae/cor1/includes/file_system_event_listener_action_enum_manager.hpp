#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerActionEnumManager \
	)

#include "file_system_event.hpp"
#include "file_system_event_listener_action_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		FileSystemEventListenerActionEnumManager:
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemEventListenerActionEnumManagerConfigurations>
    {
    public:
		FileSystemEventListenerActionEnumManager();

		std::string
			convert_enum_to_string(
				const FileSystemEventListenerAction&
					value
			);

		std::string
			convert_enum_to_string();

		FileSystemEventListenerAction
			convert_string_to_enum(
				const std::string&
					value
			);

		FileSystemEventListenerAction
			convert_string_to_enum();
    };
}

#endif
