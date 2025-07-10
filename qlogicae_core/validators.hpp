#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class Validators
    {
    public:
        static Validators& instance();

    protected:
        Validators() = default;
        ~Validators() = default;
        Validators(const Validators&) = delete;
        Validators(Validators&&) noexcept = delete;
        Validators& operator = (Validators&&) = delete;
        Validators& operator = (const Validators&) = delete;
    };
}

