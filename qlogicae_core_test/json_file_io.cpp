#include "pch.h"

#include "qlogicae_core/json_file_io.hpp"

namespace QLogicaeCoreTest
{
    class JsonFileIOTest : public ::testing::TestWithParam<std::tuple<std::string, bool, double>> {
    protected:
        void SetUp() override {
            std::ofstream("test.json") << R"({
            "name": "Jane Doe",
            "active": false,
            "score": 100.0,
            "optionalField": null,
            "tags": ["guest", false, 1.0],
            "address": {
                "street": "456 Broadway",
                "verified": false
            }
        })";
        }

        void TearDown() override {
            std::remove("test.json");
        }
    };

    TEST_F(JsonFileIOTest, Should_Expect_True_When_IsKeyPathValidForExistingPath) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "name" };
        ASSERT_TRUE(io.is_key_path_valid(path));
    }

    TEST_F(JsonFileIOTest, Should_Expect_String_When_GettingStringValue) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "name" };
        ASSERT_EQ(io.get_string(path), "Jane Doe");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Bool_When_GettingBoolValue) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "active" };
        ASSERT_FALSE(io.get_bool(path));
    }

    TEST_F(JsonFileIOTest, Should_Expect_Double_When_GettingDoubleValue) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "score" };
        ASSERT_DOUBLE_EQ(io.get_double(path), 100.0);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Empty_When_GettingNonStringAsString) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "score" };
        ASSERT_EQ(io.get_string(path), "");
    }

    TEST_F(JsonFileIOTest, Should_Throw_When_GettingArrayWithWrongType) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "name" };
        ASSERT_THROW(io.get_array(path), std::runtime_error);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Object_When_GettingValidObject) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "address" };
        auto obj = io.get_object(path);
        ASSERT_EQ(std::any_cast<std::string>(obj["street"]), "456 Broadway");
    }

    TEST_F(JsonFileIOTest, Should_Expect_True_When_InsertingThenGettingString) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "inserted" };
        ASSERT_TRUE(io.insert_string(path, "test"));
        ASSERT_EQ(io.get_string(path), "test");
    }

    TEST_F(JsonFileIOTest, Should_Expect_False_When_ParsingInvalidFile) {
        std::ofstream("test.json") << "{";
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "any" };
        ASSERT_FALSE(io.get_bool(path));
    }

    TEST_P(JsonFileIOTest, Should_Expect_CorrectTypes_When_UsingVariousInputTypes) {
        auto [str, b, d] = GetParam();
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_TRUE(io.insert_string({ "str" }, str));
        ASSERT_TRUE(io.insert_bool({ "bool" }, b));
        ASSERT_TRUE(io.insert_double({ "double" }, d));
        ASSERT_EQ(io.get_string({ "str" }), str);
        ASSERT_EQ(io.get_bool({ "bool" }), b);
        ASSERT_DOUBLE_EQ(io.get_double({ "double" }), d);
    }

    INSTANTIATE_TEST_CASE_P(
        JsonFileIOTest,
        JsonFileIOTest,
        ::testing::Values(
            std::make_tuple("Hello", true, 123.456),
            std::make_tuple("World", false, -987.321)
        )
    );

    TEST_F(JsonFileIOTest, Should_Expect_Correct_When_AsyncOperationsAreUsed)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        
        io.insert_string({ "async" }, "value");
        auto future = io.get_string_async({ "async" });
        
        ASSERT_EQ(future.get(), "value");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Performance_When_BulkInsertsUnderLimit)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        
        auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < 1000; ++i)
        {
            io.insert_double({ "perf", std::to_string(i) }, i);
        }
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        ASSERT_LT(duration.count(), 15000);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Empty_When_FilePathIsMissing) {
        QLogicaeCore::JsonFileIO io; 
        EXPECT_EQ(io.get_string({ "path" }), "");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_InsertingString) {
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_TRUE(io.insert_string({ "key" }, "value"));
        ASSERT_EQ(io.get_string({ "key" }), "value");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_InsertingBool) {
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_TRUE(io.insert_bool({ "flag" }, true));
        ASSERT_TRUE(io.get_bool({ "flag" }));
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_InsertingDouble) {
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_TRUE(io.insert_double({ "pi" }, 3.14));
        ASSERT_DOUBLE_EQ(io.get_double({ "pi" }), 3.14);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_InsertingNull) {
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_TRUE(io.insert_null({ "none" }, nullptr));
        ASSERT_EQ(io.get_null({ "none" }), nullptr);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_InsertingArray)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        std::vector<std::any> arr = { std::string("text"), true, 42.0, nullptr };
        ASSERT_TRUE(io.insert_array({ "items" }, arr));
        auto result = io.get_array({ "items" });
        ASSERT_EQ(std::any_cast<std::string>(result[0]), "text");
        ASSERT_EQ(std::any_cast<bool>(result[1]), true);
        ASSERT_DOUBLE_EQ(std::any_cast<double>(result[2]), 42.0);
        ASSERT_EQ(result[3].has_value(), true);  // nullptr
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_InsertingObject)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        std::unordered_map<std::string, std::any> obj = {
            { "name", std::string("John") },
            { "valid", true },
            { "score", 99.5 },
            { "deleted", nullptr }
        };
        ASSERT_TRUE(io.insert_object({ "user" }, obj));
        auto result = io.get_object({ "user" });
        ASSERT_EQ(std::any_cast<std::string>(result["name"]), "John");
        ASSERT_EQ(std::any_cast<bool>(result["valid"]), true);
        ASSERT_DOUBLE_EQ(std::any_cast<double>(result["score"]), 99.5);
        ASSERT_TRUE(result["deleted"].has_value());
    }

    TEST_F(JsonFileIOTest, Should_Expect_Empty_When_KeyPathInvalid)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_FALSE(io.is_key_path_valid({ "nonexistent" }));
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_UsingAsyncInsert)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        auto fut = io.insert_string_async({ "async_key" }, "async_value");
        ASSERT_TRUE(fut.get());
        ASSERT_EQ(io.get_string({ "async_key" }), "async_value");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_UsingAsyncGet)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        io.insert_double({ "value" }, 123.456);
        auto fut = io.get_double_async({ "value" });
        ASSERT_DOUBLE_EQ(fut.get(), 123.456);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Exception_When_FileEmptyInGetArray)
    {
        std::ofstream("test.json") << "";
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_THROW(io.get_array({ "any" }), std::runtime_error);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Exception_When_ValueIsNotArray)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        io.insert_string({ "not_array" }, "text");
        ASSERT_THROW(io.get_array({ "not_array" }), std::runtime_error);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Empty_When_InvalidPathUsed)
    {
        QLogicaeCore::JsonFileIO io("");
        EXPECT_EQ(io.read(), "");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_UpdatingString)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        io.insert_string({ "edit" }, "old");
        ASSERT_TRUE(io.update_string({ "edit" }, "new"));
        ASSERT_EQ(io.get_string({ "edit" }), "new");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_UpdatingBool)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        io.insert_bool({ "flag" }, false);
        ASSERT_TRUE(io.update_bool({ "flag" }, true));
        ASSERT_TRUE(io.get_bool({ "flag" }));
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_UpdatingDouble)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        io.insert_double({ "score" }, 12.5);
        ASSERT_TRUE(io.update_double({ "score" }, 100.0));
        ASSERT_DOUBLE_EQ(io.get_double({ "score" }), 100.0);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_UpdatingArray)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        io.insert_array({ "list" }, { std::string("x") });
        ASSERT_TRUE(io.update_array({ "list" }, { 3.14, true }));
        auto result = io.get_array({ "list" });
        ASSERT_DOUBLE_EQ(std::any_cast<double>(result[0]), 3.14);
        ASSERT_TRUE(std::any_cast<bool>(result[1]));
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_UpdatingObject)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        io.insert_object({ "obj" }, { { "a", 1.0 } });
        ASSERT_TRUE(io.update_object({ "obj" }, { { "b", std::string("updated") } }));
        auto result = io.get_object({ "obj" });
        ASSERT_EQ(std::any_cast<std::string>(result["b"]), "updated");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_AsyncUpdateString)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        io.insert_string({ "async" }, "init");
        auto fut = io.update_string_async({ "async" }, "done");
        ASSERT_TRUE(fut.get());
        ASSERT_EQ(io.get_string({ "async" }), "done");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Exception_When_JSONIsMalformed)
    {
        std::ofstream("test.json") << "{ invalid json }";
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_FALSE(io.insert_string({ "fail" }, "test"));
        ASSERT_EQ(io.get_string({ "fail" }), "");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Exception_When_FileDoesNotExist)
    {
        std::remove("test.json");
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_FALSE(io.insert_bool({ "x" }, true));
        ASSERT_EQ(io.get_bool({ "x" }), false);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_OverwritingSameKeyMultipleTimes)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        for (int i = 0; i < 10; ++i) {
            ASSERT_TRUE(io.insert_string({ "repeated" }, "iteration_" + std::to_string(i)));
        }
        ASSERT_EQ(io.get_string({ "repeated" }), "iteration_9");
    }

    TEST_F(JsonFileIOTest, Should_Expect_True_When_KeyPathExists) {
        QLogicaeCore::JsonFileIO io("test.json");
        io.insert_string({ "valid" }, "ok");
        ASSERT_TRUE(io.is_key_path_valid({ "valid" }));
    }

    TEST_F(JsonFileIOTest, Should_Expect_False_When_KeyPathDoesNotExist) {
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_FALSE(io.is_key_path_valid({ "missing" }));
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_UsingDeeplyNestedPaths) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath deep = { "a", "b", "c", "d", "e" };
        ASSERT_TRUE(io.insert_bool(deep, true));
        ASSERT_TRUE(io.get_bool(deep));
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_MixedConcurrentReadWrite) {
        QLogicaeCore::JsonFileIO io("test.json");
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back([&io, i]() {
                io.insert_double({ "mixed", std::to_string(i) }, i * 1.0);
                });
        }
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back([&io, i]() {
                io.get_double({ "mixed", std::to_string(i) });
                });
        }
        for (auto& t : threads) t.join();
        ASSERT_DOUBLE_EQ(io.get_double({ "mixed", "7" }), 7.0);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Death_When_PathIsEmptyAndUsed) {
        QLogicaeCore::JsonFileIO io("");
        EXPECT_EQ(io.insert_string({ "any" }, "val"), false);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_SettingAndGettingFormatFlag) {
        QLogicaeCore::JsonFileIO io("test.json");
        ASSERT_FALSE(io.get_is_formatting_allowed());
        io.set_is_formatting_allowed(true);
        ASSERT_TRUE(io.get_is_formatting_allowed());
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_InsertingDeepNestedString) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "level1", "level2", "level3", "level4", "leaf" };
        ASSERT_TRUE(io.insert_string(path, "deep_value"));
        ASSERT_EQ(io.get_string(path), "deep_value");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_UpdatingDeepNestedBool) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "a", "b", "c", "d", "e" };
        io.insert_bool(path, false);
        ASSERT_TRUE(io.update_bool(path, true));
        ASSERT_TRUE(io.get_bool(path));
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_InsertingDeepNestedArray)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "root", "nested", "structure", "array_key" };
        std::vector<std::any> array = { std::string("x"), true, 3.14 };
        ASSERT_TRUE(io.insert_array(path, array));

        auto result = io.get_array(path);
        ASSERT_EQ(std::any_cast<std::string>(result[0]), "x");
        ASSERT_TRUE(std::any_cast<bool>(result[1]));
        ASSERT_DOUBLE_EQ(std::any_cast<double>(result[2]), 3.14);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_InsertingDeepNestedObject)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "x", "y", "z", "obj" };
        std::unordered_map<std::string, std::any> obj = {
            { "id", 101.0 }, { "active", true }, { "tag", std::string("deep") }
        };
        ASSERT_TRUE(io.insert_object(path, obj));

        auto result = io.get_object(path);
        ASSERT_DOUBLE_EQ(std::any_cast<double>(result["id"]), 101.0);
        ASSERT_TRUE(std::any_cast<bool>(result["active"]));
        ASSERT_EQ(std::any_cast<std::string>(result["tag"]), "deep");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_GettingDeepNestedNull) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "config", "temp", "removed", "state" };
        ASSERT_TRUE(io.insert_null(path, nullptr));
        ASSERT_EQ(io.get_null(path), nullptr);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_ValidatingDeepNestedPath) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "k1", "k2", "k3", "exists" };
        io.insert_double(path, 42.0);
        ASSERT_TRUE(io.is_key_path_valid(path));
        ASSERT_FALSE(io.is_key_path_valid({ "k1", "k2", "missing" }));
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_AsyncInsertingDeepNestedString) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "deep", "async", "write", "text" };
        auto fut = io.insert_string_async(path, "thread-safe");
        ASSERT_TRUE(fut.get());
        ASSERT_EQ(io.get_string(path), "thread-safe");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_AsyncGettingDeepNestedBool) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "access", "rights", "nested", "flag" };
        io.insert_bool(path, true);
        auto fut = io.get_bool_async(path);
        ASSERT_TRUE(fut.get());
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_OverwritingDeepNestedValue) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "env", "staging", "log_level", "value" };
        io.insert_string(path, "debug");
        ASSERT_TRUE(io.update_string(path, "error"));
        ASSERT_EQ(io.get_string(path), "error");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_MixedNestedReadWriteAsync) {
        QLogicaeCore::JsonFileIO io("test.json");
        QLogicaeCore::JsonPath path = { "service", "config", "version", "id" };
        std::vector<std::future<bool>> writes;

        for (int i = 0; i < 10; ++i) {
            writes.push_back(io.update_double_async(path, static_cast<double>(i)));
        }

        for (auto& fut : writes) {
            ASSERT_TRUE(fut.get());
        }

        ASSERT_GE(io.get_double(path), 0.0);
        ASSERT_LE(io.get_double(path), 9.0);
    }

    TEST_F(JsonFileIOTest, Should_ReturnFalse_When_PathIsEmptyOnInsertString) {
        QLogicaeCore::JsonFileIO file("test.json");
        EXPECT_FALSE(file.insert_string({}, "value"));
    }

    TEST_F(JsonFileIOTest, Should_ReturnFalse_When_InsertPathIsNotObjectAndEndsWithArrayIndex) {
        QLogicaeCore::JsonFileIO file("test.json");
        std::vector<QLogicaeCore::JsonKey> path = { "tags", 0 }; 
        EXPECT_FALSE(file.insert_string(path, "invalid"));
    }

    TEST_F(JsonFileIOTest, Should_ReturnFalse_When_FileContainsInvalidJSON) {
        std::ofstream out("corrupt.json");
        out << R"({ "key": "value", )";
        out.close();

        QLogicaeCore::JsonFileIO file("corrupt.json");
        std::vector<QLogicaeCore::JsonKey> path = { "key" };
        EXPECT_FALSE(file.insert_string(path, "newValue"));
        std::remove("corrupt.json");
    }

    TEST_F(JsonFileIOTest, Should_ReturnEmpty_When_GetStringFromNonexistentPath) {
        QLogicaeCore::JsonFileIO file("test.json");
        std::vector<QLogicaeCore::JsonKey> path = { "user", "nickname" };
        EXPECT_EQ(file.get_string(path), "");
    }

    TEST_F(JsonFileIOTest, Should_ReturnFalse_When_GetBoolFromStringPath) {
        QLogicaeCore::JsonFileIO file("test.json");
        std::vector<QLogicaeCore::JsonKey> path = { "user", "name" };
        EXPECT_FALSE(file.get_bool(path));
    }

    TEST_F(JsonFileIOTest, Should_Throw_When_GetArrayFromStringPath) {
        QLogicaeCore::JsonFileIO file("test.json");
        std::vector<QLogicaeCore::JsonKey> path = { "user", "name" };
        EXPECT_THROW(file.get_array(path), std::runtime_error);
    }

    TEST_F(JsonFileIOTest, Should_Throw_When_GetObjectFromNullPath) {
        QLogicaeCore::JsonFileIO file("test.json");
        std::vector<QLogicaeCore::JsonKey> path = { "user", "meta" };
        EXPECT_THROW(file.get_object(path), std::runtime_error);
    }

    TEST_F(JsonFileIOTest, Should_Succeed_When_ConcurrentInsertOperations) {
        QLogicaeCore::JsonFileIO file("test.json");
        std::vector<QLogicaeCore::JsonKey> path1 = { "user", "email" };
        std::vector<QLogicaeCore::JsonKey> path2 = { "user", "address" };

        auto f1 = std::async(std::launch::async, [&]() {
            return file.insert_string(path1, "alice@example.com");
            });

        auto f2 = std::async(std::launch::async, [&]() {
            return file.insert_string(path2, "456 Broadway");
            });

        EXPECT_TRUE(f1.get());
        EXPECT_TRUE(f2.get());
    }

    TEST_F(JsonFileIOTest, Should_CreatePath_When_UpdatingNonExistentPath) {
        QLogicaeCore::JsonFileIO file("test.json");
        std::vector<QLogicaeCore::JsonKey> path = { "user", "status" };
        EXPECT_TRUE(file.update_string(path, "pending"));

        std::string value = file.get_string(path);
        EXPECT_EQ(value, "pending");
    }

    TEST_F(JsonFileIOTest, Should_Expect_Content_When_ReadAsyncIsUsed)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        io.insert_string({ "key" }, "value");
        auto future = io.read_async();
        ASSERT_TRUE(future.get().find("value") != std::string::npos);
    }

    TEST_F(JsonFileIOTest, Should_WriteSuccessfully_When_UsingWriteAsync)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        std::string content = R"({"x":1})";
        auto future = io.write_async(content);
        ASSERT_TRUE(future.get());
        ASSERT_EQ(io.read(), content);
    }

    TEST_F(JsonFileIOTest, Should_Expect_Success_When_UsingWrite)
    {
        QLogicaeCore::JsonFileIO io("test.json");
        std::string content = R"({"direct":"write"})";
        ASSERT_TRUE(io.write(content));
        ASSERT_EQ(io.get_string({ "direct" }), "write");
    }
}

