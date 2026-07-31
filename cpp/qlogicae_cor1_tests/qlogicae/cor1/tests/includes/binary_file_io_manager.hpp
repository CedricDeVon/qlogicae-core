#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		BinaryFileIoManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class BinaryFileIoManagerTest:
		public ::testing::Test
	{
	public:
		BinaryFileIoManagerTest()
		{
			temporary_file_path =
				std::filesystem::temp_directory_path()
				/ "binary_file_io_test_full.bin";
		}

		BinaryFileIoManager
			manager;

		std::filesystem::path
			temporary_file_path;

		std::vector<std::byte>
			create_bytes(
				const size_t&
				size
			)
		{
			std::vector<std::byte>
				bytes;

			bytes.resize(size);

			for
				(
					size_t
					index = 0;
					index < size;
					++index
					)
			{
				bytes[index] =
					std::byte(index % 255);
			}

			return
				bytes;
		}

		void SetUp() override
		{
			std::filesystem::remove(
				temporary_file_path
			);

			manager
				.configurations
				.is_feature_edge_case_handling_enabled = true;

			manager
				.configurations
				.is_feature_thread_safety_handling_enabled = true;
		}
	};

	class InvalidPathParameterizedTest:
		public BinaryFileIoManagerTest,
		public ::testing::WithParamInterface<std::string>
	{
	};
}

#endif
