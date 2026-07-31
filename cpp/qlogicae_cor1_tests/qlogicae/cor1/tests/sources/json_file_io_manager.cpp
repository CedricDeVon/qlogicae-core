#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonFileIoManager \
	)

#include "../includes/json_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		JsonFileIoManagerValidationTest,
		Should_ReturnTrue_When_FileContainsValidJson)
	{
		EXPECT_TRUE(
			manager.is_valid(
				valid_file.string()));
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		Should_ReturnFalse_When_FileContainsInvalidJson)
	{
		EXPECT_FALSE(
			manager.is_valid(
				invalid_file.string()));
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		Should_ReturnFalse_When_FileDoesNotExist)
	{
		auto missing =
			std::filesystem::temp_directory_path() /
			"json_file_io_missing_test.json";

		EXPECT_FALSE(
			manager.is_valid(
				missing.string()));
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		Should_ReturnFalse_When_PathIsDirectory)
	{
		EXPECT_FALSE(
			manager.is_valid(
				std::filesystem::temp_directory_path().string()));
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		Should_ReturnTrue_When_KeyPathExists)
	{
		std::vector<std::variant<std::string, size_t>>
			key_path =
		{
			std::string("a"),
			std::string("b")
		};

		EXPECT_TRUE(
			manager.is_key_path_valid(
				valid_file.string(),
				key_path));
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		Should_ReturnTrue_When_ArrayIndexExists)
	{
		std::vector<std::variant<std::string, size_t>>
			key_path =
		{
			std::string("array"),
			size_t(1)
		};

		EXPECT_TRUE(
			manager.is_key_path_valid(
				valid_file.string(),
				key_path));
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		Should_ReturnFalse_When_KeyPathDoesNotExist)
	{
		std::vector<std::variant<std::string, size_t>>
			key_path =
		{
			std::string("missing")
		};

		EXPECT_FALSE(
			manager.is_key_path_valid(
				valid_file.string(),
				key_path));
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		Should_ReturnFalse_When_KeyPathEmpty)
	{
		std::vector<std::variant<std::string, size_t>>
			key_path;

		EXPECT_FALSE(
			manager.is_key_path_valid(
				valid_file.string(),
				key_path));
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		Should_ReturnFalse_When_FileInvalidJson_ForKeyPathCheck)
	{
		std::vector<std::variant<std::string, size_t>>
			key_path =
		{
			std::string("a")
		};

		EXPECT_FALSE(
			manager.is_key_path_valid(
				invalid_file.string(),
				key_path));
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		Should_ReturnFalse_When_FileDoesNotExist_ForKeyPathCheck)
	{
		std::vector<std::variant<std::string, size_t>>
			key_path =
		{
			std::string("a")
		};

		auto missing =
			std::filesystem::temp_directory_path() /
			"json_file_io_missing_key_test.json";

		EXPECT_FALSE(
			manager.is_key_path_valid(
				missing.string(),
				key_path));
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetRawJson_ShouldReturnValue_WhenKeyPathValid
	)
	{
		auto result =
			manager.get_raw_json(
				valid_file.string(),
				{ std::string("a"), std::string("b") }
			);

		EXPECT_EQ(result, "1");
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetRawJson_ShouldReturnEmpty_WhenKeyPathInvalid
	)
	{
		auto result =
			manager.get_raw_json(
				valid_file.string(),
				{ std::string("a"), std::string("c") }
			);

		EXPECT_TRUE(result.empty());
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetRawJson_ShouldReturnEmpty_WhenJsonInvalid
	)
	{
		auto result =
			manager.get_raw_json(
				invalid_file.string(),
				{ std::string("a") }
			);

		EXPECT_TRUE(result.empty());
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetString_ShouldReturnString_WhenValueIsString
	)
	{
		std::ofstream output(valid_file);
		output << "{ \"a\": { \"b\": \"text\" } }";
		output.close();

		auto result =
			manager.get_string(
				valid_file.string(),
				{ std::string("a"), std::string("b") }
			);

		EXPECT_EQ(result, "text");
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetString_ShouldReturnEmpty_WhenTypeMismatch
	)
	{
		auto result =
			manager.get_string(
				valid_file.string(),
				{ std::string("a"), std::string("b") }
			);

		EXPECT_TRUE(result.empty());
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetDouble_ShouldReturnNumber_WhenValueIsNumber
	)
	{
		auto result =
			manager.get_double(
				valid_file.string(),
				{ std::string("a"), std::string("b") }
			);

		EXPECT_DOUBLE_EQ(result, 1.0);
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetDouble_ShouldReturnZero_WhenTypeMismatch
	)
	{
		std::ofstream output(valid_file);
		output << "{ \"a\": { \"b\": \"text\" } }";
		output.close();

		auto result =
			manager.get_double(
				valid_file.string(),
				{ std::string("a"), std::string("b") }
			);

		EXPECT_DOUBLE_EQ(result, 0.0);
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetBoolean_ShouldReturnBoolean_WhenValueIsBool
	)
	{
		std::ofstream output(valid_file);
		output << "{ \"a\": { \"b\": true } }";
		output.close();

		auto result =
			manager.get_boolean(
				valid_file.string(),
				{ std::string("a"), std::string("b") }
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetBoolean_ShouldReturnFalse_WhenTypeMismatch
	)
	{
		auto result =
			manager.get_boolean(
				valid_file.string(),
				{ std::string("a"), std::string("b") }
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetNull_ShouldReturnNull_WhenValueIsNull
	)
	{
		std::ofstream output(valid_file);
		output << "{ \"a\": { \"b\": null } }";
		output.close();

		auto result =
			manager.get_null(
				valid_file.string(),
				{ std::string("a"), std::string("b") }
			);

		EXPECT_EQ(result, nullptr);
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		GetNull_ShouldReturnNull_WhenTypeMismatch
	)
	{
		auto result =
			manager.get_null(
				valid_file.string(),
				{ std::string("a"), std::string("b") }
			);

		EXPECT_EQ(result, nullptr);
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		SetRawJson_ShouldReturnTrue_WhenValueValid
	)
	{
		bool result =
			manager.set_raw_json(
				valid_file.string(),
				{ std::string("a"), std::string("c") },
				"{\"x\":1}"
			);

		EXPECT_TRUE(result);

		auto value =
			manager.get_raw_json(
				valid_file.string(),
				{ std::string("a"), std::string("c") }
			);

		EXPECT_EQ(value, "{\"x\":1}");
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		SetRawJson_ShouldReturnFalse_WhenValueInvalid
	)
	{
		bool result =
			manager.set_raw_json(
				valid_file.string(),
				{ std::string("a"), std::string("c") },
				"{ invalid "
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		JsonFileIoManagerValidationTest,
		SetString_ShouldReturnTrue_WhenValueSet
	)
	{
		bool result =
			manager.set_string(
				valid_file.string(),
				{ std::string("a"), std::string("text") },
				"hello"
			);

		EXPECT_TRUE(result);

		auto value =
			manager.get_string(
				valid_file.string(),
				{ std::string("a"), std::string("text") }
			);

		EXPECT_EQ(value, "hello");
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendRawJson_ShouldReturnTrue_WhenValueValid)
	{
		bool result = manager.append_raw_json(
			valid_file.string(),
			{ std::string("a"), std::string("c") },
			"{\"x\":10}"
		);

		EXPECT_TRUE(result);

		auto value = manager.get_raw_json(
			valid_file.string(),
			{ std::string("a"), std::string("c") }
		);

		EXPECT_EQ(value, "{\"x\":10}");
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendRawJson_ShouldReturnFalse_WhenValueInvalid)
	{
		bool result = manager.append_raw_json(
			valid_file.string(),
			{ std::string("a"), std::string("c") },
			"{ invalid "
		);

		EXPECT_FALSE(result);
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendString_ShouldReturnTrue_WhenValueSet)
	{
		bool result = manager.append_string(
			valid_file.string(),
			{ std::string("a"), std::string("text") },
			"hello"
		);

		EXPECT_TRUE(result);

		auto value = manager.get_string(
			valid_file.string(),
			{ std::string("a"), std::string("text") }
		);

		EXPECT_EQ(value, "hello");
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendString_ShouldReturnFalse_WhenFileInvalid)
	{
		bool result = manager.append_string(
			invalid_file.string(),
			{ std::string("a"), std::string("b") },
			"value"
		);

		EXPECT_FALSE(result);
	}

	TEST_F(JsonFileIoManagerValidationTest, RemoveValue_ShouldReturnTrue_WhenKeyExists)
	{
		bool result = manager.remove_value(
			valid_file.string(),
			{ std::string("a"), std::string("b") }
		);

		EXPECT_TRUE(result);

		EXPECT_FALSE(manager.is_key_path_valid(
			valid_file.string(),
			{ std::string("a"), std::string("b") }
		));
	}

	TEST_F(JsonFileIoManagerValidationTest, RemoveValue_ShouldReturnFalse_WhenFileInvalid)
	{
		bool result = manager.remove_value(
			invalid_file.string(),
			{ std::string("a"), std::string("b") }
		);

		EXPECT_FALSE(result);
	}

	TEST_F(JsonFileIoManagerValidationTest, RemoveValue_ShouldReturnFalse_WhenKeyPathEmpty)
	{
		bool result = manager.remove_value(
			valid_file.string(),
			{}
		);

		EXPECT_FALSE(result);
	}

	TEST_F(JsonFileIoManagerValidationTest, RemoveValue_ShouldReturnFalse_WhenFileDoesNotExist)
	{
		auto missing = std::filesystem::temp_directory_path() / "missing.json";

		bool result = manager.remove_value(
			missing.string(),
			{ std::string("a") }
		);

		EXPECT_FALSE(result);
	}

	TEST_F(JsonFileIoManagerValidationTest, IsValid_ReturnsFalse_OnEmptyFile)
	{
		std::filesystem::path empty_file =
			std::filesystem::temp_directory_path() / "empty.json";
		{
			std::ofstream output(empty_file);
		}
		EXPECT_FALSE(manager.is_valid(empty_file.string()));
		std::filesystem::remove(empty_file);
	}

	TEST_F(JsonFileIoManagerValidationTest, GetRawJson_ReturnsAllTypes)
	{
		manager.set_raw_json(valid_file.string(), { "bool_val" }, "true");
		manager.set_raw_json(valid_file.string(), { "null_val" }, "null");
		manager.set_raw_json(valid_file.string(), { "string_val" }, "\"text\"");
		manager.set_raw_json(valid_file.string(), { "array_val" }, "[1,2]");
		manager.set_raw_json(valid_file.string(), { "object_val" }, "{\"x\":1}");

		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "bool_val" }), "true");
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "null_val" }), "null");
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "string_val" }), "\"text\"");
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "array_val" }), "[1,2]");
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "object_val" }), "{\"x\":1}");
	}

	TEST_F(JsonFileIoManagerValidationTest, GetString_ReturnsEmpty_OnMissingOrNonString)
	{
		EXPECT_EQ(manager.get_string(valid_file.string(), { "nonexistent" }), "");
		manager.set_raw_json(valid_file.string(), { "num" }, "1");
		EXPECT_EQ(manager.get_string(valid_file.string(), { "num" }), "");
		manager.set_raw_json(valid_file.string(), { "empty_string" }, "\"\"");
		EXPECT_EQ(manager.get_string(valid_file.string(), { "empty_string" }), "");
	}

	TEST_F(JsonFileIoManagerValidationTest, GetDouble_HandlesIntegersAndFloats)
	{
		manager.set_raw_json(valid_file.string(), { "int_val" }, "42");
		manager.set_raw_json(valid_file.string(), { "float_val" }, "3.14");
		manager.set_raw_json(valid_file.string(), { "negative_val" }, "-2.7");
		EXPECT_DOUBLE_EQ(manager.get_double(valid_file.string(), { "int_val" }), 42.0);
		EXPECT_DOUBLE_EQ(manager.get_double(valid_file.string(), { "float_val" }), 3.14);
		EXPECT_DOUBLE_EQ(manager.get_double(valid_file.string(), { "negative_val" }), -2.7);
		EXPECT_DOUBLE_EQ(manager.get_double(valid_file.string(), { "missing" }), 0.0);
	}

	TEST_F(JsonFileIoManagerValidationTest, GetBoolean_HandlesMissingAndInvalid)
	{
		manager.set_raw_json(valid_file.string(), { "true_val" }, "true");
		manager.set_raw_json(valid_file.string(), { "false_val" }, "false");
		EXPECT_TRUE(manager.get_boolean(valid_file.string(), { "true_val" }));
		EXPECT_FALSE(manager.get_boolean(valid_file.string(), { "false_val" }));
		EXPECT_FALSE(manager.get_boolean(valid_file.string(), { "missing" }));
		manager.set_raw_json(valid_file.string(), { "num" }, "1");
		EXPECT_FALSE(manager.get_boolean(valid_file.string(), { "num" }));
	}

	TEST_F(JsonFileIoManagerValidationTest, GetNull_HandlesMissingAndInvalid)
	{
		manager.set_raw_json(valid_file.string(), { "null_val" }, "null");
		EXPECT_EQ(manager.get_null(valid_file.string(), { "null_val" }), nullptr);
		EXPECT_EQ(manager.get_null(valid_file.string(), { "missing" }), nullptr);
		manager.set_raw_json(valid_file.string(), { "num" }, "1");
		EXPECT_EQ(manager.get_null(valid_file.string(), { "num" }), nullptr);
	}

	TEST_F(JsonFileIoManagerValidationTest, SetRawJson_HandlesSetNestedObjects)
	{
		std::filesystem::path new_file =
			std::filesystem::temp_directory_path() / "new.json";
		EXPECT_FALSE(manager.set_raw_json(new_file.string(), { "a", "b", "c" }, "1"));
		EXPECT_EQ(manager.get_raw_json(new_file.string(), { "a", "b", "c" }), "");
		EXPECT_FALSE(manager.set_raw_json(invalid_file.string(), { "x" }, "{]"));
		std::filesystem::remove(new_file);
	}

	TEST_F(JsonFileIoManagerValidationTest, SetString_HandlesEmptyAndNested)
	{
		EXPECT_TRUE(manager.set_string(valid_file.string(), { "nested", "key" }, "value"));
		EXPECT_EQ(manager.get_string(valid_file.string(), { "nested", "key" }), "value");
		EXPECT_TRUE(manager.set_string(valid_file.string(), { "empty" }, ""));
		EXPECT_EQ(manager.get_string(valid_file.string(), { "empty" }), "");
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendRawJsonAndAppendString)
	{
		EXPECT_TRUE(manager.append_raw_json(valid_file.string(), { "array" }, "4"));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "array" }), "4");
		EXPECT_TRUE(manager.append_string(valid_file.string(), { "new_array" }, "str"));
		EXPECT_EQ(manager.get_string(valid_file.string(), { "new_array" }), "str");
		EXPECT_FALSE(manager.append_raw_json(invalid_file.string(), { "x" }, "{]"));
		EXPECT_FALSE(manager.append_string(invalid_file.string(), { "x" }, "val"));
	}

	TEST_F(JsonFileIoManagerValidationTest, RemoveValue_HandlesNestedAndArrayIndex)
	{
		manager.set_raw_json(valid_file.string(), { "to_remove" }, "1");
		EXPECT_TRUE(manager.remove_value(valid_file.string(), { "to_remove" }));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "to_remove" }), "");
		manager.set_raw_json(valid_file.string(), { "array_val" }, "[1,2,3]");
		EXPECT_TRUE(manager.remove_value(valid_file.string(), { "array_val", size_t(1) }));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "array_val", size_t(1) }), "3");
		EXPECT_FALSE(manager.remove_value(valid_file.string(), { "missing" }));
	}

	TEST_F(JsonFileIoManagerValidationTest, IsValid_ReturnsFalse_OnEmptyFilePath)
	{
		EXPECT_FALSE(manager.is_valid(""));
	}

	TEST_F(JsonFileIoManagerValidationTest, IsKeyPathValid_ReturnsFalse_OnEmptyKeyPath)
	{
		EXPECT_FALSE(manager.is_key_path_valid(valid_file.string(), {}));
	}

	TEST_F(JsonFileIoManagerValidationTest, GetRawJson_ReturnsEmpty_OnEmptyKeyPath)
	{
		EXPECT_TRUE(manager.get_raw_json(valid_file.string(), {}).empty());
	}

	TEST_F(JsonFileIoManagerValidationTest, GetString_ReturnsEmpty_OnEmptyKeyPath)
	{
		EXPECT_TRUE(manager.get_string(valid_file.string(), {}).empty());
	}

	TEST_F(JsonFileIoManagerValidationTest, GetDouble_ReturnsZero_OnEmptyKeyPath)
	{
		EXPECT_DOUBLE_EQ(manager.get_double(valid_file.string(), {}), 0.0);
	}

	TEST_F(JsonFileIoManagerValidationTest, GetBoolean_ReturnsFalse_OnEmptyKeyPath)
	{
		EXPECT_FALSE(manager.get_boolean(valid_file.string(), {}));
	}

	TEST_F(JsonFileIoManagerValidationTest, GetNull_ReturnsNull_OnEmptyKeyPath)
	{
		EXPECT_EQ(manager.get_null(valid_file.string(), {}), nullptr);
	}

	TEST_F(JsonFileIoManagerValidationTest, SetRawJson_ReturnsFalse_OnEmptyFilePath)
	{
		EXPECT_FALSE(manager.set_raw_json("", { "a" }, "1"));
	}

	TEST_F(JsonFileIoManagerValidationTest, SetString_ReturnsFalse_OnEmptyFilePath)
	{
		EXPECT_FALSE(manager.set_string("", { "a" }, "value"));
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendRawJson_ReturnsFalse_OnEmptyFilePath)
	{
		EXPECT_FALSE(manager.append_raw_json("", { "a" }, "1"));
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendString_ReturnsFalse_OnEmptyFilePath)
	{
		EXPECT_FALSE(manager.append_string("", { "a" }, "value"));
	}

	TEST_F(JsonFileIoManagerValidationTest, RemoveValue_ReturnsFalse_OnEmptyFilePath)
	{
		EXPECT_FALSE(manager.remove_value("", { "a" }));
	}

	TEST_F(JsonFileIoManagerValidationTest, Traverse_ReturnsNull_OnInvalidIntermediatePath)
	{
		rapidjson::Document doc;
		doc.Parse("{\"x\":{\"y\":1}}");
		std::vector<std::variant<std::string, size_t>> path = { "x", "z" };
		EXPECT_EQ(manager.traverse(doc, path), nullptr);
	}

	TEST_F(JsonFileIoManagerValidationTest, Traverse_ReturnsCorrectValue_ForArrayIndex)
	{
		rapidjson::Document doc;
		doc.Parse("{\"arr\":[10,20,30]}");
		std::vector<std::variant<std::string, size_t>> path = { "arr", size_t(1) };
		rapidjson::Value* val = manager.traverse(doc, path);
		ASSERT_NE(val, nullptr);
		EXPECT_EQ(val->GetInt(), 20);
	}

	TEST_F(JsonFileIoManagerValidationTest, GetRawJson_ReturnsEmpty_OnNegativeArrayIndex)
	{
		manager.set_raw_json(valid_file.string(), { "array" }, "[10,20,30]");
		EXPECT_TRUE(manager.get_raw_json(valid_file.string(), { "array", size_t(-1) }).empty());
	}

	TEST_F(JsonFileIoManagerValidationTest, GetRawJson_ReturnsEmpty_OnOutOfRangeArrayIndex)
	{
		manager.set_raw_json(valid_file.string(), { "array" }, "[10,20,30]");
		EXPECT_TRUE(manager.get_raw_json(valid_file.string(), { "array", size_t(5) }).empty());
	}

	TEST_F(JsonFileIoManagerValidationTest, SetRawJson_OverwritesExistingValue)
	{
		manager.set_raw_json(valid_file.string(), { "a", "b" }, "1");
		EXPECT_TRUE(manager.set_raw_json(valid_file.string(), { "a", "b" }, "42"));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "a", "b" }), "42");
	}

	TEST_F(JsonFileIoManagerValidationTest, SetString_OverwritesExistingValue)
	{
		manager.set_string(valid_file.string(), { "a", "text" }, "old");
		EXPECT_TRUE(manager.set_string(valid_file.string(), { "a", "text" }, "new"));
		EXPECT_EQ(manager.get_string(valid_file.string(), { "a", "text" }), "new");
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendRawJson_ToExistingArray)
	{
		manager.set_raw_json(valid_file.string(), { "array" }, "[1,2]");
		EXPECT_TRUE(manager.append_raw_json(valid_file.string(), { "array" }, "3"));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "array" }), "3");
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendString_OverwritesExistingValue)
	{
		manager.set_string(valid_file.string(), { "key" }, "old");
		EXPECT_TRUE(manager.append_string(valid_file.string(), { "key" }, "new"));
		EXPECT_EQ(manager.get_string(valid_file.string(), { "key" }), "new");
	}

	TEST_F(JsonFileIoManagerValidationTest, RemoveValue_ArrayIndexOutOfRange)
	{
		manager.set_raw_json(valid_file.string(), { "array" }, "[1,2,3]");
		EXPECT_FALSE(manager.remove_value(valid_file.string(), { "array", size_t(5) }));
	}

	TEST_F(JsonFileIoManagerValidationTest, GetDouble_ReturnsZero_OnInvalidNumber)
	{
		manager.set_raw_json(valid_file.string(), { "not_number" }, "\"text\"");
		EXPECT_DOUBLE_EQ(manager.get_double(valid_file.string(), { "not_number" }), 0.0);
	}

	TEST_F(JsonFileIoManagerValidationTest, GetBoolean_ReturnsFalse_OnNumber)
	{
		manager.set_raw_json(valid_file.string(), { "num" }, "1");
		EXPECT_FALSE(manager.get_boolean(valid_file.string(), { "num" }));
	}

	TEST_F(JsonFileIoManagerValidationTest, GetNull_ReturnsNull_OnNonNullValue)
	{
		manager.set_raw_json(valid_file.string(), { "not_null" }, "42");
		EXPECT_EQ(manager.get_null(valid_file.string(), { "not_null" }), nullptr);
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendRawJson_ToArray_Concatenates)
	{
		manager.set_raw_json(valid_file.string(), { "numbers" }, "[1,2]");
		EXPECT_TRUE(manager.append_raw_json(valid_file.string(), { "numbers" }, "3"));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "numbers" }), "3");
		EXPECT_TRUE(manager.append_raw_json(valid_file.string(), { "numbers" }, "4"));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "numbers" }), "4");
	}

	TEST_F(JsonFileIoManagerValidationTest, DeeplyNestedKeyPath_SetAndGet)
	{
		EXPECT_TRUE(manager.set_raw_json(valid_file.string(),
			{ "level1", "level2", "level3", "value" }, "42"));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(),
			{ "level1", "level2", "level3", "value" }), "42");
	}

	TEST_F(JsonFileIoManagerValidationTest, SpecialCharacterKeysAndValues)
	{
		EXPECT_TRUE(manager.set_string(valid_file.string(), { "spécial_ß", "тест" }, "üñîçødë"));
		EXPECT_EQ(manager.get_string(valid_file.string(), { "spécial_ß", "тест" }), "üñîçødë");
	}

	TEST_F(JsonFileIoManagerValidationTest, LargeAndExtremeNumbers)
	{
		manager.set_raw_json(valid_file.string(), { "large_int" }, "9223372036854775807");
		manager.set_raw_json(valid_file.string(), { "small_int" }, "-9223372036854775808");
		manager.set_raw_json(valid_file.string(), { "large_float" }, "1.7e308");
		manager.set_raw_json(valid_file.string(), { "small_float" }, "-1.7e308");
		EXPECT_DOUBLE_EQ(manager.get_double(valid_file.string(), { "large_int" }), 9.223372036854776e18);
		EXPECT_DOUBLE_EQ(manager.get_double(valid_file.string(), { "small_int" }), -9.223372036854776e18);
		EXPECT_DOUBLE_EQ(manager.get_double(valid_file.string(), { "large_float" }), 1.7e308);
		EXPECT_DOUBLE_EQ(manager.get_double(valid_file.string(), { "small_float" }), -1.7e308);
	}

	TEST_F(JsonFileIoManagerValidationTest, NegativeArrayIndex_ReturnsEmpty)
	{
		manager.set_raw_json(valid_file.string(), { "arr" }, "[1,2,3]");
		EXPECT_TRUE(manager.get_raw_json(valid_file.string(), { "arr", size_t(-1) }).empty());
	}

	TEST_F(JsonFileIoManagerValidationTest, OutOfRangeArrayIndex_ReturnsEmpty)
	{
		manager.set_raw_json(valid_file.string(), { "arr" }, "[1,2,3]");
		EXPECT_TRUE(manager.get_raw_json(valid_file.string(), { "arr", size_t(10) }).empty());
	}

	TEST_F(JsonFileIoManagerValidationTest, ReadOnlyFile_FailsToWrite)
	{
		std::filesystem::path read_only_file =
			std::filesystem::temp_directory_path() / "readonly.json";
		{
			std::ofstream output(read_only_file);
			output << "{ \"a\":1 }";
		}
		std::filesystem::permissions(read_only_file,
			std::filesystem::perms::owner_read,
			std::filesystem::perm_options::replace);
		EXPECT_FALSE(manager.set_raw_json(read_only_file.string(), { "a" }, "2"));
		EXPECT_FALSE(manager.append_string(read_only_file.string(), { "a" }, "text"));
		std::filesystem::remove(read_only_file);
	}

	TEST_F(JsonFileIoManagerValidationTest, MalformedNestedJson_ReturnsFalse)
	{
		std::ofstream output(valid_file);
		output << "{ \"a\": { \"b\": { invalid } } }";
		output.close();
		EXPECT_FALSE(manager.is_valid(valid_file.string()));
	}

	TEST_F(JsonFileIoManagerValidationTest, Traverse_DeepNestedArrayIndex)
	{
		rapidjson::Document doc;
		doc.Parse("{\"x\":{\"y\":[[10,20],[30,40]]}}");
		std::vector<std::variant<std::string, size_t>> path = { "x", "y", size_t(1), size_t(0) };
		rapidjson::Value* val = manager.traverse(doc, path);
		ASSERT_NE(val, nullptr);
		EXPECT_EQ(val->GetInt(), 30);
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendRawJson_EmptyArray)
	{
		manager.set_raw_json(valid_file.string(), { "empty_array" }, "[]");
		EXPECT_TRUE(manager.append_raw_json(valid_file.string(), { "empty_array" }, "1"));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "empty_array" }), "1");
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendRawJson_DeepNestedArray)
	{
		manager.set_raw_json(valid_file.string(),
			{ "level1", "level2", "nested_array" },
			"[[1,2],[3,4]]"
		);
		EXPECT_TRUE(manager.append_raw_json(valid_file.string(),
			{ "level1", "level2", "nested_array", size_t(1) },
			"5"
		));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(),
			{ "level1", "level2", "nested_array", size_t(1) }),
			"5"
		);
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendString_ToArrayElement_WithSpecialCharacters)
	{
		manager.set_raw_json(valid_file.string(),
			{ "unicode_array" },
			"[\"α\",\"β\"]"
		);
		EXPECT_TRUE(manager.append_string(valid_file.string(),
			{ "unicode_array", size_t(0) },
			"üñîçødë"
		));
		EXPECT_EQ(manager.get_string(valid_file.string(),
			{ "unicode_array", size_t(0) }),
			"üñîçødë"
		);
	}

	TEST_F(JsonFileIoManagerValidationTest, LargeJsonFile_SetAndGet)
	{
		std::string large_json = "{ \"numbers\": [";
		for (int i = 0; i < 1000; ++i)
		{
			large_json += std::to_string(i);
			if (i != 999)
				large_json += ",";
		}
		large_json += "] }";
		std::ofstream output(valid_file);
		output << large_json;
		output.close();
		EXPECT_TRUE(manager.is_valid(valid_file.string()));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "numbers", size_t(0) }), "0");
		EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "numbers", size_t(999) }), "999");
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendRawJson_MultiLevelEmptyArrays)
	{
		manager.set_raw_json(valid_file.string(),
			{ "level1", "level2", "empty_array" },
			"[]"
		);
		EXPECT_TRUE(manager.append_raw_json(valid_file.string(),
			{ "level1", "level2", "empty_array" },
			"10"
		));
		EXPECT_EQ(manager.get_raw_json(valid_file.string(),
			{ "level1", "level2", "empty_array" }),
			"10"
		);
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendRawJson_ArrayElementOutOfRangeReturnsTrue)
	{
		manager.set_raw_json(valid_file.string(), { "arr" }, "[1,2,3]");
		EXPECT_TRUE(manager.append_raw_json(valid_file.string(), { "arr", size_t(10) }, "5"));
	}

	TEST_F(JsonFileIoManagerValidationTest, AppendString_ArrayElementOutOfRangeReturnsFalse)
	{
		manager.set_raw_json(valid_file.string(), { "arr" }, "[\"a\",\"b\"]");
		EXPECT_TRUE(manager.append_string(valid_file.string(), { "arr", size_t(5) }, "c"));
	}

	TEST_F(JsonFileIoManagerValidationTest, ConcurrentSetRawJson_WritesCorrectly)
	{
		std::vector<std::thread> threads;
		manager.append_string(valid_file.string(), { "key" }, "val");

		for (int i = 0; i < 10; ++i)
		{
			threads.emplace_back([this, i]()
				{
					manager.set_raw_json(valid_file.string(), { "key" }, "val");
				});
		}
		for (auto& t : threads)
			t.join();

		for (int i = 0; i < 10; ++i)
		{
			EXPECT_EQ(manager.get_raw_json(valid_file.string(), { "key" }), "\"val\"");
		}
	}

	TEST_F(JsonFileIoManagerValidationTest, ConcurrentSetString_WritesCorrectly)
	{
		std::vector<std::thread> threads;
		manager.set_string(valid_file.string(), { "string_key" }, "val");

		for (int i = 0; i < 10; ++i)
		{
			threads.emplace_back([this, i]()
				{
					manager.set_string(valid_file.string(), { "string_key" }, "val");
				});
		}
		for (auto& t : threads)
			t.join();

		for (int i = 0; i < 10; ++i)
		{
			EXPECT_EQ(manager.get_string(valid_file.string(), { "string_key" }), "val");
		}
	}

	TEST_F(JsonFileIoManagerValidationTest, ConcurrentAppendRawJson_AppendsCorrectly)
	{
		manager.set_raw_json(valid_file.string(), { "arr" }, "[]");
		std::vector<std::thread> threads;
		for (int i = 0; i < 10; ++i)
		{
			threads.emplace_back([this, i]()
				{
					manager.append_raw_json(valid_file.string(), { "arr" }, std::to_string(i));
				});
		}
		for (auto& t : threads)
			t.join();
	}

	TEST_F(JsonFileIoManagerValidationTest, ConcurrentAppendString_AppendsCorrectly)
	{
		manager.set_raw_json(valid_file.string(), { "arr" }, "[]");
		std::vector<std::thread> threads;
		for (int i = 0; i < 10; ++i)
		{
			threads.emplace_back([this, i]()
				{
					manager.append_string(valid_file.string(), { "arr" }, "str" + std::to_string(i));
				});
		}
		for (auto& t : threads)
			t.join();
	}

	TEST_F(JsonFileIoManagerValidationTest, ConcurrentRemoveValue_RemovesCorrectly)
	{
		manager.set_raw_json(valid_file.string(), { "remove_key" }, "[]");
		for (int i = 0; i < 10; ++i)
		{
			manager.append_raw_json(valid_file.string(), { "remove_key" }, std::to_string(i));
		}

		std::vector<std::thread> threads;
		for (int i = 0; i < 10; ++i)
		{
			threads.emplace_back([this, i]()
				{
					manager.remove_value(valid_file.string(), { "remove_key", std::to_string(i) });
				});
		}
		for (auto& t : threads)
			t.join();

		for (int i = 0; i < 10; ++i)
		{
			EXPECT_TRUE(manager.get_raw_json(valid_file.string(), { "remove_key", std::to_string(i) }).empty());
		}
	}

	TEST_F(JsonFileIoManagerValidationTest, ConcurrentMixedOperations)
	{
		std::vector<std::thread> threads;
		for (int i = 0; i < 5; ++i)
		{
			threads.emplace_back([this, i]()
				{
					manager.set_raw_json(valid_file.string(), { "mix", std::to_string(i) }, std::to_string(i));
					manager.append_raw_json(valid_file.string(), { "arr" }, std::to_string(i));
				});
			threads.emplace_back([this, i]()
				{
					manager.set_string(valid_file.string(), { "mix_string", std::to_string(i) }, "val" + std::to_string(i));
					manager.remove_value(valid_file.string(), { "mix", std::to_string(i) });
				});
		}
		for (auto& t : threads)
			t.join();
	}
}

#endif
