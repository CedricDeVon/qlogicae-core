#include "pch.h"

#include "sha256_hash_cryptographer.hpp"

namespace QLogicaeCore
{
	SHA256HashCryptographer::SHA256HashCryptographer() :
		Cryptographer()
	{
	}

	std::string SHA256HashCryptographer::transform(
		const std::string& va) const
	{
		try
		{
			if (va.empty())
			{
				return "";
			}

			unsigned char digest[crypto_hash_sha256_BYTES];

			if (crypto_hash_sha256(
				digest,
				reinterpret_cast<const unsigned char*>(va.data()),
				va.size()) != 0)
			{
				return "";
			}

			return QLogicaeCore::Encoder::get_instance()
				.from_bytes_to_base64(
					digest,
					crypto_hash_sha256_BYTES
				);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(std::string() + "Exception at SHA256HashCryptographer::transform(): " + exception.what());
		}
	}

	bool SHA256HashCryptographer::reverse(
		const std::string& va, const std::string& vb
	) const
	{
		try
		{
			if (va.empty() ||
				vb.empty())
			{
				return false;
			}

			const std::string computed_base64_hash = transform(va);
			if (computed_base64_hash.empty())
			{
				return false;
			}

			return sodium_memcmp(
				computed_base64_hash.data(),
				vb.data(),
				vb.size()) == 0;
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(std::string() + "Exception at SHA256HashCryptographer::reverse(): " + exception.what());
		}
	}


	std::future<bool> SHA256HashCryptographer::reverse_async(
		const std::string& va,
		const std::string& vb) const
	{
		return std::async(std::launch::async, [this, va, vb]() -> bool
			{
				return reverse(va, vb);				
			});
	}

	std::future<std::string> SHA256HashCryptographer::transform_async(
		const std::string& va) const
	{
		return std::async(std::launch::async, [this, va]() -> std::string
			{
				return transform(va);				
			});
	}
}

