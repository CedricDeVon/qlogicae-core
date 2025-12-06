#include "pch.hpp"

#include "main.hpp"


int main(int argc, char** argv)
{       
    ankerl::nanobench::Bench bench;

    bench.minEpochIterations(1); 
    bench.relative(true);

    size_t n = 100'000'000;

    bench.run("'string_view' Concatenation", [&]
        {
            std::string result;
            for (size_t i = 0; i < n; ++i)
            {
                result = std::string_view("a");
            }
        }
    );
    bench.run("'string' Concatenation", [&]
        {
            std::string result;
            for (size_t i = 0; i < n; ++i)
            {
                result = std::string("a");
            }
        }
    );


    bool exit_code;
    std::cin >> exit_code;

    return 0;
}

namespace QLogicaeCppCoreBenchmark
{

}
