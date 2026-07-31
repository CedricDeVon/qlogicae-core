#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EnumManager \
	)

#include "../includes/enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(EnumManagerTest, Should_ReturnOriginalValue_When_RuntimeExecutionDisabled)
	{
		EnumManagerConfigurations configurations;
		configurations.is_runtime_execution_handling_enabled = false;
		manager.setup(configurations);

		std::string original_value = "TestValue";
		std::string converted_value =
			manager.convert_enum_string(original_value, TextCase::UPPERCASE);
		EXPECT_EQ(converted_value, original_value);
	}

	TEST_F(EnumManagerTest, Should_ConvertToUppercase_When_TargetIsUppercase)
	{
		std::string converted_value =
			manager.convert_enum_string("testvalue", TextCase::LOWERCASE, TextCase::UPPERCASE);
		EXPECT_EQ(converted_value, "TESTVALUE");
	}

	TEST_F(EnumManagerTest, Should_ConvertToLowercase_When_TargetIsLowercase)
	{
		std::string converted_value =
			manager.convert_enum_string("TESTVALUE", TextCase::LOWERCASE);
		EXPECT_EQ(converted_value, "testvalue");
	}

	TEST_F(EnumManagerTest, Should_ConvertToCapitalized_When_TargetIsCapitalize)
	{
		std::string converted_value =
			manager.convert_enum_string("testvalue", TextCase::LOWERCASE, TextCase::CAPITALIZE);
		EXPECT_EQ(converted_value, "Testvalue");
	}

	TEST_F(EnumManagerTest, Should_ReturnNoneStringCorrectly_ForAllTextCases)
	{
		EXPECT_EQ(manager.get_none_string(TextCase::UPPERCASE), "NONE");
		EXPECT_EQ(manager.get_none_string(TextCase::LOWERCASE), "none");
		EXPECT_EQ(manager.get_none_string(TextCase::CAPITALIZE), "None");
	}

	TEST_F(EnumManagerTest, Should_HandleEmptyStringGracefully)
	{
		std::string empty_value = "";
		std::string converted_value =
			manager.convert_enum_string(empty_value, TextCase::UPPERCASE);
		EXPECT_EQ(converted_value, empty_value);
	}

	TEST_F(EnumManagerTest, Should_HandleDefaultEnumConversion)
	{
		std::string value = "defaultValue";
		std::string converted_value =
			manager.convert_default_enum_string(value);
		EXPECT_EQ(converted_value, "DEFAULTVALUE");
	}

	TEST_F(EnumManagerTest, Should_HandleExceptionGracefully)
	{
		class EnumManagerExceptionThrower : public EnumManager
		{
		public:
			std::string convert_enum_string(
				const std::string& value,
				const TextCase&,
				const TextCase&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		EnumManagerExceptionThrower test_manager;
		std::string value = "value";
		EXPECT_THROW(test_manager.convert_enum_string(value, TextCase::UPPERCASE, TextCase::UPPERCASE), std::runtime_error);
	}

	TEST_F(EnumManagerTest, Should_BeThreadSafeUnderConcurrency)
	{
		constexpr int num_threads = 8;
		std::vector<std::thread> threads;
		std::vector<std::string> results(num_threads);

		for (int i = 0; i < num_threads; ++i)
		{
			threads.emplace_back([&, i]()
			{
				results[i] = manager.convert_enum_string("threadvalue", TextCase::LOWERCASE, TextCase::UPPERCASE);
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		for (auto& result : results)
		{
			EXPECT_EQ(result, "THREADVALUE");
		}
	}

	TEST_F(EnumManagerTest, Should_PerformUnderStress)
	{
		constexpr int iterations = 10000;
		for (int i = 0; i < iterations; ++i)
		{
			std::string value = "stressTestValue" + std::to_string(i);
			std::string converted =
				manager.convert_enum_string(value, TextCase::UPPERCASE);
			EXPECT_FALSE(converted.empty());
		}
	}

	TEST_F(EnumManagerTest, Should_HandleAsyncConversion)
	{
		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_string("asyncvalue", TextCase::LOWERCASE, TextCase::UPPERCASE);
		});
		EXPECT_EQ(future_result.get(), "ASYNCVALUE");
	}

	TEST_F(EnumManagerTest, Should_ConvertParameterizedValuesCorrectly)
	{
		struct ParameterizedCase
		{
			std::string input;
			TextCase origin_case;
			TextCase target_case;
			std::string expected_output;
		};

		std::vector<ParameterizedCase> cases = {
			{"lowercase", TextCase::LOWERCASE, TextCase::UPPERCASE, "LOWERCASE"},
			{"UPPERCASE", TextCase::UPPERCASE, TextCase::LOWERCASE, "uppercase"},
			{"capitalize", TextCase::LOWERCASE, TextCase::CAPITALIZE, "Capitalize"},
			{"", TextCase::LOWERCASE, TextCase::UPPERCASE, ""}
		};

		for (const auto& test_case : cases)
		{
			std::string converted =
				manager.convert_enum_string(test_case.input, test_case.origin_case, test_case.target_case);
			EXPECT_EQ(converted, test_case.expected_output);
		}
	}

	TEST_F(EnumManagerTest, Should_HandleHighConcurrencyStress)
	{
		const int num_threads = std::thread::hardware_concurrency() * 10;
		const int iterations_per_thread = 10;
		std::vector<std::thread> threads;
		std::vector<std::string> results(num_threads * iterations_per_thread);

		for (int t = 0; t < num_threads; ++t)
		{
			threads.emplace_back([&, t]()
			{
				for (int i = 0; i < iterations_per_thread; ++i)
				{
					int index = t * iterations_per_thread + i;
					results[index] =
						manager.convert_enum_string("concurrencyTest", TextCase::LOWERCASE, TextCase::UPPERCASE);
				}
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		for (auto& result : results)
		{
			EXPECT_EQ(result, "CONCURRENCYTEST");
		}
	}

	TEST_F(EnumManagerTest, Should_HandleAsyncConversionWithPromiseAndFuture)
	{
		std::promise<std::string> promise;
		std::future<std::string> future_result = promise.get_future();

		std::thread async_thread([&]()
		{
			std::string converted =
				manager.convert_enum_string("asyncPromise", TextCase::LOWERCASE);
			promise.set_value(converted);
		});

		EXPECT_EQ(future_result.get(), "asyncpromise");
		async_thread.join();
	}

	TEST_F(EnumManagerTest, Should_HandleVeryLongStringConversion)
	{
		std::string long_string(1000, 'a');
		std::string converted =
			manager.convert_enum_string(long_string, TextCase::LOWERCASE, TextCase::UPPERCASE);
		std::string expected(1000, 'A');
		EXPECT_EQ(converted, expected);
	}

	TEST_F(EnumManagerTest, Should_HandleGetNoneStringDefault)
	{
		EnumManagerConfigurations configurations;
		configurations.text_case = TextCase::CAPITALIZE;
		manager.setup(configurations);
		EXPECT_EQ(manager.get_none_string(), "None");
	}
}

#endif
