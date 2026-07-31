#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		BinaryFileIoManager \
	)

#include "../includes/binary_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_ReturnEmptyVector_When_FileDoesNotExist
	)
	{
		manager.configurations.is_feature_edge_case_handling_enabled = true;

		auto
			result =
				manager
					.read_raw_bytes(
						temporary_file_path
							.string()
					);

		EXPECT_TRUE(
			result
				.empty()
		);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_WriteAndReadBytes_When_ValidFilePath
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(256)
				);

		bool
			write_result =
				manager
					.write_raw_bytes(
						temporary_file_path
							.string(),
						bytes
					);

		EXPECT_TRUE(
			write_result
		);

		auto
			read_result =
				manager
					.read_raw_bytes(
						temporary_file_path
							.string()
					);

		EXPECT_EQ(
			read_result
				.size(),
			bytes
				.size()
		);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_AppendBytes_When_FileExists
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(64)
				);

		manager
			.write_raw_bytes(
				temporary_file_path
					.string(),
				bytes
			);

		bool
			append_result =
				manager
					.append_raw_bytes(
						temporary_file_path
							.string(),
						bytes
					);

		EXPECT_TRUE(
			append_result
		);

		auto
			read_result =
				manager
					.read_raw_bytes(
						temporary_file_path
							.string()
					);

		EXPECT_EQ(
			read_result
				.size(),
			static_cast<size_t>(128)
		);
	}

	class BinaryFileIoManagerParameterizedTest :
		public BinaryFileIoManagerTest,
		public ::testing::WithParamInterface<size_t>
	{
	};

	TEST_P
	(
		BinaryFileIoManagerParameterizedTest,
		Should_WriteCorrectSize_When_VariousByteCounts
	)
	{
		size_t
			size =
				GetParam();

		auto
			bytes =
				create_bytes(
					size
				);

		bool
			write_result =
				manager
					.write_raw_bytes(
						temporary_file_path
							.string(),
						bytes
					);

		EXPECT_TRUE(
			write_result
		);

		auto
			read_result =
				manager
					.read_raw_bytes(
						temporary_file_path
							.string()
					);

		EXPECT_EQ(
			read_result
				.size(),
			size
		);
	}

	INSTANTIATE_TEST_CASE_P
	(
		BinaryFileIoManagerTest,
		BinaryFileIoManagerParameterizedTest,
		::testing::Values(
			static_cast<size_t>(1),
			static_cast<size_t>(32),
			static_cast<size_t>(256),
			static_cast<size_t>(1024),
			static_cast<size_t>(4096)
		)
	);

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_HandleAsyncRead_When_UsingFuture
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(512)
				);

		manager
			.write_raw_bytes(
				temporary_file_path
					.string(),
				bytes
			);

		auto
			future =
				std::async(
					std::launch::async,
					[this]()
					{
						return
							manager
								.read_raw_bytes(
									temporary_file_path
										.string()
								);
					}
				);

		auto
			result =
				future
					.get();

		EXPECT_EQ(
			result
				.size(),
			bytes
				.size()
		);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_BeThreadSafe_When_MultipleThreadsWrite
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(128)
				);

		std::vector<std::thread>
			threads;

		std::atomic<size_t>
			completed_count =
				static_cast<size_t>(0);

		for
		(
			size_t
				index = 0;
			index < static_cast<size_t>(8);
			++index
		)
		{
			threads.emplace_back(
				[this,
				 &bytes,
				 &completed_count]()
				{
					manager
						.append_raw_bytes(
							temporary_file_path
								.string(),
							bytes
						);

					++completed_count;
				}
			);
		}

		for
		(
			auto&
				thread :
				threads
		)
		{
			thread
				.join();
		}

		EXPECT_EQ(
			completed_count
				.load(),
			static_cast<size_t>(8)
		);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_HandleStressLoad_When_ManyIterations
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(32)
				);

		for
		(
			size_t
				iteration = 0;
			iteration <
				static_cast<size_t>(100);
			++iteration
		)
		{
			manager
				.write_raw_bytes(
					temporary_file_path
						.string(),
					bytes
				);

			auto
				result =
					manager
						.read_raw_bytes(
							temporary_file_path
								.string()
						);

			EXPECT_EQ(
				result
					.size(),
				bytes
					.size()
			);
		}
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_HandlePromiseFuture_When_AsynchronousWrite
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(128)
				);

		std::promise<bool>
			promise;

		std::future<bool>
			future =
				promise
					.get_future();

		std::thread
			worker(
				[this,
				 &bytes,
				 &promise]()
				{
					bool
						result =
							manager
								.write_raw_bytes(
									temporary_file_path
										.string(),
									bytes
								);

					promise
						.set_value(
							result
						);
				}
			);

		bool
			write_result =
				future
					.get();

		worker
			.join();

		EXPECT_TRUE(
			write_result
		);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_ReturnFalse_When_WritingEmptyBytes
	)
	{
		std::vector<std::byte>
			bytes;

		bool
			result =
				manager
					.write_raw_bytes(
						temporary_file_path
							.string(),
						bytes
					);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_ReturnEmptyString_When_ReadTextInvalidPath
	)
	{
		auto
			result =
				manager
					.read_raw_text(
						"invalid_file_path"
					);

		EXPECT_TRUE(
			result
				.empty()
		);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_HandleLargeFile_When_WriteAndRead
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(1024 * 1024)
				);

		bool
			write_result =
				manager
					.write_raw_bytes(
						temporary_file_path.string(),
						bytes
					);

		EXPECT_TRUE(write_result);

		auto
			read_result =
				manager
					.read_raw_bytes(
						temporary_file_path.string()
					);

		EXPECT_EQ(
			read_result.size(),
			bytes.size()
		);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_ReturnFalse_When_FilePathEmpty
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(16)
				);

		bool
			result =
				manager
					.write_raw_bytes(
						std::string(),
						bytes
					);

		EXPECT_FALSE(result);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_ReturnEmpty_When_DirectoryPathRead
	)
	{
		auto
			result =
				manager
					.read_raw_bytes(
						std::filesystem
							::temp_directory_path()
							.string()
					);

		EXPECT_TRUE(result.empty());
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_AppendConcurrently_When_MultipleThreads
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(64)
				);

		std::vector<std::thread>
			threads;

		for
		(
			size_t
				index = 0;
			index < static_cast<size_t>(16);
			++index
		)
		{
			threads.emplace_back(
				[this,&bytes]()
				{
					manager
						.append_raw_bytes(
							temporary_file_path.string(),
							bytes
						);
				}
			);
		}

		for
		(
			auto&
				thread :
				threads
		)
		{
			thread.join();
		}

		auto
			result =
				manager
					.read_raw_bytes(
						temporary_file_path.string()
					);

		EXPECT_GT(result.size(), static_cast<size_t>(0));
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_ReadWhileWriting_When_ConcurrentThreads
	)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = true;

		auto
			bytes =
				create_bytes(
					static_cast<size_t>(128)
				);

		std::atomic<bool>
			stop_flag =
				false;

		std::thread
			writer(
				[this,&bytes,&stop_flag]()
				{
					while(!stop_flag.load())
					{
						manager
							.write_raw_bytes(
								temporary_file_path.string(),
								bytes
							);
					}
				}
			);

		std::thread
			reader(
				[this,&stop_flag]()
				{
					for
					(
						size_t
							index = 0;
						index < static_cast<size_t>(100);
						++index
					)
					{
						manager
							.read_raw_bytes(
								temporary_file_path.string()
							);
					}

					stop_flag.store(true);
				}
			);

		writer.join();
		reader.join();

		EXPECT_TRUE(true);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_ResolvePromises_When_MultipleAsyncWrites
	)
	{
		std::vector<std::thread>
			threads;

		std::vector<std::future<bool>>
			futures;

		for
		(
			size_t
				index = 0;
			index < static_cast<size_t>(8);
			++index
		)
		{
			std::promise<bool>
				promise;

			futures.emplace_back(
				promise.get_future()
			);

			threads.emplace_back(
				[this,
				 promise = std::move(promise),
				 index]()
				mutable
				{
					auto
						bytes =
							create_bytes(
								static_cast<size_t>(
									64 + index
								)
							);

					bool
						result =
							manager
								.write_raw_bytes(
									temporary_file_path
										.string(),
									bytes
								);

					promise.set_value(result);
				}
			);
		}

		for
		(
			auto&
				thread :
				threads
		)
		{
			thread.join();
		}

		for
		(
			auto&
				future :
				futures
		)
		{
			EXPECT_TRUE(future.get());
		}
	}

	TEST_P
	(
		InvalidPathParameterizedTest,
		Should_ReturnEmpty_When_InvalidPaths
	)
	{
		auto
			result =
				manager
					.read_raw_bytes(
						GetParam()
					);

		EXPECT_TRUE(result.empty());
	}

	INSTANTIATE_TEST_CASE_P
	(
		BinaryFileIoManagerTest,
		InvalidPathParameterizedTest,
		::testing::Values(
			std::string(),
			std::string(":::"),
			std::string("/invalid/path/file.bin"),
			std::string("C:/invalid/<>file")
		)
	);

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_HandleAsyncLoop_When_ManyFutures
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(64)
				);

		std::vector<std::future<bool>>
			futures;

		for
		(
			size_t
				index = 0;
			index < static_cast<size_t>(100);
			++index
		)
		{
			futures.emplace_back(
				std::async(
					std::launch::async,
					[this,&bytes]()
					{
						return
							manager
								.write_raw_bytes(
									temporary_file_path
										.string(),
									bytes
								);
					}
				)
			);
		}

		for
		(
			auto&
				future :
				futures
		)
		{
			EXPECT_TRUE(future.get());
		}
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_StressSequentialOperations_When_Hundreds
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(32)
				);

		for
		(
			size_t
				index = 0;
			index < static_cast<size_t>(100);
			++index
		)
		{
			manager
				.write_raw_bytes(
					temporary_file_path.string(),
					bytes
				);

			auto
				result =
					manager
						.read_raw_bytes(
							temporary_file_path.string()
						);

			EXPECT_EQ(
				result.size(),
				bytes.size()
			);
		}
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_SynchronizeThreads_When_ConditionVariable
	)
	{
		std::mutex
			mutex;

		std::condition_variable
			condition;

		bool
			ready =
				false;

		std::thread
			worker(
				[this,&mutex,&condition,&ready]()
				{
					std::unique_lock<std::mutex>
						lock(mutex);

					condition.wait(
						lock,
						[&ready]()
						{
							return ready;
						}
					);

					manager
						.read_raw_bytes(
							temporary_file_path.string()
						);
				}
			);

		{
			std::lock_guard<std::mutex>
				lock(mutex);

			ready = true;
		}

		condition.notify_one();

		worker.join();

		EXPECT_TRUE(true);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_HandleTextApis_When_WriteReadAppend
	)
	{
		std::string
			text =
				"example_text";

		bool
			write_result =
				manager
					.write_raw_text(
						temporary_file_path.string(),
						text
					);

		EXPECT_TRUE(write_result);

		auto
			read_text =
				manager
					.read_raw_text(
						temporary_file_path.string()
					);

		EXPECT_EQ(
			read_text,
			text
		);

		bool
			append_result =
				manager
					.append_raw_text(
						temporary_file_path.string(),
						text
					);

		EXPECT_TRUE(append_result);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_ReadEmptyVector_When_FileExistsButEmpty
	)
	{
		std::ofstream
			file(
				temporary_file_path.string(),
				std::ios::binary
			);

		file.close();

		auto
			result =
				manager
					.read_raw_bytes(
						temporary_file_path.string()
					);

		EXPECT_TRUE(result.empty());
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_CreateFile_When_AppendingToNonExistingFile
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(64)
				);

		bool
			result =
				manager
					.append_raw_bytes(
						temporary_file_path.string(),
						bytes
					);

		EXPECT_TRUE(result);

		auto
			read =
				manager
					.read_raw_bytes(
						temporary_file_path.string()
					);

		EXPECT_EQ(read, bytes);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_OverwriteFile_When_WritingTwice
	)
	{
		auto
			bytes_a =
				create_bytes(
					static_cast<size_t>(32)
				);

		auto
			bytes_b =
				create_bytes(
					static_cast<size_t>(64)
				);

		manager
			.write_raw_bytes(
				temporary_file_path.string(),
				bytes_a
			);

		manager
			.write_raw_bytes(
				temporary_file_path.string(),
				bytes_b
			);

		auto
			read =
				manager
					.read_raw_bytes(
						temporary_file_path.string()
					);

		EXPECT_EQ(read, bytes_b);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_PreserveContent_When_AppendingBytes
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(32)
				);

		manager
			.write_raw_bytes(
				temporary_file_path.string(),
				bytes
			);

		manager
			.append_raw_bytes(
				temporary_file_path.string(),
				bytes
			);

		auto
			result =
				manager
					.read_raw_bytes(
						temporary_file_path.string()
					);

		std::vector<std::byte>
			expected;

		expected.insert(
			expected.end(),
			bytes.begin(),
			bytes.end()
		);

		expected.insert(
			expected.end(),
			bytes.begin(),
			bytes.end()
		);

		EXPECT_EQ(result, expected);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_AppendTextCorrectly
	)
	{
		std::string
			text =
				"example";

		manager
			.write_raw_text(
				temporary_file_path.string(),
				text
			);

		manager
			.append_raw_text(
				temporary_file_path.string(),
				text
			);

		auto
			read =
				manager
					.read_raw_text(
						temporary_file_path.string()
					);

		EXPECT_EQ(read, text + text);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_ReadExactBytes_When_Written
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(128)
				);

		manager
			.write_raw_bytes(
				temporary_file_path.string(),
				bytes
			);

		auto
			read =
				manager
					.read_raw_bytes(
						temporary_file_path.string()
					);

		EXPECT_EQ(read, bytes);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_HandleEdgeCaseDisabled_When_FileMissing
	)
	{
		manager.configurations.is_feature_edge_case_handling_enabled = true;

		auto
			result =
				manager
					.read_raw_bytes(
						temporary_file_path.string()
					);

		EXPECT_TRUE(result.empty());
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_WriteAfterFileDeletion
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(64)
				);

		manager
			.write_raw_bytes(
				temporary_file_path.string(),
				bytes
			);

		std::filesystem::remove(
			temporary_file_path
		);

		bool
			result =
				manager
					.write_raw_bytes(
						temporary_file_path.string(),
						bytes
					);

		EXPECT_TRUE(result);

		auto
			read =
				manager
					.read_raw_bytes(
						temporary_file_path.string()
					);

		EXPECT_EQ(read, bytes);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_HandleZeroByteWriteParameter
	)
	{
		auto
			bytes =
				create_bytes(
					static_cast<size_t>(0)
				);

		bool
			result =
				manager
					.write_raw_bytes(
						temporary_file_path.string(),
						bytes
					);

		EXPECT_FALSE(result);
	}

	TEST_F
	(
		BinaryFileIoManagerTest,
		Should_AppendMultipleTimesPreservingOrder
	)
	{
		auto
			bytes_a =
				create_bytes(
					static_cast<size_t>(16)
				);

		auto
			bytes_b =
				create_bytes(
					static_cast<size_t>(24)
				);

		manager
			.write_raw_bytes(
				temporary_file_path.string(),
				bytes_a
			);

		manager
			.append_raw_bytes(
				temporary_file_path.string(),
				bytes_b
			);

		auto
			result =
				manager
					.read_raw_bytes(
						temporary_file_path.string()
					);

		std::vector<std::byte>
			expected;

		expected.insert(
			expected.end(),
			bytes_a.begin(),
			bytes_a.end()
		);

		expected.insert(
			expected.end(),
			bytes_b.begin(),
			bytes_b.end()
		);

		EXPECT_EQ(result, expected);
	}

	TEST_F(
		BinaryFileIoManagerTest,
		Should_ReturnEmpty_When_RuntimeExecutionDisabled
	)
	{
		manager
			.configurations
			.is_feature_runtime_execution_handling_enabled = false;

		auto
			bytes =
				manager
				.read_raw_bytes(
					temporary_file_path.string()
				);

		EXPECT_TRUE(
			bytes.empty()
		);
	}

	TEST_F(
		BinaryFileIoManagerTest,
		Should_ReturnFalse_When_WriteRuntimeDisabled
	)
	{
		manager
			.configurations
			.is_feature_runtime_execution_handling_enabled = false;

		auto
			bytes =
				create_bytes(
					64
				);

		auto
			result =
				manager
				.write_raw_bytes(
					temporary_file_path.string(),
					bytes
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		BinaryFileIoManagerTest,
		Should_ReturnFalse_When_AppendRuntimeDisabled
	)
	{
		manager
			.configurations
			.is_feature_runtime_execution_handling_enabled = false;

		auto
			bytes =
				create_bytes(
					64
				);

		auto
			result =
				manager
				.append_raw_bytes(
					temporary_file_path.string(),
					bytes
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		BinaryFileIoManagerTest,
		Should_HandleAppend_When_FileExistsButEmpty
	)
	{
		std::ofstream(
			temporary_file_path,
			std::ios::binary
		).close();

		auto
			bytes =
				create_bytes(
					128
				);

		EXPECT_TRUE(
			manager
				.append_raw_bytes(
					temporary_file_path.string(),
					bytes
				)
		);

		auto
			result =
				manager
				.read_raw_bytes(
					temporary_file_path.string()
				);

		EXPECT_EQ(
			result,
			bytes
		);
	}

	TEST_F(
		BinaryFileIoManagerTest,
		Should_HandleEmptyText_When_WriteRawText
	)
	{
		EXPECT_FALSE(
			manager
				.write_raw_text(
					temporary_file_path.string(),
					""
				)
		);

		auto
			text =
				manager
				.read_raw_text(
					temporary_file_path.string()
				);

		EXPECT_TRUE(
			text.empty()
		);
	}

	TEST_F(
		BinaryFileIoManagerTest,
		Should_HandleEmptyText_When_AppendRawText
	)
	{
		EXPECT_TRUE(
			manager
				.write_raw_text(
					temporary_file_path.string(),
					"abc"
				)
		);

		EXPECT_FALSE(
			manager
				.append_raw_text(
					temporary_file_path.string(),
					""
				)
		);

		auto
			text =
				manager
				.read_raw_text(
					temporary_file_path.string()
				);

		EXPECT_EQ(
			text,
			"abc"
		);
	}

	TEST_F(
		BinaryFileIoManagerTest,
		Should_HandleHighContention_When_ThirtyTwoThreads
	)
	{
		const int
			thread_count =
				32;

		auto
			bytes =
				create_bytes(
					64
				);

		std::vector<
			std::thread
		>
			threads;

		for
		(
			int
				i = 0;
			i < thread_count;
			++i
		)
		{
			threads.emplace_back(
				[&]()
				{
					manager
						.append_raw_bytes(
							temporary_file_path.string(),
							bytes
						);
				}
			);
		}

		for
		(
			auto&
				thread
			:
				threads
		)
		{
			thread.join();
		}

		auto
			result =
				manager
				.read_raw_bytes(
					temporary_file_path.string()
				);

		EXPECT_EQ(
			result.size(),
			bytes.size()
			* thread_count
		);
	}
}

#endif
