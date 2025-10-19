#pragma once

#include "result.hpp"
#include "abstract_application.hpp"
#include "bcrypt_hash_cryptographer.hpp"
#include "sha256_hash_cryptographer.hpp"
#include "jsonwebtoken_cryptographer.hpp"
#include "argon2id_hash_cryptographer.hpp"
#include "aes256_cipher_cryptographer.hpp"
#include "aes256_signature_cryptographer.hpp"
#include "xchacha20_poly1305_cipher_cryptographer.hpp"

namespace QLogicaeCore
{
    class ApplicationCryptographer :
        public AbstractApplication
    {
    public:
        BcryptHashCryptographer BCRYPT_HASH;

        SHA256HashCryptographer SHA256_HASH;

        Argon2idHashCryptographer ARGON2ID_HASH;

        AES256CipherCryptographer AES256_CIPHER;

        XChaCha20Poly1305CipherCryptographer XCHACHA20_POLY1305_CIPHER;

        JsonWebTokenCryptographer JSONWEBTOKEN_SIGNATURE;

        AES256SignatureCryptographer AES256_SIGNATURE;

        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            Result<std::future<void>>& result
        );

        static ApplicationCryptographer& get_instance();

        static void get_instance(
            Result<ApplicationCryptographer*>& result
        );

    protected:
        ApplicationCryptographer();

        ~ApplicationCryptographer();

        ApplicationCryptographer(
            const ApplicationCryptographer& instance
        ) = default;

        ApplicationCryptographer(
            ApplicationCryptographer&& instance
        ) noexcept = delete;

        ApplicationCryptographer& operator = (
            ApplicationCryptographer&& instance
        ) = default;

        ApplicationCryptographer& operator = (
            const ApplicationCryptographer& instance
        ) = delete;
    };

    inline static ApplicationCryptographer& QLOGICAE_APPLICATION_CRYPTOGRAPHER =
        ApplicationCryptographer::get_instance();    
}
