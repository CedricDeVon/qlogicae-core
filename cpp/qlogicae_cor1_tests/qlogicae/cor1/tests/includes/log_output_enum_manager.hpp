#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogOutputEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class LogOutputEnumManagerTest:
		public ::testing::Test
	{
	public:
		LogOutputEnumManager manager;

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

	class LogOutputEnumManagerParameterizedTest:
		public LogOutputEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,LogOutput>>
	{
	};

	class LogOutputEnumManagerEnumToStringParameterizedTest:
		public LogOutputEnumManagerTest,
		public ::testing::WithParamInterface<LogOutput>
	{
	};
}

#endif
