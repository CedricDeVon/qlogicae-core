#include "pch.hpp"

#include "qlogicae_core/text_file_io.hpp"

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
        std::string input = GetParam();
        ASSERT_TRUE(file.write(""));
        ASSERT_TRUE(file.append(input));
        ASSERT_TRUE(file.append(input));
        std::string expected = input + input;
        EXPECT_EQ(file.read(), expected);
    }

    TEST_P(TextFileIOTest, Should_Expect_Success_When_UsingAsync)
    {
        QLogicaeCore::TextFileIO file(path);
        std::string input = GetParam();
        auto future_write = file.write_async(input);
        ASSERT_TRUE(future_write.get());
        auto future_read = file.read_async();
        EXPECT_EQ(future_read.get(), input);
    }

    TEST(TextFileIOStressTest, Should_Expect_NoRace_When_AccessedConcurrently)
    {
        QLogicaeCore::TextFileIO file("stress.txt");
        file.write("");
        std::vector<std::thread> thread_list;

        for (int index = 0; index < 64; ++index)
        {
            thread_list.emplace_back([&file]() {
                file.append("x");
                });
        }

        for (auto& thread : thread_list)
        {
            thread.join();
        }

        std::string result = file.read();
        EXPECT_EQ(result.size(), 64);
        std::filesystem::remove("stress.txt");
    }

    TEST(TextFileIOPerfTest, Should_Expect_Speed_When_RunningWrite)
    {
        QLogicaeCore::TextFileIO file("perf.txt");
        auto start = std::chrono::high_resolution_clock::now();

        for (int index = 0; index < 1000; ++index)
        {
            file.write("test");
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_LE(elapsed, 2000);
        std::filesystem::remove("perf.txt");
    }

    TEST(TextFileIOPerfTest, Should_Expect_FastAppend_When_UsingAsync)
    {
        QLogicaeCore::TextFileIO file("perf_async.txt");
        auto start = std::chrono::high_resolution_clock::now();

        auto future = file.append_async("data");
        future.get();

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_LE(elapsed, 1);
        std::filesystem::remove("perf_async.txt");
    }

    TEST(TextFileIOErrorTest, Should_Expect_Failure_When_UsingInvalidPath)
    {
        EXPECT_ANY_THROW(
            {
                QLogicaeCore::TextFileIO file("/invalid_path/file.txt");
                file.write("fail");
                EXPECT_EQ(file.read(), "");
            });
    }

    TEST(TextFileIOEdgeTest, Should_Expect_Empty_When_ReadingNonexistentFile)
    {
        QLogicaeCore::TextFileIO file("nonexistet.txt");
        EXPECT_EQ(file.read(), "");
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

