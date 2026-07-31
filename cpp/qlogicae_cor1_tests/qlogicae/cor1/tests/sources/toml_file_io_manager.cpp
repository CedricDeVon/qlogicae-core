#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TomlFileIoManager \
	)

#include "../includes/toml_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TomlFileIoManagerExtendedTest, GetValue_ReturnsCorrectValues)
	{
		EXPECT_EQ(manager.get_value<std::string>(temp_file.string(), { "section", "key1" }), "value1");
		EXPECT_EQ(manager.get_value<int>(temp_file.string(), { "section", "key2" }), 42);
		EXPECT_DOUBLE_EQ(manager.get_value<double>(temp_file.string(), { "section", "key3" }), 3.14);
	}

	TEST_F(TomlFileIoManagerExtendedTest, SetValue_UpdatesExistingKey)
	{
		EXPECT_TRUE(manager.set_value(temp_file.string(), { "section", "key2" }, 99));
		EXPECT_EQ(manager.get_value<int>(temp_file.string(), { "section", "key2" }), 99);
	}

	TEST_F(TomlFileIoManagerExtendedTest, RemoveValue_DeletesKey)
	{
		EXPECT_TRUE(manager.remove_value(temp_file.string(), { "section", "key1" }));
		EXPECT_EQ(manager.get_value<std::string>(temp_file.string(), { "section", "key1" }), "");
		EXPECT_FALSE(manager.is_key_found(temp_file.string(), { "section", "key1" }));
	}

	TEST_F(TomlFileIoManagerExtendedTest, IsKeyFound_HandlesEdgeCases)
	{
		EXPECT_FALSE(manager.is_key_found(temp_file.string(), {}));
		EXPECT_FALSE(manager.is_key_found(temp_file.string(), { "nonexistent" }));
		EXPECT_TRUE(manager.is_key_found(temp_file.string(), { "section", "key3" }));
	}

	TEST_F(TomlFileIoManagerExtendedTest, GetValue_ArrayDoubleAndString)
	{
		std::ofstream ofs(temp_file);
		ofs << R"(
[section]
double_array = [1.1, 2.2, 3.3]
string_array = ["a", "b", "c"]
)";
		ofs.close();

		auto double_arr = manager.get_value<std::vector<double>>(temp_file.string(), { "section", "double_array" });
		EXPECT_EQ(double_arr.size(), 3);
		EXPECT_DOUBLE_EQ(double_arr[0], 1.1);
		EXPECT_DOUBLE_EQ(double_arr[1], 2.2);
		EXPECT_DOUBLE_EQ(double_arr[2], 3.3);

		auto string_arr = manager.get_value<std::vector<std::string>>(temp_file.string(), { "section", "string_array" });
		EXPECT_EQ(string_arr.size(), 3);
		EXPECT_EQ(string_arr[0], "a");
		EXPECT_EQ(string_arr[1], "b");
		EXPECT_EQ(string_arr[2], "c");
	}

	TEST_F(TomlFileIoManagerExtendedTest, SetValue_CreatesNestedTables)
	{
		EXPECT_TRUE(manager.set_value<int>(temp_file.string(), { "section", "nested", "key" }, 123));
		EXPECT_EQ(manager.get_value<int>(temp_file.string(), { "section", "nested", "key" }), 123);
	}

	TEST_F(TomlFileIoManagerExtendedTest, RemoveValue_NonExistentKey)
	{
		EXPECT_FALSE(manager.remove_value(temp_file.string(), { "section", "nonexistent_key" }));
	}

	TEST_F(TomlFileIoManagerExtendedTest, IsKeyFound_WithEdgeCaseFlags)
	{
		manager.configurations.is_feature_edge_case_handling_enabled = true;
		EXPECT_FALSE(manager.is_key_found("", { "section", "key1" }));
		EXPECT_FALSE(manager.is_key_found(temp_file.string(), {}));
	}

	TEST_F(TomlFileIoManagerExtendedTest, ThreadSafetyLocking)
	{
		manager.configurations.is_feature_edge_case_handling_enabled = true;
		EXPECT_TRUE(manager.set_value<int>(temp_file.string(), { "section", "key2" }, 777));
		EXPECT_EQ(manager.get_value<int>(temp_file.string(), { "section", "key2" }), 777);
	}

	TEST_F(TomlFileIoManagerExtendedTest, ErrorHandling_InvalidFile)
	{
		EXPECT_EQ(manager.get_value<int>("nonexistent_file.toml", { "section", "key2" }), 0);
		EXPECT_FALSE(manager.set_value<int>("nonexistent_file.toml", { "section", "key2" }, 1));
		EXPECT_FALSE(manager.remove_value("nonexistent_file.toml", { "section", "key2" }));
	}

	TEST_F(TomlFileIoManagerExtendedTest, GetValue_TypeMismatchReturnsDefault)
	{
		EXPECT_EQ(manager.get_value<int>(temp_file.string(), { "section", "key1" }), 0);
		EXPECT_DOUBLE_EQ(manager.get_value<double>(temp_file.string(), { "section", "key1" }), 0.0);
		EXPECT_EQ(manager.get_value<std::string>(temp_file.string(), { "section", "key2" }), "");
	}

	TEST_F(TomlFileIoManagerExtendedTest, EmptyFileOperations)
	{
		std::ofstream ofs(temp_file);
		ofs.close();

		EXPECT_EQ(manager.get_value<int>(temp_file.string(), { "section", "key1" }), 0);
		EXPECT_FALSE(manager.set_value<int>(temp_file.string(), { "section", "key1" }, 1));
		EXPECT_FALSE(manager.remove_value(temp_file.string(), { "section", "key1" }));
	}

	TEST_F(TomlFileIoManagerExtendedTest, NonexistentSection)
	{
		EXPECT_EQ(manager.get_value<int>(temp_file.string(), { "nonexistent", "key" }), 0);
		EXPECT_FALSE(manager.remove_value(temp_file.string(), { "nonexistent", "key" }));
	}

	TEST_F(TomlFileIoManagerExtendedTest, RemoveNestedArrayAndScalarKeys)
	{
		EXPECT_TRUE(manager.set_value<int>(temp_file.string(), { "section", "nested", "key" }, 100));
		EXPECT_TRUE(manager.set_value<std::vector<int>>(temp_file.string(), { "section", "nested_array" }, { 1, 2, 3 }));

		EXPECT_TRUE(manager.remove_value(temp_file.string(), { "section", "nested", "key" }));
		EXPECT_FALSE(manager.is_key_found(temp_file.string(), { "section", "nested", "key" }));

		EXPECT_TRUE(manager.remove_value(temp_file.string(), { "section", "nested_array" }));
		EXPECT_FALSE(manager.is_key_found(temp_file.string(), { "section", "nested_array" }));
	}

	TEST_F(TomlFileIoManagerExtendedTest, GetValue_WithDefaultForMissingKey)
	{
		EXPECT_EQ(manager.get_value<int>(temp_file.string(), { "section", "missing_key" }), 0);
		EXPECT_EQ(manager.get_value<std::string>(temp_file.string(), { "section", "missing_key" }), "");
		EXPECT_DOUBLE_EQ(manager.get_value<double>(temp_file.string(), { "section", "missing_key" }), 0.0);
	}
}

#endif

/*
	TEST_F(TomlFileIoManagerExtendedTest, DefaultConfigPathOperations)
	{
		manager.configurations.file_path = temp_file.string();

		EXPECT_EQ(manager.get_value<std::string>({ "section", "key1" }), "value1");
		EXPECT_TRUE(manager.set_value<std::string>({ "section", "key1" }, "new_value"));
		EXPECT_EQ(manager.get_value<std::string>({ "section", "key1" }), "new_value");
		EXPECT_TRUE(manager.append_value<int>({ "section", "array_key" }, 5));

		auto arr_value = manager.get_value<std::vector<int>>({ "section", "array_key" });
		EXPECT_EQ(arr_value.back(), 5);

		EXPECT_TRUE(manager.remove_value({ "section", "key2" }));
		EXPECT_FALSE(manager.is_key_found({ "section", "key2" }));
	}

	TEST_F(TomlFileIoManagerExtendedTest, AppendValue_CreatesNewArrayIfNotExist)
	{
		EXPECT_TRUE(manager.append_value<int>(temp_file.string(), { "section", "new_array" }, 10));
		auto arr_value = manager.get_value<std::vector<int>>(temp_file.string(), { "section", "new_array" });
		EXPECT_EQ(arr_value.size(), 1);
		EXPECT_EQ(arr_value[0], 10);
	}

	TEST_F(TomlFileIoManagerExtendedTest,AppendValue_AddsToArray)
	{
		EXPECT_TRUE(manager.append_value(temp_file.string(),{"section","array_key"},4));
		auto arr_value = manager.get_value<std::vector<int>>(temp_file.string(),{"section","array_key"});
		EXPECT_EQ(arr_value.size(),4);
		EXPECT_EQ(arr_value.back(),4);
	}

	TEST_F(TomlFileIoManagerExtendedTest,AppendValue_ArrayDoubleAndString) //
	{
		EXPECT_TRUE(manager.append_value<double>(temp_file.string(),{"section","array_key"},4.5));
		auto arr_double = manager.get_value<std::vector<double>>(temp_file.string(),{"section","array_key"});
		EXPECT_DOUBLE_EQ(arr_double.back(),4.5);

		EXPECT_TRUE(manager.append_value<std::string>(temp_file.string(),{"section","string_array"},"d"));
		auto arr_string = manager.get_value<std::vector<std::string>>(temp_file.string(),{"section","string_array"});
		EXPECT_EQ(arr_string.back(),"d");
	}

	TEST_F(TomlFileIoManagerExtendedTest, AppendValue_TypeMismatchFails) //
	{
		EXPECT_TRUE(manager.append_value<double>(temp_file.string(), { "section", "array_key" }, 4.5));
		EXPECT_TRUE(manager.append_value<std::string>(temp_file.string(), { "section", "array_key" }, "test"));
	}

	TEST_F(TomlFileIoManagerExtendedTest, MixedTypeArrayAppend) //
	{
		EXPECT_TRUE(manager.append_value<std::string>(temp_file.string(), { "section", "array_key" }, "test"));
		EXPECT_TRUE(manager.append_value<double>(temp_file.string(), { "section", "array_key" }, 1.23));
	}

	TEST_F(TomlFileIoManagerExtendedTest, MalformedTomlFileHandling)
	{
		std::ofstream ofs(temp_file);
		ofs << R"(key1 = "value1
[section] key2 = 42)";
		ofs.close();

		EXPECT_EQ(manager.get_value<int>(temp_file.string(), { "section", "key2" }), 0);
		EXPECT_FALSE(manager.set_value<int>(temp_file.string(), { "section", "key2" }, 5));
		EXPECT_FALSE(manager.append_value<int>(temp_file.string(), { "section", "array_key" }, 1));
		EXPECT_FALSE(manager.remove_value(temp_file.string(), { "section", "key2" }));
	}

	TEST_F(TomlFileIoManagerExtendedTest, LargeArrayOperations)
	{
		std::vector<int> large_array(1000, 1);
		EXPECT_TRUE(manager.set_value<std::vector<int>>(temp_file.string(), { "section", "large_array" }, large_array));

		auto read_back = manager.get_value<std::vector<int>>(temp_file.string(), { "section", "large_array" });
		EXPECT_EQ(read_back.size(), 1000);
		EXPECT_EQ(read_back.front(), 1);
		EXPECT_EQ(read_back.back(), 1);

		EXPECT_TRUE(manager.append_value<int>(temp_file.string(), { "section", "large_array" }, 999));
		read_back = manager.get_value<std::vector<int>>(temp_file.string(), { "section", "large_array" });
		EXPECT_EQ(read_back.size(), 1001);
		EXPECT_EQ(read_back.back(), 999);
	}

	TEST_F(TomlFileIoManagerExtendedTest, ConcurrentRemoveAndAppend)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = true;
		std::vector<std::thread> threads;

		for (int i = 0; i < 5; ++i)
		{
			threads.emplace_back([this, i]() {
				manager.append_value<int>(temp_file.string(), { "section", "array_key" }, i);
				manager.remove_value(temp_file.string(), { "section", "key2" });
				});
		}

		for (auto& t : threads) t.join();

		auto arr_value = manager.get_value<std::vector<int>>(temp_file.string(), { "section", "array_key" });
		EXPECT_GE(arr_value.size(), static_cast<size_t>(8));
	}

	TEST_F(TomlFileIoManagerExtendedTest, MultiThreaded_SetGetAppend)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = true;
		std::vector<std::thread> threads;

		for (int i = 0; i < 5; ++i)
		{
			threads.emplace_back([this, i]() {
				manager.set_value<int>(temp_file.string(), { "section", "key2" }, i * 10);
				manager.append_value<int>(temp_file.string(), { "section", "array_key" }, i);
				});
		}

		for (auto& t : threads) t.join();

		auto arr_value = manager.get_value<std::vector<int>>(temp_file.string(), { "section", "array_key" });
		EXPECT_GE(arr_value.size(), static_cast<size_t>(8));
		int key2_val = manager.get_value<int>(temp_file.string(), { "section", "key2" });
		EXPECT_TRUE(key2_val % 10 == 0);
	}

*/
