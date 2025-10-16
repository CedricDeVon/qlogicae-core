#include "pch.hpp"

#include "generator.hpp"

namespace QLogicaeCore
{
    Generator::Generator()
    {
        static const int status = sodium_init();
        if (status < 0)
        {
            throw std::runtime_error(
                "Exception at: Generator::Generator(): Sodium initialization failed"
            );
        }
    }

    Generator& Generator::get_instance()
    {
        static Generator get_instance;

        return get_instance;
    }
    
    std::string Generator::random_hex(
        const size_t& length,
        const std::string_view& character_set) const
    {
        try
        {
            if (character_set.empty() || length < 1)
            {
                return "";
            }

            const std::string raw = random_string(length, character_set);
            return ENCODER.from_utf8_to_hex(raw);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_hex(): " + exception.what()
            );
        }
    }

    std::string Generator::random_rgb_hex() const
    {
        try
        {
            std::string result;
            fmt::format_to(
                std::back_inserter(result),
                "#{}",
                random_hex(6)
            );

            return result;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_rgb_hex(): " + exception.what()
            );
        }
    }

    std::string Generator::random_rgba_hex() const
    {
        try
        {
            std::string result;
            fmt::format_to(
                std::back_inserter(result),
                "#{}",
                random_hex(8)
            );

            return result;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_rgba_hex(): " + exception.what()
            );
        }
    }

    std::string Generator::random_base64(
        const size_t& length,
        const std::string_view& character_set) const
    {
        try
        {
            if (character_set.size() < 64 || length < 1)
            {
                return "";
            }

            const std::string raw = random_string(length, character_set);
            return ENCODER.from_utf8_to_base64(raw);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_base64(): " + exception.what()
            );
        }
    }

    std::string Generator::random_uuid4() const
    {
        try
        {
            thread_local uuids::uuid_random_generator uuid_generator(
                _random_m19937()
            );

            return uuids::to_string(uuid_generator());
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_uuid4(): " + exception.what()
            );
        }
    }

    std::array<unsigned char, 16> Generator::random_salt() const
    {
        try
        {
            std::array<unsigned char, 16> salt{};
            randombytes_buf(salt.data(), salt.size());
            return salt;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_salt(): " + exception.what()
            );
        }
    }

    bool Generator::random_bool(const double& true_probability) const
    {
        try
        {
            if (true_probability < 1)
            {
                return false;
            }

            return std::bernoulli_distribution(
                true_probability)(_random_m19937());
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_bool(): " + exception.what()
            );
        }
    }

    std::vector<std::string> Generator::random_string_vector(
        const size_t& size,
        const size_t& length) const
    {
        try
        {
            size_t index;
            std::vector<std::string> result;
            result.reserve(size);

            for (index = 0; index < size; ++index)
            {
                result.emplace_back(random_string(length));
            }

            return result;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_string_vector(): " + exception.what()
            );
        }
    }

    std::string Generator::random_string(
        const size_t& length,
        const std::string_view& character_set) const
    {
        try
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_string(): " + exception.what()
            );
        }

    }

    int Generator::random_int(
        const int& minimum, const int& maximum) const
    {
        try
        {
            if (maximum < minimum)
            {
                return 0;
            }

            return std::uniform_int_distribution<int>(
                minimum, maximum)(_random_m19937());
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_int(): " + exception.what()
            );
        }
    }

    double Generator::random_double(
        const double& minimum, const double& maximum) const
    {
        try
        {
            if (maximum < minimum)
            {
                return 0;
            }

            return std::uniform_real_distribution<double>(
                minimum, maximum)(_random_m19937());
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_double(): " + exception.what()
            );
        }
    }

    void Generator::random_bytes(
        unsigned char* buffer, size_t size) const
    {

        try
        {
            if (buffer == nullptr && size > 0)
            {
                return;
            }

            randombytes_buf(buffer, size);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at Generator::random_bytes(): " + exception.what()
            );
        }
    }

    std::mt19937& Generator::_random_m19937()
    {
        static thread_local std::mt19937 generator
        {
            std::random_device{}()
        };

        return generator;
    }

    void Generator::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    void Generator::random_uuid4(
        Result<std::string>& result
    ) const
    {
        thread_local uuids::uuid_random_generator uuid_generator(
            _random_m19937()
        );

        result.set_to_good_status_with_value(
            uuids::to_string(uuid_generator())
        );
    }

    void Generator::random_rgb_hex(
        Result<std::string>& result
    ) const
    {
        std::string content;
        fmt::format_to(
            std::back_inserter(content),
            "#{}",
            random_hex(6)
        );

        result.set_to_good_status_with_value(
            content
        );
    }

    void Generator::random_rgba_hex(
        Result<std::string>& result
    ) const
    {
        std::string content;
        fmt::format_to(
            std::back_inserter(content),
            "#{}",
            random_hex(8)
        );

        result.set_to_good_status_with_value(
            content
        );
    }

    void Generator::random_salt(
        Result<std::array<unsigned char, 16>>& result
    ) const
    {
        std::array<unsigned char, 16> salt{};
        randombytes_buf(salt.data(), salt.size());
        
        result.set_to_good_status_with_value(
            salt
        );
    }

    void Generator::random_bytes(
        Result<void>& result,
        unsigned char* buffer,
        size_t size
    ) const
    {
        if (buffer == nullptr && size > 0)
        {
            return result.set_to_bad_status_without_value(
                "Buffer is empty and size is greater than 0"
            );
        }
        
        randombytes_buf(buffer, size);
        result.set_to_good_status_without_value();
    }

    void Generator::random_bool(
        Result<bool>& result,
        const double& true_probability
    ) const
    {
        if (true_probability < 1)
        {
            return result.set_to_bad_status_without_value(
                "True probability is less than 1"
            );
        }

        result.set_to_good_status_with_value(
            std::bernoulli_distribution(
                true_probability
            )(_random_m19937())
        );
    }

    void Generator::random_string_vector(
        Result<std::vector<std::string>>& result,
        const size_t& size,
        const size_t& length
    ) const
    {
        size_t index;
        std::vector<std::string> content;
        content.reserve(size);

        for (index = 0; index < size; ++index)
        {
            content.emplace_back(random_string(length));
        }

        result.set_to_good_status_with_value(content);
    }

    void Generator::random_hex(
        Result<std::string>& result,
        const size_t& length,
        const std::string_view& character_set
    ) const
    {
        if (character_set.empty() || length < 1)
        {
            return result.set_to_bad_status_without_value(
                "Either character set is empty or output length is less than 1"
            );
        }

        ENCODER.from_utf8_to_hex(
            result, random_string(length, character_set)
        );
    }

    void Generator::random_string(
        Result<std::string>& result,
        const size_t& length,
        const std::string_view& character_set
    ) const
    {
        if (character_set.empty() || length < 1)
        {
            return result.set_to_bad_status_without_value(
                "Either character set is empty or output length is less than 1"
            );
        }

        std::string content;
        content.reserve(length);

        std::mt19937& random_engine = _random_m19937();

        std::uniform_int_distribution<std::size_t> distribution(
            0, character_set.size() - 1);

        for (std::size_t index = 0; index < length; ++index)
        {
            content += character_set[distribution(random_engine)];
        }

        result.set_to_good_status_with_value(content);
    }

    void Generator::random_base64(
        Result<std::string>& result,
        const size_t& length,
        const std::string_view& character_set
    ) const
    {
        if (character_set.size() < 64 || length < 1)
        {
            return result.set_to_bad_status_without_value(
                "Either character set length is less than 64 or length is less than 1"
            );
        }

        random_string(result, length, character_set);
        ENCODER.from_utf8_to_base64(result, result.get_value());
    }

    void Generator::random_int(
        Result<int>& result,
        const int& minimum,
        const int& maximum
    ) const
    {
        if (maximum < minimum)
        {
            return result.set_to_bad_status_without_value(
                "Maximum is less then minimum"
            );
        }

        result.set_to_good_status_with_value(
            std::uniform_int_distribution<int>(
            minimum, maximum)(_random_m19937())
        );
    }

    void Generator::random_double(
        Result<double>& result,
        const double& minimum,
        const double& maximum
    ) const
    {
        if (maximum < minimum)
        {
            return result.set_to_bad_status_without_value(
                "Maximum is less then minimum"
            );
        }

        result.set_to_good_status_with_value(
            std::uniform_real_distribution<double>(
                minimum, maximum)(_random_m19937())
        );
    }

    void Generator::get_instance(
        Result<Generator*>& result
    )
    {
        static Generator instance;

        result.set_to_good_status_with_value(&instance);
    }
}

