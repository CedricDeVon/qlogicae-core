#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		TimeManagerTest:
		public ::testing::Test
	{
	public:
		TimeManager
			manager_instance;

		TimeManagerTest() = default;

		void
			SetUp() override
		{
			manager_instance.construct();
			manager_instance.reset();
		}

		void
			TearDown() override
		{
			manager_instance.destruct();
			manager_instance.reset();
		}
	};

	class
		TimeManagerFormatParameterizedTest:
		public ::testing::TestWithParam<TimeFormat>
	{
	public:
		TimeManager
			manager_instance;
	};

	class
		TimeManagerScaleParameterizedTest:
		public ::testing::TestWithParam<TimeScaleUnit>
	{
	public:
		TimeManager
			manager_instance;
	};
}

#endif
