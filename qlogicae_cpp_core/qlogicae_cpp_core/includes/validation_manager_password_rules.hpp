#pragma once

#include "instance_manager.hpp"

namespace QLogicaeCppCore
{
    struct ValidationManagerPasswordRules
    {
        std::size_t minimum_length = 8;
        
        std::size_t maximum_length = 128;
        
        bool require_alpha_numerics = true;
        
        bool require_unique_characters = false;
        
        bool require_special_characters = true;
        
        bool require_uppercase_characters = true;
        
        bool require_lowercase_characters = true;
    };

    inline static ValidationManagerPasswordRules& VALIDATION_MANAGER_PASSWORD_RULES =
        INSTANCE_MANAGER.get_instance<ValidationManagerPasswordRules>();
}
