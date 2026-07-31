#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ExcelFileIoManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class ExcelFileIoManagerTest: public ::testing::Test
	{
	public:
		ExcelFileIoManager manager;

		const std::string test_file_path = "test_excel_file.xlsx";
		const std::string test_worksheet_name = "Sheet_1";
		const std::string secondary_worksheet_name = "Sheet_2";

	protected:
		void SetUp() override
		{
			if(std::filesystem::exists(test_file_path))
			{
				std::filesystem::remove(test_file_path);
			}

			xlnt::workbook wb;
			auto ws = wb.active_sheet();
			ws.title(test_worksheet_name);
			wb.save(test_file_path);

			manager.configurations.file_path = test_file_path;
			manager.configurations.worksheet_name = test_worksheet_name;
		}

		void TearDown() override
		{
			if(std::filesystem::exists(test_file_path))
			{
				std::filesystem::remove(test_file_path);
			}
		}
	};

	class ExcelFileIoManagerParameterizedTest:
		public ExcelFileIoManagerTest,
		public ::testing::WithParamInterface<std::string>
	{
	};
}

#endif
