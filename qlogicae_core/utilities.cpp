#include "pch.h"

#include "utilities.hpp"

namespace QLogicaeCore
{
    Utilities::Utilities()
    {
       
    }

    Utilities& Utilities::get_instance()
    {
        static Utilities instance;

        return instance;
    }
}
