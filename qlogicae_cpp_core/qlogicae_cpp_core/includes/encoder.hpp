#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "utilities.hpp"

namespace QLogicaeCore
{
    class Encoder
    {
    public:
        bool setup();

        std::future<bool> setup_async(
            const std::function<void(const bool& result)>& callback =
            [](const bool& result) {}
        );

        void setup(
            Result<void>& result
        );

        void setup_async(
            Result<std::future<void>>& result,
            const std::function<void(Result<void>& result)>& callback =
            [](Result<void>& result) {}
        );

        std::string from_utf8_to_hex(
            const std::string_view& text
        );

        void from_utf8_to_hex(
            Result<std::string>& result,
            const std::string_view& text
        );

        std::string from_hex_to_utf8(
            const std::string_view& text
        );

        void from_hex_to_utf8(
            Result<std::string>& result,
            const std::string_view& text
        );

        std::string from_hex_to_base64(
            const std::string_view& text
        );

        void from_hex_to_base64(
            Result<std::string>& result,
            const std::string_view& text
        );

        std::string from_base64_to_hex(
            const std::string_view& text
        );

        void from_base64_to_hex(
            Result<std::string>& result,
            const std::string_view& text
        );

        std::wstring from_utf8_to_utf16(
            const std::string_view& text
        );

        void from_utf8_to_utf16(
            Result<std::wstring>& result,
            const std::string_view& text
        );

        std::string from_utf16_to_utf8(
            const std::wstring_view& text
        );

        void from_utf16_to_utf8(
            Result<std::string>& result,
            const std::wstring_view& text
        );

        std::string from_base64_to_utf8(
            const std::string_view& text
        );

        void from_base64_to_utf8(
            Result<std::string>& result,
            const std::string_view& text
        );

        std::string from_utf8_to_base64(
            const std::string_view& text
        );

        void from_utf8_to_base64(
            Result<std::string>& result,
            const std::string_view& text
        );

        std::string from_bytes_to_hex(
            const unsigned char* bytes,
            const size_t& length
        );

        void from_bytes_to_hex(
            Result<std::string>& result,
            const unsigned char* bytes,
            const size_t& length
        );

        std::vector<unsigned char> from_hex_to_bytes(
            const std::string_view& text
        );

        void from_hex_to_bytes(
            Result<std::vector<unsigned char>>& result,
            const std::string_view& text
        );

        std::string from_bytes_to_base64(
            const unsigned char* bytes,
            const size_t& length
        );

        void from_bytes_to_base64(
            Result<std::string>& result,
            const unsigned char* bytes,
            const size_t& length
        );

        std::vector<unsigned char> from_base64_to_bytes(
            const std::string_view& text
        );

        void from_base64_to_bytes(
            Result<std::vector<unsigned char>>& result,
            const std::string_view& text
        );

        static Encoder& get_instance();

        static void get_instance(
            Result<Encoder*>& result
        );

    protected:
        Encoder();

        ~Encoder();

        Encoder(
            const Encoder& instance
        ) = delete;

        Encoder(
            Encoder&& instance
        ) noexcept = delete;

        Encoder& operator = (
            Encoder&& instance
        ) = delete;

        Encoder& operator = (
            const Encoder& instance
        ) = delete;

        std::string _to_hex(
            const std::string_view& text
        );

        void _to_hex(
            Result<std::string>& result,
            const std::string_view& text
        );

        std::string _to_base64(
            const std::string_view& text
        );

        void _to_base64(
            Result<std::string>& result,
            const std::string_view& text
        );
    };

    inline static Encoder& ENCODER = Encoder::get_instance();
}
