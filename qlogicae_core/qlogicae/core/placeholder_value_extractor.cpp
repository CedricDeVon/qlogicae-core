#include "pch.hpp"

#include "placeholder_value_extractor.hpp"

namespace QLogicaeCore
{
    PlaceholderValueExtractor::PlaceholderValueExtractor(
        const std::string& value) :
            _value(value)
    {

    }

    std::optional<std::string> PlaceholderValueExtractor::get_value() const
    {
        try
        {
            return _value;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at PlaceholderValueExtractor::get_value(): " + exception.what());
        }
    }
}

