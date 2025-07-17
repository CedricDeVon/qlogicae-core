#pragma once

#include "pch.h"

#include "generator.hpp"

namespace QLogicaeCore
{
    Generator::Generator()
    {
        static const int status = sodium_init();
        if (status < 0)
        {
            throw std::runtime_error("sodium_init failed");
        }
    }

    Generator& Generator::get_instance()
    {
        static Generator get_instance;

        return get_instance;
    }
    
    std::string Generator::random_hex(
        const size_t& length,
        const std::string_view& character_set)
    {
        if (character_set.empty() || length < 1)
        {
            return "";
        }

        const std::string raw = random_string(length, character_set);
        return Encoder::get_instance().from_utf8_to_hex(raw);
    }

    std::string Generator::random_base64(
        const size_t& length,
        const std::string_view& character_set)
    {
        if (character_set.size() < 64 || length < 1)
        {
            return "";
        }

        const std::string raw = random_string(length, character_set);
        return Encoder::get_instance().from_utf8_to_base64(raw);
    }

    std::string Generator::random_uuid4() const
    {
        thread_local uuids::uuid_random_generator uuid_generator(
            _random_m19937()
        );

        return uuids::to_string(uuid_generator());
    }

    std::array<unsigned char, 16> Generator::random_salt() const
    {
        std::array<unsigned char, 16> salt{};
        randombytes_buf(salt.data(), salt.size());
        return salt;
    }

    bool Generator::random_bool(const double& true_probability) const
    {
        if (true_probability < 1)
        {
            return false;
        }

        return std::bernoulli_distribution(
            true_probability)(_random_m19937());
    }

    std::vector<std::string> Generator::random_string_vector(
        const size_t& size,
        const size_t& length)
    {
        size_t index;
        std::vector<std::string> result;
        result.reserve(size);

        for (index = Constants::NUMBER_ZERO; index < size; ++index)
        {
            result.emplace_back(random_string(length));
        }

        return result;
    }

    std::string Generator::random_string(
        const size_t& length,
        const std::string_view& character_set)
    {
        if (character_set.empty() || length < 1)
        {
            return "";
        }

        std::string result;
        result.reserve(length);

        std::mt19937& random_engine = _random_m19937();

        std::uniform_int_distribution<std::size_t> distribution(
            0, character_set.size() - 1);

        for (std::size_t index = 0; index < length; ++index)
        {
            result += character_set[distribution(random_engine)];
        }

        return result;
    }

    int Generator::random_int(
        const int& minimum, const int& maximum) const
    {
        if (maximum < minimum)
        {
            throw std::invalid_argument("Invalid range");
        }

        return std::uniform_int_distribution<int>(
            minimum, maximum)(_random_m19937());
    }

    double Generator::random_double(
        const double& minimum, const double& maximum) const
    {
        if (maximum < minimum)
        {
            throw std::invalid_argument("Invalid range");
        }

        return std::uniform_real_distribution<double>(
            minimum, maximum)(_random_m19937());
    }

    void Generator::random_bytes(
        unsigned char* buffer, size_t size) const
    {
        if (buffer == nullptr && size > 0)
        {
            throw std::invalid_argument("Null buffer with non-zero size");
        }

        randombytes_buf(buffer, size);
    }


    std::mt19937& Generator::_random_m19937()
    {
        static thread_local std::mt19937 generator
        {
            std::random_device{}()
        };

        return generator;
    }
}

