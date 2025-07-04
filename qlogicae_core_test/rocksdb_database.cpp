#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{

    class RocksDBDatabaseTest : public ::testing::TestWithParam<std::pair<std::string, int>> {
    protected:
        std::string test_path = "rocksdb_test";
        std::shared_ptr<QLogicaeCore::RocksDBDatabase> db;

        void SetUp() override {
            std::filesystem::remove_all(test_path);
            db = std::make_shared<QLogicaeCore::RocksDBDatabase>(test_path);
        }

        void TearDown() override {
            db.reset();
            std::filesystem::remove_all(test_path);
        }
    };

    class RocksDBDatabaseTest_Param : public ::testing::TestWithParam<std::tuple<std::string, int, int, int>> {
    protected:
        std::unique_ptr<QLogicaeCore::RocksDBDatabase> db;
        const std::string test_path = "test_json_param_rocksdb";

        void SetUp() override {
            std::filesystem::remove_all(test_path);
            db = std::make_unique<QLogicaeCore::RocksDBDatabase>(test_path);
        }

        void TearDown() override {
            db.reset();
            std::filesystem::remove_all(test_path);
        }
    };

    TEST_P(RocksDBDatabaseTest_Param, Should_ParseMatrixValue_When_ValidJSONMatrix) {
        const auto& [key, row, col, expected] = GetParam();

        std::string json = R"({"data":[[1,2,3],[4,5,6],[7,8,9]]})";
        db->set_value(key, json);
        std::string result = db->get_value<std::string>(key);

        auto extract = [](const std::string& json, int row, int col) -> std::optional<int> {
            std::string start = "\"data\":[";
            auto pos = json.find(start);
            if (pos == std::string::npos) return std::nullopt;
            pos += start.length();

            int r = -1, c = 0;
            for (size_t i = pos; i < json.length(); ++i) {
                if (json[i] == '[') { ++r; c = 0; ++i; }
                if (r == row) {
                    if (isdigit(json[i]) || json[i] == '-') {
                        size_t end = json.find_first_of(",]", i);
                        if (c == col) return std::stoi(json.substr(i, end - i));
                        ++c;
                        i = end - 1;
                    }
                }
                else if (json[i] == ']') {
                    if (r > row) break;
                }
            }
            return std::nullopt;
            };

        auto val = extract(result, row, col);
        EXPECT_TRUE(val.has_value());
        EXPECT_EQ(val.value(), expected);
    }


    TEST_F(RocksDBDatabaseTest, Should_NotStoreJson_When_TransactionIsRolledBack) {
        ASSERT_TRUE(db->begin_transaction());

        std::string json = R"({"session":{"id":999,"status":"open"}})";
        db->set_value("session", json);

        ASSERT_TRUE(db->rollback_transaction());

        EXPECT_NO_THROW({
            db->get_value<std::string>("session");
            });
    }

    TEST_F(RocksDBDatabaseTest, Should_CorrectlyHandleConcurrentJson_When_MultithreadedInsertAndRead) {
        constexpr int thread_count = 16;
        constexpr int entries_per_thread = 25;
        std::vector<std::thread> threads;

        for (int t = 0; t < thread_count; ++t) {
            threads.emplace_back([&, t]() {
                for (int i = 0; i < entries_per_thread; ++i) {
                    std::string key = "json_" + std::to_string(t) + "_" + std::to_string(i);
                    std::string value = R"({"thread":)" + std::to_string(t) + R"(,"index":)" + std::to_string(i) + "}";
                    db->set_value(key, value);
                }
                });
        }

        for (auto& thread : threads) thread.join();

        for (int t = 0; t < thread_count; ++t) {
            for (int i = 0; i < entries_per_thread; ++i) {
                std::string key = "json_" + std::to_string(t) + "_" + std::to_string(i);
                auto val = db->get_value<std::string>(key);

                auto check = [t, i](const std::string& json) -> bool {
                    auto ts = "\"thread\":" + std::to_string(t);
                    auto is = "\"index\":" + std::to_string(i);
                    return json.find(ts) != std::string::npos && json.find(is) != std::string::npos;
                    };
                EXPECT_TRUE(check(val));
            }
        }
    }

    TEST_F(RocksDBDatabaseTest, Should_FinishUnderTimeLimit_When_LargeJsonStored) {
        constexpr int json_size_kb = 1024; // ~1 MB
        constexpr int value_count = 100;

        std::ostringstream oss;
        oss << R"({"data":[)";
        for (int i = 0; i < value_count; ++i) {
            oss << "\"" << std::string(json_size_kb * 1024 / value_count - 3, 'x') << "\"";
            if (i < value_count - 1) oss << ",";
        }
        oss << R"(]})";

        const std::string large_json = oss.str();

        const auto start = std::chrono::steady_clock::now();
        db->set_value("large_json", large_json);
        const auto write_end = std::chrono::steady_clock::now();

        std::string loaded = db->get_value<std::string>("large_json");
        const auto read_end = std::chrono::steady_clock::now();

        const auto write_ms = std::chrono::duration_cast<std::chrono::milliseconds>(write_end - start).count();
        const auto read_ms = std::chrono::duration_cast<std::chrono::milliseconds>(read_end - write_end).count();

        EXPECT_EQ(loaded.size(), large_json.size());
        EXPECT_LE(write_ms, 2000);
        EXPECT_LE(read_ms, 2000);
    }

    TEST_F(RocksDBDatabaseTest, Should_SetAndGet_Correctly_When_Async) {
        auto f1 = db->set_value_async("key", 123);
        f1.get();
        auto f2 = db->get_value_async<int>("key");
        EXPECT_EQ(f2.get(), 123);
    }

    TEST_F(RocksDBDatabaseTest, Should_Throw_When_KeyDoesNotExist) {
        EXPECT_THROW({
            db->get_value<int>("nonexistent");
            }, std::runtime_error);
    }

    TEST_F(RocksDBDatabaseTest, Should_WorkCorrectly_When_MultithreadedWrite) {
        constexpr int count = 100;
        std::vector<std::thread> threads;
        for (int i = 0; i < count; ++i) {
            threads.emplace_back([this, i]() {
                db->set_value("k" + std::to_string(i), i);
                });
        }
        for (auto& t : threads) t.join();
        for (int i = 0; i < count; ++i) {
            EXPECT_EQ(db->get_value<int>("k" + std::to_string(i)), i);
        }
    }

    TEST_F(RocksDBDatabaseTest, Should_CompleteUnder10Seconds_When_StressWriting1000) {
        constexpr int count = 1000;
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::thread> threads;
        for (int i = 0; i < count; ++i) {
            threads.emplace_back([this, i]() {
                db->set_value("key_" + std::to_string(i), i);
                });
        }
        for (auto& t : threads) t.join();
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LT(std::chrono::duration_cast<std::chrono::seconds>(end - start).count(), 10);
    }

    TEST_F(RocksDBDatabaseTest, Should_PerformUnder10Millisecond_When_SetAndGet) {
        auto start = std::chrono::high_resolution_clock::now();
        db->set_value("pkey", 555);
        int val = db->get_value<int>("pkey");
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_EQ(val, 555);
        EXPECT_LT(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), 10000);
    }

    TEST_P(RocksDBDatabaseTest, Should_StoreCorrectValues_When_DifferentTypes) {
        const auto& [key, value] = GetParam();
        db->set_value(key, value);
        EXPECT_EQ(db->get_value<int>(key), value);
    }

    TEST_F(RocksDBDatabaseTest, Should_Throw_When_DeserializationFails) {
        db->set_value("corrupt", std::string("not_an_int"));
        EXPECT_NO_THROW({
            db->get_value<int>("corrupt");
            });
    }

    TEST_F(RocksDBDatabaseTest, Should_Crash_When_DereferencingNullDatabasePointer) {
        EXPECT_DEATH({
            QLogicaeCore::RocksDBDatabase * ptr = nullptr;
            ptr->get_value<int>("x");
            }, "");
    }

    TEST_F(RocksDBDatabaseTest, Should_WorkCorrectly_When_BatchSetAndCommit) {
        db->begin_batch();
        db->batch_set_value("x", 100);
        db->batch_set_value("y", 200);
        db->commit_batch();
        EXPECT_EQ(db->get_value<int>("x"), 100);
        EXPECT_EQ(db->get_value<int>("y"), 200);
    }

    TEST_F(RocksDBDatabaseTest, Should_WorkCorrectly_When_BatchRemove) {
        db->set_value("to_delete", 888);
        db->begin_batch();
        db->batch_remove_value<int>("to_delete", 0);
        db->commit_batch();
        EXPECT_THROW({
            db->get_value<int>("to_delete");
            }, std::runtime_error);
    }

    TEST_F(RocksDBDatabaseTest, Should_WorkCorrectly_When_BackupAndRestore) {
        db->set_value("b", 42);
        db->create_backup("backup");
        db->remove_value("b");
        db->restore_backup("backup");
        EXPECT_EQ(db->get_value<int>("b"), 42);
    }

    TEST_F(RocksDBDatabaseTest, Should_WorkCorrectly_When_TransactionCommit) {
        db->begin_transaction();
        db->set_value("tx1", 9);
        db->commit_transaction();
        EXPECT_EQ(db->get_value<int>("tx1"), 9);
    }

    TEST_F(RocksDBDatabaseTest, Should_NotApply_When_TransactionRollback) {
        db->begin_transaction();
        db->set_value("tx2", 15);
        db->rollback_transaction();
        EXPECT_NO_THROW({
            db->get_value<int>("tx2");
            });
    }

    TEST_F(RocksDBDatabaseTest, Should_StoreExactJson_When_UsingStringifiedJson) {
        std::string key = "json";
        std::string json = R"({"user":"cedric","active":true,"count":3})";
        db->set_value(key, json);
        std::string result = db->get_value<std::string>(key);
        EXPECT_EQ(result, json);
    }

    TEST_F(RocksDBDatabaseTest, Should_StoreJson_When_ContainsEscapedCharacters) {
        std::string key = "escaped";
        std::string json = R"({"note":"Line1\nLine2\tTabbed","quote":"She said \"Hi\""})";
        db->set_value(key, json);
        std::string result = db->get_value<std::string>(key);
        EXPECT_EQ(result, json);
    }

    TEST_F(RocksDBDatabaseTest, Should_StoreJsonSync_When_SingleThreaded) {
        std::string key = "test_sync";
        std::string json = R"({"key":"value"})";
        db->set_value(key, json);
        auto result = db->get_value<std::string>(key);
        EXPECT_EQ(result, json);
    }

    TEST_F(RocksDBDatabaseTest, Should_Throw_When_JsonKeyNotFound) {
        EXPECT_THROW({
            db->get_value<std::string>("missing_json");
            }, std::runtime_error);
    }

    TEST_F(RocksDBDatabaseTest, Should_StressTest_When_JsonWritesAreHighVolume) {
        constexpr int count = 1000;
        for (int i = 0; i < count; ++i) {
            db->set_value("json_" + std::to_string(i),
                R"({"id":)" + std::to_string(i) + R"(,"value":"stress"})");
        }
        for (int i = 0; i < count; ++i) {
            std::string value = db->get_value<std::string>("json_" + std::to_string(i));
            EXPECT_TRUE(value.find(std::to_string(i)) != std::string::npos);
        }
    }

    TEST_F(RocksDBDatabaseTest, Should_PerformWithinThreshold_When_BulkJsonWrites) {
        constexpr int count = 100;
        auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < count; ++i) {
            db->set_value("bulk_json_" + std::to_string(i),
                R"({"entry":)" + std::to_string(i) + R"(,"payload":"data"})");
        }

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        EXPECT_LT(duration.count(), 2000);
    }

    TEST_F(RocksDBDatabaseTest, Should_StoreJson_When_ContainsUnicode) {
        std::string key = "unicode_json";
        std::string json = R"({"text":"Unicode"})"; // Japanese: "Hello, World"
        db->set_value(key, json);
        std::string result = db->get_value<std::string>(key);
        EXPECT_EQ(result, json);
    }

    TEST_F(RocksDBDatabaseTest, Should_StoreJson_When_ContainsEmptyObject) {
        std::string key = "empty_json";
        std::string json = R"({})";
        db->set_value(key, json);
        std::string result = db->get_value<std::string>(key);
        EXPECT_EQ(result, json);
    }

    TEST_F(RocksDBDatabaseTest, Should_StoreJson_When_ContainsDeepNesting) {
        std::string key = "deep_json";
        std::string json = R"({"a":{"b":{"c":{"d":{"e":{"f":123}}}}}})";
        db->set_value(key, json);
        std::string result = db->get_value<std::string>(key);
        EXPECT_EQ(result, json);
    }

    TEST_F(RocksDBDatabaseTest, Should_ExtractBooleanAndNumber_When_ManuallyParsed) {
        std::string key = "parse_bool_num";
        std::string json = R"({"user":"cedric","active":true,"count":42})";
        db->set_value(key, json);
        std::string result = db->get_value<std::string>(key);

        auto extract_bool = [](const std::string& json, const std::string& field) -> std::optional<bool> {
            std::string search = "\"" + field + "\":";
            auto start = json.find(search);
            if (start == std::string::npos) return std::nullopt;
            start += search.length();
            if (json.compare(start, 4, "true") == 0) return true;
            if (json.compare(start, 5, "false") == 0) return false;
            return std::nullopt;
            };

        auto extract_number = [](const std::string& json, const std::string& field) -> std::optional<int> {
            std::string search = "\"" + field + "\":";
            auto start = json.find(search);
            if (start == std::string::npos) return std::nullopt;
            start += search.length();
            auto end = json.find_first_of(",}", start);
            if (end == std::string::npos) return std::nullopt;
            try {
                return std::stoi(json.substr(start, end - start));
            }
            catch (...) {
                return std::nullopt;
            }
            };

        EXPECT_EQ(extract_bool(result, "active"), true);
        EXPECT_EQ(extract_number(result, "count"), 42);
    }

    TEST_F(RocksDBDatabaseTest, Should_ExtractJsonValue_When_ManuallyParsed) {
        std::string key = "manual_parse";
        std::string json = R"({"user":"cedric","active":true,"count":3})";
        db->set_value(key, json);
        std::string result = db->get_value<std::string>(key);

        auto extract = [](const std::string& json, const std::string& field) -> std::optional<std::string> {
            std::string search = "\"" + field + "\":\"";
            auto start = json.find(search);
            if (start == std::string::npos) return std::nullopt;
            start += search.length();
            auto end = json.find('"', start);
            if (end == std::string::npos) return std::nullopt;
            return json.substr(start, end - start);
            };

        auto user_value = extract(result, "user");
        EXPECT_TRUE(user_value.has_value());
        EXPECT_EQ(user_value.value(), "cedric");
    }

    INSTANTIATE_TEST_CASE_P(RocksDBDatabaseTest_Param, RocksDBDatabaseTest_Param,
        ::testing::Values(
            std::make_tuple("k1", 0, 0, 1),
            std::make_tuple("k2", 1, 2, 6),
            std::make_tuple("k3", 2, 1, 8)
        )
    );

    INSTANTIATE_TEST_CASE_P(
        RocksDBDatabaseTest,
        RocksDBDatabaseTest,
        ::testing::Values(
            std::make_pair(std::string("a"), 1),
            std::make_pair(std::string("b"), -999),
            std::make_pair(std::string("c"), 0),
            std::make_pair(std::string("d"), 2147483647),
            std::make_pair(std::string("e"), static_cast<int>(-2147483648LL))
        )
    );

}
