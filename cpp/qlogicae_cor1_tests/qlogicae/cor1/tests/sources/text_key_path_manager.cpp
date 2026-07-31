#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextKeyPathManager\
	)

#include "../includes/text_key_path_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TextKeyPathManagerTest, Should_ConvertStringToVector_When_ValidInput)
	{
		const auto result =
			manager.convert_key_path(sample_key_path_string, sample_delimiter);
		ASSERT_EQ(result.size(), 3u);
		EXPECT_EQ(result[0], "root");
		EXPECT_EQ(result[1], "child");
		EXPECT_EQ(result[2], "leaf");
	}

	TEST_F(TextKeyPathManagerTest, Should_ConvertVectorToString_When_ValidInput)
	{
		const auto result =
			manager.convert_key_path(sample_key_path_vector, sample_delimiter);
		EXPECT_EQ(result, sample_key_path_string);
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleEmptyString_When_EmptyInput)
	{
		const auto result =
			manager.convert_key_path("", sample_delimiter);
		EXPECT_TRUE(result.empty());
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleEmptyVector_When_EmptyInput)
	{
		const std::vector<std::string> empty_vector;
		const auto result =
			manager.convert_key_path(empty_vector, sample_delimiter);
		EXPECT_EQ(result, "");
	}

	TEST_F(TextKeyPathManagerTest, Should_UseDefaultDelimiter_When_NotSpecified_StringToVector)
	{
		const auto result =
			manager.convert_key_path(sample_key_path_string);
		EXPECT_EQ(result.size(), 3u);
		EXPECT_EQ(result[0], "root");
		EXPECT_EQ(result[1], "child");
		EXPECT_EQ(result[2], "leaf");
	}

	TEST_F(TextKeyPathManagerTest, Should_UseDefaultDelimiter_When_NotSpecified_VectorToString)
	{
		const auto result =
			manager.convert_key_path(sample_key_path_vector);
		EXPECT_EQ(result, sample_key_path_string);
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleInvalidDelimiter_When_EmptyDelimiter)
	{
		const auto result =
			manager.convert_key_path(sample_key_path_string, "");
		EXPECT_FALSE(result.empty());
		EXPECT_EQ(result[0], sample_key_path_string);
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleEdgeCase_When_SingleElementVector)
	{
		const std::vector<std::string> single_element_vector = { "root" };
		const auto result =
			manager.convert_key_path(single_element_vector, sample_delimiter);
		EXPECT_EQ(result, "root");
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleEdgeCase_When_SingleElementString)
	{
		const std::string single_element_string = "root";
		const auto result =
			manager.convert_key_path(single_element_string, sample_delimiter);
		ASSERT_EQ(result.size(), 1u);
		EXPECT_EQ(result[0], "root");
	}

	TEST_F(TextKeyPathManagerTest, Should_BeExceptionSafe_When_ThrowsInside)
	{
		try
		{
			manager.convert_key_path(sample_key_path_string, sample_delimiter);
		}
		catch (...)
		{
			FAIL() << "Exception should be handled internally";
		}
	}

	TEST_F(TextKeyPathManagerTest, Should_PerformAsynchronously_When_UsingFuture)
	{
		auto future_result =
			std::async(std::launch::async, [this]() mutable {
			return manager.convert_key_path(
				sample_key_path_string,
				sample_delimiter
			);
				});
		auto result = future_result.get();
		EXPECT_EQ(result.size(), 3u);
		EXPECT_EQ(result[2], "leaf");
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleMultithreading_When_ConcurrentAccess)
	{
		std::vector<std::thread> threads;
		std::vector<std::vector<std::string>> results(10);

		for (size_t index = 0; index < 10; ++index)
		{
			threads.emplace_back([this, index, &results]()
			{
				results[index] =
					manager.convert_key_path(sample_key_path_string, sample_delimiter);
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		for (const auto& result : results)
		{
			EXPECT_EQ(result.size(), 3u);
			EXPECT_EQ(result[1], "child");
		}
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleStress_When_HighLoadConversion)
	{
		constexpr size_t iteration_count = 10000;
		for (size_t index = 0; index < iteration_count; ++index)
		{
			const auto vector_result =
				manager.convert_key_path(sample_key_path_string, sample_delimiter);
			EXPECT_EQ(vector_result.size(), 3u);

			const auto string_result =
				manager.convert_key_path(sample_key_path_vector, sample_delimiter);
			EXPECT_EQ(string_result, sample_key_path_string);
		}
	}

	TEST_P(TextKeyPathManagerParameterizedTest, Should_HandleParameterizedTests_When_VariousInputs)
	{
		const auto& param = GetParam();
		const auto vector_result =
			manager.convert_key_path(param.first, param.second);
		const auto string_result =
			manager.convert_key_path(vector_result, param.second);
		EXPECT_EQ(string_result, param.first);
	}

	INSTANTIATE_TEST_CASE_P(
		TextKeyPathManagerParameterSet,
		TextKeyPathManagerParameterizedTest,
		::testing::Values(
			std::make_pair("root.child.leaf", "."),
			std::make_pair("a/b/c", "/"),
			std::make_pair("x|y|z", "|"),
			std::make_pair("", "."),
			std::make_pair("single", ".")
		)
	);

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_ReturnEmptyVector_When_RuntimeExecutionDisabled)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled = false;
		const auto result =
			manager.convert_key_path(sample_key_path_string, sample_delimiter);
		EXPECT_TRUE(result.empty());
		manager.configurations.is_feature_runtime_execution_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_ReturnEmptyString_When_RuntimeExecutionDisabled)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled = false;
		const auto result =
			manager.convert_key_path(sample_key_path_vector, sample_delimiter);
		EXPECT_EQ(result, "");
		manager.configurations.is_feature_runtime_execution_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_SkipMutex_When_ThreadSafetyDisabled_StringToVector)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = false;
		const auto result =
			manager.convert_key_path(sample_key_path_string, sample_delimiter);
		EXPECT_EQ(result.size(), 3u);
		manager.configurations.is_feature_thread_safety_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_SkipMutex_When_ThreadSafetyDisabled_VectorToString)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = false;
		const auto result =
			manager.convert_key_path(sample_key_path_vector, sample_delimiter);
		EXPECT_EQ(result, sample_key_path_string);
		manager.configurations.is_feature_thread_safety_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_IgnoreEdgeCase_When_Disabled_EmptyString)
	{
		manager.configurations.is_feature_edge_case_handling_enabled = true;
		const auto result =
			manager.convert_key_path("", sample_delimiter);
		EXPECT_TRUE(result.empty());
		manager.configurations.is_feature_edge_case_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_IgnoreEdgeCase_When_Disabled_EmptyVector)
	{
		manager.configurations.is_feature_edge_case_handling_enabled = false;
		const std::vector<std::string> empty_vector;
		const auto result =
			manager.convert_key_path(empty_vector, sample_delimiter);
		EXPECT_EQ(result, "");
		manager.configurations.is_feature_edge_case_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_HandleCustomDelimiterFromConfig_StringToVector)
	{
		manager.configurations.delimeter = "/";
		const std::string key_path = "root/child/leaf";
		const auto result =
			manager.convert_key_path(key_path);
		EXPECT_EQ(result.size(), 3u);
		EXPECT_EQ(result[1], "child");
		manager.configurations.delimeter = ".";
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_HandleCustomDelimiterFromConfig_VectorToString)
	{
		manager.configurations.delimeter = "/";
		const std::vector<std::string> vector_path = { "root", "child", "leaf" };
		const auto result =
			manager.convert_key_path(vector_path);
		EXPECT_EQ(result, "root/child/leaf");
		manager.configurations.delimeter = ".";
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_BeExceptionSafe_When_ThreadSafetyDisabled)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = false;
		try
		{
			manager.convert_key_path(sample_key_path_string, sample_delimiter);
			manager.convert_key_path(sample_key_path_vector, sample_delimiter);
		}
		catch (...)
		{
			FAIL();
		}
		manager.configurations.is_feature_thread_safety_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_HandleAsyncConversion_When_RuntimeExecutionDisabled)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled = false;
		auto future_result =
			std::async(std::launch::async, [this]()
			{
				return manager.convert_key_path(sample_key_path_string,
					sample_delimiter);
			});
		auto result = future_result.get();
		EXPECT_TRUE(result.empty());
		manager.configurations.is_feature_runtime_execution_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_HandleAsyncConversion_When_ThreadSafetyDisabled)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = false;
		auto future_result =
			std::async(std::launch::async, [this]()
			{
				return manager.convert_key_path(sample_key_path_string,
					sample_delimiter);
			});
		auto result = future_result.get();
		EXPECT_EQ(result.size(), 3u);
		manager.configurations.is_feature_thread_safety_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_HandleMultithreadedConversion_When_RuntimeExecutionDisabled)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled = false;
		std::vector<std::vector<std::string>> results(5);
		std::vector<std::thread> threads;
		for (size_t index = 0; index < 5; ++index)
		{
			threads.emplace_back([this, index, &results]()
			{
				results[index] =
					manager.convert_key_path(sample_key_path_string,
						sample_delimiter);
			});
		}
		for (auto& thread : threads)
		{
			thread.join();
		}
		for (const auto& result : results)
		{
			EXPECT_TRUE(result.empty());
		}
		manager.configurations.is_feature_runtime_execution_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerConfigurationOverrideTest, Should_HandleMultithreadedConversion_When_ThreadSafetyDisabled)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = false;
		std::vector<std::vector<std::string>> results(5);
		std::vector<std::thread> threads;
		for (size_t index = 0; index < 5; ++index)
		{
			threads.emplace_back([this, index, &results]()
			{
				results[index] =
					manager.convert_key_path(sample_key_path_string,
						sample_delimiter);
			});
		}
		for (auto& thread : threads)
		{
			thread.join();
		}
		for (const auto& result : results)
		{
			EXPECT_EQ(result.size(), 3u);
		}
		manager.configurations.is_feature_thread_safety_handling_enabled = true;
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleDelimiterEdgeCases_When_MultipleConsecutiveDelimiters)
	{
		const std::string input = "root..leaf";
		const auto result = manager.convert_key_path(input, ".");
		ASSERT_EQ(result.size(), 3u);
		EXPECT_EQ(result[0], "root");
		EXPECT_EQ(result[1], "");
		EXPECT_EQ(result[2], "leaf");
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleDelimiterEdgeCases_When_DelimiterAtStartOrEnd)
	{
		const std::string input = ".root.child.";
		const auto result = manager.convert_key_path(input, ".");
		ASSERT_EQ(result.size(), 4u);
		EXPECT_EQ(result[0], "");
		EXPECT_EQ(result[1], "root");
		EXPECT_EQ(result[2], "child");
		EXPECT_EQ(result[3], "");
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleExtremeSizeVector_When_HugeInputVector)
	{
		std::vector<std::string> huge_vector(10000, "node");
		const auto result = manager.convert_key_path(huge_vector, ".");
		EXPECT_EQ(result.size(), 49999u);
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleExtremeSizeString_When_HugeInputString)
	{
		std::string huge_string;
		for (size_t i = 0; i < 10000; ++i)
		{
			huge_string += "node";
			if (i < 9999) huge_string += ".";
		}
		const auto result = manager.convert_key_path(huge_string, ".");
		EXPECT_EQ(result.size(), 10000u);
	}

	TEST_F(TextKeyPathManagerTest, Should_PerformAsyncStress_When_ManyConcurrentAsyncConversions)
	{
		constexpr size_t thread_count = 20;
		constexpr size_t iteration_count = 1000;
		std::vector<std::future<std::vector<std::string>>> futures;

		for (size_t i = 0; i < thread_count; ++i)
		{
			futures.emplace_back(std::async(std::launch::async, [this]()
			{
				std::vector<std::string> last_result;
				for (size_t j = 0; j < iteration_count; ++j)
				{
					last_result = manager.convert_key_path(sample_key_path_string,
						sample_delimiter);
				}
				return last_result;
			}));
		}

		for (auto& future_result : futures)
		{
			const auto result = future_result.get();
			EXPECT_EQ(result.size(), 3u);
			EXPECT_EQ(result[0], "root");
			EXPECT_EQ(result[2], "leaf");
		}
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleEmptyDelimiterEdgeCase_When_EmptyStringAndEmptyDelimiter)
	{
		const auto result = manager.convert_key_path("", "");
		EXPECT_TRUE(result.empty());
	}

	TEST_F(TextKeyPathManagerTest, Should_HandleEmptyDelimiterEdgeCase_When_SingleElementAndEmptyDelimiter)
	{
		const std::string input = "root";
		const auto result = manager.convert_key_path(input, "");
		ASSERT_EQ(result.size(), 1u);
		EXPECT_EQ(result[0], "root");
	}
}

#endif
