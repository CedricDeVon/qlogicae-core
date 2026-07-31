#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomCharacterGenerationManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class RandomCharacterGenerationManagerTest:
		public ::testing::Test
	{
	public:
		RandomCharacterGenerationManagerTest()
		{
		}

		RandomCharacterGenerationManager manager_instance;
	};

	class ParameterizedDomainTest:
		public RandomCharacterGenerationManagerTest,
		public ::testing::WithParamInterface<int>
	{
	};

	class ParameterizedValidDomainTest:
		public RandomCharacterGenerationManagerTest,
		public ::testing::WithParamInterface<CharacterDomain>
	{
	};
}

#endif
