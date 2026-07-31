#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeScaleUnitEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TimeScaleUnitEnumManagerTest:
		public ::testing::Test
	{
	public:
		TimeScaleUnitEnumManager manager;

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

	class TimeScaleUnitEnumManagerParameterizedTest:
		public TimeScaleUnitEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,TimeScaleUnit>>
	{
	};

	class TimeScaleUnitEnumManagerEnumToStringParameterizedTest:
		public TimeScaleUnitEnumManagerTest,
		public ::testing::WithParamInterface<TimeScaleUnit>
	{
	};
}

#endif
