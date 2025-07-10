#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class AES256CipherCryptographer : public Cryptographer
    {
    public:
        AES256CipherCryptographer();
        ~AES256CipherCryptographer() = default;
        AES256CipherCryptographer(const AES256CipherCryptographer&) = delete;
        AES256CipherCryptographer(AES256CipherCryptographer&&) noexcept = delete;
        AES256CipherCryptographer& operator = (AES256CipherCryptographer&&) = delete;
        AES256CipherCryptographer& operator = (const AES256CipherCryptographer&) = delete;

        std::string reverse(const std::string_view& va, const unsigned char* vb, const unsigned char* vc) const;
        std::string transform(const std::string_view& va, const unsigned char* vb, const unsigned char* vc) const;
        std::string reverse(const std::string_view& va, const std::string_view& vb, const std::string_view& vc) const;
        std::string transform(const std::string_view& va, const std::string_view& vb, const std::string_view& vc) const;

        std::future<std::string> reverse_async(const std::string_view& va, const unsigned char* vb, const unsigned char* vc) const;
        std::future<std::string> transform_async(const std::string_view& va, const unsigned char* vb, const unsigned char* vc) const;
        std::future<std::string> reverse_async(const std::string_view& va, const std::string_view& vb, const std::string_view& vc) const;
        std::future<std::string> transform_async(const std::string_view& va, const std::string_view& vb, const std::string_view& vc) const;
    };
}


