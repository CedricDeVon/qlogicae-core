#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerManagerOptions \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
        FileSystemEventListenerManagerOptions
    {
        bool
            is_recursive_enabled;

        std::chrono::milliseconds
            debounce_interval;

        std::unordered_set<std::string>
            extensions;

        std::unordered_set<std::string>
            explicit_files;
    };
}

#endif
