#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileLogManager \
	)

#include "../includes/file_log_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{    
    INSTANTIATE_TEST_CASE_P(
        FileKeys,
        FileLogManagerParameterizedTest,
        ::testing::Values(
			FileKeyParam{ "", false },
			FileKeyParam{ "valid_key", true }
        )
    );

    TEST_P(FileLogManagerParameterizedTest, Should_SetAndGetFileOutputPath_When_ValidKey)
    {
        const FileKeyParam param = GetParam();
        auto callback = [](){ return std::string("output.log"); };
        bool set_result = manager.set_file_output_path(param.key, callback);
        EXPECT_EQ(set_result, param.expect_success);

        if(param.expect_success)
        {
            EXPECT_TRUE(manager.is_file_output_path_found(param.key));
            EXPECT_EQ(manager.get_file_output_path(param.key), "output.log");
        }
    }

    TEST_F(FileLogManagerTest, Should_RemoveFileOutputPath_When_KeyExists)
    {
        const std::string key = "remove_test";
        auto callback = [](){ return std::string("removed.log"); };
        manager.set_file_output_path(key, callback);
        EXPECT_TRUE(manager.is_file_output_path_found(key));

        bool removed = manager.remove_file_output_path(key);
        EXPECT_TRUE(removed);
        EXPECT_FALSE(manager.is_file_output_path_found(key));
    }

    TEST_F(FileLogManagerTest, Should_NotRemoveFileOutputPath_When_KeyDoesNotExist)
    {
        bool removed = manager.remove_file_output_path("nonexistent");
        EXPECT_FALSE(removed);
    }

    TEST_F(FileLogManagerTest, Should_Destruct_ClearAllPaths)
    {
        manager.set_file_output_path("key1", [](){ return "file1.log"; });
        manager.set_file_output_path("key2", [](){ return "file2.log"; });

        EXPECT_TRUE(manager.is_file_output_path_found("key1"));
        EXPECT_TRUE(manager.is_file_output_path_found("key2"));

        EXPECT_TRUE(manager.destruct());

        EXPECT_FALSE(manager.is_file_output_path_found("key1"));
        EXPECT_FALSE(manager.is_file_output_path_found("key2"));
    }

    TEST_F(FileLogManagerTest, Should_Reset_ClearAllPaths)
    {
        manager.set_file_output_path("key1", [](){ return "file1.log"; });
        manager.set_file_output_path("key2", [](){ return "file2.log"; });

        EXPECT_TRUE(manager.is_file_output_path_found("key1"));
        EXPECT_TRUE(manager.is_file_output_path_found("key2"));

        EXPECT_TRUE(manager.reset());

        EXPECT_FALSE(manager.is_file_output_path_found("key1"));
        EXPECT_FALSE(manager.is_file_output_path_found("key2"));
    }

    TEST_F(FileLogManagerTest, Should_LogRawText_When_SinglePath)
    {
        const std::string key = "log_raw_test";
        std::string file_path = "raw_test.log";
        manager.set_file_output_path(key, [&file_path](){ return file_path; });

        EXPECT_TRUE(manager.log_raw_text("HelloWorld"));
    }

    TEST_F(FileLogManagerTest, Should_LogFormattedText_When_SinglePath)
    {
        const std::string key = "log_formatted_test";
        std::string file_path = "formatted_test.log";
        manager.set_file_output_path(key, [&file_path](){ return file_path; });

        EXPECT_TRUE(manager.log_formatted_text("FormattedText", LogLevel::INFO));
        EXPECT_TRUE(manager.log_formatted_text("FormattedTextDefaultLevel"));
        EXPECT_TRUE(manager.log_formatted_text());
    }

    TEST_F(FileLogManagerTest, Should_HandleExceptionInCallback_Gracefully)
    {
        const std::string key = "exception_callback";
        manager.set_file_output_path(key, [](){ throw std::runtime_error("CallbackError"); return std::string(); });

        EXPECT_THROW(manager.log_raw_text("Test"), std::runtime_error);
        EXPECT_THROW(manager.log_formatted_text("Test", LogLevel::ERROR_TYPE), std::runtime_error);
    }

    TEST_F(FileLogManagerTest, Should_HandleEmptyKey_EdgeCases)
    {
        EXPECT_FALSE(manager.set_file_output_path("", [](){ return "fail.log"; }));
        EXPECT_FALSE(manager.remove_file_output_path(""));
        EXPECT_FALSE(manager.is_file_output_path_found(""));
    }

    TEST_F(FileLogManagerTest, Should_AsyncLogRawText_WithMultipleThreads)
    {
        const std::string key1 = "thread1";
        const std::string key2 = "thread2";
        manager.set_file_output_path(key1, [](){ return "thread1.log"; });
        manager.set_file_output_path(key2, [](){ return "thread2.log"; });

        auto future1 = std::async(std::launch::async, [&](){ return manager.log_raw_text("Threaded1"); });
        auto future2 = std::async(std::launch::async, [&](){ return manager.log_raw_text("Threaded2"); });

        EXPECT_TRUE(future1.get());
        EXPECT_TRUE(future2.get());
    }

    TEST_F(FileLogManagerTest, Should_StressTest_LogMultipleEntries)
    {
        const std::string key = "stress_test";
        manager.set_file_output_path(key, [](){ return "stress.log"; });

        auto start_time = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < 100; ++i)
        {
            std::string message = "Message" + std::to_string(i);
            EXPECT_TRUE(manager.log_raw_text(message));
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        EXPECT_LT(duration_ms, 2000);
    }

    TEST_F(FileLogManagerTest, Should_MultithreadedLogging_NoRaceConditions)
    {
        const std::string key1 = "multi1";
        const std::string key2 = "multi2";
        manager.set_file_output_path(key1, [](){ return "multi1.log"; });
        manager.set_file_output_path(key2, [](){ return "multi2.log"; });

        std::thread t1([&](){ for(int i = 0; i < 500; ++i) manager.log_raw_text("T1"); });
        std::thread t2([&](){ for(int i = 0; i < 500; ++i) manager.log_raw_text("T2"); });
        std::thread t3([&](){ for(int i = 0; i < 500; ++i) manager.log_formatted_text("T3"); });

        t1.join();
        t2.join();
        t3.join();

        EXPECT_TRUE(true);
    }

	TEST_F(FileLogManagerTest, Should_HandleEmptyAndVeryLargeLogMessages)
	{
		manager.set_file_output_path("empty_test", []() { return "empty.log"; });
		EXPECT_TRUE(manager.log_raw_text(""));
		std::string large_message(50000, 'X');
		EXPECT_TRUE(manager.log_raw_text(large_message));
	}

	TEST_F(FileLogManagerTest, Should_HandleConcurrentResetDuringLogging)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = true;

		manager.set_file_output_path("concurrent", []() { return "concurrent.log"; });

		std::thread t1([&]() { for (int i = 0; i < 100; ++i) manager.log_raw_text("T1"); });
		std::thread t2([&]() { for (int i = 0; i < 100; ++i) manager.log_formatted_text("T2"); });
		std::thread t3([&]() { manager.reset(); });

		t1.join();
		t2.join();
		t3.join();

		EXPECT_TRUE(true);
	}

	TEST_F(FileLogManagerTest, Should_HandleCallbackReturningEmptyString)
	{
		manager.set_file_output_path("empty_callback", []() { return std::string(); });
		EXPECT_TRUE(manager.log_raw_text("TestEmpty"));
		EXPECT_TRUE(manager.log_formatted_text("TestEmptyFormatted", LogLevel::INFO));
	}

	TEST_F(FileLogManagerTest, Should_LogFormattedText_WithAllLogLevels)
	{
		manager.set_file_output_path("all_levels", []() { return "all_levels.log"; });

		EXPECT_TRUE(manager.log_formatted_text("DebugMessage", LogLevel::DEBUG));
		EXPECT_TRUE(manager.log_formatted_text("InfoMessage", LogLevel::INFO));
		EXPECT_TRUE(manager.log_formatted_text("WarningMessage", LogLevel::WARNING));
		EXPECT_TRUE(manager.log_formatted_text("ErrorMessage", LogLevel::ERROR_TYPE));
	}

	TEST_F(FileLogManagerTest, Should_SimultaneousMultiplePathsAsyncLogging)
	{
		const std::string key1 = "async1";
		const std::string key2 = "async2";
		const std::string key3 = "async3";

		manager.set_file_output_path(key1, []() { return "async1.log"; });
		manager.set_file_output_path(key2, []() { return "async2.log"; });
		manager.set_file_output_path(key3, []() { return "async3.log"; });

		auto future1 = std::async(std::launch::async, [&]() {
			for (int i = 0; i < 100; ++i) manager.log_raw_text("Msg1"); return true;
			});
		auto future2 = std::async(std::launch::async, [&]() {
			for (int i = 0; i < 100; ++i) manager.log_formatted_text("Msg2"); return true;
			});
		auto future3 = std::async(std::launch::async, [&]() {
			for (int i = 0; i < 100; ++i) manager.log_raw_text("Msg3"); return true;
			});

		EXPECT_TRUE(future1.get());
		EXPECT_TRUE(future2.get());
		EXPECT_TRUE(future3.get());
	}

	TEST_F(FileLogManagerTest, Should_HandleConcurrentDestructDuringLogging)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = true;

		manager.set_file_output_path("concurrent_destruct", []() { return "concurrent_destruct.log"; });

		std::thread t1([&]() { for (int i = 0; i < 100; ++i) manager.log_raw_text("T1"); });
		std::thread t2([&]() { for (int i = 0; i < 100; ++i) manager.log_formatted_text("T2"); });
		std::thread t3([&]() { manager.destruct(); });

		t1.join();
		t2.join();
		t3.join();

		EXPECT_TRUE(true);
	}

	TEST_F(FileLogManagerTest, Should_StressTest_MultiPathAsyncLargeMessages)
	{
		const std::string key1 = "stress_async1";
		const std::string key2 = "stress_async2";
		manager.set_file_output_path(key1, []() { return "stress_async1.log"; });
		manager.set_file_output_path(key2, []() { return "stress_async2.log"; });

		std::string large_message(50000, 'L');

		auto future1 = std::async(std::launch::async, [&]() {
			for (int i = 0; i < 50; ++i) manager.log_raw_text(large_message);
			return true;
			});
		auto future2 = std::async(std::launch::async, [&]() {
			for (int i = 0; i < 50; ++i) manager.log_formatted_text(large_message, LogLevel::INFO);
			return true;
			});

		EXPECT_TRUE(future1.get());
		EXPECT_TRUE(future2.get());
	}

	INSTANTIATE_TEST_CASE_P(
		FileEdgeKeys,
		FileLogManagerEdgeKeyParameterizedTest,
		::testing::Values(
			FileKeyEdgeParam{ std::string(1024, 'A'), true },
			FileKeyEdgeParam{ reinterpret_cast<const char*>(u8"特殊字符_key"), true },
			FileKeyEdgeParam{ "!@#$%^&*()_+-={}[]|;:'<>,.?/~`", true }
		)
	);

	TEST_P(FileLogManagerEdgeKeyParameterizedTest, Should_HandleVeryLongAndSpecialCharacterKeys)
	{
		const FileKeyEdgeParam param = GetParam();
		auto callback = []() { return std::string("edge.log"); };
		bool set_result = manager.set_file_output_path(param.key, callback);
		EXPECT_EQ(set_result, param.expect_success);

		if (param.expect_success)
		{
			EXPECT_TRUE(manager.is_file_output_path_found(param.key));
			EXPECT_EQ(manager.get_file_output_path(param.key), "edge.log");
			EXPECT_TRUE(manager.remove_file_output_path(param.key));
		}
	}
}

#endif
