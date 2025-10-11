#include "pch.hpp"

#include "csv_file_io.hpp"

namespace QLogicaeCoreTest
{
    class CsvFileIOTestFixture
        : public ::testing::TestWithParam<std::tuple<std::string, std::vector<std::string>>> {
    protected:
        const std::string path = "test.csv";
        QLogicaeCore::CsvFileIO file{ path };

        void SetUp() override {
            std::ostringstream oss;
            oss << "Name,Age,City\n";
            for (int i = 0; i < 10; ++i)
                oss << "Name" << i << "," << (20 + i) << ",City" << i << "\n";

            file.write(oss.str());
            file.open();
        }

        void TearDown() override {
            file.close();
            std::remove(path.c_str());
        }
    };

    TEST_F(CsvFileIOTestFixture, Should_Expect_ValidHeaderDetection_When_HeadersAreCorrect) {
        auto future = file.is_header_found_async("Age");
        ASSERT_TRUE(future.get());
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_InvalidHeaderDetection_When_HeaderIsIncorrect) {
        auto future = file.is_header_found_async("Salary");
        ASSERT_FALSE(future.get());
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_CorrectRowCount_When_FileHasTenRows) {
        auto future = file.get_row_count_async();
        ASSERT_EQ(future.get(), 10);
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_CorrectColumnCount_When_HeaderHasThreeColumns) {
        auto future = file.get_column_count_async();
        ASSERT_EQ(future.get(), 3);
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_CorrectCell_When_CellIsQueried) {
        auto future = file.get_cell_async("City", 5);
        ASSERT_EQ(future.get(), "City5");
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_False_When_IndexOutOfRange) {
        ASSERT_FALSE(file.is_valid_index(100, 2));
        ASSERT_FALSE(file.is_valid_index(2, 100));
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_Json_When_ExportedFromCsv) {
        auto future = file.export_to_json_async();
        auto json = future.get();
        ASSERT_FALSE(json.empty());
        ASSERT_TRUE(json.find("City") != std::string::npos);
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_CorrectInsertUpdateRemoveRow_When_Invoked) {
        std::vector<std::string> row = { "Zed", "99", "NeoCity" };
        ASSERT_TRUE(file.insert_row(0, row));
        ASSERT_EQ(file.get_cell("Name", 0), "Zed");

        std::vector<std::string> new_row = { "Alice", "30", "TechCity" };
        ASSERT_TRUE(file.update_row(0, new_row));
        ASSERT_EQ(file.get_cell("City", 0), "TechCity");

        ASSERT_TRUE(file.remove_row(0));
        ASSERT_NE(file.get_cell("Name", 0), "Alice");
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_Performance_When_ExportingJson) {
        auto start = std::chrono::steady_clock::now();
        file.export_to_json();
        auto end = std::chrono::steady_clock::now();
        ASSERT_LT(std::chrono::duration_cast<std::chrono::seconds>(end - start).count(), 2);
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_CorrectRowMap_When_Queried) {
        auto future = file.get_row_as_map_async(1);
        auto map = future.get();
        ASSERT_EQ(map["Name"], "Name1");
        ASSERT_EQ(map["Age"], "21");
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_CorrectConcurrentAccess_When_MultithreadedReads) {
        std::vector<std::future<std::string>> results;
        for (int i = 0; i < 5; ++i)
            results.push_back(file.get_cell_async("City", i));

        for (int i = 0; i < 5; ++i)
            ASSERT_EQ(results[i].get(), "City" + std::to_string(i));
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_NoDeadlocks_When_StressTested) {
        std::vector<std::thread> threads;
        for (int i = 0; i < 100; ++i) {
            threads.emplace_back([this, i]() {
                file.get_row(i % 10);
                });
        }
        for (auto& t : threads)
            t.join();
        SUCCEED();
    }

    INSTANTIATE_TEST_CASE_P(
        CsvFileIOParameterizedTest,
        CsvFileIOTestFixture,
        ::testing::Values(
            std::make_tuple("City", std::vector<std::string>{ "City10", "City11", "City12", "City13", "City14", "City15", "City16", "City17", "City18", "City19" }),
            std::make_tuple("Age", std::vector<std::string>{ "30", "31", "32", "33", "34", "35", "36", "37", "38", "39" }),
            std::make_tuple("Name", std::vector<std::string>{ "NewName0", "NewName1", "NewName2", "NewName3", "NewName4", "NewName5", "NewName6", "NewName7", "NewName8", "NewName9" })
        )
    );

    TEST_P(CsvFileIOTestFixture, Should_Expect_Match_When_UpdatingColumn) {
        const auto& [header, base_values] = GetParam();
        std::vector<std::string> values;
        for (int i = 0; i < 10; ++i)
            values.push_back(base_values[i % base_values.size()] + std::to_string(i));

        ASSERT_TRUE(file.update_column(header, values));
        const auto col = file.get_column(header);
        for (const auto& val : values)
            ASSERT_NE(col.find(val), std::string::npos);
    }

    TEST_F(CsvFileIOTestFixture, Should_Fail_When_HeaderDoesNotExist) {
        const bool result = file.update_column("UnknownColumn", { "X", "Y", "Z" });
        ASSERT_FALSE(result);
    }

    TEST_F(CsvFileIOTestFixture, Should_Fail_When_ValueCountMismatch) {
        const bool result = file.update_column("Name", { "OnlyOneValue" });
        ASSERT_FALSE(result);
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_Overwrite_When_ColumnUpdatedTwice) {
        std::vector<std::string> first_values(10);
        std::vector<std::string> second_values(10);
        for (int i = 0; i < 10; ++i) {
            first_values[i] = "First" + std::to_string(i);
            second_values[i] = "Second" + std::to_string(i);
        }

        ASSERT_TRUE(file.update_column("Age", first_values));
        ASSERT_TRUE(file.update_column("Age", second_values));
        const auto col = file.get_column("Age");

        for (const auto& val : second_values)
            ASSERT_NE(col.find(val), std::string::npos);
    }

    TEST_F(CsvFileIOTestFixture, Should_Handle_EmptyStringsInUpdate) {
        std::vector<std::string> empty_values(10, "");
        ASSERT_TRUE(file.update_column("City", empty_values));
        const auto col = file.get_column("City");

        for (const auto& val : empty_values)
            ASSERT_NE(col.find(val), std::string::npos);
    }

    TEST_F(CsvFileIOTestFixture, Should_Preserve_OtherColumns_AfterUpdate) {
        const auto original_name_col = file.get_column("Name");

        std::vector<std::string> city_values(10);
        for (int i = 0; i < 10; ++i)
            city_values[i] = "UpdatedCity" + std::to_string(i);

        ASSERT_TRUE(file.update_column("City", city_values));

        const auto new_name_col = file.get_column("Name");
        ASSERT_EQ(original_name_col, new_name_col);
    }

    TEST_F(CsvFileIOTestFixture, Should_Allow_SpecialCharacters) {
        std::vector<std::string> special_values = {
            "New\nYork", "\"quoted\"", "comma,separated",
            "tab\tvalue", "C#", "C++", "Java", "Python", "Go", "Rust"
        };

        ASSERT_TRUE(file.update_column("City", special_values));
        const auto col = file.get_column("City");

        for (const auto& val : special_values)
            ASSERT_NE(col.find(val), std::string::npos);
    }

    TEST_F(CsvFileIOTestFixture, Should_BeThreadSafe_When_MultipleUpdates) {
        std::vector<std::thread> threads;

        for (int t = 0; t < 4; ++t) {
            threads.emplace_back([&, t] {
                std::vector<std::string> values(10, "Thread" + std::to_string(t));
                file.update_column("City", values);
                });
        }

        for (auto& th : threads)
            th.join();

        const auto col = file.get_column("City");
        ASSERT_FALSE(col.empty());
    }

    TEST(CsvFileIOEdgeTest, Should_Handle_EmptyCsvGracefully) {
        const std::string path = "empty.csv";
        std::ofstream(path).close();
        QLogicaeCore::CsvFileIO file{ path };
        ASSERT_TRUE(file.open());
        ASSERT_EQ(file.get_column_count(), 0);
        ASSERT_EQ(file.get_row_count(), 0);
        std::remove(path.c_str());
    }

    TEST(CsvFileIOEdgeTest, Should_Handle_MalformedRows) {
        const std::string path = "ragged.csv";
        std::ofstream f(path);
        f << "A,B,C\n1,2\n3,4,5,6\n";
        f.close();
        QLogicaeCore::CsvFileIO file{ path };
        ASSERT_TRUE(file.open());
        ASSERT_EQ(file.get_column_count(), 3);
        std::remove(path.c_str());
    }

    TEST_F(CsvFileIOTestFixture, Should_Fail_InsertRow_When_ColumnCountMismatch) {
        ASSERT_FALSE(file.insert_row(0, { "OnlyTwo", "Values" }));
    }

    TEST_F(CsvFileIOTestFixture, Should_Fail_InsertColumn_When_RowCountMismatch) {
        ASSERT_FALSE(file.insert_column(1, { "1", "2", "3" }, "Mismatch"));
    }

    TEST_F(CsvFileIOTestFixture, Should_Remove_Column_When_ValidNameGiven) {
        ASSERT_TRUE(file.remove_column("City"));
        ASSERT_FALSE(file.is_header_found("City"));
    }

    TEST_F(CsvFileIOTestFixture, Should_Fail_InsertColumn_When_NameAlreadyExists) {
        std::vector<std::string> col(10, "NewValue");
        ASSERT_FALSE(file.insert_column(0, col, "Name"));
    }

    TEST_F(CsvFileIOTestFixture, Should_Handle_LargeNumberOfRows) {
        file.close();
        std::ofstream f(path);
        f << "Col\n";
        for (int i = 0; i < 10000; ++i) f << "Val" << i << "\n";
        f.close();
        ASSERT_TRUE(file.open());
        ASSERT_EQ(file.get_row_count(), 10000);
    }

    TEST_F(CsvFileIOTestFixture, Should_Fail_When_ImportingInvalidJson) {
        std::string bad_json = R"([{"A": 1}, "invalid"])";
        ASSERT_FALSE(file.import_from_json(bad_json));
    }

    TEST_F(CsvFileIOTestFixture, Should_Allow_Reopen_After_Close) {
        ASSERT_TRUE(file.close());
        ASSERT_TRUE(file.open());
        ASSERT_EQ(file.get_column_count(), 3);
    }

    TEST_F(CsvFileIOTestFixture, Should_BeThreadSafe_When_AsyncOpenCloseCalledConcurrently) {
        std::vector<std::future<bool>> futures;
        for (int i = 0; i < 20; ++i)
            futures.push_back(i % 2 == 0 ? file.open_async() : file.close_async());

        for (auto& f : futures)
            f.get();

        SUCCEED();
    }

    TEST_F(CsvFileIOTestFixture, Should_Ignore_WhitespaceInHeaderNames) {
        ASSERT_TRUE(file.is_header_found(" Name "));
        ASSERT_TRUE(file.is_header_found("City "));
    }

    TEST(CsvFileIOCorruptTest, Should_Detect_CorruptedFile) {
        const std::string path = "corrupt.csv";
        std::ofstream(path) << "\xFF\xFF\xFF\xFF"; 
        QLogicaeCore::CsvFileIO file{ path };
        ASSERT_FALSE(file.open());
        ASSERT_TRUE(file.is_corrupted());
        std::remove(path.c_str());
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_Idempotent_Close) {
        ASSERT_TRUE(file.close());
        ASSERT_TRUE(file.close());
    }

    TEST_F(CsvFileIOTestFixture, Should_AppendRows_When_UsingAppend) {
        ASSERT_TRUE(file.append("ExtraA,ExtraB,ExtraC\n"));
        ASSERT_TRUE(file.append("Extra1,Extra2,Extra3\n"));
        file.close();
        ASSERT_TRUE(file.open());
        ASSERT_GE(file.get_row_count(), 12);  
    }

    TEST_F(CsvFileIOTestFixture, Should_Fail_Operations_When_FileIsClosed) {
        file.close();
        ASSERT_FALSE(file.is_header_found("Age"));       
        ASSERT_EQ(file.get_column_count(), 0);           
        ASSERT_EQ(file.get_row_count(), 0);
    }

    TEST_F(CsvFileIOTestFixture, Should_ExportToJson_WithQuotesEscaped) {
        std::vector<std::string> quotes = { R"("A")", R"("B")", R"("C")", R"("D")", R"("E")",
                                            R"("F")", R"("G")", R"("H")", R"("I")", R"("J")" };
        ASSERT_TRUE(file.update_column("Name", quotes));
        const auto json = file.export_to_json();
        for (const auto& val : quotes) {
            const std::string escaped = "\\\"" + val.substr(1, val.size() - 2) + "\\\""; 
            ASSERT_NE(json.find(escaped), std::string::npos);
        }
    }

    TEST_F(CsvFileIOTestFixture, Should_Survive_ConcurrentExportOnly) {
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back([this]() {
                file.export_to_json();
                });
        }
        for (auto& t : threads) t.join();
        SUCCEED();
    }

    TEST_F(CsvFileIOTestFixture, Should_ExportJson_Then_ReimportSuccessfully) {
        auto json = file.export_to_json();
        file.close();
        ASSERT_EQ(file.get_row_count(), 0);
        ASSERT_TRUE(file.import_from_json(json));
        ASSERT_EQ(file.get_row_count(), 10);
        ASSERT_EQ(file.get_cell("City", 9), "City9");
    }

    TEST_F(CsvFileIOTestFixture, Should_Handle_HeaderOnlyCsv) {
        file.close();
        std::ofstream(path) << "ColA,ColB,ColC\n"; 
        ASSERT_TRUE(file.open());
        ASSERT_EQ(file.get_row_count(), 0);
        ASSERT_EQ(file.get_column_count(), 3);
    }

    TEST_F(CsvFileIOTestFixture, Should_ClearDataCorrectly_When_Cleared) {
        file.close();
        ASSERT_EQ(file.get_column_count(), 0);
        ASSERT_EQ(file.get_row_count(), 0);
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_CorrectAllRowsAsMap_When_Queried) {
        auto rows = file.get_all_rows_as_map();
        ASSERT_EQ(rows.size(), 10);

        for (int i = 0; i < 10; ++i) {
            const auto& row = rows[i];
            ASSERT_EQ(row.at("Name"), "Name" + std::to_string(i));
            ASSERT_EQ(row.at("Age"), std::to_string(20 + i));
            ASSERT_EQ(row.at("City"), "City" + std::to_string(i));
        }
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_SameContent_When_SavedAndReadBack) {
        const std::string original = file.read();
        ASSERT_TRUE(file.save());
        file.close();

        QLogicaeCore::CsvFileIO reopened{ path };
        ASSERT_TRUE(reopened.open());
        const std::string after = reopened.read();

        ASSERT_EQ(original, after);
    }

    TEST(CsvFileIODelimiterTest, Should_Parse_Correctly_With_CustomDelimiterAndQuote) {
        const std::string path = "custom_delim.csv";
        std::ofstream(path) << "'Name';'Age';'City'\n'John';'30';'New York'\n";
        QLogicaeCore::CsvFileIO file{ path };

        file.set_delimiter(';');
        file.set_quote_character('\'');
        ASSERT_TRUE(file.open());

        ASSERT_EQ(file.get_column_count(), 3);
        ASSERT_EQ(file.get_row_count(), 1);
        ASSERT_EQ(file.get_cell("City", 0), "New York");

        std::remove(path.c_str());
    }

    TEST_F(CsvFileIOTestFixture, Should_ValidateHeaders_Correctly_When_Matching) {
        std::vector<std::string> expected = { "Name", "Age", "City" };
        ASSERT_TRUE(file.validate_headers(expected));
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_AsyncValidateHeaders_When_Mismatch) {
        const std::vector<std::string> mismatch = { "Age", "Name", "City" };
        auto future = std::async(std::launch::async, [&] {
            return file.validate_headers(mismatch);
            });
        ASSERT_FALSE(future.get());
    }

    TEST_F(CsvFileIOTestFixture, Should_FailValidateHeaders_When_MissingOrWrongOrder) {
        std::vector<std::string> missing = { "Name", "Age" };
        std::vector<std::string> wrong_order = { "City", "Age", "Name" };

        ASSERT_FALSE(file.validate_headers(missing));
        ASSERT_FALSE(file.validate_headers(wrong_order));
    }

    TEST_F(CsvFileIOTestFixture, Should_ClearAllContent_When_Cleared) {
        ASSERT_TRUE(file.clear());
        ASSERT_EQ(file.get_column_count(), 3);  
        ASSERT_EQ(file.get_row_count(), 0);    
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_CorrectAllRowsAsMap_When_QueriedAsync) {
        auto future = file.get_all_rows_as_map_async();
        const auto rows = future.get();

        ASSERT_EQ(rows.size(), 10);
        for (int i = 0; i < 10; ++i) {
            const auto& row = rows[i];
            ASSERT_EQ(row.at("Name"), "Name" + std::to_string(i));
            ASSERT_EQ(row.at("Age"), std::to_string(20 + i));
            ASSERT_EQ(row.at("City"), "City" + std::to_string(i));
        }
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_SameContent_When_SavedAndReadBackAsync) {
        const std::string original = file.read_async().get();
        ASSERT_TRUE(file.save_async().get());
        file.close();

        QLogicaeCore::CsvFileIO reopened{ path };
        ASSERT_TRUE(reopened.open_async().get());
        const std::string after = reopened.read_async().get();

        ASSERT_EQ(original, after);
    }

    TEST(CsvFileIOAsyncDelimiterTest, Should_ParseAsync_With_CustomDelimiterAndQuote) {
        const std::string path = "custom_async.csv";
        std::ofstream(path) << "'A';'B';'C'\n'X';'Y';'Z'\n";
        QLogicaeCore::CsvFileIO file{ path };

        file.set_delimiter(';');
        file.set_quote_character('\'');
        ASSERT_TRUE(file.open_async().get());

        ASSERT_EQ(file.get_column_count_async().get(), 3);
        ASSERT_EQ(file.get_row_count_async().get(), 1);
        ASSERT_EQ(file.get_cell_async("C", 0).get(), "Z");

        std::remove(path.c_str());
    }

    TEST_F(CsvFileIOTestFixture, Should_Expect_AsyncValidateHeaders_When_Matching) {
        const std::vector<std::string> expected = { "Name", "Age", "City" };
        auto future = std::async(std::launch::async, [&] {
            return file.validate_headers(expected);
            });
        ASSERT_TRUE(future.get());
    }

    TEST_F(CsvFileIOTestFixture, Should_WriteContent_When_UsingWriteAsync) {
        const std::string content = "A,B,C\n1,2,3\n4,5,6\n";
        ASSERT_TRUE(file.write_async(content).get());
        file.close();

        ASSERT_TRUE(file.open());
        ASSERT_EQ(file.get_row_count(), 2);
    }

    TEST_F(CsvFileIOTestFixture, Should_AppendContent_When_UsingAppendAsync) {
        ASSERT_TRUE(file.append_async("AppendedA,AppendedB,AppendedC\n").get());
        ASSERT_TRUE(file.append_async("MoreA,MoreB,MoreC\n").get());
        file.close();

        ASSERT_TRUE(file.open());
        ASSERT_GE(file.get_row_count(), 12);
    }

    TEST_F(CsvFileIOTestFixture, Should_ReturnTrue_When_ColumnExists) {
        ASSERT_TRUE(file.has_column("City"));
        ASSERT_FALSE(file.has_column("DoesNotExist"));
    }

    TEST_F(CsvFileIOTestFixture, Should_ReturnTrue_When_RowExists) {
        ASSERT_TRUE(file.has_row(0));
        ASSERT_FALSE(file.has_row(100));
    }

    TEST_F(CsvFileIOTestFixture, Should_InsertColumn_When_AsyncUsed) {
        std::vector<std::string> values(10, "AsyncVal");
        ASSERT_TRUE(file.insert_column_async(3, values, "AsyncCol").get());
        ASSERT_TRUE(file.has_column("AsyncCol"));
    }

    TEST_F(CsvFileIOTestFixture, Should_UpdateCell_When_AsyncUsed) {
        ASSERT_TRUE(file.update_cell_async("Name", 0, "ReplacedName").get());
        ASSERT_EQ(file.get_cell("Name", 0), "ReplacedName");
    }

    TEST_F(CsvFileIOTestFixture, Should_Use_CustomLabelParams_When_Set) {
        file.set_label_params(0, -1); 
        ASSERT_EQ(file.get_column_count(), 3);
    }
}

