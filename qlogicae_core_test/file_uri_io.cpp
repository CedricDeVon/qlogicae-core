#include "pch.h"

#include "file_uri_io.hpp"

namespace QLogicaeCoreTest
{
    class FileUriIOTest : public ::testing::TestWithParam<std::string>
    {
    protected:
        void SetUp() override
        {
            test_file_path = "test_file.bin";
            std::ofstream file(test_file_path, std::ios::binary);
            file << "TestData";
            file.close();
        }

        void TearDown() override
        {
            std::filesystem::remove(test_file_path);
            std::filesystem::remove("empty.bin");
            std::filesystem::remove("large_file.bin");
            std::filesystem::remove("no_access.bin");
        }

        std::string test_file_path;
    };

    TEST_P(FileUriIOTest, Should_ReturnDataUri_When_FileIsValid)
    {
        QLogicaeCore::FileUriIO file_uri_io(test_file_path);
        std::string result = file_uri_io.generate_data_uri();
        EXPECT_FALSE(result.empty());
    }

    TEST_P(FileUriIOTest, Should_ThrowException_When_FileIsMissing)
    {
        QLogicaeCore::FileUriIO file_uri_io("nonexistent.bin");
        EXPECT_THROW(file_uri_io.generate_data_uri(), std::runtime_error);
    }

    TEST_P(FileUriIOTest, Should_ReturnFuture_When_AsyncCalled)
    {
        QLogicaeCore::FileUriIO file_uri_io(test_file_path);
        std::future<std::string> future_result =
            file_uri_io.generate_data_uri_async();
        std::string result = future_result.get();
        EXPECT_FALSE(result.empty());
    }

    TEST_P(FileUriIOTest, Should_CompleteWithinLimit_When_StressTested)
    {
        QLogicaeCore::FileUriIO file_uri_io(test_file_path);
        std::atomic<int> counter = 0;
        std::vector<std::future<void>> threads;

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; ++i)
        {
            threads.push_back(std::async(
                std::launch::async,
                [&file_uri_io, &counter]()
                {
                    std::string uri = file_uri_io.generate_data_uri();
                    if (!uri.empty())
                    {
                        ++counter;
                    }
                }));
        }

        for (auto& t : threads)
        {
            t.get();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double>(end - start);

        EXPECT_EQ(counter, 100);
        EXPECT_LE(duration.count(), 2.0);
    }

    TEST_P(FileUriIOTest, Should_HandleEmptyFile_When_FileIsEmpty)
    {
        std::ofstream empty_file("empty.bin");
        empty_file.close();

        QLogicaeCore::FileUriIO file_uri_io("empty.bin");
        std::string result = file_uri_io.generate_data_uri();
        EXPECT_TRUE(result.find("base64,") != std::string::npos);
    }

    TEST_P(FileUriIOTest, Should_ThrowException_When_PathIsDirectory)
    {
        QLogicaeCore::FileUriIO file_uri_io("./");
        EXPECT_THROW(file_uri_io.generate_data_uri(), std::runtime_error);
    }

    TEST_P(FileUriIOTest, Should_CompleteUnderTime_When_FileIsLarge)
    {
        std::ofstream large_file("large_file.bin", std::ios::binary);
        std::string chunk(1024 * 1024, 'x');
        for (int i = 0; i < 5; ++i)
        {
            large_file << chunk;
        }
        large_file.close();

        QLogicaeCore::FileUriIO file_uri_io("large_file.bin");
        auto start = std::chrono::high_resolution_clock::now();
        std::string result = file_uri_io.generate_data_uri();
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration<double>(end - start);
        EXPECT_FALSE(result.empty());
        EXPECT_LE(duration.count(), 2.0);
    }

    TEST_P(FileUriIOTest, Should_ConstructWithName_When_ThreeArgsPassed)
    {
        QLogicaeCore::FileUriIO file_uri_io(test_file_path, "text/plain", "CustomName");
        std::string result = file_uri_io.generate_data_uri();
        EXPECT_FALSE(result.empty());
    }

    INSTANTIATE_TEST_CASE_P(
        FileUriIOTestInstances,
        FileUriIOTest,
        ::testing::Values("application/octet-stream", "text/plain"));
}

