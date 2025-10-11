#pragma once

namespace QLogicaeCore
{
    struct ValidationPasswordRules
    {
        std::size_t minimum_length = 8;
        std::size_t maximum_length = 128;
        bool require_alpha_numerics = true;
        bool require_unique_characters = false;
        bool require_special_characters = true;
        bool require_uppercase_characters = true;
        bool require_lowercase_characters = true;
    };
}
