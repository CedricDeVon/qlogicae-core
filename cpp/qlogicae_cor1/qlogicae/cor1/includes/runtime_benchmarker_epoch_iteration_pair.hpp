#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RuntimeBenchmarkerEpochIterationPair \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		RuntimeBenchmarkerEpochIterationPair
    {
	public:
        std::size_t
            epochs =
                1;

        std::size_t
            iterations =
                1;
    };
}

#endif
