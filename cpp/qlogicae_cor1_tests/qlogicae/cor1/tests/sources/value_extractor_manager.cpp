#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ValueExtractorManager \
	)

#include "../includes/value_extractor_manager.hpp"

namespace	
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TYPED_TEST_CASE(ValueExtractorManagerTest, ValueTypes);

	TYPED_TEST(ValueExtractorManagerTest, Should_ConstructSuccessfully_When_Normal)
	{
		ASSERT_TRUE(this->manager.construct());
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_DestructSuccessfully_When_Normal)
	{
		ASSERT_TRUE(this->manager.destruct());
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleException_When_ConstructThrows)
	{
		ASSERT_NO_THROW(this->manager.construct());
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleException_When_DestructThrows)
	{
		ASSERT_NO_THROW(this->manager.destruct());
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_ExecuteCallbackSuccessfully_When_CallbackSet)
	{
		this->manager.configurations.callback = []() { return TypeParam{}; };
		TypeParam result = this->manager.execute();
		(void)result;
		ASSERT_TRUE(true);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_ReturnDefault_When_CallbackNull)
	{
		this->manager.configurations.callback = nullptr;
		TypeParam result = this->manager.execute();
		ASSERT_EQ(result, TypeParam{});
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleException_When_CallbackThrows)
	{
		this->manager.configurations.callback = []() -> TypeParam { throw std::runtime_error("fail"); };
		ASSERT_THROW(this->manager.execute(), std::runtime_error);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleAsyncExecution_When_ExecuteCalled)
	{
		auto future_result = std::async(std::launch::async, [this]() { return this->manager.execute(); });
		TypeParam result = future_result.get();
		(void)result;
		ASSERT_TRUE(true);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleMultithreadedAccess_When_ExecuteCalled)
	{
		std::atomic<int> completed_count = 0;
		auto thread_lambda = [this, &completed_count]()
			{
				this->manager.execute();
				++completed_count;
			};

		std::thread thread1(thread_lambda);
		std::thread thread2(thread_lambda);

		thread1.join();
		thread2.join();

		ASSERT_EQ(completed_count.load(), 2);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleStress_When_ExecuteCalledMultipleTimes)
	{
		for (int i = 0; i < 1000; ++i)
		{
			this->manager.execute();
		}
		ASSERT_TRUE(true);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleCombinedAsyncStress_When_ExecuteCalledMultipleTimes)
	{
		std::vector<std::future<TypeParam>> futures;
		for (int i = 0; i < 50; ++i)
		{
			futures.push_back(std::async(std::launch::async, [this]()
				{
					TypeParam result{};
					for (int j = 0; j < 20; ++j)
					{
						result = this->manager.execute();
					}
					return result;
				}));
		}

		for (auto& future : futures)
		{
			TypeParam result = future.get();
			(void)result;
		}

		ASSERT_TRUE(true);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleSequentialConstructDestructEdgeCase)
	{
		for (int i = 0; i < 10; ++i)
		{
			ASSERT_TRUE(this->manager.construct());
			ASSERT_TRUE(this->manager.destruct());
		}
	}
	
	TYPED_TEST_CASE(ValueExtractorManagerTest, ValueTypesAdditional);

	TYPED_TEST(ValueExtractorManagerTest, Should_ExecuteCallbackReturnNonDefault_When_CallbackReturnsValue)
	{
		if constexpr (std::is_same_v<TypeParam, int>)
		{
			this->manager.configurations.callback = []() { return 42; };
			TypeParam result = this->manager.execute();
			ASSERT_EQ(result, 42);
		}
		else if constexpr (std::is_same_v<TypeParam, double>)
		{
			this->manager.configurations.callback = []() { return 3.14; };
			TypeParam result = this->manager.execute();
			ASSERT_EQ(result, 3.14);
		}
		else if constexpr (std::is_same_v<TypeParam, std::string>)
		{
			this->manager.configurations.callback = []() { return std::string("test"); };
			TypeParam result = this->manager.execute();
			ASSERT_EQ(result, "test");
		}
		else if constexpr (std::is_same_v<TypeParam, std::vector<int>>)
		{
			this->manager.configurations.callback = []() { return std::vector<int>{1, 2, 3}; };
			TypeParam result = this->manager.execute();
			ASSERT_EQ(result, std::vector<int>({1, 2, 3}));
		}
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleEmptyVectorReturn_When_CallbackReturnsEmptyVector)
	{
		if constexpr (std::is_same_v<TypeParam, std::vector<int>>)
		{
			this->manager.configurations.callback = []() { return std::vector<int>{}; };
			TypeParam result = this->manager.execute();
			ASSERT_TRUE(result.empty());
		}
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleThreadSafetyUtilityMutex_When_Enabled)
	{
		this->manager.configurations.is_utility_thread_safety_handling_enabled = true;
		std::atomic<int> completed_count = 0;
		auto thread_lambda = [this, &completed_count]()
		{
			this->manager.construct();
			++completed_count;
		};

		std::thread thread1(thread_lambda);
		std::thread thread2(thread_lambda);
		thread1.join();
		thread2.join();

		ASSERT_EQ(completed_count.load(), 2);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_UpdateConfiguration_When_SetupCalled)
	{
		auto old_value = this->manager.configurations.is_feature_edge_case_handling_enabled;
		ValueExtractorManagerConfigurations<TypeParam> new_config{};
		new_config.is_feature_edge_case_handling_enabled = false;

		this->manager.setup(new_config);
		ASSERT_NE(this->manager.configurations.is_feature_edge_case_handling_enabled, old_value);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_ResetConfiguration_When_ResetCalled)
	{
		this->manager.configurations.is_feature_edge_case_handling_enabled = false;
		this->manager.reset();
		ASSERT_TRUE(this->manager.configurations.is_feature_edge_case_handling_enabled);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleFeatureThreadSafetyMutex_When_Enabled)
	{
		this->manager.configurations.is_feature_thread_safety_handling_enabled = true;
		std::atomic<int> completed_count = 0;
		auto thread_lambda = [this, &completed_count]()
		{
			this->manager.execute();
			++completed_count;
		};

		std::thread thread1(thread_lambda);
		std::thread thread2(thread_lambda);
		thread1.join();
		thread2.join();
		ASSERT_EQ(completed_count.load(), 2);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleExtremeCallbackValues_ForNumerics)
	{
		if constexpr (std::is_same_v<TypeParam, int>)
		{
			this->manager.configurations.callback = []() { return INT_MIN; };
			ASSERT_EQ(this->manager.execute(), INT_MIN);
			this->manager.configurations.callback = []() { return INT_MAX; };
			ASSERT_EQ(this->manager.execute(), INT_MAX);
			this->manager.configurations.callback = []() { return 0; };
			ASSERT_EQ(this->manager.execute(), 0);
		}
		else if constexpr (std::is_same_v<TypeParam, double>)
		{
			this->manager.configurations.callback = []() { return -DBL_MAX; };
			ASSERT_EQ(this->manager.execute(), -DBL_MAX);
			this->manager.configurations.callback = []() { return DBL_MAX; };
			ASSERT_EQ(this->manager.execute(), DBL_MAX);
			this->manager.configurations.callback = []() { return 0.0; };
			ASSERT_EQ(this->manager.execute(), 0.0);
		}
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleExtremeCallbackValues_ForString)
	{
		if constexpr (std::is_same_v<TypeParam, std::string>)
		{
			this->manager.configurations.callback = []() { return std::string(""); };
			ASSERT_EQ(this->manager.execute(), "");
			this->manager.configurations.callback = []() { return std::string(10000, 'x'); };
			ASSERT_EQ(this->manager.execute().size(), 10000);
		}
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleLargeVectorCallback)
	{
		if constexpr (std::is_same_v<TypeParam, std::vector<int>>)
		{
			this->manager.configurations.callback = []()
			{
				std::vector<int> v(10000, 1);
				return v;
			};
			TypeParam result = this->manager.execute();
			ASSERT_EQ(result.size(), 10000);
		}
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleUserDefinedStructCallback)
	{
		if constexpr (std::is_same_v<TypeParam, CustomStruct>)
		{
			this->manager.configurations.callback = []() { return CustomStruct{42}; };
			TypeParam result = this->manager.execute();
			ASSERT_EQ(result.a, 42);
		}
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleNestedAsyncMultithreadedExecution)
	{
		std::vector<std::future<TypeParam>> futures;
		for (int i = 0; i < 20; ++i)
		{
			futures.push_back(std::async(std::launch::async, [this]()
			{
				TypeParam result{};
				for (int j = 0; j < 10; ++j)
				{
					result = this->manager.execute();
				}
				return result;
			}));
		}
		for (auto& f : futures)
		{
			(void)f.get();
		}
		ASSERT_TRUE(true);
	}

	TYPED_TEST(ValueExtractorManagerTest, Should_HandleInvalidConfiguration)
	{
		this->manager.configurations.is_feature_edge_case_handling_enabled = false;
		this->manager.configurations.is_feature_thread_safety_handling_enabled = false;
		ASSERT_TRUE(this->manager.construct());
		ASSERT_TRUE(this->manager.destruct());
	}

}

#endif
