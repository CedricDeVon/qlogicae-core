#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		KyberCryptographyAlgorithmEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class KyberCryptographyAlgorithmEnumManagerTest:
		public ::testing::Test
	{
	public:
		KyberCryptographyAlgorithmEnumManager manager;

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

	class KyberCryptographyAlgorithmEnumManagerParameterizedTest:
		public KyberCryptographyAlgorithmEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,KyberCryptographyAlgorithm>>
	{
	};

	class KyberCryptographyAlgorithmEnumManagerEnumToStringParameterizedTest:
		public KyberCryptographyAlgorithmEnumManagerTest,
		public ::testing::WithParamInterface<KyberCryptographyAlgorithm>
	{
	};
}

#endif
