#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerMetadataFlagsEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class FileSystemEventListenerMetadataFlagsEnumManagerTest:
		public ::testing::Test
	{
	public:
		FileSystemEventListenerMetadataFlagsEnumManager manager;

		void
			SetUp() override
		{
			manager.construct();
			manager.reset();
		}

		void
			TearDown() override
		{
			manager.destruct();
			manager.reset();
		}
	};

	class FileSystemEventListenerMetadataFlagsEnumManagerParameterizedTest:
		public FileSystemEventListenerMetadataFlagsEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,FileSystemEventListenerMetadataFlags>>
	{
	};

	class FileSystemEventListenerMetadataFlagsEnumManagerEnumToStringParameterizedTest:
		public FileSystemEventListenerMetadataFlagsEnumManagerTest,
		public ::testing::WithParamInterface<FileSystemEventListenerMetadataFlags>
	{
	};
}

#endif
