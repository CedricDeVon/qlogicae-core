#include "pch.h"

#include "qlogicae_core/binary_file_io.hpp"

namespace QLogicaeCoreTest
{
    class BinaryFileIOTest : public ::testing::TestWithParam<std::vector<std::byte>>
    {
    protected:
        std::string test_path = "test_binary_io.bin";

        void TearDown() override
        {
            std::error_code ec;
            std::filesystem::remove(test_path, ec);
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

        const bool has_bytes = !input.empty();

        const int writers = 4;
        const int readers = 4;
        const int iterations_per_writer = 25;
        const int iterations_per_reader = 50;

        std::atomic<bool> exception_occurred(false);

        auto writer_task = [&](int id) {
            try {
                for (int i = 0; i < iterations_per_writer; ++i) {
                    bool ok = file.append(input);
                    if (!ok) {
                        exception_occurred.store(true);
                        return;
                    }
                }
            }
            catch (...) {
                exception_occurred.store(true);
            }
            };

        auto reader_task = [&](int id) {
            try {
                for (int i = 0; i < iterations_per_reader; ++i) {
                    auto data = file.read();
                    (void)data; 
                }
            }
            catch (...) {
                exception_occurred.store(true);
            }
            };

        std::vector<std::thread> threads;
        for (int i = 0; i < writers; ++i) {
            threads.emplace_back(writer_task, i);
        }
        for (int i = 0; i < readers; ++i) {
            threads.emplace_back(reader_task, i);
        }

        for (auto& t : threads) {
            t.join();
        }

        ASSERT_FALSE(exception_occurred.load());

        if (has_bytes) {
            auto final_data = file.read();
            const std::size_t expected_size =
                static_cast<std::size_t>(writers) *
                static_cast<std::size_t>(iterations_per_writer) *
                input.size();
            ASSERT_EQ(final_data.size(), expected_size);
        }
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
