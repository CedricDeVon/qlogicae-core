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
                aes_256_signature_cryptographer
        ) = delete;

        AES256SignatureCryptographer(
            AES256SignatureCryptographer&&
                aes_256_signature_cryptographer
        ) noexcept = delete;

        AES256SignatureCryptographer& operator = (
            AES256SignatureCryptographer&&
                aes_256_signature_cryptographer
        ) = delete;

        AES256SignatureCryptographer& operator = (
            const AES256SignatureCryptographer&
                aes_256_signature_cryptographer
        ) = delete;

        bool setup();

        void setup(
            Result<void>& result
        );

        std::string reverse(
            const std::string& cipher,
            unsigned char* public_key
        );

        std::string reverse(
            const std::string& cipher,
            const std::string& public_key
        );

        std::string transform(
            const std::string& text,
            unsigned char* public_key,
            unsigned char* private_key
        );

        std::string transform(
            const std::string& text,
            const std::string& public_key,
            const std::string& private_key
        );

        std::future<std::string> reverse_async(
            const std::string& cipher,
            unsigned char* public_key
        );

        std::future<std::string> reverse_async(
            const std::string& cipher,
            const std::string& public_key
        );

        std::future<std::string> transform_async(
            const std::string& text,
            unsigned char* public_key,
            unsigned char* private_key
        );

        std::future<std::string> transform_async(
            const std::string& text,
            const std::string& public_key,
            const std::string& private_key
        );

        void reverse(
            Result<std::string>& result,
            const std::string& cipher,
            unsigned char* public_key
        );

        void reverse(
            Result<std::string>& result,
            const std::string& cipher,
            const std::string& public_key
        );

        void transform(
            Result<std::string>& result,
            const std::string& text,
            unsigned char* public_key,
            unsigned char* private_key
        );

        void transform(
            Result<std::string>& result,
            const std::string& text,
            const std::string& public_key,
            const std::string& private_key
        );

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string& cipher,
            unsigned char* public_key
        );

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string& cipher,
            const std::string& public_key
        );

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string& text,
            unsigned char* public_key,
            unsigned char* private_key
        );

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string& text,
            const std::string& public_key,
            const std::string& private_key
        );
    };

    static inline AES256SignatureCryptographer AES256_SIGNATURE_CRYPTOGRAPHER;
}
