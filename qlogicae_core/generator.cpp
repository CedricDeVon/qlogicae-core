#pragma once

#include "pch.h"

#include "generator.hpp"

namespace QLogicaeCore
{
    Generator& Generator::instance()
    {
        static Generator instance;

        return instance;
    }
    
    std::string Generator::random_hex(
        const size_t& length,
        const std::string_view& character_set)
    {
        return Encoder::instance().from_utf8_to_hex(
            random_string(length, character_set)
        );
    }

    std::string Generator::random_base64(
        const size_t& length,
        const std::string_view& character_set)
    {
        return Encoder::instance().from_utf8_to_base64(
            random_string(length, character_set)
        );
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
        std::random_device va;
        std::array<unsigned char, 16> vb{};
        std::generate(vb.begin(), vb.end(), std::ref(va));

        return vb;
    }

    bool Generator::random_bool(const double& true_probability) const
    {
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
        if (character_set.empty() || length == 0)
        {
            return "";
        }

        size_t index;
        std::string result;
        result.reserve(length);

        for (index = 0; index < length; ++index)
        {
            result += character_set[
                randombytes_uniform(
                    static_cast<uint32_t>(character_set.size()))
            ];
        }

        return result;
    }

    int Generator::random_int(
        const int& minimum, const int& maximum) const
    {
        return std::uniform_int_distribution<int>(
            minimum, maximum)(_random_m19937());
    }

    double Generator::random_double(
        const double& minimum, const double& maximum) const
    {
        return std::uniform_real_distribution<double>(
            minimum, maximum)(_random_m19937());
    }

    void Generator::random_bytes(
        unsigned char* buffer, size_t size) const
    {
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

