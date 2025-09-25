#pragma once

#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class AES256CipherCryptographer :
        public Cryptographer
    {
    public:
        AES256CipherCryptographer();

        ~AES256CipherCryptographer() = default;

        AES256CipherCryptographer(
            const AES256CipherCryptographer&
                aes256_cipher_cryptographer) = delete;

        AES256CipherCryptographer(
            AES256CipherCryptographer&&
                aes256_cipher_cryptographer) noexcept = delete;

        AES256CipherCryptographer& operator = (
            AES256CipherCryptographer&&
                aes256_cipher_cryptographer) = delete;

        AES256CipherCryptographer& operator = (
            const AES256CipherCryptographer&
                aes256_cipher_cryptographer) = delete;

        std::string reverse(
            const std::string_view& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        std::string transform(
            const std::string_view& text,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        std::string reverse(
            const std::string_view& cipher,
            const std::string_view& key,
            const std::string_view& nonce
        ) const;

        std::string transform(
            const std::string_view& text,
            const std::string_view& key,
            const std::string_view& nonce
        ) const;

        std::future<std::string> reverse_async(
            const std::string_view& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        std::future<std::string> transform_async(
            const std::string_view& text,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        std::future<std::string> reverse_async(
            const std::string_view& cipher,
            const std::string_view& key,
            const std::string_view& nonce
        ) const;

        std::future<std::string> transform_async(
            const std::string_view& text,
            const std::string_view& key,
            const std::string_view& nonce
        ) const;
    };
}
