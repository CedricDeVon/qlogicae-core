#include "pch.hpp"

#include "qlogicae_core/cli_io.hpp"

namespace QLogicaeCoreTest
{
    class CliIOTest : public ::testing::Test {};

    class ScanFlagParameterizedTest : public ::testing::TestWithParam<bool> {};

    class PrintFlagParameterizedTest : public ::testing::TestWithParam<bool> {};

    TEST_F(CliIOTest, Should_Expect_DefaultEnabled_When_Initialized)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        EXPECT_TRUE(cli.is_scan_enabled());
        EXPECT_TRUE(cli.is_print_enabled());
    }

    TEST_F(CliIOTest, Should_Expect_CorrectState_When_SetFlags)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        cli.set_scan_enabled(false);
        cli.set_print_enabled(false);
        EXPECT_FALSE(cli.is_scan_enabled());
        EXPECT_FALSE(cli.is_print_enabled());
        cli.set_scan_enabled(true);
        cli.set_print_enabled(true);
        EXPECT_TRUE(cli.is_scan_enabled());
        EXPECT_TRUE(cli.is_print_enabled());
    }

    TEST_F(CliIOTest, Should_Expect_Output_When_Print)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        testing::internal::CaptureStdout();
        cli.print("A");
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "A");
    }

    TEST_F(CliIOTest, Should_Expect_CorrectBehavior_When_PrintEmptyString)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        testing::internal::CaptureStdout();
        cli.print("");
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "");
    }

    TEST_F(CliIOTest, Should_Expect_CorrectBehavior_When_PrintLargeString)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        std::string large_text(100000, 'X');
        testing::internal::CaptureStdout();
        cli.print(large_text);
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, large_text);
    }

    TEST_F(CliIOTest, Should_Expect_FutureResult_When_ScanAsyncWithInputRedirect)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        std::istringstream input("inputtest");
        std::cin.rdbuf(input.rdbuf());
        std::future<std::string> result = cli.scan_async();
        EXPECT_EQ(result.get(), "inputtest");
    }

    TEST_F(CliIOTest, Should_Expect_Output_When_PrintWithNewLine)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        testing::internal::CaptureStdout();
        cli.print_with_new_line("B");
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "B\n");
    }

    TEST_F(CliIOTest, Should_Expect_Output_When_BuiltinPrint)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        testing::internal::CaptureStdout();
        cli.builtin_print("C");
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "C");
    }

    TEST_F(CliIOTest, Should_Expect_Output_When_BuiltinPrintWithNewLine)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        testing::internal::CaptureStdout();
        cli.builtin_print_with_new_line("D");
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "D");
    }

    TEST_F(CliIOTest, Should_Expect_EmptyString_When_ScanFallbackTriggered)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        std::istringstream input_stream;
        std::cin.rdbuf(input_stream.rdbuf());
        std::string result = cli.scan();
        EXPECT_EQ(result, "");
    }

    TEST_F(CliIOTest, Should_Expect_ParallelExecution_When_UsingThreads)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        std::vector<std::thread> thread_list;

        for (int index = 0; index < 8; ++index)
        {
            thread_list.emplace_back([&cli]() {
                cli.print("E");
                });
        }

        for (auto& thread : thread_list)
        {
            thread.join();
        }

        SUCCEED();
    }

    TEST_F(CliIOTest, Should_Expect_StressExecution_When_HighLoad)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        auto begin = std::chrono::steady_clock::now();
        std::atomic<int> operation_count(0);

        while (std::chrono::steady_clock::now() - begin < std::chrono::seconds(2))
        {
            cli.print("F");
            ++operation_count;
        }

        EXPECT_GT(operation_count.load(), 1000);
    }

    TEST_F(CliIOTest, Should_Expect_AsyncToComplete_When_PrintAsync)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        std::future<void> result = cli.print_async("G");
        result.get();
        SUCCEED();
    }

    TEST_F(CliIOTest, Should_Expect_UnderTwoSeconds_When_AllOperations)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        auto start = std::chrono::steady_clock::now();

        cli.print("H");
        cli.print_with_new_line("I");
        cli.builtin_print("J");
        cli.builtin_print_with_new_line("K");

        cli.print_async("L").get();
        cli.print_with_new_line_async("M").get();
        cli.builtin_print_async("N").get();
        cli.builtin_print_with_new_line_async("O").get();

        auto end = std::chrono::steady_clock::now();
        EXPECT_LT(std::chrono::duration_cast<std::chrono::seconds>(end - start).count(), 2);
    }

    TEST_P(ScanFlagParameterizedTest, Should_Expect_CorrectScanFlag_When_Set)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        cli.set_scan_enabled(GetParam());
        EXPECT_EQ(cli.is_scan_enabled(), GetParam());
    }

    INSTANTIATE_TEST_CASE_P(AllStates, ScanFlagParameterizedTest,
        ::testing::Values(true, false));

    TEST_P(PrintFlagParameterizedTest, Should_Expect_CorrectPrintFlag_When_Set)
    {
        QLogicaeCore::CliIO& cli = QLogicaeCore::CliIO::get_instance();
        cli.set_print_enabled(GetParam());
        EXPECT_EQ(cli.is_print_enabled(), GetParam());
    }

    INSTANTIATE_TEST_CASE_P(AllStates, PrintFlagParameterizedTest,
        ::testing::Values(true, false));

}
