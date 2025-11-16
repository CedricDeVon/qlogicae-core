#pragma once

#include "pch.h"

int main(void)
{
    try
    {
        for (int i = 0; i < 1000; ++i)
        {
            QLogicaeCore::LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::commit_transaction()",
                "Sample"
            );
        }

        // QLogicaeCore::UTILITIES.BOOST_ASIO_POOL.join();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << "\n";
    }    

    bool exit_code;
    std::cin >> exit_code;

    return 0;
}

/*
static std::string make_large_string(std::size_t len)
{
    std::string s;
    s.reserve(len);
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (std::size_t i = 0; i < len; ++i)
        s.push_back(charset[i % (sizeof(charset) - 1)]);
    return s;
}

static void benchmark_boost_cache()
{
    try
    {
        using namespace ankerl::nanobench;

        QLogicaeCore::BoostInterprocessCache cache("BoostInterprocessCache", QLogicaeCore::BytesSize::MB_4);
        QLogicaeCore::RocksDBDatabase db;
        db.setup("rocks_bench_db");


        std::string key = "test_key";
        std::string value = make_large_string(1'000'000);
        const char* key_1 = key.c_str();
        const char* value_1 = value.c_str();

        QLogicaeCore::Result<void> write_result;
        QLogicaeCore::Result<const char*> read_result;

        Bench bench;
        bench.title("BoostInterprocessCache Benchmark")
            .unit("ops")
            .minEpochIterations(1'000);

        bench.run("Boost: Write", [&] {
            cache.write(key_1, value_1, write_result);
            });

        bench.run("Boost: Read", [&] {
            cache.read(key_1, read_result);
            });

        bench.run("RocksDB: write", [&]
            {
                db.begin_batch();
                db.batch_set_value(key, value);
                db.batch_execute();
            });

        bench.run("RocksDB: read", [&]
            {
                db.get_value<std::string>(key);
            });

    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}

int main()
{
    using namespace ankerl;

    std::mutex _m;

    std::string template_str(1'000'000, 'x');

    nanobench::Bench bench;
    bench.minEpochIterations(100).warmup(1);

    bench.run("with", [&] {
        std::scoped_lock lock(_m);

        std::string src = template_str;
        std::string dst;
        dst = src;
        });

    bench.run("without", [&] {
        std::string src = template_str;
        std::string dst;
        dst = src;
        });
    bool ea;

    std::cin >> ea;

    return 0;
}

*/
