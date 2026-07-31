#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonFileIoManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class JsonFileIoManagerValidationTest:
		public ::testing::Test
	{
	public:
		JsonFileIoManager
			manager;

		std::filesystem::path
			valid_file;

		std::filesystem::path
			invalid_file;

		void
			SetUp() override
		{
			valid_file =
				std::filesystem::temp_directory_path() /
				"json_file_io_valid_test.json";

			invalid_file =
				std::filesystem::temp_directory_path() /
				"json_file_io_invalid_test.json";

			{
				std::ofstream output(valid_file);
				output << "{ \"a\": { \"b\": 1 }, \"array\": [1,2,3] }";
			}

			{
				std::ofstream output(invalid_file);
				output << "{ invalid json ";
			}
		}

		void
			TearDown() override
		{
			if(std::filesystem::exists(valid_file))
				std::filesystem::remove(valid_file);

			if(std::filesystem::exists(invalid_file))
				std::filesystem::remove(invalid_file);
		}
	};
}

#endif
