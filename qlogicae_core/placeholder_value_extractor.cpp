#include "pch.hpp"

#include "placeholder_value_extractor.hpp"

namespace QLogicaeCore
{
    PlaceholderValueExtractor::PlaceholderValueExtractor(
        const std::string& value
    ) :
            _value(value)
    {

    }

    std::optional<std::string> PlaceholderValueExtractor::get_value()
    {
        try
        {
            return _value;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at PlaceholderValueExtractor::get_value(): " +
                exception.what()
            );
        }
    }

    void PlaceholderValueExtractor::setup(
        Result<void>& result,
        const std::string& value
    )
    {
        _value = value;

        result.set_to_good_status_without_value();
    }

    void PlaceholderValueExtractor::get_value(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _value
        );
    }
}
