#pragma once

#include "pch.h"

#include "cryptographer_3.hpp"

namespace QLogicaeCore
{
	Cryptographer3::Cryptographer3() :
		Cryptographer()
	{
		_va = QLogicaeCore::default_cryptographer_3_properties;
	}

	Cryptographer3::Cryptographer3(
		const CryptographerProperties& va) :
			Cryptographer()
	{
		_va = va;
	}

	std::string Cryptographer3::transform(
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

	std::future<std::string> Cryptographer3::transform_async(
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

	bool Cryptographer3::reverse(
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
	
	std::future<bool> Cryptographer3::reverse_async(
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

