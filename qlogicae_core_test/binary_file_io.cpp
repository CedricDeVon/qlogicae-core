#pragma once

#include "pch.h"

#include "binary_file_io.hpp"

namespace QLogicaeCoreTest
{
    class BinaryFileIOTest : public ::testing::TestWithParam<std::vector<std::byte>>
    {
    protected:
        std::string test_path = "test_binary_io.bin";

        void TearDown() override
        {
            std::filesystem::remove(test_path);
        }
    };

    TEST_P(BinaryFileIOTest, Should_WriteAndReadCorrectBytes_When_ValidContentIsUsed)
    {
        QLogicaeCore::BinaryFileIO file(test_path);

        std::vector<std::byte> input = GetParam();
        ASSERT_TRUE(file.write(input));

        std::vector<std::byte> output = file.read();
        ASSERT_EQ(output, input);
    }

    TEST_P(BinaryFileIOTest, Should_AppendCorrectly_When_MultipleAppendsUsed)
    {
        QLogicaeCore::BinaryFileIO file(test_path);
        std::vector<std::byte> input = GetParam();
        ASSERT_TRUE(file.append(input));
        ASSERT_TRUE(file.append(input));

        std::vector<std::byte> result = file.read();
        ASSERT_EQ(result.size(), input.size() * 2);
    }

    TEST_P(BinaryFileIOTest, Should_ReturnFalse_When_InvalidOpenMode)
    {
        QLogicaeCore::BinaryFileIO file(test_path);
        ASSERT_FALSE(file.open(static_cast<QLogicaeCore::FileMode>(-1)));
    }

    TEST_P(BinaryFileIOTest, Should_ReturnEmpty_When_FileDoesNotExist)
    {
        QLogicaeCore::BinaryFileIO file("nonexistent.bin");
        std::vector<std::byte> result = file.read();
        ASSERT_TRUE(result.empty());
    }

    TEST_P(BinaryFileIOTest, Should_HandleAsyncReadWrite_When_CorrectlyUsed)
    {
        QLogicaeCore::BinaryFileIO file(test_path);
        std::vector<std::byte> input = GetParam();

        auto write_future = file.write_async(input);
        ASSERT_TRUE(write_future.get());

        auto read_future = file.read_async();
        std::vector<std::byte> result = read_future.get();
        ASSERT_EQ(result, input);
    }

    TEST_P(BinaryFileIOTest, Should_BeThreadSafe_When_UsedConcurrently)
    {
        QLogicaeCore::BinaryFileIO file(test_path);
        std::vector<std::byte> input = GetParam();

        auto write_task = [&]() {
            for (int i = 0; i < 10; ++i) {
                file.write(input);
            }
            };

        auto read_task = [&]() {
            for (int i = 0; i < 10; ++i) {
                file.read();
            }
            };

        std::thread t1(write_task);
        std::thread t2(read_task);
        t1.join();
        t2.join();
    }

    TEST_P(BinaryFileIOTest, Should_SucceedQuickly_When_PerformanceIsMeasured)
    {
        QLogicaeCore::BinaryFileIO file(test_path);
        std::vector<std::byte> input = GetParam();

        auto start = std::chrono::steady_clock::now();
        ASSERT_TRUE(file.write(input));
        auto duration = std::chrono::steady_clock::now() - start;
        ASSERT_LE(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count(), 2000);
    }

    TEST_P(BinaryFileIOTest, Should_ExitGracefully_When_DeathOnInvalidPath)
    {
        ASSERT_EXIT({
            QLogicaeCore::BinaryFileIO file("/invalid\0path", "bad");
            file.write(GetParam());
            exit(0);
            }, ::testing::ExitedWithCode(0), "");
    }

    INSTANTIATE_TEST_CASE_P(
        BinaryFileIOTestCases,
        BinaryFileIOTest,
        ::testing::Values(
            std::vector<std::byte>{},
            std::vector<std::byte>{std::byte{ 0x00 }, std::byte{ 0xFF }, std::byte{ 0x7A }},
            std::vector<std::byte>(1024, std::byte{ 0xAB }),
            std::vector<std::byte>(8192, std::byte{ 0x1F })
        )
    );
}

