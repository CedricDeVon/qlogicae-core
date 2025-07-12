#pragma once

#include "pch.h"

#include "bcrypt_hash_cryptographer.hpp"

namespace QLogicaeCore
{
	BcryptHashCryptographer::BcryptHashCryptographer() :
		Cryptographer()
	{
	}

	std::string BcryptHashCryptographer::transform(
		const std::string& va) const
	{
		if (va.empty())
		{
			throw std::invalid_argument("Password cannot be empty");
		}

		std::string hash;
		hash.resize(crypto_pwhash_STRBYTES);

		if (crypto_pwhash_str(
			hash.data(),
			va.c_str(), va.size(),
			crypto_pwhash_OPSLIMIT_MODERATE,
			crypto_pwhash_MEMLIMIT_MODERATE) != 0)
		{
			throw std::runtime_error("Hashing failed");
		}

		return hash.c_str();
	}

	bool BcryptHashCryptographer::reverse(
		const std::string& va, const std::string& vb) const
	{
		if (va.empty() || vb.empty())
		{
			return false;
		}

		return crypto_pwhash_str_verify(vb.c_str(), va.c_str(), va.size()) == 0;
			
	}

	std::future<bool> BcryptHashCryptographer::reverse_async(
		const std::string& va,
		const std::string& vb) const
	{
		return std::async(std::launch::async, [this, va, vb]() -> bool
			{
				try
				{
					return reverse(va, vb);
				}
				catch (...)
				{
					return false;
				}
			});
	}

	std::future<std::string> BcryptHashCryptographer::transform_async(
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
}
