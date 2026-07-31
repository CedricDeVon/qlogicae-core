#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
    class
        DilithiumCryptographyManagerTest :
            public ::testing::Test
    {
    public:
        DilithiumCryptographyManager
            manager;
    };

    class
        DilithiumAlgorithmParameterizedTest:
        public ::testing::TestWithParam<DilithiumCryptographyAlgorithm>
    {
    public:
        DilithiumCryptographyManager
            manager;
    };

    class
        DilithiumCryptographyManagerParameterizedTest:
        public ::testing::TestWithParam<DilithiumCryptographyAlgorithm>
    {
    public:
        DilithiumCryptographyManager
            manager;
    };
}

#endif
