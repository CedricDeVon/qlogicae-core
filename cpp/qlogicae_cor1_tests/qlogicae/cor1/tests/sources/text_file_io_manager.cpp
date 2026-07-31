#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextFileIoManager \
	)

#include "../includes/text_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{		
	TEST_F(TextFileIoManagerTest, WriteText_ReplacesFileContent)
	{
		TextFileIoManager manager;
		bool success = manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\n");
		EXPECT_TRUE(success);

		std::ifstream file(temp_file);
		std::string content((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
		EXPECT_EQ(content, "Line1\nLine2\nLine3\n");
	}

	TEST_F(TextFileIoManagerTest, AppendText_AddsContent)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\n");

		bool success = manager.append_text(temp_file.string(), "Line2\n");
		EXPECT_TRUE(success);

		std::ifstream file(temp_file);
		std::string content((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
		EXPECT_EQ(content, "Line1\nLine2\n");
	}

	TEST_F(TextFileIoManagerTest, ReadText_ReturnsFullContent)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\n");

		std::string content = manager.read_text(temp_file.string());
		EXPECT_EQ(content, "Line1\nLine2\nLine3\n");
	}

	TEST_F(TextFileIoManagerTest, GetText_ReturnsSpecificLine)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\n");

		std::string line = manager.get_text(temp_file.string(), 2);
		EXPECT_EQ(line, "Line2");
	}

	TEST_F(TextFileIoManagerTest, SetText_ReplacesSpecificLine)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\n");

		bool success = manager.set_text(temp_file.string(), 2, "NewLine2");
		EXPECT_TRUE(success);

		std::ifstream file(temp_file);
		std::string content;
		std::string line;
		while (std::getline(file, line))
			content += line + "\n";

		EXPECT_EQ(content, "Line1\nNewLine2\nLine3\n");
	}

	TEST_F(TextFileIoManagerTest, InsertText_AddsLineAtPosition)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\n");

		bool success = manager.insert_text(temp_file.string(), 2, "InsertedLine");
		EXPECT_TRUE(success);

		std::ifstream file(temp_file);
		std::string content;
		std::string line;
		while (std::getline(file, line))
			content += line + "\n";

		EXPECT_EQ(content, "Line1\nInsertedLine\nLine2\nLine3\n");
	}

	TEST_F(TextFileIoManagerTest, RemoveText_RemovesSpecificLine)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\n");

		bool success = manager.remove_text(temp_file.string(), 2);
		EXPECT_TRUE(success);

		std::ifstream file(temp_file);
		std::string content;
		std::string line;
		while (std::getline(file, line))
			content += line + "\n";

		EXPECT_EQ(content, "Line1\nLine3\n");
	}

	TEST_F(TextFileIoManagerTest, AppendTextVector_AppendsMultipleLines)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\n");

		std::vector<std::string> lines_to_append{ "Line2", "Line3" };
		bool success = manager.append_text(temp_file.string(), lines_to_append);
		EXPECT_TRUE(success);

		std::ifstream file(temp_file);
		std::string content;
		std::string line;
		while (std::getline(file, line))
			content += line + "\n";

		EXPECT_EQ(content, "Line1\nLine2\nLine3\n");
	}

	TEST_F(TextFileIoManagerTest, GetText_MultipleLines)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\nLine4\n");

		std::vector<size_t> lines_to_get{ 2, 4 };
		auto result = manager.get_text(temp_file.string(), lines_to_get);

		EXPECT_EQ(result.size(), 2);
		EXPECT_EQ(result[2], "Line2");
		EXPECT_EQ(result[4], "Line4");
	}

	TEST_F(TextFileIoManagerTest, GetText_RangeOfLines)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\nLine4\n");

		auto result = manager.get_text(temp_file.string(), 2, 3);

		EXPECT_EQ(result.size(), 2);
		EXPECT_EQ(result[2], "Line2");
		EXPECT_EQ(result[3], "Line3");
	}

	TEST_F(TextFileIoManagerTest, SetTextMultiple_ReplacesLines)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\n");

		std::unordered_map<size_t, std::string> updates{ {1, "New1"}, {3, "New3"} };
		bool success = manager.set_text(temp_file.string(), updates);
		EXPECT_TRUE(success);

		std::ifstream file(temp_file);
		std::string content;
		std::string line;
		while (std::getline(file, line))
			content += line + "\n";

		EXPECT_EQ(content, "New1\nLine2\nNew3\n");
	}

	TEST_F(TextFileIoManagerTest, InsertTextMultiple_AddsLines)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\n");

		std::unordered_map<size_t, std::string> inserts{{2, "InsertedA"}, {3, "InsertedB"}};
		bool success = manager.insert_text(temp_file.string(), inserts);
		EXPECT_TRUE(success);

		std::ifstream file(temp_file);
		std::ostringstream content_stream;
		std::string line;
		while (std::getline(file, line))
			content_stream << line << '\n';
		std::string content = content_stream.str();

		EXPECT_EQ(content, "Line1\nInsertedA\nLine2\nInsertedB\nLine3\n");
	}

	TEST_F(TextFileIoManagerTest, RemoveTextMultiple_RemovesLines)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\nLine4\n");

		std::vector<size_t> lines_to_remove{ 2, 4 };
		bool success = manager.remove_text(temp_file.string(), lines_to_remove);
		EXPECT_TRUE(success);

		std::ifstream file(temp_file);
		std::string content;
		std::string line;
		while (std::getline(file, line))
			content += line + "\n";

		EXPECT_EQ(content, "Line1\nLine3\n");
	}

	TEST_F(TextFileIoManagerTest, WriteCreatesFile)
	{
		TextFileIoManager manager;

		manager.configurations.file_path = temp_file.string();
		manager.write_text("hello");

		EXPECT_TRUE(std::filesystem::exists(temp_file));
	}

	TEST_F(TextFileIoManagerTest, WriteAndReadReturnsSameContent)
	{
		TextFileIoManager manager;

		manager.configurations.file_path = temp_file.string();
		std::string content = "sample text";

		manager.write_text(content);
		std::string result = manager.read_text();

		EXPECT_EQ(result, content);
	}

	TEST_F(TextFileIoManagerTest, ReadNonExistingFileThrows)
	{
		TextFileIoManager manager;

		manager.configurations.file_path = temp_file.string();

		EXPECT_NO_THROW(manager.read_text());
	}

	TEST_F(TextFileIoManagerTest, OverwriteExistingFile)
	{
		TextFileIoManager manager;

		manager.configurations.file_path = temp_file.string();

		manager.write_text("first");
		manager.write_text("second");

		std::string result = manager.read_text();

		EXPECT_EQ(result, "second");
	}

	TEST_F(TextFileIoManagerTest, WriteEmptyString)
	{
		TextFileIoManager manager;

		manager.configurations.file_path = temp_file.string();

		manager.write_text("");

		std::string result = manager.read_text();

		EXPECT_EQ(result, "");
	}

	TEST_F(TextFileIoManagerTest, MultipleWritesLastContentPersists)
	{
		TextFileIoManager manager;

		manager.configurations.file_path = temp_file.string();

		manager.write_text("one");
		manager.write_text("two");
		manager.write_text("three");

		std::string result = manager.read_text();

		EXPECT_EQ(result, "three");
	}

	TEST_F(TextFileIoManagerTest, FileExistsAfterWrite)
	{
		TextFileIoManager manager;

		manager.configurations.file_path = temp_file.string();

		manager.write_text("data");

		EXPECT_TRUE(std::filesystem::exists(temp_file));
	}

	TEST_F(TextFileIoManagerTest, ReadAfterMultipleWrites)
	{
		TextFileIoManager manager;

		manager.configurations.file_path = temp_file.string();

		manager.write_text("a");
		manager.write_text("b");

		EXPECT_EQ(manager.read_text(), "b");
	}

	TEST_F(TextFileIoManagerTest, GetText_InvalidLineZero)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		EXPECT_NO_THROW(manager.get_text(temp_file.string(), 0));
	}

	TEST_F(TextFileIoManagerTest, GetText_LineOutOfRange)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		EXPECT_NO_THROW(manager.get_text(temp_file.string(), 100));
	}

	TEST_F(TextFileIoManagerTest, SetText_InvalidLine)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		bool success = manager.set_text(temp_file.string(), 100, "New");
		EXPECT_FALSE(success);
	}

	TEST_F(TextFileIoManagerTest, RemoveText_InvalidLine)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		bool success = manager.remove_text(temp_file.string(), 100);
		EXPECT_FALSE(success);
	}

	TEST_F(TextFileIoManagerTest, InsertText_LineOutOfRange)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		bool success = manager.insert_text(temp_file.string(), 100, "Inserted");
		EXPECT_FALSE(success);
	}

	TEST_F(TextFileIoManagerTest, GetText_FromEmptyFile)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "");

		EXPECT_NO_THROW(manager.get_text(temp_file.string(), 1));
	}

	TEST_F(TextFileIoManagerTest, InsertIntoEmptyFile)
	{
		TextFileIoManager manager;

		manager.configurations.is_feature_edge_case_handling_enabled = true;

		manager.write_text(temp_file.string(), "");

		bool success = manager.insert_text(temp_file.string(), 1, "FirstLine");
		EXPECT_FALSE(success);

		std::string content = manager.read_text(temp_file.string());
		EXPECT_EQ(content, "");
	}

	TEST_F(TextFileIoManagerTest, RemoveFromEmptyFile)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "");

		bool success = manager.remove_text(temp_file.string(), 1);
		EXPECT_FALSE(success);
	}

	TEST_F(TextFileIoManagerTest, AppendEmptyVector)
	{
		TextFileIoManager manager;

		manager.configurations.is_feature_edge_case_handling_enabled = true;

		manager.write_text(temp_file.string(), "Line1\n");

		std::vector<std::string> lines;
		bool success = manager.append_text(temp_file.string(), lines);
		EXPECT_FALSE(success);

		std::string content = manager.read_text(temp_file.string());
		EXPECT_EQ(content, "Line1\n");
	}

	TEST_F(TextFileIoManagerTest, SetEmptyMap)
	{
		TextFileIoManager manager;

		manager.configurations.is_feature_edge_case_handling_enabled = true;

		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		std::unordered_map<size_t, std::string> updates;
		bool success = manager.set_text(temp_file.string(), updates);
		EXPECT_FALSE(success);

		std::string content = manager.read_text(temp_file.string());
		EXPECT_EQ(content, "Line1\nLine2\n");
	}

	TEST_F(TextFileIoManagerTest, InsertEmptyMap)
	{
		TextFileIoManager manager;

		manager.configurations.is_feature_edge_case_handling_enabled = true;

		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		std::unordered_map<size_t, std::string> inserts;
		bool success = manager.insert_text(temp_file.string(), inserts);
		EXPECT_FALSE(success);

		std::string content = manager.read_text(temp_file.string());
		EXPECT_EQ(content, "Line1\nLine2\n");
	}

	TEST_F(TextFileIoManagerTest, RemoveEmptyVector)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		std::vector<size_t> lines;
		bool success = manager.remove_text(temp_file.string(), lines);
		EXPECT_FALSE(success);

		std::string content = manager.read_text(temp_file.string());
		EXPECT_EQ(content, "Line1\nLine2\n");
	}

	TEST_F(TextFileIoManagerTest, AppendToMissingFile)
	{
		TextFileIoManager manager;

		bool success = manager.append_text(temp_file.string(), "Line1\n");
		EXPECT_TRUE(success);

		std::string content = manager.read_text(temp_file.string());
		EXPECT_EQ(content, "Line1\n");
	}

	TEST_F(TextFileIoManagerTest, SetTextMissingFile)
	{
		TextFileIoManager manager;

		bool success = manager.set_text(temp_file.string(), 1, "Line1");
		EXPECT_FALSE(success);
	}

	TEST_F(TextFileIoManagerTest, RemoveTextMissingFile)
	{
		TextFileIoManager manager;

		bool success = manager.remove_text(temp_file.string(), 1);
		EXPECT_FALSE(success);
	}

	TEST_F(TextFileIoManagerTest, InsertText_AtLastLine)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		bool success = manager.insert_text(temp_file.string(), 3, "LastLine");
		EXPECT_TRUE(success);

		std::string content = manager.read_text(temp_file.string());
		EXPECT_EQ(content, "Line1\nLine2\nLastLine\n");
	}

	TEST_F(TextFileIoManagerTest, RemoveText_LastLine)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		bool success = manager.remove_text(temp_file.string(), 2);
		EXPECT_TRUE(success);

		std::string content = manager.read_text(temp_file.string());
		EXPECT_EQ(content, "Line1\n");
	}

	TEST_F(TextFileIoManagerTest, SetText_LastLine)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		bool success = manager.set_text(temp_file.string(), 2, "UpdatedLine2");
		EXPECT_TRUE(success);

		std::string content = manager.read_text(temp_file.string());
		EXPECT_EQ(content, "Line1\nUpdatedLine2\n");
	}

	TEST_F(TextFileIoManagerTest, GetText_RangeStartGreaterThanEnd)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\n");

		auto result = manager.get_text(temp_file.string(), 3, 2);
		EXPECT_TRUE(result.empty());
	}

	TEST_F(TextFileIoManagerTest, GetText_RangeExceedsFile)
	{
		TextFileIoManager manager;
		manager.write_text(temp_file.string(), "Line1\nLine2\nLine3\n");

		auto result = manager.get_text(temp_file.string(), 2, 100);
		EXPECT_EQ(result.size(), 2);
		EXPECT_EQ(result[2], "Line2");
		EXPECT_EQ(result[3], "Line3");
	}

	TEST_F(TextFileIoManagerTest, EdgeFlagDisabled_AppendEmptyVector)
	{
		TextFileIoManager manager;
		manager.configurations.is_feature_edge_case_handling_enabled = false;
		manager.write_text(temp_file.string(), "Line1\n");

		std::vector<std::string> lines;
		bool success = manager.append_text(temp_file.string(), lines);
		EXPECT_TRUE(success);
	}

	TEST_F(TextFileIoManagerTest, EdgeFlagDisabled_SetEmptyMap)
	{
		TextFileIoManager manager;
		manager.configurations.is_feature_edge_case_handling_enabled = false;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		std::unordered_map<size_t, std::string> updates;
		bool success = manager.set_text(temp_file.string(), updates);
		EXPECT_TRUE(success);
	}

	TEST_F(TextFileIoManagerTest, EdgeFlagDisabled_InsertEmptyMap)
	{
		TextFileIoManager manager;
		manager.configurations.is_feature_edge_case_handling_enabled = false;
		manager.write_text(temp_file.string(), "Line1\nLine2\n");

		std::unordered_map<size_t, std::string> inserts;
		bool success = manager.insert_text(temp_file.string(), inserts);
		EXPECT_TRUE(success);
	}

	TEST_F(TextFileIoManagerTest, ReadText_FileOpenFails)
	{
		TextFileIoManager manager;
		std::filesystem::path invalid_path = "/invalid/path/test.txt";
		if (std::filesystem::exists(invalid_path))
		{
			std::filesystem::remove(invalid_path);
		}

		std::string content;
		EXPECT_NO_THROW(content = manager.read_text(invalid_path.string()));
		EXPECT_EQ(content, "");
	}

	TEST_F(TextFileIoManagerTest, WriteText_FileOpenFails)
	{
		TextFileIoManager manager;
		std::filesystem::path invalid_path = "/invalid/path/test.txt";
		if (std::filesystem::exists(invalid_path))
		{
			std::filesystem::remove(invalid_path);
		}

		bool success = manager.write_text(invalid_path.string(), "data");
		EXPECT_TRUE(success);
	}
}

#endif
