#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
        FileSystemEventListenerManagerTest :
            public testing::Test
    {
    public:
        FileSystemEventListenerManager
            manager;

        FileSystemEventListenerManagerOptions
            default_options;

        void
        SetUp() override
        {
            default_options.is_recursive_enabled = true;

            default_options.debounce_interval =
                std::chrono::milliseconds(1);
        }

        void
        TearDown() override
        {
            manager.stop_watching();
        }
    };

    class
        FileSystemEventListenerManagerParameterizedExtensionTest :
            public FileSystemEventListenerManagerTest,
            public testing::WithParamInterface<std::string>
    {
    };

}

#endif
