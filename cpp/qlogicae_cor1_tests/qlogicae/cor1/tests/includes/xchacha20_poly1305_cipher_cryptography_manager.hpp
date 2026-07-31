#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		XChaCha20Poly1305CipherCryptographyManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class XChaCha20Poly1305CipherCryptographyManagerTest:
		public ::testing::Test
	{
	public:
		XChaCha20Poly1305CipherCryptographyManager
			manager_instance;

		void
			SetUp()
		{
			manager_instance.construct();
			manager_instance.reset();
		}

		void
			TearDown()
		{
			manager_instance.destruct();
			manager_instance.reset();
		}
	};

	class XChaCha20Poly1305CipherCryptographyManagerParameterizedTest:
		public XChaCha20Poly1305CipherCryptographyManagerTest,
		public ::testing::WithParamInterface<std::string>
	{
	};
}

#endif
