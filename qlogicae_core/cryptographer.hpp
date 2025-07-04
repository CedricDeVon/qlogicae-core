#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class Cryptographer
    {
    public:
        Cryptographer() = default;
        ~Cryptographer() = default;
        Cryptographer(const Cryptographer&) = delete;
        Cryptographer(Cryptographer&&) noexcept = delete;
        Cryptographer& operator = (Cryptographer&&) = delete;
        Cryptographer& operator = (const Cryptographer&) = delete;

    protected:
        mutable std::shared_mutex _mutex;
    };
}


