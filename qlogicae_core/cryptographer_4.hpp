#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class Cryptographer4 : public Cryptographer
    {
    public:
        Cryptographer4();
        ~Cryptographer4() = default;
        Cryptographer4(const Cryptographer4&) = delete;
        Cryptographer4(Cryptographer4&&) noexcept = delete;
        Cryptographer4& operator = (Cryptographer4&&) = delete;
        Cryptographer4& operator = (const Cryptographer4&) = delete;

        std::string reverse(const std::string_view&, unsigned char*) const;
        std::string reverse(const std::string_view&, const std::string_view&) const;
        std::string transform(const std::string_view&, unsigned char*, unsigned char*) const;
        std::string transform(const std::string_view&, const std::string_view&, const std::string_view&) const;

        std::future<std::string> reverse_async(const std::string_view&, unsigned char*) const;
        std::future<std::string> reverse_async(const std::string_view&, const std::string_view&) const;
        std::future<std::string> transform_async(const std::string_view&, unsigned char*, unsigned char*) const;
        std::future<std::string> transform_async(const std::string_view&, const std::string_view&, const std::string_view&) const;
    };
}

