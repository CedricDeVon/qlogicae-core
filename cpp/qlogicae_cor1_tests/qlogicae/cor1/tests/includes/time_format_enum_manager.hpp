#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeFormatEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TimeFormatEnumManagerTest:
		public ::testing::Test
	{
	public:
		TimeFormatEnumManager manager;

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

	class TimeFormatEnumManagerParameterizedTest:
		public TimeFormatEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,TimeFormat>>
	{
	};

	class TimeFormatEnumManagerEnumToStringParameterizedTest:
		public TimeFormatEnumManagerTest,
		public ::testing::WithParamInterface<TimeFormat>
	{
	};
}

#endif
