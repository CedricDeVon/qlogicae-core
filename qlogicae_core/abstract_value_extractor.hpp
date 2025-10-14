#pragma once

#include "result.hpp"

namespace QLogicaeCore
{
    class AbstractValueExtractor
    {
    public:
        AbstractValueExtractor() = default;

        ~AbstractValueExtractor() = default;

        AbstractValueExtractor(
            const AbstractValueExtractor&
                abstract_value_extractor) = delete;

        AbstractValueExtractor(
            AbstractValueExtractor&&
                abstract_value_extractor) noexcept = delete;

        AbstractValueExtractor& operator = (
            AbstractValueExtractor&&
                abstract_value_extractor) = delete;

        AbstractValueExtractor& operator = (
            const AbstractValueExtractor&
                abstract_value_extractor) = delete;

        virtual std::optional<std::string> get_value() const = 0;

        virtual void get_value(Result<std::string>& result) const = 0;
    };
}