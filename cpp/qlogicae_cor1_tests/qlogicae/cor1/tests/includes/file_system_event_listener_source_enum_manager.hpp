#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerSourceEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class FileSystemEventListenerSourceEnumManagerTest:
		public ::testing::Test
	{
	public:
		FileSystemEventListenerSourceEnumManager manager;

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

	class FileSystemEventListenerSourceEnumManagerParameterizedTest:
		public FileSystemEventListenerSourceEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,FileSystemEventListenerSource>>
	{
	};

	class FileSystemEventListenerSourceEnumManagerEnumToStringParameterizedTest:
		public FileSystemEventListenerSourceEnumManagerTest,
		public ::testing::WithParamInterface<FileSystemEventListenerSource>
	{
	};
}

#endif
