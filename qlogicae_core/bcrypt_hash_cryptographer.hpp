#pragma once

#include "encoder.hpp"
#include "generator.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class BcryptHashCryptographer :
        public Cryptographer
    {
    public:
        BcryptHashCryptographer();

        ~BcryptHashCryptographer() = default;

        BcryptHashCryptographer(
            const BcryptHashCryptographer&
                bcrypt_hash_cryptographer) = delete;

        BcryptHashCryptographer(
            BcryptHashCryptographer&&
                bcrypt_hash_cryptographer) noexcept = delete;

        BcryptHashCryptographer& operator = (
            BcryptHashCryptographer&&
                bcrypt_hash_cryptographer) = delete;

        BcryptHashCryptographer& operator = (
            const BcryptHashCryptographer&
                bcrypt_hash_cryptographer) = delete;

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
    };
}
