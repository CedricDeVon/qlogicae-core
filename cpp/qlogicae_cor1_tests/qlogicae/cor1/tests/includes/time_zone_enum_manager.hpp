#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeZoneEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TimeZoneEnumManagerTest:
		public ::testing::Test
	{
	public:
		TimeZoneEnumManager manager;

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

	class TimeZoneEnumManagerParameterizedTest:
		public TimeZoneEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,TimeZone>>
	{
	};

	class TimeZoneEnumManagerEnumToStringParameterizedTest:
		public TimeZoneEnumManagerTest,
		public ::testing::WithParamInterface<TimeZone>
	{
	};
}

#endif
