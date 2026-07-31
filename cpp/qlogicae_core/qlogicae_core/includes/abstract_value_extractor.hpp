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
                instance
        ) = delete;

        AbstractValueExtractor(
            AbstractValueExtractor&&
                instance
        ) noexcept = delete;

        AbstractValueExtractor& operator = (
            AbstractValueExtractor&&
                instance
            ) = delete;

        AbstractValueExtractor& operator = (
            const AbstractValueExtractor&
                instance
            ) = delete;

        virtual std::optional<std::string> get_value() = 0;

        virtual void get_value(
            Result<std::string>& result
        ) = 0;
    };
}