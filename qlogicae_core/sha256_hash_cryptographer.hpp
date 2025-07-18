#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "generator.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class SHA256HashCryptographer : public Cryptographer
    {
    public:
        SHA256HashCryptographer();
        ~SHA256HashCryptographer() = default;
        SHA256HashCryptographer(const SHA256HashCryptographer&) = delete;
        SHA256HashCryptographer(SHA256HashCryptographer&&) noexcept = delete;
        SHA256HashCryptographer& operator = (SHA256HashCryptographer&&) = delete;
        SHA256HashCryptographer& operator = (const SHA256HashCryptographer&) = delete;

        std::string transform(const std::string& va) const;
        bool reverse(const std::string& va, const std::string& vb) const;

        std::future<std::string> transform_async(const std::string& va) const;
        std::future<bool> reverse_async(const std::string& va, const std::string& vb) const;
    };
}
