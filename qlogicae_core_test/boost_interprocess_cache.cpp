#include "pch.hpp"

#include "result.hpp"
#include "boost_interprocess_cache.hpp"

namespace QLogicaeCoreTest
{
    class SharedMemoryCacheTest : public ::testing::Test
    {
    protected:
        SharedMemoryCacheTest()
            : cache("TestCache", QLogicaeCore::BytesSize::KB_1)
        {
        }

        QLogicaeCore::BoostInterprocessCache cache;
    };

    class SharedMemoryCacheParameterizedTest
        : public SharedMemoryCacheTest
        , public ::testing::WithParamInterface<const char*>
    {
    };

    TEST_F(SharedMemoryCacheTest, Should_WriteAndRead_SingleKey)
    {
        QLogicaeCore::Result<void> write_result;
        cache.write("key1", "value1", write_result);
        EXPECT_TRUE(write_result.get_is_successful());

        QLogicaeCore::Result<const char*> read_result;
        cache.read("key1", read_result);
        EXPECT_TRUE(read_result.get_is_successful());
        EXPECT_STREQ(read_result.get_data(), "value1");
    }

    TEST_F(SharedMemoryCacheTest, Should_ReturnFalseForNonexistentKey)
    {
        EXPECT_FALSE(cache.is_key_found("nonexistent"));
    }

    TEST_F(SharedMemoryCacheTest, Should_RemoveKeySuccessfully)
    {
        QLogicaeCore::Result<void> write_result;
        cache.write("remove_key", "temp", write_result);

        QLogicaeCore::Result<void> remove_result;
        cache.remove("remove_key", remove_result);
        EXPECT_TRUE(remove_result.get_is_successful());
        EXPECT_FALSE(cache.is_key_found("remove_key"));
    }

    TEST_F(SharedMemoryCacheTest, Should_ClearAllKeys)
    {
        QLogicaeCore::Result<void> result;
        cache.write("k1", "v1", result);
        cache.write("k2", "v2", result);

        cache.clear(result);
        EXPECT_TRUE(result.get_is_successful());
        EXPECT_FALSE(cache.is_key_found("k1"));
        EXPECT_FALSE(cache.is_key_found("k2"));
    }

    TEST_F(SharedMemoryCacheTest, Should_WriteAndReadBatch)
    {
        std::unordered_map<const char*, const char*> items{
            {"a", "1"},
            {"b", "2"},
            {"c", "3"}
        };
        QLogicaeCore::Result<void> result;
        cache.write_batch(items, result);
        EXPECT_TRUE(result.get_is_successful());

        std::unordered_map<const char*, const char*> out;
        cache.read_batch({ "a", "b", "c" }, out, result);
        EXPECT_TRUE(result.get_is_successful());
        EXPECT_STREQ(out["a"], "1");
        EXPECT_STREQ(out["b"], "2");
        EXPECT_STREQ(out["c"], "3");
    }

    TEST_F(SharedMemoryCacheTest, Should_RemoveBatchKeys)
    {
        QLogicaeCore::Result<void> result;
        cache.write("x", "10", result);
        cache.write("y", "20", result);

        cache.remove_batch({ "x", "y" }, result);
        EXPECT_TRUE(result.get_is_successful());
        EXPECT_FALSE(cache.is_key_found("x"));
        EXPECT_FALSE(cache.is_key_found("y"));
    }

    TEST_F(SharedMemoryCacheTest, Should_HandleAsyncOperations)
    {
        QLogicaeCore::Result<void> write_result;
        auto write_future = cache.write_async("async_key", "async_val", write_result);
        write_future.get();
        EXPECT_TRUE(write_result.get_is_successful());

        QLogicaeCore::Result<const char*> read_result;
        auto read_future = cache.read_async("async_key", read_result);
        read_future.get();
        EXPECT_TRUE(read_result.get_is_successful());
        EXPECT_STREQ(read_result.get_data(), "async_val");

        auto found_future = cache.is_key_found_async("async_key");
        EXPECT_TRUE(found_future.get());
    }

    TEST_F(SharedMemoryCacheTest, Should_HandleMultithreadedWrites)
    {
        QLogicaeCore::Result<void> result1;
        QLogicaeCore::Result<void> result2;
        auto t1 = std::thread([this, &result1]() { cache.write("mt_key", "val1", result1); });
        auto t2 = std::thread([this, &result2]() { cache.write("mt_key", "val2", result2); });
        t1.join();
        t2.join();
        EXPECT_TRUE(result1.get_is_successful());
        EXPECT_TRUE(result2.get_is_successful());

        QLogicaeCore::Result<const char*> read_result;
        cache.read("mt_key", read_result);
        EXPECT_TRUE(read_result.get_is_successful());
        std::string val(read_result.get_data());
        EXPECT_TRUE(val == "val1" || val == "val2");
    }

    INSTANTIATE_TEST_CASE_P(EmptyAndValidKeys, SharedMemoryCacheParameterizedTest,
        ::testing::Values("", "param_key"));

    TEST_P(SharedMemoryCacheParameterizedTest, Should_HandleEdgeCaseKeys)
    {
        const char* key = GetParam();
        QLogicaeCore::Result<void> write_result;
        cache.write(key, "param_val", write_result);
        EXPECT_TRUE(write_result.get_is_successful());

        QLogicaeCore::Result<const char*> read_result;
        cache.read(key, read_result);
        EXPECT_TRUE(read_result.get_is_successful());
        EXPECT_STREQ(read_result.get_data(), "param_val");
    }

}