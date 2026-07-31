#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomValueGenerationManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class RandomValueGenerationManagerTest:
		public ::testing::Test
	{
	public:
		RandomValueGenerationManagerTest()
		{
		}

		RandomValueGenerationManager
			random_value_manager_instance;
	};

	class RandomValueGenerationManagerParameterizedTest:
		public RandomValueGenerationManagerTest,
		public ::testing::WithParamInterface<size_t>
	{
	};
}

#endif
