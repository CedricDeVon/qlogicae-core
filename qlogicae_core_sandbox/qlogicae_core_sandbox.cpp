#pragma once

#include "pch.h"

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

    // boost::interprocess::shared_memory_object::remove("BoostInterprocessCache");
    // std::cout << "\n[Benchmark] Boost.Interprocess BoostInterprocessCache write_batch()\n";

    /*
    
    */


    /*

    cache.write_one(key, value, result);
    cache.read_one(key, read_result);

    std::cout << read_result.get_is_successful() << " " << read_result.get_data() << "\n";


    BoostInterprocessCache cache("BenchCache"); // 64MB shared mem
    Result<void> result;
    Result<void> load_result;
    Result<std::string> read_result;

    const char* key = "key";
    const char* value = make_large_string(1'000'000).c_str();

    ankerl::nanobench::Bench bench;
    bench.title("Boost.Interprocess Cache Benchmark");
    bench.unit("ops");
    bench.minEpochIterations(1);
    
    bench.run("Boost.Interprocess: write", [&]
    {
        cache.write_one(key, value, result);
    });

    bench.run("Boost.Interprocess: read", [&]
    {
        cache.read_one(key, read_result);
    });
    
    */
   
}

static void benchmark_rocksdb()
{
    
}

int main()
{
    benchmark_boost_cache();
    benchmark_rocksdb();

    bool ea;

    std::cin >> ea;

    return 0;
}

/*
const char* filename = "boost_cache.dat";
bip::shared_memory_object::remove(filename);

bip::managed_mapped_file mfile(bip::create_only, filename, 256ull * 1024ull * 1024ull);

using CharAllocator = bip::allocator<char, bip::managed_mapped_file::segment_manager>;
using MappedString = bip::basic_string<char, std::char_traits<char>, CharAllocator>;

CharAllocator alloc_inst(mfile.get_segment_manager());
MappedString* stored_str = mfile.construct<MappedString>("CacheValue")(alloc_inst);

const std::string key = "sample_key";
const std::string value(1'000, 'X');

{
    Bench bench;
    bench.title("Boost Interprocess (Single Key-Value)");
    bench.relative(true);
    bench.minEpochIterations(1);

    bench.run("Boost Write", [&] {
        stored_str->assign(value.begin(), value.end());
        });
}

{
    Bench bench;
    bench.title("Boost Interprocess (Single Key-Value)");
    bench.relative(true);
    bench.minEpochIterations(1);

    std::string read_buffer;
    read_buffer.reserve(1'000);

    bench.run("Boost Read", [&] {
        read_buffer.assign(stored_str->begin(), stored_str->end());
        });
}

*/
    // Cleanup
    // 

    /*
    

int main()
{
   

    
    follow these requirements:

    
    using namespace QLogicaeCore;
    using namespace ankerl::nanobench;

    const std::string key = "sample_key";
    const std::string value(1'000'000, 'X');

    std::string json_str;
    std::string parsed_value;

    Bench().title("RapidJSON (Single Key-Value)")
        .minEpochIterations(325631)
        .run("RapidJSON Write", [&] {
        rapidjson::Document doc;
        doc.SetObject();
        auto& alloc = doc.GetAllocator();
        doc.AddMember(
            rapidjson::Value(key.c_str(), alloc),
            rapidjson::Value(value.c_str(), alloc),
            alloc
        );
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        json_str = buffer.GetString();
            })
        .run("RapidJSON Read", [&] {
        rapidjson::Document doc;
        doc.Parse(json_str.c_str());
        parsed_value = doc[key.c_str()].GetString();
            });

    RocksDBDatabase db;
    db.setup("rocks_bench_single", RocksDBConfig{});

    Bench().title("RocksDB (Single Key-Value)")
        .minEpochIterations(1090)
        .run("RocksDB Write (sync)", [&] {
        db.begin_batch();
        db.batch_set_value<std::string>(key, value);
        db.batch_execute();
        })
        .run("RocksDB Read (sync)", [&] {
        auto result = db.get_value<std::string>(key);
            });
 
    */

    /*
    ankerl::nanobench::Bench bench;
    bench.title("Addition Test Performance")
        .unit("op")
        .warmup(10000)
        .minEpochIterations(1464592398)
        .relative(true)
        .performanceCounters(true);

    QLogicaeCore::Result<double> res;

    bench.run("QLogicaeCore::Result.set_to_success() 1", [&]
        {
            res.set_data(101);
        }
    );

    bench.run("QLogicaeCore::Result.set_to_success() 2", [&]
        {
            res.set_to_success();
        }
    );

    bench.run("QLogicaeCore::Result.set_to_success() 3", [&]
        {
            res.set_to_success(101);
        }
    );

    bench.run("QLogicaeCore::Result.set_to_failure() 1", [&]
        {
            res.set_to_failure();
        }
    );

    bench.run("QLogicaeCore::Result.set_to_failure() 2", [&]
        {
            res.set_to_failure(101);
        }
    );

    bench.run("QLogicaeCore::Result.set_data() 1", [&]
        {
            res.set_data(101);
        }
    );

    bench.run("QLogicaeCore::Result.set_data() 2", [&]
        {
            res.data = 101;
        }
    );

    bench.run("QLogicaeCore::Result.set_to_success() 2", [&]
        {
            res.set_to_success(101);
        }
    );

    bench.run("QLogicaeCore::Result.set_to_success() 2", [&]
        {
            res.is_successful = true;
            res.data = 101;
        }
    );

    bench.run("QLogicaeCore::Result.get_data() 1", [&]
        {
            double a = res.get_data();
        }
    );

    bench.run("QLogicaeCore::Result.get_data() 2", [&]
        {
            double a = res.data;
        }
    );
    bench.run("QLogicaeCore::Result<double>::to_success() 2", [&]
        {
            Result<double>::to_success(res, 101);
        }
    );

    bench.run("QLogicaeCore::Result<double>::to_success() 2", [&]
        {
            Result<double>::to_success(res, 101);
        }
    );

    bench.run("= {}", [&]
        {
            res.is_successful = true;
            res.payload = 101;
        }
    );
    */


/*
    QLogicaeCore::Application& QLOGICAE_APPLICATION =
        QLogicaeCore::Application::get_instance();

    std::cout << QLogicaeCore::UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_ENVIRONMENT_FILE_PATH;
    std::cout << "Enter to exit\n";

ankerl::nanobench::Bench bench;
bench.title("Addition Test Performance")
.unit("op")
.warmup(10000)
.minEpochIterations(12096615)
.relative(true)
.performanceCounters(true);

double a = 1.23, b = 4.56;
double result_double = 0.0;
TemplateResult1<double> d;

bench.run("test_a (raw double add)", [&] {
    double f = test_a(a, b);
    ankerl::nanobench::doNotOptimizeAway(result_double);
    });

bench.run("test_b (struct Result)", [&] {
    Result f = test_b(a, b);
    });

bench.run("test_b_a (struct Result)", [&] {
    TemplateResult1<double> f = test_b_a(a, b);
    });

bench.run("test_b_a_a (struct Result)", [&] {
    test_b_a_a(d, a, b);
    });

bench.run("test_b_a_b (struct Result)", [&] {
    test_b_a_b(d.data, a, b);
    });
bench.run("test_b_b (struct Result)", [&] {
    TemplateResult1<double> f = test_b_b(a, b);
    });

bench.run("test_b_c (struct Result)", [&] {
    TemplateResult1<double> f = test_b_c(a, b);
    });

bench.run("test_c (AbstractResult<>)", [&] {
    QLogicaeCore::AbstractResult<double> d = test_c(a, b);

    });

bench.run("test_c_a (AbstractResult<>)", [&] {
    QLogicaeCore::AbstractResult<double> d = test_c_a(a, b);

    });

bench.run("test_b_a (struct Result)", [&] {
    TemplateResult1<double> f = test_b_a(a, b);
    });

bench.run("test_b_d (struct Result)", [&] {
    TemplateResult2<double> f = test_b_d(a, b);
    });

bench.run("test_b_e (struct Result)", [&] {
    TemplateResult2<double> f = test_b_e(a, b);
    });
*/

/*

struct AbstractInput
{
    std::string original = "original";
};

struct InputOne : AbstractInput
{
    std::string another = "another";
};

void f_a(AbstractInput a)
{

}

int main()
{
    QLogicaeCore::Application& QLOGICAE_APPLICATION =
        QLogicaeCore::Application::get_instance();

    std::cout << QLogicaeCore::UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_ENVIRONMENT_FILE_PATH;
    std::cout << "Enter to exit\n";

    f_a(InputOne { . })

    bool ea;

    std::cin >> ea;

    return 0;
}

*/

/*
* struct Result
{
    bool is_successful = true;
    std::any data;
    std::string message;
};

template <typename Type>
struct TemplateResult1
{
    bool is_successful = true;
    Type data;
    std::string message;
};

template <typename Type>
struct alignas(16) TemplateResult2
{
    bool is_successful = true;
    Type data;
    std::string message;
};

double test_a(double a, double b)
{
    return a + b;
}

Result test_b(double a, double b)
{
    return {
        .data = (a + b)
    };
}

TemplateResult1<double> test_b_a(double a, double b)
{
    return TemplateResult1<double> {
        .data = (a + b)
    };
}

void test_b_a_a(TemplateResult1<double>& r, double a, double b)
{
    r.data = a + b;
}

void test_b_a_b(double& r, double a, double b)
{
    // r = a + b;
}

TemplateResult1<double> test_b_b(double a, double b)
{
    try
    {
        return TemplateResult1<double> {
            .data = (a + b)
        };
    }
    catch (const std::exception& exception)
    {
        return TemplateResult1<double> {
            .data = (a + b)
        };
    }
}

TemplateResult1<double> test_b_c(double a, double b)
{
    try
    {
        return TemplateResult1<double> {
            .data = (a + b)
        };
    }
    catch (...)
    {
        return TemplateResult1<double> {
            .data = (a + b)
        };
    }
}

TemplateResult2<double> test_b_d(double a, double b)
{
    return TemplateResult2<double> {
        .data = (a + b)
    };
}

TemplateResult2<double> test_b_e(double a, double b)
{
    try
    {
        return TemplateResult2<double> {
            .data = (a + b)
        };
    }
    catch (const std::exception& exception)
    {
        return TemplateResult2<double> {
            .data = (a + b)
        };
    }
}

QLogicaeCore::AbstractResult<double> test_c(double a, double b)
{
    return QLogicaeCore::GoodResult<double>(a + b);
}

QLogicaeCore::AbstractResult<double> test_c_a(double a, double b)
{
    try
    {
        return QLogicaeCore::GoodResult<double>(a + b);
    }
    catch (const std::exception& exception)
    {
        return QLogicaeCore::GoodResult<double>(a + b);
    }
}

*/


/*

 class BoostInterprocessCache
    {
    public:
        using segment_t = boost::interprocess::managed_shared_memory;
        using manager_t = segment_t::segment_manager;
        using char_allocator_t = boost::interprocess::allocator<char, manager_t>;
        using string_t = boost::interprocess::basic_string<char, std::char_traits<char>, char_allocator_t>;
        using value_allocator_t = boost::interprocess::allocator<std::pair<const string_t, string_t>, manager_t>;
        using map_t = boost::interprocess::map<string_t, string_t, std::less<string_t>, value_allocator_t>;

    private:
        struct BoostInterprocessCacheSharedData
        {
            boost::interprocess::interprocess_mutex mutex;
            map_t map;

            BoostInterprocessCacheSharedData(const value_allocator_t& alloc)
                : map(std::less<string_t>(), alloc)
            {
            }
        };

        segment_t _segment;
        BoostInterprocessCacheSharedData* _data = nullptr;

    public:
        explicit BoostInterprocessCache(const char* name = "BoostInterprocessCache", const std::size_t& size = 65536)
            : _segment(boost::interprocess::open_or_create, name, size)
        {
            boost::interprocess::shared_memory_object::remove(name);

            _data = _segment.find_or_construct<BoostInterprocessCacheSharedData>("BoostInterprocessCacheSharedData")(
                value_allocator_t(_segment.get_segment_manager()));
        }

        void write(const char* key, const char* value, Result<void>& result)
        {
            boost::interprocess::scoped_lock lock(_data->mutex);

            string_t shm_key(key, _segment.get_segment_manager());
            string_t shm_value(value, _segment.get_segment_manager());

            auto& map = _data->map;
            auto it = map.find(shm_key);
            if (it != map.end())
            {
                it->second = shm_value;
            }
            else
            {
                map.emplace(std::move(shm_key), std::move(shm_value));
            }

            result.set_to_success();
        }

        void read(const char* key, Result<const char*>& result)
        {
            boost::interprocess::scoped_lock lock(_data->mutex);

            auto it = _data->map.find(string_t(key, _segment.get_segment_manager()));

            if (it != _data->map.end())
            {
                result.set_to_success(it->second.c_str());
            }
            else
            {
                result.set_to_failure("Key not found");
            }
        }
    };
*/