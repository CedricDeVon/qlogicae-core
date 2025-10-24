#include "pch.hpp"

#include "sha256_hash_cryptographer.hpp"

namespace QLogicaeCore
{
	SHA256HashCryptographer::SHA256HashCryptographer() :
		Cryptographer()
	{
	}

	bool SHA256HashCryptographer::setup()
	{
		Result<void> result;

		setup(result);

		return result.is_status_safe();
	}

	void SHA256HashCryptographer::setup(
		Result<void>& result
	)
	{
		result.set_to_good_status_without_value();
	}

	std::future<bool> SHA256HashCryptographer::setup_async()
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

	void SHA256HashCryptographer::setup_async(
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

	void SHA256HashCryptographer::setup_async(
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

	void SHA256HashCryptographer::setup_async(
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

	std::string SHA256HashCryptographer::transform(
		const std::string& va)
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
	)
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
		const std::string& vb
	)
	{
		std::promise<bool> promise;
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

	std::future<std::string> SHA256HashCryptographer::transform_async(
		const std::string& va
	)
	{
		std::promise<std::string> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, va,
			promise = std::move(promise)]() mutable
			{
				promise.set_value(
					transform(
						va
					)
				);
			}
		);

		return future;
	}

	void SHA256HashCryptographer::transform(
		Result<std::string> result,
		const std::string& text
	)
	{
		if (text.empty())
		{			
			return result.set_to_bad_status_with_value(
				"Text is empty"
			);
		}

		unsigned char digest[crypto_hash_sha256_BYTES];

		if (crypto_hash_sha256(
			digest,
			reinterpret_cast<const unsigned char*>(text.data()),
			text.size()) != 0)
		{			
			return result.set_to_bad_status_with_value(
				"Encryption failed"
			);
		}

		ENCODER.from_bytes_to_base64(
			result,
			digest,
			crypto_hash_sha256_BYTES
		);
	}

	void SHA256HashCryptographer::reverse(
		Result<bool> result,
		const std::string& cipher,
		const std::string& key
	)
	{
		if (cipher.empty() ||
			key.empty())
		{
			return result.set_to_bad_status_without_value(
				"Cipher or key is empty"
			);
		}

		const std::string computed_base64_hash =
			transform(cipher);
		if (computed_base64_hash.empty())
		{
			return result.set_to_bad_status_without_value(
				"Decryption failed"
			);
		}

		if (sodium_memcmp(
			computed_base64_hash.data(),
			key.data(),
			key.size()
		) == 0)
		{
			result.set_to_good_status_with_value(
				true
			);
		}
		else
		{
			result.set_to_good_status_with_value(
				false
			);
		}
	}

	void SHA256HashCryptographer::transform_async(
		Result<std::future<std::string>> result,
		const std::string& text
	)
	{
		std::promise<std::string> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text,
			promise = std::move(promise)]() mutable
			{
				Result<std::string> result;

				transform(
					result,
					text
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

	void SHA256HashCryptographer::reverse_async(
		Result<std::future<bool>> result,
		const std::string& cipher,
		const std::string& key
	)
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, cipher, key,
			promise = std::move(promise)]() mutable
			{
				Result<bool> result;

				reverse(
					result,
					cipher,
					key
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

	void SHA256HashCryptographer::reverse_async(
		const std::function<void(const bool& result)>& callback,
		const std::string& hash,
		const std::string& key
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, hash, key, callback]() mutable
			{
				callback(
					reverse(
						hash,
						key
					)
				);
			}
		);
	}

	void SHA256HashCryptographer::transform_async(
		const std::function<void(const std::string& result)>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				callback(
					transform(
						text
					)
				);
			}
		);
	}

	void SHA256HashCryptographer::reverse_async(
		const std::function<void(Result<bool>& result)>& callback,
		const std::string& hash,
		const std::string& key
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, hash, key, callback]() mutable
			{
				Result<bool> result;

				reverse(
					result,
					hash,
					key
				);

				callback(
					result
				);
			}
		);
	}

	void SHA256HashCryptographer::transform_async(
		const std::function<void(Result<std::string>& result)>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				Result<std::string> result;

				transform(
					result,
					text
				);

				callback(
					result
				);
			}
		);
	}

	SHA256HashCryptographer& SHA256HashCryptographer::get_instance()
	{
		static SHA256HashCryptographer instance;

		return instance;
	}

	void SHA256HashCryptographer::get_instance(
		QLogicaeCore::Result<SHA256HashCryptographer*>& result
	)
	{
		static SHA256HashCryptographer instance;

		result.set_to_good_status_with_value(&instance);
	}
}

