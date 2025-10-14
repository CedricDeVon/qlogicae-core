#include "pch.hpp"

#include "argon2id_hash_cryptographer.hpp"

namespace QLogicaeCore
{
	Argon2idHashCryptographer::Argon2idHashCryptographer() :
		Cryptographer()
	{
		_cryptographer_properties = default_cryptographer_3_properties;
	}

	Argon2idHashCryptographer::Argon2idHashCryptographer(
		const CryptographerProperties& properties) :
			Cryptographer()
	{
		_cryptographer_properties = properties;
	}

	void Argon2idHashCryptographer::setup(
		Result<void>& result,
		const CryptographerProperties& properties)
	{
		_cryptographer_properties = properties;

		result.set_to_success();
	}

	std::string Argon2idHashCryptographer::transform(
		const std::string& va) const
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
			throw std::runtime_error(
				std::string("Exception at Argon2idHashCryptographer::transform(): ") +
				exception.what()
			);
		}
	}

	std::future<std::string> Argon2idHashCryptographer::transform_async(
		const std::string& va) const
	{
		return std::async(std::launch::async, [this, va]() -> std::string
		{
			return transform(va);			
		});
	}

	bool Argon2idHashCryptographer::reverse(
		const std::string& va,
		const std::string& vb) const
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
			throw std::runtime_error(
				std::string("Exception at Argon2idHashCryptographer::reverse(): ") +
				exception.what()
			);
		}
	}
	
	std::future<bool> Argon2idHashCryptographer::reverse_async(
		const std::string& va,
		const std::string& vb) const
	{
		return std::async(std::launch::async, [this, va, vb]() -> bool
		{
			return reverse(va, vb);			
		});
	}

	void Argon2idHashCryptographer::transform(
		Result<std::string>& result,
		const std::string& text) const
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
			result.set_to_failure();
			return;
		}

		result.set_to_success(
			buffer.data()
		);
	}

	void Argon2idHashCryptographer::reverse(
		Result<bool>& result,
		const std::string& hash,
		const std::string& key) const
	{
		std::scoped_lock lock(_mutex);

		bool verified = argon2id_verify(
			hash.data(),
			key.data(),
			key.size()
		) == ARGON2_OK;

		result.set_to_success(verified);
	}

	void Argon2idHashCryptographer::transform_async(
		Result<std::future<std::string>>& result,
		const std::string& text) const
	{
		result.set_to_success(std::async(std::launch::async, [this, text]() -> std::string
			{
				Result<std::string> result;

				transform(result, text);

				return result.get_data();
			})
		);
	}

	void Argon2idHashCryptographer::reverse_async(
		Result<std::future<bool>>& result,
		const std::string& hash,
		const std::string& key) const
	{
		result.set_to_success(std::async(std::launch::async, [this, hash, key]() -> bool
			{
				Result<bool> result;

				reverse(result, hash, key);

				return result.get_data();
			}));
	}
}
