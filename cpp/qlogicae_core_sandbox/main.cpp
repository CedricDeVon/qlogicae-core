#include "pch.hpp"

#include "main.hpp"

static const int WARMUP = 1;
static const int MINIMUM_EPOCH = 100;
static const int BENCHMARK_COUNT = 1;



int main(int, char**)
{
    ankerl::nanobench::Bench bench;
    bench
        .minEpochIterations(MINIMUM_EPOCH)
        .relative(true)
        .warmup(WARMUP);

    // run_unordered_map_benchmarks(bench);
    
    return 0;
}

namespace QLogicaeCoreSandbox
{

}


/*

void run_unordered_map_benchmarks(ankerl::nanobench::Bench& bench) // STD
{
    std::vector<int> data(BENCHMARK_COUNT);

    {
        std::unordered_map<int, int> std_map;
        for (int v : data) std_map[v] = v;
        volatile int std_val = 0;
        bench.run("read_one_std_map", [&] { std_val = std_map[0]; });
    }

    {
        boost::unordered_map<int, int> boost_map;
        for (int v : data) boost_map[v] = v;
        volatile int boost_val = 0;
        bench.run("read_one_boost_map", [&] { boost_val = boost_map[0]; });
    }

    {
        absl::flat_hash_map<int, int> absl_map;
        for (int v : data) absl_map[v] = v;
        volatile int absl_val = 0;
        bench.run("read_one_absl_map", [&] { absl_val = absl_map[0]; });
    }

    {
        std::unordered_map<int, int> std_map;
        for (int v : data) std_map[v] = v;
        volatile int std_sum = 0;
        bench.run("read_all_std_map", [&] { for (auto& [k, v] : std_map) std_sum += v; });
    }

    {
        boost::unordered_map<int, int> boost_map;
        for (int v : data) boost_map[v] = v;
        volatile int boost_sum = 0;
        bench.run("read_all_boost_map", [&] { for (auto& [k, v] : boost_map) boost_sum += v; });
    }

    {
        absl::flat_hash_map<int, int> absl_map;
        for (int v : data) absl_map[v] = v;
        volatile int absl_sum = 0;
        bench.run("read_all_absl_map", [&] { for (auto& [k, v] : absl_map) absl_sum += v; });
    }

    {
        std::unordered_map<int, int> std_map;
        for (int v : data) std_map[v] = v;
        bench.run("update_one_std_map", [&] { std_map[0] = 1; });
    }

    {
        boost::unordered_map<int, int> boost_map;
        for (int v : data) boost_map[v] = v;
        bench.run("update_one_boost_map", [&] { boost_map[0] = 1; });
    }

    {
        absl::flat_hash_map<int, int> absl_map;
        for (int v : data) absl_map[v] = v;
        bench.run("update_one_absl_map", [&] { absl_map[0] = 1; });
    }

    {
        std::unordered_map<int, int> std_map;
        for (int v : data) std_map[v] = v;
        bench.run("update_all_std_map", [&] { for (auto& [k, v] : std_map) v += 1; });
    }

    {
        boost::unordered_map<int, int> boost_map;
        for (int v : data) boost_map[v] = v;
        bench.run("update_all_boost_map", [&] { for (auto& [k, v] : boost_map) v += 1; });
    }

    {
        absl::flat_hash_map<int, int> absl_map;
        for (int v : data) absl_map[v] = v;
        bench.run("update_all_absl_map", [&] { for (auto& [k, v] : absl_map) v += 1; });
    }

    {
        bench.run("remove_one_std_map", [&] {
            std::unordered_map<int, int> std_map;
            for (int v : data) std_map[v] = v;
            std_map.erase(0);
            });
    }

    {
        bench.run("remove_one_boost_map", [&] {
            boost::unordered_map<int, int> boost_map;
            for (int v : data) boost_map[v] = v;
            boost_map.erase(0);
            });
    }

    {
        bench.run("remove_one_absl_map", [&] {
            absl::flat_hash_map<int, int> absl_map;
            for (int v : data) absl_map[v] = v;
            absl_map.erase(0);
            });
    }
}



void run_string_concat_benchmarks(ankerl::nanobench::Bench& bench) // STD
{
    size_t i;
    std::string result_1;
    result_1.reserve(BENCHMARK_COUNT);

    boost::container::string result_2;
    result_2.reserve(BENCHMARK_COUNT);

    std::string result_3;
    result_3.reserve(BENCHMARK_COUNT);

    std::string result_4;
    result_4.reserve(BENCHMARK_COUNT);

    boost::container::string result_5;
    result_5.reserve(BENCHMARK_COUNT);

    std::string result_6;
    result_6.reserve(BENCHMARK_COUNT);

    std::string base = "0";
    boost::container::string boost_base = "0";

    bench.run("concat_two_std_string", [&]
        {
            result_1 = base + base;
        }
    );

    bench.run("concat_two_boost_string", [&]
        {
            result_2 = boost_base + boost_base;
        }
    );

    bench.run("concat_two_absl_strcat", [&]
        {
            result_3 = absl::StrCat(base, base);
        }
    );

    bench.run("concat_all_std_string", [&]
        {
            for (i = 0; i < BENCHMARK_COUNT; ++i) result_4 += base + base;
        }
    );

    bench.run("concat_all_boost_string", [&]
        {
            for (i = 0; i < BENCHMARK_COUNT; ++i) result_5 += boost_base + boost_base;
        }
    );

    bench.run("concat_all_absl_strcat", [&]
        {
            for (i = 0; i < BENCHMARK_COUNT; ++i) result_6 += absl::StrCat(base, base);
        }
    );
}

void run_double_string_conversion_benchmarks(ankerl::nanobench::Bench& bench) // ABSL
{
    size_t i;
    const double base_double = 3.141592653589793;
    double d, tmp;
    std::string s1, s3;
    boost::container::string s2;

    s1.reserve(32);
    s2.reserve(32);
    s3.reserve(32);

    bench.run("double_to_string_std", [&]
        {
            s1 = std::to_string(base_double);
        }
    );

    bench.run("double_to_string_boost", [&]
        {
            s2 = boost::lexical_cast<boost::container::string>(base_double);
        }
    );

    bench.run("double_to_string_absl", [&]
        {
            s3 = absl::StrFormat("%f", base_double);
        }
    );

    bench.run("string_to_double_std", [&]
        {
            d = std::stod(s1);
        }
    );

    bench.run("string_to_double_boost", [&]
        {
            d = boost::lexical_cast<double>(s2);
        }
    );

    bench.run("string_to_double_absl", [&]
        {
            absl::SimpleAtod(s3.c_str(), &tmp);
            d = tmp;
        }
    );



    bench.run("multiple double_to_string_std", [&]
        {
            for (i = 0; i < BENCHMARK_COUNT; ++i) s1 = std::to_string(base_double);
        }
    );

    bench.run("multiple double_to_string_boost", [&]
        {
            for (i = 0; i < BENCHMARK_COUNT; ++i) s2 = boost::lexical_cast<boost::container::string>(base_double);
        }
    );

    bench.run("multiple double_to_string_absl", [&]
        {
            for (i = 0; i < BENCHMARK_COUNT; ++i) s3 = absl::StrFormat("%f", base_double);
        }
    );

    bench.run("multiple string_to_double_std", [&]
        {
            for (i = 0; i < BENCHMARK_COUNT; ++i) d = std::stod(s1);
        }
    );

    bench.run("multiple string_to_double_boost", [&]
        {
            for (i = 0; i < BENCHMARK_COUNT; ++i) d = boost::lexical_cast<double>(s2);
        }
    );

    bench.run("multiple string_to_double_absl", [&]
        {
            for (i = 0; i < BENCHMARK_COUNT; ++i)
            {
                absl::SimpleAtod(s3.c_str(), &tmp);
                d = tmp;
            }
        }
    );
}


void run_vector_benchmarks(ankerl::nanobench::Bench& bench) // STD
{
    std::vector<int> data(BENCHMARK_COUNT);

    {
        std::vector<int> std_vec(data.begin(), data.end());
        volatile int std_val = 0;

        bench.run("read_one_std_vector", [&] { std_val = std_vec[0]; });
    }

    {
        boost::container::vector<int> boost_vec(data.begin(), data.end());
        volatile int boost_val = 0;

        bench.run("read_one_boost_vector", [&] { boost_val = boost_vec[0]; });
    }

    {
        absl::InlinedVector<int, BENCHMARK_COUNT> absl_vec(data.begin(), data.end());
        volatile int absl_val = 0;

        bench.run("read_one_absl_vector", [&] { absl_val = absl_vec[0]; });
    }

    {
        std::vector<int> std_vec(data.begin(), data.end());
        volatile int std_sum = 0;

        bench.run("read_all_std_vector", [&] { for (int v : std_vec) std_sum += v; });
    }

    {
        boost::container::vector<int> boost_vec(data.begin(), data.end());
        volatile int boost_sum = 0;

        bench.run("read_all_boost_vector", [&] { for (int v : boost_vec) boost_sum += v; });
    }

    {
        absl::InlinedVector<int, BENCHMARK_COUNT> absl_vec(data.begin(), data.end());
        volatile int absl_sum = 0;

        bench.run("read_all_absl_vector", [&] { for (int v : absl_vec) absl_sum += v; });
    }

    {
        std::vector<int> std_vec(data.begin(), data.end());

        bench.run("update_one_std_vector", [&] { std_vec[0] = 1; });
    }

    {
        boost::container::vector<int> boost_vec(data.begin(), data.end());

        bench.run("update_one_boost_vector", [&] { boost_vec[0] = 1; });
    }

    {
        absl::InlinedVector<int, BENCHMARK_COUNT> absl_vec(data.begin(), data.end());

        bench.run("update_one_absl_vector", [&] { absl_vec[0] = 1; });
    }

    {
        std::vector<int> std_vec(data.begin(), data.end());

        bench.run("update_all_std_vector", [&] { for (int& v : std_vec) v += 1; });
    }

    {
        boost::container::vector<int> boost_vec(data.begin(), data.end());

        bench.run("update_all_boost_vector", [&] { for (int& v : boost_vec) v += 1; });
    }

    {
        absl::InlinedVector<int, BENCHMARK_COUNT> absl_vec(data.begin(), data.end());

        bench.run("update_all_absl_vector", [&] { for (int& v : absl_vec) v += 1; });
    }

    {
        bench.run("remove_one_std_vector", [&] {
            std::vector<int> std_vec(data.begin(), data.end());
            std_vec.erase(std_vec.begin());
            });
    }

    {
        bench.run("remove_one_boost_vector", [&] {
            boost::container::vector<int> boost_vec(data.begin(), data.end());
            boost_vec.erase(boost_vec.begin());
            });
    }

    {
        bench.run("remove_one_absl_vector", [&] {
            absl::InlinedVector<int, BENCHMARK_COUNT> absl_vec(data.begin(), data.end());
            absl_vec.erase(absl_vec.begin());
            });
    }
}













void run_list_benchmarks(ankerl::nanobench::Bench& bench, const std::vector<int>& data)
{
    {
        std::list<int> std_list(data.begin(), data.end());

        auto std_it = std_list.begin();
        volatile int std_val = 0;

        bench.run("read_one_std_list", [&] { std_val = *std_it; });
    }

    {
        boost::container::list<int> boost_list(data.begin(), data.end());
        auto boost_it = boost_list.begin();
        volatile int boost_val = 0;

        bench.run("read_one_boost_list", [&] { boost_val = *boost_it; });
    }

    {
        absl::InlinedVector<int, BENCHMARK_COUNT> absl_list(data.begin(), data.end());

        for (int v : data) absl_list.push_back(v);
        volatile int absl_val = 0;

        bench.run("read_one_absl_list", [&] { absl_val = absl_list[0]; });
    }

    {
        std::list<int> std_list(data.begin(), data.end());
        volatile int std_sum = 0;
        bench.run("read_all_std_list", [&] { for (int v : std_list) std_sum += v; });
    }

    {
        boost::container::list<int> boost_list(data.begin(), data.end());
        volatile int boost_sum = 0;
        bench.run("read_all_boost_list", [&] { for (int v : boost_list) boost_sum += v; });
    }

    {
        absl::InlinedVector<int, BENCHMARK_COUNT> absl_list(data.begin(), data.end());

        for (int v : data) absl_list.push_back(v);
        volatile int absl_sum = 0;
        bench.run("read_all_absl_list", [&] { for (int v : absl_list) absl_sum += v; });
    }

    {
        std::list<int> std_list(data.begin(), data.end());
        auto it = std_list.begin();
        bench.run("update_one_std_list", [&] { *it = 1; });
    }

    {
        boost::container::list<int> boost_list(data.begin(), data.end());
        auto it = boost_list.begin();
        bench.run("update_one_boost_list", [&] { *it = 1; });
    }

    {
        absl::InlinedVector<int, BENCHMARK_COUNT> absl_list(data.begin(), data.end());

        for (int v : data) absl_list.push_back(v);
        bench.run("update_one_absl_list", [&] { absl_list[0] = 1; });
    }

    {
        std::list<int> std_list(data.begin(), data.end());
        bench.run("update_all_std_list", [&] { for (int& v : std_list) v += 1; });
    }

    {
        boost::container::list<int> boost_list(data.begin(), data.end());
        bench.run("update_all_boost_list", [&] { for (int& v : boost_list) v += 1; });
    }

    {
        absl::InlinedVector<int, BENCHMARK_COUNT> absl_list(data.begin(), data.end());

        for (int v : data) absl_list.push_back(v);
        bench.run("update_all_absl_list", [&] { for (int& v : absl_list) v += 1; });
    }

    {
        bench.run("remove_one_std_list", [&] {
            std::list<int> std_list(data.begin(), data.end());
            std_list.pop_front();
            });
    }

    {
        bench.run("remove_one_boost_list", [&] {
            boost::container::list<int> boost_list(data.begin(), data.end());
            boost_list.pop_front();
            });
    }

    {
        bench.run("remove_one_absl_list", [&] {
            absl::InlinedVector<int, BENCHMARK_COUNT> absl_list(data.begin(), data.end());


            for (int v : data) absl_list.push_back(v);
            absl_list.erase(absl_list.begin());
            });
    }

    {
        std::list<int> std_list(data.begin(), data.end());
        bench.run("remove_all_std_list", [&] {
            while (!std_list.empty()) std_list.pop_front();
            });
    }

    {
        boost::container::list<int> boost_list(data.begin(), data.end());
        bench.run("remove_all_boost_list", [&] {
            while (!boost_list.empty()) boost_list.pop_front();
            });
    }

    {
        absl::InlinedVector<int, BENCHMARK_COUNT> absl_list(data.begin(), data.end());

        for (int v : data) absl_list.push_back(v);
        bench.run("remove_all_absl_list", [&] {
            while (!absl_list.empty()) absl_list.erase(absl_list.begin());
            });
    }
}






*/