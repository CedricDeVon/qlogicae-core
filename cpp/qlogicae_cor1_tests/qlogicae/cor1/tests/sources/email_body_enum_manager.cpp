#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EmailBodyEnumManager \
	)

#include "../includes/email_body_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(EmailBodyEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		EmailBody result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, EmailBody::NONE);
	}

	TEST_F(EmailBodyEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		EmailBodyEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(EmailBody::PLAIN);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(EmailBodyEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		EmailBodyEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		EmailBody result = manager.convert_string_to_enum("PLAIN");
		EXPECT_EQ(result, EmailBody::NONE);
	}

	TEST_F(EmailBodyEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		EmailBodyEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(EmailBody::HTML);
		EXPECT_EQ(converted, "HTML");

		EmailBody result = manager.convert_string_to_enum("HTML");
		EXPECT_EQ(result, EmailBody::HTML);
	}

	TEST_F(EmailBodyEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public EmailBodyEnumManager
		{
		public:
			std::string convert_enum_to_string(const EmailBody&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(EmailBody::PLAIN), std::runtime_error);
	}

	TEST_F(EmailBodyEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		EmailBodyEnumManagerConfigurations configurations;
		configurations.type = EmailBody::PLAIN;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(EmailBody::PLAIN);
		});

		EXPECT_EQ(future_result.get(), "PLAIN");
	}

	TEST_F(EmailBodyEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(EmailBody::PLAIN);
					EmailBody result = manager.convert_string_to_enum(converted);
					if (result == EmailBody::PLAIN)
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

	TEST_F(EmailBodyEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		EmailBodyEnumManager& first_instance = SingletonManager::get_singleton<EmailBodyEnumManager>();
		EmailBodyEnumManager& second_instance = SingletonManager::get_singleton<EmailBodyEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		EmailBodyEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("HTML", EmailBody::HTML),
			std::make_pair("PLAIN", EmailBody::PLAIN),
			std::make_pair("NONE", EmailBody::NONE),
			std::make_pair("", EmailBody::NONE),
			std::make_pair("INVALID", EmailBody::NONE)
		)
	);

	TEST_P(EmailBodyEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		EmailBody expected = param.second;

		EmailBody result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		EmailBodyEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			EmailBody::HTML,
			EmailBody::PLAIN,
			EmailBody::NONE
		)
	);

	TEST_P(EmailBodyEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		EmailBody input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case EmailBody::HTML: EXPECT_EQ(result, "HTML"); break;
			case EmailBody::PLAIN: EXPECT_EQ(result, "PLAIN"); break;
			case EmailBody::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
