#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileLogManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class FileLogManagerTest: public ::testing::Test
	{
	public:
		FileLogManager manager;

		void SetUp() override
		{
			manager.reset();
		}

		void TearDown() override
		{
			manager.reset();
		}
	};

	struct FileKeyParam
	{
		std::string key;
		bool expect_success;
	};

	class FileLogManagerParameterizedTest:
		public FileLogManagerTest,
		public ::testing::WithParamInterface<FileKeyParam>
	{
	};

	struct FileKeyEdgeParam
	{
		std::string key;
		bool expect_success;
	};

	class FileLogManagerEdgeKeyParameterizedTest:
		public FileLogManagerTest,
		public ::testing::WithParamInterface<FileKeyEdgeParam>
	{
	};
}

#endif
