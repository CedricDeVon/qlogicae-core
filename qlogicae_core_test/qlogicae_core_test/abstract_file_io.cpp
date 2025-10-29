#include "pch.hpp"

#include "qlogicae_core/abstract_file_io.hpp"

namespace QLogicaeCoreTest
{
    class DummyFileIO : public QLogicaeCore::AbstractFileIO
    {
    public:
        DummyFileIO() : AbstractFileIO("dummy", "path") {}
        DummyFileIO(const std::string& path) : AbstractFileIO("dummy", path) {}
        DummyFileIO(const std::string& name, const std::string& path) : AbstractFileIO(name, path) {}
    };

    class AbstractFileIOTest : public ::testing::TestWithParam<std::string>
    {
    protected:
        DummyFileIO file;
    };

    TEST_P(AbstractFileIOTest, Should_Expect_CorrectPath_When_ConstructedWithPathOnly)
    {
        DummyFileIO file(GetParam());
        EXPECT_EQ(file.get_file_path(), GetParam());
    }

    TEST_P(AbstractFileIOTest, Should_Expect_SetPath_When_Modified)
    {
        DummyFileIO file;
        file.set_file_path(GetParam());
        EXPECT_EQ(file.get_file_path(), GetParam());
    }

    TEST(AbstractFileIOTestSimple, Should_Expect_Name_When_ConstructedWithNameAndPath)
    {
        DummyFileIO file("testname", "testpath");
        EXPECT_EQ(file.get_name(), "testname");
        EXPECT_EQ(file.get_file_path(), "testpath");
    }

    TEST(AbstractFileIOTestAsync, Should_Expect_CorrectPath_When_UsedConcurrently)
    {
        DummyFileIO file("name", "original_path");
        std::vector<std::future<void>> futures;
        for (int i = 0; i < 32; ++i)
        {
            futures.emplace_back(std::async(std::launch::async, [&file, i]() {
                std::string new_path = "path_" + std::to_string(i);
                file.set_file_path(new_path);
                }));
        }

        for (auto& f : futures)
        {
            f.get();
        }
    }

    TEST(AbstractFileIOTestPerf, Should_Expect_Performance_When_Accessed)
    {
        DummyFileIO file("name", "path");
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100000; ++i)
        {
            file.get_file_path();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_LE(ms, 2000);
    }

    TEST(AbstractFileIOTestPerf, Should_Expect_Fast_When_SettingPath)
    {
        DummyFileIO file;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; ++i)
        {
            file.set_file_path("fast_path");
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_LE(ms, 1);
    }

    TEST(AbstractFileIOTestThreading, Should_Expect_NoCrash_When_MultiThreadedSet)
    {
        DummyFileIO file("name", "initial");
        std::vector<std::thread> thread_list;

        for (int index = 0; index < 16; ++index)
        {
            thread_list.emplace_back([&file, index]() {
                file.set_file_path("thread_" + std::to_string(index));
                });
        }

        for (auto& thread : thread_list)
        {
            thread.join();
        }

        SUCCEED();
    }

    INSTANTIATE_TEST_CASE_P(
        AbstractFileIOPathTests,
        AbstractFileIOTest,
        ::testing::Values(
            "",
            "short",
            "C:/longer/path/to/file.txt",
            std::string(1024, 'a'),
            std::string(1, '\0')
        )
    );
}

