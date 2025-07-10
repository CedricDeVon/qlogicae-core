#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class AbstractValueExtractor
    {
    public:
        AbstractValueExtractor() = default;
        ~AbstractValueExtractor() = default;
        AbstractValueExtractor(const AbstractValueExtractor&) = delete;
        AbstractValueExtractor(AbstractValueExtractor&&) noexcept = delete;
        AbstractValueExtractor& operator = (AbstractValueExtractor&&) = delete;
        AbstractValueExtractor& operator = (const AbstractValueExtractor&) = delete;

        virtual std::optional<std::string> get_value() const = 0;
    };
}
