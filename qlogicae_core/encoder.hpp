#pragma once

#include "result.hpp"
#include "utilities.hpp"

namespace QLogicaeCore
{
    class Encoder
    {
    public:
        std::string from_utf8_to_hex(
            const std::string_view& text
        ) const;

        std::string from_hex_to_utf8(
            const std::string_view& text
        ) const;

        std::string from_hex_to_base64(
            const std::string_view& text
        ) const;

        std::string from_base64_to_hex(
            const std::string_view& text
        ) const;

        std::wstring from_utf8_to_utf16(
            const std::string_view& text
        ) const;

        std::string from_utf16_to_utf8(
            const std::wstring_view& text
        ) const;

        std::string from_base64_to_utf8(
            const std::string_view& text
        ) const;

        std::string from_utf8_to_base64(
            const std::string_view& text
        ) const;

        std::string from_bytes_to_hex(
            const unsigned char* bytes,
            const size_t& length
        ) const;

        std::vector<unsigned char> from_hex_to_bytes(
            const std::string_view& text
        ) const;

        std::string from_bytes_to_base64(
            const unsigned char* bytes,
            const size_t& length
        ) const;

        std::vector<unsigned char> from_base64_to_bytes(
            const std::string_view& text
        ) const;

        static Encoder& get_instance();

        void setup(
            Result<void>& result
        );

        void from_utf8_to_hex(
            Result<std::string>& result,
            const std::string_view& text
        ) const;

        void from_hex_to_utf8(
            Result<std::string>& result,
            const std::string_view& text
        ) const;

        void from_hex_to_base64(
            Result<std::string>& result,
            const std::string_view& text
        ) const;

        void from_base64_to_hex(
            Result<std::string>& result,
            const std::string_view& text
        ) const;

        void from_utf8_to_utf16(
            Result<std::wstring>& result,
            const std::string_view& text
        ) const;

        void from_utf16_to_utf8(
            Result<std::string>& result,
            const std::wstring_view& text
        ) const;
        
        void from_base64_to_utf8(
            Result<std::string>& result,
            const std::string_view& text
        ) const;

        void from_utf8_to_base64(
            Result<std::string>& result,
            const std::string_view& text
        ) const;

        void from_bytes_to_hex(
            Result<std::string>& result,
            const unsigned char* bytes,
            const size_t& length
        ) const;

        void from_hex_to_bytes(
            Result<std::vector<unsigned char>>& result,
            const std::string_view& text
        ) const;

        void from_bytes_to_base64(
            Result<std::string>& result,
            const unsigned char* bytes,
            const size_t& length
        ) const;

        void from_base64_to_bytes(
            Result<std::vector<unsigned char>>& result,
            const std::string_view& text
        ) const;

        static void get_instance(Result<Encoder*>& result);

    protected:
        Encoder();

        ~Encoder() = default;

        Encoder(const Encoder& encoder) = delete;

        Encoder(Encoder&& encoder) noexcept = delete;

        Encoder& operator = (Encoder&& encoder) = delete;

        Encoder& operator = (const Encoder& encoder) = delete;

        std::string _to_hex(const std::string_view& text) const;

        std::string _to_base64(const std::string_view& text) const;

        void _to_hex(Result<std::string>& result, const std::string_view& text) const;

        void _to_base64(Result<std::string>& result, const std::string_view& text) const;
    };

    inline static Encoder& ENCODER = Encoder::get_instance();
}
