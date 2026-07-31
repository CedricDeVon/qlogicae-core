#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CsvFileIoManager \
	)

#include "../includes/csv_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_AppendingRow_ValidValues
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"7",
			"8",
			"9"
		};

		bool result =
			manager.append_row(file_path_.string(), values);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnFalse_When_AppendingRow_InvalidFile
	)
	{
		CsvFileIoManager manager;

		std::filesystem::path invalid_path =
			std::filesystem::path("invalid_directory/file.csv");

		std::vector<std::string> values =
		{
			"1",
			"2"
		};

		bool result =
			manager.append_row(invalid_path.string(), values);

		EXPECT_FALSE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_AppendColumn_When_ValidColumnProvided
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"7",
			"8"
		};

		bool result =
			manager.append_column(
				file_path_.string(),
				"D",
				values
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnFalse_When_ColumnNameEmpty
	)
	{
		CsvFileIoManager manager;
		manager.configurations.is_feature_edge_case_handling_enabled = true;

		std::vector<std::string> values =
		{
			"1"
		};

		bool result =
			manager.append_column(
				file_path_.string(),
				"",
				values
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleAsyncAppendRow_When_FutureUsed
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"10",
			"11",
			"12"
		};

		std::future<bool> future =
			std::async(
				std::launch::async,
				[&]()
				{
					return manager.append_row(
						file_path_.string(),
						values
					);
				}
			);

		bool result = future.get();

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandlePromiseFuture_When_AsyncAppendColumn
	)
	{
		CsvFileIoManager manager;

		std::promise<bool> promise;
		std::future<bool> future =
			promise.get_future();

		std::thread worker(
			[&]()
			{
				std::vector<std::string> values =
				{
					"100",
					"200"
				};

				bool result =
					manager.append_column(
						file_path_.string(),
						"E",
						values
					);

				promise.set_value(result);
			}
		);

		bool result = future.get();

		worker.join();

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleMultithreadedAppend_When_ManyThreads
	)
	{
		CsvFileIoManager manager;

		std::atomic<int> success_count{0};

		std::vector<std::thread> threads;

		for (std::size_t index = 0;
			 index < 16;
			 ++index)
		{
			threads.emplace_back(
				[&]()
				{
					std::vector<std::string> values =
					{
						"1",
						"2",
						"3"
					};

					if (
						manager.append_row(
							file_path_.string(),
							values
						)
					)
					{
						success_count.fetch_add(
							1,
							std::memory_order_relaxed
						);
					}
				}
			);
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		EXPECT_EQ(success_count.load(), 16);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleConditionVariable_When_ConcurrentWrites
	)
	{
		CsvFileIoManager manager;

		std::mutex mutex;
		std::condition_variable condition_variable;

		bool ready = false;

		std::thread writer(
			[&]()
			{
				std::unique_lock lock(mutex);
				condition_variable.wait(
					lock,
					[&]()
					{
						return ready;
					}
				);

				std::vector<std::string> values =
				{
					"21",
					"22",
					"23"
				};

				manager.append_row(
					file_path_.string(),
					values
				);
			}
		);

		{
			std::lock_guard lock(mutex);
			ready = true;
		}

		condition_variable.notify_one();

		writer.join();

		EXPECT_TRUE(true);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleExceptionSafety_When_InvalidPathUsed
	)
	{
		CsvFileIoManager manager;

		std::filesystem::path invalid_path =
			std::filesystem::path("/root/invalid.csv");

		std::vector<std::string> values =
		{
			"1"
		};

		bool result =
			manager.append_row(
				invalid_path.string(),
				values
			);

		EXPECT_FALSE(result);
	}

	TEST_P(
		CsvFileIoManagerParameterizedValuesTest,
		Should_ReturnTrue_When_AppendingParameterizedValues
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
			GetParam();

		bool result =
			manager.append_row(
				file_path_.string(),
				values
			);

		EXPECT_TRUE(result);
	}

	INSTANTIATE_TEST_CASE_P(
		CsvFileIoManagerValues,
		CsvFileIoManagerParameterizedValuesTest,
		::testing::Values(
			std::vector<std::string>{"1","2","3"},
			std::vector<std::string>{"A","B","C"},
			std::vector<std::string>{"","",""},
			std::vector<std::string>{"123456789"}
		)
	);

	TEST_F(
		CsvFileIoManagerTest,
		Should_FillMissingRows_When_ColumnShorterThanRowCount
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"7"
		};

		bool result =
			manager.append_column(
				file_path_.string(),
				"D",
				values
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleColumnValuesGreaterThanRows_When_AppendingColumn
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"7",
			"8",
			"9",
			"10",
			"11"
		};

		bool result =
			manager.append_column(
				file_path_.string(),
				"E",
				values
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleSingleValueRow_When_AppendingRow
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"100"
		};

		bool result =
			manager.append_row(
				file_path_.string(),
				values
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleRowValuesGreaterThanColumns_When_AppendingRow
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"1",
			"2",
			"3",
			"4",
			"5",
			"6"
		};

		bool result =
			manager.append_row(
				file_path_.string(),
				values
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleHeaderOnlyCsv_When_AppendingRow
	)
	{
		std::filesystem::path header_only_path =
			std::filesystem::temp_directory_path()
			/
			std::filesystem::path("header_only_test.csv");

		std::ofstream output_stream(header_only_path.string());
		output_stream << "A,B,C\n";
		output_stream.close();

		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"1",
			"2",
			"3"
		};

		bool result =
			manager.append_row(
				header_only_path.string(),
				values
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleEmptyCsv_When_AppendingRow
	)
	{
		std::filesystem::path empty_path =
			std::filesystem::temp_directory_path()
			/
			std::filesystem::path("empty_csv_test.csv");

		std::ofstream output_stream(empty_path.string());
		output_stream.close();

		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"1",
			"2",
			"3"
		};

		bool result =
			manager.append_row(
				empty_path.string(),
				values
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleDirectoryPath_When_AppendingRow
	)
	{
		CsvFileIoManager manager;

		std::filesystem::path directory_path =
			std::filesystem::temp_directory_path();

		std::vector<std::string> values =
		{
			"1"
		};

		bool result =
			manager.append_row(
				directory_path.string(),
				values
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_CompleteLargeStressTest_When_ThousandIterations
	)
	{
		CsvFileIoManager manager;

		for
		(
			std::size_t iteration_index = 0;
			iteration_index < static_cast<std::size_t>(100);
			++iteration_index
		)
		{
			std::vector<std::string> values =
			{
				std::to_string(iteration_index),
				std::to_string(iteration_index + 1)
			};

			bool result =
				manager.append_row(
					file_path_.string(),
					values
				);

			EXPECT_TRUE(result);
		}
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_HandleAsyncConcurrentWrites_When_MultipleFutures
	)
	{
		CsvFileIoManager manager;

		std::vector<std::future<bool>> futures;

		for
		(
			std::size_t index = 0;
			index < static_cast<std::size_t>(16);
			++index
		)
		{
			futures.emplace_back(
				std::async(
					std::launch::async,
					[&]()
					{
						std::vector<std::string> values =
						{
							"1",
							"2",
							"3"
						};

						return
							manager.append_row(
								file_path_.string(),
								values
							);
					}
				)
			);
		}

		for (auto& future : futures)
		{
			bool result = future.get();
			EXPECT_TRUE(result);
		}
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTable_When_ReadCalled
	)
	{
		CsvFileIoManager manager;

		auto table =
			manager.read(
				file_path_.string()
			);

		EXPECT_EQ(
			table.size(),
			static_cast<std::size_t>(3)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_IsValidCalled
	)
	{
		CsvFileIoManager manager;

		bool result =
			manager.is_valid(
				file_path_.string()
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_ColumnNameFound
	)
	{
		CsvFileIoManager manager;

		bool result =
			manager.is_column_name_found(
				file_path_.string(),
				"A"
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnFalse_When_ColumnNameNotFound
	)
	{
		CsvFileIoManager manager;

		bool result =
			manager.is_column_name_found(
				file_path_.string(),
				"Z"
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_RowIndexFound
	)
	{
		CsvFileIoManager manager;

		bool result =
			manager.is_row_index_found(
				file_path_.string(),
				static_cast<std::size_t>(0)
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnCellValue_When_GetCellCalled
	)
	{
		CsvFileIoManager manager;

		std::string value =
			manager.get_cell(
				file_path_.string(),
				"A",
				static_cast<std::size_t>(0)
			);

		EXPECT_EQ(value, "1");
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnColumn_When_GetColumnCalled
	)
	{
		CsvFileIoManager manager;

		auto column =
			manager.get_column(
				file_path_.string(),
				"A"
			);

		EXPECT_EQ(
			column.size(),
			static_cast<std::size_t>(2)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnRow_When_GetRowCalled
	)
	{
		CsvFileIoManager manager;

		auto row =
			manager.get_row(
				file_path_.string(),
				static_cast<std::size_t>(0)
			);

		EXPECT_EQ(
			row.size(),
			static_cast<std::size_t>(3)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnColumnNames_When_GetColumnNamesCalled
	)
	{
		CsvFileIoManager manager;

		auto names =
			manager.get_column_names(
				file_path_.string()
			);

		EXPECT_EQ(
			names.size(),
			static_cast<std::size_t>(3)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnRowSize_When_GetRowSizeCalled
	)
	{
		CsvFileIoManager manager;

		auto size =
			manager.get_row_size(
				file_path_.string()
			);

		EXPECT_EQ(
			size,
			static_cast<std::size_t>(2)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnColumnSize_When_GetColumnSizeCalled
	)
	{
		CsvFileIoManager manager;

		auto size =
			manager.get_column_size(
				file_path_.string()
			);

		EXPECT_EQ(
			size,
			static_cast<std::size_t>(3)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_SetCellCalled
	)
	{
		CsvFileIoManager manager;

		bool result =
			manager.set_cell(
				file_path_.string(),
				"A",
				static_cast<std::size_t>(0),
				"100"
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_SetRowCalled
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"7",
			"8",
			"9"
		};

		bool result =
			manager.set_row(
				file_path_.string(),
				static_cast<std::size_t>(0),
				values
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_SetColumnCalled
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"10",
			"11"
		};

		bool result =
			manager.set_column(
				file_path_.string(),
				"A",
				values
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_InsertRowCalled
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"5",
			"6",
			"7"
		};

		bool result =
			manager.insert_row(
				file_path_.string(),
				static_cast<std::size_t>(1),
				values
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_InsertColumnCalled
	)
	{
		CsvFileIoManager manager;

		std::vector<std::string> values =
		{
			"10",
			"20"
		};

		bool result =
			manager.insert_column(
				file_path_.string(),
				"D",
				values
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_RemoveRowCalled
	)
	{
		CsvFileIoManager manager;

		bool result =
			manager.remove_row(
				file_path_.string(),
				static_cast<std::size_t>(0)
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_RemoveColumnCalled
	)
	{
		CsvFileIoManager manager;

		bool result =
			manager.remove_column(
				file_path_.string(),
				"A"
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnEmptyCellCount_When_GetEmptyCellCountCalled
	)
	{
		CsvFileIoManager manager;

		auto count =
			manager.get_empty_cell_count(
				file_path_.string()
			);

		EXPECT_EQ(
			count,
			static_cast<std::size_t>(0)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnNonEmptyCellCount_When_GetNonEmptyCellCountCalled
	)
	{
		CsvFileIoManager manager;

		auto count =
			manager.get_non_empty_cell_count(
				file_path_.string()
			);

		EXPECT_GT(
			count,
			static_cast<std::size_t>(0)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		Should_ReturnTrue_When_CellCoordinateValid
	)
	{
		CsvFileIoManager manager;

		bool result =
			manager.is_cell_coordinate_valid(
				file_path_.string(),
				"A",
				static_cast<std::size_t>(0)
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		CsvFileIoManagerTest,
		WriteVectorSuccess
	)
	{
		CsvFileIoManager manager;
		std::vector<std::string> values{"7","8","9"};

		EXPECT_TRUE(
			manager.write(
				file_path_.string(),
				values
			)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		WriteMapSuccess
	)
	{
		CsvFileIoManager manager;

		std::unordered_map<
			std::string,
			std::vector<std::string>
		> values{
			{"A",{"1","4"}},
			{"B",{"2","5"}},
			{"C",{"3","6"}}
		};

		EXPECT_TRUE(
			manager.write(
				file_path_.string(),
				values
			)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		GetTableSuccess
	)
	{
		CsvFileIoManager manager;

		auto table =
			manager.get_table(
				file_path_.string()
			);

		EXPECT_FALSE(
			table.empty()
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		SetTableSuccess
	)
	{
		CsvFileIoManager manager;

		std::unordered_map<
			std::string,
			std::vector<std::string>
		> table{
			{"A",{"1","4"}},
			{"B",{"2","5"}},
			{"C",{"3","6"}}
		};

		EXPECT_TRUE(
			manager.set_table(
				file_path_.string(),
				table
			)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		AppendRowMapSuccess
	)
	{
		CsvFileIoManager manager;

		std::unordered_map<
			std::string,
			std::string
		> row{
			{"A","7"},
			{"B","8"},
			{"C","9"}
		};

		EXPECT_TRUE(
			manager.append_row(
				file_path_.string(),
				row
			)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		AppendColumnMapSuccess
	)
	{
		CsvFileIoManager manager;

		std::unordered_map<
			size_t,
			std::string
		> column{
			{0,"X"},
			{1,"Y"}
		};

		EXPECT_TRUE(
			manager.append_column(
				file_path_.string(),
				"D",
				column
			)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		SetRowMapSuccess
	)
	{
		CsvFileIoManager manager;

		std::unordered_map<
			std::string,
			std::string
		> row{
			{"A","10"},
			{"B","11"},
			{"C","12"}
		};

		EXPECT_TRUE(
			manager.set_row(
				file_path_.string(),
				0,
				row
			)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		SetColumnMapSuccess
	)
	{
		CsvFileIoManager manager;

		std::unordered_map<
			size_t,
			std::string
		> column{
			{0,"10"},
			{1,"11"}
		};

		EXPECT_TRUE(
			manager.set_column(
				file_path_.string(),
				"A",
				column
			)
		);
	}

	TEST_F(
		CsvFileIoManagerTest,
		InsertRowMapSuccess
	)
	{
		CsvFileIoManager manager;

		std::unordered_map<
			std::string,
			std::string
		> row{
			{"A","13"},
			{"B","14"},
			{"C","15"}
		};

		EXPECT_TRUE(
			manager.insert_row(
				file_path_.string(),
				1,
				row
			)
		);
	}


	TEST_F(CsvFileIoManagerTest, InsertColumnMapSuccess)
	{
		CsvFileIoManager manager;

		std::unordered_map<size_t, std::string> column{
			{0, "X"},
			{1, "Y"}
		};

		EXPECT_TRUE(
			manager.insert_column(
				file_path_.string(),
				"D",
				column
			)
		);
	}

	TEST_F(CsvFileIoManagerTest, InvalidColumnName)
	{
		CsvFileIoManager manager;

		auto result = manager.get_column(
			file_path_.string(),
			"Z"
		);

		EXPECT_TRUE(result.empty());
	}

	TEST_F(CsvFileIoManagerTest, InvalidRowIndex)
	{
		CsvFileIoManager manager;

		auto result = manager.get_row(
			file_path_.string(),
			100
		);

		EXPECT_TRUE(result.empty());
	}

	TEST_F(CsvFileIoManagerTest, EmptyFilePath)
	{
		CsvFileIoManager manager;
		std::vector<std::string> values{ "1","2","3" };

		EXPECT_FALSE(
			manager.append_row("", values)
		);
	}

	TEST_F(CsvFileIoManagerTest, WhitespaceFilePath)
	{
		CsvFileIoManager manager;
		std::vector<std::string> values{ "1","2","3" };

		EXPECT_FALSE(
			manager.append_row("   ", values)
		);
	}

	TEST_F(CsvFileIoManagerTest, ConcurrentAppendRow)
	{
		CsvFileIoManager manager;

		auto task = [&]()
			{
				std::vector<std::string> row{ "7","8","9" };
				manager.append_row(file_path_.string(), row);
			};

		std::thread t1(task);
		std::thread t2(task);
		std::thread t3(task);

		t1.join();
		t2.join();
		t3.join();

		EXPECT_TRUE(manager.is_valid(file_path_.string()));
	}

	TEST_F(CsvFileIoManagerTest, ConcurrentReadWrite)
	{
		CsvFileIoManager manager;

		auto write_task = [&]()
			{
				std::vector<std::string> row{ "7","8","9" };
				manager.append_row(file_path_.string(), row);
			};

		auto read_task = [&]()
			{
				manager.read(file_path_.string());
			};

		std::thread t1(write_task);
		std::thread t2(read_task);

		t1.join();
		t2.join();

		EXPECT_TRUE(manager.is_valid(file_path_.string()));
	}

	TEST_F(CsvFileIoManagerTest, StressAppendRow)
	{
		CsvFileIoManager manager;

		for (size_t i = 0; i < 100; ++i)
		{
			std::vector<std::string> row{ "7","8","9" };
			manager.append_row(file_path_.string(), row);
		}

		EXPECT_TRUE(manager.is_valid(file_path_.string()));
	}

	TEST_P(CsvFileIoManagerParameterizedValuesTest, AppendRowParameterized)
	{
		CsvFileIoManager manager;
		auto values = GetParam();

		EXPECT_TRUE(manager.append_row(file_path_.string(), values));
	}
}

#endif
