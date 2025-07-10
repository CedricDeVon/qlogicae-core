#include "pch.h"

#include "windows_registry.hpp"

namespace QLogicaeCoreTest
{

    class WindowsRegistryTest : public ::testing::TestWithParam<std::wstring> {
    protected:
        std::wstring test_sub_key = L"Software\\UnitTest";
        std::wstring test_name_key = L"TestName";
        std::wstring test_value = L"TestValue";
        QLogicaeCore::WindowsRegistry& registry = QLogicaeCore::WindowsRegistry::hkcu();

        void SetUp() override {
            registry.set_sub_and_name_keys_via_utf16(test_sub_key, test_name_key);
        }

        void TearDown() override {
            registry.remove_value_via_utf16(test_sub_key, test_name_key);
        }
    };

    TEST_F(WindowsRegistryTest, Should_Expect_SetAndGetValue_When_UsingUtf16) {
        ASSERT_TRUE(registry.set_value_via_utf16(test_sub_key, test_name_key, test_value));
        auto value = registry.get_value_via_utf16(test_sub_key, test_name_key);
        ASSERT_TRUE(value.has_value());
        EXPECT_EQ(value.value(), test_value);
    }

    TEST_F(WindowsRegistryTest, Should_Expect_SetAndGetValue_When_UsingUtf8) {
        std::string sub = "Software\\UnitTest";
        std::string name = "TestName";
        std::string val = "TestValue";

        ASSERT_TRUE(registry.set_value_via_utf8(sub, name, val));
        auto result = registry.get_value_via_utf8(sub, name);
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), val);
    }

    TEST_F(WindowsRegistryTest, Should_Expect_KeyFound_When_ValidKeyExists_Utf8) {
        registry.set_value_via_utf16(test_sub_key, test_name_key, test_value);
        std::string sub = "Software\\UnitTest";
        std::string name = "TestName";

        EXPECT_TRUE(registry.is_sub_and_name_key_path_found_via_utf8(sub, name));
    }

    TEST_F(WindowsRegistryTest, Should_Expect_KeyNotFound_When_KeyMissing_Utf8) {
        std::string sub = "Software\\UnitTest";
        std::string name = "NonExistentKey";

        EXPECT_FALSE(registry.is_sub_and_name_key_path_found_via_utf8(sub, name));
    }

    TEST_F(WindowsRegistryTest, Should_Expect_Removal_When_ValidKeyExists) {
        registry.set_value_via_utf16(test_sub_key, test_name_key, test_value);
        EXPECT_TRUE(registry.remove_value_via_utf16(test_sub_key, test_name_key));
        auto value = registry.get_value_via_utf16(test_sub_key, test_name_key);
        ASSERT_TRUE(value.has_value());
        EXPECT_EQ(value.value(), L"");
    }

    TEST_F(WindowsRegistryTest, Should_Expect_Success_When_SubAndNameKeysSetUtf16) {
        EXPECT_TRUE(registry.set_sub_and_name_keys_via_utf16(test_sub_key, test_name_key));
    }

    TEST_F(WindowsRegistryTest, Should_Expect_Success_When_SubAndNameKeysSetUtf8) {
        EXPECT_TRUE(registry.set_sub_and_name_keys_via_utf8("Software\\UnitTest", "TestName"));
    }

    TEST_F(WindowsRegistryTest, Should_Expect_SingletonBehavior_When_AccessedMultipleTimes) {
        auto& a = QLogicaeCore::WindowsRegistry::hkcu();
        auto& b = QLogicaeCore::WindowsRegistry::hkcu();
        EXPECT_EQ(&a, &b);
    }

    TEST_F(WindowsRegistryTest, Should_Expect_ThreadSafety_When_AccessedConcurrently) {
        registry.set_value_via_utf16(test_sub_key, test_name_key, test_value);
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back([&]() {
                auto val = registry.get_value_via_utf16(test_sub_key, test_name_key);
                EXPECT_TRUE(val.has_value());
                EXPECT_EQ(val.value(), test_value);
                });
        }
        for (auto& t : threads) t.join();
    }

    TEST_F(WindowsRegistryTest, Should_Expect_StressHandling_When_RepeatedAccess) {
        for (int i = 0; i < 1000; ++i) {
            ASSERT_TRUE(registry.set_value_via_utf16(test_sub_key, test_name_key, test_value));
            auto val = registry.get_value_via_utf16(test_sub_key, test_name_key);
            ASSERT_TRUE(val.has_value());
            EXPECT_EQ(val.value(), test_value);
        }
    }

    TEST_F(WindowsRegistryTest, Should_Expect_PerformanceUnderTwoSeconds_When_BulkSetAndGet) {
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < 10000; ++i) {
            registry.set_value_via_utf16(test_sub_key, test_name_key, test_value);
            registry.get_value_via_utf16(test_sub_key, test_name_key);
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        EXPECT_LT(elapsed.count(), 2.0);
    }

    TEST_F(WindowsRegistryTest, Should_Expect_PerformanceUnderOneMillisecond_When_SingleSetAndGet) {
        auto start = std::chrono::high_resolution_clock::now();
        registry.set_value_via_utf16(test_sub_key, test_name_key, test_value);
        registry.get_value_via_utf16(test_sub_key, test_name_key);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        EXPECT_LT(duration.count(), 1000);
    }

    TEST(WindowsRegistryTestDeathTest, Should_Expect_Death_When_ForcedExitAfterSet) {
        EXPECT_DEATH({
            auto& registry = QLogicaeCore::WindowsRegistry::hkcu();
            registry.set_value_via_utf16(L"Software\\UnitTest", L"DEATH_TEST", L"VAL");
            std::exit(1);
            }, "");
    }

    INSTANTIATE_TEST_CASE_P(
        RegistryParameterized,
        WindowsRegistryTest,
        ::testing::Values(
            L"HKCU_Param_1",
            L"HKCU_Param_2",
            L"HKCU_Param_3"
        )
    );
}

