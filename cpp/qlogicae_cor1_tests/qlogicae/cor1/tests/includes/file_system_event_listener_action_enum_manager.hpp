#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerActionEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class FileSystemEventListenerActionEnumManagerTest:
		public ::testing::Test
	{
	public:
		FileSystemEventListenerActionEnumManager manager;

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

	class FileSystemEventListenerActionEnumManagerParameterizedTest:
		public FileSystemEventListenerActionEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,FileSystemEventListenerAction>>
	{
	};

	class FileSystemEventListenerActionEnumManagerEnumToStringParameterizedTest:
		public FileSystemEventListenerActionEnumManagerTest,
		public ::testing::WithParamInterface<FileSystemEventListenerAction>
	{
	};
}

#endif
