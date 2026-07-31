#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		YamlFileIoManager \
	)

#include "../includes/yaml_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		YamlFileIoManagerTest,
		Should_LoadYaml_ExpectValidNode_WhenFileExists
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		YAML::Node result =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		EXPECT_TRUE(static_cast<bool>(result));
		EXPECT_EQ(
			result["root"]["string_value"].as<std::string>(),
			"value"
		);

		auto elapsed_time =
			std::chrono::steady_clock::now() - start_time;

		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				elapsed_time
			).count(),
			2
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_LoadYaml_ExpectInvalidNode_WhenFileDoesNotExist
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		YAML::Node result =
			yaml_file_io_manager.load(
				"invalid_file.yaml"
			);

		EXPECT_FALSE(static_cast<bool>(result));

		auto elapsed_time =
			std::chrono::steady_clock::now() - start_time;

		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				elapsed_time
			).count(),
			2
		);
	}

	INSTANTIATE_TEST_CASE_P(
		YamlFileIoManagerInvalidPaths,
		YamlFileIoManagerParameterizedPathTest,
		testing::Values(
			"",
			"missing.yaml",
			":::invalid:::"
		)
	);

	TEST_F(
		YamlFileIoManagerTest,
		Should_IsValid_ExpectTrue_WhenYamlFileValid
	)
	{
		bool result =
			yaml_file_io_manager.is_valid(
				temporary_file_path.string()
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_Traverse_ExpectNestedNode_WhenKeyPathValid
	)
	{
		YAML::Node root_node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"object_value",
			"nested_key"
		};

		YAML::Node result =
			yaml_file_io_manager.traverse_tree(
				root_node,
				key_path
			);

		EXPECT_EQ(
			result.as<std::string>(),
			"nested_value"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_Traverse_ExpectSequenceNode_WhenIndexPathValid
	)
	{
		YAML::Node root_node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value",
			static_cast<size_t>(1)
		};

		YAML::Node result =
			yaml_file_io_manager.traverse_tree(
				root_node,
				key_path
			);

		EXPECT_EQ(
			result.as<std::string>(),
			"second"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_Traverse_ExpectInvalidNode_WhenKeyPathInvalid
	)
	{
		YAML::Node root_node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"invalid"
		};

		YAML::Node result =
			yaml_file_io_manager.traverse_tree(
				root_node,
				key_path
			);

		EXPECT_FALSE(static_cast<bool>(result));
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_Traverse_ExpectInvalidNode_WhenKeyPathEmpty
	)
	{
		YAML::Node root_node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		std::vector<std::variant<std::string, size_t>> key_path;

		YAML::Node result =
			yaml_file_io_manager.traverse_tree(
				root_node,
				key_path
			);

		EXPECT_FALSE(static_cast<bool>(result));
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetString_ExpectCorrectValue_WhenKeyPathValid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		std::string result =
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_EQ(result, "value");
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetDouble_ExpectCorrectValue_WhenKeyPathValid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"double_value"
		};

		double result =
			yaml_file_io_manager.get_double(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_DOUBLE_EQ(result, 10.5);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetBoolean_ExpectCorrectValue_WhenKeyPathValid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"boolean_value"
		};

		bool result =
			yaml_file_io_manager.get_boolean(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetNull_ExpectNullptr_WhenCalled
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root"
		};

		std::nullptr_t result =
			yaml_file_io_manager.get_null(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_EQ(result, nullptr);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetString_ExpectUpdatedValue_WhenKeyPathValid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		bool result =
			yaml_file_io_manager.set_string(
				temporary_file_path.string(),
				key_path,
				"updated"
			);

		EXPECT_TRUE(result);

		std::string updated_value =
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_EQ(updated_value, "updated");
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetRawYaml_ExpectUpdatedNode_WhenYamlValid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"object_value"
		};

		bool result =
			yaml_file_io_manager.set_raw_yaml(
				temporary_file_path.string(),
				key_path,
				"new_key: new_value"
			);

		EXPECT_TRUE(result);

		std::vector<std::variant<std::string, size_t>> nested_path =
		{
			"root",
			"object_value",
			"new_key"
		};

		EXPECT_EQ(
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				nested_path
			),
			"new_value"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_AppendString_ExpectAdditionalSequenceItem_WhenValid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value"
		};

		bool result =
			yaml_file_io_manager.append_string(
				temporary_file_path.string(),
				key_path,
				"third"
			);

		EXPECT_TRUE(result);

		std::vector<std::variant<std::string, size_t>> verify_path =
		{
			"root",
			"list_value",
			static_cast<size_t>(2)
		};

		EXPECT_EQ(
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				verify_path
			),
			"third"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_RemoveValue_ExpectMissingNode_WhenKeyRemoved
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		bool result =
			yaml_file_io_manager.remove_value(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_TRUE(result);

		EXPECT_FALSE(
			yaml_file_io_manager.is_key_path_valid(
				temporary_file_path.string(),
				key_path
			)
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SaveYaml_ExpectPersistedContent_WhenNodeValid
	)
	{
		YAML::Node node;

		node["saved"] = "content";

		bool result =
			yaml_file_io_manager.save(
				temporary_file_path.string(),
				node
			);

		EXPECT_TRUE(result);

		YAML::Node loaded_node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		EXPECT_EQ(
			loaded_node["saved"].as<std::string>(),
			"content"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandleAsyncOperations_ExpectSuccessfulResults_WhenConcurrent
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		auto future_result =
			std::async(
				std::launch::async,
				[this, key_path]()
				{
					return
						yaml_file_io_manager.get_string(
							temporary_file_path.string(),
							key_path
						);
				}
			);

		EXPECT_EQ(
			future_result.get(),
			"value"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandlePromiseFuture_ExpectCompletion_WhenAsyncWritePerformed
	)
	{
		std::promise<bool> completion_promise;

		std::future<bool> completion_future =
			completion_promise.get_future();

		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		std::thread worker_thread(
			[this, &completion_promise, key_path]()
			{
				bool result =
					yaml_file_io_manager.set_string(
						temporary_file_path.string(),
						key_path,
						"thread_value"
					);

				completion_promise.set_value(result);
			}
		);

		worker_thread.join();

		EXPECT_TRUE(completion_future.get());
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandleMultithreading_ExpectConsistentReads_WhenConcurrent
	)
	{
		std::atomic<size_t> success_count = 0;

		std::mutex synchronization_mutex;

		std::condition_variable synchronization_condition_variable;

		bool ready = false;

		std::vector<std::thread> worker_threads;

		for (size_t index = 0; index < 8; ++index)
		{
			worker_threads.emplace_back(
				[this,
				 &success_count,
				 &synchronization_mutex,
				 &synchronization_condition_variable,
				 &ready]()
				{
					{
						std::unique_lock<std::mutex> lock(
							synchronization_mutex
						);

						synchronization_condition_variable.wait(
							lock,
							[&ready]()
							{
								return ready;
							}
						);
					}

					std::vector<
						std::variant<std::string, size_t>
					> key_path =
					{
						"root",
						"string_value"
					};

					std::string result =
						yaml_file_io_manager.get_string(
							temporary_file_path.string(),
							key_path
						);

					if (result == "value")
					{
						++success_count;
					}
				}
			);
		}

		{
			std::lock_guard<std::mutex> lock(
				synchronization_mutex
			);

			ready = true;
		}

		synchronization_condition_variable.notify_all();

		for (auto& worker_thread : worker_threads)
		{
			worker_thread.join();
		}

		EXPECT_EQ(success_count.load(), 8);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandleStressTesting_ExpectStableBehavior_WhenRepeated
	)
	{
		for (size_t index = 0; index < 1000; ++index)
		{
			std::vector<std::variant<std::string, size_t>> key_path =
			{
				"root",
				"string_value"
			};

			std::string result =
				yaml_file_io_manager.get_string(
					temporary_file_path.string(),
					key_path
				);

			EXPECT_EQ(result, "value");
		}
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandleExceptionSafety_ExpectNoThrow_WhenOperationsFail
	)
	{
		std::vector<std::variant<std::string, size_t>> empty_key_path;

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.traverse_tree(
					YAML::Node(),
					empty_key_path
				);
			}
		);

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.load("");
			}
		);

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.save(
					"",
					YAML::Node()
				);
			}
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandleLargeYaml_ExpectSuccessfulTraversal_WhenDeepStructure
	)
	{
		YAML::Node large_node;

		for (size_t index = 0; index < 100; ++index)
		{
			large_node["root"][std::to_string(index)] =
				std::to_string(index);
		}

		EXPECT_TRUE(
			yaml_file_io_manager.save(
				temporary_file_path.string(),
				large_node
			)
		);

		for (size_t index = 0; index < 100; ++index)
		{
			std::vector<std::variant<std::string, size_t>> key_path =
			{
				"root",
				std::to_string(index)
			};

			EXPECT_EQ(
				yaml_file_io_manager.get_string(
					temporary_file_path.string(),
					key_path
				),
				std::to_string(index)
			);
		}
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_IsKeyPathValid_ExpectFalse_WhenKeyMissing
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"missing"
		};

		EXPECT_FALSE(
			yaml_file_io_manager.is_key_path_valid(
				temporary_file_path.string(),
				key_path
			)
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetRawYaml_ExpectSerializedYaml_WhenKeyValid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"object_value"
		};

		std::string result =
			yaml_file_io_manager.get_raw_yaml(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_NE(
			result.find("nested_key"),
			std::string::npos
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_RemoveValue_ExpectSequenceReduced_WhenIndexRemoved
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value",
			static_cast<size_t>(0)
		};

		EXPECT_TRUE(
			yaml_file_io_manager.remove_value(
				temporary_file_path.string(),
				key_path
			)
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetDouble_ExpectNoThrow_WhenStringConversionInvalid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		EXPECT_THROW(
			{
				yaml_file_io_manager.get_double(
					temporary_file_path.string(),
					key_path
				);
			},
			std::exception
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetBoolean_ExpectNoThrow_WhenObjectConversionInvalid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"object_value"
		};

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.get_boolean(
					temporary_file_path.string(),
					key_path
				);
			}
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetString_ExpectNoThrow_WhenSequenceConversionInvalid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value"
		};

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.get_string(
					temporary_file_path.string(),
					key_path
				);
			}
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_LoadYaml_ExpectNoThrow_WhenYamlMalformed
	)
	{
		std::ofstream output_file(
			temporary_file_path.string()
		);

		output_file
			<< "root:\n"
			<< "  invalid: [\n";

		output_file.close();

		EXPECT_THROW(
			{
				yaml_file_io_manager.load(
					temporary_file_path.string()
				);
			},
			std::exception
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetRawYaml_ExpectNoThrow_WhenYamlMalformed
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"object_value"
		};

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.set_raw_yaml(
					temporary_file_path.string(),
					key_path,
					"["
				);
			}
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_AppendRawYaml_ExpectNoThrow_WhenYamlMalformed
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value"
		};

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.append_raw_yaml(
					temporary_file_path.string(),
					key_path,
					"["
				);
			}
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_AppendString_ExpectNoThrow_WhenKeyPathEmpty
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path;

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.append_string(
					temporary_file_path.string(),
					key_path,
					"value"
				);
			}
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_Traverse_ExpectInvalidNode_WhenSequenceIndexOutOfRange
	)
	{
		YAML::Node root_node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value",
			static_cast<size_t>(999999)
		};

		YAML::Node result =
			yaml_file_io_manager.traverse_tree(
				root_node,
				key_path
			);

		EXPECT_FALSE(static_cast<bool>(result));
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SaveYaml_ExpectFalseOrNoThrow_WhenPathInvalid
	)
	{
		YAML::Node node;

		node["value"] = "test";

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.save(
					"",
					node
				);
			}
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandleConcurrentWrites_ExpectStableState_WhenParallel
	)
	{
		std::atomic<size_t> success_count = 0;

		std::vector<std::thread> worker_threads;

		for (size_t index = 0; index < 8; ++index)
		{
			worker_threads.emplace_back(
				[this, &success_count, index]()
				{
					std::vector<
						std::variant<std::string, size_t>
					> key_path =
					{
						"root",
						"string_value"
					};

					bool result =
						yaml_file_io_manager.set_string(
							temporary_file_path.string(),
							key_path,
							std::to_string(index)
						);

					if (result)
					{
						++success_count;
					}
				}
			);
		}

		for (auto& worker_thread : worker_threads)
		{
			worker_thread.join();
		}

		EXPECT_EQ(success_count.load(), 8);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandleStressMutation_ExpectStableBehavior_WhenRepeated
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		for (size_t index = 0; index < 250; ++index)
		{
			EXPECT_TRUE(
				yaml_file_io_manager.set_string(
					temporary_file_path.string(),
					key_path,
					std::to_string(index)
				)
			);

			EXPECT_EQ(
				yaml_file_io_manager.get_string(
					temporary_file_path.string(),
					key_path
				),
				std::to_string(index)
			);
		}
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetRawYaml_ExpectExactYaml_WhenObjectSerialized
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"object_value"
		};

		std::string result =
			yaml_file_io_manager.get_raw_yaml(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_EQ(
			result,
			"nested_key: nested_value"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_Traverse_ExpectInvalidNode_WhenRootNodeNull
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root"
		};

		YAML::Node result =
			yaml_file_io_manager.traverse_tree(
				YAML::Node(),
				key_path
			);

		EXPECT_FALSE(static_cast<bool>(result));
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_AppendString_ExpectNoThrow_WhenNodeScalar
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.append_string(
					temporary_file_path.string(),
					key_path,
					"value"
				);
			}
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_RemoveValue_ExpectNoThrow_WhenIndexInvalid
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value",
			static_cast<size_t>(99999)
		};

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.remove_value(
					temporary_file_path.string(),
					key_path
				);
			}
		);
	}

	TEST_P(
		YamlFileIoManagerParameterizedPathTest,
		Should_IsValid_ExpectNoThrow_WhenFilePathInvalid
	)
	{
		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.is_valid(
					GetParam()
				);
			}
		);
	}

	TEST_P(
		YamlFileIoManagerParameterizedKeyPathTest,
		Should_IsKeyPathValid_ExpectNoThrow_WhenPathInvalid
	)
	{
		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.is_key_path_valid(
					temporary_file_path.string(),
					GetParam()
				);
			}
		);
	}

	INSTANTIATE_TEST_CASE_P(
		YamlFileIoManagerInvalidKeyPaths,
		YamlFileIoManagerParameterizedKeyPathTest,
		testing::Values(
			std::vector<std::variant<std::string, size_t>>
			{
				"missing"
			},
			std::vector<std::variant<std::string, size_t>>
			{
				"root",
				static_cast<size_t>(9999)
			},
			std::vector<std::variant<std::string, size_t>>
			{
				"root",
				"missing"
			}
		)
	);

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandleAsyncFailure_ExpectNoThrow_WhenInvalidPathAsync
	)
	{
		auto future_result =
			std::async(
				std::launch::async,
				[this]()
				{
					return
						yaml_file_io_manager.load(
							"missing.yaml"
						);
				}
			);

		EXPECT_NO_THROW(
			{
				future_result.get();
			}
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandleConcurrentReadWrite_ExpectStableBehavior_WhenParallel
	)
	{
		std::atomic<bool> write_complete = false;

		std::thread writer_thread(
			[this, &write_complete]()
			{
				std::vector<
					std::variant<std::string, size_t>
				> key_path =
				{
					"root",
					"string_value"
				};

				for (size_t index = 0; index < 100; ++index)
				{
					yaml_file_io_manager.set_string(
						temporary_file_path.string(),
						key_path,
						std::to_string(index)
					);
				}

				write_complete.store(true);
			}
		);

		std::thread reader_thread(
			[this, &write_complete]()
			{
				std::vector<
					std::variant<std::string, size_t>
				> key_path =
				{
					"root",
					"string_value"
				};

				while (!write_complete.load())
				{
					EXPECT_NO_THROW(
						{
							yaml_file_io_manager.get_string(
								temporary_file_path.string(),
								key_path
							);
						}
					);
				}
			}
		);

		writer_thread.join();
		reader_thread.join();

		EXPECT_TRUE(write_complete.load());
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_HandleEmptyYamlFile_ExpectNoThrow_WhenLoaded
	)
	{
		std::ofstream output_file(
			temporary_file_path.string()
		);

		output_file.close();

		EXPECT_NO_THROW(
			{
				yaml_file_io_manager.load(
					temporary_file_path.string()
				);
			}
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetRawYaml_ExpectTypeOverwrite_WhenScalarReplaced
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		EXPECT_TRUE(
			yaml_file_io_manager.set_raw_yaml(
				temporary_file_path.string(),
				key_path,
				"nested:\n  value: test"
			)
		);

		std::vector<std::variant<std::string, size_t>> nested_path =
		{
			"root",
			"string_value",
			"nested",
			"value"
		};

		EXPECT_EQ(
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				nested_path
			),
			"test"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_ValidateConfigurationDefaults_ExpectEmptyFilePath_WhenConstructed
	)
	{
		YamlFileIoManagerConfigurations configurations;

		EXPECT_TRUE(
			configurations.file_path.empty()
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetRawYaml_ExpectOverwrite_WhenTargetIsScalar
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		bool result =
			yaml_file_io_manager.set_raw_yaml(
				temporary_file_path.string(),
				key_path,
				"new_value"
			);

		EXPECT_TRUE(result);

		EXPECT_EQ(
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				key_path
			),
			"new_value"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetRawYaml_ExpectEmptyValue_WhenIntermediateMissing
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"new_object",
			"inner_key"
		};

		bool result =
			yaml_file_io_manager.set_raw_yaml(
				temporary_file_path.string(),
				key_path,
				"value"
			);

		EXPECT_TRUE(result);

		EXPECT_EQ(
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				key_path
			),
			""
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetRawYaml_ExpectSequenceReplacement_WhenTypeMismatchOccurs
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		bool result =
			yaml_file_io_manager.set_raw_yaml(
				temporary_file_path.string(),
				key_path,
				"[a, b, c]"
			);

		EXPECT_TRUE(result);

		auto node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		EXPECT_TRUE(node["root"]["string_value"].IsSequence());
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetString_ExpectCreatePath_WhenIntermediateMapMissing
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"created_map",
			"value"
		};

		bool result =
			yaml_file_io_manager.set_string(
				temporary_file_path.string(),
				key_path,
				"123"
			);

		EXPECT_TRUE(result);

		EXPECT_EQ(
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				key_path
			),
			"123"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_AppendString_ExpectFailure_WhenTargetIsNotSequence
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		bool result =
			yaml_file_io_manager.append_string(
				temporary_file_path.string(),
				key_path,
				"x"
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_AppendString_ExpectSuccess_WhenSequenceExists
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value"
		};

		bool result =
			yaml_file_io_manager.append_string(
				temporary_file_path.string(),
				key_path,
				"third"
			);

		EXPECT_TRUE(result);

		std::vector<std::variant<std::string, size_t>> verify_path =
		{
			"root",
			"list_value",
			static_cast<size_t>(2)
		};

		EXPECT_EQ(
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				verify_path
			),
			"third"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_RemoveValue_ExpectFailure_WhenRootLoadFails
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		std::ofstream bad_file(temporary_file_path.string(), std::ios::trunc);
		bad_file << "::::invalid_yaml";
		bad_file << "::::invalid_yaml";
		bad_file << "::::invalid_yaml";
		bad_file.close();

		bool result =
			yaml_file_io_manager.remove_value(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_RemoveValue_ExpectFalse_WhenPathEmptyAfterTraversal
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path;

		bool result =
			yaml_file_io_manager.remove_value(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetString_ExpectEmpty_WhenNodeNotScalar
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"object_value"
		};

		std::string result =
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_EQ(result, "");
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetDouble_ExpectZero_WhenNodeMissing
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"missing_double"
		};

		double result =
			yaml_file_io_manager.get_double(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_DOUBLE_EQ(result, 0.0);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetBoolean_ExpectFalse_WhenNodeMissing
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"missing_bool"
		};

		bool result =
			yaml_file_io_manager.get_boolean(
				temporary_file_path.string(),
				key_path
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_ResolveOrCreate_ExpectSequenceGrowth_WhenIndexOutOfRange
	)
	{
		auto node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"auto_seq",
			static_cast<size_t>(5)
		};

		auto resolved =
			yaml_file_io_manager.resolve_or_create(
				node,
				key_path
			);

		EXPECT_TRUE(static_cast<bool>(resolved));
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetRawYaml_ExpectPersistenceIntegrity_WhenReloadedFromDisk
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		EXPECT_TRUE(
			yaml_file_io_manager.set_raw_yaml(
				temporary_file_path.string(),
				key_path,
				"persisted_value"
			)
		);

		YAML::Node reloaded =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		EXPECT_EQ(
			reloaded["root"]["string_value"].as<std::string>(),
			"persisted_value"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetString_ExpectStructureIntegrity_WhenSiblingNodesRemainUnaffected
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		yaml_file_io_manager.set_string(
			temporary_file_path.string(),
			key_path,
			"updated"
		);

		EXPECT_EQ(
			yaml_file_io_manager.get_double(
				temporary_file_path.string(),
				{ "root", "double_value" }
			),
			10.5
		);

		EXPECT_TRUE(
			yaml_file_io_manager.get_boolean(
				temporary_file_path.string(),
				{ "root", "boolean_value" }
			)
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetRawYaml_ExpectFallbackNode_WhenInvalidYamlProvided
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"fallback_test"
		};

		EXPECT_TRUE(
			yaml_file_io_manager.set_raw_yaml(
				temporary_file_path.string(),
				key_path,
				""
			)
		);

		std::string result =
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				{ "root", "fallback_test" }
			);

		EXPECT_EQ(result, "");
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_AppendString_ExpectPersistence_WhenReloadedFromDisk
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value"
		};

		EXPECT_TRUE(
			yaml_file_io_manager.append_string(
				temporary_file_path.string(),
				key_path,
				"third"
			)
		);

		YAML::Node reloaded =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		EXPECT_EQ(
			reloaded["root"]["list_value"][2].as<std::string>(),
			"third"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_AppendString_ExpectNoStructuralCorruption_WhenMultipleAppendsExecuted
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value"
		};

		for (size_t i = 0; i < 5; ++i)
		{
			EXPECT_TRUE(
				yaml_file_io_manager.append_string(
					temporary_file_path.string(),
					key_path,
					std::to_string(i)
				)
			);
		}

		YAML::Node node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		EXPECT_EQ(node["root"]["list_value"].size(), 7);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_RemoveValue_ExpectParentStructureIntact_WhenLeafRemoved
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		EXPECT_TRUE(
			yaml_file_io_manager.remove_value(
				temporary_file_path.string(),
				key_path
			)
		);

		YAML::Node node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		EXPECT_TRUE(node["root"].IsMap());
		EXPECT_FALSE(node["root"]["string_value"]);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_RemoveValue_ExpectSequenceIndexShift_WhenMiddleElementRemoved
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"list_value",
			static_cast<size_t>(0)
		};

		EXPECT_TRUE(
			yaml_file_io_manager.remove_value(
				temporary_file_path.string(),
				key_path
			)
		);

		YAML::Node node =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		EXPECT_EQ(node["root"]["list_value"][0].as<std::string>(), "second");
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_ResolveOrCreate_ExpectMapPromotion_WhenMissingIntermediateNodes
	)
	{
		YAML::Node root =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"dynamic_map",
			"inner",
			"value"
		};

		auto result =
			yaml_file_io_manager.resolve_or_create(
				root,
				key_path
			);

		EXPECT_TRUE(result.IsDefined());
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_ResolveOrCreate_ExpectSequenceExpansion_WhenIndexExceedsSize
	)
	{
		YAML::Node root =
			yaml_file_io_manager.load(
				temporary_file_path.string()
			);

		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"dynamic_seq",
			static_cast<size_t>(5)
		};

		auto result =
			yaml_file_io_manager.resolve_or_create(
				root,
				key_path
			);

		EXPECT_TRUE(result.IsDefined());
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetString_ExpectEmpty_WhenTypeMismatchOccurs
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"object_value"
		};

		EXPECT_EQ(
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				key_path
			),
			""
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetDouble_ExpectZero_WhenTypeMismatchOccurs
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		EXPECT_THROW(
			yaml_file_io_manager.get_double(
				temporary_file_path.string(),
				key_path
			),
			std::exception
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_GetBoolean_ExpectFalse_WhenTypeMismatchOccurs
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		EXPECT_THROW(
			yaml_file_io_manager.get_boolean(
				temporary_file_path.string(),
				key_path
			),
			std::exception
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_SetString_ExpectDeepOverwrite_WhenNestedPathCreatedImplicitly
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"a",
			"b",
			"c"
		};

		EXPECT_TRUE(
			yaml_file_io_manager.set_string(
				temporary_file_path.string(),
				key_path,
				"deep"
			)
		);

		EXPECT_EQ(
			yaml_file_io_manager.get_string(
				temporary_file_path.string(),
				key_path
			),
			"deep"
		);
	}

	TEST_F(
		YamlFileIoManagerTest,
		Should_MaintainConsistency_ExpectStableReadsDuringRepeatedWrites
	)
	{
		std::vector<std::variant<std::string, size_t>> key_path =
		{
			"root",
			"string_value"
		};

		for (size_t i = 0; i < 50; ++i)
		{
			EXPECT_TRUE(
				yaml_file_io_manager.set_string(
					temporary_file_path.string(),
					key_path,
					std::to_string(i)
				)
			);

			std::string value =
				yaml_file_io_manager.get_string(
					temporary_file_path.string(),
					key_path
				);

			EXPECT_EQ(value, std::to_string(i));
		}
	}
}

#endif
