#include "pch.hpp"

#include "xchacha20_poly1305_cipher_cryptographer.hpp"

namespace QLogicaeCore
{
	XChaCha20Poly1305CipherCryptographer::XChaCha20Poly1305CipherCryptographer() :
        Cryptographer()
	{

	}

    std::string XChaCha20Poly1305CipherCryptographer::reverse(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc)
    {
        return reverse(va,
            reinterpret_cast<const unsigned char*>(vb.data()),
            reinterpret_cast<const unsigned char*>(vc.data())
        );
    }

    std::string XChaCha20Poly1305CipherCryptographer::transform(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc)
    {
        return transform(va,
            reinterpret_cast<const unsigned char*>(vb.data()),
            reinterpret_cast<const unsigned char*>(vc.data())
        );
    }

    std::future<std::string> XChaCha20Poly1305CipherCryptographer::reverse_async(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc)
    {
        return std::async(std::launch::async,
            [this, va, vb, vc]() -> std::string
        {
            return reverse(va, vb, vc);            
        });
    }

    std::future<std::string> XChaCha20Poly1305CipherCryptographer::transform_async(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc)
    {
        return std::async(std::launch::async,
            [this, va, vb, vc]() -> std::string
        {
            return transform(va, vb, vc);            
        });
    }

    std::string XChaCha20Poly1305CipherCryptographer::transform(
        const std::string_view& va,
        const unsigned char* vb,
        const unsigned char* vc)
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
        const unsigned char* vc)
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
        const unsigned char* vc)
    {
        return std::async(std::launch::async, [this, va, vb, vc]() -> std::string
        {
            return reverse(va, vb, vc);            
        });
    }

    std::future<std::string> XChaCha20Poly1305CipherCryptographer::transform_async(
        const std::string_view& va,
        const unsigned char* vb,
        const unsigned char* vc)
    {
        return std::async(std::launch::async, [this, va, vb, vc]() -> std::string
        {
            return transform(va, vb, vc);            
        });
    }

    void XChaCha20Poly1305CipherCryptographer::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
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
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
                [this, cipher, key, nonce]() -> std::string
                {
                    Result<std::string> result;

                    reverse(result, cipher, key, nonce);

                    return result.get_value();
                })
        );
    }

    void XChaCha20Poly1305CipherCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        const std::string_view& text,
        const unsigned char* key,
        const unsigned char* nonce
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
                [this, text, key, nonce]() -> std::string
                {
                    Result<std::string> result;

                    transform(result, text, key, nonce);

                    return result.get_value();
                })
        );
    }

    void XChaCha20Poly1305CipherCryptographer::reverse_async(
        Result<std::future<std::string>>& result,
        const std::string_view& cipher,
        const std::string_view& key,
        const std::string_view& nonce
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async, [this, cipher, key, nonce]() -> std::string
                {
                    Result<std::string> result;

                    reverse(result, cipher, key, nonce);

                    return result.get_value();
                })
        );
    }

    void XChaCha20Poly1305CipherCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        const std::string_view& text,
        const std::string_view& key,
        const std::string_view& nonce
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async, [this, text, key, nonce]() -> std::string
            {
                    Result<std::string> result;

                    transform(result, text, key, nonce);

                    return result.get_value();
            })
        );
    }
}
