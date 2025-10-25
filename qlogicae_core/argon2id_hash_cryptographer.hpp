#pragma once

#include "result.hpp"
#include "encoder.hpp"
#include "generator.hpp"
#include "cryptographer.hpp"
#include "cryptographer_properties.hpp"

namespace QLogicaeCore
{
    class Argon2idHashCryptographer :
        public Cryptographer
    {
    public:
        Argon2idHashCryptographer();

        ~Argon2idHashCryptographer() = default;

        Argon2idHashCryptographer(
            const CryptographerProperties&
                cryptographer_properties
        );

        Argon2idHashCryptographer(
            const Argon2idHashCryptographer&
                argon2id_hash_cryptographer
        ) = delete;

        Argon2idHashCryptographer(
            Argon2idHashCryptographer&&
                argon2id_hash_cryptographer
        ) noexcept = delete;

        Argon2idHashCryptographer& operator = (
            Argon2idHashCryptographer&&
                argon2id_hash_cryptographer
            ) = delete;

        Argon2idHashCryptographer& operator = (
            const Argon2idHashCryptographer&
                argon2id_hash_cryptographer
            ) = delete;

        bool setup();

        void setup(
            Result<void>& result
        );

        bool setup(
            const CryptographerProperties& properties
        );

        void setup(
            Result<void>& result,
            const CryptographerProperties& properties
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

        void setup_async(
            Result<std::future<void>>& result,
            const CryptographerProperties& properties
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback,
            const CryptographerProperties& properties
        );

        std::future<bool> setup_async(
            const CryptographerProperties& properties
        );

        void setup_async(
            const std::function<void(const bool& result)>& callback,
            const CryptographerProperties& properties
        );

        std::string transform(
            const std::string& text
        );

        bool reverse(
            const std::string& hash,
            const std::string& key
        );

        std::future<std::string> transform_async(
            const std::string& text
        );
        
        std::future<bool> reverse_async(
            const std::string& hash,
            const std::string& key
        );

        void transform(
            Result<std::string>& result,
            const std::string& text
        );

        void reverse(
            Result<bool>& result,
            const std::string& hash,
            const std::string& key
        );

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string& text
        );

        void reverse_async(
            Result<std::future<bool>>& result,
            const std::string& hash,
            const std::string& key
        );

        void reverse_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& hash,
            const std::string& key
        );

        void transform_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& text
        );

        void reverse_async(
            const std::function<void(Result<bool>& result)>& callback,
            const std::string& hash,
            const std::string& key
        );

        void transform_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& text
        );

        static Argon2idHashCryptographer& get_instance();

        static void get_instance(
            Result<Argon2idHashCryptographer*>& result
        );

    protected:
        CryptographerProperties _cryptographer_properties;
    };

    inline static Argon2idHashCryptographer& ARGON2ID_HASH_CRYPTOGRAPHER =
        Argon2idHashCryptographer::get_instance();
}

