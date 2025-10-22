#pragma once

#include "result.hpp"
#include "abstract_application.hpp"
#include "cryptographer_properties.hpp"
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
        AES256CipherCryptographer AES256_CIPHER_CRYPTOGRAPHER;
        
        AES256SignatureCryptographer AES256_SIGNATURE_CRYPTOGRAPHER;

        Argon2idHashCryptographer ARGON2ID_HASH_CRYPTOGRAPHER;

        BcryptHashCryptographer BCRYPT_HASH_CRYPTOGRAPHER;

        SHA256HashCryptographer SHA256_HASH_CRYPTOGRAPHER;

        XChaCha20Poly1305CipherCryptographer XCHACHA20_POLY1305_CIPHER_CRYPTOGRAPHER;
         
        JsonWebTokenCryptographer JSONWEBTOKEN_SIGNATURE_CRYPTOGRAPHER;

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

