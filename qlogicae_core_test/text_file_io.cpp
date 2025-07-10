#pragma once

#include "pch.h"

#include "text_file_io.hpp"

namespace QLogicaeCoreTest
{

    class TextFileIOTest : public ::testing::TestWithParam<std::string>
    {
    protected:
        std::string path = "test_file.txt";

        void TearDown() override
        {
            std::filesystem::remove(path);
        }
    };

    TEST_P(TextFileIOTest, Should_Expect_WriteAndRead_When_UsingValidText)
    {
        QLogicaeCore::TextFileIO file(path);
        ASSERT_TRUE(file.write(GetParam()));
        std::string content = file.read();
        EXPECT_EQ(content, GetParam());
    }

    TEST_P(TextFileIOTest, Should_Expect_Append_When_CalledMultipleTimes)
    {
        QLogicaeCore::TextFileIO file(path);
        ASSERT_TRUE(file.write(""));
        ASSERT_TRUE(file.append(GetParam()));
        ASSERT_TRUE(file.append(GetParam()));
        std::string expected = std::string(GetParam()) + std::string(GetParam());
        EXPECT_EQ(file.read(), expected);
    }

    TEST_P(TextFileIOTest, Should_Expect_Success_When_UsingAsync)
    {
        QLogicaeCore::TextFileIO file(path);
        auto future_write = file.write_async(GetParam());
        ASSERT_TRUE(future_write.get());
        auto future_read = file.read_async();
        EXPECT_EQ(future_read.get(), GetParam());
    }

    TEST(TextFileIOStressTest, Should_Expect_NoRace_When_AccessedConcurrently)
    {
        QLogicaeCore::TextFileIO file("stress.txt");
        file.write("");
        std::vector<std::thread> threads;
        for (int i = 0; i < 64; ++i)
        {
            threads.emplace_back([&file, i]() {
                file.append("x");
                });
        }
        for (auto& t : threads) t.join();
        std::string result = file.read();
        EXPECT_EQ(result.size(), 64);
        std::filesystem::remove("stress.txt");
    }

    TEST(TextFileIOPerfTest, Should_Expect_Speed_When_RunningWrite)
    {
        QLogicaeCore::TextFileIO file("perf.txt");
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i)
        {
            file.write("test");
        }
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), 2000);
        std::filesystem::remove("perf.txt");
    }

    TEST(TextFileIOPerfTest, Should_Expect_FastAppend_When_UsingAsync)
    {
        QLogicaeCore::TextFileIO file("perf_async.txt");
        auto start = std::chrono::high_resolution_clock::now();
        auto f = file.append_async("data");
        f.get();
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), 1);
        std::filesystem::remove("perf_async.txt");
    }

    INSTANTIATE_TEST_CASE_P(
        TextFileIOVariations,
        TextFileIOTest,
        ::testing::Values(
            "",
            "A",
            std::string(1024, 'z'),
            std::string(1, '\0'),
            "Unicode\u2713 test"
        )
    );

}

