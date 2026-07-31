#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		XmlFileIoManager \
	)

#include "../includes/xml_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnTrue_When_KeyExists
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		bool
			result =
				manager
					.is_key_found(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_TRUE(result);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnFalse_When_KeyMissing
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"missing"
				};

		bool
			result =
				manager
					.is_key_found(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_FALSE(result);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnRootName_When_FileValid
	)
	{
		std::string
			root_name =
				manager
					.get_root_name(
						temporary_file_path
							.string()
					);

		EXPECT_EQ(
			root_name,
			"root"
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_SetRootName_When_ValidInput
	)
	{
		bool
			result =
				manager
					.set_root_name(
						temporary_file_path
							.string(),
						"new_root"
					);

		EXPECT_TRUE(result);

		std::string
			root_name =
				manager
					.get_root_name(
						temporary_file_path
							.string()
					);

		EXPECT_EQ(
			root_name,
			"new_root"
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnChildren_When_NodeExists
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root"
				};

		auto
			children =
				manager
					.get_children(
						temporary_file_path
							.string(),
						key_path
					);

		ASSERT_EQ(
			children.size(),
			static_cast<size_t>(1)
		);

		EXPECT_EQ(
			children.at(0),
			"child"
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_GetNodeValue_When_ValueExists
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		int
			value =
				manager
					.get_value<int>(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_EQ(
			value,
			10
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_SetNodeValue_When_NodeExists
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		bool
			result =
				manager
					.set_value<int>(
						temporary_file_path
							.string(),
						key_path,
						20
					);

		EXPECT_TRUE(result);

		int
			value =
				manager
					.get_value<int>(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_EQ(
			value,
			20
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_GetAttribute_When_AttributeExists
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		int
			value =
				manager
					.get_attribute<int>(
						temporary_file_path
							.string(),
						key_path,
						"value"
					);

		EXPECT_EQ(
			value,
			5
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_SetAttribute_When_Valid
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		bool
			result =
				manager
					.set_attribute<int>(
						temporary_file_path
							.string(),
						key_path,
						"value",
						50
					);

		EXPECT_TRUE(result);

		int
			value =
				manager
					.get_attribute<int>(
						temporary_file_path
							.string(),
						key_path,
						"value"
					);

		EXPECT_EQ(
			value,
			50
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_RemoveAttribute_When_Exists
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		bool
			result =
				manager
					.remove_attribute(
						temporary_file_path
							.string(),
						key_path,
						"value"
					);

		EXPECT_TRUE(result);

		int
			value =
				manager
					.get_attribute<int>(
						temporary_file_path
							.string(),
						key_path,
						"value"
					);

		EXPECT_EQ(
			value,
			0
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_RemoveValue_When_NodeExists
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		bool
			result =
				manager
					.remove_value(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_TRUE(result);

		bool
			exists =
				manager
					.is_key_found(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_FALSE(exists);
	}

	TEST_P(
		XmlFileIoManagerParameterizedValueTest,
		Should_ReturnExpectedValue_When_GetValueParameterized
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		int
			value =
				manager
					.get_value<int>(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_EQ(
			value,
			10
		);
	}

	INSTANTIATE_TEST_CASE_P(
		XmlFileIoManagerTest,
		XmlFileIoManagerParameterizedValueTest,
		::testing::Values(
			0,
			1,
			2,
			3
		)
	);

	TEST_P(
		XmlFileIoManagerParameterizedAttributeTest,
		Should_ReturnExpectedAttribute_When_GetAttributeParameterized
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		int
			value =
				manager
					.get_attribute<int>(
						temporary_file_path
							.string(),
						key_path,
						"value"
					);

		EXPECT_EQ(
			value,
			5
		);
	}

	INSTANTIATE_TEST_CASE_P(
		XmlFileIoManagerTest,
		XmlFileIoManagerParameterizedAttributeTest,
		::testing::Values(
			0,
			1,
			2
		)
	);

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleAsyncRead_When_FutureUsed
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		auto
			future_value =
				std::async(
					std::launch::async,
					[this, key_path]()
					{
						return
							manager
								.get_value<int>(
									temporary_file_path
										.string(),
									key_path
								);
					}
				);

		int
			result =
				future_value.get();

		EXPECT_EQ(
			result,
			10
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleAsyncWrite_When_FutureUsed
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		auto
			future_write =
				std::async(
					std::launch::async,
					[this, key_path]()
					{
						return
							manager
								.set_value<int>(
									temporary_file_path
										.string(),
									key_path,
									42
								);
					}
				);

		bool
			result =
				future_write.get();

		EXPECT_TRUE(result);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleMultithreadedReads_When_ConcurrentAccess
	)
	{
		std::vector<std::thread>
			threads;

		std::atomic<int>
			success_count =
				0;

		for
		(
			size_t
				index =
					0;
			index <
				static_cast<size_t>(32);
			++index
		)
		{
			threads.emplace_back(
				[this, &success_count]()
				{
					std::vector<std::string>
						key_path =
							{
								"root",
								"child"
							};

					int
						value =
							manager
								.get_value<int>(
									temporary_file_path
										.string(),
									key_path
								);

					if
					(
						value ==
						10
					)
					{
						++success_count;
					}
				}
			);
		}

		for
		(
			auto&
				thread :
				threads
		)
		{
			thread.join();
		}

		EXPECT_EQ(
			success_count.load(),
			static_cast<int>(32)
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleMultithreadedWrites_When_ConcurrentAccess
	)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = true;

		std::vector<std::thread>
			threads;

		std::atomic<int>
			success_count =
				0;

		for
		(
			size_t
				index =
					0;
			index <
				static_cast<size_t>(16);
			++index
		)
		{
			threads.emplace_back(
				[this, &success_count, index]()
				{
					std::vector<std::string>
						key_path =
							{
								"root",
								"child"
							};

					bool
						result =
							manager
								.set_value<int>(
									temporary_file_path
										.string(),
									key_path,
									static_cast<int>(
										index
									)
								);

					if
					(
						result
					)
					{
						++success_count;
					}
				}
			);
		}

		for
		(
			auto&
				thread :
				threads
		)
		{
			thread.join();
		}

		EXPECT_EQ(
			success_count.load(),
			static_cast<int>(16)
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_SustainStressLoad_When_RepeatedOperations
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		for
		(
			size_t
				index =
					0;
			index <
				static_cast<size_t>(100);
			++index
		)
		{
			bool
				write_result =
					manager
						.set_value<int>(
							temporary_file_path
								.string(),
							key_path,
							static_cast<int>(
								index
							)
						);

			EXPECT_TRUE(
				write_result
			);

			int
				value =
					manager
						.get_value<int>(
							temporary_file_path
								.string(),
							key_path
						);

			EXPECT_EQ(
				value,
				static_cast<int>(
					index
				)
			);
		}
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleInvalidPath_When_ExceptionSafetyRequired
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		int
			value =
				manager
					.get_value<int>(
						"",
						key_path
					);

		EXPECT_EQ(
			value,
			0
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleInvalidKeyPath_When_ExceptionSafetyRequired
	)
	{
		std::vector<std::string>
			key_path;

		int
			value =
				manager
					.get_value<int>(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_EQ(
			value,
			0
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_CompleteWithinPerformanceThreshold_When_OperationsRepeated
	)
	{
		auto
			start_time =
				std::chrono
					::steady_clock
					::now();

		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		for
		(
			size_t
				index =
					0;
			index <
				static_cast<size_t>(100);
			++index
		)
		{
			manager
				.get_value<int>(
					temporary_file_path
						.string(),
					key_path
				);
		}

		auto
			end_time =
				std::chrono
					::steady_clock
					::now();

		auto
			duration =
				std::chrono
					::duration_cast
					<
						std::chrono
							::milliseconds
					>
					(
						end_time -
						start_time
					);

		EXPECT_LT(
			duration.count(),
			static_cast<long long>(2000)
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnFalse_When_FileMissing
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		bool
			result =
				manager
					.is_key_found(
						"non_existing_file.xml",
						key_path
					);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleInvalidXml_When_FileCorrupted
	)
	{
		std::ofstream
			file(
				temporary_file_path
					.string(),
				std::ios::trunc
			);

		file
			<<
			"<root><child>";

		file.close();

		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		int
			value =
				manager
					.get_value<int>(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_EQ(
			value,
			0
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnEmptyChildren_When_NodeHasNone
	)
	{
		std::ofstream
			file(
				temporary_file_path.string(),
				std::ios::trunc
			);

		file
			<< "<root>"
			"<child />"
			"</root>";

		file.close();

		std::vector<std::string>
			key_path =
		{
			"root",
			"child"
		};

		auto
			children =
			manager
			.get_children(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_TRUE(
			children.empty()
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnDefault_When_AttributeMissing
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		int
			value =
				manager
					.get_attribute<int>(
						temporary_file_path
							.string(),
						key_path,
						"missing"
					);

		EXPECT_EQ(
			value,
			0
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_NotFail_When_RemoveAttributeMissing
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		bool
			result =
				manager
					.remove_attribute(
						temporary_file_path
							.string(),
						key_path,
						"missing"
					);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_NotFail_When_RemoveValueMissing
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"missing"
				};

		bool
			result =
				manager
					.remove_value(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleSetRootNameEmpty
	)
	{
		bool
			result =
				manager
					.set_root_name(
						temporary_file_path
							.string(),
						""
					);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_GetStringValue
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		std::string
			value =
				manager
					.get_value<std::string>(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_EQ(
			value,
			"10"
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_GetDoubleValue
	)
	{
		std::vector<std::string>
			key_path =
				{
					"root",
					"child"
				};

		double
			value =
				manager
					.get_value<double>(
						temporary_file_path
							.string(),
						key_path
					);

		EXPECT_DOUBLE_EQ(
			value,
			10.0
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_GetBoolValue
	)
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
			"<child>1</child>"
			"</root>";

		file.close();

		std::vector<std::string>
			key_path =
		{
			"root",
			"child"
		};

		bool
			value =
			manager
			.get_value<bool>(
				temporary_file_path
				.string(),
				key_path
			);

		EXPECT_TRUE(
			value
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleConcurrentReadWriteMixed
	)
	{
		manager
			.configurations
			.is_feature_thread_safety_handling_enabled =
				true;

		std::atomic<int>
			read_success =
				0;

		std::vector<std::thread>
			threads;

		for
		(
			size_t
				index =
					0;
			index <
				static_cast<size_t>(16);
			++index
		)
		{
			threads.emplace_back(
				[this, &read_success, index]()
				{
					std::vector<std::string>
						key_path =
							{
								"root",
								"child"
							};

					manager
						.set_value<int>(
							temporary_file_path
								.string(),
							key_path,
							static_cast<int>(
								index
							)
						);

					int
						value =
							manager
								.get_value<int>(
									temporary_file_path
										.string(),
									key_path
								);

					if
					(
						value >=
						0
					)
					{
						++read_success;
					}
				}
			);
		}

		for
		(
			auto&
				thread :
				threads
		)
		{
			thread
				.join();
		}

		EXPECT_EQ(
			read_success
				.load(),
			static_cast<int>(
				16
			)
		);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleNestedChildrenCorrectly
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);
		file << "<root><child><grandchild>1</grandchild><grandchild>2</grandchild></child></root>";
		file.close();

		std::vector<std::string> key_path = { "root", "child" };
		auto children = manager.get_children(temporary_file_path.string(), key_path);

		ASSERT_EQ(children.size(), 2);
		EXPECT_EQ(children.at(0), "grandchild");
		EXPECT_EQ(children.at(1), "grandchild");
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleEmptyFile
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);
		file << "";
		file.close();

		std::vector<std::string> key_path = { "root", "child" };
		int value = manager.get_value<int>(temporary_file_path.string(), key_path);
		EXPECT_EQ(value, 0);

		auto children = manager.get_children(temporary_file_path.string(), key_path);
		EXPECT_TRUE(children.empty());
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleSpecialCharactersInNodeAndAttribute
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);
		file << "<root><child name=\"&lt;tag&gt;\">&amp;text</child></root>";
		file.close();

		std::vector<std::string> key_path = { "root", "child" };
		std::string value = manager.get_value<std::string>(temporary_file_path.string(), key_path);
		std::string attr = manager.get_attribute<std::string>(temporary_file_path.string(), key_path, "name");

		EXPECT_EQ(value, "&text");
		EXPECT_EQ(attr, "<tag>");
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_OverwriteExistingNodeWithSetValue
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);
		file << "<root><child><grandchild>5</grandchild></child></root>";
		file.close();

		std::vector<std::string> key_path = { "root", "child" };
		bool result = manager.set_value<int>(temporary_file_path.string(), key_path, 42);
		EXPECT_TRUE(result);

		int value = manager.get_value<int>(temporary_file_path.string(), key_path);
		EXPECT_EQ(value, 42);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_HandleConcurrentRemoveAndGet
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);
		file << "<root><child>10</child></root>";
		file.close();

		manager.configurations.is_feature_thread_safety_handling_enabled = true;

		std::atomic<int> success_count = 0;
		std::vector<std::thread> threads;

		for (size_t i = 0; i < 8; ++i)
		{
			threads.emplace_back([this, &success_count]()
			{
				std::vector<std::string> key_path = { "root", "child" };
				manager.remove_value(temporary_file_path.string(), key_path);
				int value = manager.get_value<int>(temporary_file_path.string(), key_path);
				if (value == 0) ++success_count;
			});
		}

		for (auto& t : threads) t.join();

		EXPECT_EQ(success_count.load(), 8);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnDefaultValue_When_NodeValueInvalidForType
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);

		file << "<root><child>invalid_int</child></root>";
		file.close();

		std::vector<std::string> key_path = { "root", "child" };

		int value = manager.get_value<int>(temporary_file_path.string(), key_path);

		EXPECT_EQ(value, 0);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnDefaultAttribute_When_AttributeInvalidForType
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);

		file << "<root><child value=\"invalid_int\">10</child></root>";
		file.close();

		std::vector<std::string> key_path = { "root", "child" };

		int value = manager.get_attribute<int>(temporary_file_path.string(), key_path, "value");

		EXPECT_EQ(value, 0);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnDefaultDouble_When_NodeValueInvalidForType
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);
		file << "<root><child>invalid_double</child></root>";
		file.close();

		std::vector<std::string> key_path = { "root", "child" };

		double value = manager.get_value<double>(temporary_file_path.string(), key_path);

		EXPECT_DOUBLE_EQ(value, 0.0);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnDefaultBool_When_NodeValueInvalidForType
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);
		file << "<root><child>invalid_bool</child></root>";
		file.close();

		std::vector<std::string> key_path = { "root", "child" };

		bool value = manager.get_value<bool>(temporary_file_path.string(), key_path);

		EXPECT_FALSE(value);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnDefaultDoubleAttribute_When_AttributeInvalidForType
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);
		file << "<root><child value=\"invalid_double\">10</child></root>";
		file.close();

		std::vector<std::string> key_path = { "root", "child" };

		double value = manager.get_attribute<double>(temporary_file_path.string(), key_path, "value");

		EXPECT_DOUBLE_EQ(value, 0.0);
	}

	TEST_F(
		XmlFileIoManagerTest,
		Should_ReturnDefaultBoolAttribute_When_AttributeInvalidForType
	)
	{
		std::ofstream file(temporary_file_path.string(), std::ios::trunc);
		file << "<root><child value=\"invalid_bool\">10</child></root>";
		file.close();

		std::vector<std::string> key_path = { "root", "child" };

		bool value = manager.get_attribute<bool>(temporary_file_path.string(), key_path, "value");

		EXPECT_FALSE(value);
	}
}

#endif
