#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RuntimeBenchmarkerTestSuite \
	)

#include "runtime_benchmarker_test_case.hpp"
#include "runtime_benchmarker_epoch_iteration_pair.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		RuntimeBenchmarkerTestSuite
    {
	public:
        std::string
            name =
				"";

        size_t
            warmup_count =
                1;

        bool
            is_relative =
                true;

        std::vector<RuntimeBenchmarkerEpochIterationPair>
            epoch_iteration_pairs =
				{};

        std::vector<RuntimeBenchmarkerTestCase>
            test_cases =
				{};

        std::function<void()>
            before_test_suite_callback =
				[]() {};

		std::function<void()>
			before_test_case_callback =
				[]() {};

		std::function<void()>
			before_test_case_iteration_callback =
				[]() {};

		std::function<void()>
			after_test_suite_callback =
				[]() {};

		std::function<void()>
			after_test_case_callback =
				[]() {};

		std::function<void()>
			after_test_case_iteration_callback =
				[]() {};
    };
}

#endif
