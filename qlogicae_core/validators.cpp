#pragma once

#include "pch.h"

#include "validators.hpp"

namespace QLogicaeCore
{
    Validators& Validators::instance()
    {
        static Validators singleton;

        return singleton;
    }
}
