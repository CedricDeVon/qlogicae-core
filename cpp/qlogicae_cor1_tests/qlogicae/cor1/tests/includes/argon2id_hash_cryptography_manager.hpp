#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Argon2idHashCryptographyManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		Argon2idHashCryptographyManagerTest:
		public ::testing::Test
	{
	public:
		Argon2idHashCryptographyManager
			manager_instance;

		Argon2idHashCryptographyManagerTest()
		{
		}

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
		Argon2idHashCryptographyManagerParameterizedTest:
		public Argon2idHashCryptographyManagerTest,
		public ::testing::WithParamInterface<std::string>
	{

	};
}

#endif
