#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RuntimeBenchmarkerTestCase \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		RuntimeBenchmarkerTestCase
    {
	public:
        std::string
            name =
                "";

        std::function<void()>
            callback =
				[]() {};

		std::function<void()>
			before_test_callback =
				[]() {};

		std::function<void()>
			after_test_callback =
				[]() {};
    };
}

#endif
