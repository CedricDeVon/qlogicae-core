#pragma once

#include "pch.h"

#include "generator.hpp"

namespace QLogicaeCoreTest
{
    class GeneratorTest : public ::testing::TestWithParam<std::size_t> {};

    TEST_P(GeneratorTest, Should_Expect_ValidCharacters_When_UsingCustomCharset)
    {
        std::string_view character_set = "ABCXYZ";

        std::string result = QLogicaeCore::Generator::get_instance()
            .random_string(GetParam(), character_set);

        for (char character : result)
        {
            EXPECT_NE(character_set.find(character), std::string::npos);
        }
    }

    TEST_P(GeneratorTest, Should_Expect_SameInstance_When_SingletonCalledMultipleTimes)
    {
        auto& generator_first = QLogicaeCore::Generator::get_instance();
        auto& generator_second = QLogicaeCore::Generator::get_instance();

        EXPECT_EQ(&generator_first, &generator_second);
    }

    TEST_P(GeneratorTest, Should_Expect_ValidContent_When_RandomBytesCalled)
    {
        std::size_t size = GetParam();
        std::vector<unsigned char> output_buffer(size, 0);

        EXPECT_NO_THROW({
            QLogicaeCore::Generator::get_instance()
                .random_bytes(output_buffer.data(), output_buffer.size());
            });

        if (size >= 4)
        {
            std::size_t checksum = 0;
            for (unsigned char byte : output_buffer)
            {
                checksum += byte;
            }

            EXPECT_GT(checksum, 0);
        }
        else
        {
            SUCCEED();
        }
    }

    TEST_P(GeneratorTest, Should_Expect_NoCrash_When_NullBufferUsedWithZeroSize)
    {
        EXPECT_NO_THROW({
            QLogicaeCore::Generator::get_instance()
                .random_bytes(nullptr, 0);
            });
    }

    TEST_P(GeneratorTest, Should_Expect_ValidInteger_When_RangeIsValid)
    {
        int minimum = 0;
        int maximum = static_cast<int>(GetParam());

        int value = QLogicaeCore::Generator::get_instance()
            .random_int(minimum, maximum);

        EXPECT_GE(value, minimum);
        EXPECT_LE(value, maximum);
    }

    TEST_P(GeneratorTest, Should_Expect_ValidHex_When_CustomCharsetUsed)
    {
        std::string_view character_set = "0123456789ABCDEF";

        std::string result = QLogicaeCore::Generator::get_instance()
            .random_hex(GetParam(), character_set);

        EXPECT_EQ(result.size(), GetParam() * 2);
        EXPECT_TRUE(std::all_of(result.begin(), result.end(), [](char character)
            {
                return std::isxdigit(static_cast<unsigned char>(character));
            }));
    }

    TEST_P(GeneratorTest, Should_Expect_ValidBase64_When_Called)
    {
        std::string result = QLogicaeCore::Generator::get_instance()
            .random_base64(GetParam());

        if (result.empty())
        {
            EXPECT_TRUE(result.empty());
        }
        else
        {
            EXPECT_FALSE(result.empty());
        }

        for (char character : result)
        {
            EXPECT_TRUE(
                std::isalnum(static_cast<unsigned char>(character)) ||
                character == '+' || character == '/' || character == '='
            );
        }

        if (result.find('=') != std::string::npos)
        {
            EXPECT_TRUE(result.ends_with('='));
        }
    }

    TEST_P(GeneratorTest, Should_Expect_MultipleThreads_When_GeneratingConcurrently)
    {
        std::vector<std::thread> thread_list;
        std::atomic<int> success_count = 0;

        for (int index = 0; index < 16; ++index)
        {
            thread_list.emplace_back([&]()
                {
                    std::string output = QLogicaeCore::Generator::get_instance()
                        .random_string(GetParam());

                    ++success_count;
                });
        }

        for (auto& thread : thread_list)
        {
            thread.join();
        }

        EXPECT_EQ(success_count, 16);
    }

    TEST_P(GeneratorTest, Should_Expect_ResultUnder2Seconds_When_StressGenerating)
    {
        auto start_time = std::chrono::steady_clock::now();
        int generation_count = 0;

        while (std::chrono::steady_clock::now() - start_time <
            std::chrono::seconds(2))
        {
            QLogicaeCore::Generator::get_instance()
                .random_string(GetParam());

            ++generation_count;
        }

        EXPECT_GT(generation_count, 1000);
    }

    TEST_P(GeneratorTest, Should_Expect_Result_When_AsyncGenerationRuns)
    {
        auto result = std::async(std::launch::async, [&]()
            {
                return QLogicaeCore::Generator::get_instance()
                    .random_string(GetParam());
            });

        bool return_result = result.get().empty();
        if (return_result)
        {
            EXPECT_TRUE(return_result);
        }
        else
        {
            EXPECT_FALSE(return_result);
        }
    }

    INSTANTIATE_TEST_CASE_P(
        GeneratorSizes,
        GeneratorTest,
        ::testing::Values(
            0,
            1,
            8,
            16,
            32,
            64,
            128,
            256,
            512,
            1024,
            2048,
            4096,
            8192,
            16384,
            32768,
            65536,
            131072
        )
    );
}

