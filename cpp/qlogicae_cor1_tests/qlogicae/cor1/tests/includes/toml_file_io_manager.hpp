#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TomlFileIoManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TomlFileIoManagerExtendedTest: public ::testing::Test
	{
	protected:
		std::filesystem::path temp_file;

		void SetUp() override
		{
			temp_file = std::filesystem::temp_directory_path() / "toml_file_io_test.toml";
			std::ofstream ofs(temp_file);
			ofs << R"(
	[section]
	key1 = "value1"
	key2 = 42
	key3 = 3.14
	array_key = [1, 2, 3]
	)";
			ofs.close();
		}

		void TearDown() override
		{
			if(std::filesystem::exists(temp_file))
				std::filesystem::remove(temp_file);
		}

		TomlFileIoManager manager;
	};
}

#endif
