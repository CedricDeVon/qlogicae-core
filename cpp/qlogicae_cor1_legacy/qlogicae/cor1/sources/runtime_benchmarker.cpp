#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RuntimeBenchmarker \
	)

#include "../includes/runtime_benchmarker.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{	    
	RuntimeBenchmarker
		::RuntimeBenchmarker() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RuntimeBenchmarkerConfigurations>()
	{

	}

    bool
        RuntimeBenchmarker
			::execute(
				const RuntimeBenchmarkerTestSuite&
					test_suite
			)
    {
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			const std::string
				test_suite_name =
					test_suite
						.name;

			const std::size_t
				test_suite_epoch_pair_count =
					test_suite
						.epoch_iteration_pairs.size();

			const std::size_t
				test_suite_case_count =
					test_suite
						.test_cases.size();

			const std::size_t
				test_suite_warmup_count =
					test_suite
						.warmup_count;

			const bool
				test_suite_is_relative =
					test_suite
						.is_relative;

			const std::function<void()>&
				before_test_suite_callback =
					test_suite
						.before_test_suite_callback;

			const std::function<void()>&
				after_test_suite_callback =
					test_suite
						.after_test_suite_callback;

			const std::function<void()>&
				before_test_case_callback =
					test_suite
						.before_test_case_callback;

			const std::function<void()>&
				after_test_case_callback =
					test_suite
						.after_test_case_callback;

			const std::function<void()>&
				before_test_case_iteration_callback =
					test_suite
						.before_test_case_iteration_callback;

			const std::function<void()>&
				after_test_case_iteration_callback =
					test_suite
						.after_test_case_iteration_callback;

			before_test_suite_callback();

			for
			(
				const auto&
					epoch_iteration_pair :
					test_suite
						.epoch_iteration_pairs
			)
			{
				before_test_case_callback();

				const std::size_t
					epochs =
						epoch_iteration_pair
							.epochs;

				const std::size_t
					iterations =
						epoch_iteration_pair
							.iterations;

				ankerl::nanobench::Bench
					benchmarker;

				benchmarker
					.minEpochIterations(
						epochs
					);
				
				benchmarker
					.warmup(
						test_suite_warmup_count
					);
				
				benchmarker
					.relative(
						test_suite_is_relative
					);
				
				for
				(
					const auto&
						test_case :
						test_suite
							.test_cases
				)
				{
					const std::string
						test_case_name =
							test_case
								.name;

					const std::string
						benchmark_name =
							test_suite_name +
							"__" +
							test_case_name +
							"__" +
							std::to_string(
								iterations
							);

					const std::function<void()>&
						callback =
							test_case
								.callback;

					const std::function<void()>&
						before_test_callback =
							test_case
								.before_test_callback;

					const std::function<void()>&
						after_test_callback =
							test_case
								.after_test_callback;

					before_test_case_iteration_callback();

					before_test_callback();

					benchmarker
						.run(
							benchmark_name,
							[callback, iterations]()
							{
								for
								(
									std::size_t
										index_3 = 0;
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

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}        
    }
}

#endif

