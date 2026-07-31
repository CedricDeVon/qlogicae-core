#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonTextManager \
	)

#include "../includes/json_text_manager.hpp"

namespace
    QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{    
    TEST_P(
        JsonTextManagerValidationParameterizedTest,
        Should_ReturnExpectedResult_When_ValidatingJsonText
    )
    {
        const JsonValidationParameter parameter = GetParam();

        const bool result =
            manager.is_text_valid(parameter.json_text);

        EXPECT_EQ(
            result,
            parameter.expected_result
        );
    }

    TEST_P(
        JsonTextManagerKeyPathParameterizedTest,
        Should_ReturnExpectedResult_When_ValidatingKeyPath
    )
    {
        const JsonKeyPathParameter parameter = GetParam();

        const bool result =
            manager.is_key_path_valid(
                parameter.json_text,
                parameter.key_path
            );

        EXPECT_EQ(
            result,
            parameter.expected_result
        );
    }

    TEST_P(
        JsonTextManagerStringExtractionParameterizedTest,
        Should_ReturnExpectedString_When_StringPathExists
    )
    {
        const JsonStringExtractionParameter parameter = GetParam();

        const std::string result =
            manager.get_string(
                parameter.json_text,
                parameter.key_path
            );

        EXPECT_EQ(
            result,
            parameter.expected_result
        );
    }

    TEST_P(
        JsonTextManagerDoubleExtractionParameterizedTest,
        Should_ReturnExpectedDouble_When_NumberPathExists
    )
    {
        const JsonDoubleExtractionParameter parameter = GetParam();

        const double result =
            manager.get_double(
                parameter.json_text,
                parameter.key_path
            );

        EXPECT_DOUBLE_EQ(
            result,
            parameter.expected_result
        );
    }

    TEST_P(
        JsonTextManagerBooleanExtractionParameterizedTest,
        Should_ReturnExpectedBoolean_When_BooleanPathExists
    )
    {
        const JsonBooleanExtractionParameter parameter = GetParam();

        const bool result =
            manager.get_boolean(
                parameter.json_text,
                parameter.key_path
            );

        EXPECT_EQ(
            result,
            parameter.expected_result
        );
    }

    TEST_F(
        JsonTextManagerTest,
        Should_ReturnFalse_When_JsonTextEmpty
    )
    {
        const std::string json_text = "";

        const bool result =
            manager.is_text_valid(json_text);

        EXPECT_FALSE(result);
    }

    TEST_F(
        JsonTextManagerTest,
        Should_HandleConcurrentAccess_When_MultipleThreadsInvokeReads
    )
    {
        const std::string json_text =
            R"({"name":"test","value":42})";

        std::atomic<bool> success_flag = true;

        std::vector<std::thread> thread_collection;

        for (size_t index = 0; index < 32; ++index)
        {
            thread_collection.emplace_back(
                [&]()
                {
                    for (size_t iteration = 0;
                        iteration < 1000;
                        ++iteration)
                    {
                        if (!manager.is_text_valid(json_text))
                        {
                            success_flag = false;
                        }
                    }
                }
            );
        }

        for (std::thread& thread_instance : thread_collection)
        {
            thread_instance.join();
        }

        EXPECT_TRUE(success_flag);
    }

    TEST_F(
        JsonTextManagerTest,
        Should_HandleAsyncValidation_When_UsingFuture
    )
    {
        const std::string json_text =
            R"({"name":"async"})";

        std::future<bool> future_result =
            std::async(
                std::launch::async,
                [&]()
                {
                    return manager.is_text_valid(json_text);
                }
            );

        const bool result = future_result.get();

        EXPECT_TRUE(result);
    }

    TEST_F(
        JsonTextManagerTest,
        Should_HandleAsyncExtraction_When_UsingPromise
    )
    {
        const std::string json_text =
            R"({"value":3.14})";

        std::promise<double> promise_value;
        std::future<double> future_value =
            promise_value.get_future();

        std::thread thread_instance(
            [&]()
            {
                const double result =
                    manager.get_double(
                        json_text,
                        { std::string("value") }
                    );

                promise_value.set_value(result);
            }
        );

        const double result = future_value.get();

        thread_instance.join();

        EXPECT_DOUBLE_EQ(
            result,
            3.14
        );
    }

    TEST_F(
        JsonTextManagerTest,
        Should_HandleStressLoad_When_RepeatedJsonParsing
    )
    {
        const std::string json_text =
            R"({"value":123})";

        for (size_t iteration = 0;
            iteration < 100000;
            ++iteration)
        {
            const bool result =
                manager.is_text_valid(json_text);

            if (!result)
            {
                FAIL();
            }
        }

        SUCCEED();
    }

    TEST_F(
        JsonTextManagerTest,
        Should_ReturnEmptyString_When_TypeMismatchForString
    )
    {
        const std::string json_text =
            R"({"value":42})";

        const std::string result =
            manager.get_string(
                json_text,
                { std::string("value") }
            );

        EXPECT_EQ(
            result,
            ""
        );
    }

    TEST_F(
        JsonTextManagerTest,
        Should_ReturnZero_When_TypeMismatchForDouble
    )
    {
        const std::string json_text =
            R"({"value":"string"})";

        const double result =
            manager.get_double(
                json_text,
                { std::string("value") }
            );

        EXPECT_DOUBLE_EQ(
            result,
            0.0
        );
    }

    INSTANTIATE_TEST_CASE_P(
        JsonValidationTests,
        JsonTextManagerValidationParameterizedTest,
        ::testing::Values(
            JsonValidationParameter{
                R"({"a":1})",
                true
            },
            JsonValidationParameter{
                R"({"a":})",
                false
            }
        )
    );

    INSTANTIATE_TEST_CASE_P(
        JsonKeyPathTests,
        JsonTextManagerKeyPathParameterizedTest,
        ::testing::Values(
            JsonKeyPathParameter{
                R"({"a":{"b":1}})",
                { std::string("a"), std::string("b") },
                true
            },
            JsonKeyPathParameter{
                R"({"a":1})",
                { std::string("b") },
                false
            }
        )
    );

    INSTANTIATE_TEST_CASE_P(
        JsonStringExtractionTests,
        JsonTextManagerStringExtractionParameterizedTest,
        ::testing::Values(
            JsonStringExtractionParameter{
                R"({"name":"alpha"})",
                { std::string("name") },
                "alpha"
            }
        )
    );

    INSTANTIATE_TEST_CASE_P(
        JsonDoubleExtractionTests,
        JsonTextManagerDoubleExtractionParameterizedTest,
        ::testing::Values(
            JsonDoubleExtractionParameter{
                R"({"value":5.5})",
                { std::string("value") },
                5.5
            }
        )
    );

    INSTANTIATE_TEST_CASE_P(
        JsonBooleanExtractionTests,
        JsonTextManagerBooleanExtractionParameterizedTest,
        ::testing::Values(
            JsonBooleanExtractionParameter{
                R"({"flag":true})",
                { std::string("flag") },
                true
            }
        )
    );

	TEST_F(
		JsonTextManagerTest,
		Should_ReturnFalse_When_KeyPathEmpty
	)
	{
		const std::string json_text =
			R"({"a":1})";

		const bool result =
			manager.is_key_path_valid(
				json_text,
				{}
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_ReturnFalse_When_JsonInvalidDuringKeyPathValidation
	)
	{
		const std::string json_text =
			R"({"a":})";

		const bool result =
			manager.is_key_path_valid(
				json_text,
				{ std::string("a") }
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_ReturnFalse_When_ArrayIndexOutOfBounds
	)
	{
		const std::string json_text =
			R"({"a":[1,2]})";

		const bool result =
			manager.is_key_path_valid(
				json_text,
				{ std::string("a"), static_cast<size_t>(5) }
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_ReturnFalse_When_ObjectKeyMissing
	)
	{
		const std::string json_text =
			R"({"a":1})";

		const bool result =
			manager.is_key_path_valid(
				json_text,
				{ std::string("missing") }
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_ReturnEmptyString_When_KeyPathInvalid
	)
	{
		const std::string json_text =
			R"({"name":"alpha"})";

		const std::string result =
			manager.get_string(
				json_text,
				{ std::string("missing") }
			);

		EXPECT_EQ(
			result,
			""
		);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_ReturnZero_When_KeyPathInvalidForDouble
	)
	{
		const std::string json_text =
			R"({"value":1.2})";

		const double result =
			manager.get_double(
				json_text,
				{ std::string("missing") }
			);

		EXPECT_DOUBLE_EQ(
			result,
			0.0
		);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_ReturnFalse_When_KeyPathInvalidForBoolean
	)
	{
		const std::string json_text =
			R"({"flag":true})";

		const bool result =
			manager.get_boolean(
				json_text,
				{ std::string("missing") }
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_ReturnCorrectValue_When_ArrayIndexAccessed
	)
	{
		const std::string json_text =
			R"({"values":[10,20,30]})";

		const double result =
			manager.get_double(
				json_text,
				{ std::string("values"), static_cast<size_t>(1) }
			);

		EXPECT_DOUBLE_EQ(
			result,
			20.0
		);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_ReturnFalse_When_JsonInvalidForExtraction
	)
	{
		const std::string json_text =
			R"({"value":})";

		const std::string result =
			manager.get_string(
				json_text,
				{ std::string("value") }
			);

		EXPECT_EQ(
			result,
			""
		);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_HandleDeepNestedKeyPath
	)
	{
		const std::string json_text =
			R"({"a":{"b":{"c":{"d":"value"}}}})";

		const std::string result =
			manager.get_string(
				json_text,
				{
					std::string("a"),
					std::string("b"),
					std::string("c"),
					std::string("d")
				}
			);

		EXPECT_EQ(
			result,
			"value"
		);
	}

	INSTANTIATE_TEST_CASE_P(
		JsonValidationAdditionalTests,
		JsonTextManagerValidationParameterizedTest,
		::testing::Values(
			JsonValidationParameter{
				"[]",
				true
			},
			JsonValidationParameter{
				"{}",
				true
			},
			JsonValidationParameter{
				"invalid",
				false
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonKeyPathAdditionalTests,
		JsonTextManagerKeyPathParameterizedTest,
		::testing::Values(
			JsonKeyPathParameter{
				R"({"a":[{"b":5}]})",
				{ std::string("a"), static_cast<size_t>(0), std::string("b") },
				true
			},
			JsonKeyPathParameter{
				R"({"a":[1,2,3]})",
				{ std::string("a"), static_cast<size_t>(3) },
				false
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonStringExtractionAdditionalTests,
		JsonTextManagerStringExtractionParameterizedTest,
		::testing::Values(
			JsonStringExtractionParameter{
				R"({"a":{"b":"text"}})",
				{ std::string("a"), std::string("b") },
				"text"
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonDoubleExtractionAdditionalTests,
		JsonTextManagerDoubleExtractionParameterizedTest,
		::testing::Values(
			JsonDoubleExtractionParameter{
				R"({"a":{"b":2.5}})",
				{ std::string("a"), std::string("b") },
				2.5
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonBooleanExtractionAdditionalTests,
		JsonTextManagerBooleanExtractionParameterizedTest,
		::testing::Values(
			JsonBooleanExtractionParameter{
				R"({"a":{"b":false}})",
				{ std::string("a"), std::string("b") },
				false
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonValidationExtendedTests,
		JsonTextManagerValidationParameterizedTest,
		::testing::Values(
			JsonValidationParameter{ "true", true },
			JsonValidationParameter{ "false", true },
			JsonValidationParameter{ "null", true },
			JsonValidationParameter{ "123", true },
			JsonValidationParameter{ "\"text\"", true },
			JsonValidationParameter{ "   ", false }
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonKeyPathExtendedTests,
		JsonTextManagerKeyPathParameterizedTest,
		::testing::Values(
			JsonKeyPathParameter{
				R"([{"a":1}])",
				{ static_cast<size_t>(0), std::string("a") },
				true
			},
			JsonKeyPathParameter{
				R"({"a":1})",
				{ std::string("a"), static_cast<size_t>(0) },
				false
			},
			JsonKeyPathParameter{
				R"({"a":[1,2]})",
				{ std::string("a"), std::string("b") },
				false
			},
			JsonKeyPathParameter{
				R"({"a":[[1,2],[3,4]]})",
				{ std::string("a"), static_cast<size_t>(1), static_cast<size_t>(0) },
				true
			},
			JsonKeyPathParameter{
				R"({"a":[{"b":[{"c":1}]}]})",
				{
					std::string("a"),
					static_cast<size_t>(0),
					std::string("b"),
					static_cast<size_t>(0),
					std::string("c")
				},
				true
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonStringExtractionExtendedTests,
		JsonTextManagerStringExtractionParameterizedTest,
		::testing::Values(
			JsonStringExtractionParameter{
				R"({"a":null})",
				{ std::string("a") },
				""
			},
			JsonStringExtractionParameter{
				R"({"a":true})",
				{ std::string("a") },
				""
			},
			JsonStringExtractionParameter{
				R"({"a":[1,2]})",
				{ std::string("a") },
				""
			},
			JsonStringExtractionParameter{
				R"({"a":{"b":1}})",
				{ std::string("a") },
				""
			},
			JsonStringExtractionParameter{
				R"({"测试":"value"})",
				{ std::string("测试") },
				"value"
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonDoubleExtractionExtendedTests,
		JsonTextManagerDoubleExtractionParameterizedTest,
		::testing::Values(
			JsonDoubleExtractionParameter{
				R"({"value":5})",
				{ std::string("value") },
				5.0
			},
			JsonDoubleExtractionParameter{
				R"({"value":true})",
				{ std::string("value") },
				0.0
			},
			JsonDoubleExtractionParameter{
				R"({"value":null})",
				{ std::string("value") },
				0.0
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonBooleanExtractionExtendedTests,
		JsonTextManagerBooleanExtractionParameterizedTest,
		::testing::Values(
			JsonBooleanExtractionParameter{
				R"({"flag":1})",
				{ std::string("flag") },
				false
			},
			JsonBooleanExtractionParameter{
				R"({"flag":"true"})",
				{ std::string("flag") },
				false
			},
			JsonBooleanExtractionParameter{
				R"({"flag":null})",
				{ std::string("flag") },
				false
			},
			JsonBooleanExtractionParameter{
				R"({"flag":[true]})",
				{ std::string("flag") },
				false
			}
		)
	);

	TEST_F(
		JsonTextManagerTest,
		Should_HandleMixedConcurrentReadsAcrossMethods
	)
	{
		const std::string json_text =
			R"({"a":[{"b":[{"c":1}]}],"flag":true,"name":"alpha"})";

		std::atomic<bool> success_flag = true;

		std::vector<std::thread> threads;

		for (size_t index = 0; index < 32; ++index)
		{
			threads.emplace_back(
				[&]()
				{
					for (size_t iteration = 0; iteration < 1000; ++iteration)
					{
						if (!manager.is_text_valid(json_text))
						{
							success_flag = false;
						}

						if (!manager.is_key_path_valid(
								json_text,
								{
									std::string("a"),
									static_cast<size_t>(0),
									std::string("b"),
									static_cast<size_t>(0),
									std::string("c")
								}))
						{
							success_flag = false;
						}

						const std::string name =
							manager.get_string(
								json_text,
								{ std::string("name") });

						if (name != "alpha")
						{
							success_flag = false;
						}

						const bool flag =
							manager.get_boolean(
								json_text,
								{ std::string("flag") });

						if (!flag)
						{
							success_flag = false;
						}

						const double value =
							manager.get_double(
								json_text,
								{
									std::string("a"),
									static_cast<size_t>(0),
									std::string("b"),
									static_cast<size_t>(0),
									std::string("c")
								});

						if (value != 1.0)
						{
							success_flag = false;
						}
					}
				});
		}

		for (std::thread& thread : threads)
		{
			thread.join();
		}

		EXPECT_TRUE(success_flag);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_HandleDeeplyNestedJsonStructure
	)
	{
		const std::string json_text =
			R"({"a":[{"b":[{"c":[{"d":[{"e":42}]}]}]}]})";

		const double result =
			manager.get_double(
				json_text,
				{
					std::string("a"),
					static_cast<size_t>(0),
					std::string("b"),
					static_cast<size_t>(0),
					std::string("c"),
					static_cast<size_t>(0),
					std::string("d"),
					static_cast<size_t>(0),
					std::string("e")
				});

		EXPECT_DOUBLE_EQ(result, 42.0);
	}

	INSTANTIATE_TEST_CASE_P(
		JsonValidationEdgeTests,
		JsonTextManagerValidationParameterizedTest,
		::testing::Values(
			JsonValidationParameter{
				R"({"a":1,})",
				false
			},
			JsonValidationParameter{
				R"({"a":"text})",
				false
			},
			JsonValidationParameter{
				R"({"a":1 2})",
				false
			},
			JsonValidationParameter{
				R"([1,2,3])",
				true
			},
			JsonValidationParameter{
				R"("")",
				true
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonKeyPathRootArrayTests,
		JsonTextManagerKeyPathParameterizedTest,
		::testing::Values(
			JsonKeyPathParameter{
				R"([1,2,3])",
				{ static_cast<size_t>(0) },
				true
			},
			JsonKeyPathParameter{
				R"([1,2,3])",
				{ static_cast<size_t>(2) },
				true
			},
			JsonKeyPathParameter{
				R"([1,2,3])",
				{ static_cast<size_t>(3) },
				false
			},
			JsonKeyPathParameter{
				R"([{"a":5}])",
				{ static_cast<size_t>(0), std::string("a") },
				true
			},
			JsonKeyPathParameter{
				R"([{"a":5}])",
				{ static_cast<size_t>(0), std::string("missing") },
				false
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonKeyPathEmptyStructureTests,
		JsonTextManagerKeyPathParameterizedTest,
		::testing::Values(
			JsonKeyPathParameter{
				R"({})",
				{ std::string("a") },
				false
			},
			JsonKeyPathParameter{
				R"([])",
				{ static_cast<size_t>(0) },
				false
			},
			JsonKeyPathParameter{
				R"({"":5})",
				{ std::string("") },
				true
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonStringExtractionRootTests,
		JsonTextManagerStringExtractionParameterizedTest,
		::testing::Values(
			JsonStringExtractionParameter{
				R"(["root"])",
				{ static_cast<size_t>(0) },
				"root"
			},
			JsonStringExtractionParameter{
				R"([ "a","b","c" ])",
				{ static_cast<size_t>(1) },
				"b"
			},
			JsonStringExtractionParameter{
				R"({"": "emptykey"})",
				{ std::string("") },
				"emptykey"
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonDoubleExtractionRootTests,
		JsonTextManagerDoubleExtractionParameterizedTest,
		::testing::Values(
			JsonDoubleExtractionParameter{
				R"([123])",
				{ static_cast<size_t>(0) },
				123.0
			},
			JsonDoubleExtractionParameter{
				R"([-3.14])",
				{ static_cast<size_t>(0) },
				-3.14
			},
			JsonDoubleExtractionParameter{
				R"([1e6])",
				{ static_cast<size_t>(0) },
				1000000.0
			},
			JsonDoubleExtractionParameter{
				R"([10,20,30])",
				{ static_cast<size_t>(2) },
				30.0
			},
			JsonDoubleExtractionParameter{
				R"({"a":[1,2,3]})",
				{ std::string("a"), static_cast<size_t>(0) },
				1.0
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonBooleanExtractionRootTests,
		JsonTextManagerBooleanExtractionParameterizedTest,
		::testing::Values(
			JsonBooleanExtractionParameter{
				R"(true)",
				{},
				false
			},
			JsonBooleanExtractionParameter{
				R"(false)",
				{},
				false
			},
			JsonBooleanExtractionParameter{
				R"([true,false,true])",
				{ static_cast<size_t>(1) },
				false
			},
			JsonBooleanExtractionParameter{
				R"({"a":[true]})",
				{ std::string("a"), static_cast<size_t>(0) },
				true
			}
		)
	);

	TEST_F(
		JsonTextManagerTest,
		Should_HandleLargeArrayIndexBoundary
	)
	{
		const std::string json_text =
			R"({"values":[1,2,3]})";

		const double last_value =
			manager.get_double(
				json_text,
				{ std::string("values"), static_cast<size_t>(2) });

		const double out_of_bounds =
			manager.get_double(
				json_text,
				{ std::string("values"), static_cast<size_t>(3) });

		EXPECT_DOUBLE_EQ(last_value, 3.0);
		EXPECT_DOUBLE_EQ(out_of_bounds, 0.0);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_HandleNegativeAndScientificNumbers
	)
	{
		const std::string json_text =
			R"({"a":-2.5,"b":1e3})";

		const double a =
			manager.get_double(
				json_text,
				{ std::string("a") });

		const double b =
			manager.get_double(
				json_text,
				{ std::string("b") });

		EXPECT_DOUBLE_EQ(a, -2.5);
		EXPECT_DOUBLE_EQ(b, 1000.0);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_HandleRootArrayExtraction
	)
	{
		const std::string json_text =
			R"([5,10,15])";

		const double value =
			manager.get_double(
				json_text,
				{ static_cast<size_t>(1) });

		EXPECT_DOUBLE_EQ(value, 10.0);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_HandleDeepRecursionLevels
	)
	{
		const std::string json_text =
			R"({"a":{"b":{"c":{"d":{"e":{"f":{"g":{"h":{"i":{"j":99}}}}}}}}}})";

		const double result =
			manager.get_double(
				json_text,
				{
					std::string("a"),
					std::string("b"),
					std::string("c"),
					std::string("d"),
					std::string("e"),
					std::string("f"),
					std::string("g"),
					std::string("h"),
					std::string("i"),
					std::string("j")
				});

		EXPECT_DOUBLE_EQ(result, 99.0);
	}

	TEST_F(
		JsonTextManagerTest,
		Should_HandleEmptyStructures
	)
	{
		const std::string object_json = "{}";
		const std::string array_json = "[]";

		const bool object_path =
			manager.is_key_path_valid(
				object_json,
				{ std::string("a") });

		const bool array_path =
			manager.is_key_path_valid(
				array_json,
				{ static_cast<size_t>(0) });

		EXPECT_FALSE(object_path);
		EXPECT_FALSE(array_path);
	}

	INSTANTIATE_TEST_CASE_P(
		JsonValidationPathologicalTests,
		JsonTextManagerValidationParameterizedTest,
		::testing::Values(
			JsonValidationParameter{
				R"({"a":{"a":{"a":{"a":{"a":{"a":{"a":{"a":{"a":{"a":1}}}}}}}}}})",
				true
			},
			JsonValidationParameter{
				[](){
					std::stringstream ss;
					ss << "[";
					for (size_t i = 0; i < 10000; ++i) { if(i != 0) ss << ","; ss << i; }
					ss << "]";
					return ss.str();
				}(),
				true
			},
			JsonValidationParameter{
				std::string("{\"a\":\"") + char(0xFF) + R"("})",
				true
			},
			JsonValidationParameter{
				R"({"newline":"line\nbreak","quote":"quote\"escape","unicode":"\u1234"})",
				true
			},
			JsonValidationParameter{
				R"({"key":1,"key":2})",
				true
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonKeyPathPathologicalTests,
		JsonTextManagerKeyPathParameterizedTest,
		::testing::Values(
			JsonKeyPathParameter{
				R"({"key":1,"key":2})",
				{ std::string("key") },
				true
			},
			JsonKeyPathParameter{
				R"({"a":{"a":{"a":{"a":{"a":{"a":{"a":{"a":{"a":{"a":1}}}}}}}}}})",
				{ std::string("a"), std::string("a"), std::string("a"),
				  std::string("a"), std::string("a"), std::string("a"),
				  std::string("a"), std::string("a"), std::string("a"), std::string("a") },
				true
			},
			JsonKeyPathParameter{
				[](){
					std::stringstream ss;
					ss << "[";
					for (size_t i = 0; i < 10000; ++i) { if(i != 0) ss << ","; ss << i; }
					ss << "]";
					return ss.str();
				}(),
				{ static_cast<size_t>(9999) },
				true
			},
			JsonKeyPathParameter{
				R"({"newline":"line\nbreak","quote":"quote\"escape","unicode":"\u1234"})",
				{ std::string("unicode") },
				true
			},
			JsonKeyPathParameter{
				R"({"key":1,"key":2})",
				{ std::string("key") },
				true
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonStringExtractionPathologicalTests,
		JsonTextManagerStringExtractionParameterizedTest,
		::testing::Values(
			JsonStringExtractionParameter{
				R"({"newline":"line\nbreak"})",
				{ std::string("newline") },
				"line\nbreak"
			},
			JsonStringExtractionParameter{
				R"({"quote":"quote\"escape"})",
				{ std::string("quote") },
				"quote\"escape"
			},
			JsonStringExtractionParameter{
				R"({"unicode":"\u1234"})",
				{ std::string("unicode") },
				"\u1234"
			},
			JsonStringExtractionParameter{
				R"({"key":1,"key":2})",
				{ std::string("key") },
				""
			},
			JsonStringExtractionParameter{
				std::string("{\"a\":\"") + char(0xFF) + R"("})",
				{ std::string("a") },
				"\xFF"
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonDoubleExtractionPathologicalTests,
		JsonTextManagerDoubleExtractionParameterizedTest,
		::testing::Values(
			JsonDoubleExtractionParameter{
				[](){
					std::stringstream ss;
					ss << "[";
					for (size_t i = 0; i < 10000; ++i) { if(i != 0) ss << ","; ss << i; }
					ss << "]";
					return ss.str();
				}(),
				{ static_cast<size_t>(5000) },
				5000.0
			}
		)
	);

	INSTANTIATE_TEST_CASE_P(
		JsonBooleanExtractionPathologicalTests,
		JsonTextManagerBooleanExtractionParameterizedTest,
		::testing::Values(
			JsonBooleanExtractionParameter{
				R"({"flag":true})",
				{ std::string("flag") },
				true
			},
			JsonBooleanExtractionParameter{
				R"({"key":1,"key":2})",
				{ std::string("key") },
				false
			}
		)
	);
}

#endif
