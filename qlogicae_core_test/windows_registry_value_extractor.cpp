#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{

    class WindowsRegistryValueExtractorTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            const std::wstring sub_key = L"Software\\ErwinTest";
            const std::wstring name_key = L"SampleKey";
            const std::wstring value = L"RegistryValue";

            HKEY hkey;
            RegCreateKeyExW(HKEY_CURRENT_USER, sub_key.c_str(), 0, nullptr, 0, KEY_SET_VALUE, nullptr, &hkey, nullptr);
            RegSetValueExW(hkey, name_key.c_str(), 0, REG_SZ,
                reinterpret_cast<const BYTE*>(value.c_str()),
                static_cast<DWORD>((value.size() + 1) * sizeof(wchar_t)));
            RegCloseKey(hkey);
        }

        void TearDown() override
        {
            const std::wstring sub_key = L"Software\\ErwinTest";
            RegDeleteKeyW(HKEY_CURRENT_USER, sub_key.c_str());
        }
    };

    TEST_F(WindowsRegistryValueExtractorTest, Should_Expect_Value_When_ValidUtf8)
    {
        QLogicaeCore::WindowsRegistryValueExtractor extractor("Software\\ErwinTest", "SampleKey");
        auto result = extractor.get_value();
        EXPECT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "RegistryValue");
    }

    TEST_F(WindowsRegistryValueExtractorTest, Should_Expect_Value_When_ValidUtf16)
    {
        QLogicaeCore::WindowsRegistryValueExtractor extractor(L"Software\\ErwinTest", L"SampleKey");
        auto result = extractor.get_value();
        EXPECT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "RegistryValue");
    }

    TEST_F(WindowsRegistryValueExtractorTest, Should_Expect_Empty_When_KeyMissing)
    {
        QLogicaeCore::WindowsRegistryValueExtractor extractor(L"Software\\ErwinTest", L"MissingKey");
        auto result = extractor.get_value();
        EXPECT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "");
    }

    TEST_F(WindowsRegistryValueExtractorTest, Should_Expect_Empty_When_SubKeyMissing)
    {
        QLogicaeCore::WindowsRegistryValueExtractor extractor(L"Software\\DoesNotExist", L"SampleKey");
        auto result = extractor.get_value();
        EXPECT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "");
    }

    TEST_F(WindowsRegistryValueExtractorTest, Should_Expect_NoThrow_When_AsyncGet)
    {
        QLogicaeCore::WindowsRegistryValueExtractor extractor("Software\\ErwinTest", "SampleKey");
        auto future = std::async(std::launch::async, [&]() { return extractor.get_value(); });
        EXPECT_NO_THROW(future.get());
    }

    TEST_F(WindowsRegistryValueExtractorTest, Should_Expect_Correct_When_UsedMultithreaded)
    {
        QLogicaeCore::WindowsRegistryValueExtractor extractor("Software\\ErwinTest", "SampleKey");
        std::vector<std::thread> threads;
        std::atomic<int> match = 0;

        for (int i = 0; i < 32; ++i)
        {
            threads.emplace_back([&]()
                {
                    if (extractor.get_value().value() == "RegistryValue") ++match;
                });
        }

        for (auto& t : threads) t.join();
        EXPECT_EQ(match.load(), 32);
    }

    TEST_F(WindowsRegistryValueExtractorTest, Should_Expect_ThousandCalls_When_Stressed)
    {
        QLogicaeCore::WindowsRegistryValueExtractor extractor("Software\\ErwinTest", "SampleKey");
        auto start = std::chrono::steady_clock::now();
        int count = 0;

        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(2))
        {
            extractor.get_value();
            ++count;
        }

        EXPECT_GT(count, 1000);
    }

    class WindowsRegistryValueExtractorParameterizedTest : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {};

    TEST_P(WindowsRegistryValueExtractorParameterizedTest, Should_Expect_Empty_When_NonexistentKeyCombo)
    {
        const auto& [sub_key, name_key] = GetParam();
        QLogicaeCore::WindowsRegistryValueExtractor extractor(sub_key, name_key);
        auto result = extractor.get_value();
        EXPECT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "");
    }

    INSTANTIATE_TEST_CASE_P(
        InvalidCombos,
        WindowsRegistryValueExtractorParameterizedTest,
        ::testing::Values(
            std::make_tuple("Software\\Invalid1", "Key1"),
            std::make_tuple("Software\\Invalid2", "Key2"),
            std::make_tuple("Software\\Invalid3", "Key3")
        )
    );

    TEST_F(WindowsRegistryValueExtractorTest, Should_Expect_OneMillisecond_Execution_When_Queried)
    {
        QLogicaeCore::WindowsRegistryValueExtractor extractor("Software\\ErwinTest", "SampleKey");
        auto start = std::chrono::steady_clock::now();
        extractor.get_value();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start).count();
        EXPECT_LT(duration, 1000);
    }
}
