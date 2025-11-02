#include "pch.hpp"

#include "../includes/jsonwebtoken_cryptographer.hpp"

namespace QLogicaeCore
{
    JsonWebTokenCryptographer::JsonWebTokenCryptographer() :
        Cryptographer()
    {

    }

    JsonWebTokenCryptographer::~JsonWebTokenCryptographer()
    {

    }

    const jwt::algorithm::es256k& JsonWebTokenCryptographer::
        _get_es256k_signer(
            const std::string& public_key,
            const std::string& private_key
        )
    {
        static const jwt::algorithm::es256k signer(
            public_key, private_key, "", "");

        return signer;        
    }

    const jwt::algorithm::es256k& JsonWebTokenCryptographer::
        _get_es256k_verifier(
            const std::string& public_key
        )
    {
        static const jwt::algorithm::es256k verifier(
            public_key, "", "", "");

        return verifier;
    }

    std::string JsonWebTokenCryptographer::transform(
        JsonWebTokenTransformInput options
    )
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
            LOGGER.handle_exception_async(
                "QLogicaeCore::JsonWebTokenCryptographer::transform()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::JsonWebTokenCryptographer::transform(): " +
                exception.what()
            );
        }
    }

    JsonWebTokenReverseResult JsonWebTokenCryptographer::reverse(
        JsonWebTokenReverseInput options
    )
    {
        JsonWebTokenReverseResult result;

        try
        {
            if (options.token.empty())
            {
                result.message =
                    "QLogicaeCore::JsonWebTokenCryptographer::reverse(): Token input is empty";

                return result;
            }

            if (options.issuer.empty())
            {
                result.message =
                    "QLogicaeCore::JsonWebTokenCryptographer::reverse(): Expected issuer is empty";

                return result;
            }

            if (options.public_key.empty())
            {
                result.message =
                    "QLogicaeCore::JsonWebTokenCryptographer::reverse(): Public key is empty";

                return result;
            }

            auto decoded = jwt::decode(options.token);

            if (decoded.get_issuer() != options.issuer)
            {
                result.message =
                    "QLogicaeCore::JsonWebTokenCryptographer::reverse(): Invalid issuer";

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
            LOGGER.handle_exception_async(
                "QLogicaeCore::JsonWebTokenCryptographer::reverse()",
                ex.what()
            );

            result.message = std::string(
                "QLogicaeCore::JsonWebTokenCryptographer::reverse(): JWT verification failed: ") +
                ex.what();
        }

        return result;
    }

    std::future<std::string> JsonWebTokenCryptographer::transform_async(
        JsonWebTokenTransformInput options
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, options,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    transform(
                        options
                    )
                );
            }
        );

        return future;
    }

    std::future<JsonWebTokenReverseResult> JsonWebTokenCryptographer::reverse_async(
        JsonWebTokenReverseInput options
    )
    {
        std::promise<JsonWebTokenReverseResult> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, options,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    reverse(
                        options
                    )
                );
            }
        );

        return future;
    }

    bool JsonWebTokenCryptographer::setup()
    {
        Result<void> result;

        setup(result);

        return result.is_status_safe();
    }

    void JsonWebTokenCryptographer::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    void JsonWebTokenCryptographer::transform(
        Result<std::string>& result,
        JsonWebTokenTransformInput options
    )
    {
        if (options.issuer.empty() ||
            options.data.empty())
        {
            return result.set_to_bad_status_with_value("");
        }

        if (options.public_key.empty() ||
            options.private_key.empty())
        {
            return result.set_to_bad_status_with_value("");
        }

        if (options.lifetime < std::chrono::seconds{ 1 } ||
            options.lifetime > std::chrono::hours{ 24 * 30 })
        {
            return result.set_to_bad_status_with_value("");
        }

        auto now = std::chrono::system_clock::now();

        auto builder = jwt::create()
            .set_type("JWT")
            .set_issuer(options.issuer)
            .set_subject(options.data)
            .set_issued_at(now);

        if (options.lifetime.count() > 0)
        {
            builder.set_expires_at(now + options.lifetime);
        }

        for (const auto& [k, v] : options.claims)
        {
            builder.set_payload_claim(k, jwt::claim(v));
        }

        result.set_to_good_status_with_value(builder.sign(_get_es256k_signer(
            options.public_key, options.private_key))
        );
    }

    void JsonWebTokenCryptographer::reverse(
        Result<JsonWebTokenReverseResult>& result,
        JsonWebTokenReverseInput options
    )
    {
        JsonWebTokenReverseResult& json_result =
            result.get_value();
        if (options.token.empty())
        {
            json_result.message = "Token input is empty";
            return result.set_status_to_bad();
        }

        if (options.issuer.empty())
        {
            json_result.message = "Expected issuer is empty";
            return result.set_status_to_bad();
        }

        if (options.public_key.empty())
        {
            json_result.message = "Public key is empty";
            return result.set_status_to_bad();
        }

        auto decoded = jwt::decode(options.token);

        if (decoded.get_issuer() != options.issuer)
        {
            json_result.message = "Invalid issuer";
            return result.set_status_to_bad();
        }

        jwt::verify()
            .allow_algorithm(_get_es256k_verifier(options.public_key))
            .with_issuer(options.issuer)
            .leeway(30)
            .verify(decoded);

        json_result.is_successful = true;
        json_result.subject = decoded.get_subject();

        for (const auto& [k, v] : decoded.get_header_json())
        {
            json_result.headers[k] = v.serialize();
        }

        for (const auto& [k, v] : decoded.get_payload_json())
        {
            json_result.payloads[k] = v.serialize();
        }

        result.set_status_to_good();
    }

    void JsonWebTokenCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        JsonWebTokenTransformInput options
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, options,
            promise = std::move(promise)]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    options
                );

                promise.set_value(
                    result.get_value()
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void JsonWebTokenCryptographer::reverse_async(
        Result<std::future<JsonWebTokenReverseResult>>& result,
        JsonWebTokenReverseInput options
    )
    {
        std::promise<JsonWebTokenReverseResult> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, options,
            promise = std::move(promise)]() mutable
            {
                Result<JsonWebTokenReverseResult> result;

                reverse(
                    result,
                    options
                );

                promise.set_value(
                    result.get_value()
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void JsonWebTokenCryptographer::reverse_async(
        const std::function<void(const JsonWebTokenReverseResult& result)>& callback,
        JsonWebTokenReverseInput options
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, options, callback]() mutable
            {
                callback(
                    reverse(
                        options
                    )
                );
            }
        );
    }

    void JsonWebTokenCryptographer::transform_async(
        const std::function<void(const std::string& result)>& callback,
        JsonWebTokenTransformInput options
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, options, callback]() mutable
            {
                callback(
                    transform(
                        options
                    )
                );
            }
        );
    }

    void JsonWebTokenCryptographer::reverse_async(
        const std::function<void(Result<JsonWebTokenReverseResult>& result)>& callback,
        JsonWebTokenReverseInput options
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, options, callback]() mutable
            {
                Result<JsonWebTokenReverseResult> result;

                reverse(
                    result,
                    options
                );

                callback(
                    result
                );
            }
        );
    }

    void JsonWebTokenCryptographer::transform_async(
        const std::function<void(Result<std::string>& result)>& callback,
        JsonWebTokenTransformInput options
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, options, callback]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    options
                );

                callback(
                    result
                );
            }
        );
    }

    JsonWebTokenCryptographer& JsonWebTokenCryptographer::get_instance()
    {
        static JsonWebTokenCryptographer instance;

        return instance;
    }

    void JsonWebTokenCryptographer::get_instance(
        QLogicaeCore::Result<JsonWebTokenCryptographer*>& result
    )
    {
        static JsonWebTokenCryptographer instance;

        result.set_to_good_status_with_value(&instance);
    }
}
