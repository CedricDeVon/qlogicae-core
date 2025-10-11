#include "pch.hpp"

#include "jsonwebtoken_cryptographer.hpp"

namespace QLogicaeCore
{
    JsonWebTokenCryptographer::JsonWebTokenCryptographer() :
        Cryptographer()
    {

    }

    const jwt::algorithm::es256k& JsonWebTokenCryptographer::
        _get_es256k_signer(
            const std::string& public_key,
            const std::string& private_key
        ) const
    {
        static const jwt::algorithm::es256k signer(
            public_key, private_key, "", "");

        return signer;        
    }

    const jwt::algorithm::es256k& JsonWebTokenCryptographer::
        _get_es256k_verifier(
            const std::string& public_key) const
    {
        static const jwt::algorithm::es256k verifier(
            public_key, "", "", "");

        return verifier;
    }

    std::string JsonWebTokenCryptographer::transform(
        JsonWebTokenTransformInput options) const
    {
        try
        {
            if (options.issuer.empty() ||
                options.data.empty())
            {
                return "";
            }

            if (options.public_key.empty() ||
                options.private_key.empty())
            {
                return "";
            }

            if (options.lifetime < std::chrono::seconds{ 1 } ||
                options.lifetime > std::chrono::hours{ 24 * 30 })
            {
                return "";
            }

            auto now = std::chrono::system_clock::now();

            auto builder = jwt::create()
                .set_type("JWT")
                .set_issuer(options.issuer)
                .set_subject(options.data)
                .set_issued_at(now);

            if (options.lifetime.count() > 0)
                builder.set_expires_at(now + options.lifetime);

            for (const auto& [k, v] : options.claims)
                builder.set_payload_claim(k, jwt::claim(v));

            return builder.sign(_get_es256k_signer(
                options.public_key, options.private_key));
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at JsonWebTokenCryptographer::transform(): " + exception.what());
        }
    }

    JsonWebTokenReverseResult JsonWebTokenCryptographer::reverse(
        JsonWebTokenReverseInput options) const
    {
        JsonWebTokenReverseResult result;

        try
        {
            if (options.token.empty())
            {
                result.message = "Exception at JsonWebTokenCryptographer::reverse(): Token input is empty";
                
                return result;
            }

            if (options.issuer.empty())
            {
                result.message = "Exception at JsonWebTokenCryptographer::reverse(): Expected issuer is empty";
                
                return result;
            }

            if (options.public_key.empty())
            {
                result.message = "Exception at JsonWebTokenCryptographer::reverse(): Public key is empty";
                
                return result;
            }

            auto decoded = jwt::decode(options.token);

            if (decoded.get_issuer() != options.issuer)
            {
                result.message = "Exception at JsonWebTokenCryptographer::reverse(): Invalid issuer";

                return result;
            }

            jwt::verify()
                .allow_algorithm(_get_es256k_verifier(options.public_key))
                .with_issuer(options.issuer)
                .leeway(30)
                .verify(decoded);

            result.is_successful = true;
            result.subject = decoded.get_subject();

            for (const auto& [k, v] : decoded.get_header_json())
            {
                result.headers[k] = v.serialize();
            }

            for (const auto& [k, v] : decoded.get_payload_json())
            {
                result.payloads[k] = v.serialize();
            }
        }
        catch (const std::exception& ex)
        {
            result.message = std::string("Exception at JsonWebTokenCryptographer::reverse(): JWT verification failed: ") + ex.what();
        }

        return result;
    }

    std::future<std::string> JsonWebTokenCryptographer::transform_async(
        JsonWebTokenTransformInput options) const
    {
        return std::async(std::launch::async, [this, options]()
            {
                return this->transform(options);
            });
    }

    std::future<JsonWebTokenReverseResult> JsonWebTokenCryptographer::reverse_async(
        JsonWebTokenReverseInput options) const
    {
        return std::async(std::launch::async, [this, options]()
            {
                return this->reverse(options);
            });
    }
}