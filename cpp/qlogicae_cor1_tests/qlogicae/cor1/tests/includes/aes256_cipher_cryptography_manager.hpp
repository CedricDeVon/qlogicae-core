#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Aes256CipherCryptographyManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class Aes256CipherCryptographyManagerTest: public ::testing::Test
	{
	public:
		Aes256CipherCryptographyManager manager;

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

	class Aes256CipherCryptographyManagerParameterizedTest:
		public Aes256CipherCryptographyManagerTest,
		public ::testing::WithParamInterface<std::tuple<std::string,std::string,std::string>>
	{
	};

	class MockErrorManager
	{
	public:
		bool handle_error_outputs(const std::string&,const std::string&)
		{
			throw std::runtime_error("mock error");
		}

		bool handle_error_outputs(const std::string&)
		{
			throw std::runtime_error("mock error");
		}

		bool handle_error_outputs(const std::exception&)
		{
			throw std::runtime_error("mock error");
		}
	};

	class Aes256CipherCryptographyManagerExceptionTest:
		public ::testing::Test
	{
	public:
		Aes256CipherCryptographyManager manager;

		MockErrorManager mock_error_manager;

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
