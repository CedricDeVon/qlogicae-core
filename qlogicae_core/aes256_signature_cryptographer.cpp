#include "pch.hpp"

#include "aes256_signature_cryptographer.hpp"

namespace QLogicaeCore
{
	AES256SignatureCryptographer::AES256SignatureCryptographer() :
		Cryptographer()
	{

	}

	std::string AES256SignatureCryptographer::reverse(
		const std::string_view& va,
		const std::string_view& vb) const
	{
		return reverse(
			va,
			reinterpret_cast<unsigned char*>(const_cast<char*>(vb.data()))
		);
	}

	std::string AES256SignatureCryptographer::transform(
		const std::string_view& va,
		const std::string_view& vb,
		const std::string_view& vc) const
	{
		return transform(
			va,
			reinterpret_cast<unsigned char*>(const_cast<char*>(vb.data())),
			reinterpret_cast<unsigned char*>(const_cast<char*>(vc.data()))
		);
	}

	std::future<std::string> AES256SignatureCryptographer::reverse_async(
		const std::string_view& va,
		const std::string_view& vb) const
	{
		return std::async(std::launch::async,
			[this, va, vb]() -> std::string
			{
				return reverse(va, vb);				
			});
	}

	std::future<std::string> AES256SignatureCryptographer::transform_async(
		const std::string_view& va,
		const std::string_view& vb,
		const std::string_view& vc) const
	{
		return std::async(std::launch::async,
			[this, va, vb, vc]() -> std::string
			{
				return transform(va, vb, vc);				
			});
	}

	std::string AES256SignatureCryptographer::transform(
		const std::string_view& va,
		unsigned char* vb,
		unsigned char* vc) const
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
			throw std::runtime_error(
				std::string("Exception at AES256SignatureCryptographer::transform(): ") +
				exception.what()
			);
		}
	}

	std::string AES256SignatureCryptographer::reverse(
		const std::string_view& va,
		unsigned char* vb) const
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
			unsigned char* vf = vd.data(), *vg = vc.data();

			if (crypto_sign_open(vf, &ve, vc.data(), vh, vb) != 0)
			{
				return "";
			}

			return std::string(reinterpret_cast<const char*>(vf), ve);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("Exception at AES256SignatureCryptographer::reverse(): ") +
				exception.what()
			);
		}
	}

	std::future<std::string> AES256SignatureCryptographer::reverse_async(
		const std::string_view& va,
		unsigned char* vb) const
	{
		return std::async(std::launch::async, [this, va, vb]() -> std::string
		{
			return reverse(va, vb);			
		});
	}

	std::future<std::string> AES256SignatureCryptographer::transform_async(
		const std::string_view& va,
		unsigned char* vb,
		unsigned char* vc) const
	{
		return std::async(std::launch::async, [this, va, vb, vc]() -> std::string
		{
			return transform(va, vb, vc);			
		});
	}

    void AES256SignatureCryptographer::reverse(
        Result<std::string>& result,
        const std::string_view& cipher,
        unsigned char* public_key
    ) const
    {
        std::scoped_lock lock(_mutex);

        if (!public_key)
        {
            result.set_to_failure("");
            return;
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
            result.set_to_failure("");
            return;
        }

        result.set_to_success(std::string(
            reinterpret_cast<const char*>(message_ptr), message_len
        ));
    }

    void AES256SignatureCryptographer::reverse(
        Result<std::string>& result,
        const std::string_view& cipher,
        const std::string_view& public_key
    ) const
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
        const std::string_view& text,
        unsigned char* public_key,
        unsigned char* private_key
    ) const
    {
        std::scoped_lock lock(_mutex);

        if (!public_key || !private_key)
        {
            result.set_to_failure("");
            return;
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

        result.set_to_success(
            ENCODER.from_bytes_to_base64(signed_ptr, signed_len)
        );
    }

    void AES256SignatureCryptographer::transform(
        Result<std::string>& result,
        const std::string_view& text,
        const std::string_view& public_key,
        const std::string_view& private_key
    ) const
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
        const std::string_view& cipher,
        unsigned char* public_key
    ) const
    {
        result.set_to_success(
            std::async(std::launch::async, [this, cipher, public_key]() -> std::string
            {
                Result<std::string> inner_result;
                reverse(inner_result, cipher, public_key);
                return inner_result.get_data();
            })
        );
    }

    void AES256SignatureCryptographer::reverse_async(
        Result<std::future<std::string>>& result,
        const std::string_view& cipher,
        const std::string_view& public_key
    ) const
    {
        result.set_to_success(
            std::async(std::launch::async, [this, cipher, public_key]() -> std::string
                {
                    Result<std::string> inner_result;
                    reverse(inner_result, cipher, public_key);
                    return inner_result.get_data();
                })
        );
    }

    void AES256SignatureCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        const std::string_view& text,
        unsigned char* public_key,
        unsigned char* private_key
    ) const
    {
        result.set_to_success(
            std::async(std::launch::async, [this, text, public_key, private_key]() -> std::string
                {
                    Result<std::string> inner_result;
                    transform(inner_result, text, public_key, private_key);
                    return inner_result.get_data();
                })
        );
    }

    void AES256SignatureCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        const std::string_view& text,
        const std::string_view& public_key,
        const std::string_view& private_key
    ) const
    {
        result.set_to_success(
            std::async(std::launch::async, [this, text, public_key, private_key]() -> std::string
                {
                    Result<std::string> inner_result;
                    transform(inner_result, text, public_key, private_key);
                    return inner_result.get_data();
                })
        );
    }
}

