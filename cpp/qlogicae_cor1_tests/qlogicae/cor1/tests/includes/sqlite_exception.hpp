#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteException \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class SQLiteExceptionTest : public ::testing::Test
    {
    };

    struct SQLiteExceptionParameter
    {
        std::string message;
        int error_code;
        int extended_code;
    };

    class SQLiteExceptionParameterizedTest :
        public ::testing::TestWithParam<SQLiteExceptionParameter>
    {
    };
}

#endif