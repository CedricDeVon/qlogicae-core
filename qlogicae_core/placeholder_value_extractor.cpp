#pragma once

#include "pch.h"

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
        catch (...)
        {
            return "";
        }
    }
}

