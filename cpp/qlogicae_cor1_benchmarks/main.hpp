#pragma once

#include "qlogicae/cor1/benchmarks/includes/application.hpp"

#include "qlogicae/cor1/includes/asynchronous_manager.hpp"

namespace Experiment10 // pure
{
    std::string extern_static_string_input_value = "0";

    std::string extern_static_string_output_value = "";
}

int main(int, char**);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int
)
{
    return main(__argc, __argv);
}

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_BENCHMARKS_NAMESPACE_NAME
{

}

struct NanobenchBenchmarkEpochIterationPair
{
    std::size_t epochs = 1;

    std::size_t iterations = 1;
};

struct NanobenchBenchmarkingTestCase
{
    std::string name = "";

    std::function<void()> callback = []() {};

    std::function<void()> before_test_callback = []() {};

    std::function<void()> after_test_callback = []() {};
};

struct NanobenchBenchmarkingTestSuite
{
    std::string name = "";

    size_t warmup_count = 1;

    bool is_relative = true;

    std::vector<NanobenchBenchmarkEpochIterationPair> epoch_iteration_pairs = {};

    std::vector<NanobenchBenchmarkingTestCase> test_cases = {};

    std::function<void()> before_test_suite_callback = []() {};

    std::function<void()> before_test_case_callback = []() {};

    std::function<void()> before_test_case_iteration_callback = []() {};

    std::function<void()> after_test_suite_callback = []() {};

    std::function<void()> after_test_case_callback = []() {};

    std::function<void()> after_test_case_iteration_callback = []() {};
};

std::string make_timestamp()
{
	auto now = std::chrono::system_clock::now();

	auto seconds =
		std::chrono::time_point_cast<std::chrono::seconds>(now);

	auto nanoseconds =
		std::chrono::duration_cast<std::chrono::nanoseconds>(
			now - seconds
		).count();

	std::time_t tt =
		std::chrono::system_clock::to_time_t(seconds);

	std::tm tm{};
	localtime_s(&tm, &tt);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
		<< '.' << std::setw(9) << std::setfill('0')
		<< nanoseconds;

	return oss.str();
}

void execute_nanobenchmark(
    const NanobenchBenchmarkingTestSuite& test_suite
)
{
	std::string timestamp_start = make_timestamp();
	
    const std::string test_suite_name =
        test_suite.name;

    const std::size_t test_suite_epoch_pair_count =
        test_suite.epoch_iteration_pairs.size();

    const std::size_t test_suite_case_count =
        test_suite.test_cases.size();

    const std::size_t test_suite_warmup_count =
        test_suite.warmup_count;

    const bool test_suite_is_relative =
        test_suite.is_relative;

    const std::function<void()>& before_test_suite_callback =
        test_suite.before_test_suite_callback;

    const std::function<void()>& after_test_suite_callback =
        test_suite.after_test_suite_callback;

    const std::function<void()>& before_test_case_callback =
        test_suite.before_test_case_callback;

    const std::function<void()>& after_test_case_callback =
        test_suite.after_test_case_callback;

    const std::function<void()>& before_test_case_iteration_callback =
        test_suite.before_test_case_iteration_callback;

    const std::function<void()>& after_test_case_iteration_callback =
        test_suite.after_test_case_iteration_callback;

    before_test_suite_callback();

    for (std::size_t epoch_index = 0;
        epoch_index < test_suite_epoch_pair_count;
        ++epoch_index)
    {
        before_test_case_callback();

        const auto& epoch_iteration_pair =
            test_suite.epoch_iteration_pairs[epoch_index];

        const std::size_t epochs =
            epoch_iteration_pair.epochs;

        const std::size_t iterations =
            epoch_iteration_pair.iterations;

        ankerl::nanobench::Bench benchmarker;
        benchmarker.minEpochIterations(epochs);
        benchmarker.warmup(test_suite_warmup_count);
        benchmarker.relative(test_suite_is_relative);

        for (std::size_t test_index = 0;
            test_index < test_suite_case_count;
            ++test_index)
        {
            const auto& test_case =
                test_suite.test_cases[test_index];

            const std::string test_case_name =
                test_case.name;

            const std::string benchmark_name =
                test_suite_name + " | " + test_case_name + " | " + std::to_string(iterations);

            const std::function<void()>& callback =
                test_case.callback;

            const std::function<void()>& before_test_callback =
                test_case.before_test_callback;

            const std::function<void()>& after_test_callback =
                test_case.after_test_callback;

            before_test_case_iteration_callback();

            before_test_callback();

            benchmarker.run(
                benchmark_name,
                [callback, iterations]()
                {
                    for (std::size_t index_3 = 0;
                        index_3 < iterations;
                        ++index_3
                        )
                    {
                        callback();
                    }
                }
            );

            after_test_callback();

            after_test_case_iteration_callback();
        }

		fast_io::io::println("");

        after_test_case_callback();
    }

    after_test_suite_callback();

	std::string timestamp_end = make_timestamp();

	fast_io::io::println("About");
	fast_io::io::println("- Timestamp Start:\t" + timestamp_start);
	fast_io::io::println("- Timestamp End:\t" + timestamp_end);
}


namespace RuntimeErrorThrowPerformance
{
	/*

	Conclusion:
	- failed edge cases should return immediately - do not throw
	- unexpected runtime errors should be handled via try-catch

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |                1.32 |      755,643,213.86 |    0.3% |      0.02 | `RuntimeErrorThrowPerformance__without_runtime_error_throw__1`
	|     0.1% |            2,598.22 |          384,878.60 |    0.1% |     31.60 | `RuntimeErrorThrowPerformance__with_runtime_error_throw_with_exception__1`
	|     0.1% |            2,274.42 |          439,672.63 |    0.0% |     27.55 | `RuntimeErrorThrowPerformance__with_runtime_error_throw_without_exception__1`

	|   100.0% |              965.28 |        1,035,967.09 |    0.2% |      0.01 | `RuntimeErrorThrowPerformance__without_runtime_error_throw__1000`
	|     0.0% |        2,611,936.28 |              382.86 |    0.2% |     31.61 | `RuntimeErrorThrowPerformance__with_runtime_error_throw_with_exception__1000`
	|     0.0% |        2,269,344.43 |              440.66 |    0.1% |     27.47 | `RuntimeErrorThrowPerformance__with_runtime_error_throw_without_exception__1000`

	|   100.0% |          956,200.00 |            1,045.81 |    0.2% |      0.01 | `RuntimeErrorThrowPerformance__without_runtime_error_throw__1000000`
	|     0.0% |    2,598,170,700.00 |                0.38 |    0.1% |     28.58 | `RuntimeErrorThrowPerformance__with_runtime_error_throw_with_exception__1000000`
	|     0.0% |    2,261,668,900.00 |                0.44 |    0.1% |     24.88 | `RuntimeErrorThrowPerformance__with_runtime_error_throw_without_exception__1000000`

	About
	- Timestamp Created: 8:50 AM, February 6, 2026

	*/



	class TestSubject1
	{
	public:
		static TestSubject1
			singleton;

		void without_runtime_error_throw()
		{
				
		}

		void with_runtime_error_throw_with_exception()
		{
			try
			{
				throw std::runtime_error("");
			}
			catch (const std::exception& exception)
			{

			}
		}

		void with_runtime_error_throw_without_exception()
		{
			try
			{
				throw std::runtime_error("");
			}
			catch (...)
			{

			}
		}
	};

	TestSubject1
		TestSubject1
			::singleton;

	void execute()
	{
		QLogicaeCppCore::RuntimeBenchmarkerTestSuite test_suite
		{
			.name = "RuntimeErrorThrowPerformance",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 1000000,
					.iterations = 1
				},
				{
					.epochs = 1000,
					.iterations = 1000
				},
				{
					.epochs = 1,
					.iterations = 1000000
				},
			},
			.test_cases =
			{
				{
					.name = "without_runtime_error_throw",
					.callback = []() { TestSubject1::singleton.without_runtime_error_throw(); }
				},
				{
					.name = "with_runtime_error_throw_with_exception",
					.callback = []() { TestSubject1::singleton.with_runtime_error_throw_with_exception(); }
				},
				{
					.name = "with_runtime_error_throw_without_exception",
					.callback = []() { TestSubject1::singleton.with_runtime_error_throw_without_exception(); }
				}
			}
		};

		QLogicaeCppCore::RuntimeBenchmarker::singleton.execute(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}



namespace BoostMutexLockAndDefensiveProgrammingRuntimePerformance
{
	/*

	Conclusion:
	- do wrap methods within a callback function, if performance is not a major concern

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |                1.23 |      816,135,754.36 |    1.5% |      1.49 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__empty_method__1`
	|   101.3% |                1.21 |      826,553,059.19 |    0.7% |      1.47 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__all_conditions_false__1`
	|    72.7% |                1.69 |      593,302,437.43 |    0.4% |      2.04 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_all_conditions_false_pre_edge_case_checking__1`
	|    51.1% |                2.40 |      416,976,601.25 |    0.1% |      2.91 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_all_conditions_false_post_edge_case_checking__1`
	|    10.8% |               11.36 |       88,004,974.63 |    0.1% |     13.77 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_true_and_all_conditions_false__1`
	|    51.0% |                2.40 |      416,537,089.47 |    0.2% |      2.91 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_all_conditions_false__1`
	|    10.8% |               11.36 |       88,061,945.94 |    0.1% |     13.74 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_true_and_no_conditions__1`
	|    56.7% |                2.16 |      462,535,168.64 |    0.2% |      2.62 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_no_conditions__1`

	|   100.0% |              969.12 |        1,031,858.72 |    0.3% |      1.06 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__empty_method__1000`
	|   100.1% |              968.26 |        1,032,780.57 |    0.1% |      1.06 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__all_conditions_false__1000`
	|    66.9% |            1,448.87 |          690,190.78 |    0.1% |      1.75 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_all_conditions_false_pre_edge_case_checking__1000`
	|    44.6% |            2,171.10 |          460,595.98 |    0.2% |      2.63 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_all_conditions_false_post_edge_case_checking__1000`
	|     8.6% |           11,314.51 |           88,382.06 |    0.1% |     13.69 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_true_and_all_conditions_false__1000`
	|    44.7% |            2,166.94 |          461,480.64 |    0.1% |      2.64 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_all_conditions_false__1000`
	|     8.6% |           11,313.16 |           88,392.63 |    0.1% |     13.93 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_true_and_no_conditions__1000`
	|    48.1% |            2,016.07 |          496,013.86 |    3.5% |      2.70 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_no_conditions__1000`

	|   100.0% |      112,998,500.00 |                8.85 |    3.2% |      1.23 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__empty_method__100000000`
	|   116.3% |       97,156,100.00 |               10.29 |    1.2% |      1.08 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__all_conditions_false__100000000`
	|    76.5% |      147,661,400.00 |                6.77 |    0.5% |      1.62 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_all_conditions_false_pre_edge_case_checking__100000000`
	|    52.4% |      215,809,600.00 |                4.63 |    0.1% |      2.38 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_all_conditions_false_post_edge_case_checking__100000000`
	|    10.0% |    1,133,210,400.00 |                0.88 |    0.1% |     12.47 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_true_and_all_conditions_false__100000000`
	|    52.2% |      216,363,500.00 |                4.62 |    0.2% |      2.38 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_all_conditions_false__100000000`
	|    10.0% |    1,132,939,200.00 |                0.88 |    0.2% |     12.51 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_true_and_no_conditions__100000000`
	|    58.8% |      192,015,700.00 |                5.21 |    0.1% |      2.12 | `BoostMutexLockAndDefensiveProgrammingRuntimePerformance__mutex_false_and_no_conditions__100000000`

	About
	- Timestamp Created: 7:45 AM, January 31, 2026

	*/

	struct TestSubject2
	{
		bool
			condition_1 = true;

		bool
			condition_2 = false;

		bool
			condition_3 = false;

		bool
			condition_4 = false;

		bool get_conditions()
		{
			return
				condition_2 ||
				condition_3 ||
				condition_4;
		}

		bool get_conditions_false()
		{
			return
				!get_conditions();
		}
	};

	class TestSubject1
	{
	public:
		static TestSubject1
			singleton;

		boost::mutex
			mutex_1;

		TestSubject2
			configurations_1 =
		{ true, false, false, false };

		TestSubject2
			configurations_2 =
		{ false, false, false, false };

		void mutex_false_and_all_conditions_false_pre_edge_case_checking()
		{
			if (configurations_2.get_conditions_false())
			{
				return;
			}

			boost::unique_lock<boost::mutex>
				mutex_lock;
			if
				(
					configurations_2.condition_1
					)
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						mutex_1
					);
			}
		}

		void mutex_false_and_all_conditions_false_post_edge_case_checking()
		{
			boost::unique_lock<boost::mutex>
				mutex_lock;
			if
				(
					configurations_2.condition_1
					)
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						mutex_1
					);
			}

			if (configurations_2.get_conditions_false())
			{
				return;
			}
		}

		void mutex_true_and_all_conditions_false()
		{
			boost::unique_lock<boost::mutex>
				mutex_lock;
			if
				(
					configurations_1.condition_1
					)
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						mutex_1
					);
			}

			if (configurations_1.get_conditions())
			{
				return;
			}
		}

		void mutex_false_and_all_conditions_false()
		{
			boost::unique_lock<boost::mutex>
				mutex_lock;
			if
				(
					configurations_2.condition_1
					)
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						mutex_1
					);
			}

			if (configurations_2.get_conditions_false())
			{
				return;
			}
		}

		void mutex_true_and_no_conditions()
		{
			boost::unique_lock<boost::mutex>
				mutex_lock;
			if
				(
					configurations_1.condition_1
					)
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						mutex_1
					);
			}
		}

		void mutex_false_and_no_conditions()
		{
			boost::unique_lock<boost::mutex>
				mutex_lock;
			if
				(
					configurations_2.condition_1
					)
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						mutex_1
					);
			}
		}

		void all_conditions_false()
		{
			if (configurations_2.get_conditions_false())
			{
				return;
			}
		}

		void empty_method()
		{

		}
	};

	TestSubject1
		TestSubject1
		::singleton;

	void execute()
	{
		QLogicaeCppCore::RuntimeBenchmarkerTestSuite test_suite
		{
			.name = "BoostMutexLockAndDefensiveProgrammingRuntimePerformance",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 100000000,
					.iterations = 1
				},
				{
					.epochs = 100000,
					.iterations = 1000
				},
				{
					.epochs = 1,
					.iterations = 100000000
				},
			},
			.test_cases =
			{
				{
					.name = "empty_method",
					.callback = []() { TestSubject1::singleton.empty_method(); }
				},
				{
					.name = "all_conditions_false",
					.callback = []() { TestSubject1::singleton.all_conditions_false(); }
				},
				{
					.name = "mutex_false_and_all_conditions_false_pre_edge_case_checking",
					.callback = []() { TestSubject1::singleton.mutex_false_and_all_conditions_false_pre_edge_case_checking(); }
				},
				{
					.name = "mutex_false_and_all_conditions_false_post_edge_case_checking",
					.callback = []() { TestSubject1::singleton.mutex_false_and_all_conditions_false_post_edge_case_checking(); }
				},
				{
					.name = "mutex_true_and_all_conditions_false",
					.callback = []() { TestSubject1::singleton.mutex_true_and_all_conditions_false(); }
				},
				{
					.name = "mutex_false_and_all_conditions_false",
					.callback = []() { TestSubject1::singleton.mutex_false_and_all_conditions_false(); }
				},
				{
					.name = "mutex_true_and_no_conditions",
					.callback = []() { TestSubject1::singleton.mutex_true_and_no_conditions(); }
				},
				{
					.name = "mutex_false_and_no_conditions",
					.callback = []() { TestSubject1::singleton.mutex_false_and_no_conditions(); }
				},
			}
		};

		QLogicaeCppCore::RuntimeBenchmarker::singleton.execute(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}

namespace CallbackOrNone
{
	/*

	Conclusion:
	- do wrap methods within a callback function, if performance is not a major concern


	= 1 character(s)
	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |                9.31 |      107,459,927.90 |    1.8% |      0.10 | `Callback Or None__no_callback_function_called__1`
	|    18.4% |               50.57 |       19,773,323.84 |    0.5% |      0.62 | `Callback Or None__with_callback_function_called__1`

	|   100.0% |            8,944.84 |          111,796.33 |    0.2% |      0.10 | `Callback Or None__no_callback_function_called__1000`
	|    17.8% |           50,389.06 |           19,845.58 |    0.2% |      0.61 | `Callback Or None__with_callback_function_called__1000`

	|   100.0% |        8,933,600.00 |              111.94 |    0.4% |      0.10 | `Callback Or None__no_callback_function_called__1000000`
	|    17.8% |       50,258,400.00 |               19.90 |    0.1% |      0.55 | `Callback Or None__with_callback_function_called__1000000`



	= 100 character(s)
	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |               79.88 |       12,518,356.17 |    1.0% |      0.98 | `Callback Or None__no_callback_function_called__1`
	|    42.0% |              190.23 |        5,256,757.10 |    0.2% |      2.31 | `Callback Or None__with_callback_function_called__1`

	|   100.0% |           79,033.59 |           12,652.85 |    0.2% |      0.87 | `Callback Or None__no_callback_function_called__1000`
	|    41.5% |          190,436.40 |            5,251.10 |    0.1% |      2.32 | `Callback Or None__with_callback_function_called__1000`

	|   100.0% |       78,851,000.00 |               12.68 |    0.2% |      0.87 | `Callback Or None__no_callback_function_called__1000000`
	|    41.4% |      190,532,100.00 |                5.25 |    0.3% |      2.10 | `Callback Or None__with_callback_function_called__1000000`

	About
	- Timestamp Created: 7:36 PM, January 20, 2026



		bool
			test_1(const std::string& v);

		bool
			test_2(const std::string& v);

		bool
			handle(
				const std::function<void()>
					callback = []() {}
			);



	template <typename AbstractConfigurationsType> bool
		AbstractClass<AbstractConfigurationsType>
			::test_1(const std::string& v)
	{
		try
		{
			boost::unique_lock<boost::mutex> mutex_lock;
			if (configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock = boost::unique_lock<boost::mutex> (feature_handling_mutex_1);
			}

			std::string i = v;

			return
				true;
		}
		catch
		(
			const std::exception&
				exception
		)
		{
			return
				handle_error_outputs(
					exception
				);
		}
	}

	template <typename AbstractConfigurationsType> bool
		AbstractClass<AbstractConfigurationsType>
			::test_2(const std::string& v)
	{
		return handle(
			[this, v]()
			{
				std::string i = v;
			}
		);
	}

	template <typename AbstractConfigurationsType> bool
		AbstractClass<AbstractConfigurationsType>
			::handle(
				const std::function<void()>
					callback
			)
	{
		try
		{
			boost::unique_lock<boost::mutex>
				mutex_lock;
			if (configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						feature_handling_mutex_1
					);
			}

			callback();

			return
				true;
		}
		catch
		(
			const std::exception&
				exception
		)
		{
			return
				handle_error_outputs(
					exception
				);
		}
	}

	*/

	void execute()
	{
		QLogicaeCppCore::RuntimeBenchmarkerTestSuite test_suite
		{
			.name = "Callback Or None",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 1000000,
					.iterations = 1
				},
				{
					.epochs = 1000,
					.iterations = 1000
				},
				{
					.epochs = 1,
					.iterations = 1000000
				},
			},
			.test_cases =
			{
				/*			
				{
					.name = "no_callback_function_called",
					.callback = []() { QLogicaeCppCore::SingletonManager::singleton.test_1("0"); }
				},
				{
					.name = "with_callback_function_called",
					.callback = []() { QLogicaeCppCore::SingletonManager::singleton.test_2("0"); }
				}
				*/ 
			}
		};

		QLogicaeCppCore::RuntimeBenchmarker::singleton.execute(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}

namespace AsynchronousBenchmarks
{
	/*

	Conclusions
	- multi-threading (general usage)
		- boost_asio_co_spawn_strand__detached__constant_lambda()
		- boost_asio_co_spawn_strand__use_future__constant_lambda()

	- fire-and-forget threads
		- boost_asio_co_spawn_io__detached__constant_lambda()
		- boost_asio_co_spawn_io__use_future__constant_lambda()



	About
	- Timestamp Created
		- 8:01 AM, January 14, 2026

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |              465.05 |        2,150,298.05 |    2.3% |      0.52 | `thread_creation | boost_asio_co_spawn_strand__detached__constant_lambda | 1`
	|    26.4% |            1,762.47 |          567,385.27 |    0.5% |      2.14 | `thread_creation | boost_asio_co_spawn_io__detached__constant_lambda | 1`
	|    69.1% |              673.04 |        1,485,798.31 |    1.7% |      0.83 | `thread_creation | boost_asio_co_spawn_strand__use_future__constant_lambda | 1`
	|    22.9% |            2,031.28 |          492,299.86 |    0.3% |      2.46 | `thread_creation | boost_asio_co_spawn_io__use_future__constant_lambda | 1`
	|    27.7% |            1,677.93 |          595,972.57 |    0.3% |      2.03 | `thread_creation | boost_asio_post_thread__thread_pool_instance__constant_lambda | 1`
	|    27.5% |            1,693.60 |          590,459.93 |    0.3% |      2.04 | `thread_creation | boost_asio_post_thread__thread_pool_heap__constant_lambda | 1`
	|    22.5% |            2,070.83 |          482,897.90 |    0.4% |      2.51 | `thread_creation | boost_asio_co_spawn_thread__detached__constant_lambda | 1`
	|    24.3% |            1,914.20 |          522,411.17 |    1.9% |      2.30 | `thread_creation | boost_asio_post_thread__system_executor__constant_lambda | 1`
	|    26.9% |            1,725.65 |          579,490.37 |    1.0% |      2.09 | `thread_creation | boost_asio_dispatch_thread__thread_pool_instance__constant_lambda | 1`
	|    26.1% |            1,785.19 |          560,165.56 |    0.6% |      2.20 | `thread_creation | boost_asio_dispatch_thread__thread_pool_heap__constant_lambda | 1`
	|     9.4% |            4,943.96 |          202,267.21 |    1.5% |      6.18 | `thread_creation | std_async_thread__constant_lambda | 1`

	|   100.0% |            4,478.64 |          223,281.91 |    1.8% |      0.50 | `thread_creation | boost_asio_co_spawn_strand__detached__constant_lambda | 10`
	|    25.5% |           17,570.24 |           56,914.41 |    0.8% |      2.12 | `thread_creation | boost_asio_co_spawn_io__detached__constant_lambda | 10`
	|    61.3% |            7,311.49 |          136,771.08 |    5.0% |      0.97 | `thread_creation | boost_asio_co_spawn_strand__use_future__constant_lambda | 10`
	|    16.2% |           27,694.07 |           36,108.82 |    1.5% |      3.33 | `thread_creation | boost_asio_co_spawn_io__use_future__constant_lambda | 10`
	|    19.0% |           23,587.24 |           42,395.80 |    0.7% |      2.86 | `thread_creation | boost_asio_post_thread__thread_pool_instance__constant_lambda | 10`
	|    19.0% |           23,606.80 |           42,360.67 |    0.5% |      2.86 | `thread_creation | boost_asio_post_thread__thread_pool_heap__constant_lambda | 10`
	|    15.5% |           28,968.51 |           34,520.24 |    0.6% |      3.52 | `thread_creation | boost_asio_co_spawn_thread__detached__constant_lambda | 10`
	|    16.7% |           26,823.11 |           37,281.28 |    0.2% |      3.23 | `thread_creation | boost_asio_post_thread__system_executor__constant_lambda | 10`
	|    18.9% |           23,643.36 |           42,295.18 |    0.6% |      2.96 | `thread_creation | boost_asio_dispatch_thread__thread_pool_instance__constant_lambda | 10`
	|    18.7% |           24,007.64 |           41,653.41 |    0.5% |      2.93 | `thread_creation | boost_asio_dispatch_thread__thread_pool_heap__constant_lambda | 10`
	|     8.8% |           50,691.71 |           19,727.09 |    4.8% |      6.23 | `thread_creation | std_async_thread__constant_lambda | 10`

	|   100.0% |           47,171.53 |           21,199.23 |    1.3% |      0.51 | `thread_creation | boost_asio_co_spawn_strand__detached__constant_lambda | 100`
	|    20.5% |          229,674.59 |            4,353.99 |    1.1% |      2.75 | `thread_creation | boost_asio_co_spawn_io__detached__constant_lambda | 100`
	|    64.6% |           73,010.37 |           13,696.69 |    1.3% |      0.97 | `thread_creation | boost_asio_co_spawn_strand__use_future__constant_lambda | 100`
	|    17.3% |          272,201.17 |            3,673.75 |    2.0% |      3.27 | `thread_creation | boost_asio_co_spawn_io__use_future__constant_lambda | 100`
	|    20.1% |          235,073.93 |            4,253.98 |    0.4% |      2.83 | `thread_creation | boost_asio_post_thread__thread_pool_instance__constant_lambda | 100`
	|    20.0% |          236,368.07 |            4,230.69 |    0.6% |      2.88 | `thread_creation | boost_asio_post_thread__thread_pool_heap__constant_lambda | 100`
	|    16.5% |          285,316.09 |            3,504.88 |    0.3% |      3.46 | `thread_creation | boost_asio_co_spawn_thread__detached__constant_lambda | 100`
	|    17.8% |          265,601.21 |            3,765.04 |    0.8% |      3.23 | `thread_creation | boost_asio_post_thread__system_executor__constant_lambda | 100`
	|    19.8% |          238,357.06 |            4,195.39 |    0.9% |      2.91 | `thread_creation | boost_asio_dispatch_thread__thread_pool_instance__constant_lambda | 100`
	|    18.7% |          252,047.88 |            3,967.50 |    3.4% |      3.09 | `thread_creation | boost_asio_dispatch_thread__thread_pool_heap__constant_lambda | 100`
	|     8.9% |          528,372.05 |            1,892.61 |    3.3% |      6.41 | `thread_creation | std_async_thread__constant_lambda | 100`

	|   100.0% |          522,610.78 |            1,913.47 |    1.2% |      0.63 | `thread_creation | boost_asio_co_spawn_strand__detached__constant_lambda | 1000`
	|    21.1% |        2,482,494.74 |              402.82 |    1.0% |      2.97 | `thread_creation | boost_asio_co_spawn_io__detached__constant_lambda | 1000`
	|    69.1% |          756,775.23 |            1,321.40 |    2.5% |      1.01 | `thread_creation | boost_asio_co_spawn_strand__use_future__constant_lambda | 1000`
	|    18.1% |        2,886,800.95 |              346.40 |    0.9% |      3.46 | `thread_creation | boost_asio_co_spawn_io__use_future__constant_lambda | 1000`
	|    21.3% |        2,452,335.65 |              407.77 |    0.5% |      2.97 | `thread_creation | boost_asio_post_thread__thread_pool_instance__constant_lambda | 1000`
	|    21.1% |        2,477,329.91 |              403.66 |    1.0% |      2.99 | `thread_creation | boost_asio_post_thread__thread_pool_heap__constant_lambda | 1000`
	|    17.4% |        3,002,938.32 |              333.01 |    0.4% |      3.64 | `thread_creation | boost_asio_co_spawn_thread__detached__constant_lambda | 1000`
	|    18.8% |        2,781,906.96 |              359.47 |    0.5% |      3.36 | `thread_creation | boost_asio_post_thread__system_executor__constant_lambda | 1000`
	|    20.9% |        2,504,734.29 |              399.24 |    0.8% |      3.03 | `thread_creation | boost_asio_dispatch_thread__thread_pool_instance__constant_lambda | 1000`
	|    20.9% |        2,500,058.88 |              399.99 |    0.5% |      3.03 | `thread_creation | boost_asio_dispatch_thread__thread_pool_heap__constant_lambda | 1000`
	|     9.9% |        5,294,259.13 |              188.88 |    4.1% |      6.48 | `thread_creation | std_async_thread__constant_lambda | 1000`

	|   100.0% |      510,373,700.00 |                1.96 |    1.1% |      5.62 | `thread_creation | boost_asio_co_spawn_strand__detached__constant_lambda | 1000000`
	|    20.2% |    2,524,726,900.00 |                0.40 |    0.6% |     29.48 | `thread_creation | boost_asio_co_spawn_io__detached__constant_lambda | 1000000`
	|    64.4% |      792,991,200.00 |                1.26 |    1.6% |      8.72 | `thread_creation | boost_asio_co_spawn_strand__use_future__constant_lambda | 1000000`
	|    17.4% |    2,937,717,500.00 |                0.34 |    0.6% |     32.36 | `thread_creation | boost_asio_co_spawn_io__use_future__constant_lambda | 1000000`
	|    19.9% |    2,565,697,600.00 |                0.39 |    1.0% |     28.21 | `thread_creation | boost_asio_post_thread__thread_pool_instance__constant_lambda | 1000000`
	|    19.8% |    2,574,147,900.00 |                0.39 |    0.6% |     28.37 | `thread_creation | boost_asio_post_thread__thread_pool_heap__constant_lambda | 1000000`
	|    16.7% |    3,050,680,500.00 |                0.33 |    0.6% |     33.70 | `thread_creation | boost_asio_co_spawn_thread__detached__constant_lambda | 1000000`
	|    18.0% |    2,840,849,400.00 |                0.35 |    0.7% |     31.59 | `thread_creation | boost_asio_post_thread__system_executor__constant_lambda | 1000000`
	|    19.7% |    2,594,505,200.00 |                0.39 |    0.7% |     28.90 | `thread_creation | boost_asio_dispatch_thread__thread_pool_instance__constant_lambda | 1000000`
	|    19.7% |    2,587,159,400.00 |                0.39 |    0.3% |     28.52 | `thread_creation | boost_asio_dispatch_thread__thread_pool_heap__constant_lambda | 1000000`
	|     9.4% |    5,422,414,400.00 |                0.18 |    0.9% |     59.39 | `thread_creation | std_async_thread__constant_lambda | 1000000`

	*/

	inline static std::function<void()> instance_lambda = []() {};

	inline static boost::asio::thread_pool THREAD_POOL_INSTANCE{ std::thread::hardware_concurrency() };

	inline static std::shared_ptr<boost::asio::thread_pool> THREAD_POOL_HEAP;

	inline static boost::asio::io_context IO;

	inline static boost::asio::strand<decltype(IO.get_executor())> STRAND(IO.get_executor());

	inline static auto WORK = boost::asio::make_work_guard(IO);

	inline static std::vector<std::thread> WORKERS;

	inline static boost::asio::inline_executor exec;

	void start_io_workers()
	{
		for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
			WORKERS.emplace_back([] { IO.run(); });
	}

	void stop_io_workers()
	{
		WORK.reset();
		IO.stop();
		for (auto& t : WORKERS)
			if (t.joinable())
				t.join();
		WORKERS.clear();
	}

	void boost_asio_co_spawn_io__detached__constant_lambda()
	{
		// auto start = std::chrono::high_resolution_clock::now();
		boost::asio::co_spawn(
			IO,
			[]() -> boost::asio::awaitable<void>
			{
				co_return;
			},
			boost::asio::detached
		);
		// auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start)
		//	.count();
		// std::cout << "Nanoseconds " << ": " << ns << " ns\n";
	}

	void boost_asio_post_thread__thread_pool_instance__constant_lambda()
	{
		// auto start = std::chrono::high_resolution_clock::now();
		boost::asio::post(
			THREAD_POOL_INSTANCE,
			[]() {}
		);
		// auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start)
		//	.count();
		// std::cout << "Nanoseconds " << ": " << ns << " ns\n";
	}

	void boost_asio_co_spawn_strand__detached__constant_lambda()
	{
		// auto start = std::chrono::high_resolution_clock::now();
		boost::asio::co_spawn(
			STRAND,
			[]() -> boost::asio::awaitable<void>
			{
				co_return;
			},
			boost::asio::detached
		);
		// auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start)
		//	.count();
		// std::cout << "Nanoseconds " << ": " << ns << " ns\n";
	}

	std::future<void>
		boost_asio_co_spawn_io__use_future__constant_lambda()
	{
		// auto start = std::chrono::high_resolution_clock::now();
		std::function<void()> callback = []() {};

		auto future = boost::asio::co_spawn(
			IO,
			[callback]() -> boost::asio::awaitable<void>
			{
				callback();

				co_return;
			},
			boost::asio::use_future
		);
		// auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start)
		//	.count();
		// std::cout << "Nanoseconds " << ": " << ns << " ns\n";

		return future;
	}

	std::future<void>
		boost_asio_co_spawn_strand__use_future__constant_lambda()
	{
		// auto start = std::chrono::high_resolution_clock::now();
		std::function<void()> callback = []() {};

		auto future = boost::asio::co_spawn(
			STRAND,
			[callback]() -> boost::asio::awaitable<void>
			{
				callback();

				co_return;
			},
			boost::asio::use_future
		);
		// auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start)
		//	.count();
		// std::cout << "Nanoseconds " << ": " << ns << " ns\n";

		return future;
	}

	void boost_asio_post_thread__system_executor__constant_lambda()
	{
		boost::asio::post(boost::asio::system_executor(), []() {});
	}

	void boost_asio_dispatch_thread__inline_executor__constant_lambda()
	{
		boost::asio::dispatch(exec, []() {});
	}

	void boost_asio_co_spawn_thread__detached__constant_lambda()
	{
		boost::asio::co_spawn(
			THREAD_POOL_INSTANCE.get_executor(),
			[]() -> boost::asio::awaitable<void>
			{
				co_return;
			},
			boost::asio::detached
		);
	}

	void boost_asio_dispatch_thread__thread_pool_instance__constant_lambda()
	{
		boost::asio::dispatch(
			THREAD_POOL_INSTANCE,
			[]() {}
		);
	}

	void boost_asio_post_thread__thread_pool_heap__constant_lambda()
	{
		boost::asio::post(
			*THREAD_POOL_HEAP,
			[]() {}
		);
	}

	void boost_asio_dispatch_thread__thread_pool_heap__constant_lambda()
	{
		boost::asio::dispatch(
			*THREAD_POOL_HEAP,
			[]() {}
		);
	}

	void std_async_thread__constant_lambda()
	{
		std::async(
			std::launch::async,
			[]() {}
		);
	}

	void execute()
	{
		THREAD_POOL_HEAP =
			std::make_shared<boost::asio::thread_pool>(
				std::thread::hardware_concurrency()
			);

		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "thread_creation",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 100000,
					.iterations = 1
				},
				{
					.epochs = 100,
					.iterations = 1000
				},
				{
					.epochs = 1,
					.iterations = 1000000
				}
			},
			.test_cases =
			{
				{
					.name = "boost_asio_co_spawn_strand__detached__constant_lambda",
					.callback = boost_asio_co_spawn_strand__detached__constant_lambda
				},
				{
					.name = "boost_asio_co_spawn_io__detached__constant_lambda",
					.callback = boost_asio_co_spawn_io__detached__constant_lambda
				},
				{
					.name = "boost_asio_co_spawn_strand__use_future__constant_lambda",
					.callback = boost_asio_co_spawn_strand__use_future__constant_lambda
				},
				{
					.name = "boost_asio_co_spawn_io__use_future__constant_lambda",
					.callback = boost_asio_co_spawn_io__use_future__constant_lambda
				},
				{
					.name = "boost_asio_post_thread__thread_pool_instance__constant_lambda",
					.callback = boost_asio_post_thread__thread_pool_instance__constant_lambda
				},
				{
					.name = "boost_asio_post_thread__thread_pool_heap__constant_lambda",
					.callback = boost_asio_post_thread__thread_pool_heap__constant_lambda
				},
				{
					.name = "boost_asio_co_spawn_thread__detached__constant_lambda",
					.callback = boost_asio_co_spawn_thread__detached__constant_lambda
				},
				{
					.name = "boost_asio_post_thread__system_executor__constant_lambda",
					.callback = boost_asio_post_thread__system_executor__constant_lambda
				},
				{
					.name = "boost_asio_dispatch_thread__thread_pool_instance__constant_lambda",
					.callback = boost_asio_dispatch_thread__thread_pool_instance__constant_lambda
				},
				{
					.name = "boost_asio_dispatch_thread__thread_pool_heap__constant_lambda",
					.callback = boost_asio_dispatch_thread__thread_pool_heap__constant_lambda
				},
				{
					.name = "std_async_thread__constant_lambda",
					.callback = std_async_thread__constant_lambda
				}
			}
		};

		start_io_workers();

		execute_nanobenchmark(
			test_suite
		);

		stop_io_workers();

		/*
		boost_asio_post_thread__thread_pool_instance__constant_lambda();
		boost_asio_co_spawn_io__detached__constant_lambda();
		boost_asio_co_spawn_strand__detached__constant_lambda();
		*/

		bool exit_code;
		std::cin >> exit_code;
	}
}



namespace ArithmeticOperationsPerTypes
{
	/*

	Conclusions
	- index and loops
		- size_t
	- floating-point number calculations
		- long double
	- integer calculations
		- long long int



	About
	- Timestamp Created
		- 8:06 AM, January 14, 2026

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |                1.91 |      522,535,815.02 |    1.2% |      0.47 | `Arithmetic Operations Per Type | add__instance__char | 1`
	|   101.3% |                1.89 |      529,530,385.14 |    0.8% |      0.46 | `Arithmetic Operations Per Type | add__instance__short_int | 1`
	|   130.2% |                1.47 |      680,262,808.03 |    1.7% |      0.36 | `Arithmetic Operations Per Type | add__instance__int | 1`
	|   135.7% |                1.41 |      708,858,861.97 |    1.1% |      0.34 | `Arithmetic Operations Per Type | add__instance__long_int | 1`
	|   133.3% |                1.44 |      696,436,513.98 |    0.4% |      0.35 | `Arithmetic Operations Per Type | add__instance__long_long_int | 1`
	|   101.2% |                1.89 |      528,822,927.05 |    1.3% |      0.46 | `Arithmetic Operations Per Type | add__instance__int8_t | 1`
	|    99.9% |                1.92 |      521,774,024.71 |    0.6% |      0.47 | `Arithmetic Operations Per Type | add__instance__int16_t | 1`
	|   134.3% |                1.43 |      701,706,556.83 |    1.4% |      0.35 | `Arithmetic Operations Per Type | add__instance__int32_t | 1`
	|   134.4% |                1.42 |      702,350,831.12 |    3.2% |      0.34 | `Arithmetic Operations Per Type | add__instance__int64_t | 1`
	|   132.5% |                1.44 |      692,347,740.88 |    0.6% |      0.35 | `Arithmetic Operations Per Type | add__instance__size_t | 1`
	|    61.6% |                3.11 |      321,681,290.51 |    0.0% |      0.75 | `Arithmetic Operations Per Type | add__instance__float | 1`
	|    61.6% |                3.11 |      321,640,703.56 |    0.1% |      0.75 | `Arithmetic Operations Per Type | add__instance__double | 1`
	|    61.6% |                3.11 |      321,806,391.06 |    0.1% |      0.75 | `Arithmetic Operations Per Type | add__instance__long_double | 1`
	|   160.1% |                1.20 |      836,323,272.53 |    0.1% |      0.29 | `Arithmetic Operations Per Type | subtract__instance__char | 1`
	|   160.2% |                1.19 |      837,113,241.52 |    0.0% |      0.29 | `Arithmetic Operations Per Type | subtract__instance__short_int | 1`
	|   159.6% |                1.20 |      834,181,006.16 |    0.3% |      0.29 | `Arithmetic Operations Per Type | subtract__instance__int | 1`
	|   160.1% |                1.20 |      836,657,499.21 |    0.1% |      0.29 | `Arithmetic Operations Per Type | subtract__instance__long_int | 1`
	|   160.0% |                1.20 |      836,171,439.57 |    0.1% |      0.29 | `Arithmetic Operations Per Type | subtract__instance__long_long_int | 1`
	|   159.9% |                1.20 |      835,435,075.06 |    0.2% |      0.29 | `Arithmetic Operations Per Type | subtract__instance__int8_t | 1`
	|   160.1% |                1.20 |      836,325,924.08 |    0.1% |      0.29 | `Arithmetic Operations Per Type | subtract__instance__int16_t | 1`
	|   160.0% |                1.20 |      835,849,081.01 |    0.1% |      0.29 | `Arithmetic Operations Per Type | subtract__instance__int32_t | 1`
	|   159.8% |                1.20 |      834,846,432.32 |    0.2% |      0.29 | `Arithmetic Operations Per Type | subtract__instance__int64_t | 1`
	|   156.8% |                1.22 |      819,401,890.21 |    1.6% |      0.30 | `Arithmetic Operations Per Type | subtract__instance__size_t | 1`
	|    60.9% |                3.14 |      318,194,415.22 |    0.9% |      0.76 | `Arithmetic Operations Per Type | subtract__instance__float | 1`
	|    61.2% |                3.12 |      320,044,295.42 |    0.4% |      0.76 | `Arithmetic Operations Per Type | subtract__instance__double | 1`
	|    61.3% |                3.12 |      320,092,091.80 |    0.2% |      0.76 | `Arithmetic Operations Per Type | subtract__instance__long_double | 1`
	|    88.8% |                2.15 |      464,157,092.86 |    0.2% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__char | 1`
	|    88.8% |                2.16 |      463,874,572.71 |    0.2% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__short_int | 1`
	|   100.0% |                1.91 |      522,582,492.51 |    0.1% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__int | 1`
	|   100.0% |                1.91 |      522,729,883.17 |    0.1% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__long_int | 1`
	|   100.1% |                1.91 |      522,942,422.52 |    0.1% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__long_long_int | 1`
	|    88.9% |                2.15 |      464,718,691.00 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__int8_t | 1`
	|    88.9% |                2.15 |      464,666,384.19 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__int16_t | 1`
	|   100.0% |                1.91 |      522,788,354.22 |    0.1% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__int32_t | 1`
	|   100.1% |                1.91 |      523,040,666.96 |    0.1% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__int64_t | 1`
	|   100.1% |                1.91 |      523,018,023.64 |    0.1% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__size_t | 1`
	|    89.0% |                2.15 |      465,034,802.31 |    0.0% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__float | 1`
	|    88.9% |                2.15 |      464,770,955.57 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__double | 1`
	|    88.9% |                2.15 |      464,709,785.40 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__long_double | 1`
	|   160.0% |                1.20 |      836,034,592.36 |    0.1% |      0.29 | `Arithmetic Operations Per Type | divide__instance__char | 1`
	|   160.0% |                1.20 |      836,316,558.85 |    0.1% |      0.29 | `Arithmetic Operations Per Type | divide__instance__short_int | 1`
	|   160.0% |                1.20 |      836,029,516.48 |    0.1% |      0.29 | `Arithmetic Operations Per Type | divide__instance__int | 1`
	|   160.1% |                1.20 |      836,517,699.20 |    0.1% |      0.29 | `Arithmetic Operations Per Type | divide__instance__long_int | 1`
	|   159.8% |                1.20 |      835,162,844.18 |    0.2% |      0.29 | `Arithmetic Operations Per Type | divide__instance__long_long_int | 1`
	|   160.1% |                1.19 |      836,823,983.22 |    0.1% |      0.29 | `Arithmetic Operations Per Type | divide__instance__int8_t | 1`
	|   160.0% |                1.20 |      835,932,453.82 |    0.1% |      0.29 | `Arithmetic Operations Per Type | divide__instance__int16_t | 1`
	|   160.2% |                1.19 |      836,859,194.13 |    0.1% |      0.29 | `Arithmetic Operations Per Type | divide__instance__int32_t | 1`
	|   159.9% |                1.20 |      835,525,248.35 |    0.2% |      0.29 | `Arithmetic Operations Per Type | divide__instance__int64_t | 1`
	|   160.0% |                1.20 |      836,277,126.66 |    0.2% |      0.29 | `Arithmetic Operations Per Type | divide__instance__size_t | 1`
	|   159.9% |                1.20 |      835,711,753.85 |    0.2% |      0.29 | `Arithmetic Operations Per Type | divide__instance__float | 1`
	|   160.1% |                1.20 |      836,639,469.16 |    0.1% |      0.29 | `Arithmetic Operations Per Type | divide__instance__double | 1`
	|   160.2% |                1.19 |      836,894,510.69 |    0.1% |      0.29 | `Arithmetic Operations Per Type | divide__instance__long_double | 1`

	|   100.0% |            1,909.79 |          523,618.07 |    0.1% |      0.46 | `Arithmetic Operations Per Type | add__instance__char | 1000`
	|   100.1% |            1,908.47 |          523,980.61 |    0.1% |      0.46 | `Arithmetic Operations Per Type | add__instance__short_int | 1000`
	|   132.9% |            1,437.25 |          695,771.81 |    1.0% |      0.35 | `Arithmetic Operations Per Type | add__instance__int | 1000`
	|   133.0% |            1,435.76 |          696,497.59 |    0.5% |      0.35 | `Arithmetic Operations Per Type | add__instance__long_int | 1000`
	|   132.8% |            1,437.72 |          695,547.56 |    0.5% |      0.35 | `Arithmetic Operations Per Type | add__instance__long_long_int | 1000`
	|   100.2% |            1,906.84 |          524,428.12 |    0.0% |      0.46 | `Arithmetic Operations Per Type | add__instance__int8_t | 1000`
	|   100.1% |            1,906.94 |          524,401.01 |    0.1% |      0.46 | `Arithmetic Operations Per Type | add__instance__int16_t | 1000`
	|   131.6% |            1,451.08 |          689,142.36 |    0.7% |      0.35 | `Arithmetic Operations Per Type | add__instance__int32_t | 1000`
	|   131.3% |            1,454.24 |          687,646.73 |    0.7% |      0.35 | `Arithmetic Operations Per Type | add__instance__int64_t | 1000`
	|   133.0% |            1,436.32 |          696,223.73 |    0.1% |      0.35 | `Arithmetic Operations Per Type | add__instance__size_t | 1000`
	|    61.4% |            3,107.95 |          321,755.41 |    0.1% |      0.75 | `Arithmetic Operations Per Type | add__instance__float | 1000`
	|    61.4% |            3,110.17 |          321,525.60 |    0.1% |      0.76 | `Arithmetic Operations Per Type | add__instance__double | 1000`
	|    61.4% |            3,107.91 |          321,759.43 |    0.1% |      0.75 | `Arithmetic Operations Per Type | add__instance__long_double | 1000`
	|   197.8% |              965.53 |        1,035,703.42 |    0.1% |      0.21 | `Arithmetic Operations Per Type | subtract__instance__char | 1000`
	|   197.6% |              966.66 |        1,034,494.21 |    0.1% |      0.23 | `Arithmetic Operations Per Type | subtract__instance__short_int | 1000`
	|   197.0% |              969.23 |        1,031,751.66 |    0.3% |      0.24 | `Arithmetic Operations Per Type | subtract__instance__int | 1000`
	|   196.4% |              972.45 |        1,028,328.26 |    0.7% |      0.21 | `Arithmetic Operations Per Type | subtract__instance__long_int | 1000`
	|   197.7% |              965.82 |        1,035,389.86 |    0.1% |      0.21 | `Arithmetic Operations Per Type | subtract__instance__long_long_int | 1000`
	|   197.4% |              967.41 |        1,033,686.59 |    0.2% |      0.21 | `Arithmetic Operations Per Type | subtract__instance__int8_t | 1000`
	|   197.3% |              967.82 |        1,033,251.64 |    0.2% |      0.23 | `Arithmetic Operations Per Type | subtract__instance__int16_t | 1000`
	|   197.5% |              966.84 |        1,034,301.81 |    0.2% |      0.21 | `Arithmetic Operations Per Type | subtract__instance__int32_t | 1000`
	|   197.6% |              966.29 |        1,034,882.00 |    0.2% |      0.21 | `Arithmetic Operations Per Type | subtract__instance__int64_t | 1000`
	|   197.1% |              969.00 |        1,031,987.17 |    0.1% |      0.21 | `Arithmetic Operations Per Type | subtract__instance__size_t | 1000`
	|    61.4% |            3,111.34 |          321,405.40 |    0.2% |      0.75 | `Arithmetic Operations Per Type | subtract__instance__float | 1000`
	|    61.4% |            3,112.36 |          321,299.30 |    0.2% |      0.76 | `Arithmetic Operations Per Type | subtract__instance__double | 1000`
	|    61.4% |            3,112.49 |          321,285.73 |    0.1% |      0.75 | `Arithmetic Operations Per Type | subtract__instance__long_double | 1000`
	|    88.7% |            2,152.61 |          464,553.34 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__char | 1000`
	|    88.7% |            2,152.76 |          464,520.06 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__short_int | 1000`
	|    99.7% |            1,915.50 |          522,057.57 |    0.2% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__int | 1000`
	|    99.9% |            1,912.33 |          522,921.67 |    0.1% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__long_int | 1000`
	|    99.8% |            1,912.76 |          522,805.96 |    0.1% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__long_long_int | 1000`
	|    88.7% |            2,152.50 |          464,576.36 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__int8_t | 1000`
	|    88.7% |            2,151.99 |          464,685.36 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__int16_t | 1000`
	|    99.7% |            1,914.88 |          522,226.35 |    0.1% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__int32_t | 1000`
	|    99.9% |            1,911.75 |          523,081.31 |    0.0% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__int64_t | 1000`
	|    99.8% |            1,913.33 |          522,650.03 |    0.1% |      0.46 | `Arithmetic Operations Per Type | multiply__instance__size_t | 1000`
	|    88.8% |            2,151.43 |          464,807.20 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__float | 1000`
	|    88.7% |            2,152.15 |          464,652.36 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__double | 1000`
	|    88.8% |            2,151.59 |          464,773.63 |    0.1% |      0.52 | `Arithmetic Operations Per Type | multiply__instance__long_double | 1000`
	|   197.7% |              965.98 |        1,035,214.10 |    0.2% |      0.23 | `Arithmetic Operations Per Type | divide__instance__char | 1000`
	|   197.7% |              965.81 |        1,035,402.13 |    0.1% |      0.21 | `Arithmetic Operations Per Type | divide__instance__short_int | 1000`
	|   198.0% |              964.76 |        1,036,523.42 |    0.1% |      0.21 | `Arithmetic Operations Per Type | divide__instance__int | 1000`
	|   197.7% |              965.92 |        1,035,283.13 |    0.1% |      0.23 | `Arithmetic Operations Per Type | divide__instance__long_int | 1000`
	|   197.7% |              966.16 |        1,035,029.16 |    0.2% |      0.21 | `Arithmetic Operations Per Type | divide__instance__long_long_int | 1000`
	|   197.9% |              964.90 |        1,036,375.22 |    0.1% |      0.23 | `Arithmetic Operations Per Type | divide__instance__int8_t | 1000`
	|   197.9% |              965.19 |        1,036,066.82 |    0.1% |      0.21 | `Arithmetic Operations Per Type | divide__instance__int16_t | 1000`
	|   197.9% |              964.82 |        1,036,465.08 |    0.1% |      0.21 | `Arithmetic Operations Per Type | divide__instance__int32_t | 1000`
	|   197.6% |              966.70 |        1,034,442.25 |    0.2% |      0.23 | `Arithmetic Operations Per Type | divide__instance__int64_t | 1000`
	|   197.8% |              965.47 |        1,035,769.06 |    0.1% |      0.23 | `Arithmetic Operations Per Type | divide__instance__size_t | 1000`
	|   197.9% |              965.17 |        1,036,091.57 |    0.1% |      0.21 | `Arithmetic Operations Per Type | divide__instance__float | 1000`
	|   197.5% |              966.97 |        1,034,160.56 |    0.2% |      0.23 | `Arithmetic Operations Per Type | divide__instance__double | 1000`
	|   197.6% |              966.69 |        1,034,462.62 |    0.4% |      0.22 | `Arithmetic Operations Per Type | divide__instance__long_double | 1000`

	|   100.0% |        1,901,400.00 |              525.93 |    3.7% |      0.02 | `Arithmetic Operations Per Type | add__instance__char | 1000000`
	|    99.5% |        1,910,000.00 |              523.56 |    2.5% |      0.02 | `Arithmetic Operations Per Type | add__instance__short_int | 1000000`
	|   132.7% |        1,433,200.00 |              697.74 |    0.1% |      0.02 | `Arithmetic Operations Per Type | add__instance__int | 1000000`
	|   132.7% |        1,432,800.00 |              697.93 |    0.5% |      0.02 | `Arithmetic Operations Per Type | add__instance__long_int | 1000000`
	|   132.6% |        1,433,500.00 |              697.59 |    0.7% |      0.02 | `Arithmetic Operations Per Type | add__instance__long_long_int | 1000000`
	|    99.5% |        1,911,000.00 |              523.29 |    1.7% |      0.02 | `Arithmetic Operations Per Type | add__instance__int8_t | 1000000`
	|    99.2% |        1,917,500.00 |              521.51 |    2.9% |      0.02 | `Arithmetic Operations Per Type | add__instance__int16_t | 1000000`
	|   132.7% |        1,432,700.00 |              697.98 |    0.1% |      0.02 | `Arithmetic Operations Per Type | add__instance__int32_t | 1000000`
	|   132.1% |        1,439,000.00 |              694.93 |    0.5% |      0.02 | `Arithmetic Operations Per Type | add__instance__int64_t | 1000000`
	|   132.5% |        1,435,400.00 |              696.67 |    0.5% |      0.02 | `Arithmetic Operations Per Type | add__instance__size_t | 1000000`
	|    61.2% |        3,105,200.00 |              322.04 |    0.1% |      0.04 | `Arithmetic Operations Per Type | add__instance__float | 1000000`
	|    61.3% |        3,104,200.00 |              322.14 |    0.0% |      0.03 | `Arithmetic Operations Per Type | add__instance__double | 1000000`
	|    61.2% |        3,104,800.00 |              322.08 |    0.0% |      0.03 | `Arithmetic Operations Per Type | add__instance__long_double | 1000000`
	|   198.8% |          956,500.00 |            1,045.48 |    0.2% |      0.01 | `Arithmetic Operations Per Type | subtract__instance__char | 1000000`
	|   198.9% |          955,900.00 |            1,046.13 |    0.1% |      0.01 | `Arithmetic Operations Per Type | subtract__instance__short_int | 1000000`
	|   199.0% |          955,300.00 |            1,046.79 |    0.1% |      0.01 | `Arithmetic Operations Per Type | subtract__instance__int | 1000000`
	|   199.1% |          955,100.00 |            1,047.01 |    0.1% |      0.01 | `Arithmetic Operations Per Type | subtract__instance__long_int | 1000000`
	|   199.0% |          955,300.00 |            1,046.79 |    0.1% |      0.01 | `Arithmetic Operations Per Type | subtract__instance__long_long_int | 1000000`
	|   199.0% |          955,400.00 |            1,046.68 |    0.1% |      0.01 | `Arithmetic Operations Per Type | subtract__instance__int8_t | 1000000`
	|   198.3% |          959,000.00 |            1,042.75 |    0.5% |      0.01 | `Arithmetic Operations Per Type | subtract__instance__int16_t | 1000000`
	|   199.0% |          955,300.00 |            1,046.79 |    0.1% |      0.01 | `Arithmetic Operations Per Type | subtract__instance__int32_t | 1000000`
	|   199.0% |          955,300.00 |            1,046.79 |    0.1% |      0.01 | `Arithmetic Operations Per Type | subtract__instance__int64_t | 1000000`
	|   198.9% |          956,000.00 |            1,046.03 |    0.1% |      0.01 | `Arithmetic Operations Per Type | subtract__instance__size_t | 1000000`
	|    61.3% |        3,104,100.00 |              322.15 |    0.0% |      0.03 | `Arithmetic Operations Per Type | subtract__instance__float | 1000000`
	|    61.3% |        3,104,200.00 |              322.14 |    0.0% |      0.03 | `Arithmetic Operations Per Type | subtract__instance__double | 1000000`
	|    61.2% |        3,104,500.00 |              322.11 |    0.0% |      0.03 | `Arithmetic Operations Per Type | subtract__instance__long_double | 1000000`
	|    88.5% |        2,148,600.00 |              465.42 |    0.0% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__char | 1000000`
	|    88.5% |        2,148,600.00 |              465.42 |    0.0% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__short_int | 1000000`
	|    99.5% |        1,911,900.00 |              523.04 |    0.1% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__int | 1000000`
	|    99.5% |        1,910,000.00 |              523.56 |    0.0% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__long_int | 1000000`
	|    99.5% |        1,910,200.00 |              523.51 |    0.0% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__long_long_int | 1000000`
	|    88.5% |        2,148,600.00 |              465.42 |    0.0% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__int8_t | 1000000`
	|    88.5% |        2,149,400.00 |              465.25 |    0.0% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__int16_t | 1000000`
	|    99.5% |        1,910,100.00 |              523.53 |    0.0% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__int32_t | 1000000`
	|    99.5% |        1,911,000.00 |              523.29 |    0.1% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__int64_t | 1000000`
	|    99.5% |        1,910,500.00 |              523.42 |    0.0% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__size_t | 1000000`
	|    88.4% |        2,151,200.00 |              464.86 |    0.1% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__float | 1000000`
	|    88.2% |        2,155,500.00 |              463.93 |    0.3% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__double | 1000000`
	|    88.4% |        2,150,000.00 |              465.12 |    0.1% |      0.02 | `Arithmetic Operations Per Type | multiply__instance__long_double | 1000000`
	|   198.9% |          955,800.00 |            1,046.24 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__char | 1000000`
	|   198.9% |          955,800.00 |            1,046.24 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__short_int | 1000000`
	|   199.0% |          955,300.00 |            1,046.79 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__int | 1000000`
	|   199.0% |          955,400.00 |            1,046.68 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__long_int | 1000000`
	|   198.7% |          957,000.00 |            1,044.93 |    0.3% |      0.01 | `Arithmetic Operations Per Type | divide__instance__long_long_int | 1000000`
	|   198.9% |          955,800.00 |            1,046.24 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__int8_t | 1000000`
	|   199.0% |          955,300.00 |            1,046.79 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__int16_t | 1000000`
	|   199.0% |          955,300.00 |            1,046.79 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__int32_t | 1000000`
	|   199.0% |          955,600.00 |            1,046.46 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__int64_t | 1000000`
	|   198.6% |          957,400.00 |            1,044.50 |    0.3% |      0.01 | `Arithmetic Operations Per Type | divide__instance__size_t | 1000000`
	|   199.0% |          955,500.00 |            1,046.57 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__float | 1000000`
	|   199.0% |          955,300.00 |            1,046.79 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__double | 1000000`
	|   199.0% |          955,500.00 |            1,046.57 |    0.1% |      0.01 | `Arithmetic Operations Per Type | divide__instance__long_double | 1000000`

	*/

	class Samples
	{
	public:
		char char_instance_value = 1;

		int int_instance_value = 1;

		short int short_int_instance_value = 1;

		long int long_int_instance_value = 1;

		long long int long_long_int_instance_value = 1;

		int8_t int8_t_instance_value = 1;

		int16_t int16_t_instance_value = 1;

		int32_t int32_t_instance_value = 1;

		int64_t int64_t_instance_value = 1;

		size_t size_t_instance_value = 1;

		float float_instance_value = 1.0;

		double double_instance_value = 1.0;

		long double long_double_instance_value = 1.0;

		static Samples instance;

		void add__instance__char()
		{
			char_instance_value += char_instance_value + 1;
		}

		void add__instance__short_int()
		{
			short_int_instance_value += short_int_instance_value + 1;
		}

		void add__instance__int()
		{
			int_instance_value += int_instance_value + 1;
		}

		void add__instance__long_int()
		{
			long_int_instance_value += long_int_instance_value + 1;
		}

		void add__instance__long_long_int()
		{
			long_long_int_instance_value += long_long_int_instance_value + 1;
		}

		void add__instance__int8_t()
		{
			int8_t_instance_value += int8_t_instance_value + 1;
		}

		void add__instance__int16_t()
		{
			int16_t_instance_value += int16_t_instance_value + 1;
		}

		void add__instance__int32_t()
		{
			int32_t_instance_value += int32_t_instance_value + 1;
		}

		void add__instance__int64_t()
		{
			int64_t_instance_value += int64_t_instance_value + 1;
		}

		void add__instance__size_t()
		{
			size_t_instance_value += size_t_instance_value + 1;

		}

		void add__instance__float()
		{
			float_instance_value += float_instance_value + 1.0;
		}

		void add__instance__double()
		{
			double_instance_value += double_instance_value + 1.0;
		}

		void add__instance__long_double()
		{
			long_double_instance_value += long_double_instance_value + 1.0;
		}



		void multiply__instance__char()
		{
			char_instance_value *= char_instance_value * 1;
		}

		void multiply__instance__short_int()
		{
			short_int_instance_value *= short_int_instance_value * 1;
		}

		void multiply__instance__int()
		{
			int_instance_value *= int_instance_value * 1;
		}

		void multiply__instance__long_int()
		{
			long_int_instance_value *= long_int_instance_value * 1;
		}

		void multiply__instance__long_long_int()
		{
			long_long_int_instance_value *= long_long_int_instance_value * 1;
		}

		void multiply__instance__int8_t()
		{
			int8_t_instance_value *= int8_t_instance_value * 1;
		}

		void multiply__instance__int16_t()
		{
			int16_t_instance_value *= int16_t_instance_value * 1;
		}

		void multiply__instance__int32_t()
		{
			int32_t_instance_value *= int32_t_instance_value * 1;
		}

		void multiply__instance__int64_t()
		{
			int64_t_instance_value *= int64_t_instance_value * 1;
		}

		void multiply__instance__size_t()
		{
			size_t_instance_value *= size_t_instance_value * 1;

		}

		void multiply__instance__float()
		{
			float_instance_value *= float_instance_value * 1.0;
		}

		void multiply__instance__double()
		{
			double_instance_value *= double_instance_value * 1.0;
		}

		void multiply__instance__long_double()
		{
			long_double_instance_value *= long_double_instance_value * 1.0;
		}



		void subtract__instance__char()
		{
			char_instance_value -= char_instance_value - 1;
		}

		void subtract__instance__short_int()
		{
			short_int_instance_value -= short_int_instance_value - 1;
		}

		void subtract__instance__int()
		{
			int_instance_value -= int_instance_value - 1;
		}

		void subtract__instance__long_int()
		{
			long_int_instance_value -= long_int_instance_value - 1;
		}

		void subtract__instance__long_long_int()
		{
			long_long_int_instance_value -= long_long_int_instance_value - 1;
		}

		void subtract__instance__int8_t()
		{
			int8_t_instance_value -= int8_t_instance_value - 1;
		}

		void subtract__instance__int16_t()
		{
			int16_t_instance_value -= int16_t_instance_value - 1;
		}

		void subtract__instance__int32_t()
		{
			int32_t_instance_value -= int32_t_instance_value - 1;
		}

		void subtract__instance__int64_t()
		{
			int64_t_instance_value -= int64_t_instance_value - 1;
		}

		void subtract__instance__size_t()
		{
			size_t_instance_value -= size_t_instance_value - 1;

		}

		void subtract__instance__float()
		{
			float_instance_value -= float_instance_value - 1.0;
		}

		void subtract__instance__double()
		{
			double_instance_value -= double_instance_value - 1.0;
		}

		void subtract__instance__long_double()
		{
			long_double_instance_value -= long_double_instance_value - 1.0;
		}


		void divide__instance__char()
		{
			char_instance_value = char_instance_value / 1;
		}

		void divide__instance__short_int()
		{
			short_int_instance_value = short_int_instance_value / 1;
		}

		void divide__instance__int()
		{
			int_instance_value = int_instance_value / 1;
		}

		void divide__instance__long_int()
		{
			long_int_instance_value = long_int_instance_value / 1;
		}

		void divide__instance__long_long_int()
		{
			long_long_int_instance_value = long_long_int_instance_value / 1;
		}

		void divide__instance__int8_t()
		{
			int8_t_instance_value = int8_t_instance_value / 1;
		}

		void divide__instance__int16_t()
		{
			int16_t_instance_value = int16_t_instance_value / 1;
		}

		void divide__instance__int32_t()
		{
			int32_t_instance_value = int32_t_instance_value / 1;
		}

		void divide__instance__int64_t()
		{
			int64_t_instance_value = int64_t_instance_value / 1;
		}

		void divide__instance__size_t()
		{
			size_t_instance_value = size_t_instance_value / 1;

		}

		void divide__instance__float()
		{
			float_instance_value = float_instance_value / 1.0;
		}

		void divide__instance__double()
		{
			double_instance_value = double_instance_value / 1.0;
		}

		void divide__instance__long_double()
		{
			long_double_instance_value = long_double_instance_value / 1.0;
		}
	};

	Samples Samples::instance;

	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "Arithmetic Operations Per Type",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 20000000,
					.iterations = 1
				},
				{
					.epochs = 20000,
					.iterations = 1000
				},
				{
					.epochs = 1,
					.iterations = 1000000
				}
			},
			.test_cases =
			{
				{
					.name = "add__instance__char",
					.callback = []() { Samples::instance.add__instance__char(); }
				},
				{
					.name = "add__instance__short_int",
					.callback = []() { Samples::instance.add__instance__short_int(); }
				},
				{
					.name = "add__instance__int",
					.callback = []() { Samples::instance.add__instance__int(); }
				},
				{
					.name = "add__instance__long_int",
					.callback = []() { Samples::instance.add__instance__long_int(); }
				},
				{
					.name = "add__instance__long_long_int",
					.callback = []() { Samples::instance.add__instance__long_long_int(); }
				},
				{
					.name = "add__instance__int8_t",
					.callback = []() { Samples::instance.add__instance__int8_t(); }
				},
				{
					.name = "add__instance__int16_t",
					.callback = []() { Samples::instance.add__instance__int16_t(); }
				},
				{
					.name = "add__instance__int32_t",
					.callback = []() { Samples::instance.add__instance__int32_t(); }
				},
				{
					.name = "add__instance__int64_t",
					.callback = []() { Samples::instance.add__instance__int64_t(); }
				},
				{
					.name = "add__instance__size_t",
					.callback = []() { Samples::instance.add__instance__size_t(); }
				},
				{
					.name = "add__instance__float",
					.callback = []() { Samples::instance.add__instance__float(); }
				},
				{
					.name = "add__instance__double",
					.callback = []() { Samples::instance.add__instance__double(); }
				},
				{
					.name = "add__instance__long_double",
					.callback = []() { Samples::instance.add__instance__long_double(); }
				},

				{
					.name = "subtract__instance__char",
					.callback = []() { Samples::instance.subtract__instance__char(); }
				},
				{
					.name = "subtract__instance__short_int",
					.callback = []() { Samples::instance.subtract__instance__short_int(); }
				},
				{
					.name = "subtract__instance__int",
					.callback = []() { Samples::instance.subtract__instance__int(); }
				},
				{
					.name = "subtract__instance__long_int",
					.callback = []() { Samples::instance.subtract__instance__long_int(); }
				},
				{
					.name = "subtract__instance__long_long_int",
					.callback = []() { Samples::instance.subtract__instance__long_long_int(); }
				},
				{
					.name = "subtract__instance__int8_t",
					.callback = []() { Samples::instance.subtract__instance__int8_t(); }
				},
				{
					.name = "subtract__instance__int16_t",
					.callback = []() { Samples::instance.subtract__instance__int16_t(); }
				},
				{
					.name = "subtract__instance__int32_t",
					.callback = []() { Samples::instance.subtract__instance__int32_t(); }
				},
				{
					.name = "subtract__instance__int64_t",
					.callback = []() { Samples::instance.subtract__instance__int64_t(); }
				},
				{
					.name = "subtract__instance__size_t",
					.callback = []() { Samples::instance.subtract__instance__size_t(); }
				},
				{
					.name = "subtract__instance__float",
					.callback = []() { Samples::instance.subtract__instance__float(); }
				},
				{
					.name = "subtract__instance__double",
					.callback = []() { Samples::instance.subtract__instance__double(); }
				},
				{
					.name = "subtract__instance__long_double",
					.callback = []() { Samples::instance.subtract__instance__long_double(); }
				},


				{
					.name = "multiply__instance__char",
					.callback = []() { Samples::instance.multiply__instance__char(); }
				},
				{
					.name = "multiply__instance__short_int",
					.callback = []() { Samples::instance.multiply__instance__short_int(); }
				},
				{
					.name = "multiply__instance__int",
					.callback = []() { Samples::instance.multiply__instance__int(); }
				},
				{
					.name = "multiply__instance__long_int",
					.callback = []() { Samples::instance.multiply__instance__long_int(); }
				},
				{
					.name = "multiply__instance__long_long_int",
					.callback = []() { Samples::instance.multiply__instance__long_long_int(); }
				},
				{
					.name = "multiply__instance__int8_t",
					.callback = []() { Samples::instance.multiply__instance__int8_t(); }
				},
				{
					.name = "multiply__instance__int16_t",
					.callback = []() { Samples::instance.multiply__instance__int16_t(); }
				},
				{
					.name = "multiply__instance__int32_t",
					.callback = []() { Samples::instance.multiply__instance__int32_t(); }
				},
				{
					.name = "multiply__instance__int64_t",
					.callback = []() { Samples::instance.multiply__instance__int64_t(); }
				},
				{
					.name = "multiply__instance__size_t",
					.callback = []() { Samples::instance.multiply__instance__size_t(); }
				},
				{
					.name = "multiply__instance__float",
					.callback = []() { Samples::instance.multiply__instance__float(); }
				},
				{
					.name = "multiply__instance__double",
					.callback = []() { Samples::instance.multiply__instance__double(); }
				},
				{
					.name = "multiply__instance__long_double",
					.callback = []() { Samples::instance.multiply__instance__long_double(); }
				},


				{
					.name = "divide__instance__char",
					.callback = []() { Samples::instance.divide__instance__char(); }
				},
				{
					.name = "divide__instance__short_int",
					.callback = []() { Samples::instance.divide__instance__short_int(); }
				},
				{
					.name = "divide__instance__int",
					.callback = []() { Samples::instance.divide__instance__int(); }
				},
				{
					.name = "divide__instance__long_int",
					.callback = []() { Samples::instance.divide__instance__long_int(); }
				},
				{
					.name = "divide__instance__long_long_int",
					.callback = []() { Samples::instance.divide__instance__long_long_int(); }
				},
				{
					.name = "divide__instance__int8_t",
					.callback = []() { Samples::instance.divide__instance__int8_t(); }
				},
				{
					.name = "divide__instance__int16_t",
					.callback = []() { Samples::instance.divide__instance__int16_t(); }
				},
				{
					.name = "divide__instance__int32_t",
					.callback = []() { Samples::instance.divide__instance__int32_t(); }
				},
				{
					.name = "divide__instance__int64_t",
					.callback = []() { Samples::instance.divide__instance__int64_t(); }
				},
				{
					.name = "divide__instance__size_t",
					.callback = []() { Samples::instance.divide__instance__size_t(); }
				},
				{
					.name = "divide__instance__float",
					.callback = []() { Samples::instance.divide__instance__float(); }
				},
				{
					.name = "divide__instance__double",
					.callback = []() { Samples::instance.divide__instance__double(); }
				},
				{
					.name = "divide__instance__long_double",
					.callback = []() { Samples::instance.divide__instance__long_double(); }
				},
			}
		};

		execute_nanobenchmark(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}


namespace StringOperations
{
	/*
	
	Conclusions
	- general api method signature
		- Type synchronous_method(const Type& a, ..., const ConfigurationType& configurations = {})
		- std::future<Type> asynchronous_method(const Type& a, ..., const std::function<FunctionType>& callback = {}, const ConfigurationType& configurations = {})
		- void asynchronous_method(const Type& a, ..., const ConfigurationType& configurations = {})
	- strategies
		- for method parameter types and local variables
			- when string is processed within the method			
				- std::string
			- when passing by value (via recursion or iteration)			
				- std::string_view

	 
	About
	- Timestamp Created
		- 8:06 AM, January 14, 2026

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |                3.87 |      258,130,456.78 |    0.7% |      0.49 | `String Operations | assign__string_to_string | 1`
	|   320.5% |                1.21 |      827,404,997.58 |    0.3% |      0.15 | `String Operations | assign__string_view_to_string_view | 1`
	|    99.4% |                3.90 |      256,629,770.35 |    0.1% |      0.47 | `String Operations | assign__string_view_to_string | 1`
	|   320.0% |                1.21 |      825,890,885.62 |    0.3% |      0.15 | `String Operations | assign__string_to_string_view | 1`
	|    29.0% |               13.35 |       74,933,394.59 |    1.1% |      1.62 | `String Operations | assign__string_parameter__const_arguments__concatenate_string | 1`
	|    28.9% |               13.41 |       74,552,514.90 |    0.7% |      1.62 | `String Operations | assign__const_string_parameter__const_arguments__concatenate_string | 1`
	|   228.6% |                1.69 |      590,074,986.87 |    0.9% |      0.20 | `String Operations | assign__reference_string_parameter__instance_arguments__concatenate_string | 1`
	|    55.8% |                6.94 |      144,041,334.25 |    0.2% |      0.76 | `String Operations | assign__const_reference_string_parameter__const_arguments__concatenate_string | 1`
	|    83.6% |                4.63 |      215,909,872.42 |    0.3% |      0.56 | `String Operations | return_and_assign__string_parameter__const_arguments__concatenate_string | 1`
	|    83.2% |                4.66 |      214,751,888.69 |    0.4% |      0.56 | `String Operations | return_and_assign__const_string_parameter__const_arguments__concatenate_string | 1`
	|   228.2% |                1.70 |      589,098,997.32 |    1.3% |      0.21 | `String Operations | return_and_assign__reference_string_parameter__instance_arguments__concatenate_string | 1`
	|   201.0% |                1.93 |      518,841,586.37 |    0.6% |      0.23 | `String Operations | return_and_assign__const_reference_string_parameter__const_arguments__concatenate_string | 1`
	|     1.9% |              198.85 |        5,028,808.96 |    2.5% |     23.83 | `String Operations | recursive__pass_and_return__const_reference_string_parameter__const_arguments__concatenate_string | 1`
	|     2.0% |              195.93 |        5,103,973.49 |    0.7% |     24.32 | `String Operations | recursive__pass_and_return__const_reference_string_view_parameter__const_arguments__concatenate_string | 1`
	|     1.6% |              240.06 |        4,165,650.83 |    1.8% |     28.91 | `String Operations | recursive__pass_and_return__const_reference_char_string_parameter__const_arguments__concatenate_string | 1`
	|    13.9% |               27.82 |       35,941,841.90 |    0.5% |      3.38 | `String Operations | recursive__pass__const_reference_string_parameter__const_arguments__concatenate_string | 1`
	|    15.2% |               25.56 |       39,129,338.96 |    1.0% |      3.10 | `String Operations | recursive__pass__const_reference_string_view_parameter__const_arguments__concatenate_string | 1`
	|    11.9% |               32.52 |       30,751,979.08 |    0.8% |      3.94 | `String Operations | recursive__pass__const_reference_char_string_parameter__const_arguments__concatenate_string | 1`

	|   100.0% |            3,673.60 |          272,212.74 |    0.3% |      0.44 | `String Operations | assign__string_to_string | 1000`
	|   374.4% |              981.17 |        1,019,187.27 |    0.5% |      0.12 | `String Operations | assign__string_view_to_string_view | 1000`
	|    98.9% |            3,713.30 |          269,302.47 |    0.2% |      0.45 | `String Operations | assign__string_view_to_string | 1000`
	|   331.6% |            1,108.00 |          902,524.91 |    0.4% |      0.13 | `String Operations | assign__string_to_string_view | 1000`
	|    27.6% |           13,301.49 |           75,179.55 |    0.4% |      1.61 | `String Operations | assign__string_parameter__const_arguments__concatenate_string | 1000`
	|    27.5% |           13,345.91 |           74,929.31 |    0.4% |      1.61 | `String Operations | assign__const_string_parameter__const_arguments__concatenate_string | 1000`
	|   234.4% |            1,566.97 |          638,176.33 |    1.3% |      0.19 | `String Operations | assign__reference_string_parameter__instance_arguments__concatenate_string | 1000`
	|    59.1% |            6,220.40 |          160,761.46 |    0.1% |      0.76 | `String Operations | assign__const_reference_string_parameter__const_arguments__concatenate_string | 1000`
	|    74.9% |            4,905.75 |          203,842.42 |    0.5% |      0.59 | `String Operations | return_and_assign__string_parameter__const_arguments__concatenate_string | 1000`
	|    74.9% |            4,905.04 |          203,871.76 |    0.3% |      0.59 | `String Operations | return_and_assign__const_string_parameter__const_arguments__concatenate_string | 1000`
	|   229.4% |            1,601.45 |          624,435.52 |    2.7% |      0.20 | `String Operations | return_and_assign__reference_string_parameter__instance_arguments__concatenate_string | 1000`
	|   206.1% |            1,782.42 |          561,033.55 |    0.5% |      0.22 | `String Operations | return_and_assign__const_reference_string_parameter__const_arguments__concatenate_string | 1000`
	|     1.7% |          218,880.04 |            4,568.71 |    1.4% |     26.23 | `String Operations | recursive__pass_and_return__const_reference_string_parameter__const_arguments__concatenate_string | 1000`
	|     1.8% |          199,754.10 |            5,006.16 |    0.3% |     24.18 | `String Operations | recursive__pass_and_return__const_reference_string_view_parameter__const_arguments__concatenate_string | 1000`
	|     1.6% |          226,195.24 |            4,420.96 |    0.9% |     27.49 | `String Operations | recursive__pass_and_return__const_reference_char_string_parameter__const_arguments__concatenate_string | 1000`
	|    12.8% |           28,611.99 |           34,950.39 |    0.1% |      3.46 | `String Operations | recursive__pass__const_reference_string_parameter__const_arguments__concatenate_string | 1000`
	|    12.7% |           28,947.43 |           34,545.38 |    0.6% |      3.50 | `String Operations | recursive__pass__const_reference_string_view_parameter__const_arguments__concatenate_string | 1000`
	|    10.5% |           34,946.34 |           28,615.30 |    0.2% |      4.23 | `String Operations | recursive__pass__const_reference_char_string_parameter__const_arguments__concatenate_string | 1000`

	|   100.0% |        3,610,890.00 |              276.94 |    0.4% |      0.44 | `String Operations | assign__string_to_string | 1000000`
	|   377.1% |          957,541.67 |            1,044.34 |    0.3% |      0.12 | `String Operations | assign__string_view_to_string_view | 1000000`
	|    99.8% |        3,618,533.33 |              276.36 |    0.4% |      0.44 | `String Operations | assign__string_view_to_string | 1000000`
	|   332.7% |        1,085,180.00 |              921.51 |    0.4% |      0.13 | `String Operations | assign__string_to_string_view | 1000000`
	|    27.3% |       13,223,490.91 |               75.62 |    0.2% |      1.61 | `String Operations | assign__string_parameter__const_arguments__concatenate_string | 1000000`
	|    27.2% |       13,278,575.00 |               75.31 |    0.1% |      1.62 | `String Operations | assign__const_string_parameter__const_arguments__concatenate_string | 1000000`
	|   241.2% |        1,496,781.82 |              668.10 |    0.2% |      0.18 | `String Operations | assign__reference_string_parameter__instance_arguments__concatenate_string | 1000000`
	|    58.1% |        6,213,336.36 |              160.94 |    0.1% |      0.76 | `String Operations | assign__const_reference_string_parameter__const_arguments__concatenate_string | 1000000`
	|    77.2% |        4,676,363.64 |              213.84 |    1.0% |      0.57 | `String Operations | return_and_assign__string_parameter__const_arguments__concatenate_string | 1000000`
	|    76.8% |        4,701,075.00 |              212.72 |    0.8% |      0.57 | `String Operations | return_and_assign__const_string_parameter__const_arguments__concatenate_string | 1000000`
	|   243.0% |        1,486,016.67 |              672.94 |    1.0% |      0.18 | `String Operations | return_and_assign__reference_string_parameter__instance_arguments__concatenate_string | 1000000`
	|   207.3% |        1,741,718.18 |              574.15 |    0.3% |      0.21 | `String Operations | return_and_assign__const_reference_string_parameter__const_arguments__concatenate_string | 1000000`
	|     1.7% |      207,753,390.91 |                4.81 |    1.2% |     25.70 | `String Operations | recursive__pass_and_return__const_reference_string_parameter__const_arguments__concatenate_string | 1000000`
	|     1.9% |      193,253,275.00 |                5.17 |    0.3% |     23.69 | `String Operations | recursive__pass_and_return__const_reference_string_view_parameter__const_arguments__concatenate_string | 1000000`
	|     1.6% |      226,073,530.00 |                4.42 |    0.7% |     27.85 | `String Operations | recursive__pass_and_return__const_reference_char_string_parameter__const_arguments__concatenate_string | 1000000`
	|    13.0% |       27,698,570.00 |               36.10 |    1.5% |      3.37 | `String Operations | recursive__pass__const_reference_string_parameter__const_arguments__concatenate_string | 1000000`
	|    15.2% |       23,760,136.36 |               42.09 |    0.8% |      2.90 | `String Operations | recursive__pass__const_reference_string_view_parameter__const_arguments__concatenate_string | 1000000`
	|    10.8% |       33,395,383.33 |               29.94 |    0.5% |      4.07 | `String Operations | recursive__pass__const_reference_char_string_parameter__const_arguments__concatenate_string | 1000000`
	*/

	class Samples
	{
	public:
		std::string instance_string_input = "a";

		std::string instance_string_output = "";

		std::string instance_string_output_2 = "";

		std::string_view instance_string_view_input = "a";

		std::string_view instance_string_view_output = "";

		static Samples instance;

		void assign__string_to_string()
		{
			instance_string_output =
				instance_string_input;
		}

		void assign__string_view_to_string_view()
		{
			instance_string_view_output =
				instance_string_view_input;
		}

		void assign__string_view_to_string()
		{
			instance_string_output =
				instance_string_view_input;
		}

		void assign__string_to_string_view()
		{
			instance_string_view_output =
				instance_string_input;
		}

		void assign__string_parameter__const_arguments__concatenate_string(
			std::string a, std::string b
		)
		{
			instance_string_output =
				a + b;
		}

		void assign__const_string_parameter__const_arguments__concatenate_string(
			const std::string a, const std::string b
		)
		{
			instance_string_output =
				a + b;
		}

		void assign__reference_string_parameter__instance_arguments__concatenate_string(
			std::string& a, std::string& b
		)
		{
			a += b;
		}

		void assign__const_reference_string_parameter__const_arguments__concatenate_string(
			const std::string& a, const std::string& b
		)
		{
			instance_string_output =
				a + b;
		}

		std::string return_and_assign__string_parameter__const_arguments__concatenate_string(
			std::string a, std::string b
		)
		{
			return
				a + b;
		}

		std::string return_and_assign__const_string_parameter__const_arguments__concatenate_string(
			const std::string a, const std::string b
		)
		{
			return
				a + b;
		}

		std::string return_and_assign__reference_string_parameter__instance_arguments__concatenate_string(
			std::string& a, std::string& b
		)
		{
			return
				a + b;
		}

		std::string return_and_assign__const_reference_string_parameter__const_arguments__concatenate_string(
			const std::string& a, const std::string& b
		)
		{
			return
				a + b;
		}



		std::string recursive__pass_and_return__const_reference_string_parameter__const_arguments__concatenate_string(
			const std::string& value_1,
			const std::string& value_2,
			const std::size_t layers
		)
		{
			if (layers == 0)
			{
				return value_1 + value_2;
			}

			return recursive__pass_and_return__const_reference_string_parameter__const_arguments__concatenate_string(
				value_1,
				value_2,
				layers - 1
			);
		}

		std::string recursive__pass_and_return__const_reference_string_view_parameter__const_arguments__concatenate_string(
			const std::string_view& value_1,
			const std::string_view& value_2,
			const std::size_t layers
		)
		{
			if (layers == 0)
			{
				return std::string(value_1.data()) + value_2.data();
			}

			return recursive__pass_and_return__const_reference_string_view_parameter__const_arguments__concatenate_string(
				value_1,
				value_2,
				layers - 1
			);
		}

		std::string recursive__pass_and_return__const_reference_char_string_parameter__const_arguments__concatenate_string(
			const char* value_1,
			const char* value_2,
			const std::size_t layers
		)
		{
			if (layers == 0)
			{
				return std::string(value_1) + std::string(value_2);
			}

			return recursive__pass_and_return__const_reference_char_string_parameter__const_arguments__concatenate_string(
				value_1,
				value_2,
				layers - 1
			);
		}
		void recursive__pass__const_reference_string_parameter__const_arguments__concatenate_string(
			std::string& output,
			const std::string& value_1,
			const std::string& value_2,
			const std::size_t layers
		)
		{
			if (layers == 0)
			{
				output = value_1 + value_2;
				return;
			}

			recursive__pass__const_reference_string_parameter__const_arguments__concatenate_string(
				output,
				value_1,
				value_2,
				layers - 1
			);
		}

		void recursive__pass__const_reference_string_view_parameter__const_arguments__concatenate_string(
			std::string& output,
			const std::string_view& value_1,
			const std::string_view& value_2,
			const std::size_t layers
		)
		{
			if (layers == 0)
			{
				output = std::string(value_1.data()) + value_2.data();
				return;
			}

			recursive__pass__const_reference_string_view_parameter__const_arguments__concatenate_string(
				output,
				value_1,
				value_2,
				layers - 1
			);
		}

		void recursive__pass__const_reference_char_string_parameter__const_arguments__concatenate_string(
			std::string& output,
			const char* value_1,
			const char* value_2,
			const std::size_t layers
		)
		{
			if (layers == 0)
			{
				output = std::string(value_1) + std::string(value_2);
				return;
			}

			recursive__pass__const_reference_char_string_parameter__const_arguments__concatenate_string(
				output,
				value_1,
				value_2,
				layers - 1
			);
		}


	};

	Samples Samples::instance;

	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "String Operations",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 10000000,
					.iterations = 1
				},
				{
					.epochs = 10000,
					.iterations = 1000
				},
				{
					.epochs = 10,
					.iterations = 1000000
				}
			},
			.test_cases =
			{
				{
					.name = "assign__string_to_string",
					.callback = []() { Samples::instance.assign__string_to_string(); }
				},
				{
					.name = "assign__string_view_to_string_view",
					.callback = []() { Samples::instance.assign__string_view_to_string_view(); }
				},
				{
					.name = "assign__string_view_to_string",
					.callback = []() { Samples::instance.assign__string_view_to_string(); }
				},
				{
					.name = "assign__string_to_string_view",
					.callback = []() { Samples::instance.assign__string_to_string_view(); }
				},
				{
					.name = "assign__string_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						Samples::instance
							.assign__string_parameter__const_arguments__concatenate_string("a", "a");
					}
				},
				{
					.name = "assign__const_string_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						Samples::instance
							.assign__const_string_parameter__const_arguments__concatenate_string("a", "a");
					}
				},
				{
					.name = "assign__reference_string_parameter__instance_arguments__concatenate_string",
					.callback = []()
					{
						std::string input_1 = "";
						std::string input_2 = "";
						Samples::instance
							.assign__reference_string_parameter__instance_arguments__concatenate_string(input_1, input_2);
					}
				},
				{
					.name = "assign__const_reference_string_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						Samples::instance
							.assign__const_reference_string_parameter__const_arguments__concatenate_string("a", "a");
					}
				},

				{
					.name = "return_and_assign__string_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						std::string v = Samples::instance
							.return_and_assign__string_parameter__const_arguments__concatenate_string("a", "a");
					}
				},
				{
					.name = "return_and_assign__const_string_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						std::string v = Samples::instance
							.return_and_assign__const_string_parameter__const_arguments__concatenate_string("a", "a");
					}
				},
				{
					.name = "return_and_assign__reference_string_parameter__instance_arguments__concatenate_string",
					.callback = []()
					{
						std::string input_1 = "";
						std::string input_2 = "";
						std::string v = Samples::instance
							.return_and_assign__reference_string_parameter__instance_arguments__concatenate_string(input_1, input_2);
					}
				},
				{
					.name = "return_and_assign__const_reference_string_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						std::string v = Samples::instance
							.return_and_assign__const_reference_string_parameter__const_arguments__concatenate_string("a", "a");
					}
				},
				{
					.name = "recursive__pass_and_return__const_reference_string_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						std::string v = Samples::instance
							.recursive__pass_and_return__const_reference_string_parameter__const_arguments__concatenate_string("a", "a", 40);
					}
				},
				{
					.name = "recursive__pass_and_return__const_reference_string_view_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						std::string v = Samples::instance
							.recursive__pass_and_return__const_reference_string_view_parameter__const_arguments__concatenate_string("a", "a", 40);
					}
				},
				{
					.name = "recursive__pass_and_return__const_reference_char_string_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						std::string v = Samples::instance
							.recursive__pass_and_return__const_reference_char_string_parameter__const_arguments__concatenate_string("a", "a", 40);
					}
				},
				{
					.name = "recursive__pass__const_reference_string_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						std::string output = "";
						Samples::instance
							.recursive__pass__const_reference_string_parameter__const_arguments__concatenate_string(output, "a", "a", 40);
					}
				},
				{
					.name = "recursive__pass__const_reference_string_view_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						std::string output = "";
						Samples::instance
							.recursive__pass__const_reference_string_view_parameter__const_arguments__concatenate_string(output, "a", "a", 40);
					}
				},
				{
					.name = "recursive__pass__const_reference_char_string_parameter__const_arguments__concatenate_string",
					.callback = []()
					{
						std::string output = "";
						Samples::instance
							.recursive__pass__const_reference_char_string_parameter__const_arguments__concatenate_string(output, "a", "a", 40);
					}
				}

			}
		};

		execute_nanobenchmark(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}



namespace ExecutionWithinNestedNamespaces
{
	/*

	Conclusion
	- Only one layered namespace, per C++ project, to avoid compilation re-definition errors



	About
	- Timestamp Created
		- 8:26 AM, January 14, 2026

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |                3.12 |      320,870,434.23 |    0.2% |      3.78 | `Namespace Layers | layer_0 | 1`
	|   100.2% |                3.11 |      321,625,795.53 |    0.1% |      3.76 | `Namespace Layers | Layer1::layer_1 | 1`
	|   100.3% |                3.11 |      321,758,366.82 |    0.0% |      3.76 | `Namespace Layers | Layer1::Layer2::layer_2 | 1`
	|   100.1% |                3.11 |      321,075,843.00 |    0.0% |      3.77 | `Namespace Layers | Layer1::Layer2::Layer3::layer_3 | 1`
	|   100.0% |                3.12 |      320,865,499.26 |    0.2% |      3.77 | `Namespace Layers | Layer1::Layer2::Layer3::Layer4::layer_4 | 1`
	|   100.3% |                3.11 |      321,716,101.28 |    0.0% |      3.76 | `Namespace Layers | Layer1::Layer2::Layer3::Layer4::Layer5::layer_5 | 1`

	|   100.0% |            3,112.98 |          321,235.58 |    0.1% |      3.77 | `Namespace Layers | layer_0 | 1000`
	|   100.1% |            3,108.33 |          321,715.92 |    0.0% |      3.76 | `Namespace Layers | Layer1::layer_1 | 1000`
	|   100.2% |            3,108.01 |          321,749.66 |    0.0% |      3.76 | `Namespace Layers | Layer1::Layer2::layer_2 | 1000`
	|   100.1% |            3,109.03 |          321,644.19 |    0.0% |      3.77 | `Namespace Layers | Layer1::Layer2::Layer3::layer_3 | 1000`
	|   100.2% |            3,107.40 |          321,812.44 |    0.0% |      3.76 | `Namespace Layers | Layer1::Layer2::Layer3::Layer4::layer_4 | 1000`
	|   100.2% |            3,107.50 |          321,801.99 |    0.0% |      3.76 | `Namespace Layers | Layer1::Layer2::Layer3::Layer4::Layer5::layer_5 | 1000`

	|   100.0% |        3,108,554.55 |              321.69 |    0.1% |      0.38 | `Namespace Layers | layer_0 | 1000000`
	|   100.1% |        3,106,845.45 |              321.87 |    0.1% |      0.38 | `Namespace Layers | Layer1::layer_1 | 1000000`
	|    95.8% |        3,243,275.00 |              308.33 |    1.2% |      0.40 | `Namespace Layers | Layer1::Layer2::layer_2 | 1000000`
	|   100.0% |        3,109,916.67 |              321.55 |    0.2% |      0.38 | `Namespace Layers | Layer1::Layer2::Layer3::layer_3 | 1000000`
	|   100.0% |        3,109,481.82 |              321.60 |    0.1% |      0.38 | `Namespace Layers | Layer1::Layer2::Layer3::Layer4::layer_4 | 1000000`
	|    99.9% |        3,110,250.00 |              321.52 |    0.1% |      0.38 | `Namespace Layers | Layer1::Layer2::Layer3::Layer4::Layer5::layer_5 | 1000000`

	*/

	class Samples
	{
	public:
		double double_output = 1;

		static Samples instance;
	};

	Samples Samples::instance;

	void layer_0()
	{
		Samples::instance.double_output +=
			Samples::instance.double_output * 1.0 * 2.0;
		Samples::instance.double_output +=
			Samples::instance.double_output * 1.0 * 2.0;
	}

	namespace Layer1
	{
		void layer_1()
		{
			Samples::instance.double_output +=
				Samples::instance.double_output * 1.0 * 2.0;
			Samples::instance.double_output +=
				Samples::instance.double_output * 1.0 * 2.0;
		}

		namespace Layer2
		{
			void layer_2()
			{
				Samples::instance.double_output +=
					Samples::instance.double_output * 1.0 * 2.0;
				Samples::instance.double_output +=
					Samples::instance.double_output * 1.0 * 2.0;
			}

			namespace Layer3
			{
				void layer_3()
				{
					Samples::instance.double_output +=
						Samples::instance.double_output * 1.0 * 2.0;
					Samples::instance.double_output +=
						Samples::instance.double_output * 1.0 * 2.0;
				}

				namespace Layer4
				{
					void layer_4()
					{
						Samples::instance.double_output +=
							Samples::instance.double_output * 1.0 * 2.0;
						Samples::instance.double_output +=
							Samples::instance.double_output * 1.0 * 2.0;
					}

					namespace Layer5
					{
						void layer_5()
						{
							Samples::instance.double_output +=
								Samples::instance.double_output * 1.0 * 2.0;
							Samples::instance.double_output +=
								Samples::instance.double_output * 1.0 * 2.0;
						}
					}
				}
			}
		}
	}

	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "Namespace Layers",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 100000000,
					.iterations = 1
				},
				{
					.epochs = 100000,
					.iterations = 1000
				},
				{
					.epochs = 10,
					.iterations = 1000000
				}
			},
			.test_cases =
			{
				{
					.name = "layer_0",
					.callback = []() { layer_0(); }
				},
				{
					.name = "Layer1::layer_1",
					.callback = []() { Layer1::layer_1(); }
				},
				{
					.name = "Layer1::Layer2::layer_2",
					.callback = []() { Layer1::Layer2::layer_2(); }
				},
				{
					.name = "Layer1::Layer2::Layer3::layer_3",
					.callback = []() { Layer1::Layer2::Layer3::layer_3(); }
				},
				{
					.name = "Layer1::Layer2::Layer3::Layer4::layer_4",
					.callback = []() { Layer1::Layer2::Layer3::Layer4::layer_4(); }
				},
				{
					.name = "Layer1::Layer2::Layer3::Layer4::Layer5::layer_5",
					.callback = []() { Layer1::Layer2::Layer3::Layer4::Layer5::layer_5(); }
				},
			}
		};

		execute_nanobenchmark(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}


namespace ExecutionWithinNestedTryCatchBlocks
{
	/*

	Conclusion:
	- Wrapping strategies
		- class methods
		- lambda functions

	Usage
	- Indiscriminate



	About
	- Timestamp Created
		- 8:27 AM, January 14, 2026

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |                1.94 |      515,508,984.62 |    0.5% |      0.24 | `try_catch | nested_try_catch_block | 1`
	|   101.4% |                1.91 |      522,555,446.13 |    0.1% |      0.23 | `try_catch | no_try_catch_block | 1`
	|   101.4% |                1.91 |      522,783,208.40 |    0.1% |      0.23 | `try_catch | with_try_catch_block | 1`

	|   100.0% |               17.48 |       57,222,083.35 |    0.3% |      0.21 | `try_catch | nested_try_catch_block | 10`
	|   100.0% |               17.47 |       57,226,584.62 |    0.3% |      0.21 | `try_catch | no_try_catch_block | 10`
	|   100.0% |               17.47 |       57,249,342.20 |    0.2% |      0.21 | `try_catch | with_try_catch_block | 10`

	|   100.0% |              173.80 |        5,753,826.47 |    0.2% |      0.21 | `try_catch | nested_try_catch_block | 100`
	|   100.0% |              173.74 |        5,755,611.27 |    0.1% |      0.21 | `try_catch | no_try_catch_block | 100`
	|   100.1% |              173.64 |        5,758,971.64 |    0.2% |      0.21 | `try_catch | with_try_catch_block | 100`

	|   100.0% |            1,679.36 |          595,463.74 |    0.1% |      0.20 | `try_catch | nested_try_catch_block | 1000`
	|   100.0% |            1,679.66 |          595,360.21 |    0.1% |      0.20 | `try_catch | no_try_catch_block | 1000`
	|    99.7% |            1,684.17 |          593,765.94 |    0.2% |      0.20 | `try_catch | with_try_catch_block | 1000`

	|   100.0% |           16,756.65 |           59,677.80 |    0.1% |      0.20 | `try_catch | nested_try_catch_block | 10000`
	|    99.9% |           16,769.24 |           59,632.98 |    0.2% |      0.20 | `try_catch | no_try_catch_block | 10000`
	|   100.0% |           16,750.04 |           59,701.34 |    0.1% |      0.20 | `try_catch | with_try_catch_block | 10000`

	|   100.0% |          167,407.62 |            5,973.44 |    0.1% |      0.20 | `try_catch | nested_try_catch_block | 100000`
	|   100.0% |          167,420.87 |            5,972.97 |    0.1% |      0.21 | `try_catch | no_try_catch_block | 100000`
	|    99.8% |          167,708.70 |            5,962.72 |    0.3% |      0.20 | `try_catch | with_try_catch_block | 100000`

	|   100.0% |        1,677,641.67 |              596.07 |    0.3% |      0.20 | `try_catch | nested_try_catch_block | 1000000`
	|   100.3% |        1,672,800.00 |              597.80 |    0.0% |      0.20 | `try_catch | no_try_catch_block | 1000000`
	|   100.2% |        1,674,318.18 |              597.26 |    0.2% |      0.20 | `try_catch | with_try_catch_block | 1000000`

	|   100.0% |       16,740,700.00 |               59.73 |    0.1% |      0.19 | `try_catch | nested_try_catch_block | 10000000`
	|   100.0% |       16,738,600.00 |               59.74 |    0.1% |      0.18 | `try_catch | no_try_catch_block | 10000000`
	|    99.7% |       16,787,400.00 |               59.57 |    0.3% |      0.19 | `try_catch | with_try_catch_block | 10000000`

	*/

	class Samples
	{
	public:
		double double_input_1 = 1;

		double double_output_1 = 1;

		static Samples instance;
	};

	Samples Samples::instance;

	void nested_try_catch_block()
	{
		try
		{
			try
			{
				try
				{
					try
					{
						try
						{
							try
							{
								try
								{
									try
									{
										try
										{
											try
											{
												Samples::instance.double_output_1 =
													Samples::instance.double_input_1 + Samples::instance.double_input_1;
											}
											catch (...)
											{

											}
										}
										catch (...)
										{

										}
									}
									catch (...)
									{

									}
								}
								catch (...)
								{

								}
							}
							catch (...)
							{

							}
						}
						catch (...)
						{

						}
					}
					catch (...)
					{

					}
				}
				catch (...)
				{

				}
			}
			catch (...)
			{

			}
		}
		catch (std::exception& exception)
		{
			Samples::instance.double_output_1 = 0.0;
		}
		catch (...)
		{

		}
	}

	void with_try_catch_block()
	{
		try
		{
			Samples::instance.double_output_1 =
				Samples::instance.double_input_1 + Samples::instance.double_input_1;
		}
		catch (std::exception& exception)
		{
			Samples::instance.double_output_1 = 0.0;
		}
		catch (...)
		{

		}
	}

	void no_try_catch_block()
	{
		Samples::instance.double_output_1 =
			Samples::instance.double_input_1 + Samples::instance.double_input_1;
	}

	void before_test_case_iteration_callback()
	{
		Samples::instance.double_output_1 = 0.0;
	}

	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "try_catch",
			.warmup_count = 2,
			.epoch_iteration_pairs =
			{
				{
					.epochs = 10'000'000,
					.iterations = 1
				},
				{
					.epochs = 1'000'000,
					.iterations = 10
				},
				{
					.epochs = 100'000,
					.iterations = 100
				},
				{
					.epochs = 10'000,
					.iterations = 1'000
				},
				{
					.epochs = 1'000,
					.iterations = 10'000
				},
				{
					.epochs = 100,
					.iterations = 100'000
				},
				{
					.epochs = 10,
					.iterations = 1'000'000
				},
				{
					.epochs = 1,
					.iterations = 10'000'000
				}
			},

			.test_cases =
			{
				{
					.name = "nested_try_catch_block",
					.callback = nested_try_catch_block
				},
				{
					.name = "no_try_catch_block",
					.callback = no_try_catch_block
				},
				{
					.name = "with_try_catch_block",
					.callback = with_try_catch_block
				}
			},

			.before_test_case_iteration_callback =
				before_test_case_iteration_callback
		};

		execute_nanobenchmark(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}





namespace LoopExecution
{
	/*

	Conclusion
	- use 'while' or 'for each' loops



	About
	- Timestamp Created
		- 8:31 AM, January 14, 2026

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |               55.34 |       18,069,653.81 |    0.2% |      6.70 | `loops | for_loop | 1`
	|   100.4% |               55.12 |       18,142,605.87 |    0.1% |      6.69 | `loops | while_loop | 1`
	|   100.4% |               55.12 |       18,142,872.07 |    0.1% |      6.69 | `loops | do_while_loop | 1`
	|   154.4% |               35.85 |       27,893,959.62 |    2.0% |      4.34 | `loops | ranged_based_for_loop | 1`
	|   153.4% |               36.08 |       27,716,970.40 |    0.8% |      4.39 | `loops | for_each__begin_and_end_collection_pointers | 1`
	|   143.4% |               38.58 |       25,917,977.10 |    0.1% |      4.67 | `loops | for_each__collection_reference | 1`

	|   100.0% |           54,588.35 |           18,318.93 |    0.0% |      6.61 | `loops | for_loop | 1000`
	|   100.0% |           54,596.26 |           18,316.27 |    0.0% |      6.61 | `loops | while_loop | 1000`
	|    99.7% |           54,769.54 |           18,258.32 |    0.1% |      6.63 | `loops | do_while_loop | 1000`
	|   155.4% |           35,132.08 |           28,464.01 |    0.1% |      4.26 | `loops | ranged_based_for_loop | 1000`
	|   155.1% |           35,190.82 |           28,416.50 |    0.2% |      4.27 | `loops | for_each__begin_and_end_collection_pointers | 1000`
	|   144.3% |           37,829.52 |           26,434.38 |    0.2% |      4.59 | `loops | for_each__collection_reference | 1000`

	|   100.0% |       54,620,825.00 |               18.31 |    0.1% |      6.67 | `loops | for_loop | 1000000`
	|   100.1% |       54,570,075.00 |               18.33 |    0.0% |      6.66 | `loops | while_loop | 1000000`
	|    99.7% |       54,783,280.00 |               18.25 |    0.1% |      6.72 | `loops | do_while_loop | 1000000`
	|   155.8% |       35,051,360.00 |               28.53 |    0.5% |      4.32 | `loops | ranged_based_for_loop | 1000000`
	|   154.5% |       35,358,536.36 |               28.28 |    0.4% |      4.33 | `loops | for_each__begin_and_end_collection_pointers | 1000000`
	|   144.3% |       37,864,816.67 |               26.41 |    0.2% |      4.63 | `loops | for_each__collection_reference | 1000000`
	*/

	class Samples
	{
	public:
		size_t index = 0;

		size_t size = 0;

		char output_value;

		std::string data = std::string(0, '0');

		static Samples instance;

		void for_loop()
		{
			for (index = 0; index < size; ++index)
			{
				output_value = data[index];
			}
		}

		void while_loop()
		{
			index = 0;
			while (index < size)
			{
				output_value = data[index];
				++index;
			}
		}

		void do_while_loop()
		{
			index = 0;
			do
			{
				output_value = data[index];
				++index;

			} while (index < size);
		}

		void ranged_based_for_loop()
		{
			for (const char& datum : data)
			{
				output_value = datum;
			}
		}

		void for_each__begin_and_end_collection_pointers()
		{
			std::ranges::for_each(
				data.begin(),
				data.end(),
				[this](const char datum)
				{
					output_value = datum;
				}
			);
		}

		void for_each__collection_reference()
		{
			std::ranges::for_each(
				data,
				[this](const char datum)
				{
					output_value = datum;
				}
			);
		}
	};

	Samples Samples::instance;

	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "loops",
			.warmup_count = 1,
			.epoch_iteration_pairs =
			{
				{
					.epochs = 10000000,
					.iterations = 1
				},
				{
					.epochs = 10000,
					.iterations = 1000
				},
				{
					.epochs = 10,
					.iterations = 1000000
				}
			},

			.test_cases =
			{
				{
					.name = "for_loop",
					.callback = []() { Samples::instance.for_loop(); }
				},
				{
					.name = "while_loop",
					.callback = []() { Samples::instance.while_loop(); }
				},
				{
					.name = "do_while_loop",
					.callback = []() { Samples::instance.do_while_loop(); }
				},
				{
					.name = "ranged_based_for_loop",
					.callback = []() { Samples::instance.ranged_based_for_loop(); }
				},
				{
					.name = "for_each__begin_and_end_collection_pointers",
					.callback = []() { Samples::instance.for_each__begin_and_end_collection_pointers(); }
				},
				{
					.name = "for_each__collection_reference",
					.callback = []() { Samples::instance.for_each__collection_reference(); }
				}
			}
		};

		execute_nanobenchmark(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}


namespace FileInputAndOutput
{
	/*

	Conclusion
	- file read operations
		fast_io
	- file write operations
		fstream
	- file append operations
		fstream


	About
	- Timestamp Created
		- 8:32 AM, January 14, 2026

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |            3,433.22 |          291,271.80 |   27.2% |      0.60 | :wavy_dash: `file_io | folly_file_write | 1` (Unstable with ~11,003.4 iters. Increase `minEpochIterations` to e.g. 110034)
	|    91.4% |            3,755.86 |          266,250.90 |    3.9% |      0.50 | `file_io | folly_file_append | 1`
	|   102.1% |            3,361.23 |          297,510.27 |    1.7% |      0.41 | `file_io | folly_file_read | 1`
	|    94.3% |            3,641.67 |          274,599.21 |   35.0% |      0.45 | :wavy_dash: `file_io | fast_io_file_write | 1` (Unstable with ~9,946.2 iters. Increase `minEpochIterations` to e.g. 99462)
	|    89.8% |            3,823.55 |          261,536.78 |   40.3% |      0.69 | :wavy_dash: `file_io | fast_io_file_append | 1` (Unstable with ~11,003.4 iters. Increase `minEpochIterations` to e.g. 110034)
	|95,908.1% |                3.58 |      279,353,340.15 |    6.4% |      0.01 | :wavy_dash: `file_io | fast_io_file_read | 1` (Unstable with ~290,823.2 iters. Increase `minEpochIterations` to e.g. 2908232)
	|    71.8% |            4,783.66 |          209,045.12 |   54.8% |      0.88 | :wavy_dash: `file_io | boost_file_write | 1` (Unstable with ~11,003.4 iters. Increase `minEpochIterations` to e.g. 110034)
	|    59.9% |            5,733.50 |          174,413.67 |    4.8% |      0.86 | `file_io | boost_file_append | 1`
	|    59.5% |            5,768.89 |          173,343.57 |    0.2% |      0.63 | `file_io | boost_file_read | 1`
	|   105.6% |            3,252.33 |          307,472.10 |   37.5% |      0.38 | :wavy_dash: `file_io | ofstream_file_write | 1` (Unstable with ~11,003.4 iters. Increase `minEpochIterations` to e.g. 110034)
	|    96.1% |            3,571.54 |          279,991.34 |   83.6% |      0.61 | :wavy_dash: `file_io | ofstream_file_append | 1` (Unstable with ~11,003.4 iters. Increase `minEpochIterations` to e.g. 110034)
	|16,229.0% |               21.15 |       47,270,537.53 |    2.8% |      0.01 | `file_io | ifstream_file_read | 1`
	|   120.1% |            2,859.78 |          349,677.32 |   77.1% |      0.54 | :wavy_dash: `file_io | fstream_file_write | 1` (Unstable with ~11,003.4 iters. Increase `minEpochIterations` to e.g. 110034)
	|    93.8% |            3,660.82 |          273,162.72 |   65.5% |      0.51 | :wavy_dash: `file_io | fstream_file_append | 1` (Unstable with ~11,003.4 iters. Increase `minEpochIterations` to e.g. 110034)
	|19,677.9% |               17.45 |       57,316,133.66 |    0.1% |      0.01 | `file_io | fstream_file_read | 1`

	*/

	inline static std::string file_input_1 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	inline static std::string file_output_1 = "";

	inline static std::string file_input_2 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	inline static std::string file_output_2 = "";

	inline static std::string file_path_1 = "output_1.txt";

	inline static std::string file_path_2 = "output_2.txt";

	inline static fast_io::native_file fast_io_write_file(file_path_1, fast_io::open_mode::out);

	inline static fast_io::native_file fast_io_append_file(file_path_1, fast_io::open_mode::app);

	inline static fast_io::native_file_loader fast_io_read_file(file_path_1);

	inline static std::ofstream ofstream_write_file(file_path_2, std::ios::out);

	inline static std::ofstream ofstream_append_file(file_path_2, std::ios::app);

	inline static std::ifstream ifstream_read_file(file_path_2, std::ios::in);

	inline static std::fstream fstream_write_file(file_path_2, std::ios::out);

	inline static std::fstream fstream_append_file(file_path_2, std::ios::app);

	inline static std::fstream fstream_read_file(file_path_2, std::ios::in);

	inline static folly::File folly_write_file(file_path_1, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	inline static folly::File folly_append_file(file_path_1, O_WRONLY | O_CREAT | O_APPEND, 0644);

	inline static folly::File folly_read_file(file_path_1, O_RDONLY);

	inline static boost::iostreams::stream<boost::iostreams::file_sink> boost_write_file(
		file_path_1,
		std::ios::trunc
	);

	inline static boost::iostreams::stream<boost::iostreams::file_sink> boost_append_file(
		file_path_1,
		std::ios::app
	);

	inline static boost::iostreams::stream<boost::iostreams::file_source> boost_read_file(
		file_path_1
	);

	void folly_file_write()
	{
		const char* buf = file_input_1.data();
		size_t remaining = file_input_1.size();
		while (remaining > 0)
		{
			int written = _write(folly_write_file.fd(), buf, static_cast<unsigned int>(remaining));
			if (written <= 0) break;
			remaining -= written;
			buf += written;
		}
	}

	void folly_file_append()
	{
		const char* buf = file_input_1.data();
		size_t remaining = file_input_1.size();
		while (remaining > 0)
		{
			int written = _write(folly_append_file.fd(), buf, static_cast<unsigned int>(remaining));
			if (written <= 0) break;
			remaining -= written;
			buf += written;
		}
	}

	void folly_file_read()
	{
		long size = _lseek(folly_read_file.fd(), 0, SEEK_END);
		_lseek(folly_read_file.fd(), 0, SEEK_SET);

		std::string buffer(size, '\0');
		char* buf = buffer.data();
		long remaining = size;

		while (remaining > 0)
		{
			int readBytes = _read(folly_read_file.fd(), buf, static_cast<unsigned int>(remaining));
			if (readBytes <= 0) break;
			remaining -= readBytes;
			buf += readBytes;
		}
	}

	void boost_file_write()
	{
		boost_write_file.write(file_input_1.data(), file_input_1.size());
		boost_write_file.flush();
	}

	void boost_file_append()
	{
		boost_append_file.write(file_input_1.data(), file_input_1.size());
		boost_append_file.flush();
	}

	void boost_file_read()
	{
		std::string output;

		boost_read_file.seekg(0, std::ios::end);
		output.resize(static_cast<size_t>(boost_read_file.tellg()));
		boost_read_file.seekg(0, std::ios::beg);
		boost_read_file.read(output.data(), output.size());
	}

	void fast_io_file_write()
	{
		fast_io::io::print(
			fast_io_write_file,
			file_input_1
		);

	}

	void fast_io_file_append()
	{
		fast_io::io::print(
			fast_io_append_file,
			file_input_1
		);
	}

	void fast_io_file_read()
	{
		std::string output
		{
			fast_io_read_file.begin(),
			fast_io_read_file.end()
		};
	}

	void ofstream_file_write()
	{
		ofstream_write_file << file_input_2;
	}

	void ofstream_file_append()
	{
		ofstream_append_file << file_input_2;
	}

	void ifstream_file_read()
	{
		ifstream_read_file >> file_output_2;
	}

	void fstream_file_write()
	{
		fstream_write_file << file_input_2;
	}

	void fstream_file_append()
	{
		fstream_append_file << file_input_2;
	}

	void fstream_file_read()
	{
		fstream_read_file >> file_output_2;
	}

	void before_test_case_iteration_callback()
	{
		file_output_1 = "";
		file_output_2 = "";

		std::ofstream ofstream_write_file_temp_1(file_path_1, std::ios::out);
		ofstream_write_file_temp_1 << "";

		std::ofstream ofstream_write_file_temp_2(file_path_2, std::ios::out);
		ofstream_write_file_temp_2 << "";
	}

	void after_test_case_iteration_callback()
	{
		file_output_1 = "";
		file_output_2 = "";

		std::ofstream ofstream_write_file_temp_1(file_path_1, std::ios::out);
		ofstream_write_file_temp_1 << "";

		std::ofstream ofstream_write_file_temp_2(file_path_2, std::ios::out);
		ofstream_write_file_temp_2 << "";
	}

	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "File I/O",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 10'000,
					.iterations = 1
				}

			},

			.test_cases =
			{
				{
					.name = "folly_file_write",
					.callback = folly_file_write
				},
				{
					.name = "folly_file_append",
					.callback = folly_file_append
				},
				{
					.name = "folly_file_read",
					.callback = folly_file_read,
					.before_test_callback = []()
					{
						std::ofstream ofstream_write_file_temp_1(file_path_1, std::ios::out);
						ofstream_write_file_temp_1 << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
					}
				},
				{
					.name = "fast_io_file_write",
					.callback = fast_io_file_write
				},
				{
					.name = "fast_io_file_append",
					.callback = fast_io_file_append
				},
				{
					.name = "fast_io_file_read",
					.callback = fast_io_file_read,
					.before_test_callback = []()
					{
						std::ofstream ofstream_write_file_temp_1(file_path_1, std::ios::out);
						ofstream_write_file_temp_1 << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
					}
				},
				{
					.name = "boost_file_write",
					.callback = boost_file_write
				},
				{
					.name = "boost_file_append",
					.callback = boost_file_append
				},
				{
					.name = "boost_file_read",
					.callback = boost_file_read,
					.before_test_callback = []()
					{
						std::ofstream ofstream_write_file_temp_1(file_path_1, std::ios::out);
						ofstream_write_file_temp_1 << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
					}
				},
				{
					.name = "ofstream_file_write",
					.callback = ofstream_file_write
				},
				{
					.name = "ofstream_file_append",
					.callback = ofstream_file_append
				},
				{
					.name = "ifstream_file_read",
					.callback = ifstream_file_read,
					.before_test_callback = []()
					{
						std::ofstream ofstream_write_file_temp_2(file_path_2, std::ios::out);
						ofstream_write_file_temp_2 << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
					}
				},
				{
					.name = "fstream_file_write",
					.callback = fstream_file_write
				},
				{
					.name = "fstream_file_append",
					.callback = fstream_file_append
				},
				{
					.name = "fstream_file_read",
					.callback = fstream_file_read,
					.before_test_callback = []()
					{
						std::ofstream ofstream_write_file_temp_2(file_path_2, std::ios::out);
						ofstream_write_file_temp_2 << "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
					}
				}
			},
			/*


			*/
		.before_test_case_iteration_callback =
			before_test_case_iteration_callback,

		.after_test_case_iteration_callback =
			after_test_case_iteration_callback
		};

		execute_nanobenchmark(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}


namespace RawOrInstanceOrStaticMethodSignaturesAndStringConcatenation
{
	/*

	Conclusion
	- instance variables will be prioritized
	- AVOID static-centric code design



	About
	- Timestamp Created
		- 8:31 AM, January 14, 2026

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |               61.14 |       16,356,382.11 |    0.2% |      0.75 | `object_instance_or_object_static | sum_raw_instance_1 | 1`
	|    39.6% |              154.54 |        6,470,887.54 |    1.0% |      1.90 | `object_instance_or_object_static | sum_raw_instance_2 | 1`
	|    53.6% |              114.03 |        8,769,907.16 |    0.1% |      1.38 | `object_instance_or_object_static | sum_raw_instance_3 | 1`
	|   103.7% |               58.98 |       16,955,423.22 |    0.1% |      0.71 | `object_instance_or_object_static | sum_raw_static_1 | 1`
	|    41.5% |              147.34 |        6,787,144.39 |    0.3% |      1.79 | `object_instance_or_object_static | sum_raw_static_2 | 1`
	|    55.1% |              111.02 |        9,007,455.84 |    0.1% |      1.35 | `object_instance_or_object_static | sum_raw_static_3 | 1`
	|   103.1% |               59.28 |       16,869,056.81 |    0.2% |      0.72 | `object_instance_or_object_static | sum_object_instance_1 | 1`
	|    40.4% |              151.27 |        6,610,493.74 |    0.1% |      1.83 | `object_instance_or_object_static | sum_object_instance_2 | 1`
	|    52.4% |              116.57 |        8,578,406.73 |    0.2% |      1.41 | `object_instance_or_object_static | sum_object_instance_3 | 1`
	|   102.2% |               59.84 |       16,712,132.05 |    0.2% |      0.72 | `object_instance_or_object_static | sum_object_static_1 | 1`
	|    40.4% |              151.37 |        6,606,282.66 |    0.2% |      1.83 | `object_instance_or_object_static | sum_object_static_2 | 1`
	|    53.3% |              114.74 |        8,715,618.58 |    0.5% |      1.40 | `object_instance_or_object_static | sum_object_static_3 | 1`

	|   100.0% |              642.26 |        1,556,998.28 |    0.9% |      0.71 | `object_instance_or_object_static | sum_raw_instance_1 | 10`
	|    42.6% |            1,508.37 |          662,966.11 |    0.6% |      1.83 | `object_instance_or_object_static | sum_raw_instance_2 | 10`
	|    57.4% |            1,118.62 |          893,959.01 |    0.3% |      1.36 | `object_instance_or_object_static | sum_raw_instance_3 | 10`
	|   108.3% |              592.99 |        1,686,375.96 |    0.1% |      0.72 | `object_instance_or_object_static | sum_raw_static_1 | 10`
	|    43.7% |            1,469.60 |          680,456.18 |    0.2% |      1.78 | `object_instance_or_object_static | sum_raw_static_2 | 10`
	|    57.1% |            1,125.77 |          888,277.56 |    0.1% |      1.36 | `object_instance_or_object_static | sum_raw_static_3 | 10`
	|   108.1% |              594.23 |        1,682,851.39 |    0.1% |      0.72 | `object_instance_or_object_static | sum_object_instance_1 | 10`
	|    42.5% |            1,511.10 |          661,769.75 |    0.2% |      1.83 | `object_instance_or_object_static | sum_object_instance_2 | 10`
	|    55.9% |            1,148.45 |          870,739.32 |    0.1% |      1.39 | `object_instance_or_object_static | sum_object_instance_3 | 10`
	|   107.4% |              598.22 |        1,671,638.77 |    0.1% |      0.72 | `object_instance_or_object_static | sum_object_static_1 | 10`
	|    42.7% |            1,505.86 |          664,072.63 |    0.2% |      1.83 | `object_instance_or_object_static | sum_object_static_2 | 10`
	|    56.7% |            1,132.58 |          882,938.76 |    0.1% |      1.37 | `object_instance_or_object_static | sum_object_static_3 | 10`

	|   100.0% |            5,981.55 |          167,180.68 |    0.2% |      0.73 | `object_instance_or_object_static | sum_raw_instance_1 | 100`
	|    39.5% |           15,156.40 |           65,978.72 |    0.3% |      1.83 | `object_instance_or_object_static | sum_raw_instance_2 | 100`
	|    51.9% |           11,530.73 |           86,724.75 |    0.1% |      1.40 | `object_instance_or_object_static | sum_raw_instance_3 | 100`
	|   101.2% |            5,910.28 |          169,196.75 |    0.3% |      0.72 | `object_instance_or_object_static | sum_raw_static_1 | 100`
	|    41.4% |           14,433.49 |           69,283.33 |    0.1% |      1.75 | `object_instance_or_object_static | sum_raw_static_2 | 100`
	|    53.5% |           11,173.77 |           89,495.32 |    0.2% |      1.35 | `object_instance_or_object_static | sum_raw_static_3 | 100`
	|   101.2% |            5,911.36 |          169,165.92 |    0.4% |      0.72 | `object_instance_or_object_static | sum_object_instance_1 | 100`
	|    39.5% |           15,147.29 |           66,018.40 |    0.1% |      1.83 | `object_instance_or_object_static | sum_object_instance_2 | 100`
	|    51.4% |           11,633.48 |           85,958.83 |    0.1% |      1.41 | `object_instance_or_object_static | sum_object_instance_3 | 100`
	|   100.4% |            5,959.44 |          167,800.88 |    0.4% |      0.72 | `object_instance_or_object_static | sum_object_static_1 | 100`
	|    39.8% |           15,040.25 |           66,488.26 |    0.1% |      1.82 | `object_instance_or_object_static | sum_object_static_2 | 100`
	|    53.6% |           11,157.64 |           89,624.72 |    0.2% |      1.35 | `object_instance_or_object_static | sum_object_static_3 | 100`

	|   100.0% |           61,461.58 |           16,270.33 |    0.2% |      0.74 | `object_instance_or_object_static | sum_raw_instance_1 | 1000`
	|    40.3% |          152,402.19 |            6,561.59 |    0.1% |      1.84 | `object_instance_or_object_static | sum_raw_instance_2 | 1000`
	|    53.0% |          115,876.94 |            8,629.84 |    0.1% |      1.40 | `object_instance_or_object_static | sum_raw_instance_3 | 1000`
	|   103.9% |           59,171.01 |           16,900.17 |    0.3% |      0.72 | `object_instance_or_object_static | sum_raw_static_1 | 1000`
	|    41.7% |          147,218.60 |            6,792.62 |    0.2% |      1.78 | `object_instance_or_object_static | sum_raw_static_2 | 1000`
	|    54.0% |          113,813.24 |            8,786.32 |    0.1% |      1.38 | `object_instance_or_object_static | sum_raw_static_3 | 1000`
	|   104.4% |           58,886.25 |           16,981.89 |    0.1% |      0.71 | `object_instance_or_object_static | sum_object_instance_1 | 1000`
	|    41.3% |          148,980.96 |            6,712.27 |    0.2% |      1.80 | `object_instance_or_object_static | sum_object_instance_2 | 1000`
	|    53.6% |          114,643.41 |            8,722.70 |    0.1% |      1.39 | `object_instance_or_object_static | sum_object_instance_3 | 1000`
	|   103.7% |           59,285.32 |           16,867.58 |    0.1% |      0.72 | `object_instance_or_object_static | sum_object_static_1 | 1000`
	|    40.4% |          152,102.15 |            6,574.53 |    0.2% |      1.84 | `object_instance_or_object_static | sum_object_static_2 | 1000`
	|    53.5% |          114,794.44 |            8,711.22 |    0.0% |      1.39 | `object_instance_or_object_static | sum_object_static_3 | 1000`

	|   100.0% |       61,237,900.00 |               16.33 |    0.6% |      0.68 | `object_instance_or_object_static | sum_raw_instance_1 | 1000000`
	|    40.4% |      151,577,200.00 |                6.60 |    0.1% |      1.67 | `object_instance_or_object_static | sum_raw_instance_2 | 1000000`
	|    53.1% |      115,399,200.00 |                8.67 |    0.1% |      1.27 | `object_instance_or_object_static | sum_raw_instance_3 | 1000000`
	|   105.6% |       57,995,500.00 |               17.24 |    0.2% |      0.64 | `object_instance_or_object_static | sum_raw_static_1 | 1000000`
	|    41.6% |      147,160,700.00 |                6.80 |    0.3% |      1.62 | `object_instance_or_object_static | sum_raw_static_2 | 1000000`
	|    54.0% |      113,486,600.00 |                8.81 |    0.2% |      1.25 | `object_instance_or_object_static | sum_raw_static_3 | 1000000`
	|   102.3% |       59,868,700.00 |               16.70 |    0.1% |      0.66 | `object_instance_or_object_static | sum_object_instance_1 | 1000000`
	|    40.7% |      150,534,700.00 |                6.64 |    0.0% |      1.65 | `object_instance_or_object_static | sum_object_instance_2 | 1000000`
	|    53.1% |      115,429,200.00 |                8.66 |    0.1% |      1.27 | `object_instance_or_object_static | sum_object_instance_3 | 1000000`
	|   101.8% |       60,131,700.00 |               16.63 |    0.1% |      0.66 | `object_instance_or_object_static | sum_object_static_1 | 1000000`
	|    39.9% |      153,444,900.00 |                6.52 |    0.2% |      1.69 | `object_instance_or_object_static | sum_object_static_2 | 1000000`
	|    56.3% |      108,823,900.00 |                9.19 |    0.2% |      1.20 | `object_instance_or_object_static | sum_object_static_3 | 1000000`

	*/

	std::string raw_output_1 = "0";

	std::string raw_input_1 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	std::string raw_input_2 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	void sum_raw_instance_1()
	{
		raw_output_1 =
			raw_input_1 +
			raw_input_2;
	}

	std::string sum_raw_output_1 = "0";

	void sum_raw_instance_2_func(
		const std::string& input_1,
		const std::string& input_2
	)
	{
		sum_raw_output_1 =
			input_1 + input_2;
	}

	void sum_raw_instance_2()
	{
		sum_raw_instance_2_func(
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		);
	}

	std::string sum_raw_instance_3_func()
	{
		raw_output_1 =
			raw_input_1 +
			raw_input_2;

		return raw_output_1;
	}

	void sum_raw_instance_3()
	{
		sum_raw_instance_3_func();
	}

	inline static std::string sum_raw_static_1_output = "0";

	inline static std::string sum_raw_static_1_input_1 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	inline static std::string sum_raw_static_1_input_2 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	void sum_raw_static_1()
	{
		sum_raw_static_1_output =
			sum_raw_static_1_input_1 +
			sum_raw_static_1_input_2;
	}

	inline static std::string sum_raw_static_2_output = "0";

	void sum_raw_static_2_func(
		const std::string& input_1,
		const std::string& input_2
	)
	{
		sum_raw_static_2_output =
			input_1 + input_2;
	}

	void sum_raw_static_2()
	{
		sum_raw_static_2_func(
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		);
	}

	std::string sum_raw_static_3_func()
	{
		sum_raw_static_1_output =
			sum_raw_static_1_input_1 +
			sum_raw_static_1_input_2;

		return sum_raw_static_1_output;
	}

	void sum_raw_static_3()
	{
		sum_raw_static_3_func();
	}

	class Instance
	{
	public:
		std::string sum_object_instance_1_output = "0";

		std::string sum_object_instance_1_input_1 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

		std::string sum_object_instance_1_input_2 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

		void sum_object_instance_1()
		{
			sum_object_instance_1_output =
				sum_object_instance_1_input_1 +
				sum_object_instance_1_input_2;
		}

		std::string sum_object_instance_2_output = "0";

		void sum_object_instance_2(
			const std::string& input_1,
			const std::string& input_2
		)
		{
			sum_object_instance_2_output =
				input_1 + input_2;
		}

		std::string sum_object_instance_3_func()
		{
			sum_object_instance_1_output =
				sum_object_instance_1_input_1 +
				sum_object_instance_1_input_2;

			return sum_object_instance_1_output;
		}

		void sum_object_instance_3()
		{
			sum_object_instance_3_func();
		}

		inline static std::string sum_object_static_1_output = "0";

		inline static std::string sum_object_static_1_input_1 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

		inline static std::string sum_object_static_1_input_2 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

		inline static void sum_object_static_1()
		{
			sum_object_static_1_output =
				sum_object_static_1_input_1 +
				sum_object_static_1_input_2;
		}

		inline static std::string sum_object_static_2_output = "0";

		inline static void sum_object_static_2(
			const std::string& input_1,
			const std::string& input_2
		)
		{
			sum_object_static_2_output =
				input_1 + input_2;
		}

		inline static std::string sum_object_static_3_func()
		{
			sum_object_static_1_output =
				sum_object_static_1_input_1 +
				sum_object_static_1_input_2;

			return sum_object_static_1_output;
		}

		inline static void sum_object_static_3()
		{
			sum_object_static_3_func();
		}
	};

	Instance object;

	void sum_object_instance_1()
	{
		object.sum_object_instance_1();
	}

	void sum_object_instance_2()
	{
		object.sum_object_instance_2(
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		);
	}

	void sum_object_instance_3()
	{
		object.sum_object_instance_3();
	}

	void sum_object_static_1()
	{
		Instance::sum_object_static_1();
	}

	void sum_object_static_2()
	{
		Instance::sum_object_static_2(
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		);
	}

	void sum_object_static_3()
	{
		Instance::sum_object_static_3();
	}

	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "object_instance_or_object_static",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 1'000'000,
					.iterations = 1
				},
				{
					.epochs = 100'000,
					.iterations = 10
				},
				{
					.epochs = 10'000,
					.iterations = 100
				},
				{
					.epochs = 1'000,
					.iterations = 1'000
				},
				{
					.epochs = 1,
					.iterations = 1'000'000
				}
			},

			.test_cases =
			{
				{
					.name = "sum_raw_instance_1",
					.callback = sum_raw_instance_1
				},
				{
					.name = "sum_raw_instance_2",
					.callback = sum_raw_instance_2
				},
				{
					.name = "sum_raw_instance_3",
					.callback = sum_raw_instance_3
				},
				{
					.name = "sum_raw_static_1",
					.callback = sum_raw_static_1
				},
				{
					.name = "sum_raw_static_2",
					.callback = sum_raw_static_2
				},
				{
					.name = "sum_raw_static_3",
					.callback = sum_raw_static_3
				},
				{
					.name = "sum_object_instance_1",
					.callback = sum_object_instance_1
				},
				{
					.name = "sum_object_instance_2",
					.callback = sum_object_instance_2
				},
				{
					.name = "sum_object_instance_3",
					.callback = sum_object_instance_3
				},
				{
					.name = "sum_object_static_1",
					.callback = sum_object_static_1
				},
				{
					.name = "sum_object_static_2",
					.callback = sum_object_static_2
				},
				{
					.name = "sum_object_static_3",
					.callback = sum_object_static_3
				}
			}
		};

		execute_nanobenchmark(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}


namespace AsynchronousHandling
{
	/*

	Conclusions
	- strategies
		- priority option
			- folly::MicroSpinLock
		- secondary option
			- boost::mutex
		- legacy option
			- std::mutex


	About
	- Timestamp Created
		- 8:33 AM, January 14, 2026

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |               18.36 |       54,471,079.26 |    1.4% |      0.23 | `Asynchronous Handling | instance__synchronous__without_boost_mutex_lock | 1`
	|    63.6% |               28.85 |       34,658,851.47 |    0.1% |      0.35 | `Asynchronous Handling | instance__synchronous__with_boost_mutex_lock | 1`
	|   224.8% |                8.17 |      122,435,881.59 |    0.4% |      0.09 | `Asynchronous Handling | instance__asynchronous__folly_micro_spin_lock | 1`
	|    75.5% |               24.31 |       41,137,931.17 |    0.4% |      0.29 | `Asynchronous Handling | instance__asynchronous__folly_micro_spin_lock__map | 1`
	|   121.6% |               15.09 |       66,261,502.07 |    0.2% |      0.18 | `Asynchronous Handling | instance__asynchronous__std_unique_lock__allocated | 1`
	|   162.8% |               11.28 |       88,684,517.05 |    0.2% |      0.14 | `Asynchronous Handling | instance__asynchronous__boost_unique_lock__allocated | 1`
	| 1,537.8% |                1.19 |      837,647,375.30 |    0.0% |      0.01 | `Asynchronous Handling | instance__asynchronous__boost_unique_lock__unallocated | 1`
	|   101.6% |               18.07 |       55,337,599.23 |    0.6% |      0.22 | `Asynchronous Handling | static__synchronous__without_boost_mutex_lock | 1`
	|    71.7% |               25.61 |       39,054,532.67 |    0.2% |      0.31 | `Asynchronous Handling | static__synchronous__with_boost_mutex_lock | 1`
	|   284.2% |                6.46 |      154,794,510.68 |    0.2% |      0.08 | `Asynchronous Handling | static__asynchronous__folly_micro_spin_lock | 1`
	|    75.0% |               24.48 |       40,846,566.27 |    0.3% |      0.30 | `Asynchronous Handling | static__asynchronous__folly_micro_spin_lock__map | 1`
	|   120.1% |               15.29 |       65,393,304.01 |    0.3% |      0.19 | `Asynchronous Handling | static__asynchronous__std_unique_lock__allocated | 1`
	|   161.4% |               11.38 |       87,901,505.62 |    0.4% |      0.14 | `Asynchronous Handling | static__asynchronous__boost_unique_lock__allocated | 1`
	| 1,523.4% |                1.21 |      829,824,764.55 |    0.9% |      0.01 | `Asynchronous Handling | static__asynchronous__boost_unique_lock__unallocated | 1`

	|   100.0% |           18,351.18 |           54,492.41 |    0.8% |      0.22 | `Asynchronous Handling | instance__synchronous__without_boost_mutex_lock | 1000`
	|    63.3% |           28,992.30 |           34,491.92 |    0.2% |      0.35 | `Asynchronous Handling | instance__synchronous__with_boost_mutex_lock | 1000`
	|   223.6% |            8,206.05 |          121,861.24 |    0.2% |      0.09 | `Asynchronous Handling | instance__asynchronous__folly_micro_spin_lock | 1000`
	|    76.9% |           23,864.01 |           41,904.11 |    0.7% |      0.29 | `Asynchronous Handling | instance__asynchronous__folly_micro_spin_lock__map | 1000`
	|   121.3% |           15,123.85 |           66,120.73 |    0.2% |      0.18 | `Asynchronous Handling | instance__asynchronous__std_unique_lock__allocated | 1000`
	|   163.2% |           11,242.06 |           88,951.64 |    0.2% |      0.14 | `Asynchronous Handling | instance__asynchronous__boost_unique_lock__allocated | 1000`
	| 1,526.6% |            1,202.09 |          831,887.83 |    0.1% |      0.01 | `Asynchronous Handling | instance__asynchronous__boost_unique_lock__unallocated | 1000`
	|   101.3% |           18,116.28 |           55,198.97 |    0.6% |      0.22 | `Asynchronous Handling | static__synchronous__without_boost_mutex_lock | 1000`
	|    71.5% |           25,650.54 |           38,985.53 |    0.1% |      0.31 | `Asynchronous Handling | static__synchronous__with_boost_mutex_lock | 1000`
	|   284.6% |            6,447.18 |          155,106.60 |    0.0% |      0.08 | `Asynchronous Handling | static__asynchronous__folly_micro_spin_lock | 1000`
	|    76.2% |           24,073.64 |           41,539.20 |    0.4% |      0.29 | `Asynchronous Handling | static__asynchronous__folly_micro_spin_lock__map | 1000`
	|   121.6% |           15,094.77 |           66,248.12 |    0.2% |      0.18 | `Asynchronous Handling | static__asynchronous__std_unique_lock__allocated | 1000`
	|   162.6% |           11,284.67 |           88,615.81 |    0.3% |      0.14 | `Asynchronous Handling | static__asynchronous__boost_unique_lock__allocated | 1000`
	| 1,529.4% |            1,199.91 |          833,393.67 |    0.1% |      0.02 | `Asynchronous Handling | static__asynchronous__boost_unique_lock__unallocated | 1000`

	|   100.0% |       18,224,100.00 |               54.87 |    0.3% |      0.20 | `Asynchronous Handling | instance__synchronous__without_boost_mutex_lock | 1000000`
	|    63.2% |       28,814,800.00 |               34.70 |    0.2% |      0.32 | `Asynchronous Handling | instance__synchronous__with_boost_mutex_lock | 1000000`
	|   224.4% |        8,120,400.00 |              123.15 |    0.0% |      0.09 | `Asynchronous Handling | instance__asynchronous__folly_micro_spin_lock | 1000000`
	|    75.7% |       24,062,600.00 |               41.56 |    0.4% |      0.27 | `Asynchronous Handling | instance__asynchronous__folly_micro_spin_lock__map | 1000000`
	|   118.8% |       15,345,500.00 |               65.17 |    1.7% |      0.17 | `Asynchronous Handling | instance__asynchronous__std_unique_lock__allocated | 1000000`
	|   162.1% |       11,239,400.00 |               88.97 |    0.0% |      0.12 | `Asynchronous Handling | instance__asynchronous__boost_unique_lock__allocated | 1000000`
	| 1,525.9% |        1,194,300.00 |              837.31 |    0.1% |      0.01 | `Asynchronous Handling | instance__asynchronous__boost_unique_lock__unallocated | 1000000`
	|   101.0% |       18,050,200.00 |               55.40 |    0.3% |      0.20 | `Asynchronous Handling | static__synchronous__without_boost_mutex_lock | 1000000`
	|    71.2% |       25,591,400.00 |               39.08 |    0.2% |      0.28 | `Asynchronous Handling | static__synchronous__with_boost_mutex_lock | 1000000`
	|   282.7% |        6,446,100.00 |              155.13 |    0.0% |      0.07 | `Asynchronous Handling | static__asynchronous__folly_micro_spin_lock | 1000000`
	|    78.4% |       23,241,800.00 |               43.03 |    0.4% |      0.26 | `Asynchronous Handling | static__asynchronous__folly_micro_spin_lock__map | 1000000`
	|   121.0% |       15,063,700.00 |               66.38 |    0.1% |      0.17 | `Asynchronous Handling | static__asynchronous__std_unique_lock__allocated | 1000000`
	|   162.0% |       11,246,000.00 |               88.92 |    0.1% |      0.12 | `Asynchronous Handling | static__asynchronous__boost_unique_lock__allocated | 1000000`
	| 1,523.8% |        1,196,000.00 |              836.12 |    0.0% |      0.01 | `Asynchronous Handling | static__asynchronous__boost_unique_lock__unallocated | 1000000`

	*/

	class InstanceCollections
	{
	public:
		folly::MicroSpinLock micro_spin_lock;

		std::mutex std_mutex;

		boost::mutex boost_mutex;

		std::unordered_map<std::string, folly::MicroSpinLock>
			folly_micro_spin_lock_collection;

		std::string z;

		std::string string_1(std::string x, std::string y)
		{
			return x + y;
		}

		void string_2(std::string x, std::string y)
		{
			boost::unique_lock<boost::mutex> lock(boost_mutex);

			z = x + y;
		}

		void instance__synchronous__without_boost_mutex_lock()
		{
			string_1("a", "b");
		}

		void instance__synchronous__with_boost_mutex_lock()
		{
			string_2("a", "b");
		}

		void instance__asynchronous__folly_micro_spin_lock()
		{
			micro_spin_lock.lock();
			micro_spin_lock.unlock();
		}

		void instance__asynchronous__folly_micro_spin_lock__map()
		{
			folly_micro_spin_lock_collection["instance"].lock();
			folly_micro_spin_lock_collection["instance"].unlock();
		}

		void instance__asynchronous__std_unique_lock__allocated()
		{
			std::unique_lock<std::mutex> lock(std_mutex);
		}

		void instance__asynchronous__boost_unique_lock__allocated()
		{
			boost::unique_lock<boost::mutex> lock(boost_mutex);
		}

		void instance__asynchronous__boost_unique_lock__unallocated()
		{
			boost::unique_lock<boost::mutex> lock;
		}

	};

	class StaticCollections
	{
	public:
		inline static folly::MicroSpinLock micro_spin_lock;

		inline static std::mutex std_mutex;

		inline static boost::mutex boost_mutex;

		inline static std::unordered_map<std::string, folly::MicroSpinLock>
			folly_micro_spin_lock_collection;


		inline static std::string z;

		static std::string string_1(std::string x, std::string y)
		{
			return x + y;
		}

		static void string_2(std::string x, std::string y)
		{
			boost::unique_lock<boost::mutex> lock(boost_mutex);

			z = x + y;
		}

		static void static__synchronous__without_boost_mutex_lock()
		{
			string_1("a", "b");
		}

		static void static__synchronous__with_boost_mutex_lock()
		{
			string_2("a", "b");
		}

		static void static__asynchronous__folly_micro_spin_lock()
		{
			micro_spin_lock.lock();
			micro_spin_lock.unlock();
		}

		static void static__asynchronous__folly_micro_spin_lock__map()
		{
			folly_micro_spin_lock_collection["instance"].lock();
			folly_micro_spin_lock_collection["instance"].unlock();
		}

		static void static__asynchronous__std_unique_lock__allocated()
		{
			std::unique_lock<std::mutex> lock(std_mutex);
		}

		static void static__asynchronous__boost_unique_lock__allocated()
		{
			boost::unique_lock<boost::mutex> lock(boost_mutex);
		}

		static void static__asynchronous__boost_unique_lock__unallocated()
		{
			boost::unique_lock<boost::mutex> lock;
		}
	};

	inline static InstanceCollections singleton;



	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "Asynchronous Handling",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 1000000,
					.iterations = 1
				},
				{
					.epochs = 1000,
					.iterations = 1000
				},
				{
					.epochs = 1,
					.iterations = 1000000
				}
			},

			.test_cases =
			{
				{
					.name = "instance__synchronous__without_boost_mutex_lock",
					.callback = []() { singleton.instance__synchronous__without_boost_mutex_lock(); }
				},
				{
					.name = "instance__synchronous__with_boost_mutex_lock",
					.callback = []() { singleton.instance__synchronous__with_boost_mutex_lock(); }
				},
				{
					.name = "instance__asynchronous__folly_micro_spin_lock",
					.callback = []() { singleton.instance__asynchronous__folly_micro_spin_lock(); }
				},
				{
					.name = "instance__asynchronous__folly_micro_spin_lock__map",
					.callback = []() { singleton.instance__asynchronous__folly_micro_spin_lock__map(); }
				},
				{
					.name = "instance__asynchronous__std_unique_lock__allocated",
					.callback = []() { singleton.instance__asynchronous__std_unique_lock__allocated(); }
				},
				{
					.name = "instance__asynchronous__boost_unique_lock__allocated",
					.callback = []() { singleton.instance__asynchronous__boost_unique_lock__allocated(); }
				},
				{
					.name = "instance__asynchronous__boost_unique_lock__unallocated",
					.callback = []() { singleton.instance__asynchronous__boost_unique_lock__unallocated(); }
				},
				{
					.name = "static__synchronous__without_boost_mutex_lock",
					.callback = []() { StaticCollections::static__synchronous__without_boost_mutex_lock(); }
				},
				{
					.name = "static__synchronous__with_boost_mutex_lock",
					.callback = []() { StaticCollections::static__synchronous__with_boost_mutex_lock(); }
				},
				{
					.name = "static__asynchronous__folly_micro_spin_lock",
					.callback = []() { StaticCollections::static__asynchronous__folly_micro_spin_lock(); }
				},
				{
					.name = "static__asynchronous__folly_micro_spin_lock__map",
					.callback = []() { StaticCollections::static__asynchronous__folly_micro_spin_lock__map(); }
				},
				{
					.name = "static__asynchronous__std_unique_lock__allocated",
					.callback = []() { StaticCollections::static__asynchronous__std_unique_lock__allocated(); }
				},
				{
					.name = "static__asynchronous__boost_unique_lock__allocated",
					.callback = []() { StaticCollections::static__asynchronous__boost_unique_lock__allocated(); }
				},
				{
					.name = "static__asynchronous__boost_unique_lock__unallocated",
					.callback = []() { StaticCollections::static__asynchronous__boost_unique_lock__unallocated(); }
				},

			}
		};

		execute_nanobenchmark(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}


namespace StaticValues
{
	/*

	Conclusion
	- use class statics

	NOTE
	- pure statics are unique, per file. They DO NOT represent a reliable true global state.



	About
	- Timestamp Created
		- 8:33 AM, January 14, 2026

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |                9.80 |      102,018,594.06 |    2.2% |      1.19 | `pure_static_vs_struct_static_vs_class_static | extern_static_string | 1`
	|   104.6% |                9.37 |      106,747,586.38 |    0.2% |      1.14 | `pure_static_vs_struct_static_vs_class_static | struct_static_string | 1`
	|   103.5% |                9.47 |      105,625,306.88 |    0.3% |      1.14 | `pure_static_vs_struct_static_vs_class_static | class_static_string | 1`
	|   120.4% |                8.14 |      122,815,895.70 |    0.2% |      0.99 | `pure_static_vs_struct_static_vs_class_static | pure_namespace_static_string | 1`
	|   117.7% |                8.33 |      120,108,904.26 |    0.2% |      1.01 | `pure_static_vs_struct_static_vs_class_static | pure_static_string | 1`

	|   100.0% |               92.46 |       10,815,100.85 |    0.3% |      1.12 | `pure_static_vs_struct_static_vs_class_static | extern_static_string | 10`
	|   101.6% |               91.02 |       10,986,279.03 |    0.2% |      1.10 | `pure_static_vs_struct_static_vs_class_static | struct_static_string | 10`
	|   100.2% |               92.30 |       10,834,745.82 |    0.2% |      1.12 | `pure_static_vs_struct_static_vs_class_static | class_static_string | 10`
	|   116.8% |               79.13 |       12,636,892.99 |    0.0% |      0.96 | `pure_static_vs_struct_static_vs_class_static | pure_namespace_static_string | 10`
	|   115.7% |               79.89 |       12,516,887.45 |    0.1% |      0.97 | `pure_static_vs_struct_static_vs_class_static | pure_static_string | 10`

	|   100.0% |              924.99 |        1,081,087.33 |    0.1% |      1.12 | `pure_static_vs_struct_static_vs_class_static | extern_static_string | 100`
	|   102.7% |              900.46 |        1,110,546.34 |    0.1% |      1.09 | `pure_static_vs_struct_static_vs_class_static | struct_static_string | 100`
	|   100.1% |              924.38 |        1,081,805.03 |    0.0% |      1.12 | `pure_static_vs_struct_static_vs_class_static | class_static_string | 100`
	|   117.0% |              790.64 |        1,264,801.81 |    0.1% |      0.96 | `pure_static_vs_struct_static_vs_class_static | pure_namespace_static_string | 100`
	|   115.4% |              801.70 |        1,247,345.64 |    0.1% |      0.97 | `pure_static_vs_struct_static_vs_class_static | pure_static_string | 100`

	|   100.0% |            9,101.99 |          109,866.14 |    0.0% |      1.10 | `pure_static_vs_struct_static_vs_class_static | extern_static_string | 1000`
	|   102.7% |            8,864.54 |          112,809.06 |    0.1% |      1.07 | `pure_static_vs_struct_static_vs_class_static | struct_static_string | 1000`
	|    99.9% |            9,108.35 |          109,789.32 |    0.1% |      1.10 | `pure_static_vs_struct_static_vs_class_static | class_static_string | 1000`
	|   115.4% |            7,889.46 |          126,751.44 |    0.1% |      0.96 | `pure_static_vs_struct_static_vs_class_static | pure_namespace_static_string | 1000`
	|   115.2% |            7,899.48 |          126,590.66 |    0.0% |      0.96 | `pure_static_vs_struct_static_vs_class_static | pure_static_string | 1000`

	|   100.0% |        9,227,100.00 |              108.38 |    0.7% |      0.10 | `pure_static_vs_struct_static_vs_class_static | extern_static_string | 1000000`
	|   101.3% |        9,105,700.00 |              109.82 |    0.8% |      0.10 | `pure_static_vs_struct_static_vs_class_static | struct_static_string | 1000000`
	|    99.4% |        9,287,100.00 |              107.68 |    0.5% |      0.10 | `pure_static_vs_struct_static_vs_class_static | class_static_string | 1000000`
	|   117.1% |        7,878,600.00 |              126.93 |    0.0% |      0.09 | `pure_static_vs_struct_static_vs_class_static | pure_namespace_static_string | 1000000`
	|   115.0% |        8,021,900.00 |              124.66 |    1.1% |      0.09 | `pure_static_vs_struct_static_vs_class_static | pure_static_string | 1000000`

	*/

	/*
	static std::string benchmark_value = "0";

	namespace Cache
	{
		static std::string pure_static_string_input_value = benchmark_value;

		static std::string pure_static_string_output_value = "";

		struct StructStringSample
		{
			inline static std::string struct_static_string_input_value = benchmark_value;

			inline static std::string struct_static_string_output_value = "";
		};

		class ClassStringSample
		{
		public:
			inline static std::string class_static_string_input_value = benchmark_value;

			inline static std::string class_static_string_output_value = "";
		};
	};

	extern std::string extern_static_string_input_value;

	extern std::string extern_static_string_output_value;

	static std::string pure_static_string_input_value = benchmark_value;

	static std::string pure_static_string_output_value = "";

	struct StructStringSample
	{
		inline static std::string struct_static_string_input_value = benchmark_value;

		inline static std::string struct_static_string_output_value = "";
	};

	class ClassStringSample
	{
	public:
		inline static std::string class_static_string_input_value = benchmark_value;

		inline static std::string class_static_string_output_value = "";
	};

	void extern_static_string()
	{
		extern_static_string_output_value =
			extern_static_string_input_value +
			extern_static_string_input_value;
	}

	void pure_namespace_static_string()
	{
		Cache::pure_static_string_output_value =
			Cache::pure_static_string_input_value +
			Cache::pure_static_string_input_value;
	}

	void pure_static_string()
	{
		pure_static_string_output_value =
			pure_static_string_input_value +
			pure_static_string_input_value;
	}

	void struct_static_string()
	{
		StructStringSample::struct_static_string_output_value =
			StructStringSample::struct_static_string_input_value +
			StructStringSample::struct_static_string_input_value;
	}

	void class_static_string()
	{
		ClassStringSample::class_static_string_output_value =
			ClassStringSample::class_static_string_input_value +
			ClassStringSample::class_static_string_input_value;
	}

	static std::string pure_static_double_input_value = benchmark_value;

	static std::string pure_double_output_value = "";

	struct StructDoubleSample
	{
		inline static std::string struct_static_double_input_value = benchmark_value;

		inline static std::string struct_double_output_value = "";
	};

	class ClassDoubleSample
	{
	public:
		inline static std::string class_static_double_input_value = benchmark_value;

		inline static std::string class_double_output_value = "";
	};

	void pure_static_double()
	{
		pure_double_output_value =
			pure_static_double_input_value +
			pure_static_double_input_value;
	}

	void struct_static_double()
	{
		StructDoubleSample::struct_double_output_value =
			StructDoubleSample::struct_static_double_input_value +
			StructDoubleSample::struct_static_double_input_value;
	}

	void class_static_double()
	{
		ClassDoubleSample::class_double_output_value =
			ClassDoubleSample::class_static_double_input_value +
			ClassDoubleSample::class_static_double_input_value;
	}


	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite_1
		{
			.name = "pure_static_vs_struct_static_vs_class_static",
			.warmup_count = 2,
			.epoch_iteration_pairs =
			{
				{
					.epochs = 10'000'000,
					.iterations = 1
				},
				{
					.epochs = 1'000'000,
					.iterations = 10
				},
				{
					.epochs = 100'000,
					.iterations = 100
				},
				{
					.epochs = 10'000,
					.iterations = 1'000
				},
				{
					.epochs = 1,
					.iterations = 1'000'000
				}
			},

			.test_cases =
			{
				{
					.name = "extern_static_string",
					.callback = extern_static_string
				},
				{
					.name = "struct_static_string",
					.callback = struct_static_string
				},
				{
					.name = "class_static_string",
					.callback = class_static_string
				},
				{
					.name = "pure_namespace_static_string",
					.callback = pure_namespace_static_string
				},
				{
					.name = "pure_static_string",
					.callback = pure_static_string
				}
			}
		};

		execute_nanobenchmark(
			test_suite_1
		);

		bool exit_code;
		std::cin >> exit_code;
	}
	*/ 
}


namespace ClassOrMethodLevelConfigurations1
{
	/*

	Conclusion
	- use class-level configurations
	- implement customized configurations per objects



	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |                1.21 |      825,844,244.10 |    0.6% |      0.60 | `Class Or Method Level Configurations1 | configurations_full__class_level | 1`
	|    12.9% |                9.35 |      106,919,434.25 |    0.1% |      4.10 | `Class Or Method Level Configurations1 | configurations_empty__method_level | 1`
	|     2.5% |               48.26 |       20,722,476.59 |    0.2% |     23.41 | `Class Or Method Level Configurations1 | configurations_full__method_level | 1`

	|   100.0% |              969.80 |        1,031,140.80 |    0.2% |      0.43 | `Class Or Method Level Configurations1 | configurations_full__class_level | 1000`
	|    10.6% |            9,113.45 |          109,727.93 |    0.1% |      3.99 | `Class Or Method Level Configurations1 | configurations_empty__method_level | 1000`
	|     2.0% |           48,420.34 |           20,652.48 |    0.2% |     23.48 | `Class Or Method Level Configurations1 | configurations_full__method_level | 1000`

	|   100.0% |        9,627,360.00 |              103.87 |    0.2% |      0.47 | `Class Or Method Level Configurations1 | configurations_full__class_level | 10000000`
	|    10.6% |       91,009,720.00 |               10.99 |    0.0% |      4.46 | `Class Or Method Level Configurations1 | configurations_empty__method_level | 10000000`
	|     2.0% |      485,094,340.00 |                2.06 |    0.2% |     23.78 | `Class Or Method Level Configurations1 | configurations_full__method_level | 10000000`

	About
	- Timestamp Start:      2026-01-15 18:38:58.646074400
	- Timestamp End:        2026-01-15 18:40:23.958922200



	*/

	struct Configurations1
	{
		bool is_enabled =
			default_is_enabled;

		std::string value_1 =
			default_value_1;

		static bool default_is_enabled;

		static std::string default_value_1;

	};

	bool Configurations1::default_is_enabled =
		true;

	std::string Configurations1::default_value_1 =
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";



	struct Configurations2
	{
		bool is_enabled =
			true;

		std::string value_1 =
			"";

		std::string value_2 =
			"";

		std::string value_3 =
			"";

		std::string value_4 =
			"";
	};




	class BenchmarkingSuspect1
	{
	public:
		Configurations1 instance_configurations;

		static BenchmarkingSuspect1 instance;

		void configurations_full__class_level()
		{

		}

		void configurations_full__method_level(
			const Configurations1& configurations = {}
		)
		{

		}

		void configurations_empty__method_level(
			const Configurations2& configurations = {}
		)
		{

		}
	};

	BenchmarkingSuspect1 BenchmarkingSuspect1::instance;

	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "Class Or Method Level Configurations1",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 40000000,
					.iterations = 1
				},
				{
					.epochs = 40000,
					.iterations = 1000
				},
				{
					.epochs = 4,
					.iterations = 10000000
				},
			},
			.test_cases =
			{
				{
					.name = "configurations_full__class_level",
					.callback = []() { BenchmarkingSuspect1::instance.configurations_full__class_level(); }
				},
				{
					.name = "configurations_empty__method_level",
					.callback = []() { BenchmarkingSuspect1::instance.configurations_empty__method_level(); }
				},
				{
					.name = "configurations_full__method_level",
					.callback = []() { BenchmarkingSuspect1::instance.configurations_full__method_level(); }
				},
			}
		};

		execute_nanobenchmark(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}



namespace WithOrWithoutMutexParallelismPerformance
{
	/*

	Conclusion
	- No concrete conclusion
	- For now:
		- option 1
			- benchmark is either sync or async is faster
			- if async
				- benchmark is either full or semi mutex is faster
			- else
				- use sync

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |       29,121,263.64 |               34.34 |    9.1% |      3.65 | :wavy_dash: `With Or Without Mutex Parallelism Performance | file_write_and_read__co_spawn__no_mutex__sync__n | 1` (Unstable with ~11.1 iters. Increase `minEpochIterations` to e.g. 111)
	|   108.0% |       26,957,827.27 |               37.09 |    1.8% |      3.36 | `With Or Without Mutex Parallelism Performance | file_write_and_read__co_spawn__no_mutex__async__n | 1`
	|   107.4% |       27,102,800.00 |               36.90 |    4.2% |      3.67 | `With Or Without Mutex Parallelism Performance | file_write_and_read__co_spawn__with_semi_mutex__n | 1`
	|   102.8% |       28,332,445.45 |               35.30 |    4.3% |      3.49 | `With Or Without Mutex Parallelism Performance | file_write_and_read__co_spawn__with_full_mutex__n | 1`
	|   114.7% |       25,380,550.00 |               39.40 |    4.2% |      3.42 | `With Or Without Mutex Parallelism Performance | file_write_and_read__post__no_mutex__async__n | 1`
	|   102.5% |       28,410,790.91 |               35.20 |   13.0% |      3.50 | :wavy_dash: `With Or Without Mutex Parallelism Performance | file_write_and_read__post__with_semi_mutex__n | 1` (Unstable with ~11.1 iters. Increase `minEpochIterations` to e.g. 111)
	|    83.4% |       34,929,100.00 |               28.63 |    4.9% |      4.20 | `With Or Without Mutex Parallelism Performance | file_write_and_read__post__with_full_mutex__n | 1`

	|   100.0% |      302,526,600.00 |                3.31 |    2.3% |      3.59 | `With Or Without Mutex Parallelism Performance | file_write_and_read__co_spawn__no_mutex__sync__n | 10`
	|   100.3% |      301,568,000.00 |                3.32 |    1.1% |      3.32 | `With Or Without Mutex Parallelism Performance | file_write_and_read__co_spawn__no_mutex__async__n | 10`
	|   100.9% |      299,789,600.00 |                3.34 |    2.4% |      3.50 | `With Or Without Mutex Parallelism Performance | file_write_and_read__co_spawn__with_semi_mutex__n | 10`
	|    97.8% |      309,206,300.00 |                3.23 |    0.7% |      3.40 | `With Or Without Mutex Parallelism Performance | file_write_and_read__co_spawn__with_full_mutex__n | 10`
	|   104.6% |      289,108,900.00 |                3.46 |    5.1% |      3.20 | :wavy_dash: `With Or Without Mutex Parallelism Performance | file_write_and_read__post__no_mutex__async__n | 10` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
	|   100.2% |      301,806,100.00 |                3.31 |    2.1% |      3.32 | `With Or Without Mutex Parallelism Performance | file_write_and_read__post__with_semi_mutex__n | 10`
	|    76.3% |      396,437,700.00 |                2.52 |    3.1% |      4.44 | `With Or Without Mutex Parallelism Performance | file_write_and_read__post__with_full_mutex__n | 10`

	About
	- Timestamp Start:      2026-01-15 12:33:46.227126000
	- Timestamp End:        2026-01-15 12:34:39.336563600
	*/

	inline static boost::asio::thread_pool THREAD_POOL_INSTANCE{ std::thread::hardware_concurrency() };

	inline static std::shared_ptr<boost::asio::thread_pool> THREAD_POOL_HEAP;

	inline static boost::asio::io_context IO;

	inline static boost::asio::strand<decltype(IO.get_executor())> STRAND(IO.get_executor());

	inline static auto WORK = boost::asio::make_work_guard(IO);

	inline static std::vector<std::thread> WORKERS;

	inline static boost::asio::inline_executor exec;

	inline static size_t size_2 = 10;

	void start_io_workers()
	{
		for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
			WORKERS.emplace_back([] { IO.run(); });
	}

	void stop_io_workers()
	{
		WORK.reset();
		IO.stop();
		for (auto& t : WORKERS)
			if (t.joinable())
				t.join();
		WORKERS.clear();
	}

	class Samples
	{
	public:
		// size_t size_1 = 128;

		std::string input_1 = std::string(2000000, '0');

		std::string output_1 = "";

		std::string output_2 = "";

		std::string output_3 = "";

		std::string output_4 = "";

		std::string output_5 = "";

		std::string output_6 = "";

		std::string output_7 = "";

		boost::mutex mutex;

		static Samples instance;

		std::future<void>
			file_write_and_read__co_spawn__with_semi_mutex(
				const std::string&
				file_output_path
			)
		{
			auto future = boost::asio::co_spawn(
				STRAND,
				[this, file_output_path]() -> boost::asio::awaitable<void>
				{
					fast_io::native_file fast_io_write_file(
						file_output_path,
						fast_io::open_mode::out
					);

					{
						boost::unique_lock lock(mutex);

						fast_io::io::print(
							fast_io_write_file,
							input_1
						);
					}

					co_return;
				},
				boost::asio::use_future
			);

			return future;
		}

		std::future<void>
			file_write_and_read__co_spawn__with_full_mutex(
				const std::string&
				file_output_path
			)
		{
			auto future = boost::asio::co_spawn(
				STRAND,
				[this, file_output_path]() -> boost::asio::awaitable<void>
				{
					boost::unique_lock lock(mutex);

					fast_io::native_file fast_io_write_file(
						file_output_path,
						fast_io::open_mode::out
					);

					fast_io::io::print(
						fast_io_write_file,
						input_1
					);

					co_return;
				},
				boost::asio::use_future
			);

			return future;
		}

		std::future<void>
			file_write_and_read__co_spawn__no_mutex__async(
				const std::string&
				file_output_path
			)
		{
			auto future = boost::asio::co_spawn(
				STRAND,
				[this, file_output_path]() -> boost::asio::awaitable<void>
				{
					fast_io::native_file fast_io_write_file(
						file_output_path,
						fast_io::open_mode::out
					);

					fast_io::io::print(
						fast_io_write_file,
						input_1
					);

					co_return;
				},
				boost::asio::use_future
			);

			return future;
		}

		void
			file_write_and_read__co_spawn__no_mutex__sync(
				const std::string&
				file_output_path
			)
		{
			fast_io::native_file fast_io_write_file(
				file_output_path,
				fast_io::open_mode::out
			);

			fast_io::io::print(
				fast_io_write_file,
				input_1
			);

		};

		std::future<void>
			file_write_and_read__post__with_semi_mutex(
				const std::string&
				file_output_path
			)
		{
			std::promise<void> promise;
			std::future<void> future = promise.get_future();

			boost::asio::post(
				THREAD_POOL_INSTANCE,
				[this, file_output_path, promise = std::move(promise)]() mutable
				{
					fast_io::native_file fast_io_write_file(
						file_output_path,
						fast_io::open_mode::out
					);

					{
						boost::unique_lock lock(mutex);

						fast_io::io::print(
							fast_io_write_file,
							input_1
						);
					}

					promise.set_value();
				}
			);

			return future;
		}

		std::future<void>
			file_write_and_read__post__with_full_mutex(
				const std::string&
				file_output_path
			)
		{
			std::promise<void> promise;
			std::future<void> future = promise.get_future();

			boost::asio::post(
				THREAD_POOL_INSTANCE,
				[this, file_output_path, promise = std::move(promise)]() mutable
				{
					boost::unique_lock lock(mutex);

					fast_io::native_file fast_io_write_file(
						file_output_path,
						fast_io::open_mode::out
					);

					fast_io::io::print(
						fast_io_write_file,
						input_1
					);

					promise.set_value();
				}
			);

			return future;
		}

		std::future<void>
			file_write_and_read__post__no_mutex__async(
				const std::string&
				file_output_path
			)
		{
			std::promise<void> promise;
			std::future<void> future = promise.get_future();

			boost::asio::post(
				THREAD_POOL_INSTANCE,
				[this, file_output_path, promise = std::move(promise)]() mutable
				{
					fast_io::native_file fast_io_write_file(
						file_output_path,
						fast_io::open_mode::out
					);

					fast_io::io::print(
						fast_io_write_file,
						input_1
					);

					promise.set_value();
				}
			);

			return future;
		}
	};

	Samples Samples::instance;

	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "With Or Without Mutex Parallelism Performance",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 10,
					.iterations = 1
				},
				{
					.epochs = 1,
					.iterations = 10
				},
			},
			.test_cases =
			{
				{
					.name = "file_write_and_read__co_spawn__no_mutex__sync__n",
					.callback = []()
					{
						for (int i = 0; i < size_2; ++i)
						{
							Samples::instance.file_write_and_read__co_spawn__no_mutex__sync(
								std::string("temp/1_output_") + std::to_string(i) + ".txt"
							);
						}
					}
				},
				{
					.name = "file_write_and_read__co_spawn__no_mutex__async__n",
					.callback = []()
					{
						std::vector<std::future<void>> futures;
						for (int i = 0; i < size_2; ++i)
						{
							futures.push_back(Samples::instance.file_write_and_read__co_spawn__no_mutex__async(
								std::string("temp/2_output_") + std::to_string(i) + ".txt"
							));
						}

						for (auto& future : futures)
						{
							future.get();
						}
					}
				},
				{
					.name = "file_write_and_read__co_spawn__with_semi_mutex__n",
					.callback = []()
					{
						std::vector<std::future<void>> futures;
						for (int i = 0; i < size_2; ++i)
						{
							futures.push_back(Samples::instance.file_write_and_read__co_spawn__with_semi_mutex(
								std::string("temp/3_output_") + std::to_string(i) + ".txt"
							));
						}

						for (auto& future : futures)
						{
							future.get();
						}
					}
				},
				{
					.name = "file_write_and_read__co_spawn__with_full_mutex__n",
					.callback = []()
					{
						std::vector<std::future<void>> futures;
						for (int i = 0; i < size_2; ++i)
						{
							futures.push_back(Samples::instance.file_write_and_read__co_spawn__with_full_mutex(
								std::string("temp/4_output_") + std::to_string(i) + ".txt"
							));
						}

						for (auto& future : futures)
						{
							future.get();
						}
					}
				},
				{
					.name = "file_write_and_read__post__no_mutex__async__n",
					.callback = []()
					{
						std::vector<std::future<void>> futures;
						for (int i = 0; i < size_2; ++i)
						{
							futures.push_back(Samples::instance.file_write_and_read__post__no_mutex__async(
								std::string("temp/5_output_") + std::to_string(i) + ".txt"
							));
						}

						for (auto& future : futures)
						{
							future.get();
						}
					}
				},
				{
					.name = "file_write_and_read__post__with_semi_mutex__n",
					.callback = []()
					{
						std::vector<std::future<void>> futures;
						for (int i = 0; i < size_2; ++i)
						{
							futures.push_back(Samples::instance.file_write_and_read__post__with_semi_mutex(
								std::string("temp/6_output_") + std::to_string(i) + ".txt"
							));
						}

						for (auto& future : futures)
						{
							future.get();
						}
					}
				},
				{
					.name = "file_write_and_read__post__with_full_mutex__n",
					.callback = []()
					{
						std::vector<std::future<void>> futures;
						for (int i = 0; i < size_2; ++i)
						{
							futures.push_back(Samples::instance.file_write_and_read__post__with_full_mutex(
								std::string("temp/7_output_") + std::to_string(i) + ".txt"
							));
						}

						for (auto& future : futures)
						{
							future.get();
						}
					}
				}
			}
		};

		start_io_workers();
		execute_nanobenchmark(
			test_suite
		);
		stop_io_workers();

		bool exit_code;
		std::cin >> exit_code;
	}
}





/*



namespace Experiment_12 // std::string f(const std::string&, ...)
{

	// Results:
	// - small const arguments -> std::string f(const std::string&, ...)
	// - large const arguments -> std::string f(const std::string&, ...)

	inline static std::shared_ptr<boost::asio::thread_pool> THREAD_POOL =
		std::make_shared<boost::asio::thread_pool>(
			std::thread::hardware_concurrency()
		);

	inline static std::string value = "0";

	inline static std::string static_output_value_1 = "";

	inline static std::string static_input_value_1 = "0";

	inline static std::string static_input_value_2 = "0";

	class InstanceObject
	{
	public:
		InstanceObject() = default;

		std::string instance_output_value_1 = "";


		void function_11(std::string x, std::string y)
		{
			instance_output_value_1 = x + y;
		}

		void function_12(const std::string x, const std::string y)
		{
			instance_output_value_1 = x + y;
		}

		void function_13(const std::string& x, const std::string& y)
		{
			instance_output_value_1 = x + y;
		}



		std::string function_14(std::string x, std::string y)
		{
			return x + y;
		}

		std::string function_15(const std::string x, const std::string y)
		{
			return x + y;
		}

		std::string function_16(const std::string& x, const std::string_view& y)
		{
			return x + y.data();
		}



		std::string function_1(std::string x, std::string y)
		{
			return x + y;
		}

		std::string function_2(const std::string x, const std::string y)
		{
			return x + y;
		}

		std::string function_3(const std::string& x, const std::string& y)
		{
			return x + y;
		}



		void function_4(std::string& z, std::string x, std::string y)
		{
			z = x + y;
		}

		void function_5(std::string& z, const std::string x, const std::string y)
		{
			z = x + y;
		}

		void function_6(std::string& z, const std::string& x, const std::string& y)
		{
			z = x + y;
		}

		void function_11(std::string& z, const std::string& x, const std::string& y)
		{
			z = x + y;
		}



		void function_7(std::string x, std::string y)
		{
			static_output_value_1 = x + y;
		}

		void function_8(const std::string x, const std::string y)
		{
			static_output_value_1 = x + y;
		}

		void function_9(const std::string& x, const std::string& y)
		{
			static_output_value_1 = x + y;
		}



		void function_10()
		{
			static_output_value_1 = static_input_value_1 + static_input_value_2;
		}

		static InstanceObject instance;
	};

	InstanceObject InstanceObject::instance;

	void execute()
	{
		NanobenchBenchmarkingTestSuite test_suite
		{
			.name = "Experiment_12",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 1000000,
					.iterations = 1
				},
				{
					.epochs = 100000,
					.iterations = 10
				},
				{
					.epochs = 10000,
					.iterations = 100
				},
				{
					.epochs = 1000,
					.iterations = 1000
				},
				{
					.epochs = 1,
					.iterations = 1000000
				}
			},

			.test_cases =
			{
				{
					.name = "function_signature__constant_arguments__16",
					.callback = []() { std::string z = InstanceObject::instance.function_16("0", "0"); }
				},
				{
					.name = "function_signature__constant_arguments__3",
					.callback = []() { std::string z = InstanceObject::instance.function_3("0", "0"); }
				},
				{
					.name = "function_signature__constant_arguments__6",
					.callback = []() { InstanceObject::instance.function_6(static_output_value_1, "0", "0"); }
				},
				{
					.name = "function_signature__constant_arguments__9",
					.callback = []() { InstanceObject::instance.function_9("0", "0"); }
				},
				{
					.name = "function_signature__constant_arguments__13",
					.callback = []() { InstanceObject::instance.function_13("0", "0"); }
				},
				{
					.name = "function_signature__reference_arguments__16",
					.callback = []() { std::string z = InstanceObject::instance.function_16(static_input_value_1, static_input_value_2); }
				},
				{
					.name = "function_signature__reference_arguments__3",
					.callback = []() { std::string z = InstanceObject::instance.function_3(static_input_value_1, static_input_value_2); }
				},
				{
					.name = "function_signature__reference_arguments__6",
					.callback = []() { InstanceObject::instance.function_6(static_output_value_1, static_input_value_1, static_input_value_2); }
				},
				{
					.name = "function_signature__reference_arguments__9",
					.callback = []() { InstanceObject::instance.function_9(static_input_value_1, static_input_value_2); }
				},
				{
					.name = "function_signature__reference_arguments__13",
					.callback = []() { InstanceObject::instance.function_13(static_input_value_1, static_input_value_2); }
				},
			}
		};

		execute_nanobenchmark(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}

					{
						.name = "function_signature__reference_arguments__1",
						.callback = []() { std::string z = InstanceObject::instance.function_1(static_input_value_1, static_input_value_2); }
					},
					{
						.name = "function_signature__reference_arguments__2",
						.callback = []() { std::string z = InstanceObject::instance.function_2(static_input_value_1, static_input_value_2); }
					},
					{
						.name = "function_signature__reference_arguments__4",
						.callback = []() { InstanceObject::instance.function_4(static_output_value_1, static_input_value_1, static_input_value_2); }
					},
					{
						.name = "function_signature__reference_arguments__5",
						.callback = []() { InstanceObject::instance.function_5(static_output_value_1, static_input_value_1, static_input_value_2); }
					},
					{
						.name = "function_signature__reference_arguments__7",
						.callback = []() { InstanceObject::instance.function_7(static_input_value_1, static_input_value_2); }
					},
					{
						.name = "function_signature__reference_arguments__8",
						.callback = []() { InstanceObject::instance.function_8(static_input_value_1, static_input_value_2); }
					},
					{
						.name = "function_signature__reference_arguments__10",
						.callback = []() { InstanceObject::instance.function_10(); }
					},
					{
						.name = "function_signature__constant_arguments__1",
						.callback = []() { std::string z = InstanceObject::instance.function_1(value, value); }
					},
					{
						.name = "function_signature__constant_arguments__2",
						.callback = []() { std::string z = InstanceObject::instance.function_2(value, value); }
					},
					{
						.name = "function_signature__constant_arguments__4",
						.callback = []() { InstanceObject::instance.function_4(static_output_value_1, value, value); }
					},
					{
						.name = "function_signature__constant_arguments__5",
						.callback = []() { InstanceObject::instance.function_5(static_output_value_1, value, value); }
					},
					{
						.name = "function_signature__constant_arguments__7",
						.callback = []() { InstanceObject::instance.function_7(value, value); }
					},
					{
						.name = "function_signature__constant_arguments__8",
						.callback = []() { InstanceObject::instance.function_8(value, value); }
					},
					{
						.name = "function_signature__constant_arguments__10",
						.callback = []() { InstanceObject::instance.function_10(); }
					},
					{
						.name = "function_signature__constant_arguments__11",
						.callback = []() { InstanceObject::instance.function_11(value, value); }
					},
					{
						.name = "function_signature__constant_arguments__12",
						.callback = []() { InstanceObject::instance.function_12(value, value); }
					},
					{
						.name = "instance_string_1",
						.callback = instance_string_1
					},
					{
						.name = "instance_string_2",
						.callback = instance_string_2
					},
					{
						.name = "instance_lock_with_folly",
						.callback = instance_lock_with_folly
					},
					{
						.name = "static_lock_with_folly",
						.callback = static_lock_with_folly
					},
					{
						.name = "instance_lock_with_folly_2",
						.callback = instance_lock_with_folly_2
					},
					{
						.name = "static_lock_with_folly_2",
						.callback = static_lock_with_folly_2
					},
					{
						.name = "instance_lock_with_folly_map",
						.callback = instance_lock_with_folly_map
					},
					{
						.name = "static_lock_with_folly_map",
						.callback = static_lock_with_folly_map
					},
					{
						.name = "instance_lock_with_std_mutex",
						.callback = instance_lock_with_std_mutex
					},
					{
						.name = "static_lock_with_std_mutex",
						.callback = static_lock_with_std_mutex
					},
					{
						.name = "instance_lock_with_boost_mutex",
						.callback = instance_lock_with_boost_mutex
					},
					{
						.name = "static_lock_with_boost_mutex",
						.callback = static_lock_with_boost_mutex
					},
					{
						.name = "instance_lock_with_empty_boost_lock",
						.callback = instance_lock_with_empty_boost_lock
					},
					{
						.name = "static_lock_with_empty_boost_lock",
						.callback = static_lock_with_empty_boost_lock
					},
					{
						.name = "instance_lock_with_boost_mutex_disabled",
						.callback = instance_lock_with_boost_mutex_disabled
					},
					{
						.name = "static_lock_with_boost_mutex_disabled",
						.callback = static_lock_with_boost_mutex_disabled
					},
					{
						.name = "instance_lock_with_boost_mutex_disabled_scoped",
						.callback = instance_lock_with_boost_mutex_disabled_scoped
					},
					{
						.name = "static_lock_with_boost_mutex_disabled_scoped",
						.callback = static_lock_with_boost_mutex_disabled_scoped
					}

}


*/

