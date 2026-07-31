#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyAlgorithmEnumManager \
	)

#include "../includes/dilithium_cryptography_algorithm_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(DilithiumCryptographyAlgorithmEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		DilithiumCryptographyAlgorithm result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, DilithiumCryptographyAlgorithm::NONE);
	}

	TEST_F(DilithiumCryptographyAlgorithmEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		DilithiumCryptographyAlgorithmEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(DilithiumCryptographyAlgorithm::DILITHIUM_5);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(DilithiumCryptographyAlgorithmEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		DilithiumCryptographyAlgorithmEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		DilithiumCryptographyAlgorithm result = manager.convert_string_to_enum("DILITHIUM_5");
		EXPECT_EQ(result, DilithiumCryptographyAlgorithm::NONE);
	}

	TEST_F(DilithiumCryptographyAlgorithmEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		DilithiumCryptographyAlgorithmEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(DilithiumCryptographyAlgorithm::DILITHIUM_3);
		EXPECT_EQ(converted, "DILITHIUM_3");

		DilithiumCryptographyAlgorithm result = manager.convert_string_to_enum("DILITHIUM_3");
		EXPECT_EQ(result, DilithiumCryptographyAlgorithm::DILITHIUM_3);
	}

	TEST_F(DilithiumCryptographyAlgorithmEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public DilithiumCryptographyAlgorithmEnumManager
		{
		public:
			std::string convert_enum_to_string(const DilithiumCryptographyAlgorithm&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(DilithiumCryptographyAlgorithm::DILITHIUM_2), std::runtime_error);
	}

	TEST_F(DilithiumCryptographyAlgorithmEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		DilithiumCryptographyAlgorithmEnumManagerConfigurations configurations;
		configurations.type = DilithiumCryptographyAlgorithm::DILITHIUM_5;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(DilithiumCryptographyAlgorithm::DILITHIUM_5);
		});

		EXPECT_EQ(future_result.get(), "DILITHIUM_5");
	}

	TEST_F(DilithiumCryptographyAlgorithmEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(DilithiumCryptographyAlgorithm::DILITHIUM_3);
					DilithiumCryptographyAlgorithm result = manager.convert_string_to_enum(converted);
					if (result == DilithiumCryptographyAlgorithm::DILITHIUM_3)
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

	TEST_F(DilithiumCryptographyAlgorithmEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		DilithiumCryptographyAlgorithmEnumManager& first_instance = SingletonManager::get_singleton<DilithiumCryptographyAlgorithmEnumManager>();
		DilithiumCryptographyAlgorithmEnumManager& second_instance = SingletonManager::get_singleton<DilithiumCryptographyAlgorithmEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		DilithiumCryptographyAlgorithmEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("DILITHIUM_2", DilithiumCryptographyAlgorithm::DILITHIUM_2),
			std::make_pair("DILITHIUM_3", DilithiumCryptographyAlgorithm::DILITHIUM_3),
			std::make_pair("DILITHIUM_5", DilithiumCryptographyAlgorithm::DILITHIUM_5),
			std::make_pair("NONE", DilithiumCryptographyAlgorithm::NONE),
			std::make_pair("", DilithiumCryptographyAlgorithm::NONE),
			std::make_pair("INVALID", DilithiumCryptographyAlgorithm::NONE)
		)
	);

	TEST_P(DilithiumCryptographyAlgorithmEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		DilithiumCryptographyAlgorithm expected = param.second;

		DilithiumCryptographyAlgorithm result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		DilithiumCryptographyAlgorithmEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			DilithiumCryptographyAlgorithm::DILITHIUM_2,
			DilithiumCryptographyAlgorithm::DILITHIUM_3,
			DilithiumCryptographyAlgorithm::DILITHIUM_5,
			DilithiumCryptographyAlgorithm::NONE
		)
	);

	TEST_P(DilithiumCryptographyAlgorithmEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		DilithiumCryptographyAlgorithm input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case DilithiumCryptographyAlgorithm::DILITHIUM_2: EXPECT_EQ(result, "DILITHIUM_2"); break;
			case DilithiumCryptographyAlgorithm::DILITHIUM_3: EXPECT_EQ(result, "DILITHIUM_3"); break;
			case DilithiumCryptographyAlgorithm::DILITHIUM_5: EXPECT_EQ(result, "DILITHIUM_5"); break;
			case DilithiumCryptographyAlgorithm::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
