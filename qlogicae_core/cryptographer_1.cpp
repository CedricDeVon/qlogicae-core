#pragma once

#include "pch.h"

#include "cryptographer_1.hpp"

namespace QLogicaeCore
{
	Cryptographer1::Cryptographer1() : Cryptographer()
	{
	}

    std::string Cryptographer1::reverse(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc) const
    {
        return reverse(va,
            reinterpret_cast<const unsigned char*>(vb.data()),
            reinterpret_cast<const unsigned char*>(vc.data())
        );
    }

    std::string Cryptographer1::transform(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc) const
    {
        return transform(va,
            reinterpret_cast<const unsigned char*>(vb.data()),
            reinterpret_cast<const unsigned char*>(vc.data())
        );
    }

    std::future<std::string> Cryptographer1::reverse_async(
        const std::string_view& va,
        const std::string_view& vb,
        const std::string_view& vc) const
    {
        return std::async(std::launch::async,
            [this, va, vb, vc]() -> std::string
        {
            try
            {
                return reverse(va, vb, vc);
            }
            catch (...)
            {
                return "";
            }
        });
    }

    std::future<std::string> Cryptographer1::transform_async(
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

    std::string Cryptographer1::transform(
        const std::string_view& va,
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

            unsigned long long ve = 0, vg = va.size();
            std::vector<unsigned char> vd(
                vg + crypto_aead_xchacha20poly1305_ietf_ABYTES
            );
            unsigned char* vf = vd.data();

            if (crypto_aead_xchacha20poly1305_ietf_encrypt(
                vf, &ve,
                reinterpret_cast<const unsigned char*>(va.data()), vg,
                nullptr, 0, nullptr, vc, vb) != 0)
            {
                return "";
            }

            return QLogicaeCore::Encoder::instance()
                .from_bytes_to_base64(vf, ve);
        }
        catch (...)
        {
            return "";
        }
    }

    std::string Cryptographer1::reverse(
        const std::string_view& va,
        const unsigned char* vb,
        const unsigned char* vc) const
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!vb || !vc ||
                va.size() < crypto_aead_xchacha20poly1305_ietf_ABYTES)
            {
                return "";
            }

            unsigned long long ve = 0;
            std::vector<unsigned char> vd =
                QLogicaeCore::Encoder::instance().from_base64_to_bytes(va);
            size_t vf = vd.size();
            std::vector<unsigned char> decrypted(
                vf - crypto_aead_xchacha20poly1305_ietf_ABYTES
            );

            if (crypto_aead_xchacha20poly1305_ietf_decrypt(
                decrypted.data(), &ve,
                nullptr,
                vd.data(), vf,
                nullptr, 0, vc, vb) != 0)
            {
                return "";
            }

            return std::string(
                reinterpret_cast<char*>(decrypted.data()), ve
            );
        }
        catch (...)
        {
            return "";
        }
    }

    std::future<std::string> Cryptographer1::reverse_async(
        const std::string_view& va,
        const unsigned char* vb,
        const unsigned char* vc) const
    {
        return std::async(std::launch::async, [this, va, vb, vc]() -> std::string
        {
            try
            {
                return reverse(va, vb, vc);
            }
            catch (...)
            {
                return "";
            }
        });
    }

    std::future<std::string> Cryptographer1::transform_async(
        const std::string_view& va,
        const unsigned char* vb,
        const unsigned char* vc) const
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
