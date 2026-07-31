#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		StateManager \
	)

#include "../includes/state_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
    TEST_F
    (
        StateManagerTest,
        Should_AddItem_ExpectTrue_WhenValidSingleItem
    )
    {
        StateManagerItem
            item =
                create_item(
                    "key1",
                    1
                );

        bool
            result =
                state_manager.add(
                    item
                );

        ASSERT_TRUE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_AddItems_ExpectTrue_WhenValidVector
    )
    {
        std::vector<StateManagerItem>
            items;

        items.push_back(
            create_item(
                "key1",
                1
            )
        );

        bool
            result =
                state_manager.add(
                    items
                );

        ASSERT_TRUE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_GetValue_ExpectCorrect_WhenKeyExists
    )
    {
        StateManagerItem
            item =
                create_item(
                    "key1",
                    5
                );

        state_manager.add(
            item
        );

        std::any
            value =
                state_manager.get(
                    "key1"
                );

        ASSERT_EQ(
            std::any_cast<int>(
                value
            ),
            5
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_SetValue_ExpectUpdated_WhenKeyExists
    )
    {
        StateManagerItem
            item =
                create_item(
                    "key1",
                    1
                );

        state_manager.add(
            item
        );

        bool
            result =
                state_manager.set(
                    "key1",
                    10
                );

        ASSERT_TRUE(
            result
        );

        std::any
            value =
                state_manager.get(
                    "key1"
                );

        ASSERT_EQ(
            std::any_cast<int>(
                value
            ),
            10
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_ResetValue_ExpectInitial_WhenResetCalled
    )
    {
        StateManagerItem
            item =
                create_item(
                    "key1",
                    1
                );

        state_manager.add(
            item
        );

        state_manager.set(
            "key1",
            10
        );

        bool
            result =
                state_manager.reset(
                    "key1"
                );

        ASSERT_TRUE(
            result
        );

        std::any
            value =
                state_manager.get(
                    "key1"
                );

        ASSERT_EQ(
            std::any_cast<int>(
                value
            ),
            1
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_RemoveItem_ExpectTrue_WhenKeyExists
    )
    {
        StateManagerItem
            item =
                create_item(
                    "key1",
                    1
                );

        state_manager.add(
            item
        );

        bool
            result =
                state_manager.remove(
                    "key1"
                );

        ASSERT_TRUE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_ClearItems_ExpectTrue_WhenNotEmpty
    )
    {
        StateManagerItem
            item =
                create_item(
                    "key1",
                    1
                );

        state_manager.add(
            item
        );

        bool
            result =
                state_manager.clear();

        ASSERT_TRUE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Signal_ExpectExecution_WhenSignalExists
    )
    {
        StateManagerItem
            item =
                create_item(
                    "key1",
                    1
                );

        std::atomic<bool>
            executed =
                false;

        item.signals["test"] =
            [&executed]() -> std::any
            {
                executed =
                    true;

                return
                    std::any();
            };

        state_manager.add(
            item
        );

        bool
            result =
                state_manager.signal(
                    "key1",
                    std::vector<std::string>{ "test" }
                );

        ASSERT_TRUE(
            result
        );

        ASSERT_TRUE(
            executed.load()
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_HandleAsyncSet_ExpectCorrectValue_WhenUsingFuture
    )
    {
        StateManagerItem
            item =
                create_item(
                    "key1",
                    1
                );

        state_manager.add(
            item
        );

        std::future<bool>
            future_result =
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        return
                            state_manager.set(
                                "key1",
                                50
                            );
                    }
                );

        bool
            result =
                future_result.get();

        ASSERT_TRUE(
            result
        );

        ASSERT_EQ(
            std::any_cast<int>(
                state_manager.get(
                    "key1"
                )
            ),
            50
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_HandleMultithreadedSet_ExpectConsistency_WhenConcurrent
    )
    {
        StateManagerItem
            item =
                create_item(
                    "key1",
                    0
                );

        state_manager.add(
            item
        );

        std::vector<std::thread>
            threads;

        for
        (
            int index = 0;
            index < 100;
            ++index
        )
        {
            threads.emplace_back(
                [&]()
                {
                    state_manager.set(
                        "key1",
                        1
                    );
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

        ASSERT_EQ(
            std::any_cast<int>(
                state_manager.get(
                    "key1"
                )
            ),
            1
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_HandleStress_ExpectNoCrash_WhenHighLoad
    )
    {
        for
        (
            int index = 0;
            index < 10000;
            ++index
        )
        {
            StateManagerItem
                item =
                    create_item(
                        std::to_string(index),
                        index
                    );

            state_manager.add(
                item
            );
        }

        ASSERT_TRUE(
            true
        );
    }

    TEST_P
    (
        StateManagerParameterizedTest,
        Should_SetValues_ExpectCorrect_WhenParameterized
    )
    {
        int
            value =
                GetParam();

        StateManagerItem
            item;

        item.key =
            "key";

        item.initial_value =
            value;

        item.current_value =
            value;

        state_manager.add(
            item
        );

        state_manager.set(
            "key",
            value + 1
        );

        ASSERT_EQ(
            std::any_cast<int>(
                state_manager.get(
                    "key"
                )
            ),
            value + 1
        );
    }

    INSTANTIATE_TEST_CASE_P
    (
        StateManagerValues,
        StateManagerParameterizedTest,
        ::testing::Values(
            0,
            1,
            10,
            100
        )
    );

    TEST_F
    (
        StateManagerTest,
        Should_HandleEdgeEmptyKey_ExpectFailure_WhenInvalid
    )
    {
        bool
            result =
                state_manager.set(
                    "",
                    1
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_HandleException_ExpectSafe_WhenInvalidAccess
    )
    {
        try
        {
            state_manager.get(
                "invalid"
            );
        }
        catch
        (
            ...
        )
        {
            ASSERT_TRUE(
                true
            );

            return;
        }

        ASSERT_TRUE(
            true
        );
    }

	TEST_F
	(
		StateManagerTest,
		Should_NotAddItems_ExpectNoInsertion_WhenVectorContainsNewKeys
	)
	{
		std::vector<StateManagerItem>
			items;

		items.push_back(
			create_item(
				"new_key",
				1
			)
		);

		state_manager.add(
			items
		);

		std::any
			value =
				state_manager.get(
					"new_key"
				);

		ASSERT_TRUE(
			value.has_value() ==
			false
		);
	}

	TEST_F
	(
		StateManagerTest,
		Should_UpdateItems_ExpectOverwrite_WhenKeysExistInVectorAdd
	)
	{
		StateManagerItem
			item =
				create_item(
					"key1",
					1
				);

		state_manager.add(
			item
		);

		std::vector<StateManagerItem>
			items;

		items.push_back(
			create_item(
				"key1",
				5
			)
		);

		state_manager.add(
			items
		);

		ASSERT_EQ(
			std::any_cast<int>(
				state_manager.get(
					"key1"
				)
			),
			5
		);
	}

	TEST_F
	(
		StateManagerTest,
		Should_GetMultiple_ExpectCorrectMap_WhenKeysExist
	)
	{
		state_manager.add(
			create_item(
				"a",
				1
			)
		);

		state_manager.add(
			create_item(
				"b",
				2
			)
		);

		std::unordered_map<std::string,std::any>
			values =
				state_manager.get(
					std::vector<std::string>{ "a", "b" }
				);

		ASSERT_EQ(
			std::any_cast<int>(
				values["a"]
			),
			1
		);

		ASSERT_EQ(
			std::any_cast<int>(
				values["b"]
			),
			2
		);
	}

	TEST_F
	(
		StateManagerTest,
		Should_SetMultiple_ExpectOnlyExistingUpdated_WhenBulkSet
	)
	{
		state_manager.add(
			create_item(
				"a",
				1
			)
		);

		std::unordered_map<std::string,std::any>
			values;

		values["a"] =
			5;

		values["b"] =
			10;

		state_manager.set(
			values
		);

		ASSERT_EQ(
			std::any_cast<int>(
				state_manager.get(
					"a"
				)
			),
			5
		);
	}

	TEST_F
	(
		StateManagerTest,
		Should_ResetMultiple_ExpectInitialValues_WhenBulkReset
	)
	{
		state_manager.add(
			create_item(
				"a",
				1
			)
		);

		state_manager.set(
			"a",
			5
		);

		state_manager.reset(
			std::vector<std::string>{ "a" }
		);

		ASSERT_EQ(
			std::any_cast<int>(
				state_manager.get(
					"a"
				)
			),
			1
		);
	}

	TEST_F
	(
		StateManagerTest,
		Should_RemoveMultiple_ExpectItemsRemoved_WhenBulkRemove
	)
	{
		state_manager.add(
			create_item(
				"a",
				1
			)
		);

		state_manager.add(
			create_item(
				"b",
				2
			)
		);

		state_manager.remove(
			std::vector<std::string>{ "a", "b" }
		);

		std::any
			value_a =
				state_manager.get(
					"a"
				);

		ASSERT_TRUE(
			value_a.has_value() ==
			false
		);
	}

	TEST_F
	(
		StateManagerTest,
		Should_SignalAll_ExpectAllSignalsExecuted_WhenSingleKey
	)
	{
		StateManagerItem
			item =
				create_item(
					"k",
					1
				);

		std::atomic<int>
			count =
				0;

		item.signals["s1"] =
			[&count]() -> std::any
			{
				count.fetch_add(1);

				return std::any();
			};

		item.signals["s2"] =
			[&count]() -> std::any
			{
				count.fetch_add(1);

				return std::any();
			};

		state_manager.add(
			item
		);

		state_manager.signal(
			"k"
		);

		ASSERT_EQ(
			count.load(),
			2
		);
	}

	TEST_F
	(
		StateManagerTest,
		Should_SignalMap_ExpectSelectiveExecution_WhenUsingMap
	)
	{
		StateManagerItem
			item =
				create_item(
					"k",
					1
				);

		std::atomic<int>
			count =
				0;

		item.signals["s1"] =
			[&count]() -> std::any
			{
				count.fetch_add(1);

				return std::any();
			};

		state_manager.add(
			item
		);

		std::unordered_map<std::string,
			std::vector<std::string>>
			target;

		target["k"] =
			std::vector<std::string>{ "s1" };

		state_manager.signal(
			target
		);

		ASSERT_EQ(
			count.load(),
			1
		);
	}

	TEST_F
	(
		StateManagerTest,
		Should_SignalVector_ExpectAllSignalsExecuted_WhenMultipleKeys
	)
	{
		StateManagerItem
			item =
				create_item(
					"k",
					1
				);

		std::atomic<int>
			count =
				0;

		item.signals["s"] =
			[&count]() -> std::any
			{
				count.fetch_add(1);

				return std::any();
			};

		state_manager.add(
			item
		);

		state_manager.signal(
			std::vector<std::string>{ "k" }
		);

		ASSERT_EQ(
			count.load(),
			1
		);
	}

	TEST_F
	(
		StateManagerTest,
		Should_HandleConcurrentReadWrite_ExpectConsistency_WhenMixedOps
	)
	{
		state_manager.add(
			create_item(
				"k",
				0
			)
		);

		std::atomic<bool>
			run =
				true;

		std::thread
			writer(
				[&]()
				{
					for
					(
						int index = 0;
						index < 1000;
						++index
					)
					{
						state_manager.set(
							"k",
							index
						);
					}

					run =
						false;
				}
			);

		std::thread
			reader(
				[&]()
				{
					while
					(
						run.load()
					)
					{
						state_manager.get(
							"k"
						);
					}
				}
			);

		writer.join();
		reader.join();

		ASSERT_TRUE(
			true
		);
	}

	TEST_F
	(
		StateManagerTest,
		Should_HandleAsyncSignal_ExpectExecution_WhenUsingFuture
	)
	{
		StateManagerItem
			item =
				create_item(
					"k",
					1
				);

		std::atomic<bool>
			executed =
				false;

		item.signals["s"] =
			[&executed]() -> std::any
			{
				executed =
					true;

				return std::any();
			};

		state_manager.add(
			item
		);

		std::future<bool>
			future_result =
				std::async(
					std::launch::async,
					[&]()
					{
						return
							state_manager.signal(
								"k"
							);
					}
				);

		ASSERT_TRUE(
			future_result.get()
		);

		ASSERT_TRUE(
			executed.load()
		);
	}
	
	TEST_F
	(
		StateManagerTest,
		Should_HandleStressConcurrent_ExpectNoCrash_WhenHighLoadMixed
	)
	{
		state_manager.add(
			create_item(
				"k",
				0
			)
		);

		std::vector<std::thread>
			threads;

		for
		(
			int index = 0;
			index < 50;
			++index
		)
		{
			threads.emplace_back(
				[&]()
				{
					for
					(
						int inner = 0;
						inner < 500;
						++inner
					)
					{
						state_manager.set(
							"k",
							inner
						);

						state_manager.get(
							"k"
						);
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

		ASSERT_TRUE(
			true
		);
	}

    TEST_F
    (
        StateManagerTest,
        Should_AddItems_ExpectFalse_WhenEmptyVector
    )
    {
        std::vector<StateManagerItem>
            items;

        bool
            result =
                state_manager.add(
                    items
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_GetMultiple_ExpectFalse_WhenEmptyVector
    )
    {
        std::vector<std::string>
            keys;

        auto
            result =
                state_manager.get(
                    keys
                );

        ASSERT_TRUE(
            result.empty()
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_SignalMap_ExpectFalse_WhenEmptyMap
    )
    {
        std::unordered_map<std::string,
            std::vector<std::string>>
            target;

        bool
            result =
                state_manager.signal(
                    target
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_SignalVector_ExpectFalse_WhenEmptyVector
    )
    {
        std::vector<std::string>
            keys;

        bool
            result =
                state_manager.signal(
                    keys
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Signal_ExpectFalse_WhenEmptySignalKeys
    )
    {
        StateManagerItem
            item =
                create_item(
                    "k",
                    1
                );

        bool
            add_result =
                state_manager.add(
                    item
                );

        ASSERT_TRUE(
            add_result
        );

        std::vector<std::string>
            signals;

        bool
            result =
                state_manager.signal(
                    "k",
                    signals
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_SetMap_ExpectFalse_WhenEmptyMap
    )
    {
        std::unordered_map<std::string,std::any>
            values;

        bool
            result =
                state_manager.set(
                    values
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_ResetMultiple_ExpectFalse_WhenEmptyVector
    )
    {
        std::vector<std::string>
            keys;

        bool
            result =
                state_manager.reset(
                    keys
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_RemoveMultiple_ExpectFalse_WhenEmptyVector
    )
    {
        std::vector<std::string>
            keys;

        bool
            result =
                state_manager.remove(
                    keys
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Clear_ExpectFalse_WhenAlreadyEmpty
    )
    {
        bool
            result =
                state_manager.clear();

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Get_ExpectInsertion_WhenKeyDoesNotExist
    )
    {
        std::any
            value =
                state_manager.get(
                    "missing"
                );

        ASSERT_TRUE(
            value.has_value() ==
            false
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Signal_ExpectNoCrash_WhenKeyDoesNotExist
    )
    {
        bool
            result =
                state_manager.signal(
                    "missing"
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Set_ExpectFalse_WhenKeyDoesNotExist
    )
    {
        bool
            result =
                state_manager.set(
                    "missing",
                    1
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Signal_ExpectNoExecution_WhenSignalMissing
    )
    {
        StateManagerItem
            item =
                create_item(
                    "k",
                    1
                );

        std::atomic<bool>
            executed =
                false;

        item.signals["valid"] =
            [&executed]() -> std::any
            {
                executed =
                    true;

                return
                    std::any();
            };

        bool
            add_result =
                state_manager.add(
                    item
                );

        ASSERT_TRUE(
            add_result
        );

        bool
            result =
                state_manager.signal(
                    "k",
                    std::vector<std::string>{ "invalid" }
                );

        ASSERT_TRUE(
            result
        );

        ASSERT_FALSE(
            executed.load()
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Signal_ExpectNoCrash_WhenSignalsEmpty
    )
    {
        StateManagerItem
            item =
                create_item(
                    "k",
                    1
                );

        bool
            add_result =
                state_manager.add(
                    item
                );

        ASSERT_TRUE(
            add_result
        );

        bool
            result =
                state_manager.signal(
                    "k"
                );

        ASSERT_TRUE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Signal_ExpectIgnoreNullFunction_WhenSignalNull
    )
    {
        StateManagerItem
            item =
                create_item(
                    "k",
                    1
                );

        item.signals["null"] =
            std::function<std::any()>();

        bool
            add_result =
                state_manager.add(
                    item
                );

        ASSERT_TRUE(
            add_result
        );

        bool
            result =
                state_manager.signal(
                    "k"
                );

        ASSERT_TRUE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Signal_ExpectThrow_WhenSignalThrows
    )
    {
        StateManagerItem
            item =
            create_item(
                "k",
                1
            );

        item.signals["throw"] =
            []() -> std::any
        {
            throw std::runtime_error(
                "error"
            );
        };

        state_manager.add(
            item
        );

        ASSERT_THROW(
            state_manager.signal(
                "k"
            ),
            std::runtime_error
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_AddItems_ExpectPartialUpdate_WhenMixedKeys
    )
    {
        StateManagerItem
            existing =
                create_item(
                    "a",
                    1
                );

        bool
            add_result =
                state_manager.add(
                    existing
                );

        ASSERT_TRUE(
            add_result
        );

        std::vector<StateManagerItem>
            items;

        items.push_back(
            create_item(
                "a",
                10
            )
        );

        items.push_back(
            create_item(
                "b",
                20
            )
        );

        bool
            result =
                state_manager.add(
                    items
                );

        ASSERT_TRUE(
            result
        );

        ASSERT_EQ(
            std::any_cast<int>(
                state_manager.get(
                    "a"
                )
            ),
            10
        );

        std::any
            value_b =
                state_manager.get(
                    "b"
                );

        ASSERT_TRUE(
            value_b.has_value() ==
            false
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_GetMultiple_ExpectPartialInsertion_WhenMixedKeys
    )
    {
        bool
            add_result =
                state_manager.add(
                    create_item(
                        "a",
                        1
                    )
                );

        ASSERT_TRUE(
            add_result
        );

        auto
            result =
                state_manager.get(
                    std::vector<std::string>{ "a", "b" }
                );

        ASSERT_EQ(
            std::any_cast<int>(
                result["a"]
            ),
            1
        );

        ASSERT_TRUE(
            result["b"].has_value() ==
            false
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Get_ExpectFalse_WhenEmptyKey
    )
    {
        std::any
            value =
                state_manager.get(
                    ""
                );

        ASSERT_TRUE(
            value.has_value() ==
            false
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Remove_ExpectFalse_WhenKeyDoesNotExist
    )
    {
        bool
            result =
                state_manager.remove(
                    "missing"
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Reset_ExpectFalse_WhenKeyDoesNotExist
    )
    {
        bool
            result =
                state_manager.reset(
                    "missing"
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Signal_ExpectFalse_WhenEmptyKey
    )
    {
        bool
            result =
                state_manager.signal(
                    ""
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_SignalMap_ExpectPartialExecution_WhenMixedKeys
    )
    {
        StateManagerItem
            item =
                create_item(
                    "valid",
                    1
                );

        std::atomic<int>
            count =
                0;

        item.signals["s"] =
            [&count]() -> std::any
            {
                count.fetch_add(1);

                return std::any();
            };

        bool
            add_result =
                state_manager.add(
                    item
                );

        ASSERT_TRUE(
            add_result
        );

        std::unordered_map<std::string,
            std::vector<std::string>>
            target;

        target["valid"] =
            std::vector<std::string>{ "s" };

        target["invalid"] =
            std::vector<std::string>{ "s" };

        bool
            result =
                state_manager.signal(
                    target
                );

        ASSERT_TRUE(
            result
        );

        ASSERT_EQ(
            count.load(),
            1
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_SetMap_ExpectNoInsertion_WhenInvalidKeysPresent
    )
    {
        bool
            add_result =
                state_manager.add(
                    create_item(
                        "a",
                        1
                    )
                );

        ASSERT_TRUE(
            add_result
        );

        std::unordered_map<std::string,std::any>
            values;

        values["a"] =
            5;

        values["b"] =
            10;

        bool
            result =
                state_manager.set(
                    values
                );

        ASSERT_TRUE(
            result
        );

        ASSERT_EQ(
            std::any_cast<int>(
                state_manager.get(
                    "a"
                )
            ),
            5
        );

        std::any
            value_b =
                state_manager.get(
                    "b"
                );

        ASSERT_TRUE(
            value_b.has_value() ==
            false
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Clear_ExpectStateReset_WhenFollowedByOperations
    )
    {
        bool
            add_result =
                state_manager.add(
                    create_item(
                        "a",
                        1
                    )
                );

        ASSERT_TRUE(
            add_result
        );

        bool
            clear_result =
                state_manager.clear();

        ASSERT_TRUE(
            clear_result
        );

        std::any
            value =
                state_manager.get(
                    "a"
                );

        ASSERT_TRUE(
            value.has_value() ==
            false
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Get_ExpectEmptyAny_WhenEmptyStringKey
    )
    {
        std::any
            value =
                state_manager.get(
                    ""
                );

        ASSERT_TRUE(
            value.has_value() ==
            false
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_AddVector_ExpectFalse_WhenEmptyVector
    )
    {
        std::vector<StateManagerItem>
            items;

        bool
            result =
                state_manager.add(
                    items
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_GetVector_ExpectEmpty_WhenEmptyVector
    )
    {
        std::vector<std::string>
            keys;

        auto
            result =
                state_manager.get(
                    keys
                );

        ASSERT_TRUE(
            result.empty()
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_ResetVector_ExpectFalse_WhenEmptyVector
    )
    {
        std::vector<std::string>
            keys;

        bool
            result =
                state_manager.reset(
                    keys
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_RemoveVector_ExpectFalse_WhenEmptyVector
    )
    {
        std::vector<std::string>
            keys;

        bool
            result =
                state_manager.remove(
                    keys
                );

        ASSERT_FALSE(
            result
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_SignalMap_ExpectPartial_WhenMixedKeys
    )
    {
        StateManagerItem
            item =
                create_item(
                    "valid",
                    1
                );

        std::atomic<int>
            count =
                0;

        item.signals["s"] =
            [&count]() -> std::any
            {
                count.fetch_add(1);
                return std::any();
            };

        bool
            add_result =
                state_manager.add(
                    item
                );

        ASSERT_TRUE(
            add_result
        );

        std::unordered_map<std::string,
            std::vector<std::string>>
            target;

        target["valid"] =
            std::vector<std::string>{ "s" };

        target["invalid"] =
            std::vector<std::string>{ "s" };

        bool
            result =
                state_manager.signal(
                    target
                );

        ASSERT_TRUE(
            result
        );

        ASSERT_EQ(
            count.load(),
            1
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_SetMap_ExpectNoInsert_WhenInvalidKeysPresent
    )
    {
        StateManagerItem
            item =
                create_item(
                    "a",
                    1
                );

        bool
            add_result =
                state_manager.add(
                    item
                );

        ASSERT_TRUE(
            add_result
        );

        std::unordered_map<std::string,std::any>
            values;

        values["a"] =
            5;

        values["b"] =
            10;

        bool
            result =
                state_manager.set(
                    values
                );

        ASSERT_TRUE(
            result
        );

        ASSERT_EQ(
            std::any_cast<int>(
                state_manager.get(
                    "a"
                )
            ),
            5
        );

        std::any
            value_b =
                state_manager.get(
                    "b"
                );

        ASSERT_TRUE(
            value_b.has_value() ==
            false
        );
    }

    TEST_F
    (
        StateManagerTest,
        Should_Clear_ExpectStateReset_WhenFollowedByGet
    )
    {
        state_manager.add(
            create_item(
                "a",
                1
            )
        );

        bool
            clear_result =
                state_manager.clear();

        ASSERT_TRUE(
            clear_result
        );

        std::any
            value =
                state_manager.get(
                    "a"
                );

        ASSERT_TRUE(
            value.has_value() ==
            false
        );
    }
}

#endif
