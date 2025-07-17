#pragma once

#include "pch.h"

#include "dot_env_value_extractor.hpp"

namespace QLogicaeCore
{
    DotEnvValueExtractor::DotEnvValueExtractor(
        const std::string& key) :
            _key(QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(key))
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
            return QLogicaeCore::Encoder::get_instance().from_utf16_to_utf8(
                DotEnv::get_instance().get(_key.c_str()).value()
            ); 
        }
        catch (...)
        {
            return "";
        }
    }

    std::optional<std::wstring> DotEnvValueExtractor::get_key() const
    {
        return _key;
    }
}
