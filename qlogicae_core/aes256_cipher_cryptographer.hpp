#pragma once

#include "result.hpp"
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

        void setup(Result<void>& result);

        std::string reverse(
            const std::string& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        std::string transform(
            const std::string& text,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        std::string reverse(
            const std::string& cipher,
            const std::string& key,
            const std::string& nonce
        ) const;

        std::string transform(
            const std::string& text,
            const std::string& key,
            const std::string& nonce
        ) const;

        std::future<std::string> reverse_async(
            const std::string& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        std::future<std::string> transform_async(
            const std::string& text,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        std::future<std::string> reverse_async(
            const std::string& cipher,
            const std::string& key,
            const std::string& nonce
        ) const;

        std::future<std::string> transform_async(
            const std::string& text,
            const std::string& key,
            const std::string& nonce
        ) const;

        void reverse(
            Result<std::string>& result,
            const std::string& cipher,
            const unsigned char* key,
            const unsigned char* nonce) const;

        void transform(
            Result<std::string>& result,
            const std::string& text,
            const unsigned char* key,
            const unsigned char* nonce) const;

        void reverse(
            Result<std::string>& result,
            const std::string& cipher,
            const std::string& key,
            const std::string& nonce) const;

        void transform(
            Result<std::string>& result,
            const std::string& text,
            const std::string& key,
            const std::string& nonce) const;

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string& cipher,
            const unsigned char* key,
            const unsigned char* nonce) const;

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string& text,
            const unsigned char* key,
            const unsigned char* nonce) const;

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string& cipher,
            const std::string& key,
            const std::string& nonce) const;

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string& text,
            const std::string& key,
            const std::string& nonce) const;
    };
}
