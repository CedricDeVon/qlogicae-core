#include "pch.hpp"

#include "../includes/sqlite_exception.hpp"

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

    int SQLiteException::get_error_code() noexcept
    {
        return error_code;
    }

    int SQLiteException::get_extended_code() noexcept
    {
        return extended_code;
    }

    void SQLiteException::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }
}
