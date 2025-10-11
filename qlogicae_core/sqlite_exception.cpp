#include "pch.hpp"

#include "sqlite_exception.hpp"

namespace QLogicaeCore
{
    SQLiteException::SQLiteException(const std::string& message,
        const int error_code,
        const int extended_code)
        : std::runtime_error(message),
        error_code(error_code),
        extended_code(extended_code)
    {
    }

    int SQLiteException::get_error_code() const noexcept
    {
        return error_code;
    }

    int SQLiteException::get_extended_code() const noexcept
    {
        return extended_code;
    }
}
