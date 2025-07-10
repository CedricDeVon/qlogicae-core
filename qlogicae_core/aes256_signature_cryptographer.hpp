#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class AES256SignatureCryptographer : public Cryptographer
    {
    public:
        AES256SignatureCryptographer();
        ~AES256SignatureCryptographer() = default;
        AES256SignatureCryptographer(const AES256SignatureCryptographer&) = delete;
        AES256SignatureCryptographer(AES256SignatureCryptographer&&) noexcept = delete;
        AES256SignatureCryptographer& operator = (AES256SignatureCryptographer&&) = delete;
        AES256SignatureCryptographer& operator = (const AES256SignatureCryptographer&) = delete;

        std::string reverse(const std::string_view& va, unsigned char* vb) const;
        std::string reverse(const std::string_view& va, const std::string_view& vb) const;
        std::string transform(const std::string_view& va, unsigned char* vb, unsigned char* vc) const;
        std::string transform(const std::string_view& va, const std::string_view& vb, const std::string_view& vc) const;

        std::future<std::string> reverse_async(const std::string_view& va, unsigned char* vb) const;
        std::future<std::string> reverse_async(const std::string_view& va, const std::string_view& vb) const;
        std::future<std::string> transform_async(const std::string_view& va, unsigned char* vb, unsigned char* vc) const;
        std::future<std::string> transform_async(const std::string_view& va, const std::string_view& vb, const std::string_view& vc) const;
    };
}
