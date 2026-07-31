#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TemperatureManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	struct
		TemperatureConversionParameters
	{
		double
			input_value;

		TemperatureUnit
			original_unit;

		TemperatureUnit
			target_unit;

		double
			expected_value;
	};

	class
		TemperatureManagerTest:
		public ::testing::Test
	{
	public:
		TemperatureManager
			temperature_manager;

		void
			SetUp() override
		{
			temperature_manager.construct();
			temperature_manager.reset();
		}

		void
			TearDown() override
		{
			temperature_manager.destruct();
			temperature_manager.reset();
		}
	};

	class
		TemperatureManagerParameterizedTest:
		public TemperatureManagerTest,
		public ::testing::WithParamInterface<
		TemperatureConversionParameters
		>
	{
	};
}

#endif
