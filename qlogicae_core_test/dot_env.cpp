#include "pch.h"

#include "qlogicae_core/dot_env.hpp"

namespace QLogicaeCoreTest
{
    class DotEnvTest : public ::testing::TestWithParam<std::wstring>
    {
    protected:
        void SetUp() override {}
        void TearDown() override {}
    };

    class DotEnvEmptyArgumentTest : public ::testing::Test
    {
    };

    TEST_F(DotEnvEmptyArgumentTest, Should_Return_False_When_Set_Key_Is_Empty)
    {
        const wchar_t* key = L"";
        const wchar_t* value = L"value";
        bool result = QLogicaeCore::DotEnv::get_instance().set(key, value);
        ASSERT_FALSE(result);
    }

    TEST_F(DotEnvEmptyArgumentTest, Should_Return_False_When_Set_Key_And_Value_Are_Empty)
    {
        bool result = QLogicaeCore::DotEnv::get_instance().set(L"", L"");
        ASSERT_FALSE(result);
    }

    TEST_F(DotEnvEmptyArgumentTest, Should_Return_False_When_Remove_Key_Is_Empty)
    {
        bool result = QLogicaeCore::DotEnv::get_instance().remove(L"");
        ASSERT_FALSE(result);
    }

    TEST_F(DotEnvEmptyArgumentTest, Should_Return_Empty_When_Get_Key_Is_Empty)
    {
        std::optional<std::wstring> result =
            QLogicaeCore::DotEnv::get_instance().get(L"");
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value(), L"");
    }

    TEST_P(DotEnvTest, Should_Set_Expect_Success_When_Key_And_Value_Are_Valid)
    {
        std::wstring key = GetParam();
        std::wstring value = L"TestValue";
        bool result = QLogicaeCore::DotEnv::get_instance().set(key.c_str(), value.c_str());
        ASSERT_TRUE(result);
        std::optional<std::wstring> retrieved =
            QLogicaeCore::DotEnv::get_instance().get(key.c_str());
        ASSERT_TRUE(retrieved.has_value());
        ASSERT_EQ(retrieved.value(), value);
        QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
    }

    TEST_P(DotEnvTest, Should_Remove_Expect_Success_When_Key_Is_Valid)
    {
        std::wstring key = GetParam();
        QLogicaeCore::DotEnv::get_instance().set(key.c_str(), L"ToRemove");
        bool result = QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
        ASSERT_TRUE(result);
        std::optional<std::wstring> value = QLogicaeCore::DotEnv::get_instance().get(key.c_str());
        ASSERT_TRUE(value.has_value());
        ASSERT_EQ(value.value(), L"");
    }

    TEST(DotEnvStressTest, Should_Perform_Within_Limit_When_Loaded)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int index = 0; index < 10000; ++index)
        {
            std::wstring key = L"StressKey" + std::to_wstring(index);
            std::wstring value = L"StressValue" + std::to_wstring(index);
            QLogicaeCore::DotEnv::get_instance().set(key.c_str(), value.c_str());
            std::optional<std::wstring> retrieved = QLogicaeCore::DotEnv::get_instance().get(key.c_str());
            ASSERT_TRUE(retrieved.has_value());
            ASSERT_EQ(retrieved.value(), value);
            QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        ASSERT_LT(duration.count(), 2);
    }

    TEST(DotEnvExceptionTest, Should_Return_False_When_Set_Null)
    {
        bool result = QLogicaeCore::DotEnv::get_instance().set(nullptr, nullptr);
        ASSERT_FALSE(result);
    }

    TEST(DotEnvExceptionTest, Should_Return_False_When_Remove_Null)
    {
        bool result = QLogicaeCore::DotEnv::get_instance().remove(nullptr);
        ASSERT_FALSE(result);
    }

    TEST(DotEnvExceptionTest, Should_Return_Empty_When_Get_Null)
    {
        std::optional<std::wstring> result = QLogicaeCore::DotEnv::get_instance().get(nullptr);
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value(), L"");
    }

    TEST_P(DotEnvTest, Should_Get_Expect_Correct_Value_When_Called_Asynchronously)
    {
        std::wstring key = GetParam();
        std::wstring value = L"AsyncValue";
        QLogicaeCore::DotEnv::get_instance().set(key.c_str(), value.c_str());
        std::future<std::optional<std::wstring>> futureValue = std::async(std::launch::async, [key]() {
            return QLogicaeCore::DotEnv::get_instance().get(key.c_str());
            });
        std::optional<std::wstring> result = futureValue.get();
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result.value(), value);
        QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
    }

    TEST_P(DotEnvTest, Should_Be_Thread_Safe_When_Accessed_Concurrently)
    {
        std::wstring key = GetParam();
        std::wstring value = L"ThreadedValue";
        QLogicaeCore::DotEnv::get_instance().set(key.c_str(), value.c_str());
        std::mutex accessMutex;
        std::atomic<bool> ready(false);
        std::condition_variable startCondition;
        std::mutex startMutex;
        std::vector<std::thread> threads;
        for (int index = 0; index < 10; ++index)
        {
            threads.emplace_back([&]() {
                std::unique_lock<std::mutex> lock(startMutex);
                startCondition.wait(lock, [&] { return ready.load(); });
                std::optional<std::wstring> result;
                {
                    std::lock_guard<std::mutex> guard(accessMutex);
                    result = QLogicaeCore::DotEnv::get_instance().get(key.c_str());
                }
                ASSERT_TRUE(result.has_value());
                ASSERT_EQ(result.value(), value);
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

    TEST(DotEnvRaceConditionTest, Should_Handle_Concurrent_Set_And_Remove)
    {
        std::wstring key = L"RACE_KEY";
        std::atomic<bool> running(true);
        std::vector<std::thread> threads;
        for (int i = 0; i < 5; ++i)
        {
            threads.emplace_back([&]() {
                while (running.load())
                {
                    QLogicaeCore::DotEnv::get_instance().set(key.c_str(), L"VALUE");
                }
                });
            threads.emplace_back([&]() {
                while (running.load())
                {
                    QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
                }
                });
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        running.store(false);
        for (std::thread& thread : threads)
        {
            thread.join();
        }
        QLogicaeCore::DotEnv::get_instance().remove(key.c_str());
    }

    TEST(DotEnvSingletonTest, Should_Return_Same_Instance_When_Called_Multiple_Times)
    {
        std::set<void*> instanceAddresses;
        std::mutex addressMutex;
        std::vector<std::thread> threads;
        for (int i = 0; i < 50; ++i)
        {
            threads.emplace_back([&]() {
                void* address = static_cast<void*>(&QLogicaeCore::DotEnv::get_instance());
                std::lock_guard<std::mutex> lock(addressMutex);
                instanceAddresses.insert(address);
                });
        }
        for (std::thread& thread : threads)
        {
            thread.join();
        }
        ASSERT_EQ(instanceAddresses.size(), 1);
    }

    INSTANTIATE_TEST_CASE_P(
        DotEnvTestParameters,
        DotEnvTest,
        ::testing::Values(
            L"DOT_ENV_TEST_KEY",
            std::wstring(1024, L'x'),
            L"ENV_WITH_SPACES",
            std::wstring(L"null\0key", 9),
            std::wstring(L"long_key_", 9) + std::wstring(1000, L'A')
        )
    );
}

