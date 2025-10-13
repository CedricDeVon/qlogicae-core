#pragma once

#include "result.hpp"
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

        std::string transform(
            const std::string& text
        ) const;
        
        bool reverse(
            const std::string& cipher,
            const std::string& key
        ) const;

        std::future<std::string> transform_async(
            const std::string& text
        ) const;
        
        std::future<bool> reverse_async(
            const std::string& cipher,
            const std::string& key
        ) const;

        void transform(
            Result<std::string> result,
            const std::string& text
        ) const;

        void reverse(
            Result<void> result,
            const std::string& cipher,
            const std::string& key
        ) const;

        void transform_async(
            Result<std::future<std::string>> result,
            const std::string& text
        ) const;

        void reverse_async(
            Result<std::future<void>> result,
            const std::string& cipher,
            const std::string& key
        ) const;
    };

}
