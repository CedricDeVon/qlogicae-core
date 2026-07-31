#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemManager \
	)

#include "../includes/file_system_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnExecutableFolderPath_When_Called)
	{
		std::wstring result = file_system_manager.get_executable_folder_wstring_path();
		EXPECT_FALSE(result.empty());
		EXPECT_TRUE(std::filesystem::exists(result));
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnExecutedFolderPath_When_Called)
	{
		std::wstring result = file_system_manager.get_executed_folder_wstring_path();
		EXPECT_FALSE(result.empty());
		EXPECT_TRUE(std::filesystem::exists(result));
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnProgramDataFolderPath_When_Called)
	{
		std::wstring result = file_system_manager.get_program_data_folder_wstring_path();
		EXPECT_FALSE(result.empty());
		EXPECT_TRUE(std::filesystem::exists(result));
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnLocalAppDataFolderPath_When_Called)
	{
		std::wstring result = file_system_manager.get_local_app_data_folder_wstring_path();
		EXPECT_FALSE(result.empty());
		EXPECT_TRUE(std::filesystem::exists(result));
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnRoamingAppDataFolderPath_When_Called)
	{
		std::wstring result = file_system_manager.get_roaming_app_data_folder_wstring_path();
		EXPECT_FALSE(result.empty());
		EXPECT_TRUE(std::filesystem::exists(result));
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnExecutableFolderPathString_When_Called)
	{
		std::string result = file_system_manager.get_executable_folder_path();
		EXPECT_FALSE(result.empty());
		EXPECT_TRUE(std::filesystem::exists(result));
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnExecutedFolderPathString_When_Called)
	{
		std::string result = file_system_manager.get_executed_folder_path();
		EXPECT_FALSE(result.empty());
		EXPECT_TRUE(std::filesystem::exists(result));
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnProgramDataFolderPathString_When_Called)
	{
		std::string result = file_system_manager.get_program_data_folder_path();
		EXPECT_FALSE(result.empty());
		EXPECT_TRUE(std::filesystem::exists(result));
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnLocalAppDataFolderPathString_When_Called)
	{
		std::string result = file_system_manager.get_local_app_data_folder_path();
		EXPECT_FALSE(result.empty());
		EXPECT_TRUE(std::filesystem::exists(result));
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnRoamingAppDataFolderPathString_When_Called)
	{
		std::string result = file_system_manager.get_roaming_app_data_folder_path();
		EXPECT_FALSE(result.empty());
		EXPECT_TRUE(std::filesystem::exists(result));
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_ReturnPathsCorrectly_When_CalledFromMultipleThreads)
	{
		auto future_exe = std::async(std::launch::async, [&]()
		{
			return file_system_manager.get_executable_folder_wstring_path();
		});

		auto future_exec = std::async(std::launch::async, [&]()
		{
			return file_system_manager.get_executed_folder_wstring_path();
		});

		auto future_prog = std::async(std::launch::async, [&]()
		{
			return file_system_manager.get_program_data_folder_wstring_path();
		});

		EXPECT_FALSE(future_exe.get().empty());
		EXPECT_FALSE(future_exec.get().empty());
		EXPECT_FALSE(future_prog.get().empty());
	}

	TEST_F(FileSystemManagerFolderPathsTest, Should_NotThrow_When_CalledRepeatedly)
	{
		for (int i = 0; i < 10; i++)
		{
			EXPECT_NO_THROW(file_system_manager.get_executable_folder_wstring_path());
			EXPECT_NO_THROW(file_system_manager.get_executed_folder_wstring_path());
			EXPECT_NO_THROW(file_system_manager.get_program_data_folder_wstring_path());
			EXPECT_NO_THROW(file_system_manager.get_local_app_data_folder_wstring_path());
			EXPECT_NO_THROW(file_system_manager.get_roaming_app_data_folder_wstring_path());

			EXPECT_NO_THROW(file_system_manager.get_executable_folder_path());
			EXPECT_NO_THROW(file_system_manager.get_executed_folder_path());
			EXPECT_NO_THROW(file_system_manager.get_program_data_folder_path());
			EXPECT_NO_THROW(file_system_manager.get_local_app_data_folder_path());
			EXPECT_NO_THROW(file_system_manager.get_roaming_app_data_folder_path());
		}
	}

	TEST_F(FileSystemManagerPathOperationsTest, Should_ReturnFileByteSize)
	{
		auto size_w = file_system_manager.get_file_byte_size(test_file_w);
		auto size_s = file_system_manager.get_file_byte_size(test_file_s);
		EXPECT_GT(size_w, static_cast<size_t>(0));
		EXPECT_GT(size_s, static_cast<size_t>(0));
	}

	TEST_F(FileSystemManagerPathOperationsTest, Should_ReturnFolderByteSize)
	{
		auto size_w = file_system_manager.get_folder_byte_size(test_folder_w.c_str());
		auto size_s = file_system_manager.get_folder_byte_size(test_folder_s);
		EXPECT_GE(size_w, static_cast<size_t>(0));
		EXPECT_GE(size_s, static_cast<size_t>(0));
	}

	TEST_F(FileSystemManagerPathOperationsTest, Should_ReturnAbsolutePath)
	{
		auto abs_w = file_system_manager.get_absolute_path(test_file_w);
		auto abs_s = file_system_manager.get_absolute_path(test_file_s);
		EXPECT_TRUE(std::filesystem::exists(abs_w));
		EXPECT_TRUE(std::filesystem::exists(abs_s));
	}

	TEST_F(FileSystemManagerPathOperationsTest, Should_ReturnRelativePath)
	{
		auto base_w = file_system_manager.get_executed_folder_wstring_path();
		auto base_s = file_system_manager.get_executed_folder_path();

		auto rel_w = file_system_manager.get_relative_path(base_w, base_w + L"\\" + test_file_w);
		auto rel_s = file_system_manager.get_relative_path(base_s, base_s + "\\" + test_file_s);

		EXPECT_FALSE(rel_w.empty());
		EXPECT_FALSE(rel_s.empty());

	}

	TEST_F(FileSystemManagerPathOperationsTest, Should_ReturnFileExtension)
	{
		auto ext_w = file_system_manager.get_file_extension(test_file_w);
		auto ext_s = file_system_manager.get_file_extension(test_file_s);
		EXPECT_EQ(ext_w, L".txt");
		EXPECT_EQ(ext_s, ".txt");
	}

	TEST_F(FileSystemManagerPathOperationsTest, Should_ReturnFileStem)
	{
		auto stem_w = file_system_manager.get_file_stem(test_file_w);
		auto stem_s = file_system_manager.get_file_stem(test_file_s);
		EXPECT_EQ(stem_w, L"test_file");
		EXPECT_EQ(stem_s, "test_file");
	}

	TEST_F(FileSystemManagerPathOperationsTest, Should_CheckPathExistence)
	{
		EXPECT_TRUE(file_system_manager.is_path_found(test_file_w));
		EXPECT_TRUE(file_system_manager.is_path_found(test_file_s));
		EXPECT_FALSE(file_system_manager.is_path_found(L"nonexistent.txt"));
		EXPECT_FALSE(file_system_manager.is_path_found("nonexistent.txt"));
	}

	TEST_F(FileSystemManagerPathOperationsTest, Should_CheckIfEntityIsFileOrFolder)
	{
		EXPECT_TRUE(file_system_manager.is_entity(test_file_w));
		EXPECT_TRUE(file_system_manager.is_file(test_file_w));
		EXPECT_FALSE(file_system_manager.is_folder(test_file_w));

		EXPECT_TRUE(file_system_manager.is_entity(test_folder_w.c_str()));
		EXPECT_FALSE(file_system_manager.is_file(test_folder_w.c_str()));
		EXPECT_TRUE(file_system_manager.is_folder(test_folder_w.c_str()));
	}

	TEST_F(FileSystemManagerPathOperationsTest, Should_ValidateUserPermissions)
	{
		auto perms = std::filesystem::perms::owner_read;
		EXPECT_TRUE(file_system_manager.is_entity_user_permission_level_valid(test_file_w, perms));
		EXPECT_TRUE(file_system_manager.is_entity_user_permission_level_valid(test_file_s, perms));
	}

    TEST_F(FileSystemManagerEntityAttributesTest, Should_SetAndClearReadStatus_Wstring)
    {
        EXPECT_TRUE(file_system_manager.set_entity_read_status(test_file_w, true));
        EXPECT_TRUE(is_read_only(test_file_w));

        EXPECT_TRUE(file_system_manager.set_entity_read_status(test_file_w, false));
        EXPECT_FALSE(is_read_only(test_file_w));

        EXPECT_TRUE(file_system_manager.set_entity_read_status(test_folder_w, true));
        EXPECT_TRUE(is_read_only(test_folder_w));

        EXPECT_TRUE(file_system_manager.set_entity_read_status(test_folder_w, false));
        EXPECT_FALSE(is_read_only(test_folder_w));
    }

    TEST_F(FileSystemManagerEntityAttributesTest, Should_SetAndClearReadStatus_String)
    {
        EXPECT_TRUE(file_system_manager.set_entity_read_status(test_file_s, true));
        EXPECT_TRUE(is_read_only(test_file_w));

        EXPECT_TRUE(file_system_manager.set_entity_read_status(test_file_s, false));
        EXPECT_FALSE(is_read_only(test_file_w));

        EXPECT_TRUE(file_system_manager.set_entity_read_status(test_folder_s, true));
        EXPECT_TRUE(is_read_only(test_folder_w));

        EXPECT_TRUE(file_system_manager.set_entity_read_status(test_folder_s, false));
        EXPECT_FALSE(is_read_only(test_folder_w));
    }

    TEST_F(FileSystemManagerEntityAttributesTest, Should_SetAndClearWriteStatus_Wstring)
    {
        EXPECT_TRUE(file_system_manager.set_entity_write_status(test_file_w, false));
        EXPECT_TRUE(is_read_only(test_file_w));

        EXPECT_TRUE(file_system_manager.set_entity_write_status(test_file_w, true));
        EXPECT_FALSE(is_read_only(test_file_w));
    }

    TEST_F(FileSystemManagerEntityAttributesTest, Should_SetAndClearWriteStatus_String)
    {
        EXPECT_TRUE(file_system_manager.set_entity_write_status(test_file_s, false));
        EXPECT_TRUE(is_read_only(test_file_w));

        EXPECT_TRUE(file_system_manager.set_entity_write_status(test_file_s, true));
        EXPECT_FALSE(is_read_only(test_file_w));
    }

    TEST_F(FileSystemManagerEntityAttributesTest, Should_SetAndClearVisibility_Wstring)
    {
        EXPECT_TRUE(file_system_manager.set_entity_visibility(test_file_w, false));
        EXPECT_TRUE(is_hidden(test_file_w));

        EXPECT_TRUE(file_system_manager.set_entity_visibility(test_file_w, true));
        EXPECT_FALSE(is_hidden(test_file_w));

        EXPECT_TRUE(file_system_manager.set_entity_visibility(test_folder_w, false));
        EXPECT_TRUE(is_hidden(test_folder_w));

        EXPECT_TRUE(file_system_manager.set_entity_visibility(test_folder_w, true));
        EXPECT_FALSE(is_hidden(test_folder_w));
    }

    TEST_F(FileSystemManagerEntityAttributesTest, Should_SetAndClearVisibility_String)
    {
        EXPECT_TRUE(file_system_manager.set_entity_visibility(test_file_s, false));
        EXPECT_TRUE(is_hidden(test_file_w));

        EXPECT_TRUE(file_system_manager.set_entity_visibility(test_file_s, true));
        EXPECT_FALSE(is_hidden(test_file_w));

        EXPECT_TRUE(file_system_manager.set_entity_visibility(test_folder_s, false));
        EXPECT_TRUE(is_hidden(test_folder_w));

        EXPECT_TRUE(file_system_manager.set_entity_visibility(test_folder_s, true));
        EXPECT_FALSE(is_hidden(test_folder_w));
    }

    TEST_F(FileSystemManagerEntityAttributesTest, Should_ReturnFalseForNonexistentPaths)
    {
        EXPECT_FALSE(file_system_manager.set_entity_read_status(L"nonexistent.txt", true));
        EXPECT_FALSE(file_system_manager.set_entity_write_status(L"nonexistent.txt", false));
        EXPECT_FALSE(file_system_manager.set_entity_visibility(L"nonexistent.txt", false));

        EXPECT_FALSE(file_system_manager.set_entity_read_status("nonexistent.txt", true));
        EXPECT_FALSE(file_system_manager.set_entity_write_status("nonexistent.txt", false));
        EXPECT_FALSE(file_system_manager.set_entity_visibility("nonexistent.txt", false));
    }

    TEST_F(FileSystemManagerEntityOperationsTest, Should_CreateFolder)
    {
        EXPECT_TRUE(file_system_manager.create_folder(L"created_folder_w"));
        EXPECT_TRUE(file_system_manager.create_folder("created_folder_s"));

        EXPECT_TRUE(std::filesystem::exists(L"created_folder_w"));
        EXPECT_TRUE(std::filesystem::exists("created_folder_s"));
    }

    TEST_F(FileSystemManagerEntityOperationsTest, Should_CopyFile)
    {
        EXPECT_TRUE(file_system_manager.copy_file(test_file_w, L"copy_file_w.txt"));
        EXPECT_TRUE(file_system_manager.copy_file(test_file_s, "copy_file_s.txt"));

        EXPECT_TRUE(std::filesystem::exists(L"copy_file_w.txt"));
        EXPECT_TRUE(std::filesystem::exists("copy_file_s.txt"));
    }

    TEST_F(FileSystemManagerEntityOperationsTest, Should_CopyFolder)
    {
        EXPECT_TRUE(file_system_manager.copy_folder(test_folder_w, L"copy_folder_w"));
        EXPECT_TRUE(file_system_manager.copy_folder(test_folder_s, "copy_folder_s"));

        EXPECT_TRUE(std::filesystem::exists(L"copy_folder_w"));
        EXPECT_TRUE(std::filesystem::exists("copy_folder_s"));
    }

    TEST_F(FileSystemManagerEntityOperationsTest, Should_MoveFile)
    {
        EXPECT_TRUE(file_system_manager.move_file(test_file_w, L"moved_file.txt"));
        EXPECT_FALSE(std::filesystem::exists(test_file_w));
        EXPECT_TRUE(std::filesystem::exists(L"moved_file.txt"));

        std::ofstream(test_file_s).put('x');
        EXPECT_TRUE(file_system_manager.move_file(test_file_s, "moved_file.txt"));
        EXPECT_FALSE(std::filesystem::exists(test_file_s));
        EXPECT_TRUE(std::filesystem::exists("moved_file.txt"));
    }

    TEST_F(FileSystemManagerEntityOperationsTest, Should_RenameFile)
    {
        EXPECT_TRUE(file_system_manager.rename_file(test_file_w, L"renamed_file.txt"));
        EXPECT_FALSE(std::filesystem::exists(test_file_w));
        EXPECT_TRUE(std::filesystem::exists(L"renamed_file.txt"));

        std::ofstream(test_file_s).put('x');
        EXPECT_TRUE(file_system_manager.rename_file(test_file_s, "renamed_file.txt"));
        EXPECT_FALSE(std::filesystem::exists(test_file_s));
        EXPECT_TRUE(std::filesystem::exists("renamed_file.txt"));
    }

	/*

	TEST_F(FileSystemManagerEntityOperationsTest, Should_MoveFolder)
	{
		EXPECT_TRUE(file_system_manager.move_folder(test_folder_w, L"moved_folder"));
		EXPECT_FALSE(std::filesystem::exists(test_folder_w));
		EXPECT_TRUE(std::filesystem::exists(L"moved_folder"));

		std::filesystem::create_directory(test_folder_s);
		EXPECT_TRUE(file_system_manager.move_folder(test_folder_s, "moved_folder"));
		EXPECT_FALSE(std::filesystem::exists(test_folder_s));
		EXPECT_TRUE(std::filesystem::exists("moved_folder"));
	}

    TEST_F(FileSystemManagerEntityOperationsTest, Should_RenameFolder)
    {
        EXPECT_TRUE(file_system_manager.rename_folder(test_folder_w, L"renamed_folder"));
        EXPECT_FALSE(std::filesystem::exists(test_folder_w));
        EXPECT_TRUE(std::filesystem::exists(L"renamed_folder"));

        std::filesystem::create_directory(test_folder_s);
        EXPECT_TRUE(file_system_manager.rename_folder(test_folder_s, "renamed_folder"));
        EXPECT_FALSE(std::filesystem::exists(test_folder_s));
        EXPECT_TRUE(std::filesystem::exists("renamed_folder"));
    }

    TEST_F(FileSystemManagerEntityOperationsTest, Should_RenameEntity)
    {
        EXPECT_TRUE(file_system_manager.rename_entity(test_file_w, L"renamed_file.txt"));
        EXPECT_FALSE(std::filesystem::exists(test_file_w));
        EXPECT_TRUE(std::filesystem::exists(L"renamed_file.txt"));

        std::ofstream(test_file_s).put('x');
        EXPECT_TRUE(file_system_manager.rename_entity(test_file_s, "renamed_file.txt"));
        EXPECT_FALSE(std::filesystem::exists(test_file_s));
        EXPECT_TRUE(std::filesystem::exists("renamed_file.txt"));

        EXPECT_TRUE(file_system_manager.rename_entity(test_folder_w, L"renamed_folder"));
        EXPECT_FALSE(std::filesystem::exists(test_folder_w));
        EXPECT_TRUE(std::filesystem::exists(L"renamed_folder"));

        std::filesystem::create_directory(test_folder_s);
        EXPECT_TRUE(file_system_manager.rename_entity(test_folder_s, "renamed_folder"));
        EXPECT_FALSE(std::filesystem::exists(test_folder_s));
        EXPECT_TRUE(std::filesystem::exists("renamed_folder"));
    }
	*/


    TEST_F(FileSystemManagerRemoveOperationsTest, Should_RemoveFile)
    {
        EXPECT_TRUE(file_system_manager.remove_file(test_file_w));
        EXPECT_FALSE(std::filesystem::exists(test_file_w));

        std::ofstream(test_file_s).put('x');
        EXPECT_TRUE(file_system_manager.remove_file(test_file_s));
        EXPECT_FALSE(std::filesystem::exists(test_file_s));
    }

    TEST_F(FileSystemManagerRemoveOperationsTest, Should_RemoveFolder)
    {
        EXPECT_TRUE(file_system_manager.remove_folder(test_folder_w));
        EXPECT_FALSE(std::filesystem::exists(test_folder_w));

        std::filesystem::create_directory(test_folder_s);
        EXPECT_TRUE(file_system_manager.remove_folder(test_folder_s));
        EXPECT_FALSE(std::filesystem::exists(test_folder_s));
    }

    TEST_F(FileSystemManagerRemoveOperationsTest, Should_RemoveFolderSubFiles)
    {
        const std::wstring folder_w = L"folder_with_files_w";
        const std::string folder_s = "folder_with_files_s";

        std::filesystem::create_directory(folder_w);
        std::ofstream("folder_with_files_w/file1.txt").put('x');
        std::ofstream("folder_with_files_w/file2.txt").put('x');

        std::filesystem::create_directory(folder_s);
        std::ofstream("folder_with_files_s/file1.txt").put('x');
        std::ofstream("folder_with_files_s/file2.txt").put('x');

        EXPECT_TRUE(file_system_manager.remove_folder_sub_files(folder_w));
        EXPECT_TRUE(std::filesystem::exists(folder_w));
        EXPECT_TRUE(std::filesystem::is_empty(folder_w));

        EXPECT_TRUE(file_system_manager.remove_folder_sub_files(folder_s));
        EXPECT_TRUE(std::filesystem::exists(folder_s));
        EXPECT_TRUE(std::filesystem::is_empty(folder_s));
    }

    TEST_F(FileSystemManagerRemoveOperationsTest, Should_HandleNonexistentEntitiesGracefully)
    {
        EXPECT_FALSE(file_system_manager.remove_file(L"nonexistent_file.txt"));
        EXPECT_FALSE(file_system_manager.remove_file("nonexistent_file.txt"));

        EXPECT_FALSE(file_system_manager.remove_folder(L"nonexistent_folder"));
        EXPECT_FALSE(file_system_manager.remove_folder("nonexistent_folder"));

        EXPECT_FALSE(file_system_manager.remove_folder_sub_files(L"nonexistent_folder"));
        EXPECT_FALSE(file_system_manager.remove_folder_sub_files("nonexistent_folder"));
    }

	TEST_F(FileSystemManagerEntityOperationsTest, Should_HandleNestedFoldersCopyMoveRemove)
	{
		std::filesystem::create_directory(test_folder_w + L"/sub1");
		std::ofstream((test_folder_w + L"/sub1/file1.txt").c_str()).put('x');

		std::filesystem::create_directory(test_folder_s + "/sub1");
		std::ofstream((test_folder_s + "/sub1/file1.txt").c_str()).put('x');

		EXPECT_TRUE(file_system_manager.copy_folder(test_folder_w, L"nested_copy_w"));
		EXPECT_TRUE(std::filesystem::exists(L"nested_copy_w/sub1/file1.txt"));

		EXPECT_TRUE(file_system_manager.copy_folder(test_folder_s, "nested_copy_s"));
		EXPECT_TRUE(std::filesystem::exists("nested_copy_s/sub1/file1.txt"));

		EXPECT_TRUE(file_system_manager.move_folder(L"nested_copy_w", L"nested_move_w"));
		EXPECT_FALSE(std::filesystem::exists(L"nested_copy_w"));
		EXPECT_TRUE(std::filesystem::exists(L"nested_move_w/sub1/file1.txt"));

		EXPECT_TRUE(file_system_manager.move_folder("nested_copy_s", "nested_move_s"));
		EXPECT_FALSE(std::filesystem::exists("nested_copy_s"));
		EXPECT_TRUE(std::filesystem::exists("nested_move_s/sub1/file1.txt"));

		EXPECT_TRUE(file_system_manager.remove_folder(L"nested_move_w"));
		EXPECT_FALSE(std::filesystem::exists(L"nested_move_w"));

		EXPECT_TRUE(file_system_manager.remove_folder("nested_move_s"));
		EXPECT_FALSE(std::filesystem::exists("nested_move_s"));
	}

	TEST_F(FileSystemManagerEntityOperationsTest, Should_HandleNonexistentAndInvalidPaths)
	{
		EXPECT_FALSE(file_system_manager.copy_file(L"<>invalid.txt", L"dest.txt"));
		EXPECT_FALSE(file_system_manager.copy_file("invalid<>.txt", "dest.txt"));

		EXPECT_FALSE(file_system_manager.move_file(L"nonexistent.txt", L"dest.txt"));
		EXPECT_FALSE(file_system_manager.move_file("nonexistent.txt", "dest.txt"));

		EXPECT_FALSE(file_system_manager.rename_file(L"nonexistent.txt", L"renamed.txt"));
		EXPECT_FALSE(file_system_manager.rename_file("nonexistent.txt", "renamed.txt"));

		EXPECT_FALSE(file_system_manager.rename_folder(L"nonexistent_folder", L"renamed"));
		EXPECT_FALSE(file_system_manager.rename_entity(L"nonexistent_entity", L"renamed"));
	}	

	TEST_F(FileSystemManagerEntityOperationsTest, Should_HandleSymbolicLinksAndJunctions)
	{
#ifdef _WIN32
		std::filesystem::create_directory("target_folder");
		BOOL result = CreateSymbolicLinkA("link_folder", "target_folder", SYMBOLIC_LINK_FLAG_DIRECTORY);
		if (result == 0) SUCCEED(); 
		else
		{
			EXPECT_TRUE(file_system_manager.is_folder("target_folder"));
			EXPECT_TRUE(file_system_manager.is_folder("link_folder"));
			EXPECT_TRUE(file_system_manager.remove_folder("link_folder"));
			EXPECT_TRUE(file_system_manager.remove_folder("target_folder"));
		}
#else
		SUCCEED();
#endif
	}
}

#endif
