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

    bool Generator::setup()
    {
        try
        {
            Result<void> void_result;

            setup(void_result);

            return void_result.is_status_safe();
        }
        catch (const std::exception& exception)
        {

        }
    }

    void Generator::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    std::future<bool> Generator::setup_async()
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup()
                );
            }
        );

        return future;
    }

    void Generator::setup_async(
        Result<std::future<void>>& result
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, promise = std::move(promise)]() mutable
            {
                Result<void> void_result;

                setup(void_result);

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    std::string Generator::random_hex(
        const size_t& length,
        const std::string_view& character_set
    )
    {
        try
        {
            Result<std::string> string_result;

            random_hex(
                string_result,
                length,
                character_set
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_hex(
        Result<std::string>& result,
        const size_t& length,
        const std::string_view& character_set
    )
    {
        if (character_set.empty() || length < 1)
        {
            return result.set_to_bad_status_without_value(
                "Either character set is empty or output length is less than 1"
            );
        }

        ENCODER.from_utf8_to_hex(
            result,
            random_string(
                length, character_set
            )
        );
    }

    std::string Generator::random_base64(
        const size_t& length,
        const std::string_view& character_set
    )
    {
        try
        {
            Result<std::string> string_result;

            random_hex(
                string_result,
                length,
                character_set
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_base64(
        Result<std::string>& result,
        const size_t& length,
        const std::string_view& character_set
    )
    {
        if (character_set.size() < 64 || length < 1)
        {
            return result.set_to_bad_status_without_value(
                "Either character set length is less than 64 or length is less than 1"
            );
        }

        random_string(
            result,
            length,
            character_set
        );
        ENCODER.from_utf8_to_base64(
            result,
            result.get_value()
        );
    }

    std::string Generator::random_rgb_hex()
    {
        try
        {
            Result<std::string> string_result;

            random_rgb_hex(
                string_result
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_rgb_hex(
        Result<std::string>& result
    )
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

    std::string Generator::random_rgba_hex()
    {
        try
        {
            Result<std::string> string_result;

            random_rgba_hex(
                string_result
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_rgba_hex(
        Result<std::string>& result
    )
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

    std::string Generator::random_uuid4()
    {
        try
        {
            Result<std::string> string_result;

            random_rgba_hex(
                string_result
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_uuid4(
        Result<std::string>& result
    )
    {
        thread_local uuids::uuid_random_generator uuid_generator(
            _random_m19937()
        );

        result.set_to_good_status_with_value(
            uuids::to_string(uuid_generator())
        );
    }


    std::array<unsigned char, 16> Generator::random_salt()
    {
        try
        {
            Result<std::array<unsigned char, 16>> result;

            random_salt(
                result
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_salt(
        Result<std::array<unsigned char, 16>>& result
    )
    {
        std::array<unsigned char, 16> salt{};
        randombytes_buf(salt.data(), salt.size());

        result.set_to_good_status_with_value(
            salt
        );
    }

    bool Generator::random_bool(
        const double& true_probability
    )
    {
        try
        {
            Result<bool> result;

            random_bool(
                result,
                true_probability
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_bool(
        Result<bool>& result,
        const double& true_probability
    )
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

    std::vector<std::string> Generator::random_string_vector(
        const size_t& size,
        const size_t& length
    )
    {
        try
        {
            Result<std::vector<std::string>> result;

            random_string_vector(
                result,
                size,
                length
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_string_vector(
        Result<std::vector<std::string>>& result,
        const size_t& size,
        const size_t& length
    )
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

    std::string Generator::random_string(
        const size_t& length,
        const std::string_view& character_set
    )
    {
        try
        {
            Result<std::string> result;

            random_string(
                result,
                length,
                character_set
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_string(
        Result<std::string>& result,
        const size_t& length,
        const std::string_view& character_set
    )
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

    int Generator::random_int(
        const int& minimum,
        const int& maximum
    )
    {
        try
        {
            Result<int> result;

            random_int(
                result,
                minimum,
                maximum
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_int(
        Result<int>& result,
        const int& minimum,
        const int& maximum
    )
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

    double Generator::random_double(
        const double& minimum,
        const double& maximum
    )
    {
        try
        {
            Result<double> result;

            random_double(
                result,
                minimum,
                maximum
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_double(
        Result<double>& result,
        const double& minimum,
        const double& maximum
    )
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

    void Generator::random_bytes(
        unsigned char* buffer,
        size_t size
    )
    {
        try
        {
            Result<void> result;

            random_bytes(
                result,
                buffer,
                size
            );
        }
        catch (const std::exception& exception)
        {
            
        }
    }

    void Generator::random_bytes(
        Result<void>& result,
        unsigned char* buffer,
        size_t size
    )
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

    Generator& Generator::get_instance()
    {
        static Generator get_instance;

        return get_instance;
    }

    void Generator::get_instance(
        Result<Generator*>& result
    )
    {
        static Generator instance;

        result.set_to_good_status_with_value(&instance);
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

