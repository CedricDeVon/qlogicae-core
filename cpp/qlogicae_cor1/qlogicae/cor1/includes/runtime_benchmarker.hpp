#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RuntimeBenchmarker \
	)

#include "runtime_benchmarker_test_case.hpp"
#include "runtime_benchmarker_test_suite.hpp"
#include "runtime_benchmarker_configurations.hpp"
#include "runtime_benchmarker_epoch_iteration_pair.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		RuntimeBenchmarker :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RuntimeBenchmarkerConfigurations>
    {
    public:        
		RuntimeBenchmarker();

        bool
            execute(
                const RuntimeBenchmarkerTestSuite&
                    test_suite
        );
    };    
}

#endif
