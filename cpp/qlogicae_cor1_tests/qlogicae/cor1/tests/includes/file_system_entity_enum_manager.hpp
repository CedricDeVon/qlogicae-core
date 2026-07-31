#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEntityEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class FileSystemEntityEnumManagerTest:
		public ::testing::Test
	{
	public:
		FileSystemEntityEnumManager manager;

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

	class FileSystemEntityEnumManagerParameterizedTest:
		public FileSystemEntityEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,FileSystemEntity>>
	{
	};

	class FileSystemEntityEnumManagerEnumToStringParameterizedTest:
		public FileSystemEntityEnumManagerTest,
		public ::testing::WithParamInterface<FileSystemEntity>
	{
	};
}

#endif
