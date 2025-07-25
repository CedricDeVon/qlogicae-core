#pragma once

#include "pch.h"

#include "aes256_signature_cryptographer.hpp"

namespace QLogicaeCore
{
	AES256SignatureCryptographer::AES256SignatureCryptographer() : Cryptographer()
	{

	}

	std::string AES256SignatureCryptographer::reverse(
		const std::string_view& va,
		const std::string_view& vb) const
	{
		return reverse(
			va,
			reinterpret_cast<unsigned char*>(const_cast<char*>(vb.data()))
		);
	}

	std::string AES256SignatureCryptographer::transform(
		const std::string_view& va,
		const std::string_view& vb,
		const std::string_view& vc) const
	{
		return transform(
			va,
			reinterpret_cast<unsigned char*>(const_cast<char*>(vb.data())),
			reinterpret_cast<unsigned char*>(const_cast<char*>(vc.data()))
		);
	}

	std::future<std::string> AES256SignatureCryptographer::reverse_async(
		const std::string_view& va,
		const std::string_view& vb) const
	{
		return std::async(std::launch::async,
			[this, va, vb]() -> std::string
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

	std::future<std::string> AES256SignatureCryptographer::transform_async(
		const std::string_view& va,
		const std::string_view& vb,
		const std::string_view& vc) const
	{
		return std::async(std::launch::async,
			[this, va, vb, vc]() -> std::string
			{
				try
				{
					return transform(va, vb, vc);
				}
				catch (...)
				{
					return "";
				}
			});
	}

	std::string AES256SignatureCryptographer::transform(
		const std::string_view& va,
		unsigned char* vb,
		unsigned char* vc) const
	{
		try
		{
			std::scoped_lock lock(_mutex);

			if (!vb || !vc)
			{
				return "";
			}

			crypto_sign_keypair(vb, vc);

			const unsigned char* vd =
				reinterpret_cast<const unsigned char*>(va.data());
			unsigned long long ve = va.size(), vf;

			std::vector<unsigned char> vg(ve + crypto_sign_BYTES);
			unsigned char* vh = vg.data();

			crypto_sign(vh, &vf, vd, ve, vc);

			return QLogicaeCore::Encoder::get_instance().from_bytes_to_base64(vh, vf);
		}
		catch (...)
		{
			return "";
		}
	}

	std::string AES256SignatureCryptographer::reverse(
		const std::string_view& va,
		unsigned char* vb) const
	{
		try
		{
			std::scoped_lock lock(_mutex);

			if (!vb)
			{
				return "";
			}

			std::vector<unsigned char> vc =
				QLogicaeCore::Encoder::get_instance().from_base64_to_bytes(va);
			unsigned long long ve, vh = vc.size();
			std::vector<unsigned char> vd(vh);
			unsigned char* vf = vd.data(), *vg = vc.data();

			if (crypto_sign_open(vf, &ve, vc.data(), vh, vb) != 0)
			{
				return "";
			}

			return std::string(reinterpret_cast<const char*>(vf), ve);
		}
		catch (...)
		{
			return "";
		}
	}

	std::future<std::string> AES256SignatureCryptographer::reverse_async(
		const std::string_view& va,
		unsigned char* vb) const
	{
		return std::async(std::launch::async, [this, va, vb]() -> std::string
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

	std::future<std::string> AES256SignatureCryptographer::transform_async(
		const std::string_view& va,
		unsigned char* vb,
		unsigned char* vc) const
	{
		return std::async(std::launch::async, [this, va, vb, vc]() -> std::string
		{
			try
			{
				return transform(va, vb, vc);
			}
			catch (...)
			{
				return "";
			}
		});
	}
}

