#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEvent \
	)

#include "file_system_entity.hpp"
#include "file_system_event_listener_action.hpp"
#include "file_system_event_listener_source.hpp"
#include "file_system_event_listener_metadata_flags.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
        FileSystemEvent
    {
        std::uint64_t
            sequence;

        std::uint64_t
            correlation_id;

        std::string
            path;

        std::string
            old_path;

        FileSystemEventListenerAction
            action;

        FileSystemEntity
            type;

        FileSystemEventListenerSource
            source;

        FileSystemEventListenerMetadataFlags
            metadata_flags;

        std::uint8_t
            flags;

        std::chrono::steady_clock::time_point
            timestamp;
    };
}

#endif
