#pragma once

#include "result.hpp"
#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class AES256SignatureCryptographer :
        public Cryptographer
    {
    public:
        AES256SignatureCryptographer();

        ~AES256SignatureCryptographer() = default;

        AES256SignatureCryptographer(
            const AES256SignatureCryptographer&
                aes_256_signature_cryptographer) = delete;

        AES256SignatureCryptographer(
            AES256SignatureCryptographer&&
                aes_256_signature_cryptographer) noexcept = delete;

        AES256SignatureCryptographer& operator = (
            AES256SignatureCryptographer&&
                aes_256_signature_cryptographer) = delete;

        AES256SignatureCryptographer& operator = (
            const AES256SignatureCryptographer&
                aes_256_signature_cryptographer) = delete;

        std::string reverse(
            const std::string_view& cipher,
            unsigned char* public_key
        ) const;

        std::string reverse(
            const std::string_view& cipher,
            const std::string_view& public_key
        ) const;

        std::string transform(
            const std::string_view& text,
            unsigned char* public_key,
            unsigned char* private_key
        ) const;

        std::string transform(
            const std::string_view& text,
            const std::string_view& public_key,
            const std::string_view& private_key
        ) const;

        std::future<std::string> reverse_async(
            const std::string_view& cipher,
            unsigned char* public_key
        ) const;

        std::future<std::string> reverse_async(
            const std::string_view& cipher,
            const std::string_view& public_key
        ) const;

        std::future<std::string> transform_async(
            const std::string_view& text,
            unsigned char* public_key,
            unsigned char* private_key
        ) const;

        std::future<std::string> transform_async(
            const std::string_view& text,
            const std::string_view& public_key,
            const std::string_view& private_key
        ) const;

        void reverse(Result<std::string>& result,
            const std::string_view& cipher,
            unsigned char* public_key) const;

        void reverse(Result<std::string>& result,
            const std::string_view& cipher,
            const std::string_view& public_key) const;

        void transform(Result<std::string>& result,
            const std::string_view& text,
            unsigned char* public_key,
            unsigned char* private_key) const;

        void transform(Result<std::string>& result,
            const std::string_view& text,
            const std::string_view& public_key,
            const std::string_view& private_key) const;

        void reverse_async(Result<std::future<std::string>>& result,
            const std::string_view& cipher,
            unsigned char* public_key) const;

        void reverse_async(Result<std::future<std::string>>& result,
            const std::string_view& cipher,
            const std::string_view& public_key) const;

        void transform_async(Result<std::future<std::string>>& result,
            const std::string_view& text,
            unsigned char* public_key,
            unsigned char* private_key) const;

        void transform_async(Result<std::future<std::string>>& result,
            const std::string_view& text,
            const std::string_view& public_key,
            const std::string_view& private_key) const;
    };
}