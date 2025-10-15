#pragma once

namespace QLogicaeCore
{
    class SQLiteException :
        public std::runtime_error
    {
    public:
        SQLiteException(
            const std::string& message,
            const int error_code,
            const int extended_code);

        int get_error_code() const noexcept;

        int get_extended_code() const noexcept;

    protected:
        int error_code;
        int extended_code;
    };
}
