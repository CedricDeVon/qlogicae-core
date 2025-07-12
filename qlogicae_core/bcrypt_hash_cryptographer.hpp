#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "generator.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class BcryptHashCryptographer : public Cryptographer
    {
    public:
        BcryptHashCryptographer();
        ~BcryptHashCryptographer() = default;
        BcryptHashCryptographer(const BcryptHashCryptographer&) = delete;
        BcryptHashCryptographer(BcryptHashCryptographer&&) noexcept = delete;
        BcryptHashCryptographer& operator = (BcryptHashCryptographer&&) = delete;
        BcryptHashCryptographer& operator = (const BcryptHashCryptographer&) = delete;

        std::string transform(const std::string& va) const;
        bool reverse(const std::string& va, const std::string& vb) const;

        std::future<std::string> transform_async(const std::string& va) const;
        std::future<bool> reverse_async(const std::string& va, const std::string& vb) const;
    };
}
