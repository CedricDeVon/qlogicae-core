#pragma once

#include "result.hpp"
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
                bcrypt_hash_cryptographer
        ) = delete;

        BcryptHashCryptographer(
            BcryptHashCryptographer&&
                bcrypt_hash_cryptographer
        ) noexcept = delete;

        BcryptHashCryptographer& operator = (
            BcryptHashCryptographer&&
                bcrypt_hash_cryptographer
            ) = delete;

        BcryptHashCryptographer& operator = (
            const BcryptHashCryptographer&
                bcrypt_hash_cryptographer
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

        static BcryptHashCryptographer& get_instance();

        void get_instance(
            Result<BcryptHashCryptographer*>& result
        );
    };

    inline static BcryptHashCryptographer& BCRYPT_HASH_CRYPTOGRAPHER =
        BcryptHashCryptographer::get_instance();
}
