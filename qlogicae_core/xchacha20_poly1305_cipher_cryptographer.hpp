#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class XChaCha20Poly1305CipherCryptographer : public Cryptographer
    {
    public:
        XChaCha20Poly1305CipherCryptographer();
        ~XChaCha20Poly1305CipherCryptographer() = default;
        XChaCha20Poly1305CipherCryptographer(const XChaCha20Poly1305CipherCryptographer&) = delete;
        XChaCha20Poly1305CipherCryptographer(XChaCha20Poly1305CipherCryptographer&&) noexcept = delete;
        XChaCha20Poly1305CipherCryptographer& operator = (XChaCha20Poly1305CipherCryptographer&&) = delete;
        XChaCha20Poly1305CipherCryptographer& operator = (const XChaCha20Poly1305CipherCryptographer&) = delete;

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
