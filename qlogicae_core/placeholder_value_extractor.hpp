#pragma once

#include "pch.h"

#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    class PlaceholderValueExtractor : public AbstractValueExtractor
    {
    public:
        ~PlaceholderValueExtractor() = default;
        PlaceholderValueExtractor(const std::string&);
        PlaceholderValueExtractor(
            const PlaceholderValueExtractor&) = delete;
        PlaceholderValueExtractor(
            PlaceholderValueExtractor&&) noexcept = delete;
        PlaceholderValueExtractor& operator =
            (PlaceholderValueExtractor&&) = delete;
        PlaceholderValueExtractor& operator =
            (const PlaceholderValueExtractor&) = delete;

        std::optional<std::string> get_value() const;

    protected:
        const std::string _value;
    };
}

