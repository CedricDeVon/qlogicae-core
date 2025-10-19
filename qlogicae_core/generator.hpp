#pragma once

#include "utilities.hpp"
#include "encoder.hpp"

#include <random>

namespace QLogicaeCore
{
    class Generator
    {
    public:
        std::string random_uuid4();

        std::string random_rgb_hex();

        std::string random_rgba_hex();

        std::array<unsigned char, 16> random_salt();

        void random_bytes(
            unsigned char* buffer, size_t size
        );

        bool random_bool(
            const double& = UTILITIES.RANDOM_BOOLEAN_MAXIMUM
        );

        std::vector<std::string> random_string_vector(
            const size_t&,
            const size_t& = UTILITIES.RANDOM_SIZE_T_BITS
        );

        std::string random_hex(
            const size_t&,
            const std::string_view & =
                UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        );

        std::string random_string(
            const size_t&,
            const std::string_view& =
                UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        );

        std::string random_base64(
            const size_t&,
            const std::string_view & =
                UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        );

        int random_int(
            const int& = std::numeric_limits<int>::min(),
            const int& = std::numeric_limits<int>::max()
        );

        double random_double(
            const double& = UTILITIES.RANDOM_DOUBLE_MINIMUM,
            const double& = UTILITIES.RANDOM_DOUBLE_MAXIMUM
        );

        static Generator& get_instance();

        void setup(
            Result<void>& result
        );

        void random_uuid4(
            Result<std::string>& result
        );

        void random_rgb_hex(
            Result<std::string>& result
        );

        void random_rgba_hex(
            Result<std::string>& result
        );

        void random_salt(
            Result<std::array<unsigned char, 16>>& result
        );

        void random_bytes(
            Result<void>& result,
            unsigned char* buffer, size_t size
        );

        void random_bool(
            Result<bool>& result,
            const double& = UTILITIES.RANDOM_BOOLEAN_MAXIMUM
        );

        void random_string_vector(
            Result<std::vector<std::string>>& result,
            const size_t&,
            const size_t & = UTILITIES.RANDOM_SIZE_T_BITS
        );

        void random_hex(
            Result<std::string>& result,
            const size_t&,
            const std::string_view & =
            UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        );

        void random_string(
            Result<std::string>& result,
            const size_t&,
            const std::string_view & =
            UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        );

        void random_base64(
            Result<std::string>& result,
            const size_t&,
            const std::string_view & =
            UTILITIES.FULL_VISIBLE_ASCII_CHARACTERSET
        );

        void random_int(
            Result<int>& result,
            const int& = std::numeric_limits<int>::min(),
            const int& = std::numeric_limits<int>::max()
        );

        void random_double(
            Result<double>& result,
            const double& = UTILITIES.RANDOM_DOUBLE_MINIMUM,
            const double& = UTILITIES.RANDOM_DOUBLE_MAXIMUM
        );

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

