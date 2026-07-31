#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EntityActivationManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		EntityActivationManagerTest:
		public ::testing::Test
	{
	public:
		EntityActivationManagerTest()
		{
		}

		EntityActivationManager
			manager;

		int
			entity_value_one =
			1;

		int
			entity_value_two =
			2;

		int
			entity_value_three =
			3;
	};

	class
		EntityActivationManagerParameterizedStatusTest:
		public ::testing::TestWithParam<EntityActivationStatus>
	{
	public:
		EntityActivationManager
			manager;

		int
			entity_value =
			10;
	};
}

#endif
