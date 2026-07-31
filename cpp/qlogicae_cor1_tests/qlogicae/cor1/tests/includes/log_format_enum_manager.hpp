#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogFormatEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class LogFormatEnumManagerTest:
		public ::testing::Test
	{
	public:
		LogFormatEnumManager manager;

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

	class LogFormatEnumManagerParameterizedTest:
		public LogFormatEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,LogFormat>>
	{
	};

	class LogFormatEnumManagerEnumToStringParameterizedTest:
		public LogFormatEnumManagerTest,
		public ::testing::WithParamInterface<LogFormat>
	{
	};
}

#endif
