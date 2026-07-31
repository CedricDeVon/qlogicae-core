#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		XmlFileIoManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		XmlFileIoManagerTest :
			public ::testing::Test
	{
	public:
		XmlFileIoManagerTest()
		{
			temporary_file_path =
				std::filesystem::temp_directory_path()
				/
				"xml_file_io_manager_test.xml";
		}

		XmlFileIoManager
			manager;

		std::filesystem::path
			temporary_file_path;

		void
			SetUp() override
		{
			std::ofstream
				file(
					temporary_file_path
					.string(),
					std::ios::trunc
				);

			file
				<<
				"<root>"
				"<child value=\"5\">10</child>"
				"</root>";

			file
				.close();

			manager
				.configurations
				.file_path =
				temporary_file_path
				.string();
		}

		void
			TearDown() override
		{
			if
			(
				std::filesystem
					::exists(
						temporary_file_path
					)
			)
			{
				std::filesystem
					::remove(
						temporary_file_path
					);
			}
		}
	};

	class
		XmlFileIoManagerParameterizedValueTest :
			public XmlFileIoManagerTest,
			public ::testing::WithParamInterface<int>
	{
	};

	class
		XmlFileIoManagerParameterizedAttributeTest :
			public XmlFileIoManagerTest,
			public ::testing::WithParamInterface<int>
	{
	};
}

#endif
