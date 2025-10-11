#include "pch.hpp"

#include "qlogicae/core/dot_env_value_extractor.hpp"

namespace QLogicaeCoreTest
{
    class DotEnvValueExtractorTest : public ::testing::TestWithParam<std::wstring>
    {
    protected:
        void SetUp() override {}
        void TearDown() override {}
    };

    class DotEnvValueExtractorEmptyArgumentTest : public ::testing::Test
    {
    };

    class DotEnvValueExtractorEdgeKeyTest
        : public ::testing::TestWithParam<std::wstring>
    {
    };

    TEST_P(DotEnvValueExtractorTest, Should_Return_Correct_Value_When_Key_Is_Valid)
    {
        std::wstring key = GetParam();
        std::wstring value = L"ExtractorTestValue";
        QLogicaeCore::DotEnv::get_instance().set(key.c_str(), value.c_str());
        QLogicaeCore::DotEnvValueExtractor extractor(key);
        std::optional<std::string> result = extractor.get_value();
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value(), QLogicaeCore::Encoder::get_instance().from_utf16_to_utf8(value));
        QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
    }

    TEST_P(DotEnvValueExtractorTest, Should_Work_Asynchronously_When_Value_Extracted)
    {
        std::wstring key = GetParam();
        std::wstring value = L"AsyncExtract";
        QLogicaeCore::DotEnv::get_instance().set(key.c_str(), value.c_str());
        std::future<std::optional<std::string>> future = std::async(std::launch::async, [key]() {
            QLogicaeCore::DotEnvValueExtractor extractor(key);
            return extractor.get_value();
            });
        std::optional<std::string> result = future.get();
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value(), QLogicaeCore::Encoder::get_instance().from_utf16_to_utf8(value));
        QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
    }

    TEST_P(DotEnvValueExtractorTest, Should_Handle_Concurrent_Extraction_When_Threaded)
    {
        std::wstring key = GetParam();
        std::wstring value = L"ThreadedExtract";
        QLogicaeCore::DotEnv::get_instance().set(key.c_str(), value.c_str());
        QLogicaeCore::DotEnvValueExtractor extractor(key);

        std::mutex accessMutex;
        std::condition_variable startCondition;
        std::atomic<bool> ready(false);
        std::mutex startMutex;
        std::vector<std::thread> threads;

        for (int index = 0; index < 10; ++index)
        {
            threads.emplace_back([&]() {
                std::unique_lock<std::mutex> lock(startMutex);
                startCondition.wait(lock, [&] { return ready.load(); });
                std::optional<std::string> result;
                {
                    std::lock_guard<std::mutex> guard(accessMutex);
                    result = extractor.get_value();
                }
                ASSERT_TRUE(result.has_value());
                ASSERT_EQ(result.value(), QLogicaeCore::Encoder::get_instance().from_utf16_to_utf8(value));
                });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
            std::lock_guard<std::mutex> lock(startMutex);
            ready.store(true);
        }
        startCondition.notify_all();

        for (std::thread& thread : threads)
        {
            thread.join();
        }

        QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
    }

    TEST(DotEnvValueExtractorStressTest, Should_Perform_Within_Limit_When_Loaded)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int index = 0; index < 10000; ++index)
        {
            std::wstring key = L"ExtractorStressKey" + std::to_wstring(index);
            std::wstring value = L"ExtractorStressValue" + std::to_wstring(index);
            QLogicaeCore::DotEnv::get_instance().set(key.c_str(), value.c_str());
            QLogicaeCore::DotEnvValueExtractor extractor(key);
            std::optional<std::string> result = extractor.get_value();
            ASSERT_TRUE(result.has_value());
            ASSERT_EQ(result.value(), QLogicaeCore::Encoder::get_instance().from_utf16_to_utf8(value));
            QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        ASSERT_LT(duration.count(), 2);
    }

    TEST_F(DotEnvValueExtractorEmptyArgumentTest, Should_Return_Empty_When_Key_Is_Empty)
    {
        QLogicaeCore::DotEnvValueExtractor extractor(L"");
        std::optional<std::string> result = extractor.get_value();
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value(), "");
    }

    TEST(DotEnvValueExtractorTest,
        Should_Handle_Empty_Result_When_Constructed_With_Invalid_UTF8)
    {
        std::string invalidUtf8 = "\xC3\x28"; 

        QLogicaeCore::DotEnvValueExtractor extractor(invalidUtf8);
        std::optional<std::string> value = extractor.get_value();

        ASSERT_TRUE(value.has_value());
        ASSERT_EQ(value.value(), "");
    }

    TEST(DotEnvValueExtractorTest,
        Should_Return_Correct_Key_When_Using_Valid_Wide_Key)
    {
        std::wstring testKey = L"DUMMY_KEY";

        QLogicaeCore::DotEnvValueExtractor extractor(testKey);
        std::optional<std::wstring> key = extractor.get_key();

        ASSERT_TRUE(key.has_value());
        ASSERT_EQ(key.value(), testKey);
    }

    TEST_P(DotEnvValueExtractorEdgeKeyTest,
        Should_Set_Expect_Success_When_Using_Edge_Case_Keys)
    {
        std::wstring key = GetParam();
        std::wstring value = L"TestEdgeValue";

        bool setResult = QLogicaeCore::DotEnv::get_instance().set(
            key.c_str(), value.c_str()
        );

        ASSERT_TRUE(setResult);

        QLogicaeCore::DotEnvValueExtractor extractor(key);
        std::optional<std::string> extracted = extractor.get_value();

        ASSERT_TRUE(extracted.has_value());

        std::wstring decoded = QLogicaeCore::Encoder::get_instance()
            .from_utf8_to_utf16(extracted.value());

        ASSERT_EQ(decoded, value);

        QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
    }

    INSTANTIATE_TEST_CASE_P(
        DotEnvValueExtractorTest,
        DotEnvValueExtractorEdgeKeyTest,
        ::testing::Values(
            std::wstring(L"\uFFFF"),
            std::wstring(L"\U0001F600"),  
            std::wstring(L"\U00024B62"),  
            std::wstring(256, L'a'),      
            std::wstring(L"HelloWorld")
        )
    );

    TEST(DotEnvValueExtractorNegativeTest,
        Should_Return_Empty_When_Key_Is_Not_Present)
    {
        std::wstring missingKey = L"NON_EXISTENT_ENV_VAR_1234";

        QLogicaeCore::DotEnv::get_instance().remove(missingKey.c_str());

        QLogicaeCore::DotEnvValueExtractor extractor(missingKey);
        std::optional<std::string> value = extractor.get_value();

        ASSERT_TRUE(value.has_value());
        ASSERT_EQ(value.value(), "");
    }

    INSTANTIATE_TEST_CASE_P(
        DotEnvValueExtractorTestParameters,
        DotEnvValueExtractorTest,
        ::testing::Values(
            L"EXTRACTOR_TEST_KEY",
            std::wstring(1024, L'x'),
            L"ENV_EXTRACT_WITH_SPACES",
            std::wstring(L"null\0extract", 13),
            std::wstring(L"long_extract_", 13) + std::wstring(1000, L'E')
        )
    );
}
