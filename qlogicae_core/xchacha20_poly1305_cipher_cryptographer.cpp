#include "pch.hpp"

#include "xchacha20_poly1305_cipher_cryptographer.hpp"

namespace QLogicaeCore
{
	XChaCha20Poly1305CipherCryptographer::XChaCha20Poly1305CipherCryptographer() :
        Cryptographer()
	{

	}

    bool XChaCha20Poly1305CipherCryptographer::setup()
    {      
        Result<void> result;

        setup(result);

        return result.is_status_safe();
    }

    void XChaCha20Poly1305CipherCryptographer::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    std::future<bool> XChaCha20Poly1305CipherCryptographer::setup_async()
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

    void XChaCha20Poly1305CipherCryptographer::setup_async(
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

    void XChaCha20Poly1305CipherCryptographer::setup_async(
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

    void XChaCha20Poly1305CipherCryptographer::setup_async(
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

    std::string XChaCha20Poly1305CipherCryptographer::reverse(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc
    )
    {
        return reverse(va,
            reinterpret_cast<const unsigned char*>(vb.data()),
            reinterpret_cast<const unsigned char*>(vc.data())
        );
    }

    std::string XChaCha20Poly1305CipherCryptographer::transform(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc
    )
    {
        return transform(va,
            reinterpret_cast<const unsigned char*>(vb.data()),
            reinterpret_cast<const unsigned char*>(vc.data())
        );
    }

    std::future<std::string> XChaCha20Poly1305CipherCryptographer::reverse_async(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc
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
                    reverse(
                        va,
                        vb,
                        vc
                    )
                );
            }
        );
    }

    std::future<std::string> XChaCha20Poly1305CipherCryptographer::transform_async(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc
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
    }

    std::string XChaCha20Poly1305CipherCryptographer::transform(
        const std::string_view& va,
        const unsigned char* vb,
        const unsigned char* vc
    )
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!vb || !vc)
            {
                return "";
            }

            unsigned long long ve = 0, vg = va.size();
            std::vector<unsigned char> vd(
                vg + crypto_aead_xchacha20poly1305_ietf_ABYTES
            );
            unsigned char* vf = vd.data();

            if (crypto_aead_xchacha20poly1305_ietf_encrypt(
                vf, &ve,
                reinterpret_cast<const unsigned char*>(va.data()), vg,
                nullptr, 0, nullptr, vc, vb) != 0)
            {
                return "";
            }

            return ENCODER
                .from_bytes_to_base64(vf, ve);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at XChaCha20Poly1305CipherCryptographer::transform(): ") +
                exception.what()
            );
        }
    }

    std::string XChaCha20Poly1305CipherCryptographer::reverse(
        const std::string_view& va,
        const unsigned char* vb,
        const unsigned char* vc
    )
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!vb || !vc ||
                va.size() < crypto_aead_xchacha20poly1305_ietf_ABYTES)
            {
                return "";
            }

            unsigned long long ve = 0;
            std::vector<unsigned char> vd =
                ENCODER.from_base64_to_bytes(va);
            size_t vf = vd.size();
            std::vector<unsigned char> decrypted(
                vf - crypto_aead_xchacha20poly1305_ietf_ABYTES
            );

            if (crypto_aead_xchacha20poly1305_ietf_decrypt(
                decrypted.data(), &ve,
                nullptr,
                vd.data(), vf,
                nullptr, 0, vc, vb) != 0)
            {
                return "";
            }

            return std::string(
                reinterpret_cast<char*>(decrypted.data()), ve
            );
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at XChaCha20Poly1305CipherCryptographer::reverse(): ") +
                exception.what()
            );
        }
    }

    std::future<std::string> XChaCha20Poly1305CipherCryptographer::reverse_async(
        const std::string_view& va,
        const unsigned char* vb,
        const unsigned char* vc
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
                    reverse(
                        va,
                        vb,
                        vc
                    )
                );
            }
        );

        return future;
    }

    std::future<std::string> XChaCha20Poly1305CipherCryptographer::transform_async(
        const std::string_view& va,
        const unsigned char* vb,
        const unsigned char* vc
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

    void XChaCha20Poly1305CipherCryptographer::reverse(
        Result<std::string>& result,
        const std::string_view& cipher,
        const unsigned char* key,
        const unsigned char* nonce
    )
    {
        std::scoped_lock lock(_mutex);

        if (!key || !nonce ||
            cipher.size() < crypto_aead_xchacha20poly1305_ietf_ABYTES)
        {
            return result.set_to_bad_status_with_value(
                "Key, or nonce is null or cipher size is less than 32"
            );
        }

        unsigned long long ve = 0;
        std::vector<unsigned char> vd =
            ENCODER.from_base64_to_bytes(cipher);
        size_t vf = vd.size();
        std::vector<unsigned char> decrypted(
            vf - crypto_aead_xchacha20poly1305_ietf_ABYTES
        );

        if (crypto_aead_xchacha20poly1305_ietf_decrypt(
            decrypted.data(), &ve,
            nullptr,
            vd.data(), vf,
            nullptr, 0, nonce, key) != 0)
        {
            return result.set_to_bad_status_with_value(
                "Decryption failed"
            );
        }

        result.set_to_good_status_with_value(std::string(
            reinterpret_cast<char*>(decrypted.data()), ve
        ));
        
    }

    void XChaCha20Poly1305CipherCryptographer::transform(
        Result<std::string>& result,
        const std::string_view& text,
        const unsigned char* key,
        const unsigned char* nonce
    )
    {
        std::scoped_lock lock(_mutex);

        if (!key || !nonce)
        {
            return result.set_to_bad_status_with_value(
                "Key or nonce is null"
            );
        }

        unsigned long long ve = 0, vg = text.size();
        std::vector<unsigned char> vd(
            vg + crypto_aead_xchacha20poly1305_ietf_ABYTES
        );
        unsigned char* vf = vd.data();

        if (crypto_aead_xchacha20poly1305_ietf_encrypt(
            vf, &ve,
            reinterpret_cast<const unsigned char*>(text.data()), vg,
            nullptr, 0, nullptr, nonce, key) != 0)
        {
            result.set_to_bad_status_with_value("");
        }

        ENCODER.from_bytes_to_base64(result, vf, ve);        
    }

    void XChaCha20Poly1305CipherCryptographer::reverse(
        Result<std::string>& result,
        const std::string_view& cipher,
        const std::string_view& key,
        const std::string_view& nonce
    )
    {
        result.set_to_good_status_with_value(reverse(cipher,
            reinterpret_cast<const unsigned char*>(key.data()),
            reinterpret_cast<const unsigned char*>(nonce.data())
        ));
    }

    void XChaCha20Poly1305CipherCryptographer::transform(
        Result<std::string>& result,
        const std::string_view& text,
        const std::string_view& key,
        const std::string_view& nonce
    )
    {
        result.set_to_good_status_with_value(transform(text,
            reinterpret_cast<const unsigned char*>(key.data()),
            reinterpret_cast<const unsigned char*>(nonce.data())
        ));
    }

    void XChaCha20Poly1305CipherCryptographer::reverse_async(
        Result<std::future<std::string>>& result,
        const std::string_view& cipher,
        const unsigned char* key,
        const unsigned char* nonce
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, cipher, key, nonce,
            promise = std::move(promise)]() mutable
            {
                Result<std::string> result;

                reverse(
                    result,
                    cipher,
                    key,
                    nonce
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

    void XChaCha20Poly1305CipherCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        const std::string_view& text,
        const unsigned char* key,
        const unsigned char* nonce
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, text, key, nonce,
            promise = std::move(promise)]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    text,
                    key,
                    nonce
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

    void XChaCha20Poly1305CipherCryptographer::reverse_async(
        Result<std::future<std::string>>& result,
        const std::string_view& cipher,
        const std::string_view& key,
        const std::string_view& nonce
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, cipher, key, nonce,
            promise = std::move(promise)]() mutable
            {
                Result<std::string> result;

                reverse(
                    result,
                    cipher,
                    key,
                    nonce
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

    void XChaCha20Poly1305CipherCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        const std::string_view& text,
        const std::string_view& key,
        const std::string_view& nonce
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, text, key, nonce,
            promise = std::move(promise)]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    text,
                    key,
                    nonce
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

    void XChaCha20Poly1305CipherCryptographer::reverse_async(
        const std::function<void(const std::string& result)>& callback,
        const std::string& cipher,
        const unsigned char* key,
        const unsigned char* nonce
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, cipher, key, nonce, callback]() mutable
            {
                callback(
                    reverse(
                        cipher,
                        key,
                        nonce
                    )
                );
            }
        );
    }

    void XChaCha20Poly1305CipherCryptographer::transform_async(
        const std::function<void(const std::string& result)>& callback,
        const std::string& text,
        const unsigned char* key,
        const unsigned char* nonce
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, text, key, nonce, callback]() mutable
            {
                callback(
                    transform(
                        text,
                        key,
                        nonce
                    )
                );
            }
        );
    }

    void XChaCha20Poly1305CipherCryptographer::reverse_async(
        const std::function<void(const std::string& result)>& callback,
        const std::string& cipher,
        const std::string& key,
        const std::string& nonce
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, cipher, key, nonce, callback]() mutable
            {
                callback(
                    reverse(
                        cipher,
                        key,
                        nonce
                    )
                );
            }
        );
    }

    void XChaCha20Poly1305CipherCryptographer::transform_async(
        const std::function<void(const std::string& result)>& callback,
        const std::string& text,
        const std::string& key,
        const std::string& nonce
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, text, key, nonce, callback]() mutable
            {
                callback(
                    transform(
                        text,
                        key,
                        nonce
                    )
                );
            }
        );
    }

    void XChaCha20Poly1305CipherCryptographer::reverse_async(
        const std::function<void(Result<std::string>& result)>& callback,
        const std::string& cipher,
        const unsigned char* key,
        const unsigned char* nonce
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, cipher, key, nonce, callback]() mutable
            {
                Result<std::string> result;

                reverse(
                    result,
                    cipher,
                    key,
                    nonce
                );

                callback(
                    result
                );
            }
        );
    }

    void XChaCha20Poly1305CipherCryptographer::transform_async(
        const std::function<void(Result<std::string>& result)>& callback,
        const std::string& text,
        const unsigned char* key,
        const unsigned char* nonce
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, text, key, nonce, callback]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    text,
                    key,
                    nonce
                );

                callback(
                    result
                );
            }
        );
    }

    void XChaCha20Poly1305CipherCryptographer::reverse_async(
        const std::function<void(Result<std::string>& result)>& callback,
        const std::string& cipher,
        const std::string& key,
        const std::string& nonce
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, cipher, key, nonce, callback]() mutable
            {
                Result<std::string> result;

                reverse(
                    result,
                    cipher,
                    key,
                    nonce
                );

                callback(
                    result
                );
            }
        );
    }

    void XChaCha20Poly1305CipherCryptographer::transform_async(
        const std::function<void(Result<std::string>& result)>& callback,
        const std::string& text,
        const std::string& key,
        const std::string& nonce
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, text, key, nonce, callback]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    text,
                    key,
                    nonce
                );

                callback(
                    result
                );
            }
        );
    }

    XChaCha20Poly1305CipherCryptographer& XChaCha20Poly1305CipherCryptographer::get_instance()
    {
        static XChaCha20Poly1305CipherCryptographer instance;

        return instance;
    }

    void XChaCha20Poly1305CipherCryptographer::get_instance(
        Result<XChaCha20Poly1305CipherCryptographer*>& result
    )
    {
        static XChaCha20Poly1305CipherCryptographer instance;

        result.set_to_good_status_with_value(&instance);
    }
}
