#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "generator.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class JsonWebTokenCryptographer : public Cryptographer
    {
    public:
        JsonWebTokenCryptographer();
        ~JsonWebTokenCryptographer() = default;
        JsonWebTokenCryptographer(const JsonWebTokenCryptographer&) = delete;
        JsonWebTokenCryptographer(JsonWebTokenCryptographer&&) noexcept = delete;
        JsonWebTokenCryptographer& operator = (JsonWebTokenCryptographer&&) = delete;
        JsonWebTokenCryptographer& operator = (const JsonWebTokenCryptographer&) = delete;

        std::string transform(JsonWebTokenTransformInput options) const;
        JsonWebTokenReverseResult reverse(JsonWebTokenReverseInput options) const;
        std::future<std::string> transform_async(JsonWebTokenTransformInput options) const;
        std::future<JsonWebTokenReverseResult> reverse_async(JsonWebTokenReverseInput options) const;
        
    protected:
        const jwt::algorithm::es256k& _get_es256k_signer(
            const std::string& public_key,
            const std::string& private_key) const;

        const jwt::algorithm::es256k& _get_es256k_verifier(
            const std::string& public_key) const;
    };
}
