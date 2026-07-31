#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogMediumEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class LogMediumEnumManagerTest:
		public ::testing::Test
	{
	public:
		LogMediumEnumManager manager;

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

	class LogMediumEnumManagerParameterizedTest:
		public LogMediumEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,LogMedium>>
	{
	};

	class LogMediumEnumManagerEnumToStringParameterizedTest:
		public LogMediumEnumManagerTest,
		public ::testing::WithParamInterface<LogMedium>
	{
	};
}

#endif
