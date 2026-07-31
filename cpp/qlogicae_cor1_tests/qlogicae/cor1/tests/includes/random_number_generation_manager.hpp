#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomNumberGenerationManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class RandomNumberGenerationManagerTest: public ::testing::Test
	{
	public:
		RandomNumberGenerationManagerTest()
		{
		}

		RandomNumberGenerationManager manager_instance;
	};

	struct RandomNumberGenerationManagerParam
	{
		int minimum;
		int maximum;
	};

	class RandomNumberGenerationManagerParameterizedTest:
		public RandomNumberGenerationManagerTest,
		public ::testing::WithParamInterface<RandomNumberGenerationManagerParam>
	{
	};

	struct RandomNumberGenerationManagerEdgeParam
	{
		int maximum;
		std::unordered_set<int> excluded;
	};

	class RandomNumberGenerationManagerEdgeParameterizedTest:
		public RandomNumberGenerationManagerTest,
		public ::testing::WithParamInterface<RandomNumberGenerationManagerEdgeParam>
	{
	};

	class RandomNumberGenerationManagerFloatParameterizedTest:
		public RandomNumberGenerationManagerTest,
		public ::testing::WithParamInterface<std::pair<double,double>>
	{
	};
}

#endif
