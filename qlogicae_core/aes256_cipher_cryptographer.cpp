#include "pch.hpp"

#include "aes256_cipher_cryptographer.hpp"

namespace QLogicaeCore
{
	AES256CipherCryptographer::AES256CipherCryptographer() :
		Cryptographer()
	{

	}

	void AES256CipherCryptographer::setup(Result<void>& result)
	{
		result.set_to_success();
	}

	std::string AES256CipherCryptographer::reverse(
		const std::string& va,
		const std::string& vb,
		const std::string& vc) const
	{
		return reverse(va,
			reinterpret_cast<const unsigned char*>(vb.data()),
			reinterpret_cast<const unsigned char*>(vc.data())
		);
	}

	std::string AES256CipherCryptographer::transform(
		const std::string& va,
		const std::string& vb,
		const std::string& vc) const
	{
		return transform(va,
			reinterpret_cast<const unsigned char*>(vb.data()),
			reinterpret_cast<const unsigned char*>(vc.data())
		);
	}

	std::future<std::string> AES256CipherCryptographer::reverse_async(
		const std::string& va,
		const std::string& vb,
		const std::string& vc) const
	{
		return std::async(std::launch::async,
			[this, va, vb, vc]() -> std::string
			{
				return reverse(va, vb, vc);				
			});
	}

	std::future<std::string> AES256CipherCryptographer::transform_async(
		const std::string& va,
		const std::string& vb,
		const std::string& vc) const
	{
		return std::async(std::launch::async,
			[this, va, vb, vc]() -> std::string
			{
				return transform(va, vb, vc);				
			});
	}

	std::string AES256CipherCryptographer::transform(
		const std::string& va,
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
		const std::string& va,
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
		const std::string& va,
		const unsigned char* vb,
		const unsigned char* vc) const
	{
		return std::async(std::launch::async, [this, va, vb, vc]() -> std::string
		{
			return reverse(va, vb, vc);			
		});
	}

	std::future<std::string> AES256CipherCryptographer::transform_async(
		const std::string& va,
		const unsigned char* vb,
		const unsigned char* vc) const
	{
		return std::async(std::launch::async, [this, va, vb, vc]() -> std::string
		{
			return transform(va, vb, vc);			
		});
	}



	void AES256CipherCryptographer::reverse(
		Result<std::string>& result,
		const std::string& cipher,
		const std::string& key,
		const std::string& nonce
	) const
	{
		reverse(
			result, 
			cipher,
			reinterpret_cast<const unsigned char*>(key.data()),
			reinterpret_cast<const unsigned char*>(nonce.data())
		);
	}

	void AES256CipherCryptographer::transform(
		Result<std::string>& result,
		const std::string& text,
		const std::string& key,
		const std::string& nonce
	) const
	{
		transform(
			result,
			text,
			reinterpret_cast<const unsigned char*>(key.data()),
			reinterpret_cast<const unsigned char*>(nonce.data())
		);
	}

	void AES256CipherCryptographer::reverse(
		Result<std::string>& result,
		const std::string& cipher,
		const unsigned char* key,
		const unsigned char* nonce
	) const
	{
		std::scoped_lock lock(_mutex);

		if (!key || !nonce)
		{
			result.set_to_failure();
			return;
		}

		std::vector<unsigned char> bytes =
			ENCODER.from_base64_to_bytes(cipher);
		unsigned long long out_len, in_len = bytes.size();
		std::vector<unsigned char> decrypted(in_len);
		unsigned char* out_ptr = decrypted.data();

		if (crypto_aead_aes256gcm_decrypt(
			out_ptr, &out_len, nullptr,
			bytes.data(), in_len,
			nullptr, 0, nonce, key) != 0)
		{
			result.set_to_failure();
			return;
		}

		result.set_to_success(
			std::string(reinterpret_cast<const char*>(out_ptr), out_len)
		);
	}

	void AES256CipherCryptographer::transform(
		Result<std::string>& result,
		const std::string& text,
		const unsigned char* key,
		const unsigned char* nonce
	) const
	{
		std::scoped_lock lock(_mutex);

		if (!key || !nonce)
		{
			result.set_to_failure();
			return;
		}

		unsigned long long text_len = text.size(), cipher_len;
		const unsigned char* text_ptr = reinterpret_cast<const unsigned char*>(text.data());
		std::vector<unsigned char> cipher_buf(text_len + crypto_aead_aes256gcm_ABYTES);
		unsigned char* cipher_ptr = cipher_buf.data();

		crypto_aead_aes256gcm_encrypt(
			cipher_ptr, &cipher_len,
			text_ptr, text_len,
			nullptr, 0, nullptr,
			nonce, key
		);

		ENCODER.from_bytes_to_base64(result, cipher_ptr, cipher_len);
	}


	void AES256CipherCryptographer::reverse_async(
		Result<std::future<std::string>>& result,
		const std::string& cipher,
		const unsigned char* key,
		const unsigned char* nonce
	) const
	{
		result.set_to_success(std::async(std::launch::async, [this, cipher, key, nonce]()
			{
				return reverse(cipher, key, nonce);
			})
		);
	}

	void AES256CipherCryptographer::transform_async(
		Result<std::future<std::string>>& result,
		const std::string& text,
		const unsigned char* key,
		const unsigned char* nonce
	) const
	{
		result.set_to_success(std::async(std::launch::async, [this, text, key, nonce]()
			{
				Result<std::string> result;

				transform(result, text, key, nonce);

				return result.get_data();
			})
		);
	}

	void AES256CipherCryptographer::reverse_async(
		Result<std::future<std::string>>& result,
		const std::string& cipher,
		const std::string& key,
		const std::string& nonce
	) const
	{
		result.set_to_success(std::async(std::launch::async, [this, cipher, key, nonce]()
			{
				Result<std::string> result;

				reverse(result, cipher, key, nonce);

				return result.get_data();
			})
		);
	}

	void AES256CipherCryptographer::transform_async(
		Result<std::future<std::string>>& result,
		const std::string& text,
		const std::string& key,
		const std::string& nonce
	) const
	{
		result.set_to_success(std::async(std::launch::async, [this, text, key, nonce]()
			{
				Result<std::string> result;

				transform(
					result,
					text,
					reinterpret_cast<const unsigned char*>(key.data()),
					reinterpret_cast<const unsigned char*>(nonce.data())
				);

				return result.get_data();
			})
		);
	}
}
