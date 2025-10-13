#include "pch.hpp"

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

		return ENCODER.from_bytes_to_base64(
			digest,
			crypto_hash_sha256_BYTES
		);
	}

	bool SHA256HashCryptographer::reverse(
		const std::string& va, const std::string& vb
	) const
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

	void SHA256HashCryptographer::transform(
		Result<std::string> result,
		const std::string& text
	) const
	{
		if (text.empty())
		{
			result.set_to_failure("");
			return;
		}

		unsigned char digest[crypto_hash_sha256_BYTES];

		if (crypto_hash_sha256(
			digest,
			reinterpret_cast<const unsigned char*>(text.data()),
			text.size()) != 0)
		{
			result.set_to_failure("");
			return;
		}

		result.set_to_success(
			ENCODER.from_bytes_to_base64(
				digest,
				crypto_hash_sha256_BYTES
			)
		);
	}

	void SHA256HashCryptographer::reverse(
		Result<void> result,
		const std::string& cipher,
		const std::string& key
	) const
	{
		if (cipher.empty() ||
			key.empty())
		{
			result.set_to_failure();
			return;
		}

		const std::string computed_base64_hash = transform(cipher);
		if (computed_base64_hash.empty())
		{
			result.set_to_failure();
			return;
		}

		result.set_is_successful(
			sodium_memcmp(
				computed_base64_hash.data(),
				key.data(),
				key.size()
			) == 0
		);
	}

	void SHA256HashCryptographer::transform_async(
		Result<std::future<std::string>> result,
		const std::string& text
	) const
	{
		result.set_to_success(std::async(std::launch::async, [this, text]() -> std::string
			{
				Result<std::string> result;
				transform(result, text);

				return result.get_data();
			}
		));		
	}

	void SHA256HashCryptographer::reverse_async(
		Result<std::future<void>> result,
		const std::string& cipher,
		const std::string& key
	) const
	{
		result.set_to_success(std::async(std::launch::async, [this, cipher, key]() -> void
			{
				Result<void> result;
				reverse(result, cipher, key);			
			}
		));
	}
}

