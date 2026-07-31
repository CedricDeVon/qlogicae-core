#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ExcelFileIoManager \
	)

#include "../includes/excel_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(ExcelFileIoManagerTest, Should_ReturnTrue_When_FileIsValid)
	{
		EXPECT_TRUE(manager.is_file_valid());
	}

	TEST_F(ExcelFileIoManagerTest, Should_ReturnFalse_When_WorksheetDoesNotExist)
	{
		EXPECT_FALSE(manager.is_worksheet_found("NonExistentSheet"));
	}

	TEST_F(ExcelFileIoManagerTest, Should_CreateWorksheet_When_NotExists)
	{
		EXPECT_TRUE(manager.create_worksheet(secondary_worksheet_name));
	}

	TEST_F(ExcelFileIoManagerTest, Should_NotCreateWorksheet_When_AlreadyExists)
	{
		manager.create_worksheet(secondary_worksheet_name);
		EXPECT_FALSE(manager.create_worksheet(secondary_worksheet_name));
	}

	TEST_F(ExcelFileIoManagerTest, Should_ClearWorksheet_When_WorksheetExists)
	{
		EXPECT_TRUE(manager.clear_worksheet(test_worksheet_name));
	}

	TEST_F(ExcelFileIoManagerTest, Should_RemoveWorksheet_When_WorksheetExists)
	{
		manager.create_worksheet(secondary_worksheet_name);
		EXPECT_TRUE(manager.remove_worksheet(secondary_worksheet_name));
	}

	TEST_F(ExcelFileIoManagerTest, Should_SetAndGetCellValue_When_ValidCoordinates)
	{
		EXPECT_TRUE(manager.set_cell_value("A1", "TestValue"));
		EXPECT_EQ(manager.get_cell_value("A1"), "TestValue");
	}

	TEST_F(ExcelFileIoManagerTest, Should_SetAndGetCellValues_When_ValidMap)
	{
		std::unordered_map<std::string, std::string> cell_values{
			{"B1", "ValueB1"}, {"C1", "ValueC1"}
		};
		EXPECT_TRUE(manager.set_cell_values(cell_values));
		auto results = manager.get_cell_values({"B1", "C1"});
		EXPECT_EQ(results["B1"], "ValueB1");
		EXPECT_EQ(results["C1"], "ValueC1");
	}

	TEST_F(ExcelFileIoManagerTest, Should_SetAndGetCellValues_When_CoordinateRange)
	{
		EXPECT_TRUE(manager.set_cell_values("D1", "D3", "RangeValue"));
		auto results = manager.get_cell_values("D1", "D3");
		EXPECT_EQ(results["D1"], "RangeValue");
		EXPECT_EQ(results["D2"], "RangeValue");
		EXPECT_EQ(results["D3"], "RangeValue");
	}

	TEST_F(ExcelFileIoManagerTest, Should_ClearCellValue_When_ValidCoordinate)
	{
		manager.set_cell_value("E1", "ClearTest");
		EXPECT_TRUE(manager.clear_cell_value("E1"));
		EXPECT_EQ(manager.get_cell_value("E1"), "");
	}

	TEST_F(ExcelFileIoManagerTest, Should_ClearCellValues_When_VectorCoordinates)
	{
		manager.set_cell_values({{"F1", "X1"}, {"F2", "X2"}});
		EXPECT_TRUE(manager.clear_cell_values({"F1", "F2"}));
		auto results = manager.get_cell_values({"F1", "F2"});
		EXPECT_EQ(results["F1"], "");
		EXPECT_EQ(results["F2"], "");
	}

	TEST_F(ExcelFileIoManagerTest, Should_ClearCellValues_When_CoordinateRange)
	{
		manager.set_cell_values("G1", "G3", "Y");
		EXPECT_TRUE(manager.clear_cell_values("G1", "G3"));
		auto results = manager.get_cell_values("G1", "G3");
		EXPECT_EQ(results["G1"], "");
		EXPECT_EQ(results["G2"], "");
		EXPECT_EQ(results["G3"], "");
	}

	TEST_F(ExcelFileIoManagerTest, Should_BeThreadSafe_When_MultipleThreadsModifyCells)
	{
		manager.create_worksheet("ThreadSheet");
		auto thread_task = [&]()
		{
			for (int i = 1; i <= 10; ++i)
			{
				manager.set_cell_value("A" + std::to_string(i), "ThreadValue");
			}
		};

		std::thread t1(thread_task);
		std::thread t2(thread_task);

		t1.join();
		t2.join();

		auto results = manager.get_cell_values("A1", "A10");
		for (int i = 1; i <= 10; ++i)
		{
			EXPECT_EQ(results["A" + std::to_string(i)], "ThreadValue");
		}
	}

	TEST_F(ExcelFileIoManagerTest, Should_HandleAsync_SetAndGetCellValue)
	{
		auto future_result = std::async(std::launch::async, [&]()
		{
			manager.set_cell_value("H1", "AsyncValue");
			return manager.get_cell_value("H1");
		});
		EXPECT_EQ(future_result.get(), "AsyncValue");
	}

	TEST_F(ExcelFileIoManagerTest, Should_HandleStress_LoadManyCells)
	{
		for (int row = 1; row <= 2; ++row)
		{
			for (int col = 1; col <= 2; ++col)
			{
				std::string coordinate = "I" + std::to_string(row);
				manager.set_cell_value(coordinate, "Stress");
			}
		}
		for (int row = 1; row <= 2; ++row)
		{
			std::string coordinate = "I" + std::to_string(row);
			EXPECT_EQ(manager.get_cell_value(coordinate), "Stress");
		}
	}

	TEST_F(ExcelFileIoManagerTest, Should_CopyWorksheet_When_SourceExists)
	{
		manager.create_worksheet(test_worksheet_name);
		EXPECT_TRUE(manager.copy_worksheet(test_worksheet_name, secondary_worksheet_name));
	}

	TEST_F(ExcelFileIoManagerTest, Should_NotCopyWorksheet_When_SourceDoesNotExist)
	{
		EXPECT_FALSE(manager.copy_worksheet("NonExistentSheet", secondary_worksheet_name));
	}

	TEST_F(ExcelFileIoManagerTest, Should_NotCopyWorksheet_When_DestinationAlreadyExists)
	{
		manager.create_worksheet(test_worksheet_name);
		manager.create_worksheet(secondary_worksheet_name);
		EXPECT_FALSE(manager.copy_worksheet(test_worksheet_name, secondary_worksheet_name));
	}

	TEST_F(ExcelFileIoManagerTest, Should_FailToRemoveWorksheet_When_NotExists)
	{
		EXPECT_THROW(manager.remove_worksheet("NonExistentSheet"), std::runtime_error);
	}

	TEST_P(ExcelFileIoManagerParameterizedTest, Should_HandleEmptyAndInvalidCoordinates)
	{
		const std::string invalid_coordinate = GetParam();
		EXPECT_FALSE(manager.set_cell_value(invalid_coordinate, "Invalid"));
		EXPECT_EQ(manager.get_cell_value(invalid_coordinate), "");
	}

	INSTANTIATE_TEST_CASE_P(
		EdgeCases,
		ExcelFileIoManagerParameterizedTest,
		::testing::Values("", " ", "InvalidCell", "\0")
	);
}

#endif
