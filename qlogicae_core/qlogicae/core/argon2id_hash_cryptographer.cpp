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
		const CryptographerProperties& va) :
			Cryptographer()
	{
		_cryptographer_properties = va;
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
		const std::string_view& va,
		const std::string_view& vb) const
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
		const std::string_view& va,
		const std::string_view& vb) const
	{
		return std::async(std::launch::async, [this, va, vb]() -> bool
		{
			return reverse(va, vb);			
		});
	}
}
