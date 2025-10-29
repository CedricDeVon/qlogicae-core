#include "pch.hpp"

#include "abstract_application.hpp"

namespace QLogicaeCore
{
    AbstractApplication::AbstractApplication()
    {
        _is_enabled = false;
    }

    AbstractApplication::~AbstractApplication()
    {

    }

    bool AbstractApplication::get_is_enabled()
    {
        return _is_enabled;
    }

    void AbstractApplication::get_is_enabled(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    void AbstractApplication::set_is_enabled(
        const bool& value
    )
    {
        _is_enabled = value;
    }

    void AbstractApplication::set_is_enabled(
        Result<void>& result,
        const bool& value
    )
    {
        _is_enabled = value;

        result.set_to_good_status_without_value();
    }
}
