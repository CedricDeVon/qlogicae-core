#pragma once

#include "pch.h"

#include "cli_io.hpp"

namespace QLogicaeCoreTest
{
    class CliIOTest : public ::testing::Test {};

    TEST_F(CliIOTest, Should_Expect_DefaultEnabled_When_Initialized)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        EXPECT_TRUE(cli.is_scan_enabled());
        EXPECT_TRUE(cli.is_print_enabled());
    }

    TEST_F(CliIOTest, Should_Expect_CorrectState_When_SetFlags)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
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
        auto& cli = QLogicaeCore::CliIO::instance();
        testing::internal::CaptureStdout();
        cli.print("Hello");
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "Hello");
    }

    TEST_F(CliIOTest, Should_Expect_Output_When_PrintWithNewLine)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        testing::internal::CaptureStdout();
        cli.print_with_new_line("World");
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "World\n");
    }

    TEST_F(CliIOTest, Should_Expect_Output_When_BuiltinPrint)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        testing::internal::CaptureStdout();
        cli.builtin_print("Builtin");
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "Builtin");
    }

    TEST_F(CliIOTest, Should_Expect_Output_When_BuiltinPrintWithNewLine)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        testing::internal::CaptureStdout();
        cli.builtin_print_with_new_line("Text");
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "Text");
    }

    TEST_F(CliIOTest, Should_Expect_FutureCompleted_When_PrintAsync)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        auto result = cli.print_async("Hello");
        result.get();
        SUCCEED();
    }

    TEST_F(CliIOTest, Should_Expect_FutureCompleted_When_PrintWithNewLineAsync)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        auto result = cli.print_with_new_line_async("World");
        result.get();
        SUCCEED();
    }

    TEST_F(CliIOTest, Should_Expect_FutureCompleted_When_BuiltinPrintAsync)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        auto result = cli.builtin_print_async("Test");
        result.get();
        SUCCEED();
    }

    TEST_F(CliIOTest, Should_Expect_FutureCompleted_When_BuiltinPrintWithNewLineAsync)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        auto result = cli.builtin_print_with_new_line_async("NewLine");
        result.get();
        SUCCEED();
    }

    TEST_F(CliIOTest, Should_Expect_ScanToReturnString_When_BuiltinScan)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        std::istringstream input("hello");
        std::cin.rdbuf(input.rdbuf());
        std::string result = cli.builtin_scan();
        EXPECT_EQ(result, "hello");
    }

    TEST_F(CliIOTest, Should_Expect_FutureResult_When_BuiltinScanAsync)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        std::istringstream input("async");
        std::cin.rdbuf(input.rdbuf());
        auto future = cli.builtin_scan_async();
        EXPECT_EQ(future.get(), "async");
    }

    TEST_F(CliIOTest, Should_Expect_FutureResult_When_ScanAsyncWithFallback)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        std::istringstream input("fastio");
        std::cin.rdbuf(input.rdbuf());
        auto future = cli.scan_async();
        EXPECT_EQ(future.get(), "fastio");
    }

    TEST_F(CliIOTest, Should_Expect_ParallelPrints_When_Multithreaded)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        std::vector<std::future<void>> futures;

        for (int i = 0; i < 16; ++i)
        {
            futures.push_back(cli.print_async("x"));
        }

        for (auto& f : futures) f.get();
        SUCCEED();
    }

    TEST_F(CliIOTest, Should_Expect_NoThrow_When_StressPrintUnder2Seconds)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        auto start = std::chrono::steady_clock::now();
        int ops = 0;

        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(2))
        {
            cli.print("z");
            ++ops;
        }

        EXPECT_GT(ops, 1000);
    }

    TEST_F(CliIOTest, Should_Expect_Under1Millisecond_When_SimplePrint)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        auto start = std::chrono::steady_clock::now();
        cli.print("z");
        auto duration = std::chrono::steady_clock::now() - start;
        EXPECT_LT(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count(), 1);
    }

    TEST_F(CliIOTest, Should_Expect_EmptyString_When_ExceptionThrown)
    {
        class FaultyCliIO : public QLogicaeCore::CliIO
        {
        public:
            std::string scan_override() const
            {
                throw std::runtime_error("fail");
            }
        };

        SUCCEED();
    }

    class ScanEnabledTest : public ::testing::TestWithParam<bool> {};

    TEST_P(ScanEnabledTest, Should_Expect_CorrectScanFlag_When_Parameterized)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        cli.set_scan_enabled(GetParam());
        EXPECT_EQ(cli.is_scan_enabled(), GetParam());
    }

    INSTANTIATE_TEST_CASE_P(ScanStates, ScanEnabledTest, ::testing::Values(true, false));

    class PrintEnabledTest : public ::testing::TestWithParam<bool> {};

    TEST_P(PrintEnabledTest, Should_Expect_CorrectPrintFlag_When_Parameterized)
    {
        auto& cli = QLogicaeCore::CliIO::instance();
        cli.set_print_enabled(GetParam());
        EXPECT_EQ(cli.is_print_enabled(), GetParam());
    }

    INSTANTIATE_TEST_CASE_P(PrintStates, PrintEnabledTest, ::testing::Values(true, false));
}
