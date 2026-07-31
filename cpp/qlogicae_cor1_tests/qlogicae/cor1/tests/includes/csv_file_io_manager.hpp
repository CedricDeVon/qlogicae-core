#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CsvFileIoManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class CsvFileIoManagerTest
		: public ::testing::Test
	{
	public:
		CsvFileIoManagerTest()
		{
			file_path_ =
				std::filesystem::temp_directory_path()
				/
				std::filesystem::path("csv_file_io_manager_test.csv");

			std::ofstream output_stream(file_path_.string());
			output_stream << "A,B,C\n";
			output_stream << "1,2,3\n";
			output_stream << "4,5,6\n";
			output_stream.close();
		}

		std::filesystem::path file_path_;
	};

	class CsvFileIoManagerParameterizedValuesTest
		: public ::testing::TestWithParam<std::vector<std::string>>
	{
	public:
		CsvFileIoManagerParameterizedValuesTest()
		{
			file_path_ =
				std::filesystem::temp_directory_path()
				/
				std::filesystem::path("csv_file_io_manager_param.csv");

			std::ofstream output_stream(file_path_.string());
			output_stream << "A,B,C\n";
			output_stream << "1,2,3\n";
			output_stream.close();
		}

		std::filesystem::path file_path_;
	};

	class CsvFileIoManagerEmptyParameterizedTest
		: public ::testing::TestWithParam<int>
	{
	public:
		CsvFileIoManagerEmptyParameterizedTest()
		{
			file_path_ =
				std::filesystem::temp_directory_path()
				/
				std::filesystem::path("csv_empty_param.csv");

			std::ofstream output_stream(file_path_.string());
			output_stream << "A,B\n";
			output_stream.close();
		}

		std::filesystem::path file_path_;
	};
}

#endif
