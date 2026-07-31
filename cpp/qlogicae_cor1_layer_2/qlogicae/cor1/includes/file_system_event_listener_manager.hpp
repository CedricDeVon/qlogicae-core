#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerManager \
	)

#include "file_system_entity.hpp"
#include "file_system_event_listener_slot.hpp"
#include "file_system_event_listener_source.hpp"
#include "file_system_event_listener_action.hpp"
#include "file_system_event_listener_watch_context.hpp"
#include "file_system_event_listener_metadata_flags.hpp"
#include "file_system_event_listener_manager_options.hpp"
#include "file_system_event_listener_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{	                           
    class
        FileSystemEventListenerManager :
            public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<
                FileSystemEventListenerManagerConfigurations
            >,
            public efsw::FileWatchListener
    {
    public:
        QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
        (
            QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
        );
        
        QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
        (
            QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3
        );

        std::thread
            watcher_thread;

        std::thread
            dispatcher_thread;

        std::atomic<bool>
            is_running;

        std::atomic<std::size_t>
            write_index;

        std::atomic<std::size_t>
            read_index;

        std::atomic<std::uint64_t>
            sequence_counter;

        efsw::FileWatcher
            watcher;

        std::vector<FileSystemEventListenerSlot>
            ring_buffer;

        std::vector<std::function<void(const FileSystemEvent&)>>
            listeners;

        std::unordered_map<
            efsw::WatchID,
            FileSystemEventListenerWatchContext
        >
            watch_registry;

        static constexpr std::size_t
            queue_capacity = 65536;

        FileSystemEventListenerManager();

        ~FileSystemEventListenerManager();

        bool
            construct();

        bool
            destruct();

        bool
            start_watching();

        bool
            stop_watching();

        bool
            add_watch(
                const std::string&
                    directory,
                const FileSystemEventListenerManagerOptions&
                    options
            );
        
        bool
            add_listener(
                const std::function<void(
                    const FileSystemEvent&)>&
                        callback
                );

        bool
            dispatch_loop();

        bool
            notify_batch(
                std::vector<FileSystemEvent>&
                    batch
            );

        bool
            passes_filter(
                const std::string&
                    path,
                const FileSystemEventListenerManagerOptions&
                    options
            );

        bool
            resolve_full_path(
                const efsw::WatchID&
                    watch_id,
                const std::string&
                    directory,
                const std::string&
                    filename,
                std::string&
                    out_path
            );

        bool
            resolve_old_path(
                const efsw::WatchID&
                    watch_id,
                const std::string&
                    directory,
                const std::string&
                    old_filename,
                std::string&
                    out_path
            );
        
        bool
            remove_watch(
                const std::string&
                    directory
            );

        void
            handleFileAction(
                efsw::WatchID
                    watch_id,
                const std::string&
                    directory,
                const std::string&
                    filename,
                efsw::Action
                    action,
                std::string
                    old_filename
            ) override;

        FileSystemEventListenerAction
            translate_action(
                const efsw::Action&
                    action
            );
    };
}

#endif
