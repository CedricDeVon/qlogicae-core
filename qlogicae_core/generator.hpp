#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "globals.hpp"

namespace QLogicaeCore
{
    class Generator
    {
    public:
        std::string random_uuid4() const;
        std::string random_rgb_hex() const;
        std::string random_rgba_hex() const;
        std::array<unsigned char, 16> random_salt() const;
        void random_bytes(unsigned char* buffer, size_t size) const;
        bool random_bool(const double& = Constants::RANDOM_BOOLEAN_MAXIMUM) const;
        std::vector<std::string> random_string_vector(const size_t&, const size_t& = Constants::RANDOM_SIZE_T_BITS) const;
        std::string random_hex(const size_t&, const std::string_view & = Constants::FULL_VISIBLE_ASCII_CHARACTERSET) const;
        std::string random_string(const size_t&, const std::string_view& = Constants::FULL_VISIBLE_ASCII_CHARACTERSET) const;
        std::string random_base64(const size_t&, const std::string_view & = Constants::FULL_VISIBLE_ASCII_CHARACTERSET) const;
        int random_int(const int& = std::numeric_limits<int>::min(), const int& = std::numeric_limits<int>::max()) const;
        double random_double(const double& = Constants::RANDOM_DOUBLE_MINIMUM, const double& = Constants::RANDOM_DOUBLE_MAXIMUM) const;

        static Generator& get_instance();

    protected:
        Generator();
        ~Generator() = default;
        Generator(const Generator&) = delete;
        Generator(Generator&&) noexcept = delete;
        Generator& operator = (Generator&&) = delete;
        Generator& operator = (const Generator&) = delete;

        static std::mt19937& _random_m19937();
    };
}

