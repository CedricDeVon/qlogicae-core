#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextFileIoManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TextFileIoManagerTest: public ::testing::Test
	{
	protected:
		std::filesystem::path temp_file;

		void SetUp() override
		{
			temp_file = std::filesystem::temp_directory_path() / "text_file_io_test.txt";

			if(std::filesystem::exists(temp_file))
			{
				std::filesystem::remove(temp_file);
			}
		}

		void TearDown() override
		{
			if(std::filesystem::exists(temp_file))
			{
				std::filesystem::remove(temp_file);
			}
		}
	};
}

#endif
