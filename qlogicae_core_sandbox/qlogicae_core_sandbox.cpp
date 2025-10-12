#pragma once

#include "pch.h"

using namespace QLogicaeCore;

int main()
{
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

    /*

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


    bool ea;

    std::cin >> ea;

    return 0;
}


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
