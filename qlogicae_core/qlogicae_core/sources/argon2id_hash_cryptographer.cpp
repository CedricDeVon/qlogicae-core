#include "pch.hpp"

#include "../includes/argon2id_hash_cryptographer.hpp"

namespace QLogicaeCore
{
	Argon2idHashCryptographer::Argon2idHashCryptographer() :
		Cryptographer()
	{
		_cryptographer_properties = DEFAULT_CRYPTOGRAPHER_3_PROPERTIES;
	}

	Argon2idHashCryptographer::Argon2idHashCryptographer(
		const CryptographerProperties& properties
	) :
			Cryptographer()
	{
		_cryptographer_properties = properties;
	}

	bool Argon2idHashCryptographer::setup()
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
				"QLogicaeCore::Argon2idHashCryptographer::setup()",
				exception.what()
			);

			return false;
		}
	}

	void Argon2idHashCryptographer::setup(
		Result<void>& result
	)
	{		
		result.set_to_good_status_without_value();
	}

	bool Argon2idHashCryptographer::setup(
		const CryptographerProperties& properties
	)
	{
		Result<void> result;

		setup(result, properties);

		return result.is_status_safe();
	}

	void Argon2idHashCryptographer::setup(
		Result<void>& result,
		const CryptographerProperties& properties
	)
	{
		_cryptographer_properties = properties;

		result.set_to_good_status_without_value();
	}

	std::future<bool> Argon2idHashCryptographer::setup_async()
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

	void Argon2idHashCryptographer::setup_async(
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

	void Argon2idHashCryptographer::setup_async(
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

	void Argon2idHashCryptographer::setup_async(
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

	std::future<bool> Argon2idHashCryptographer::setup_async(
		const CryptographerProperties& properties
	)
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, properties,
			promise = std::move(promise)]() mutable
			{
				promise.set_value(
					setup(
						properties
					)
				);
			}
		);

		return future;
	}

	void Argon2idHashCryptographer::setup_async(
		const std::function<void(const bool& result)>& callback,
		const CryptographerProperties& properties
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, properties, callback]() mutable
			{
				callback(
					setup(
						properties
					)
				);
			}
		);
	}

	void Argon2idHashCryptographer::setup_async(
		Result<std::future<void>>& result,
		const CryptographerProperties& properties
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, properties,
			promise = std::move(promise)]() mutable
			{
				Result<void> result;

				setup(result, properties);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Argon2idHashCryptographer::setup_async(
		const std::function<void(Result<void>& result)>& callback,
		const CryptographerProperties& properties
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, properties]() mutable
			{
				Result<void> result;

				setup(result, properties);

				callback(
					result
				);
			}
		);
	}

	std::string Argon2idHashCryptographer::transform(
		const std::string& va
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			std::array<char, 512> vb{};
			int vc = argon2id_hash_encoded(
				_cryptographer_properties.uint32_t_1,
				_cryptographer_properties.uint32_t_2,
				_cryptographer_properties.uint32_t_3,
				va.data(),
				va.size(),
				GENERATOR.random_salt().data(),
				_cryptographer_properties.size_t_2,
				_cryptographer_properties.size_t_1,
				vb.data(), vb.size());
			if (vc != ARGON2_OK)
			{
				return "";
			}

			return vb.data();
		}
		catch (const std::exception& exception)
		{
			LOGGER.handle_exception_async(
				"QLogicaeCore::Argon2idHashCryptographer::transform()",
				exception.what()
			);

			return "";
		}
	}

	std::future<std::string> Argon2idHashCryptographer::transform_async(
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

	bool Argon2idHashCryptographer::reverse(
		const std::string& va,
		const std::string& vb
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			return argon2id_verify(
				va.data(), vb.data(), vb.size()
			) == ARGON2_OK;
		}
		catch (const std::exception& exception)
		{
			LOGGER.handle_exception_async(
				"QLogicaeCore::Argon2idHashCryptographer::reverse()",
				exception.what()
			);

			return false;
		}
	}
	
	std::future<bool> Argon2idHashCryptographer::reverse_async(
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

	void Argon2idHashCryptographer::transform(
		Result<std::string>& result,
		const std::string& text
	)
	{
		std::scoped_lock lock(_mutex);

		std::array<char, 512> buffer{};
		int status = argon2id_hash_encoded(
			_cryptographer_properties.uint32_t_1,
			_cryptographer_properties.uint32_t_2,
			_cryptographer_properties.uint32_t_3,
			text.data(),
			text.size(),
			GENERATOR.random_salt().data(),
			_cryptographer_properties.size_t_2,
			_cryptographer_properties.size_t_1,
			buffer.data(),
			buffer.size()
		);

		if (status != ARGON2_OK)
		{
			return result.set_to_bad_status_without_value(
				"Hashing failed"
			);
		}

		result.set_to_good_status_with_value(
			buffer.data()
		);
	}

	void Argon2idHashCryptographer::reverse(
		Result<bool>& result,
		const std::string& hash,
		const std::string& key
	)
	{
		std::scoped_lock lock(_mutex);

		bool verified = argon2id_verify(
			hash.data(),
			key.data(),
			key.size()
		) == ARGON2_OK;

		result.set_to_good_status_with_value(verified);
	}

	void Argon2idHashCryptographer::transform_async(
		Result<std::future<std::string>>& result,
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

	void Argon2idHashCryptographer::reverse_async(
		Result<std::future<bool>>& result,
		const std::string& hash,
		const std::string& key
	)
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, hash, key,
			promise = std::move(promise)]() mutable
			{
				Result<bool> result;

				reverse(
					result,
					hash,
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

	void Argon2idHashCryptographer::reverse_async(
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

	void Argon2idHashCryptographer::transform_async(
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

	void Argon2idHashCryptographer::reverse_async(
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

	void Argon2idHashCryptographer::transform_async(
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

	Argon2idHashCryptographer& Argon2idHashCryptographer::get_instance()
	{
		static Argon2idHashCryptographer instance;

		return instance;
	}

	void Argon2idHashCryptographer::get_instance(
		QLogicaeCore::Result<Argon2idHashCryptographer*>& result
	)
	{
		static Argon2idHashCryptographer instance;

		result.set_to_good_status_with_value(&instance);
	}
}
