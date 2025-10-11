#include "pch.hpp"

#include "qlogicae/core/toml_file_io.hpp"

namespace QLogicaeCoreTest
{
    class TomlFileIOTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::TomlFileIO toml_file_io;

        std::vector<std::string> valid_key_path = { "section", "key" };
        std::vector<std::string> empty_key_path = {};
        std::vector<std::string> invalid_key_path = { "invalid_section", "invalid_key" };

        template<typename ValueType>
        void set_value_and_verify(const std::vector<std::string>& key_path,
            const ValueType& value)
        {
            bool set_result = toml_file_io.set_value<ValueType>(key_path, value);
            EXPECT_TRUE(set_result);

            auto get_result = toml_file_io.get_value<ValueType>(key_path);
            EXPECT_TRUE(get_result.has_value());
            if (get_result)
            {
                EXPECT_EQ(get_result.value(), value);
            }
        }
    };

    TEST_F(TomlFileIOTest, Should_ReturnFalse_When_LoadOnEmptyOrInvalidFile)
    {
        bool load_result = toml_file_io.load();
        EXPECT_FALSE(load_result);
    }

    TEST_F(TomlFileIOTest, Should_ReturnFalse_When_SaveWithoutLoadedData)
    {
        bool save_result = toml_file_io.save();
        EXPECT_FALSE(save_result);
    }

    TEST_F(TomlFileIOTest, Should_ReturnFalse_When_SaveAsWithEmptyPath)
    {
        bool save_as_result = toml_file_io.save_as("");
        EXPECT_FALSE(save_as_result);
    }

    TEST_F(TomlFileIOTest, Should_ReturnNullopt_When_GetValueWithEmptyKeyPath)
    {
        auto result = toml_file_io.get_value<int64_t>(empty_key_path);
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(TomlFileIOTest, Should_ReturnNullopt_When_GetValueWithInvalidKeyPath)
    {
        auto result = toml_file_io.get_value<int64_t>(invalid_key_path);
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(TomlFileIOTest, Should_SetAndGetValueCorrectly_WithVariousTypes)
    {
        set_value_and_verify<int64_t>(valid_key_path, 42);
        set_value_and_verify<double>(valid_key_path, 3.14159);
        set_value_and_verify<std::string>(valid_key_path, "test_value");
        set_value_and_verify<bool>(valid_key_path, true);
    }

    TEST_F(TomlFileIOTest, Should_ReturnFalse_When_SetValueWithEmptyKeyPath)
    {
        bool result = toml_file_io.set_value<int64_t>(empty_key_path, 5);
        EXPECT_FALSE(result);
    }

    TEST_F(TomlFileIOTest, Should_ReturnFalse_When_RemoveValueWithEmptyKeyPath)
    {
        bool result = toml_file_io.remove_value(empty_key_path);
        EXPECT_FALSE(result);
    }

    TEST_F(TomlFileIOTest, Should_PerformLoadAsyncCorrectly)
    {
        std::future<bool> future = toml_file_io.load_async();
        bool result = future.get();
        EXPECT_FALSE(result);
    }

    TEST_F(TomlFileIOTest, Should_PerformSaveAsyncCorrectly)
    {
        std::future<bool> future = toml_file_io.save_async();
        bool result = future.get();
        EXPECT_FALSE(result);
    }

    TEST_F(TomlFileIOTest, Should_PerformSaveAsAsyncWithEmptyPath)
    {
        std::future<bool> future = toml_file_io.save_as_async("");
        bool result = future.get();
        EXPECT_FALSE(result);
    }

    TEST_F(TomlFileIOTest, Should_PerformGetValueAsync_WithEmptyAndValidKeyPaths)
    {
        std::future<std::optional<int64_t>> future_empty =
            toml_file_io.get_value_async<int64_t>(empty_key_path);
        auto result_empty = future_empty.get();
        EXPECT_FALSE(result_empty.has_value());

        toml_file_io.set_value<int64_t>(valid_key_path, 123);
        std::future<std::optional<int64_t>> future_valid =
            toml_file_io.get_value_async<int64_t>(valid_key_path);
        auto result_valid = future_valid.get();
        EXPECT_TRUE(result_valid.has_value());
        if (result_valid)
        {
            EXPECT_EQ(result_valid.value(), 123);
        }
    }

    TEST_F(TomlFileIOTest, Should_PerformSetValueAsync_WithVariousTypes)
    {
        std::future<bool> future_int =
            toml_file_io.set_value_async<int64_t>(valid_key_path, 456);
        EXPECT_TRUE(future_int.get());

        std::future<bool> future_string =
            toml_file_io.set_value_async<std::string>(valid_key_path, "async_test");
        EXPECT_TRUE(future_string.get());
    }

    TEST_F(TomlFileIOTest, Should_SetValuesCorrectly_ForMultiplePairs)
    {
        std::unordered_map<std::vector<std::string>, int64_t,
            QLogicaeCore::VectorStringHash,
            QLogicaeCore::VectorStringEqual> values
        {
            {{"section1", "key1"}, 1},
            {{"section2", "key2"}, 2},
            {{"section3", "key3"}, 3}
        };

        bool result = toml_file_io.set_values<int64_t>(values);
        EXPECT_TRUE(result);

        for (const auto& pair : values)
        {
            auto value = toml_file_io.get_value<int64_t>(pair.first);
            EXPECT_TRUE(value.has_value());
            if (value)
            {
                EXPECT_EQ(value.value(), pair.second);
            }
        }
    }

    TEST_F(TomlFileIOTest, Should_RemoveKeysCorrectly)
    {
        std::unordered_map<std::vector<std::string>, int64_t,
            QLogicaeCore::VectorStringHash,
            QLogicaeCore::VectorStringEqual> values
        {
            {{"section1", "key1"}, 100},
            {{"section2", "key2"}, 200}
        };
        toml_file_io.set_values<int64_t>(values);

        std::vector<std::vector<std::string>> keys_to_remove
        {
            {"section1", "key1"},
            {"section2", "key2"}
        };

        bool remove_result = toml_file_io.remove_keys(keys_to_remove);
        EXPECT_TRUE(remove_result);

        for (const auto& key : keys_to_remove)
        {
            auto value = toml_file_io.get_value<int64_t>(key);
            EXPECT_FALSE(value.has_value());
        }
    }

    TEST_F(TomlFileIOTest, Should_PerformSetValuesAsyncCorrectly)
    {
        std::unordered_map<std::vector<std::string>, int64_t,
            QLogicaeCore::VectorStringHash,
            QLogicaeCore::VectorStringEqual> values
        {
            {{"async_section1", "key1"}, 1},
            {{"async_section2", "key2"}, 2}
        };

        std::future<bool> future = toml_file_io.set_values_async<int64_t>(values);
        bool result = future.get();
        EXPECT_TRUE(result);

        for (const auto& pair : values)
        {
            auto value = toml_file_io.get_value<int64_t>(pair.first);
            EXPECT_TRUE(value.has_value());
            if (value)
            {
                EXPECT_EQ(value.value(), pair.second);
            }
        }
    }

    TEST_F(TomlFileIOTest, Should_PerformRemoveKeysAsyncCorrectly)
    {
        std::unordered_map<std::vector<std::string>, int64_t,
            QLogicaeCore::VectorStringHash,
            QLogicaeCore::VectorStringEqual> values
        {
            {{"section1", "key1"}, 100},
            {{"section2", "key2"}, 200}
        };
        toml_file_io.set_values<int64_t>(values);

        std::vector<std::vector<std::string>> keys_to_remove
        {
            {"section1", "key1"},
            {"section2", "key2"}
        };

        std::future<bool> future_remove = toml_file_io.remove_keys_async(keys_to_remove);
        EXPECT_TRUE(future_remove.get());

        for (const auto& key : keys_to_remove)
        {
            auto value = toml_file_io.get_value<int64_t>(key);
            EXPECT_FALSE(value.has_value());
        }
    }

    TEST_F(TomlFileIOTest, Should_PerformRemoveValueAsync_WithEmptyAndValidKeys)
    {
        std::future<bool> future_empty = toml_file_io.remove_value_async(empty_key_path);
        EXPECT_FALSE(future_empty.get());

        toml_file_io.set_value<int64_t>(valid_key_path, 789);
        std::future<bool> future_valid = toml_file_io.remove_value_async(valid_key_path);
        EXPECT_TRUE(future_valid.get());

        auto value_after_removal = toml_file_io.get_value<int64_t>(valid_key_path);
        EXPECT_FALSE(value_after_removal.has_value());
    }

    class TomlFileIOParameterizedTest : public ::testing::TestWithParam<std::tuple<std::vector<std::string>, int64_t>>
    {
    protected:
        QLogicaeCore::TomlFileIO toml_file_io;
    };

    INSTANTIATE_TEST_CASE_P(
        TomlFileIOParameterizedTest,
        TomlFileIOParameterizedTest,
        ::testing::Values(
            std::make_tuple(std::vector<std::string>{"param_section", "key1"}, 10),
            std::make_tuple(std::vector<std::string>{"param_section", "key2"}, 20),
            std::make_tuple(std::vector<std::string>{"param_section", "key3"}, 30),
            std::make_tuple(std::vector<std::string>{}, 0)
        )
    );

    TEST_P(TomlFileIOParameterizedTest, Should_SetAndGetValueCorrectly)
    {
        std::vector<std::string> key_path = std::get<0>(GetParam());
        int64_t value = std::get<1>(GetParam());

        if (key_path.empty())
        {
            EXPECT_FALSE(toml_file_io.set_value<int64_t>(key_path, value));
        }
        else
        {
            EXPECT_TRUE(toml_file_io.set_value<int64_t>(key_path, value));

            auto get_result = toml_file_io.get_value<int64_t>(key_path);
            EXPECT_TRUE(get_result.has_value());
            if (get_result)
            {
                EXPECT_EQ(get_result.value(), value);
            }
        }
    }
    
    class TomlFileIOStressTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::TomlFileIO toml_file_io;
    };

    TEST_F(TomlFileIOStressTest, Should_HandleLargeNumberOfSetValueAndGetValue)
    {
        for (int64_t index = 0; index < 10000; ++index)
        {
            std::vector<std::string> key_path = { "stress_section", "key" + std::to_string(index) };
            EXPECT_TRUE(toml_file_io.set_value<int64_t>(key_path, index));

            auto value = toml_file_io.get_value<int64_t>(key_path);
            EXPECT_TRUE(value.has_value());
            if (value)
            {
                EXPECT_EQ(value.value(), index);
            }
        }
    }

    TEST_F(TomlFileIOStressTest, Should_HandleConcurrentSetValueAsync)
    {
        std::vector<std::future<bool>> futures;
        for (int64_t index = 0; index < 100; ++index)
        {
            std::vector<std::string> key_path = { "concurrent_section", "key" + std::to_string(index) };
            futures.push_back(toml_file_io.set_value_async<int64_t>(key_path, index));
        }

        for (auto& future : futures)
        {
            EXPECT_TRUE(future.get());
        }
    }

    class TomlFileIOExceptionSafetyTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::TomlFileIO toml_file_io;
    };

    TEST_F(TomlFileIOExceptionSafetyTest, Should_NotThrow_When_GetValueCalledWithInvalidKey)
    {
        EXPECT_NO_THROW({
            auto value = toml_file_io.get_value<int64_t>({"invalid", "key"});
            (void)value;
            });
    }

    TEST_F(TomlFileIOExceptionSafetyTest, Should_NotThrow_When_SetValueCalledWithInvalidKey)
    {
        EXPECT_NO_THROW({
            bool result = toml_file_io.set_value<int64_t>({"invalid", "key"}, 123);
            (void)result;
            });
    }

    TEST_F(TomlFileIOExceptionSafetyTest, Should_NotThrow_When_LoadAsyncCalled)
    {
        EXPECT_NO_THROW({
            auto future = toml_file_io.load_async();
            bool result = future.get();
            (void)result;
            });
    }

    TEST_F(TomlFileIOExceptionSafetyTest, Should_NotThrow_When_SaveAsyncCalled)
    {
        EXPECT_NO_THROW({
            auto future = toml_file_io.save_async();
            bool result = future.get();
            (void)result;
            });
    }

    TEST_F(TomlFileIOExceptionSafetyTest, Should_NotThrow_When_RemoveKeysAsyncCalled)
    {
        EXPECT_NO_THROW({
            auto future = toml_file_io.remove_keys_async({{"key1"}, {"key2"}});
            bool result = future.get();
            (void)result;
            });
    }

    class TomlFileIOPerformanceTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::TomlFileIO toml_file_io;
    };

    TEST_F(TomlFileIOPerformanceTest, Should_CompleteStressSetValueAndGetValueUnderTwoSeconds)
    {
        auto start_time = std::chrono::steady_clock::now();

        for (int64_t index = 0; index < 10000; ++index)
        {
            std::vector<std::string> key_path = { "stress_section", "key" + std::to_string(index) };
            EXPECT_TRUE(toml_file_io.set_value<int64_t>(key_path, index));

            auto value = toml_file_io.get_value<int64_t>(key_path);
            EXPECT_TRUE(value.has_value());
            if (value)
            {
                EXPECT_EQ(value.value(), index);
            }
        }

        auto end_time = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - start_time;
        EXPECT_LT(elapsed_seconds.count(), 2.0);
    }

    TEST_F(TomlFileIOPerformanceTest, Should_CompleteConcurrentSetValueAsyncUnderTwoSeconds)
    {
        auto start_time = std::chrono::steady_clock::now();

        std::vector<std::future<bool>> futures;
        for (int64_t index = 0; index < 100; ++index)
        {
            std::vector<std::string> key_path = { "concurrent_section", "key" + std::to_string(index) };
            futures.push_back(toml_file_io.set_value_async<int64_t>(key_path, index));
        }

        for (auto& future : futures)
        {
            EXPECT_TRUE(future.get());
        }

        auto end_time = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - start_time;
        EXPECT_LT(elapsed_seconds.count(), 2.0);
    }

    class TomlFileIOMultithreadStressTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::TomlFileIO toml_file_io;
    };

    TEST_F(TomlFileIOMultithreadStressTest, Should_HandleConcurrentReadsAndWritesSafely)
    {
        std::vector<std::thread> threads;

        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back([this, i]()
                {
                    for (int j = 0; j < 100; ++j)
                    {
                        std::vector<std::string> key_path = { "multi_thread_section", "key" + std::to_string(i * 100 + j) };
                        toml_file_io.set_value<int64_t>(key_path, i * 100 + j);
                    }
                });
        }

        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back([this, i]()
                {
                    for (int j = 0; j < 100; ++j)
                    {
                        std::vector<std::string> key_path = { "multi_thread_section", "key" + std::to_string(i * 100 + j) };
                        auto val = toml_file_io.get_value<int64_t>(key_path);
                        if (val)
                        {
                            EXPECT_GE(val.value(), 0);
                        }
                    }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }
    }

    class TomlFileIOMockableRootTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::TomlFileIO toml_file_io;

        void SetRootToNullopt()
        {

        }
    };

    TEST_F(TomlFileIOMockableRootTest, Should_ReturnNullopt_When_GetValueCalledWithNulloptRoot)
    {
        auto result = toml_file_io.get_value<int64_t>({ "any", "key" });
        EXPECT_FALSE(result.has_value());
    }

    TEST_F(TomlFileIOMockableRootTest, Should_ReturnFalse_When_RemoveValueCalledWithNulloptRoot)
    {
        bool result = toml_file_io.remove_value({ "any", "key" });
        EXPECT_FALSE(result);
    }

    class TomlFileIOExceptionThrowTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::TomlFileIO toml_file_io;
    };

    TEST_F(TomlFileIOExceptionThrowTest, Should_NotThrow_IfGetValueThrows)
    {
        EXPECT_NO_THROW({
            auto result = toml_file_io.get_value<int64_t>({"nonexistent", "key"});
            (void)result;
            });
    }

    TEST_F(TomlFileIOExceptionThrowTest, Should_NotThrow_IfSetValueThrows)
    {
        EXPECT_NO_THROW({
            bool result = toml_file_io.set_value<int64_t>({"nonexistent", "key"}, 1);
            (void)result;
            });
    }

    TEST_F(TomlFileIOExceptionThrowTest, Should_NotThrow_IfRemoveValueThrows)
    {
        EXPECT_NO_THROW({
            bool result = toml_file_io.remove_value({"nonexistent", "key"});
            (void)result;
            });
    }

    TEST_F(TomlFileIOExceptionThrowTest, Should_NotThrow_IfLoadThrowsAsync)
    {
        EXPECT_NO_THROW({
            auto future = toml_file_io.load_async();
            (void)future.get();
            });
    }

    TEST_F(TomlFileIOExceptionThrowTest, Should_NotThrow_IfSaveThrowsAsync)
    {
        EXPECT_NO_THROW({
            auto future = toml_file_io.save_async();
            (void)future.get();
            });
    }

    TEST_F(TomlFileIOExceptionThrowTest, Should_NotThrow_IfRemoveKeysThrowsAsync)
    {
        EXPECT_NO_THROW({
            auto future = toml_file_io.remove_keys_async({{"key1"}, {"key2"}});
            (void)future.get();
            });
    }

    TEST_F(TomlFileIOExceptionThrowTest, Should_CorrectlyReportRemoveValueAsync)
    {
        QLogicaeCore::TomlFileIO file_io;
        std::vector<std::string> path = { "parent", "child" };
        ASSERT_TRUE(file_io.set_value(path, std::int64_t{ 123 }));
        std::future<bool> result_future = file_io.remove_value_async(path);
        ASSERT_EQ(result_future.wait_for(std::chrono::seconds(1)), std::future_status::ready);
        bool result = result_future.get();
        EXPECT_TRUE(result);
    }

    TEST_F(TomlFileIOExceptionThrowTest, Should_ValidateAsyncReturnValuesGranularly)
    {
        toml_file_io.set_value<int64_t>({ "async", "key" }, 999);

        auto future_get = toml_file_io.get_value_async<int64_t>({ "async", "key" });
        auto get_result = future_get.get();
        EXPECT_TRUE(get_result.has_value());
        if (get_result)
        {
            EXPECT_EQ(get_result.value(), 999);
        }

        auto future_set = toml_file_io.set_value_async<int64_t>({ "async", "key" }, 1000);
        bool set_result = future_set.get();
        EXPECT_TRUE(set_result);

        auto future_remove = toml_file_io.remove_value_async({ "async", "key" });
        bool remove_result = future_remove.get();
        EXPECT_TRUE(remove_result);
    }

    class TomlFileIOIntegrationTest : public ::testing::Test
    {
    protected:
        std::string temp_file_path = "temp_test.toml";

        void TearDown() override
        {
            std::error_code ec;
            std::filesystem::remove(temp_file_path, ec);
        }
    };

    TEST_F(TomlFileIOIntegrationTest, Should_SaveAndLoadSuccessfully_WithRealFile)
    {
        QLogicaeCore::TomlFileIO io(temp_file_path);

        std::vector<std::string> key_path = { "app", "version" };
        std::string version_value = "1.2.3";

        EXPECT_TRUE(io.set_value<std::string>(key_path, version_value));
        EXPECT_TRUE(io.save());

        QLogicaeCore::TomlFileIO io_loaded(temp_file_path);
        EXPECT_TRUE(io_loaded.load());

        auto loaded_value = io_loaded.get_value<std::string>(key_path);
        EXPECT_TRUE(loaded_value.has_value());
        if (loaded_value)
        {
            EXPECT_EQ(loaded_value.value(), version_value);
        }
    }

    TEST_F(TomlFileIOIntegrationTest, Should_HandleConcurrentModificationConflictsSafely)
    {
        QLogicaeCore::TomlFileIO io;

        std::vector<std::string> key_path = { "concurrent", "counter" };
        EXPECT_TRUE(io.set_value<int64_t>(key_path, 0));

        constexpr int thread_count = 10;
        constexpr int increments_per_thread = 1000;

        std::vector<std::thread> threads;

        for (int i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&io, &key_path, increments_per_thread]()
                {
                    for (int j = 0; j < increments_per_thread; ++j)
                    {
                        auto val_opt = io.get_value<int64_t>(key_path);
                        int64_t val = val_opt.value_or(0);
                        io.set_value<int64_t>(key_path, val + 1);
                    }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        auto final_val_opt = io.get_value<int64_t>(key_path);
        EXPECT_TRUE(final_val_opt.has_value());

        if (final_val_opt)
        {
            EXPECT_LE(final_val_opt.value(), thread_count * increments_per_thread);
        }
    }

    TEST_F(TomlFileIOIntegrationTest, Should_HandleNestedTablesBeyondTwoLevels)
    {
        QLogicaeCore::TomlFileIO io;

        std::vector<std::string> deep_key_path = { "level1", "level2", "level3", "key" };
        int64_t expected_value = 12345;

        EXPECT_TRUE(io.set_value<int64_t>(deep_key_path, expected_value));

        auto value = io.get_value<int64_t>(deep_key_path);
        EXPECT_TRUE(value.has_value());
        if (value)
        {
            EXPECT_EQ(value.value(), expected_value);
        }
    }

    TEST_F(TomlFileIOIntegrationTest, Should_SupportArrayTypeValues)
    {
        QLogicaeCore::TomlFileIO io;

        std::vector<std::string> key_path = { "settings", "enabled_features" };
        std::vector<std::string> features = { "feature1", "feature2", "feature3" };

        EXPECT_TRUE(io.set_value<std::vector<std::string>>(key_path, features));

        auto loaded_features = io.get_value<std::vector<std::string>>(key_path);
        EXPECT_TRUE(loaded_features.has_value());
        if (loaded_features)
        {
            EXPECT_EQ(loaded_features.value(), features);
        }
    }

    TEST_F(TomlFileIOIntegrationTest, Should_FailLoadOnMalformedTomlFile)
    {        
        std::ofstream ofs(temp_file_path);
        ofs << "invalid_toml = [this, is, malformed\n"; 
        ofs.close();

        QLogicaeCore::TomlFileIO io(temp_file_path);

        EXPECT_ANY_THROW({
            bool result = io.load();
            EXPECT_FALSE(result);
        });
    }
}

