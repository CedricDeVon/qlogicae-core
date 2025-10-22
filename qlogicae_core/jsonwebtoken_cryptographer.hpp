#pragma once

#include "encoder.hpp"
#include "generator.hpp"
#include "cryptographer.hpp"
#include "jsonwebtoken_reverse_input.hpp"
#include "jsonwebtoken_reverse_result.hpp"
#include "jsonwebtoken_transform_input.hpp"

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

        bool setup();

        void setup(
            Result<void>& result
        );

        std::string transform(
            JsonWebTokenTransformInput options
        );

        JsonWebTokenReverseResult reverse(
            JsonWebTokenReverseInput options
        );

        std::future<std::string> transform_async(
            JsonWebTokenTransformInput options
        );

        std::future<JsonWebTokenReverseResult> reverse_async(
            JsonWebTokenReverseInput options
        );
        
        void transform(
            Result<std::string>& result,
            JsonWebTokenTransformInput options
        );

        void reverse(
            Result<JsonWebTokenReverseResult>& result,
            JsonWebTokenReverseInput options
        );

        void transform_async(
            Result<std::future<std::string>>& result,
            JsonWebTokenTransformInput options
        );

        void reverse_async(
            Result<std::future<JsonWebTokenReverseResult>>& result,
            JsonWebTokenReverseInput options
        );

    protected:
        const jwt::algorithm::es256k& _get_es256k_signer(
            const std::string& public_key,
            const std::string& private_key
        );

        const jwt::algorithm::es256k& _get_es256k_verifier(
            const std::string& public_key
        );
    };
}
