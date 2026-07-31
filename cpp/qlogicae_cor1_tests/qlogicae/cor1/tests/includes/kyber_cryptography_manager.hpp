#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		KyberCryptographyManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
    class KyberCryptographyManagerTest
        : public ::testing::Test
    {
    protected:
        KyberCryptographyManager cryptography_manager;
    };

    class KyberAlgorithmParameterTest
        : public ::testing::TestWithParam<
        KyberCryptographyAlgorithm>
    {
    protected:
        KyberCryptographyManager cryptography_manager;
    };
}

#endif
