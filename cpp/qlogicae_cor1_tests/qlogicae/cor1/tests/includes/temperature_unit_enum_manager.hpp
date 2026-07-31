#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TemperatureUnitEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TemperatureUnitEnumManagerTest:
		public ::testing::Test
	{
	public:
		TemperatureUnitEnumManager manager;

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

	class TemperatureUnitEnumManagerParameterizedTest:
		public TemperatureUnitEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,TemperatureUnit>>
	{
	};

	class TemperatureUnitEnumManagerEnumToStringParameterizedTest:
		public TemperatureUnitEnumManagerTest,
		public ::testing::WithParamInterface<TemperatureUnit>
	{
	};
}

#endif
