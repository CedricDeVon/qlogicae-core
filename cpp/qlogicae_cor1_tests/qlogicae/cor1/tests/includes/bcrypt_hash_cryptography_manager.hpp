#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		BcryptHashCryptographyManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		BcryptHashCryptographyManagerTest:
		public ::testing::Test
	{
	public:
		BcryptHashCryptographyManagerTest() = default;

		BcryptHashCryptographyManager
			manager;

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

	class
		BcryptHashCryptographyManagerParameterizedTest:
		public ::testing::TestWithParam<
		std::string>
	{
	public:
		BcryptHashCryptographyManager
			manager;

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
}

#endif
