#include "pch.hpp"

#include "encoder.hpp"

namespace QLogicaeCore
{
    Encoder::Encoder()
    {
        if (sodium_init() < 0)
        {
            throw std::runtime_error(
                "Exception at Encoder::Encoder(): Sodium package is not initialized"
            );
        }
    }

    Encoder& Encoder::get_instance()
    {
        static Encoder singleton;

        return singleton;
    }

    std::string Encoder::from_bytes_to_base64(
        const unsigned char* text,
        const size_t& length) const
    {
        try
        {
            std::string base64(sodium_base64_encoded_len(
                length,
                sodium_base64_VARIANT_ORIGINAL),
                '\0'
            );
            sodium_bin2base64(
                base64.data(),
                base64.size(),
                text,
                length,
                sodium_base64_VARIANT_ORIGINAL
            );

            base64.resize(strlen(base64.data()));
            
            return base64;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_bytes_to_base64(): ") +
                exception.what()
            );
        }
    }

    std::vector<unsigned char> Encoder::from_base64_to_bytes(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return {};
            }

            std::vector<unsigned char> buffer(text.length());
            size_t actual_len = 0;

            if (sodium_base642bin(
                buffer.data(), buffer.size(),
                text.data(), text.length(),
                nullptr, &actual_len,
                nullptr, sodium_base64_VARIANT_ORIGINAL
            ) != 0)
            {
                return {};
            }

            buffer.resize(actual_len);

            return buffer;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_base64_to_bytes(): ") +
                exception.what()
            );
        }
    }

    std::string Encoder::from_bytes_to_hex(
        const unsigned char* text,
        const size_t& length) const
    {
        try
        {
            const char* hex_chars = UTILITIES.HEXADECIMAL_CHARACTERSET_1.c_str();
            std::string output;
            output.reserve(length * 2);

            size_t index = 0;
            for (index = 0; index < length; ++index)
            {
                unsigned char byte = text[index];
                output.push_back(hex_chars[(byte >> 4) & 0x0F]);
                output.push_back(hex_chars[byte & 0x0F]);
            }

            return output;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_bytes_to_hex(): ") +
                exception.what()
            );
        }
    }

    std::vector<unsigned char> Encoder::from_hex_to_bytes(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return {};
            }

            unsigned int byte;
            std::string va = text.data();
            std::vector<unsigned char> bytes;
            bytes.reserve(text.length() / 2);
            size_t index = 0, text_length = text.length();
            for (index = 0; index < text_length; index += 2)
            {
                std::istringstream(va.substr(index, 2)) >> std::hex >> byte;
                bytes.push_back(static_cast<unsigned char>(byte));
            }

            return bytes;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_hex_to_bytes(): ") +
                exception.what()
            );
        }
    }

    std::string Encoder::from_utf16_to_utf8(
        const std::wstring_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return "";
            }

            int size_needed = WideCharToMultiByte(
                CP_UTF8, 0,
                text.data(), -1,
                nullptr, 0,
                nullptr, nullptr
            );
            std::string result(size_needed, 0);
            WideCharToMultiByte(
                CP_UTF8, 0,
                text.data(), -1,
                &result[0], size_needed,
                nullptr, nullptr
            );
            result.pop_back();

            return result;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_utf16_to_utf8(): ") +
                exception.what()
            );
        }
    }

    std::wstring Encoder::from_utf8_to_utf16(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return L"";
            }

            unsigned int size_needed = MultiByteToWideChar(
                CP_UTF8, 0,
                text.data(), -1,
                nullptr, 0
            );
            std::wstring result(size_needed, 0);
            MultiByteToWideChar(
                CP_UTF8, 0,
                text.data(), -1,
                &result[0], size_needed
            );
            result.pop_back();

            return result;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_utf8_to_utf16(): ") +
                exception.what()
            );
        }
    }

    std::string Encoder::from_utf8_to_hex(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return "";
            }

            return _to_hex(text);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_utf8_to_hex(): ") +
                exception.what()
            );
        }
    }

    std::string Encoder::from_utf8_to_base64(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return "";
            }

            return _to_base64(text);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_utf8_to_base64(): ") +
                exception.what()
            );
        }
    }

    std::string Encoder::from_hex_to_utf8(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return "";
            }

            size_t bin_len = 0;
            std::vector<unsigned char> buffer(text.size() / 2, 0);

            if (sodium_hex2bin(
                buffer.data(), buffer.size(),
                text.data(), text.size(),
                nullptr, &bin_len, nullptr) != 0)
            {
                return "";
            }

            return std::string(reinterpret_cast<const char*>(
                buffer.data()), bin_len);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_hex_to_utf8(): ") +
                exception.what()
            );
        }
    }

    std::string Encoder::from_hex_to_base64(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return "";
            }

            return _to_base64(from_hex_to_utf8(text));
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_hex_to_base64(): ") +
                exception.what()
            );
        }
    }

    std::string Encoder::from_base64_to_utf8(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return "";
            }

            size_t bin_len = 0;
            std::vector<unsigned char> buffer(text.size(), 0);

            if (sodium_base642bin(buffer.data(), buffer.size(),
                text.data(), text.size(),
                nullptr, &bin_len, nullptr,
                sodium_base64_VARIANT_ORIGINAL) != 0)
            {
                return "";
            }

            return std::string(reinterpret_cast<const char*>(
                buffer.data()), bin_len);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_base64_to_utf8(): ") +
                exception.what()
            );
        }
    }

    std::string Encoder::from_base64_to_hex(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return "";
            }

            return _to_hex(from_base64_to_utf8(text));
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::from_base64_to_hex(): ") +
                exception.what()
            );
        }
    }

    std::string Encoder::_to_hex(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return "";
            }

            std::string output(text.size() * 3, '\0');

            sodium_bin2hex(output.data(), output.size(),
                reinterpret_cast<const unsigned char*>(
                    text.data()),
                text.size());
            output.resize(std::strlen(output.c_str()));

            return output;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::_to_hex(): ") +
                exception.what()
            );
        }
    }

    std::string Encoder::_to_base64(
        const std::string_view& text) const
    {
        try
        {
            if (text.empty())
            {
                return "";
            }

            std::string output(sodium_base64_encoded_len(
                text.size(),
                sodium_base64_VARIANT_ORIGINAL),
                '\0'
            );

            sodium_bin2base64(output.data(), output.size(),
                reinterpret_cast<const unsigned char*>(
                    text.data()), text.size(),
                sodium_base64_VARIANT_ORIGINAL);
            output.resize(std::strlen(output.c_str()));

            return output;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Encoder::_to_base64(): ") +
                exception.what()
            );
        }
    }

    void Encoder::get_instance(
        Result<Encoder*>& result
    )
    {
        static Encoder singleton;

        result.set_to_good_status_with_value(&singleton);
    }

    void Encoder::from_bytes_to_base64(
        Result<std::string>& result,
        const unsigned char* text,
        const size_t& length
    ) const
    {
        std::string base64(sodium_base64_encoded_len(
            length,
            sodium_base64_VARIANT_ORIGINAL),
            '\0'
        );
        sodium_bin2base64(
            base64.data(),
            base64.size(),
            text,
            length,
            sodium_base64_VARIANT_ORIGINAL
        );

        base64.resize(strlen(base64.data()));

        result.set_to_good_status_with_value(base64);
    }

    void Encoder::from_base64_to_bytes(
        Result<std::vector<unsigned char>>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        std::vector<unsigned char> buffer(text.length());
        size_t actual_len = 0;

        if (sodium_base642bin(
            buffer.data(), buffer.size(),
            text.data(), text.length(),
            nullptr, &actual_len,
            nullptr, sodium_base64_VARIANT_ORIGINAL
        ) != 0)
        {
            return result.set_to_bad_status_without_value(
                "Encoding failed"
            );
        }

        buffer.resize(actual_len);

        result.set_to_good_status_with_value(buffer);
    }

    void Encoder::from_bytes_to_hex(
        Result<std::string>& result,
        const unsigned char* text,
        const size_t& length
    ) const
    {
        const char* hex_chars = UTILITIES.HEXADECIMAL_CHARACTERSET_1.c_str();
        std::string output;
        output.reserve(length * 2);

        size_t index = 0;
        for (index = 0; index < length; ++index)
        {
            unsigned char byte = text[index];
            output.push_back(hex_chars[(byte >> 4) & 0x0F]);
            output.push_back(hex_chars[byte & 0x0F]);
        }

        result.set_to_good_status_with_value(output);
    }

    void Encoder::from_hex_to_bytes(
        Result<std::vector<unsigned char>>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        unsigned int byte;
        std::string va = text.data();
        std::vector<unsigned char> bytes;
        bytes.reserve(text.length() / 2);
        size_t index = 0, text_length = text.length();
        for (index = 0; index < text_length; index += 2)
        {
            std::istringstream(va.substr(index, 2)) >> std::hex >> byte;
            bytes.push_back(static_cast<unsigned char>(byte));
        }

        result.set_to_good_status_with_value(bytes);
    }

    void Encoder::from_utf16_to_utf8(
        Result<std::string>& result,
        const std::wstring_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        int size_needed = WideCharToMultiByte(
            CP_UTF8, 0,
            text.data(), -1,
            nullptr, 0,
            nullptr, nullptr
        );
        std::string data(size_needed, 0);
        WideCharToMultiByte(
            CP_UTF8, 0,
            text.data(), -1,
            &data[0], size_needed,
            nullptr, nullptr
        );
        data.pop_back();

        result.set_to_good_status_with_value(data);
    }

    void Encoder::from_utf8_to_utf16(
        Result<std::wstring>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        unsigned int size_needed = MultiByteToWideChar(
            CP_UTF8, 0,
            text.data(), -1,
            nullptr, 0
        );
        std::wstring data(size_needed, 0);
        MultiByteToWideChar(
            CP_UTF8, 0,
            text.data(), -1,
            &data[0], size_needed
        );
        data.pop_back();

        result.set_to_good_status_with_value(data);
    }

    void Encoder::from_utf8_to_hex(
        Result<std::string>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        _to_hex(result, text);
    }

    void Encoder::from_utf8_to_base64(
        Result<std::string>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        _to_base64(result, text);
    }

    void Encoder::from_hex_to_utf8(
        Result<std::string>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        size_t bin_len = 0;
        std::vector<unsigned char> buffer(text.size() / 2, 0);

        if (sodium_hex2bin(
            buffer.data(), buffer.size(),
            text.data(), text.size(),
            nullptr, &bin_len, nullptr) != 0)
        {
            return result.set_to_bad_status_without_value(
                "Encoding failed"
            );
        }

        result.set_to_good_status_with_value(
            std::string(reinterpret_cast<const char*>(
                buffer.data()), bin_len
            )
        );
    }

    void Encoder::from_hex_to_base64(
        Result<std::string>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        from_hex_to_utf8(result, text);
        _to_base64(result, result.get_value());
    }

    void Encoder::from_base64_to_utf8(
        Result<std::string>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        size_t bin_len = 0;
        std::vector<unsigned char> buffer(text.size(), 0);

        if (sodium_base642bin(buffer.data(), buffer.size(),
            text.data(), text.size(),
            nullptr, &bin_len, nullptr,
            sodium_base64_VARIANT_ORIGINAL) != 0)
        {
            return result.set_to_bad_status_without_value(
                "Encoding failed"
            );
        }

        result.set_to_good_status_with_value(
            std::string(reinterpret_cast<const char*>(
                buffer.data()), bin_len)
        );
    }

    void Encoder::from_base64_to_hex(
        Result<std::string>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        from_base64_to_utf8(result, text);
    }

    void Encoder::_to_hex(
        Result<std::string>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        std::string output(text.size() * 3, '\0');

        sodium_bin2hex(output.data(), output.size(),
            reinterpret_cast<const unsigned char*>(
                text.data()),
            text.size());
        output.resize(std::strlen(output.c_str()));

        result.set_to_good_status_with_value(
            output
        );
    }

    void Encoder::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    void Encoder::_to_base64(
        Result<std::string>& result,
        const std::string_view& text
    ) const
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        std::string output(sodium_base64_encoded_len(
            text.size(),
            sodium_base64_VARIANT_ORIGINAL),
            '\0'
        );

        sodium_bin2base64(output.data(), output.size(),
            reinterpret_cast<const unsigned char*>(
                text.data()), text.size(),
            sodium_base64_VARIANT_ORIGINAL);
        output.resize(std::strlen(output.c_str()));

        result.set_to_good_status_with_value(
            output
        );
    }
}
