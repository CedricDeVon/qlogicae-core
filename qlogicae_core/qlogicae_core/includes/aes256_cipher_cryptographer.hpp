#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class AES256CipherCryptographer :
        public Cryptographer
    {
    public:
        AES256CipherCryptographer();

        ~AES256CipherCryptographer();

        AES256CipherCryptographer(
            const AES256CipherCryptographer&
                aes256_cipher_cryptographer
        ) = delete;

        AES256CipherCryptographer(
            AES256CipherCryptographer&&
                aes256_cipher_cryptographer
        ) noexcept = delete;

        AES256CipherCryptographer& operator = (
            AES256CipherCryptographer&&
                aes256_cipher_cryptographer
        ) = delete;

        AES256CipherCryptographer& operator = (
            const AES256CipherCryptographer&
                aes256_cipher_cryptographer
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
            const std::string& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        );

        std::string transform(
            const std::string& text,
            const unsigned char* key,
            const unsigned char* nonce
        );

        std::string reverse(
            const std::string& cipher,
            const std::string& key,
            const std::string& nonce
        );

        std::string transform(
            const std::string& text,
            const std::string& key,
            const std::string& nonce
        );

        std::future<std::string> reverse_async(
            const std::string& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        );

        std::future<std::string> transform_async(
            const std::string& text,
            const unsigned char* key,
            const unsigned char* nonce
        );

        std::future<std::string> reverse_async(
            const std::string& cipher,
            const std::string& key,
            const std::string& nonce
        );

        std::future<std::string> transform_async(
            const std::string& text,
            const std::string& key,
            const std::string& nonce
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

        void reverse(
            Result<std::string>& result,
            const std::string& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void transform(
            Result<std::string>& result,
            const std::string& text,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void reverse(
            Result<std::string>& result,
            const std::string& cipher,
            const std::string& key,
            const std::string& nonce
        );

        void transform(
            Result<std::string>& result,
            const std::string& text,
            const std::string& key,
            const std::string& nonce
        );

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string& cipher,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string& text,
            const unsigned char* key,
            const unsigned char* nonce
        );

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string& cipher,
            const std::string& key,
            const std::string& nonce
        );

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string& text,
            const std::string& key,
            const std::string& nonce
        );

        static AES256CipherCryptographer& get_instance();

        static void get_instance(
            Result<AES256CipherCryptographer*>& result
        );
    };

    inline static AES256CipherCryptographer& AES256_CIPHER_CRYPTOGRAPHER =
        AES256CipherCryptographer::get_instance();
}
