#include "pch.hpp"

#include "dot_env_value_extractor.hpp"

namespace QLogicaeCore
{
    DotEnvValueExtractor::DotEnvValueExtractor(
        const std::string& key
    ) :
            _key(
                ENCODER.from_utf8_to_utf16(key)
            )
    {

    }

    DotEnvValueExtractor::DotEnvValueExtractor(
        const std::wstring& key) :
            _key(key)
    {

    }

    std::optional<std::wstring> DotEnvValueExtractor::get_key() const
    {
        return _key;
    }

    std::optional<std::string> DotEnvValueExtractor::get_value() const
    {
        try
        {
            return ENCODER
                .from_utf16_to_utf8(
                    DOT_ENV.get(_key.c_str()
                ).value()
            ); 
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at DotEnvValueExtractor::get_value(): " +
                exception.what()
            );
        }
    }

    void DotEnvValueExtractor::get_key(
        Result<std::optional<std::wstring>>& result
    ) const
    {
        result.set_to_good_status_with_value(_key);
    }

    void DotEnvValueExtractor::get_value(
        Result<std::string>& result
    ) const
    {
        Result<std::wstring> output;

        DOT_ENV.get(
            output, _key.c_str()
        );
        ENCODER.from_utf16_to_utf8(
            result, output.get_value()
        );        
    }

    void DotEnvValueExtractor::setup(
        Result<void>& result,
        const std::string key
    )
    {
        Result<std::wstring> r;

        ENCODER.from_utf8_to_utf16(r, key);

        _key = r.get_value();

        result.set_to_good_status_without_value();
    }

    void DotEnvValueExtractor::setup(
        Result<void>& result,
        const std::wstring key
    )
    {
        _key = key;

        result.set_to_good_status_without_value();
    }
}
