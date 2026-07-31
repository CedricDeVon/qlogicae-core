#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteException \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class SQLiteException :
        public std::runtime_error
    {
    public:
		int
			error_code;

		int
			extended_code;

        SQLiteException(
            const std::string&
				message_value,
            const int
				error_code_value,
            const int
				extended_code_value
        );

		SQLiteException();
    };
}

#endif

