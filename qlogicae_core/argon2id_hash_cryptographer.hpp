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

        void setup(
            Result<void>& result,
            const CryptographerProperties& va
        );

        std::string transform(
            const std::string& text
        ) const;

        bool reverse(
            const std::string& hash,
            const std::string& key
        ) const;

        std::future<std::string> transform_async(
            const std::string& text
        ) const;
        
        std::future<bool> reverse_async(
            const std::string& hash,
            const std::string& key
        ) const;

        void transform(
            Result<std::string>& result,
            const std::string& text
        ) const;

        void reverse(
            Result<bool>& result,
            const std::string& hash,
            const std::string& key
        ) const;

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string& text
        ) const;

        void reverse_async(
            Result<std::future<bool>>& result,
            const std::string& hash,
            const std::string& key
        ) const;

    protected:
        CryptographerProperties _cryptographer_properties;
    };
}

