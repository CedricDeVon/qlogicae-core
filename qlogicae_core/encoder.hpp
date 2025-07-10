#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class Encoder
    {
    public:
        std::string from_utf8_to_hex(const std::string_view&) const;
        std::string from_hex_to_utf8(const std::string_view&) const;
        std::string from_hex_to_base64(const std::string_view&) const;
        std::string from_base64_to_hex(const std::string_view&) const;
        std::wstring from_utf8_to_utf16(const std::string_view&) const;
        std::string from_utf16_to_utf8(const std::wstring_view&) const;
        std::string from_base64_to_utf8(const std::string_view&) const;
        std::string from_utf8_to_base64(const std::string_view&) const;
        std::string from_bytes_to_hex(const unsigned char*, const size_t&) const;
        std::vector<unsigned char> from_hex_to_bytes(const std::string_view&) const;
        std::string from_bytes_to_base64(const unsigned char*, const size_t&) const;
        std::vector<unsigned char> from_base64_to_bytes(const std::string_view&) const;

        static Encoder& instance();

    protected:
        Encoder();
        ~Encoder() = default;
        Encoder(const Encoder&) = delete;
        Encoder(Encoder&&) noexcept = delete;
        Encoder& operator = (Encoder&&) = delete;
        Encoder& operator = (const Encoder&) = delete;

        std::string _to_hex(const std::string_view&) const;
        std::string _to_base64(const std::string_view&) const;
    };
}
