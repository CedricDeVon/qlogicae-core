#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class Cryptographer2 : public Cryptographer
    {
    public:
        Cryptographer2();
        ~Cryptographer2() = default;
        Cryptographer2(const Cryptographer2&) = delete;
        Cryptographer2(Cryptographer2&&) noexcept = delete;
        Cryptographer2& operator = (Cryptographer2&&) = delete;
        Cryptographer2& operator = (const Cryptographer2&) = delete;

        std::string reverse(const std::string_view&, const unsigned char*, const unsigned char*) const;
        std::string transform(const std::string_view&, const unsigned char*, const unsigned char*) const;
        std::string reverse(const std::string_view&, const std::string_view&, const std::string_view&) const;
        std::string transform(const std::string_view&, const std::string_view&, const std::string_view&) const;

        std::future<std::string> reverse_async(const std::string_view&, const unsigned char*, const unsigned char*) const;
        std::future<std::string> transform_async(const std::string_view&, const unsigned char*, const unsigned char*) const;
        std::future<std::string> reverse_async(const std::string_view&, const std::string_view&, const std::string_view&) const;
        std::future<std::string> transform_async(const std::string_view&, const std::string_view&, const std::string_view&) const;
    };
}

