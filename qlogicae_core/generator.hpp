#pragma once

#include "utilities.hpp"
#include "encoder.hpp"

#include <random>

namespace QLogicaeCore
{
    class Generator
    {
    public:
        std::string random_uuid4() const;

        std::string random_rgb_hex() const;

        std::string random_rgba_hex() const;

        std::array<unsigned char, 16> random_salt() const;

        void random_bytes(
            unsigned char* buffer, size_t size
        ) const;

        bool random_bool(
            const double& = UTILITIES.RANDOM_BOOLEAN_MAXIMUM
        ) const;

        std::vector<std::string> random_string_vector(
            const size_t&,
            const size_t& = UTILITIES.RANDOM_SIZE_T_BITS
        ) const;

        std::string random_hex(
            const size_t&,
            const std::string_view & =
                UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        ) const;

        std::string random_string(
            const size_t&,
            const std::string_view& =
                UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        ) const;

        std::string random_base64(
            const size_t&,
            const std::string_view & =
                UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        ) const;

        int random_int(
            const int& = std::numeric_limits<int>::min(),
            const int& = std::numeric_limits<int>::max()
        ) const;

        double random_double(
            const double& = UTILITIES.RANDOM_DOUBLE_MINIMUM,
            const double& = UTILITIES.RANDOM_DOUBLE_MAXIMUM
        ) const;

        static Generator& get_instance();

        void random_uuid4(Result<std::string>& result) const;

        void random_rgb_hex(Result<std::string>& result) const;

        void random_rgba_hex(Result<std::string>& result) const;

        void random_salt(Result<std::array<unsigned char, 16>>& result) const;

        void random_bytes(Result<void>& result,
            unsigned char* buffer, size_t size
        ) const;

        void random_bool(Result<bool>& result,
            const double& = UTILITIES.RANDOM_BOOLEAN_MAXIMUM
        ) const;

        void random_string_vector(Result<std::vector<std::string>>& result,
            const size_t&,
            const size_t & = UTILITIES.RANDOM_SIZE_T_BITS
        ) const;

        void random_hex(Result<std::string>& result,
            const size_t&,
            const std::string_view & =
            UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        ) const;

        void random_string(Result<std::string>& result,
            const size_t&,
            const std::string_view & =
            UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        ) const;

        void random_base64(Result<std::string>& result,
            const size_t&,
            const std::string_view & =
            UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        ) const;

        void random_int(Result<int>& result,
            const int& = std::numeric_limits<int>::min(),
            const int& = std::numeric_limits<int>::max()
        ) const;

        void random_double(Result<double>& result,
            const double& = UTILITIES.RANDOM_DOUBLE_MINIMUM,
            const double& = UTILITIES.RANDOM_DOUBLE_MAXIMUM
        ) const;

        static void get_instance(Result<Generator*>& result);

    protected:
        Generator();

        ~Generator() = default;

        Generator(const Generator& generator) = delete;

        Generator(Generator&& generator) noexcept = delete;

        Generator& operator = (Generator&& generator) = delete;

        Generator& operator = (const Generator& generator) = delete;

        static std::mt19937& _random_m19937();
    };

    inline static Generator& GENERATOR = Generator::get_instance();
}

