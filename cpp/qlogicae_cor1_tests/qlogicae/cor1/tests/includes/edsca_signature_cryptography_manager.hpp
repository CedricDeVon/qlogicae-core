#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EdscaSignatureCryptographyManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		EdscaSignatureCryptographyManagerTest:
		public ::testing::Test
	{
	public:
		EdscaSignatureCryptographyManagerTest()
		{
			manager.construct();
		}

		EdscaSignatureCryptographyManager
			manager;

		std::vector<std::uint8_t>
			text =
			std::vector<std::uint8_t>
		{
			static_cast<std::uint8_t>(1),
			static_cast<std::uint8_t>(2),
			static_cast<std::uint8_t>(3)
		};

		std::vector<std::uint8_t>
			public_key =
			std::vector<std::uint8_t>
			(
				crypto_sign_PUBLICKEYBYTES
			);

		std::vector<std::uint8_t>
			private_key =
			std::vector<std::uint8_t>
			(
				crypto_sign_SECRETKEYBYTES
			);
	};

	class
		EdscaSignatureCryptographyManagerParameterizedTest:
		public ::testing::TestWithParam<std::vector<std::uint8_t>>
	{
	public:
		EdscaSignatureCryptographyManagerParameterizedTest()
		{
			manager.construct();
		}

		EdscaSignatureCryptographyManager
			manager;

		std::vector<std::uint8_t>
			public_key =
			std::vector<std::uint8_t>
			(
				crypto_sign_PUBLICKEYBYTES
			);

		std::vector<std::uint8_t>
			private_key =
			std::vector<std::uint8_t>
			(
				crypto_sign_SECRETKEYBYTES
			);
	};
}

#endif
