#include "pch.hpp"

#include "../includes/aes256_signature_cryptographer.hpp"

namespace QLogicaeCore
{
	AES256SignatureCryptographer::AES256SignatureCryptographer() :
		Cryptographer()
	{
        
	}

    AES256SignatureCryptographer::~AES256SignatureCryptographer()
    {

    }

    bool AES256SignatureCryptographer::setup()
    {
        try
        {
            Result<void> result;

            setup(result);

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::AES256SignatureCryptographer::setup()",
                exception.what()
            );
   
            return false;
        }
    }

    void AES256SignatureCryptographer::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    std::future<bool> AES256SignatureCryptographer::setup_async()
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup()
                );
            }
        );

        return future;
    }

    void AES256SignatureCryptographer::setup_async(
        const std::function<void(const bool& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                callback(
                    setup()
                );
            }
        );
    }

    void AES256SignatureCryptographer::setup_async(
        Result<std::future<void>>& result
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(result);

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void AES256SignatureCryptographer::setup_async(
        const std::function<void(Result<void>& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;

                setup(result);

                callback(
                    result
                );
            }
        );
    }

	std::string AES256SignatureCryptographer::reverse(
		const std::string& va,
		const std::string& vb
    )
	{
		return reverse(
			va,
			reinterpret_cast<unsigned char*>(const_cast<char*>(vb.data()))
		);
	}

	std::string AES256SignatureCryptographer::transform(
		const std::string& va,
		const std::string& vb,
		const std::string& vc
    )
	{
		return transform(
			va,
			reinterpret_cast<unsigned char*>(const_cast<char*>(vb.data())),
			reinterpret_cast<unsigned char*>(const_cast<char*>(vc.data()))
		);
	}

	std::future<std::string> AES256SignatureCryptographer::reverse_async(
		const std::string& va,
		const std::string& vb
    )
	{
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, va, vb,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    reverse(
                        va,
                        vb
                    )
                );
            }
        );

        return future;
	}

	std::future<std::string> AES256SignatureCryptographer::transform_async(
		const std::string& va,
		const std::string& vb,
		const std::string& vc
    )
	{
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, va, vb, vc,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    transform(
                        va,
                        vb,
                        vc
                    )
                );
            }
        );

        return future;
	}

	std::string AES256SignatureCryptographer::transform(
		const std::string& va,
		unsigned char* vb,
		unsigned char* vc
    )
	{
		try
		{
			std::scoped_lock lock(_mutex);

			if (!vb || !vc)
			{
				return "";
			}

			crypto_sign_keypair(vb, vc);

			const unsigned char* vd =
				reinterpret_cast<const unsigned char*>(va.data());
			unsigned long long ve = va.size(), vf;

			std::vector<unsigned char> vg(ve + crypto_sign_BYTES);
			unsigned char* vh = vg.data();

			crypto_sign(vh, &vf, vd, ve, vc);

			return ENCODER.from_bytes_to_base64(vh, vf);
		}
		catch (const std::exception& exception)
		{
            LOGGER.handle_exception_async(
                "QLogicaeCore::AES256SignatureCryptographer::transform()",
                exception.what()
            );

			throw std::runtime_error(
				std::string("QLogicaeCore::AES256SignatureCryptographer::transform() - ") +
                exception.what()
            );
        }
    }

    std::string AES256SignatureCryptographer::reverse(
        const std::string& va,
        unsigned char* vb
    )
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!vb)
            {
                return "";
            }

            std::vector<unsigned char> vc =
                ENCODER.from_base64_to_bytes(va);
            unsigned long long ve, vh = vc.size();
            std::vector<unsigned char> vd(vh);
            unsigned char* vf = vd.data(), * vg = vc.data();

            if (crypto_sign_open(vf, &ve, vc.data(), vh, vb) != 0)
            {
                return "";
            }

            return std::string(reinterpret_cast<const char*>(vf), ve);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::AES256SignatureCryptographer::reverse()",
                exception.what()
            );

            throw std::runtime_error(
                std::string("QLogicaeCore::AES256SignatureCryptographer::reverse() - ") +
				exception.what()
			);
		}
	}

	std::future<std::string> AES256SignatureCryptographer::reverse_async(
		const std::string& va,
		unsigned char* vb
    )
	{
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, va, vb,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    reverse(
                        va,
                        vb
                    )
                );
            }
        );

        return future;
	}

	std::future<std::string> AES256SignatureCryptographer::transform_async(
		const std::string& va,
		unsigned char* vb,
		unsigned char* vc
    )
	{
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, va, vb, vc,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    transform(
                        va,
                        vb,
                        vc
                    )
                );
            }
        );

        return future;
	}

    void AES256SignatureCryptographer::reverse(
        Result<std::string>& result,
        const std::string& cipher,
        unsigned char* public_key
    )
    {
        std::scoped_lock lock(_mutex);

        if (!public_key)
        {
            return result.set_to_bad_status_with_value(
                "Empty public key"
            );
        }

        std::vector<unsigned char> decoded =
            ENCODER.from_base64_to_bytes(cipher);
        unsigned long long message_len, cipher_len = decoded.size();
        std::vector<unsigned char> message(cipher_len);
        unsigned char* message_ptr = message.data();

        if (crypto_sign_open(
            message_ptr, &message_len,
            decoded.data(), cipher_len,
            public_key
        ) != 0)
        {
            return result.set_to_bad_status_with_value(
                "Decryption failed"
            );
        }

        result.set_to_good_status_with_value(
            std::string(
                reinterpret_cast<const char*>(message_ptr),
                message_len
            )
        );
    }

    void AES256SignatureCryptographer::reverse(
        Result<std::string>& result,
        const std::string& cipher,
        const std::string& public_key
    )
    {
        reverse(
            result,
            cipher,
            reinterpret_cast<unsigned char*>(
                const_cast<char*>(public_key.data())
                )
        );
    }

    void AES256SignatureCryptographer::transform(
        Result<std::string>& result,
        const std::string& text,
        unsigned char* public_key,
        unsigned char* private_key
    )
    {
        std::scoped_lock lock(_mutex);

        if (!public_key || !private_key)
        {            
            return result.set_to_bad_status_with_value(
                "Empty public key or private key"
            );
        }

        crypto_sign_keypair(public_key, private_key);

        const unsigned char* text_ptr =
            reinterpret_cast<const unsigned char*>(text.data());
        unsigned long long text_len = text.size(), signed_len;

        std::vector<unsigned char> signed_data(
            text_len + crypto_sign_BYTES
        );
        unsigned char* signed_ptr = signed_data.data();

        crypto_sign(
            signed_ptr, &signed_len,
            text_ptr, text_len,
            private_key
        );

        ENCODER.from_bytes_to_base64(result, signed_ptr, signed_len);
    }

    void AES256SignatureCryptographer::transform(
        Result<std::string>& result,
        const std::string& text,
        const std::string& public_key,
        const std::string& private_key
    )
    {
        transform(
            result,
            text,
            reinterpret_cast<unsigned char*>(
                const_cast<char*>(public_key.data())
                ),
            reinterpret_cast<unsigned char*>(
                const_cast<char*>(private_key.data())
                )
        );
    }

    void AES256SignatureCryptographer::reverse_async(
        Result<std::future<std::string>>& result,
        const std::string& cipher,
        unsigned char* public_key
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, cipher, public_key,
            promise = std::move(promise)]() mutable
            {
                Result<std::string> result;

                reverse(
                    result,
                    cipher,
                    public_key
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

    void AES256SignatureCryptographer::reverse_async(
        Result<std::future<std::string>>& result,
        const std::string& cipher,
        const std::string& public_key
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, cipher, public_key,
            promise = std::move(promise)]() mutable
            {
                Result<std::string> result;

                reverse(
                    result,
                    cipher,
                    public_key
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

    void AES256SignatureCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        const std::string& text,
        unsigned char* public_key,
        unsigned char* private_key
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, text, public_key, private_key,
            promise = std::move(promise)]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    text,
                    public_key,
                    private_key
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
    
    void AES256SignatureCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        const std::string& text,
        const std::string& public_key,
        const std::string& private_key
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, text, public_key, private_key,
            promise = std::move(promise)]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    text,
                    public_key,
                    private_key
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

    void AES256SignatureCryptographer::reverse_async(
        const std::function<void(const std::string& result)>& callback,
        const std::string& cipher,
        unsigned char* public_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, cipher, public_key, callback]() mutable
            {
                callback(
                    reverse(
                        cipher,
                        public_key
                    )
                );
            }
        );
    }

    void AES256SignatureCryptographer::transform_async(
        const std::function<void(const std::string& result)>& callback,
        const std::string& text,
        unsigned char* public_key,
        unsigned char* private_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, text, public_key, private_key]() mutable
            {
                callback(
                    transform(
                        text,
                        public_key,
                        private_key
                    )
                );
            }
        );
    }

    void AES256SignatureCryptographer::reverse_async(
        const std::function<void(const std::string& result)>& callback,
        const std::string& cipher,
        const std::string& public_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, cipher, public_key, callback]() mutable
            {
                callback(
                    reverse(
                        cipher,
                        public_key
                    )
                );
            }
        );
    }

    void AES256SignatureCryptographer::transform_async(
        const std::function<void(const std::string& result)>& callback,
        const std::string& text,
        const std::string& public_key,
        const std::string& private_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, text, public_key, private_key]() mutable
            {
                callback(
                    transform(
                        text,
                        public_key,
                        private_key
                    )
                );
            }
        );
    }

    void AES256SignatureCryptographer::reverse_async(
        const std::function<void(Result<std::string>& result)>& callback,
        const std::string& cipher,
        unsigned char* public_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, cipher, public_key]() mutable
            {
                Result<std::string> result;
                
                reverse(
                    result,
                    cipher,
                    public_key
                );

                callback(
                    result
                );
            }
        );
    }

    void AES256SignatureCryptographer::transform_async(
        const std::function<void(Result<std::string>& result)>& callback,
        const std::string& text,
        unsigned char* public_key,
        unsigned char* private_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, text, public_key, private_key]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    text,
                    public_key,
                    private_key
                );

                callback(
                    result
                );
            }
        );
    }

    void AES256SignatureCryptographer::reverse_async(
        const std::function<void(Result<std::string>& result)>& callback,
        const std::string& cipher,
        const std::string& public_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, cipher, public_key]() mutable
            {
                Result<std::string> result;

                reverse(
                    result,
                    cipher,
                    public_key
                );

                callback(
                    result
                );
            }
        );
    }

    void AES256SignatureCryptographer::transform_async(
        const std::function<void(Result<std::string>& result)>& callback,
        const std::string& text,
        const std::string& public_key,
        const std::string& private_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, text, public_key, private_key]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    text,
                    public_key,
                    private_key
                );

                callback(
                    result
                );
            }
        );
    }

    AES256SignatureCryptographer& AES256SignatureCryptographer::get_instance()
    {
        static AES256SignatureCryptographer instance;

        return instance;
    }

    void AES256SignatureCryptographer::get_instance(
        QLogicaeCore::Result<AES256SignatureCryptographer*>& result
    )
    {
        static AES256SignatureCryptographer instance;

        result.set_to_good_status_with_value(&instance);
    }
}

