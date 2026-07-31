#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RegularExpressionManager \
	)

#include "../includes/regular_expression_manager.hpp"

namespace
    QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
    TEST_F(
        RegularExpressionManagerTest,
        Should_ReturnTrue_When_PatternMatchesValue
    )
    {
        bool
            result =
                regular_expression_manager
                    .is_direct_pattern_matched(
                        "abc123",
                        "[a-z]+[0-9]+"
                    );

        EXPECT_TRUE(
            result
        );
    }

    TEST_F(
        RegularExpressionManagerTest,
        Should_ReturnFalse_When_PatternDoesNotMatchValue
    )
    {
        bool
            result =
                regular_expression_manager
                    .is_direct_pattern_matched(
                        "abc",
                        "[0-9]+"
                    );

        EXPECT_FALSE(
            result
        );
    }

    TEST_F(
        RegularExpressionManagerTest,
        Should_ReturnFalse_When_PatternIsInvalid
    )
    {
        bool
            result =
                regular_expression_manager
                    .is_direct_pattern_matched(
                        "abc",
                        "["
                    );

        EXPECT_FALSE(
            result
        );
    }

    TEST_F(
        RegularExpressionManagerTest,
        Should_HandleEmptyValue_When_EmptyStringProvided
    )
    {
        bool
            result =
                regular_expression_manager
                    .is_direct_pattern_matched(
                        "",
                        ".*"
                    );

		EXPECT_FALSE(
            result
        );
    }

    TEST_F(
        RegularExpressionManagerTest,
        Should_HandleEmptyPattern_When_EmptyPatternProvided
    )
    {
        bool
            result =
                regular_expression_manager
                    .is_direct_pattern_matched(
                        "abc",
                        ""
                    );

        EXPECT_FALSE(
            result
        );
    }

    TEST_P(
        RegularExpressionManagerParameterizedTest,
        Should_MatchExpectedResult_When_ValidParametersProvided
    )
    {
        RegularExpressionParameters
            parameters =
                GetParam();

        bool
            result =
                regular_expression_manager
                    .is_direct_pattern_matched(
                        parameters.value,
                        parameters.pattern
                    );

        EXPECT_EQ(
            result,
            parameters.expected_result
        );
    }

	INSTANTIATE_TEST_CASE_P(
		RegularExpressionManagerConversions,
		RegularExpressionManagerParameterizedTest,
		::testing::Values(
			RegularExpressionParameters
			{
				"123",
				"[0-9]+",
				true
			},
			RegularExpressionParameters
			{
				"abc",
				"[a-z]+",
				true
			},
			RegularExpressionParameters
			{
				"ABC",
				"[a-z]+",
				false
			},
			RegularExpressionParameters
			{
				"abc123",
				"^[a-z]+[0-9]+$",
				true
			},
			RegularExpressionParameters
			{
				"",
				"^$",
				false
			},
			RegularExpressionParameters
			{
				" ",
				"\\s",
				true
			},
			RegularExpressionParameters
			{
				"abc",
				"[",
				false
			},
			RegularExpressionParameters
			{
				"üñîçødé",
				"üñîçødé",
				true
			},
			RegularExpressionParameters
			{
				"你好",
				"你好",
				true
			},
			RegularExpressionParameters
			{
				"こんにちは",
				"こんばんは",
				false
			},
			RegularExpressionParameters
			{
				std::string(1000000, 'a'),
				"a+",
				true
			},
			RegularExpressionParameters
			{
				"abc123XYZ",
				"^[a-z0-9A-Z]+$",
				true
			},
			RegularExpressionParameters
			{
				"abc\n123",
				"^[a-z0-9]+$",
				false
			},
			RegularExpressionParameters
			{
				"tab\tspace",
				"\\t",
				true
			},
			RegularExpressionParameters
			{
				"newline\n",
				"\\n",
				true
			},
			RegularExpressionParameters
			{
				"special$^*()",
				"\\$\\^\\*\\(\\)",
				true
			},
			RegularExpressionParameters
			{
				"mixed123ABC",
				"[a-z]+[0-9]+[A-Z]+",
				true
			},
			RegularExpressionParameters
			{
				"emptystring",
				"",
				false
			}
		)
	);

    TEST_F(
        RegularExpressionManagerTest,
        Should_NotThrow_When_CalledConcurrently
    )
    {
        std::atomic<bool>
            completed =
                false;

        std::thread
            worker_thread =
                std::thread(
                    [&]()
                    {
                        for
                        (
                            std::size_t
                                iteration = 0;
                            iteration < 10000;
                            ++iteration
                        )
                        {
                            regular_expression_manager
                                .is_direct_pattern_matched(
                                    "abc123",
                                    "[a-z]+[0-9]+"
                                );
                        }

                        completed =
                            true;
                    }
                );

        worker_thread
            .join();

        EXPECT_TRUE(
            completed
        );
    }

    TEST_F(
        RegularExpressionManagerTest,
        Should_NotDeadlock_When_MultipleThreadsExecuteSimultaneously
    )
    {
        std::atomic<std::size_t>
            completed_threads =
                0;

        std::vector<std::thread>
            worker_threads;

        for
        (
            std::size_t
                thread_index = 0;
            thread_index < 8;
            ++thread_index
        )
        {
            worker_threads
                .emplace_back(
                    [&]()
                    {
                        for
                        (
                            std::size_t
                                iteration = 0;
                            iteration < 5000;
                            ++iteration
                        )
                        {
                            regular_expression_manager
                                .is_direct_pattern_matched(
                                    "value",
                                    "value"
                                );
                        }

                        ++completed_threads;
                    }
                );
        }

        for
        (
            std::thread&
                worker_thread :
                worker_threads
        )
        {
            worker_thread
                .join();
        }

        EXPECT_EQ(
            completed_threads.load(),
            static_cast<std::size_t>(
                8
            )
        );
    }

    TEST_F(
        RegularExpressionManagerTest,
        Should_ExecuteAsynchronously_When_UsingStdAsync
    )
    {
        std::future<bool>
            result_future =
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        return
                            regular_expression_manager
                                .is_direct_pattern_matched(
                                    "async123",
                                    "[a-z]+[0-9]+"
                                );
                    }
                );

        EXPECT_TRUE(
            result_future.get()
        );
    }

    TEST_F(
        RegularExpressionManagerTest,
        Should_ExecuteMultipleAsyncTasks_When_UsingFutures
    )
    {
        std::vector<
            std::future<bool>
        >
            futures;

        for
        (
            std::size_t
                iteration = 0;
            iteration < 16;
            ++iteration
        )
        {
            futures
                .emplace_back(
                    std::async(
                        std::launch::async,
                        [&]()
                        {
                            return
                                regular_expression_manager
                                    .is_direct_pattern_matched(
                                        "123",
                                        "[0-9]+"
                                    );
                        }
                    )
                );
        }

        for
        (
            std::future<bool>&
                result_future :
                futures
        )
        {
            EXPECT_TRUE(
                result_future.get()
            );
        }
    }

    TEST_F(
        RegularExpressionManagerTest,
        Should_NotThrow_When_ExceptionOccursInternally
    )
    {
        bool
            result =
                regular_expression_manager
                    .is_direct_pattern_matched(
                        "test",
                        "("
                    );

        EXPECT_FALSE(
            result
        );
    }

	TEST_F(
		RegularExpressionManagerTest,
		Should_MatchDefaultPattern_When_DefaultPatternSet
	)
	{
		RegularExpressionManagerConfigurations
			configurations;

		configurations.pattern =
			"[a-z]+";

		regular_expression_manager
			.setup(
				configurations
			);

		EXPECT_TRUE(
			regular_expression_manager
			.is_direct_pattern_matched(
				"abc"
			)
		);

		EXPECT_FALSE(
			regular_expression_manager
			.is_direct_pattern_matched(
				"123"
			)
		);
	}

	TEST_F(
		RegularExpressionManagerTest,
		Should_HandleNullPcre2CodeGracefully
	)
	{
		bool
			result =
			regular_expression_manager
			.is_pattern_matched(
				"abc",
				nullptr
			);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		RegularExpressionManagerTest,
		Should_ExecuteCorrectly_When_ThreadSafetyOverrideEnabled
	)
	{
		RegularExpressionManagerConfigurations
			configurations;

		configurations.is_thread_safety_handling_override_enabled =
			true;

		regular_expression_manager
			.setup(
				configurations
			);

		EXPECT_TRUE(
			regular_expression_manager
			.is_direct_pattern_matched(
				"test",
				"test"
			)
		);
	}

	TEST_F(
		RegularExpressionManagerTest,
		Should_HandleExtremeLargeStringInput
	)
	{
		std::string
			large_string(
				1000000,
				'a'
			);

		RegularExpressionManagerConfigurations
			configurations;

		configurations.pattern =
			"a+";

		regular_expression_manager
			.setup(
				configurations
			);

		EXPECT_TRUE(
			regular_expression_manager
			.is_direct_pattern_matched(
				large_string
			)
		);
	}

	TEST_P(
		RegularExpressionManagerUnicodeParameterizedTest,
		Should_HandleUnicodePatternsCorrectly
	)
	{
		UnicodePatternTestParameters
			parameters =
			GetParam();

		RegularExpressionManagerConfigurations
			configurations;

		configurations.pattern =
			parameters.pattern;

		regular_expression_manager
			.setup(
				configurations
			);

		EXPECT_EQ(
			regular_expression_manager
			.is_direct_pattern_matched(
				parameters.input_value
			),
			parameters.expected_value
		);
	}

	INSTANTIATE_TEST_CASE_P(
		RegularExpressionManagerUnicodeTests,
		RegularExpressionManagerUnicodeParameterizedTest,
		::testing::Values(
			UnicodePatternTestParameters
			{
				"üñîçødé",
				"üñîçødé",
				true
			},
			UnicodePatternTestParameters
			{
				"你好",
				"你好",
				true
			},
			UnicodePatternTestParameters
			{
				"こんにちは",
				"こんばんは",
				false
			}
		)
	);
}

#endif
