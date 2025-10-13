#include "pch.hpp"

#include "result.hpp"

#include <string>

namespace QLogicaeCore
{
    bool Result<void>::get_is_successful() const
    {
        return _is_successful;
    }

    void Result<void>::set_is_successful(const bool& value)
    {
        _is_successful = value;
    }

    void Result<void>::set_is_successful_to_true()
    {
        _is_successful = true;
    }

    void Result<void>::set_is_successful_to_false()
    {
        _is_successful = false;
    }

    void Result<void>::set_to_success()
    {
        _is_successful = true;
    }

    void Result<void>::set_to_failure()
    {
        _is_successful = false;
    }
}
