#include "pch.hpp"

#include "../includes/encoder.hpp"

namespace QLogicaeCore
{
    Encoder::Encoder()
    {
        if (sodium_init() < 0)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::Encoder()",
                "Sodium package is not installed"
            );

            throw std::runtime_error(
                "QLogicaeCore::Encoder::Encoder() - Sodium package is not initialized"
            );
        }
    }

    Encoder::~Encoder()
    {
        
    }

    bool Encoder::setup()
    {
        try
        {
            Result<void> void_result;

            setup(void_result);

            return void_result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::setup()",
                exception.what()
            );

            return false;
        }
    }

    void Encoder::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    std::future<bool> Encoder::setup_async(
        const std::function<void(const bool& value)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                bool value = setup();

                promise.set_value(
                    value
                );

                if (callback)
                {
                    callback(
                        value
                    );
                }
            }
        );

        return future;
    }

    void Encoder::setup_async(
        Result<std::future<void>>& result,
        const std::function<void(Result<void>& result)>& callback
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(result);

                promise.set_value();

                callback(
                    result
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    std::string Encoder::from_bytes_to_base64(
        const unsigned char* text,
        const size_t& length
    )
    {
        try
        {
            Result<std::string> result;

            from_bytes_to_base64(
                result,
                text,
                length
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_bytes_to_base64()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::from_bytes_to_base64(
        Result<std::string>& result,
        const unsigned char* text,
        const size_t& length
    )
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

    std::vector<unsigned char> Encoder::from_base64_to_bytes(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::vector<unsigned char>> result;

            from_base64_to_bytes(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_base64_to_bytes()",
                exception.what()
            );

            return {};
        }
    }

    void Encoder::from_base64_to_bytes(
        Result<std::vector<unsigned char>>& result,
        const std::string_view& text
    )
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

    std::string Encoder::from_bytes_to_hex(
        const unsigned char* text,
        const size_t& length
    )
    {
        try
        {
            Result<std::string> result;

            from_bytes_to_hex(
                result,
                text,
                length
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_bytes_to_hex()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::from_bytes_to_hex(
        Result<std::string>& result,
        const unsigned char* text,
        const size_t& length
    )
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

    std::vector<unsigned char> Encoder::from_hex_to_bytes(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::vector<unsigned char>> result;

            from_hex_to_bytes(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_hex_to_bytes()",
                exception.what()
            );

            return {};
        }
    }

    void Encoder::from_hex_to_bytes(
        Result<std::vector<unsigned char>>& result,
        const std::string_view& text
    )
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

    std::string Encoder::from_utf16_to_utf8(
        const std::wstring_view& text
    )
    {
        try
        {
            Result<std::string> result;

            from_utf16_to_utf8(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_utf16_to_utf8()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::from_utf16_to_utf8(
        Result<std::string>& result,
        const std::wstring_view& text
    )
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

    std::wstring Encoder::from_utf8_to_utf16(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::wstring> result;

            from_utf8_to_utf16(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_utf8_to_utf16()",
                exception.what()
            );

            return L"";
        }
    }

    void Encoder::from_utf8_to_utf16(
        Result<std::wstring>& result,
        const std::string_view& text
    )
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

    std::string Encoder::from_utf8_to_hex(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::string> result;

            from_utf8_to_hex(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_utf8_to_hex()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::from_utf8_to_hex(
        Result<std::string>& result,
        const std::string_view& text
    )
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        _to_hex(result, text);
    }

    std::string Encoder::from_utf8_to_base64(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::string> result;

            from_utf8_to_base64(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_utf8_to_base64()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::from_utf8_to_base64(
        Result<std::string>& result,
        const std::string_view& text
    )
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        _to_base64(result, text);
    }

    std::string Encoder::from_hex_to_utf8(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::string> result;

            from_hex_to_utf8(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_hex_to_utf8()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::from_hex_to_utf8(
        Result<std::string>& result,
        const std::string_view& text
    )
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

    std::string Encoder::from_hex_to_base64(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::string> result;

            from_hex_to_base64(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_hex_to_base64()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::from_hex_to_base64(
        Result<std::string>& result,
        const std::string_view& text
    )
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        from_hex_to_utf8(result, text);
        _to_base64(result, result.get_value());
        result.set_to_good_status_with_value(
            result.get_value()
        );
    }

    std::string Encoder::from_base64_to_utf8(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::string> result;

            from_base64_to_utf8(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_base64_to_utf8()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::from_base64_to_utf8(
        Result<std::string>& result,
        const std::string_view& text
    )
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
                buffer.data()), bin_len
            )
        );
    }

    std::string Encoder::from_base64_to_hex(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::string> result;

            from_base64_to_hex(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::from_base64_to_hex()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::from_base64_to_hex(
        Result<std::string>& result,
        const std::string_view& text
    )
    {
        if (text.empty())
        {
            return result.set_to_bad_status_without_value(
                "Text is empty"
            );
        }

        Result<std::vector<unsigned char>> bytes_result;
        from_base64_to_bytes(bytes_result, text);

        if (!bytes_result.is_status_safe())
        {
            return result.set_to_bad_status_without_value(
                bytes_result.get_message()
            );
        }

        Result<std::string> hex_result;
        from_bytes_to_hex(hex_result,
            bytes_result.get_value().data(),
            bytes_result.get_value().size());

        if (!hex_result.is_status_safe())
        {
            return result.set_to_bad_status_without_value(
                hex_result.get_message()
            );
        }

        result.set_to_good_status_with_value(
            hex_result.get_value()
        );
    }

    Encoder& Encoder::get_instance()
    {
        static Encoder instance;

        return instance;
    }

    void Encoder::get_instance(
        Result<Encoder*>& result
    )
    {
        static Encoder singleton;

        result.set_to_good_status_with_value(&singleton);
    }

    std::string Encoder::_to_hex(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::string> result;

            _to_hex(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::_to_hex()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::_to_hex(
        Result<std::string>& result,
        const std::string_view& text
    )
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

    std::string Encoder::_to_base64(
        const std::string_view& text
    )
    {
        try
        {
            Result<std::string> result;

            _to_base64(
                result,
                text
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Encoder::_to_base64()",
                exception.what()
            );

            return "";
        }
    }

    void Encoder::_to_base64(
        Result<std::string>& result,
        const std::string_view& text
    )
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
