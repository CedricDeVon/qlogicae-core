#include "pch.hpp"

#include "dot_env_value_extractor.hpp"

namespace QLogicaeCore
{
    DotEnvValueExtractor::DotEnvValueExtractor(
        const std::string& key) :
            _key(ENCODER
                .from_utf8_to_utf16(key))
    {

    }

    DotEnvValueExtractor::DotEnvValueExtractor(
        const std::wstring& key) :
            _key(key)
    {

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
            throw std::runtime_error(std::string() + "Exception at DotEnvValueExtractor::get_value(): " + exception.what());
        }
    }

    std::optional<std::wstring> DotEnvValueExtractor::get_key() const
    {
        return _key;
    }
}
