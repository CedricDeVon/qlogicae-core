#pragma once

#include "encoder.hpp"
#include "generator.hpp"
#include "cryptographer.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4244)
#endif

#include <jwt-cpp/jwt.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

namespace QLogicaeCore
{
    class JsonWebTokenCryptographer :
        public Cryptographer
    {
    public:
        JsonWebTokenCryptographer();

        ~JsonWebTokenCryptographer() = default;

        JsonWebTokenCryptographer(
            const JsonWebTokenCryptographer&
                json_web_token_cryptographer
        ) = delete;

        JsonWebTokenCryptographer(
            JsonWebTokenCryptographer&&
                json_web_token_cryptographer
        ) noexcept = delete;

        JsonWebTokenCryptographer& operator = (
            JsonWebTokenCryptographer&&
                json_web_token_cryptographer
        ) = delete;

        JsonWebTokenCryptographer& operator = (
            const JsonWebTokenCryptographer&
                json_web_token_cryptographer
         ) = delete;

        std::string transform(
            JsonWebTokenTransformInput options
        ) const;

        JsonWebTokenReverseResult reverse(
            JsonWebTokenReverseInput options
        ) const;

        std::future<std::string> transform_async(
            JsonWebTokenTransformInput options
        ) const;

        std::future<JsonWebTokenReverseResult> reverse_async(
            JsonWebTokenReverseInput options
        ) const;
        
    protected:
        const jwt::algorithm::es256k& _get_es256k_signer(
            const std::string& public_key,
            const std::string& private_key
        ) const;

        const jwt::algorithm::es256k& _get_es256k_verifier(
            const std::string& public_key
        ) const;
    };
}
