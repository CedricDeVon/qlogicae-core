#include "pch.hpp"

#include "qlogicae_cpp_core/includes/file_system_manager.hpp"

namespace QLogicaeCppCoreTest
{
    class FileSystemManagerTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            manager.construct(result_status);
        }

        void TearDown() override
        {
            manager.destruct(result_status);
        }

        QLogicaeCppCore::FileSystemManager manager;
        QLogicaeCppCore::Result<bool> result_status;
    };

    struct FilePermissionTestData
    {
        std::wstring path;
        std::filesystem::perms permission;
        bool expected;
    };

    class FileSystemManagerPermissionTest :
        public FileSystemManagerTest,
        public ::testing::WithParamInterface<FilePermissionTestData>
    {
    };

    TEST_F(FileSystemManagerTest, Should_ConstructAndDestruct_Correctly)
    {
        EXPECT_TRUE(result_status.get_value());
    }

    TEST_F(FileSystemManagerTest, Should_GetExecutableFolderPath_ReturnGood)
    {
        QLogicaeCppCore::Result<std::wstring> path_result;
        manager.get_executable_folder_path(path_result);
        EXPECT_TRUE(path_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(path_result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetExecutedFolderPath_ReturnGood)
    {
        QLogicaeCppCore::Result<std::wstring> path_result;
        manager.get_executed_folder_path(path_result);
        EXPECT_TRUE(path_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(path_result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetProgramDataFolderPath_ReturnGood)
    {
        QLogicaeCppCore::Result<std::wstring> path_result;
        manager.get_program_data_folder_path(path_result);
        EXPECT_TRUE(path_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(path_result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetLocalAppDataFolderPath_ReturnGood)
    {
        QLogicaeCppCore::Result<std::wstring> path_result;
        manager.get_local_app_data_folder_path(path_result);
        EXPECT_TRUE(path_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(path_result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetRoamingAppDataFolderPath_ReturnGood)
    {
        QLogicaeCppCore::Result<std::wstring> path_result;
        manager.get_roaming_app_data_folder_path(path_result);
        EXPECT_TRUE(path_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(path_result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetFileByteSize_HandleFileAndDirectory)
    {
        std::filesystem::path test_file = std::filesystem::temp_directory_path() / L"test_file.txt";
        std::ofstream ofs(test_file.wstring());
        ofs << "test";
        ofs.close();

        QLogicaeCppCore::Result<std::size_t> size_result;
        manager.get_file_byte_size(size_result, test_file.wstring());
        EXPECT_TRUE(size_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_EQ(size_result.get_value(), 4);

        QLogicaeCppCore::Result<std::size_t> dir_result;
        manager.get_file_byte_size(dir_result, std::filesystem::temp_directory_path().wstring());
        EXPECT_FALSE(dir_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        std::filesystem::remove(test_file);
    }

    TEST_F(FileSystemManagerTest, Should_GetFolderByteSize_CalculateCorrectly)
    {
        std::filesystem::path test_dir = std::filesystem::temp_directory_path() / L"test_folder";
        std::filesystem::create_directory(test_dir);
        std::filesystem::path file_path = test_dir / L"file.txt";
        std::ofstream ofs(file_path.wstring());
        ofs << "12345";
        ofs.close();

        QLogicaeCppCore::Result<std::size_t> size_result;
        manager.get_folder_byte_size(size_result, test_dir.wstring(), false);
        EXPECT_TRUE(size_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_EQ(size_result.get_value(), 5);

        std::filesystem::remove(file_path);
        std::filesystem::remove(test_dir);
    }

    TEST_F(FileSystemManagerTest, Should_HandleAbsoluteAndRelativePaths)
    {
        QLogicaeCppCore::Result<std::wstring_view> abs_result;
        manager.get_absolute_path(abs_result, L".");
        EXPECT_TRUE(abs_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(abs_result.get_value().empty());

        QLogicaeCppCore::Result<std::wstring_view> rel_result;
        manager.get_relative_path(rel_result, L".", std::filesystem::temp_directory_path().wstring());
        EXPECT_TRUE(rel_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
    }

    TEST_F(FileSystemManagerTest, Should_GetFileExtensionAndStem)
    {
        std::filesystem::path file_path = std::filesystem::temp_directory_path() / L"test_file.txt";
        std::ofstream ofs(file_path.wstring());
        ofs.close();

        QLogicaeCppCore::Result<std::wstring> ext_result;
        manager.get_file_extension(ext_result, file_path.wstring());
        EXPECT_EQ(ext_result.get_value(), L".txt");

        QLogicaeCppCore::Result<std::wstring> stem_result;
        manager.get_file_stem(stem_result, file_path.wstring());
        EXPECT_EQ(stem_result.get_value(), L"test_file");

        std::filesystem::remove(file_path);
    }

    TEST_F(FileSystemManagerTest, Should_GetEntityPathsFilesAndFolders)
    {
        std::filesystem::path test_dir = std::filesystem::temp_directory_path() / L"test_entity_dir";
        std::filesystem::create_directory(test_dir);
        std::ofstream(test_dir / L"file.txt").put('x');

        QLogicaeCppCore::Result<std::vector<std::wstring>> entities_result;
        manager.get_entity_paths(entities_result, test_dir.wstring(), true);
        EXPECT_TRUE(entities_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(entities_result.get_value().empty());

        std::filesystem::remove_all(test_dir);
    }

    INSTANTIATE_TEST_CASE_P(
        PermissionTests,
        FileSystemManagerPermissionTest,
        ::testing::Values(
            FilePermissionTestData{ L"C:\\Windows", std::filesystem::perms::owner_read, true },
            FilePermissionTestData{ L"C:\\Windows", std::filesystem::perms::owner_write, true }
        )
    );

    TEST_P(FileSystemManagerPermissionTest, Should_ValidateUserPermissionLevel)
    {
        const auto& data = GetParam();
        QLogicaeCppCore::Result<bool> perm_result;
        manager.is_entity_user_permission_level_valid(perm_result, data.path, data.permission);
        EXPECT_EQ(perm_result.get_value(), data.expected);
    }

    TEST_F(FileSystemManagerTest, Should_ExecuteAsyncOperations)
    {
        auto future_result = std::async(std::launch::async, [&]()
            {
                QLogicaeCppCore::Result<std::wstring> path_result;
                manager.get_executable_folder_path(path_result);
                return path_result.is_status(QLogicaeCppCore::ResultStatus::GOOD);
            });

        EXPECT_TRUE(future_result.get());
    }

    TEST_F(FileSystemManagerTest, Should_HandleConcurrentAccess)
    {
        std::vector<std::thread> threads;
        std::atomic<int> success_count = 0;
        for (int i = 0; i < 16; i++)
        {
            threads.emplace_back([&]()
                {
                    QLogicaeCppCore::Result<std::wstring> result;
                    manager.get_executed_folder_path(result);
                    if (result.is_status(QLogicaeCppCore::ResultStatus::GOOD))
                        success_count++;
                });
        }
        for (auto& t : threads)
            t.join();

        EXPECT_EQ(success_count.load(), 16);
    }

    TEST_F(FileSystemManagerTest, Should_ConstructSuccessfully_When_Called)
    {
        QLogicaeCppCore::Result<bool> result;
        manager.construct(result);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(FileSystemManagerTest, Should_DestructSuccessfully_When_Called)
    {
        QLogicaeCppCore::Result<bool> result;
        manager.destruct(result);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(FileSystemManagerTest, Should_GetExecutableFolderPath_When_Valid)
    {
        QLogicaeCppCore::Result<std::wstring> result;
        manager.get_executable_folder_path(result);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetExecutedFolderPath_When_Valid)
    {
        QLogicaeCppCore::Result<std::wstring> result;
        manager.get_executed_folder_path(result);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetProgramDataFolderPath_When_Valid)
    {
        QLogicaeCppCore::Result<std::wstring> result;
        manager.get_program_data_folder_path(result);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetLocalAppDataFolderPath_When_Valid)
    {
        QLogicaeCppCore::Result<std::wstring> result;
        manager.get_local_app_data_folder_path(result);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetRoamingAppDataFolderPath_When_Valid)
    {
        QLogicaeCppCore::Result<std::wstring> result;
        manager.get_roaming_app_data_folder_path(result);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetFileByteSize_When_FileExists)
    {
        const std::wstring test_file = L"C:\\Windows\\notepad.exe";
        QLogicaeCppCore::Result<std::size_t> result;
        manager.get_file_byte_size(result, test_file);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_GT(result.get_value(), 0);
    }

    TEST_F(FileSystemManagerTest, Should_ReturnBad_When_FileDoesNotExist)
    {
        QLogicaeCppCore::Result<std::size_t> result;
        manager.get_file_byte_size(result, L"C:\\invalid_file_123456.txt");
        EXPECT_FALSE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_EQ(result.get_value(), 0);
    }

    TEST_F(FileSystemManagerTest, Should_GetFolderByteSize_When_Valid)
    {
        const std::wstring folder = L"C:\\Windows";
        QLogicaeCppCore::Result<std::size_t> result;
        manager.get_folder_byte_size(result, folder, false);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_GT(result.get_value(), 0);
    }

    TEST_F(FileSystemManagerTest, Should_GetAbsolutePath_When_Valid)
    {
        const std::wstring relative = L".\\";
        QLogicaeCppCore::Result<std::wstring_view> result;
        manager.get_absolute_path(result, relative);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_GetRelativePath_When_Valid)
    {
        const std::wstring from = L"C:\\Windows";
        const std::wstring to = L"C:\\Windows\\System32";
        QLogicaeCppCore::Result<std::wstring_view> result;
        manager.get_relative_path(result, from, to);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(result.get_value().empty());
    }

    TEST_F(FileSystemManagerTest, Should_CreateAndRemoveFolder_When_Valid)
    {
        const std::wstring folder = L"C:\\TempTestFolder";
        QLogicaeCppCore::Result<bool> create_result;
        manager.create_folder(create_result, folder);
        EXPECT_TRUE(create_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        QLogicaeCppCore::Result<bool> remove_result;
        manager.remove_folder(remove_result, folder);
        EXPECT_TRUE(remove_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
    }

    TEST_F(FileSystemManagerTest, Should_FindFilesByPattern_When_Valid)
    {
        std::filesystem::path temp_dir = std::filesystem::temp_directory_path() / L"pattern_test";
        std::filesystem::create_directory(temp_dir);
        std::ofstream(temp_dir / L"match1.txt").put('x');
        std::ofstream(temp_dir / L"match2.log").put('y');
        std::ofstream(temp_dir / L"nomatch.dat").put('z');

        QLogicaeCppCore::Result<std::vector<std::wstring>> result;
        manager.find_files_by_pattern(result, temp_dir.wstring(), L".txt", false);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_EQ(result.get_value().size(), 1);

        std::filesystem::remove_all(temp_dir);
    }

    TEST_F(FileSystemManagerTest, Should_CopyFolder_When_Valid)
    {
        std::filesystem::path src_dir = std::filesystem::temp_directory_path() / L"copy_src";
        std::filesystem::path dst_dir = std::filesystem::temp_directory_path() / L"copy_dst";
        std::filesystem::create_directory(src_dir);
        std::ofstream(src_dir / L"file.txt").put('x');

        QLogicaeCppCore::Result<bool> result;
        manager.copy_folder(result, src_dir.wstring(), dst_dir.wstring(), true);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_TRUE(std::filesystem::exists(dst_dir / L"file.txt"));

        std::filesystem::remove_all(src_dir);
        std::filesystem::remove_all(dst_dir);
    }

    TEST_F(FileSystemManagerTest, Should_MoveFolder_When_Valid)
    {
        std::filesystem::path src_dir = std::filesystem::temp_directory_path() / L"move_src";
        std::filesystem::path dst_dir = std::filesystem::temp_directory_path() / L"move_dst";
        std::filesystem::create_directory(src_dir);

        QLogicaeCppCore::Result<bool> result;
        manager.move_folder(result, src_dir.wstring(), dst_dir.wstring());
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(std::filesystem::exists(src_dir));
        EXPECT_TRUE(std::filesystem::exists(dst_dir));

        std::filesystem::remove_all(dst_dir);
    }

    TEST_F(FileSystemManagerTest, Should_RenameEntityFileAndFolder_When_Valid)
    {
        std::filesystem::path file_path = std::filesystem::temp_directory_path() / L"rename_file.txt";
        std::ofstream(file_path).put('x');
        std::filesystem::path folder_path = std::filesystem::temp_directory_path() / L"rename_folder";
        std::filesystem::create_directory(folder_path);

        QLogicaeCppCore::Result<bool> result;
        manager.rename_entity(result, file_path.wstring(), L"renamed_file.txt");
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_TRUE(std::filesystem::exists(std::filesystem::temp_directory_path() / L"renamed_file.txt"));
        std::filesystem::remove(std::filesystem::temp_directory_path() / L"renamed_file.txt");

        manager.rename_entity(result, folder_path.wstring(), L"renamed_folder");
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_TRUE(std::filesystem::exists(std::filesystem::temp_directory_path() / L"renamed_folder"));
        std::filesystem::remove_all(std::filesystem::temp_directory_path() / L"renamed_folder");
    }

    TEST_F(FileSystemManagerTest, Should_RemoveFolderSubFiles_When_RecursiveAndNonRecursive)
    {
        std::filesystem::path test_dir = std::filesystem::temp_directory_path() / L"remove_subfiles";
        std::filesystem::create_directory(test_dir);
        std::ofstream(test_dir / L"file1.txt").put('x');
        std::filesystem::path sub_dir = test_dir / L"sub";
        std::filesystem::create_directory(sub_dir);
        std::ofstream(sub_dir / L"file2.txt").put('y');

        QLogicaeCppCore::Result<bool> result;
        manager.remove_folder_sub_files(result, test_dir.wstring(), false);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(std::filesystem::exists(test_dir / L"file1.txt"));
        EXPECT_TRUE(std::filesystem::exists(sub_dir));

        manager.remove_folder_sub_files(result, test_dir.wstring(), true);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_FALSE(std::filesystem::exists(sub_dir));

        std::filesystem::remove_all(test_dir);
    }

    TEST_F(FileSystemManagerTest, Should_ValidateIsPathFoundEntityFileFolder)
    {
        std::filesystem::path test_file = std::filesystem::temp_directory_path() / L"testfile.txt";
        std::ofstream(test_file).put('x');
        std::filesystem::path test_dir = std::filesystem::temp_directory_path() / L"testfolder";
        std::filesystem::create_directory(test_dir);

        QLogicaeCppCore::Result<bool> result;
        manager.is_path_found(result, test_file.wstring());
        EXPECT_TRUE(result.get_value());

        manager.is_entity(result, test_file.wstring());
        EXPECT_TRUE(result.get_value());

        manager.is_file(result, test_file.wstring());
        EXPECT_TRUE(result.get_value());

        manager.is_folder(result, test_dir.wstring());
        EXPECT_TRUE(result.get_value());

        std::filesystem::remove(test_file);
        std::filesystem::remove_all(test_dir);
    }

    TEST_F(FileSystemManagerTest, Should_ReturnBad_When_InvalidPath)
    {
        QLogicaeCppCore::Result<bool> result;
        manager.is_path_found(result, L"C:\\invalid_path_123");
        EXPECT_FALSE(result.get_value());

        manager.is_entity(result, L"C:\\invalid_path_123");
        EXPECT_FALSE(result.get_value());

        manager.is_file(result, L"C:\\invalid_path_123");
        EXPECT_FALSE(result.get_value());

        manager.is_folder(result, L"C:\\invalid_path_123");
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(FileSystemManagerTest, Should_GetFilePaths_RecursiveAndNonRecursive)
    {
        std::filesystem::path test_dir = std::filesystem::temp_directory_path() / L"test_file_paths";
        std::filesystem::create_directory(test_dir);
        std::ofstream(test_dir / L"file1.txt").put('a');
        std::filesystem::create_directory(test_dir / L"subdir");
        std::ofstream(test_dir / L"subdir/file2.txt").put('b');

        QLogicaeCppCore::Result<std::vector<std::wstring>> result_non_recursive;
        manager.get_file_paths(result_non_recursive, test_dir.wstring(), false);
        EXPECT_TRUE(result_non_recursive.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_EQ(result_non_recursive.get_value().size(), 1);

        QLogicaeCppCore::Result<std::vector<std::wstring>> result_recursive;
        manager.get_file_paths(result_recursive, test_dir.wstring(), true);
        EXPECT_TRUE(result_recursive.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_EQ(result_recursive.get_value().size(), 2);

        std::filesystem::remove_all(test_dir);
    }

    TEST_F(FileSystemManagerTest, Should_HandleEmptyFoldersCorrectly)
    {
        std::filesystem::path empty_dir = std::filesystem::temp_directory_path() / L"empty_folder_test";
        std::filesystem::create_directory(empty_dir);

        QLogicaeCppCore::Result<std::size_t> folder_size;
        manager.get_folder_byte_size(folder_size, empty_dir.wstring(), true);
        EXPECT_TRUE(folder_size.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_EQ(folder_size.get_value(), 0);

        QLogicaeCppCore::Result<std::vector<std::wstring>> paths_result;
        manager.get_entity_paths(paths_result, empty_dir.wstring(), true);
        EXPECT_TRUE(paths_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_TRUE(paths_result.get_value().empty());

        std::filesystem::remove_all(empty_dir);
    }

    TEST_F(FileSystemManagerTest, Should_HandleNonExistentPaths)
    {
        std::wstring invalid_path = L"C:\\invalid_path_123456789";
        QLogicaeCppCore::Result<bool> path_result;
        manager.is_path_found(path_result, invalid_path);
        EXPECT_FALSE(path_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        QLogicaeCppCore::Result<std::size_t> size_result;
        manager.get_file_byte_size(size_result, invalid_path);
        EXPECT_FALSE(size_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        manager.get_folder_byte_size(size_result, invalid_path, true);
        EXPECT_FALSE(size_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
    }

    TEST_F(FileSystemManagerTest, Should_ValidateFilePermissions_Dynamically)
    {
        std::filesystem::path test_file = std::filesystem::temp_directory_path() / L"permission_test_file.txt";
        std::ofstream(test_file).put('x');

        QLogicaeCppCore::Result<bool> read_perm;
        manager.is_entity_user_permission_level_valid(read_perm, test_file.wstring(),
            std::filesystem::perms::owner_read);
        EXPECT_TRUE(read_perm.get_value());

        QLogicaeCppCore::Result<bool> write_perm;
        manager.is_entity_user_permission_level_valid(write_perm, test_file.wstring(),
            std::filesystem::perms::owner_write);
        EXPECT_TRUE(write_perm.get_value());

        std::filesystem::remove(test_file);
    }

    TEST_F(FileSystemManagerTest, Should_StressTestConcurrentAccess)
    {
        std::filesystem::path test_file = std::filesystem::temp_directory_path() / L"stress_test_file.txt";
        std::ofstream(test_file).put('x');

        std::atomic<int> success_count = 0;
        std::vector<std::thread> threads;
        for (int i = 0; i < 32; i++)
        {
            threads.emplace_back([&]()
                {
                    QLogicaeCppCore::Result<std::wstring> result;
                    manager.get_executed_folder_path(result);
                    if (result.is_status(QLogicaeCppCore::ResultStatus::GOOD))
                        success_count++;
                });
        }

        for (auto& t : threads)
            t.join();

        EXPECT_EQ(success_count.load(), 32);

        std::filesystem::remove(test_file);
    }

    TEST_F(FileSystemManagerTest, Should_SetEntityReadStatus_When_Valid)
    {
        std::filesystem::path test_file = std::filesystem::temp_directory_path() / L"read_status_test.txt";
        std::ofstream(test_file).put('x');

        QLogicaeCppCore::Result<bool> result;
        manager.set_entity_read_status(result, test_file.wstring(), true);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        std::filesystem::remove(test_file);
    }

    TEST_F(FileSystemManagerTest, Should_SetEntityWriteStatus_When_Valid)
    {
        std::filesystem::path test_file = std::filesystem::temp_directory_path() / L"write_status_test.txt";
        std::ofstream(test_file).put('x');

        QLogicaeCppCore::Result<bool> result;
        manager.set_entity_write_status(result, test_file.wstring(), false);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        std::filesystem::remove(test_file);
    }

    TEST_F(FileSystemManagerTest, Should_SetEntityVisibility_When_Valid)
    {
        std::filesystem::path test_file = std::filesystem::temp_directory_path() / L"visibility_test.txt";
        std::ofstream(test_file).put('x');

        QLogicaeCppCore::Result<bool> result;
        manager.set_entity_visibility(result, test_file.wstring(), true);
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        std::filesystem::remove(test_file);
    }

    TEST_F(FileSystemManagerTest, Should_CopyAndMoveFile_When_Valid)
    {
        std::filesystem::path src_file = std::filesystem::temp_directory_path() / L"source_file.txt";
        std::filesystem::path dst_file = std::filesystem::temp_directory_path() / L"destination_file.txt";
        std::ofstream(src_file).put('x');

        QLogicaeCppCore::Result<bool> result;
        manager.copy_file(result, src_file.wstring(), dst_file.wstring());
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        manager.move_file(result, dst_file.wstring(), (dst_file.wstring() + L".moved"));
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        manager.remove_file(result, (dst_file.wstring() + L".moved"));
        std::filesystem::remove(src_file);
    }

    TEST_F(FileSystemManagerTest, Should_HandleUNCPaths)
    {
        std::wstring unc_path = L"\\\\localhost\\C$\\Windows";
        QLogicaeCppCore::Result<std::size_t> size_result;
        manager.get_folder_byte_size(size_result, unc_path, false);
        EXPECT_TRUE(size_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
    }

    TEST_F(FileSystemManagerTest, Should_HandleCopyMoveOverwriteConflicts)
    {
        std::filesystem::path src_file = std::filesystem::temp_directory_path() / L"conflict_src.txt";
        std::filesystem::path dst_file = std::filesystem::temp_directory_path() / L"conflict_dst.txt";
        std::ofstream(src_file).put('x');
        std::ofstream(dst_file).put('y');

        QLogicaeCppCore::Result<bool> result;
        manager.copy_file(result, src_file.wstring(), dst_file.wstring());
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
        EXPECT_TRUE(std::filesystem::exists(dst_file));

        manager.move_file(result, dst_file.wstring(), src_file.wstring());
        EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        std::filesystem::remove(src_file);
        if (std::filesystem::exists(dst_file))
            std::filesystem::remove(dst_file);
    }

    TEST_F(FileSystemManagerTest, Should_HandleAttributeChangesOnNonExistentFiles)
    {
        const std::wstring invalid_file = L"C:\\nonexistent_file_xyz.txt";
        QLogicaeCppCore::Result<bool> result;

        manager.set_entity_read_status(result, invalid_file, true);
        EXPECT_FALSE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        manager.set_entity_write_status(result, invalid_file, false);
        EXPECT_FALSE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

        manager.set_entity_visibility(result, invalid_file, true);
        EXPECT_FALSE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
    }

    TEST_F(FileSystemManagerTest, Should_HandleConcurrentModificationStress)
    {
        std::filesystem::path test_dir = std::filesystem::temp_directory_path() / L"concurrent_mod_test";
        std::filesystem::create_directory(test_dir);

        std::vector<std::thread> threads;
        std::atomic<int> success_count = 0;

        for (int i = 0; i < 32; i++)
        {
            threads.emplace_back([&]()
                {
                    std::filesystem::path file_path = test_dir / ("file_" + std::to_string(rand() % 1000) + ".txt");
                    std::ofstream(file_path).put('x');

                    QLogicaeCppCore::Result<std::size_t> size_result;
                    manager.get_file_byte_size(size_result, file_path.wstring());
                    if (size_result.is_status(QLogicaeCppCore::ResultStatus::GOOD))
                        success_count++;

                    manager.remove_file(result_status, file_path.wstring());
                });
        }

        for (auto& t : threads)
            t.join();

        EXPECT_EQ(success_count.load(), 32);
        std::filesystem::remove_all(test_dir);
    }

    TEST_F(FileSystemManagerTest, Should_HandleFilesWithMultipleDotsAndLeadingDot)
    {
        std::filesystem::path file1 = std::filesystem::temp_directory_path() / L"multi.part.name.txt";
        std::ofstream(file1).put('x');

        std::filesystem::path file2 = std::filesystem::temp_directory_path() / L".leadingdot";
        std::ofstream(file2).put('y');

        QLogicaeCppCore::Result<std::wstring> ext_result1, stem_result1;
        manager.get_file_extension(ext_result1, file1.wstring());
        manager.get_file_stem(stem_result1, file1.wstring());
        EXPECT_EQ(ext_result1.get_value(), L".txt");
        EXPECT_EQ(stem_result1.get_value(), L"multi.part.name");

        QLogicaeCppCore::Result<std::wstring> ext_result2, stem_result2;
        manager.get_file_extension(ext_result2, file2.wstring());
        manager.get_file_stem(stem_result2, file2.wstring());
        EXPECT_EQ(ext_result2.get_value(), L"");
        EXPECT_EQ(stem_result2.get_value(), L".leadingdot");

        std::filesystem::remove(file1);
        std::filesystem::remove(file2);
    }

    TEST_F(FileSystemManagerTest, Should_HandleDeeplyNestedDirectories)
    {
        std::wstring base_dir = L"\\\\?\\" + std::filesystem::temp_directory_path().wstring() + L"\\deep_nested_test";
        std::filesystem::path nested = base_dir;
        try
        {
            for (int i = 0; i < 10; i++) 
            {
                nested /= L"level_" + std::to_wstring(i);
                std::filesystem::create_directory(nested);
                std::ofstream(nested / L"file.txt").put('x');
            }

            QLogicaeCppCore::Result<std::size_t> folder_size;
            manager.get_folder_byte_size(folder_size, base_dir, true);
            EXPECT_TRUE(folder_size.is_status(QLogicaeCppCore::ResultStatus::GOOD));
            EXPECT_GT(folder_size.get_value(), 0);

            std::filesystem::remove_all(base_dir);
        }
        catch (...)
        {
            
        }
    }

    TEST_F(FileSystemManagerTest, Should_HandlePermissionRestrictedFolders)
    {
        std::filesystem::path restricted_dir = std::filesystem::temp_directory_path() / L"restricted_test";
        std::filesystem::create_directory(restricted_dir);

        try
        {
            std::filesystem::permissions(restricted_dir, std::filesystem::perms::none);

            QLogicaeCppCore::Result<bool> perm_result;
            manager.is_entity_user_permission_level_valid(perm_result, restricted_dir.wstring(),
                std::filesystem::perms::owner_write);

            EXPECT_FALSE(perm_result.get_value());

            std::filesystem::permissions(restricted_dir, std::filesystem::perms::all); 
            std::filesystem::remove_all(restricted_dir);
        }
        catch (...)
        {
            std::filesystem::remove_all(restricted_dir);
        }
    }

    TEST_F(FileSystemManagerTest, Should_HandleSymbolicLinks)
    {
        std::filesystem::path target_file = std::filesystem::temp_directory_path() / L"symlink_target.txt";
        std::ofstream(target_file).put('x');
        std::filesystem::path symlink_file = std::filesystem::temp_directory_path() / L"symlink_file.txt";

        try
        {
            std::filesystem::create_symlink(target_file, symlink_file);

            QLogicaeCppCore::Result<bool> result;
            manager.is_path_found(result, symlink_file.wstring());
            EXPECT_TRUE(result.get_value());

            std::filesystem::remove(target_file);
            std::filesystem::remove(symlink_file);
        }
        catch (...)
        {
            std::filesystem::remove(target_file);
        }
    }

    TEST_F(FileSystemManagerTest, Should_HandleVeryLongPaths)
    {
        try
        {
            std::wstring long_path = L"\\\\?\\" + std::filesystem::temp_directory_path().wstring();
            for (int i = 0; i < 15; i++)
                long_path += L"\\very_long_folder_" + std::to_wstring(i);

            std::filesystem::create_directories(long_path);
            EXPECT_TRUE(std::filesystem::exists(long_path));

            QLogicaeCppCore::Result<bool> result;
            manager.is_path_found(result, long_path);
            EXPECT_TRUE(result.is_status(QLogicaeCppCore::ResultStatus::GOOD));
            EXPECT_TRUE(result.get_value());

            QLogicaeCppCore::Result<std::size_t> size_result;
            manager.get_folder_byte_size(size_result, long_path, true);
            EXPECT_TRUE(size_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

            std::filesystem::remove_all(long_path);
        }
        catch (...)
        {
            
        }
    }

}




/*
TEST_F(FileSystemManagerTest, Should_HandleEmptyOrInvalidArguments)
{
    QLogicaeCppCore::Result<std::size_t> size_result;
    manager.get_file_byte_size(size_result, L"");
    EXPECT_FALSE(size_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

    manager.get_folder_byte_size(size_result, L"", true);
    EXPECT_FALSE(size_result.is_status(QLogicaeCppCore::ResultStatus::GOOD));

    QLogicaeCppCore::Result<std::wstring> str_result;
    manager.get_file_extension(str_result, L"");
    EXPECT_EQ(str_result.get_value(), L"");

    manager.get_file_stem(str_result, L"");
    EXPECT_EQ(str_result.get_value(), L"");
}
*/