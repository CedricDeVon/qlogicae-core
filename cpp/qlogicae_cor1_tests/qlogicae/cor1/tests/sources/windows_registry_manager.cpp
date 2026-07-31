#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsRegistryManager \
	)

#include "../includes/windows_registry_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(WindowsRegistryManagerTest, Should_SetAndGetValue_When_NormalString)
	{
		std::wstring value = L"TestValue";
		ASSERT_TRUE(manager.set_value_via_wstring(value));
		ASSERT_EQ(manager.get_value_via_wstring(), value);
	}

	TEST_F(WindowsRegistryManagerTest, Should_OverwriteValue_When_SetTwice)
	{
		std::wstring first_value = L"First";
		std::wstring second_value = L"Second";
		ASSERT_TRUE(manager.set_value_via_wstring(first_value));
		ASSERT_TRUE(manager.set_value_via_wstring(second_value));
		ASSERT_EQ(manager.get_value_via_wstring(), second_value);
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleEmptyValue_When_SetEmptyString)
	{
		std::wstring empty_value = L"";
		ASSERT_FALSE(manager.set_value_via_wstring(empty_value));
		ASSERT_FALSE(manager.get_value_via_wstring().empty());
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleLargeValue_When_SetLargeString)
	{
		std::wstring large_value(32000, L'A');
		ASSERT_TRUE(manager.set_value_via_wstring(large_value));
		ASSERT_EQ(manager.get_value_via_wstring(), large_value);
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleUTF8Multibyte_When_SetMultibyteString)
	{
		std::wstring multibyte_value = L"漢字𐍈テスト";
		ASSERT_TRUE(manager.set_value_via_wstring(multibyte_value));
		ASSERT_EQ(manager.get_value_via_wstring(), multibyte_value);
	}

	TEST_F(WindowsRegistryManagerTest, Should_SetAndGetValueString_When_UsingStringInterface)
	{
		std::string value = "TestString";
		ASSERT_TRUE(manager.set_value_via_string(value));
		ASSERT_EQ(manager.get_value_via_string(), value);
	}

	TEST_F(WindowsRegistryManagerTest, Should_OverwriteValueString_When_SetTwiceStringInterface)
	{
		std::string first_value = "First";
		std::string second_value = "Second";
		ASSERT_TRUE(manager.set_value_via_string(first_value));
		ASSERT_TRUE(manager.set_value_via_string(second_value));
		ASSERT_EQ(manager.get_value_via_string(), second_value);
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleMultithreadedAccess_When_SetAndGetConcurrently)
	{
		std::wstring first_value = L"Thread1";
		std::wstring second_value = L"Thread2";

		std::thread thread1([&]() { manager.set_value_via_wstring(first_value); });
		std::thread thread2([&]() { manager.set_value_via_wstring(second_value); });

		thread1.join();
		thread2.join();

		std::wstring result = manager.get_value_via_wstring();
		ASSERT_TRUE(result == first_value || result == second_value);
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleAsyncAccess_When_SetAndGetAsync)
	{
		std::wstring async_value = L"AsyncValue";

		auto future_set = std::async(std::launch::async, [&]() {
			return manager.set_value_via_wstring(async_value);
		});

		ASSERT_TRUE(future_set.get());

		auto future_get = std::async(std::launch::async, [&]() {
			return manager.get_value_via_wstring();
		});

		ASSERT_EQ(future_get.get(), async_value);
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleStressTest_When_SetManyValues)
	{
		for (int i = 0; i < 100; ++i)
		{
			std::wstring value = L"Value" + std::to_wstring(i);
			ASSERT_TRUE(manager.set_value_via_wstring(value));
			ASSERT_EQ(manager.get_value_via_wstring(), value);
		}
	}

	INSTANTIATE_TEST_CASE_P(
		InvalidKeys,
		WindowsRegistryManagerInvalidInputTest,
		::testing::Values(L"", L" ", L"\t")
	);

	TEST_P(WindowsRegistryManagerInvalidInputTest, Should_HandleInvalidKeys_When_SetValue)
	{
		std::wstring param = GetParam();
		ASSERT_NO_THROW(manager.set_value_via_wstring(param));
	}

	TEST_F(WindowsRegistryManagerTest, Should_ReturnTrue_When_PathFound)
	{
		std::wstring value = L"Exists";
		ASSERT_TRUE(manager.set_value_via_wstring(value));
		ASSERT_TRUE(manager.is_path_found_via_wstring());
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleGetValuesViaWstring_WithMultipleValues)
	{
		manager.set_value_via_wstring(L"Value1");
		manager.set_value(HKEY_CURRENT_USER, manager.configurations.sub_key, L"ExtraKey", L"ExtraValue");
		auto result = manager.get_values_via_wstring();
		ASSERT_GE(result.size(), static_cast<size_t>(2));
		ASSERT_EQ(result[manager.configurations.name_key], L"Value1");
		ASSERT_EQ(result[L"ExtraKey"], L"ExtraValue");
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleGetValuesViaString_WithMultipleValues)
	{
		manager.set_value_via_string("Value1");
		manager.set_value(HKEY_CURRENT_USER, manager.configurations.sub_key, L"ExtraKey", L"ExtraValue");
		auto result = manager.get_values_via_string();
		ASSERT_GE(result.size(), static_cast<size_t>(2));
		ASSERT_EQ(result["ExtraKey"], "ExtraValue");
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleCrossEncodingGet_When_SetWstringGetString)
	{
		std::wstring value = L"CrossValue";
		manager.set_value_via_wstring(value);
		ASSERT_EQ(manager.get_value_via_wstring(), value);
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleCrossEncodingGet_When_SetStringGetWstring)
	{
		std::string value = "CrossValue";
		manager.set_value_via_string(value);
		ASSERT_EQ(manager.get_value_via_wstring(), L"CrossValue");
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleEmptySubKey)
	{
		manager.configurations.sub_key = L"";
		ASSERT_FALSE(manager.set_value_via_wstring(L"EmptyKey"));
		ASSERT_EQ(manager.get_value_via_wstring(), L"");
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleNonExistentSubKey)
	{
		std::wstring value = manager.get_value(HKEY_CURRENT_USER, L"NonExistentKey", L"Name");
		ASSERT_TRUE(value.empty());
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleThreadSafetyFlagsDisabled)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = false;
		manager.configurations.is_feature_thread_safety_handling_enabled = false;
		std::wstring value = L"ThreadSafetyOff";
		ASSERT_TRUE(manager.set_value_via_wstring(value));
		ASSERT_EQ(manager.get_value_via_wstring(), value);
	}

	TEST_F(WindowsRegistryManagerTest, Should_HandleConstructDestructIdempotency)
	{
		ASSERT_TRUE(manager.construct());
		ASSERT_TRUE(manager.construct());
		ASSERT_TRUE(manager.destruct());
		ASSERT_TRUE(manager.destruct());
	}
}

#endif

/*
TEST_F(WindowsRegistryManagerTest, Should_ReturnFalse_When_PathNotFound)
{
	manager.remove_value_via_wstring();
	ASSERT_FALSE(manager.is_path_found_via_wstring());
}
*/

/*
TEST_F(WindowsRegistryManagerTest, Should_RemoveValue_When_KeyExists)
{
	std::wstring value = L"TempValue";
	ASSERT_TRUE(manager.set_value_via_wstring(value));
	ASSERT_TRUE(manager.remove_value_via_wstring());
	ASSERT_EQ(manager.get_value_via_wstring(), L"");
}
*/
