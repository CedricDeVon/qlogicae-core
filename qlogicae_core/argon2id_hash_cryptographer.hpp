#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "generator.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class Argon2idHashCryptographer : public Cryptographer
    {
    public:
        Argon2idHashCryptographer();
        ~Argon2idHashCryptographer() = default;
        Argon2idHashCryptographer(const CryptographerProperties&);
        Argon2idHashCryptographer(const Argon2idHashCryptographer&) = delete;
        Argon2idHashCryptographer(Argon2idHashCryptographer&&) noexcept = delete;
        Argon2idHashCryptographer& operator = (Argon2idHashCryptographer&&) = delete;
        Argon2idHashCryptographer& operator = (const Argon2idHashCryptographer&) = delete;

        std::string transform(const std::string& va) const;
        bool reverse(const std::string_view& va, const std::string_view& vb) const;

        std::future<std::string> transform_async(const std::string& va) const;
        std::future<bool> reverse_async(const std::string_view& va, const std::string_view& vb) const;

    protected:
        CryptographerProperties _va;
    };
}
