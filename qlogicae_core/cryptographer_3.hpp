#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "generator.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class Cryptographer3 : public Cryptographer
    {
    public:
        Cryptographer3();
        ~Cryptographer3() = default;
        Cryptographer3(const CryptographerProperties&);
        Cryptographer3(const Cryptographer3&) = delete;
        Cryptographer3(Cryptographer3&&) noexcept = delete;
        Cryptographer3& operator = (Cryptographer3&&) = delete;
        Cryptographer3& operator = (const Cryptographer3&) = delete;

        std::string transform(const std::string&) const;
        bool reverse(const std::string_view&, const std::string_view&) const;

        std::future<std::string> transform_async(const std::string&) const;
        std::future<bool> reverse_async(const std::string_view&, const std::string_view&) const;

    protected:
        CryptographerProperties _va;
    };
}


