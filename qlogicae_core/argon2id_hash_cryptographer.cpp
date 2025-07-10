#pragma once

#include "pch.h"

#include "argon2id_hash_cryptographer.hpp"

namespace QLogicaeCore
{
	Argon2idHashCryptographer::Argon2idHashCryptographer() :
		Cryptographer()
	{
		_va = QLogicaeCore::default_cryptographer_3_properties;
	}

	Argon2idHashCryptographer::Argon2idHashCryptographer(
		const CryptographerProperties& va) :
			Cryptographer()
	{
		_va = va;
	}

	std::string Argon2idHashCryptographer::transform(
		const std::string& va) const
	{
		try
		{
			std::scoped_lock lock(_mutex);

			std::array<char, 512> vb{};
			int vc = argon2id_hash_encoded(
				_va.uint32_t_1,
				_va.uint32_t_2,
				_va.uint32_t_3,
				va.data(),
				va.size(),
				QLogicaeCore::Generator::instance().random_salt().data(),
				_va.size_t_2,
				_va.size_t_1,
				vb.data(), vb.size());
			if (vc != ARGON2_OK)
			{
				return "";
			}

			return vb.data();
		}
		catch (...)
		{
			return "";
		}
	}

	std::future<std::string> Argon2idHashCryptographer::transform_async(
		const std::string& va) const
	{
		return std::async(std::launch::async, [this, va]() -> std::string
		{
			try
			{
				return transform(va);
			}
			catch (...)
			{
				return "";
			}
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
		catch (...)
		{
			return "";
		}
	}
	
	std::future<bool> Argon2idHashCryptographer::reverse_async(
		const std::string_view& va,
		const std::string_view& vb) const
	{
		return std::async(std::launch::async, [this, va, vb]() -> bool
		{
			try
			{
				return reverse(va, vb);
			}
			catch (...)
			{
				return "";
			}
		});
	}
}

