#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerWatchContext \
	)

#include "file_system_event_listener_manager_options.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
        FileSystemEventListenerWatchContext
    {
        std::string
            directory;

        FileSystemEventListenerManagerOptions
            options;
    };
}

#endif
