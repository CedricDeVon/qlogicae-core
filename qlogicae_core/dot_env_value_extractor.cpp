#pragma once

#include "pch.h"

#include "dot_env_value_extractor.hpp"

namespace QLogicaeCore
{
    DotEnvValueExtractor::DotEnvValueExtractor(
        const std::string& key) :
            _key(QLogicaeCore::Encoder::instance().from_utf8_to_utf16(key))
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
            return QLogicaeCore::Encoder::instance().from_utf16_to_utf8(
                DotEnv::instance().get(_key.c_str()).value()
            ); 
        }
        catch (...)
        {
            return "";
        }
    }
}
