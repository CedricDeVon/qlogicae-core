#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "encoder.hpp"
#include "generator.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class SHA256HashCryptographer :
        public Cryptographer
    {
    public:
        SHA256HashCryptographer();
        
        ~SHA256HashCryptographer() = default;
        
        SHA256HashCryptographer(
            const SHA256HashCryptographer&
                sha256_hash_cryptographer
        ) = delete;
        
        SHA256HashCryptographer(
            SHA256HashCryptographer&&
                sha256_hash_cryptographer
        ) noexcept = delete;
        
        SHA256HashCryptographer& operator = (
            SHA256HashCryptographer&&
                sha256_hash_cryptographer
        ) = delete;
        
        SHA256HashCryptographer& operator = (
            const SHA256HashCryptographer&
                sha256_hash_cryptographer
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
            const std::string& cipher,
            const std::string& key
        );

        std::future<std::string> transform_async(
            const std::string& text
        );
        
        std::future<bool> reverse_async(
            const std::string& cipher,
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
            Result<std::string> result,
            const std::string& text
        );

        void reverse(
            Result<bool> result,
            const std::string& cipher,
            const std::string& key
        );

        void transform_async(
            Result<std::future<std::string>> result,
            const std::string& text
        );

        void reverse_async(
            Result<std::future<bool>> result,
            const std::string& cipher,
            const std::string& key
        );

        static SHA256HashCryptographer& get_instance();

        static void get_instance(
            Result<SHA256HashCryptographer*>& result
        );
    };

    inline static SHA256HashCryptographer& SHA256_HASH_CRYPTOGRAPHER =
        SHA256HashCryptographer::get_instance();
}
