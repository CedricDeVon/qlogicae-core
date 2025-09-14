#pragma once

#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    class PlaceholderValueExtractor :
        public AbstractValueExtractor
    {
    public:
        ~PlaceholderValueExtractor() = default;
        
        PlaceholderValueExtractor(
            const std::string& name
        );
        
        PlaceholderValueExtractor(
            const PlaceholderValueExtractor&
                placeholder_value_extractor
        ) = delete;
        
        PlaceholderValueExtractor(
            PlaceholderValueExtractor&&
                placeholder_value_extractor
        ) noexcept = delete;
        
        PlaceholderValueExtractor& operator =
            (PlaceholderValueExtractor&&
                placeholder_value_extractor) = delete;
        
        PlaceholderValueExtractor& operator =
            (const PlaceholderValueExtractor&
                placeholder_value_extractor) = delete;

        std::optional<std::string> get_value() const;

    protected:
        const std::string _value;
    };
}
