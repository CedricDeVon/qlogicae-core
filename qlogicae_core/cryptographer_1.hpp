#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class Cryptographer1 : public Cryptographer
    {
    public:
        Cryptographer1();
        ~Cryptographer1() = default;
        Cryptographer1(const Cryptographer1&) = delete;
        Cryptographer1(Cryptographer1&&) noexcept = delete;
        Cryptographer1& operator = (Cryptographer1&&) = delete;
        Cryptographer1& operator = (const Cryptographer1&) = delete;

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

