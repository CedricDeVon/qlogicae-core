#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerSlot \
	)

#include "file_system_event.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
        FileSystemEventListenerSlot
    {
        std::atomic<bool>
            is_ready;

        FileSystemEvent
            event;

        FileSystemEventListenerSlot() :
            is_ready(false)
        {

        }

        FileSystemEventListenerSlot(
            const FileSystemEventListenerSlot&
        ) = delete;

        FileSystemEventListenerSlot&
            operator = (
                const FileSystemEventListenerSlot&
            ) = delete;

        FileSystemEventListenerSlot(
            FileSystemEventListenerSlot&&
                other
        ) noexcept :
            is_ready(other.is_ready.load(
                std::memory_order_relaxed
            )),
            event(std::move(other.event))
        {
            other.is_ready.store(
                false,
                std::memory_order_relaxed
            );
        }

        FileSystemEventListenerSlot&
            operator = (
                FileSystemEventListenerSlot&&
                    other
            ) noexcept
        {
            is_ready.store(
                other.is_ready.load(
                    std::memory_order_relaxed
                ),
                std::memory_order_relaxed
            );

            event = std::move(other.event);

            other.is_ready.store(
                false,
                std::memory_order_relaxed
            );

            return *this;
        }
    };
}

#endif
