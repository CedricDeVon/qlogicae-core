#include "pch.h"

#include "windows_registry_value_extractor.hpp"

namespace QLogicaeCoreTest
{
    class WindowsRegistryValueExtractorTest
        : public ::testing::TestWithParam<std::string>
    {
    protected:
        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();
    };

    TEST_P(WindowsRegistryValueExtractorTest,
        Should_Extract_Expect_Value_When_Key_Is_Valid)
    {
        std::string sub_key = "Software\\ExtractorTest";
        std::string name_key = GetParam();
        std::string value = "ValidExtractedValue";

        bool set = registry.set_value_via_utf8(sub_key, name_key, value);
        ASSERT_TRUE(set);

        QLogicaeCore::WindowsRegistryValueExtractor extractor(
            sub_key, name_key
        );

        std::optional<std::string> result = extractor.get_value();

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value(), value);

        bool removed = registry.remove_value_via_utf8(sub_key, name_key);
        ASSERT_TRUE(removed);
    }

    INSTANTIATE_TEST_CASE_P(
        WindowsRegistryValueExtractorTest,
        WindowsRegistryValueExtractorTest,
        ::testing::Values(
            "BasicKey",
            "G",
            "\u00FF_key",
            std::string(256, 'Z'),
            std::string("name\0null", 9)
        )
    );

    TEST(WindowsRegistryValueExtractorEmptyTest,
        Should_Not_Throw_When_Sub_And_Name_Are_Empty)
    {
        QLogicaeCore::WindowsRegistryValueExtractor extractor(
            "", ""
        );

        std::optional<std::string> value;
        ASSERT_NO_THROW({
            value = extractor.get_value();
            });

        ASSERT_TRUE(value.has_value());
    }

    TEST(WindowsRegistryValueExtractorKeyTest,
        Should_Return_Correct_Key_When_Constructed)
    {
        std::string sub_key = "Software\\CorrectKey";
        std::string name_key = "Name123";

        QLogicaeCore::WindowsRegistryValueExtractor extractor(
            sub_key, name_key
        );

        ASSERT_EQ(extractor.get_sub_key().value(), sub_key);
        ASSERT_EQ(extractor.get_name_key().value(), name_key);
    }

    TEST(WindowsRegistryValueExtractorAsyncTest,
        Should_Return_Value_Correctly_When_Called_Asynchronously)
    {
        std::string sub_key = "Software\\AsyncTest";
        std::string name_key = "AsyncKey";
        std::string value = "AsyncValue";

        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        bool ok = registry.set_value_via_utf8(sub_key, name_key, value);
        ASSERT_TRUE(ok);

        QLogicaeCore::WindowsRegistryValueExtractor extractor(
            sub_key, name_key
        );

        auto future = std::async(std::launch::async, [&extractor]()
            {
                return extractor.get_value();
            });

        auto status = future.wait_for(std::chrono::seconds(2));
        ASSERT_EQ(status, std::future_status::ready);
        ASSERT_EQ(future.get().value(), value);

        registry.remove_value_via_utf8(sub_key, name_key);
    }

    TEST(WindowsRegistryValueExtractorThreadedTest,
        Should_Allow_Concurrent_Extractions_Without_Errors)
    {
        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        std::string sub_key = "Software\\Threaded";
        std::string name_key = "ThreadedKey";
        std::string value = "ThreadedValue";

        bool set = registry.set_value_via_utf8(sub_key, name_key, value);
        ASSERT_TRUE(set);

        std::atomic<int> success_count = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back([&sub_key, &name_key, &value, &success_count]()
                {
                    QLogicaeCore::WindowsRegistryValueExtractor extractor(
                        sub_key, name_key
                    );

                    std::optional<std::string> result = extractor.get_value();
                    if (result.has_value() && result.value() == value)
                    {
                        ++success_count;
                    }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        ASSERT_EQ(success_count.load(), 10);

        registry.remove_value_via_utf8(sub_key, name_key);
    }

    TEST(WindowsRegistryValueExtractorStressTest,
        Should_Handle_Many_Extractions_Under_2_Seconds)
    {
        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        std::string sub_key = "Software\\StressTest";
        std::string name_key = "StressKey";
        std::string value = "StressValue";

        bool set = registry.set_value_via_utf8(sub_key, name_key, value);
        ASSERT_TRUE(set);

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 10000; ++i)
        {
            QLogicaeCore::WindowsRegistryValueExtractor extractor(
                sub_key, name_key
            );

            std::optional<std::string> result = extractor.get_value();
            ASSERT_TRUE(result.has_value());
            ASSERT_EQ(result.value(), value);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;

        ASSERT_LT(std::chrono::duration_cast<std::chrono::seconds>(
            duration).count(), 2);

        registry.remove_value_via_utf8(sub_key, name_key);
    }

    TEST(WindowsRegistryValueExtractorWideConstructorTest,
        Should_Extract_UTF8_Encoded_Value_When_Constructed_With_Wide_Strings)
    {
        std::wstring sub_key = L"Software\\WideStringTest";
        std::wstring name_key = L"WideNameKey";
        std::wstring value = L"Unicode";

        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        bool ok = registry.set_value_via_utf16(sub_key, name_key, value);
        ASSERT_TRUE(ok);

        QLogicaeCore::WindowsRegistryValueExtractor extractor(
            sub_key, name_key
        );

        std::optional<std::string> result = extractor.get_value();

        ASSERT_TRUE(result.has_value());

        std::wstring decoded = QLogicaeCore::Encoder::get_instance()
            .from_utf8_to_utf16(result.value());

        ASSERT_EQ(decoded, value);

        registry.remove_value_via_utf16(sub_key, name_key);
    }

    TEST(WindowsRegistryValueExtractorCorruptedDataTest,
        Should_Return_Empty_When_Registry_Data_Is_Unreadable)
    {
        std::string sub_key = "Software\\NonExistentSubKey";
        std::string name_key = "MissingKey";

        QLogicaeCore::WindowsRegistryValueExtractor extractor(
            sub_key, name_key
        );

        std::optional<std::string> result = extractor.get_value();

        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value(), "");
    }

    TEST(WindowsRegistryValueExtractorOwnershipTest,
        Should_Return_Consistent_Value_When_Called_Repeatedly)
    {
        std::string sub_key = "Software\\OwnershipTest";
        std::string name_key = "RapidKey";
        std::string value = "RapidValue123";

        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        bool set = registry.set_value_via_utf8(sub_key, name_key, value);
        ASSERT_TRUE(set);

        QLogicaeCore::WindowsRegistryValueExtractor extractor(
            sub_key, name_key
        );

        for (int i = 0; i < 10000; ++i)
        {
            std::optional<std::string> result = extractor.get_value();
            ASSERT_TRUE(result.has_value());
            ASSERT_EQ(result.value(), value);
        }

        bool removed = registry.remove_value_via_utf8(sub_key, name_key);
        ASSERT_TRUE(removed);
    }

    TEST(WindowsRegistryValueExtractorDestructiveTest,
        Should_Return_Empty_When_Registry_Key_Is_Removed_Before_Extraction)
    {
        std::string sub_key = "Software\\DestructiveTest";
        std::string name_key = "DestructKey";
        std::string value = "ThisWillBeDeleted";

        QLogicaeCore::WindowsRegistry& registry =
            QLogicaeCore::WindowsRegistry::hkcu();

        bool set = registry.set_value_via_utf8(sub_key, name_key, value);
        ASSERT_TRUE(set);

        QLogicaeCore::WindowsRegistryValueExtractor extractor(
            sub_key, name_key
        );

        bool removed = registry.remove_value_via_utf8(sub_key, name_key);
        ASSERT_TRUE(removed);

        std::optional<std::string> result = extractor.get_value();
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value(), "");
    }

    TEST(WindowsRegistryValueExtractorKeyConsistencyTest,
        Should_Return_Same_Sub_And_Name_On_Repeated_Calls)
    {
        std::string sub_key = "Software\\KeyCheck";
        std::string name_key = "ConsistentKey";

        QLogicaeCore::WindowsRegistryValueExtractor extractor(
            sub_key, name_key
        );

        for (int i = 0; i < 1000; ++i)
        {
            std::optional<std::string> sub = extractor.get_sub_key();
            std::optional<std::string> name = extractor.get_name_key();

            ASSERT_TRUE(sub.has_value());
            ASSERT_TRUE(name.has_value());

            ASSERT_EQ(sub.value(), sub_key);
            ASSERT_EQ(name.value(), name_key);
        }
    }
}
