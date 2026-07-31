#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogLevelEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class LogLevelEnumManagerTest:
		public ::testing::Test
	{
	public:
		LogLevelEnumManager manager;

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

	class LogLevelEnumManagerParameterizedTest:
		public LogLevelEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,LogLevel>>
	{
	};

	class LogLevelEnumManagerEnumToStringParameterizedTest:
		public LogLevelEnumManagerTest,
		public ::testing::WithParamInterface<LogLevel>
	{
	};
}

#endif
