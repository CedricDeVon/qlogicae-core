#pragma once

#include "result.hpp"
#include "logger.hpp"
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

        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            const std::function<void(const bool& result)>& callback
        );

        void setup_async(
            Result<std::future<void>>& result
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback
        );

        std::string reverse(
            const std::string_view& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        );
        
        std::string transform(
            const std::string_view& text,
            const unsigned char* key,
            const unsigned char* nonce
        );
        
        std::string reverse(
            const std::string_view& cipher,
            const std::string_view& key,
            const std::string_view& nonce
        );
        
        std::string transform(
            const std::string_view& text,
            const std::string_view& key,
            const std::string_view& nonce
        );
        
        std::future<std::string> reverse_async(
            const std::string_view& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        );
        
        std::future<std::string> transform_async(
            const std::string_view& text,
            const unsigned char* key,
            const unsigned char* nonce
        );
        
        std::future<std::string> reverse_async(
            const std::string_view& cipher,
            const std::string_view& key,
            const std::string_view& nonce
        );
        
        std::future<std::string> transform_async(
            const std::string_view& text,
            const std::string_view& key,
            const std::string_view& nonce
        );

        void reverse_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void transform_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& text,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void reverse_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& cipher,
            const std::string& key,
            const std::string& nonce
        );

        void transform_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& text,
            const std::string& key,
            const std::string& nonce
        );

        void reverse(
            Result<std::string>& result,
            const std::string_view& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void transform(
            Result<std::string>& result,
            const std::string_view& text,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void reverse(
            Result<std::string>& result,
            const std::string_view& cipher,
            const std::string_view& key,
            const std::string_view& nonce
        );

        void transform(
            Result<std::string>& result,
            const std::string_view& text,
            const std::string_view& key,
            const std::string_view& nonce
        );

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string_view& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string_view& text,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string_view& cipher,
            const std::string_view& key,
            const std::string_view& nonce
        );

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string_view& text,
            const std::string_view& key,
            const std::string_view& nonce
        );

        void reverse_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void transform_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& text,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void reverse_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& cipher,
            const std::string& key,
            const std::string& nonce
        );

        void transform_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& text,
            const std::string& key,
            const std::string& nonce
        );

        static XChaCha20Poly1305CipherCryptographer& get_instance();

        static void get_instance(
            Result<XChaCha20Poly1305CipherCryptographer*>& result
        );
    };

    inline static XChaCha20Poly1305CipherCryptographer& XCHACHA20_POLY1305_CIPHER_CRYPTOGRAPHER =
        XChaCha20Poly1305CipherCryptographer::get_instance();
}

