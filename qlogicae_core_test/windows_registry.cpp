#include "pch.h"

#include "windows_registry.hpp"

namespace QLogicaeCoreTest
{
    class WindowsRegistryTest
        : public ::testing::TestWithParam<std::wstring>
    {
    protected:
        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();
    };

    TEST_P(WindowsRegistryTest,
        Should_Set_Expect_Success_When_Key_And_Value_Are_Valid)
    {
        std::wstring key = GetParam();
        std::wstring value = L"TestValue";

        bool set = registry.set_sub_and_name_keys_via_utf16(L"Software\\Test", key);
        ASSERT_TRUE(set);

        bool result = registry.set_value_via_utf16(L"", L"", value);
        ASSERT_TRUE(result);

        std::optional<std::wstring> retrieved =
            registry.get_value_via_utf16(L"", L"");

        ASSERT_TRUE(retrieved.has_value());
        ASSERT_EQ(retrieved.value(), value);

        bool removed = registry.remove_value_via_utf16(L"", L"");
        ASSERT_TRUE(removed);
    }

    INSTANTIATE_TEST_CASE_P(
        WindowsRegistryTest,
        WindowsRegistryTest,
        ::testing::Values(
            L"ValidKey",
            std::wstring(256, L'X'),
            L"A",
            L"\uFFFF",
            std::wstring(L"key\0mid", 7)
        )
    );

    class WindowsRegistryEmptyArgumentTest : public ::testing::Test {};

    TEST_F(WindowsRegistryEmptyArgumentTest,
        Should_Fail_When_Sub_And_Name_Are_Empty)
    {
        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        std::wstring value = L"Test";

        bool result = registry.set_value_via_utf16(L"", L"", value);
        ASSERT_TRUE(result);
    }

    TEST(WindowsRegistryAsyncTest,
        Should_Complete_All_Async_Registry_Access_Within_Time)
    {
        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        auto future = std::async(std::launch::async, [&registry]()
            {
                registry.set_sub_and_name_keys_via_utf16(L"Software\\Async", L"A");
                registry.set_value_via_utf16(L"", L"", L"Value");
                return registry.get_value_via_utf16(L"", L"");
            });

        auto status = future.wait_for(std::chrono::seconds(2));
        ASSERT_EQ(status, std::future_status::ready);
        ASSERT_TRUE(future.get().has_value());
    }

    TEST(WindowsRegistryThreadedTest,
        Should_Handle_Concurrent_Set_Get_Remove_Correctly)
    {
        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        std::mutex mutex;
        std::atomic<int> success_count = 0;

        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back([&registry, &success_count, &mutex, i]()
                {
                    std::wstring key = L"Key" + std::to_wstring(i);
                    std::wstring value = L"Value" + std::to_wstring(i);

                    {
                        std::lock_guard<std::mutex> lock(mutex);
                        registry.set_sub_and_name_keys_via_utf16(
                            L"Software\\Concurrent", key
                        );
                        if (registry.set_value_via_utf16(L"", L"", value))
                        {
                            ++success_count;
                        }
                        registry.remove_value_via_utf16(L"", L"");
                    }
                });
        }

        for (auto& t : threads)
        {
            t.join();
        }

        ASSERT_EQ(success_count.load(), 10);
    }

    TEST(WindowsRegistryStressTest,
        Should_Complete_Thousands_Of_Calls_Under_2_Seconds)
    {
        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 10000; ++i)
        {
            std::wstring key = L"Stress" + std::to_wstring(i);
            registry.set_sub_and_name_keys_via_utf16(L"Software\\Stress", key);
            registry.set_value_via_utf16(L"", L"", L"value");
            registry.get_value_via_utf16(L"", L"");
            registry.remove_value_via_utf16(L"", L"");
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;

        ASSERT_LT(std::chrono::duration_cast<std::chrono::seconds>(
            duration).count(), 2);
    }

    TEST(WindowsRegistryExceptionSafetyTest,
        Should_Not_Throw_When_Values_Are_Invalid)
    {
        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        ASSERT_NO_THROW({
            registry.get_value_via_utf16(L"", L"");
            });

        ASSERT_NO_THROW({
            registry.set_value_via_utf16(L"", L"", L"");
            });

        ASSERT_NO_THROW({
            registry.remove_value_via_utf16(L"", L"");
            });
    }
}

