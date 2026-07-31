#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomSeedGenerationManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class RandomSeedGenerationManagerTest:
		public ::testing::Test
	{
	public:
		RandomSeedGenerationManagerTest()
		{
		}

		RandomSeedGenerationManager manager_instance;

		static constexpr std::uint64_t MAX_ITERATIONS =
			static_cast<std::uint64_t>(100000ULL);

		static constexpr std::size_t THREAD_COUNT =
			static_cast<std::size_t>(8U);

		static constexpr std::size_t ITERATION_COUNT =
			static_cast<std::size_t>(50000U);
	};

	class RandomSeedGenerationManagerParameterizedTest:
		public RandomSeedGenerationManagerTest,
		public ::testing::WithParamInterface<std::uint64_t>
	{
	public:
		RandomSeedGenerationManagerParameterizedTest()
		{
		}
	};

	class SplitMix64ParameterizedTest:
		public RandomSeedGenerationManagerTest,
		public ::testing::WithParamInterface<std::uint64_t>
	{
	};

	class DeterministicSeedParameterizedTest:
		public RandomSeedGenerationManagerTest,
		public ::testing::WithParamInterface<std::uint64_t>
	{
	};

	class RandomSeedGenerationManagerEmptySeedTest:
		public RandomSeedGenerationManagerTest,
		public ::testing::WithParamInterface<int>
	{
	public:
		RandomSeedGenerationManagerEmptySeedTest()
		{
		}
	};
}

#endif
