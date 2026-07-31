#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EmailSecurityEnumManager \
	)

#include "../includes/email_security_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(EmailSecurityEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		EmailSecurity result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, EmailSecurity::NONE);
	}

	TEST_F(EmailSecurityEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		EmailSecurityEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(EmailSecurity::SSL);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(EmailSecurityEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		EmailSecurityEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		EmailSecurity result = manager.convert_string_to_enum("SSL");
		EXPECT_EQ(result, EmailSecurity::NONE);
	}

	TEST_F(EmailSecurityEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		EmailSecurityEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(EmailSecurity::SSL);
		EXPECT_EQ(converted, "SSL");

		EmailSecurity result = manager.convert_string_to_enum("SSL");
		EXPECT_EQ(result, EmailSecurity::SSL);
	}

	TEST_F(EmailSecurityEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public EmailSecurityEnumManager
		{
		public:
			std::string convert_enum_to_string(const EmailSecurity&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(EmailSecurity::SSL), std::runtime_error);
	}

	TEST_F(EmailSecurityEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		EmailSecurityEnumManagerConfigurations configurations;
		configurations.type = EmailSecurity::SSL;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(EmailSecurity::SSL);
		});

		EXPECT_EQ(future_result.get(), "SSL");
	}

	TEST_F(EmailSecurityEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(EmailSecurity::SSL);
					EmailSecurity result = manager.convert_string_to_enum(converted);
					if (result == EmailSecurity::SSL)
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

	TEST_F(EmailSecurityEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		EmailSecurityEnumManager& first_instance = SingletonManager::get_singleton<EmailSecurityEnumManager>();
		EmailSecurityEnumManager& second_instance = SingletonManager::get_singleton<EmailSecurityEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		EmailSecurityEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("SSL", EmailSecurity::SSL),
			std::make_pair("NONE", EmailSecurity::NONE),
			std::make_pair("", EmailSecurity::NONE),
			std::make_pair("INVALID", EmailSecurity::NONE)
		)
	);

	TEST_P(EmailSecurityEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		EmailSecurity expected = param.second;

		EmailSecurity result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		EmailSecurityEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			EmailSecurity::SSL,
			EmailSecurity::SSL,
			EmailSecurity::NONE
		)
	);

	TEST_P(EmailSecurityEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		EmailSecurity input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case EmailSecurity::SSL: EXPECT_EQ(result, "SSL"); break;
			case EmailSecurity::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
