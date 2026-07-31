#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CryptographyMigrationManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
    class CryptographyMigrationManagerTest:
        public ::testing::Test
    {
    public:
        CryptographyMigrationManager manager;
    };

    struct MigrationTestParameters
    {
        bool callback_return;
        bool throw_exception;
        bool expect_success;
    };

    class CryptographyMigrationManagerParameterizedTest:
        public ::testing::TestWithParam<MigrationTestParameters>
    {
    public:
        CryptographyMigrationManager manager;
    };
}

#endif
