#include "pch.h"

#include "aes256_cipher_cryptographer.hpp"

namespace QLogicaeCore
{
	AES256CipherCryptographer::AES256CipherCryptographer() :
		Cryptographer()
	{

	}

	std::string AES256CipherCryptographer::reverse(
		const std::string_view& va,
		const std::string_view& vb,
		const std::string_view& vc) const
	{
		return reverse(va,
			reinterpret_cast<const unsigned char*>(vb.data()),
			reinterpret_cast<const unsigned char*>(vc.data())
		);
	}

	std::string AES256CipherCryptographer::transform(
		const std::string_view& va,
		const std::string_view& vb,
		const std::string_view& vc) const
	{
		return transform(va,
			reinterpret_cast<const unsigned char*>(vb.data()),
			reinterpret_cast<const unsigned char*>(vc.data())
		);
	}

	std::future<std::string> AES256CipherCryptographer::reverse_async(
		const std::string_view& va,
		const std::string_view& vb,
		const std::string_view& vc) const
	{
		return std::async(std::launch::async,
			[this, va, vb, vc]() -> std::string
			{
				return reverse(va, vb, vc);				
			});
	}

	std::future<std::string> AES256CipherCryptographer::transform_async(
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

	std::string AES256CipherCryptographer::transform(
		const std::string_view& va,
		const unsigned char* vb,
		const unsigned char* vc) const
	{
		try
		{
			std::scoped_lock lock(_mutex);

			if (!vb || !vc)
			{
				return "";
			}

			unsigned long long ve = va.size(), vg;
			const unsigned char* vd = reinterpret_cast<const unsigned char*>(
				va.data()
			);


			std::vector<unsigned char> vf(
				ve + crypto_aead_aes256gcm_ABYTES
			);
			unsigned char* vh = vf.data();

			crypto_aead_aes256gcm_encrypt(
				vh, &vg, vd, ve,
				nullptr, 0, nullptr,
				vc, vb
			);

			return ENCODER.from_bytes_to_base64(
				vh, vg
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("Exception at AES256CipherCryptographer::transform(): ") +
				exception.what()
			);
		}
	}

	std::string AES256CipherCryptographer::reverse(
		const std::string_view& va,
		const unsigned char* vb,
		const unsigned char* vc) const
	{
		try
		{
			std::scoped_lock lock(_mutex);

			if (!vb || !vc)
			{
				return "";
			}

			std::vector<unsigned char> vf =
				ENCODER.from_base64_to_bytes(va);
			unsigned long long vh, vi = vf.size();
			std::vector<unsigned char> vg(vi);
			unsigned char* vj = vg.data();

			if (crypto_aead_aes256gcm_decrypt(
				vj, &vh, nullptr,
				vf.data(), vi,
				nullptr, 0, vc, vb) != 0)
			{
				return "";
			}
			return std::string(
				reinterpret_cast<const char*>(vj), vh
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("Exception at AES256CipherCryptographer::reverse(): ") +
				exception.what()
			);
		}
	}

	std::future<std::string> AES256CipherCryptographer::reverse_async(
		const std::string_view& va,
		const unsigned char* vb,
		const unsigned char* vc) const
	{
		return std::async(std::launch::async, [this, va, vb, vc]() -> std::string
		{
			return reverse(va, vb, vc);			
		});
	}

	std::future<std::string> AES256CipherCryptographer::transform_async(
		const std::string_view& va,
		const unsigned char* vb,
		const unsigned char* vc) const
	{
		return std::async(std::launch::async, [this, va, vb, vc]() -> std::string
		{
			return transform(va, vb, vc);			
		});
	}
}
