#include "pch.hpp"

#include "aes256_cipher_cryptographer.hpp"

namespace QLogicaeCore
{
	AES256CipherCryptographer::AES256CipherCryptographer() :
		Cryptographer()
	{

	}

	bool AES256CipherCryptographer::setup()
	{
		Result<void> result;

		setup(result);

		return result.is_status_safe();
	}

	void AES256CipherCryptographer::setup(
		Result<void>& result
	)
	{
		result.set_to_good_status_without_value();
	}

	std::future<bool> AES256CipherCryptographer::setup_async()
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

	void AES256CipherCryptographer::setup_async(
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

	void AES256CipherCryptographer::setup_async(
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

	void AES256CipherCryptographer::setup_async(
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

	std::string AES256CipherCryptographer::reverse(
		const std::string& va,
		const std::string& vb,
		const std::string& vc
	)
	{
		return reverse(va,
			reinterpret_cast<const unsigned char*>(vb.data()),
			reinterpret_cast<const unsigned char*>(vc.data())
		);
	}

	std::string AES256CipherCryptographer::transform(
		const std::string& va,
		const std::string& vb,
		const std::string& vc
	)
	{
		return transform(va,
			reinterpret_cast<const unsigned char*>(vb.data()),
			reinterpret_cast<const unsigned char*>(vc.data())
		);
	}

	std::future<std::string> AES256CipherCryptographer::reverse_async(
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

	std::future<std::string> AES256CipherCryptographer::transform_async(
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

	std::string AES256CipherCryptographer::transform(
		const std::string& va,
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

	std::future<std::string> AES256CipherCryptographer::transform_async(
		const std::string& va,
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



	void AES256CipherCryptographer::reverse(
		Result<std::string>& result,
		const std::string& cipher,
		const std::string& key,
		const std::string& nonce
	)
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
	)
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
	)
	{
		std::scoped_lock lock(_mutex);

		if (!key || !nonce)
		{			
			return result.set_to_bad_status_without_value(
				"Empty key or nonce"
			);
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
			return result.set_to_bad_status_without_value(
				"Decryption failed"
			);
		}

		result.set_to_good_status_with_value(
			std::string(reinterpret_cast<const char*>(out_ptr), out_len)
		);
	}

	void AES256CipherCryptographer::transform(
		Result<std::string>& result,
		const std::string& text,
		const unsigned char* key,
		const unsigned char* nonce
	)
	{
		std::scoped_lock lock(_mutex);

		if (!key || !nonce)
		{
			return result.set_to_bad_status_without_value(
				"Empty key or nonce"
			);
		}

		unsigned long long text_len = text.size(), cipher_len;
		const unsigned char* text_ptr =
			reinterpret_cast<const unsigned char*>(text.data());
		std::vector<unsigned char> cipher_buf(
			text_len + crypto_aead_aes256gcm_ABYTES
		);
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

	void AES256CipherCryptographer::transform_async(
		Result<std::future<std::string>>& result,
		const std::string& text,
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

	void AES256CipherCryptographer::reverse_async(
		Result<std::future<std::string>>& result,
		const std::string& cipher,
		const std::string& key,
		const std::string& nonce
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

	void AES256CipherCryptographer::transform_async(
		Result<std::future<std::string>>& result,
		const std::string& text,
		const std::string& key,
		const std::string& nonce
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

	void AES256CipherCryptographer::reverse_async(
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

	void AES256CipherCryptographer::transform_async(
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

	void AES256CipherCryptographer::reverse_async(
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

	void AES256CipherCryptographer::transform_async(
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

	void AES256CipherCryptographer::reverse_async(
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

	void AES256CipherCryptographer::transform_async(
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

	void AES256CipherCryptographer::reverse_async(
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

	void AES256CipherCryptographer::transform_async(
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

	AES256CipherCryptographer& AES256CipherCryptographer::get_instance()
	{
		static AES256CipherCryptographer instance;

		return instance;
	}

	void AES256CipherCryptographer::get_instance(
		QLogicaeCore::Result<AES256CipherCryptographer*>& result
	)
	{
		static AES256CipherCryptographer instance;

		result.set_to_good_status_with_value(&instance);
	}
}
