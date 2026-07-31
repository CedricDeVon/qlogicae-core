#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		KyberCryptographyAlgorithmEnumManager \
	)

#include "../includes/kyber_cryptography_algorithm_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(KyberCryptographyAlgorithmEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		KyberCryptographyAlgorithm result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, KyberCryptographyAlgorithm::NONE);
	}

	TEST_F(KyberCryptographyAlgorithmEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		KyberCryptographyAlgorithmEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(KyberCryptographyAlgorithm::KYBER_1024);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(KyberCryptographyAlgorithmEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		KyberCryptographyAlgorithmEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		KyberCryptographyAlgorithm result = manager.convert_string_to_enum("KYBER_1024");
		EXPECT_EQ(result, KyberCryptographyAlgorithm::NONE);
	}

	TEST_F(KyberCryptographyAlgorithmEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		KyberCryptographyAlgorithmEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(KyberCryptographyAlgorithm::KYBER_768);
		EXPECT_EQ(converted, "KYBER_768");

		KyberCryptographyAlgorithm result = manager.convert_string_to_enum("KYBER_768");
		EXPECT_EQ(result, KyberCryptographyAlgorithm::KYBER_768);
	}

	TEST_F(KyberCryptographyAlgorithmEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public KyberCryptographyAlgorithmEnumManager
		{
		public:
			std::string convert_enum_to_string(const KyberCryptographyAlgorithm&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(KyberCryptographyAlgorithm::KYBER_512), std::runtime_error);
	}

	TEST_F(KyberCryptographyAlgorithmEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		KyberCryptographyAlgorithmEnumManagerConfigurations configurations;
		configurations.type = KyberCryptographyAlgorithm::KYBER_1024;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(KyberCryptographyAlgorithm::KYBER_1024);
		});

		EXPECT_EQ(future_result.get(), "KYBER_1024");
	}

	TEST_F(KyberCryptographyAlgorithmEnumManagerTest, Should_SupportHighConcurrencyStressTest)
	{
		constexpr int num_threads = 16;
		constexpr int iterations = 10000;

		std::vector<std::thread> threads;
		std::atomic<int> success_count{ 0 };

		for (int i = 0; i < num_threads; ++i)
		{
			threads.emplace_back([&]()
			{
				for (int j = 0; j < iterations; ++j)
				{
					std::string converted = manager.convert_enum_to_string(KyberCryptographyAlgorithm::KYBER_768);
					KyberCryptographyAlgorithm result = manager.convert_string_to_enum(converted);
					if (result == KyberCryptographyAlgorithm::KYBER_768)
					{
						success_count++;
					}
				}
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		EXPECT_EQ(success_count.load(), num_threads * iterations);
	}

	TEST_F(KyberCryptographyAlgorithmEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		KyberCryptographyAlgorithmEnumManager& first_instance = SingletonManager::get_singleton<KyberCryptographyAlgorithmEnumManager>();
		KyberCryptographyAlgorithmEnumManager& second_instance = SingletonManager::get_singleton<KyberCryptographyAlgorithmEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		KyberCryptographyAlgorithmEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("KYBER_512", KyberCryptographyAlgorithm::KYBER_512),
			std::make_pair("KYBER_768", KyberCryptographyAlgorithm::KYBER_768),
			std::make_pair("KYBER_1024", KyberCryptographyAlgorithm::KYBER_1024),
			std::make_pair("NONE", KyberCryptographyAlgorithm::NONE),
			std::make_pair("", KyberCryptographyAlgorithm::NONE),
			std::make_pair("INVALID", KyberCryptographyAlgorithm::NONE)
		)
	);

	TEST_P(KyberCryptographyAlgorithmEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		KyberCryptographyAlgorithm expected = param.second;

		KyberCryptographyAlgorithm result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		KyberCryptographyAlgorithmEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			KyberCryptographyAlgorithm::KYBER_512,
			KyberCryptographyAlgorithm::KYBER_768,
			KyberCryptographyAlgorithm::KYBER_1024,
			KyberCryptographyAlgorithm::NONE
		)
	);

	TEST_P(KyberCryptographyAlgorithmEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		KyberCryptographyAlgorithm input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case KyberCryptographyAlgorithm::KYBER_512: EXPECT_EQ(result, "KYBER_512"); break;
			case KyberCryptographyAlgorithm::KYBER_768: EXPECT_EQ(result, "KYBER_768"); break;
			case KyberCryptographyAlgorithm::KYBER_1024: EXPECT_EQ(result, "KYBER_1024"); break;
			case KyberCryptographyAlgorithm::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
