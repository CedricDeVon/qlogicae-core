#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyAlgorithmEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class DilithiumCryptographyAlgorithmEnumManagerTest:
		public ::testing::Test
	{
	public:
		DilithiumCryptographyAlgorithmEnumManager manager;

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

	class DilithiumCryptographyAlgorithmEnumManagerParameterizedTest:
		public DilithiumCryptographyAlgorithmEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,DilithiumCryptographyAlgorithm>>
	{
	};

	class DilithiumCryptographyAlgorithmEnumManagerEnumToStringParameterizedTest:
		public DilithiumCryptographyAlgorithmEnumManagerTest,
		public ::testing::WithParamInterface<DilithiumCryptographyAlgorithm>
	{
	};
}

#endif
