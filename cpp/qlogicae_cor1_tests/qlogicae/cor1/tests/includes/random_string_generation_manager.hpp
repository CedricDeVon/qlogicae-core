#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomStringGenerationManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class RandomStringGenerationManagerTest:
		public ::testing::Test
	{
	protected:
		RandomStringGenerationManager manager_instance;
	};

	class ParameterizedDomainTest:
		public RandomStringGenerationManagerTest,
		public ::testing::WithParamInterface<CharacterDomain>
	{
	};

	class ParameterizedLengthTest:
		public RandomStringGenerationManagerTest,
		public ::testing::WithParamInterface<size_t>
	{
	};

	class ParameterizedOutputTypeTest:
		public RandomStringGenerationManagerTest,
		public ::testing::WithParamInterface<std::string>
	{
	};

	class ParameterizedExcludedSetTest:
		public RandomStringGenerationManagerTest,
		public ::testing::WithParamInterface<std::unordered_set<char>>
	{
	};
}

#endif
