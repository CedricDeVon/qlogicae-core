#pragma once

#include "result.hpp"
#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class XChaCha20Poly1305CipherCryptographer :
        public Cryptographer
    {
    public:
        XChaCha20Poly1305CipherCryptographer();
        
        ~XChaCha20Poly1305CipherCryptographer() = default;
        
        XChaCha20Poly1305CipherCryptographer(
            const XChaCha20Poly1305CipherCryptographer&
                xchacha20poly1305_cryptographer
        ) = delete;
        
        XChaCha20Poly1305CipherCryptographer(
            XChaCha20Poly1305CipherCryptographer&&
                xchacha20poly1305_cryptographer
        ) noexcept = delete;
        
        XChaCha20Poly1305CipherCryptographer& operator = (
            XChaCha20Poly1305CipherCryptographer&&
                xchacha20poly1305_cryptographer
        ) = delete;
        
        XChaCha20Poly1305CipherCryptographer& operator = (
            const XChaCha20Poly1305CipherCryptographer&
                xchacha20poly1305_cryptographer
        ) = delete;

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

        void setup(
            Result<void>& result
        );

        void reverse(
            Result<std::string>& result,
            const std::string_view& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        void transform(
            Result<std::string>& result,
            const std::string_view& text,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        void reverse(
            Result<std::string>& result,
            const std::string_view& cipher,
            const std::string_view& key,
            const std::string_view& nonce
        ) const;

        void transform(
            Result<std::string>& result,
            const std::string_view& text,
            const std::string_view& key,
            const std::string_view& nonce
        ) const;

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string_view& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string_view& text,
            const unsigned char* key,
            const unsigned char* nonce
        ) const;

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string_view& cipher,
            const std::string_view& key,
            const std::string_view& nonce
        ) const;

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string_view& text,
            const std::string_view& key,
            const std::string_view& nonce
        ) const;
    };
}

