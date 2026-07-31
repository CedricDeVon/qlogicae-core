#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Sha256HashCryptographyManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class Sha256HashCryptographyManagerTest: public ::testing::Test
	{
	public:
		Sha256HashCryptographyManager manager_instance;

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

	class Sha256HashCryptographyManagerParameterizedTest:
		public Sha256HashCryptographyManagerTest,
		public ::testing::WithParamInterface<std::string>
	{
	};
}

#endif
