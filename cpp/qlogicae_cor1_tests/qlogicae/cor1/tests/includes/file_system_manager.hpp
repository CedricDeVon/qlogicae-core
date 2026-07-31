#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemManager \
	)

#include "qlogicae/cor1/includes/file_system_manager.hpp"

#include <Shlwapi.h>

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class FileSystemManagerFolderPathsTest: public ::testing::Test
	{
	public:
		FileSystemManager file_system_manager;

		void
			SetUp() override
		{
			file_system_manager.construct();
			file_system_manager.reset();
		}

		void
			TearDown() override
		{
			file_system_manager.destruct();
			file_system_manager.reset();
		}
	};

	class FileSystemManagerPathOperationsTest: public ::testing::Test
	{
	public:
		FileSystemManager file_system_manager;

		const std::wstring test_file_w = L"test_file.txt";
		const std::string test_file_s = "test_file.txt";

		const std::wstring test_folder_w = L"test_folder";
		const std::string test_folder_s = "test_folder";

		void SetUp() override
		{
			if(!std::filesystem::exists(test_folder_w))
				std::filesystem::create_directory(test_folder_w);

			std::ofstream(test_file_s).put('x');

			file_system_manager.construct();
			file_system_manager.reset();
		}

		void TearDown() override
		{
			std::filesystem::remove(test_file_s);
			std::filesystem::remove_all(test_folder_w);

			file_system_manager.destruct();
			file_system_manager.reset();
		}
	};

	class FileSystemManagerEntityAttributesTest: public ::testing::Test
	{
	public:
		FileSystemManager file_system_manager;

		const std::wstring test_file_w = L"test_file.txt";
		const std::string test_file_s = "test_file.txt";

		const std::wstring test_folder_w = L"test_folder";
		const std::string test_folder_s = "test_folder";

		void SetUp() override
		{
			if(!std::filesystem::exists(test_folder_w))
				std::filesystem::create_directory(test_folder_w);

			std::ofstream(test_file_s).put('x');

			SetFileAttributesW(test_file_w.c_str(),FILE_ATTRIBUTE_NORMAL);
			SetFileAttributesW(test_folder_w.c_str(),FILE_ATTRIBUTE_NORMAL);

			file_system_manager.construct();
			file_system_manager.reset();
		}

		void TearDown() override
		{
			SetFileAttributesW(test_file_w.c_str(),FILE_ATTRIBUTE_NORMAL);
			SetFileAttributesW(test_folder_w.c_str(),FILE_ATTRIBUTE_NORMAL);

			std::filesystem::remove(test_file_s);
			std::filesystem::remove_all(test_folder_w);

			file_system_manager.destruct();
			file_system_manager.reset();
		}

		bool is_read_only(const std::wstring& path)
		{
			DWORD attr = GetFileAttributesW(path.c_str());
			return (attr & FILE_ATTRIBUTE_READONLY) != 0;
		}

		bool is_hidden(const std::wstring& path)
		{
			DWORD attr = GetFileAttributesW(path.c_str());
			return (attr & FILE_ATTRIBUTE_HIDDEN) != 0;
		}
	};

	class FileSystemManagerEntityOperationsTest: public ::testing::Test
	{
	public:
		FileSystemManager file_system_manager;

		const std::wstring test_file_w = L"test_file.txt";
		const std::string test_file_s = "test_file.txt";

		const std::wstring test_folder_w = L"test_folder";
		const std::string test_folder_s = "test_folder";

		void SetUp() override
		{
			if(!std::filesystem::exists(test_folder_w))
				std::filesystem::create_directory(test_folder_w);

			std::ofstream(test_file_s).put('x');

			file_system_manager.construct();
			file_system_manager.reset();
		}

		void TearDown() override
		{
			std::filesystem::remove(test_file_s);
			std::filesystem::remove_all(test_folder_w);
			std::filesystem::remove_all(L"copy_folder_w");
			std::filesystem::remove_all("copy_folder_s");
			std::filesystem::remove("moved_file.txt");
			std::filesystem::remove("moved_folder");
			std::filesystem::remove_all("renamed_folder");
			std::filesystem::remove("renamed_file.txt");

			file_system_manager.destruct();
			file_system_manager.reset();
		}
	};

	class FileSystemManagerRemoveOperationsTest: public ::testing::Test
	{
	public:
		FileSystemManager file_system_manager;

		const std::wstring test_file_w = L"test_file.txt";
		const std::string test_file_s = "test_file.txt";

		const std::wstring test_folder_w = L"test_folder";
		const std::string test_folder_s = "test_folder";

		void SetUp() override
		{
			std::ofstream(test_file_s).put('x');

			if(!std::filesystem::exists(test_folder_w))
				std::filesystem::create_directory(test_folder_w);

			std::ofstream("test_folder/sub_file.txt").put('x');
			std::ofstream("test_folder/sub_file_s.txt").put('x');

			file_system_manager.construct();
			file_system_manager.reset();
		}

		void TearDown() override
		{
			std::filesystem::remove(test_file_s);
			std::filesystem::remove_all(test_folder_w);

			file_system_manager.destruct();
			file_system_manager.reset();
		}
	};
}

#endif
