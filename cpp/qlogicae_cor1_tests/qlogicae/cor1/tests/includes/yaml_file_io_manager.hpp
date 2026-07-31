#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		YamlFileIoManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		YamlFileIoManagerTest :
		public testing::Test
	{
	public:
		YamlFileIoManager
			yaml_file_io_manager;
	
		std::filesystem::path
			temporary_directory_path;

		std::filesystem::path
			temporary_file_path;

		YamlFileIoManagerTest()
		{
			temporary_directory_path =
				std::filesystem::temp_directory_path() /
				"yaml_file_io_manager_test";

			std::filesystem::create_directories(
				temporary_directory_path
			);

			temporary_file_path =
				temporary_directory_path /
				"test.yaml";
		}

		void
			SetUp() override
		{
			std::ofstream output_file(
				temporary_file_path.string()
			);

			output_file
				<< "root:\n"
				<< "  string_value: value\n"
				<< "  double_value: 10.5\n"
				<< "  boolean_value: true\n"
				<< "  list_value:\n"
				<< "    - first\n"
				<< "    - second\n"
				<< "  object_value:\n"
				<< "    nested_key: nested_value\n";

			output_file.close();

			yaml_file_io_manager
				.configurations
				.file_path =
				temporary_file_path.string();
		}

		void
			TearDown() override
		{
			std::error_code error_code;

			std::filesystem::remove_all(
				temporary_directory_path,
				error_code
			);
		}
	};

	class
		YamlFileIoManagerParameterizedPathTest :
			public YamlFileIoManagerTest,
			public testing::WithParamInterface<std::string>
	{
	};

	class
		YamlFileIoManagerParameterizedKeyPathTest:
		public YamlFileIoManagerTest,
		public testing::WithParamInterface<
		std::vector<std::variant<std::string,size_t>>
		>
	{
	};
}

#endif
