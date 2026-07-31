#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsEnvironmentVariableManager \
	)

#include "../includes/windows_environment_variable_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_Construct_Safely_When_Invoked
	)
	{
		ASSERT_TRUE(
			manager.construct()
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_Destruct_Safely_When_Invoked
	)
	{
		ASSERT_TRUE(
			manager.destruct()
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_ReturnEmpty_When_KeyDoesNotExist
	)
	{
		std::wstring
			result =
				manager.get_value(
					L"QLOGICAE_NON_EXISTENT_KEY"
				);

		ASSERT_TRUE(
			result.empty()
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_SetAndGetValue_When_ValidWideKeyProvided
	)
	{
		ASSERT_TRUE(
			manager.set_value(
				L"QLOGICAE_TEST_KEY_W",
				L"QLOGICAE_TEST_VALUE_W"
			)
		);

		ASSERT_EQ(
			manager.get_value(
				L"QLOGICAE_TEST_KEY_W"
			),
			L"QLOGICAE_TEST_VALUE_W"
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_RemoveValue_When_KeyExists
	)
	{
		manager.set_value(
			L"QLOGICAE_REMOVE_KEY",
			L"VALUE"
		);

		ASSERT_TRUE(
			manager.remove_value(
				L"QLOGICAE_REMOVE_KEY"
			)
		);

		ASSERT_TRUE(
			manager.get_value(
				L"QLOGICAE_REMOVE_KEY"
			).empty()
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_HandleUtf8_When_StringInterfaceUsed
	)
	{
		ASSERT_TRUE(
			manager.set_value(
				std::string(
					"QLOGICAE_UTF8_KEY"
				),
				std::string(
					"UTF8_VALUE"
				)
			)
		);

		ASSERT_EQ(
			manager.get_value(
				std::string(
					"QLOGICAE_UTF8_KEY"
				)
			),
			"UTF8_VALUE"
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_BeThreadSafe_When_AccessedConcurrently
	)
	{
		std::atomic<bool>
			completed =
				false;

		std::thread
			writer(
				[&]()
				{
					for (
						std::size_t
							iteration = 0;
						iteration < 1000;
						iteration++
					)
					{
						manager.set_value(
							L"QLOGICAE_MT_KEY",
							L"VALUE"
						);
					}
				}
			);

		std::thread
			reader(
				[&]()
				{
					for (
						std::size_t
							iteration = 0;
						iteration < 1000;
						iteration++
					)
					{
						manager.get_value(
							L"QLOGICAE_MT_KEY"
						);
					}
					completed.store(
						true
					);
				}
			);

		writer.join();
		reader.join();

		ASSERT_TRUE(
			completed.load()
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_OperateCorrectly_When_AsyncInvoked
	)
	{
		std::future<bool>
			result =
				std::async(
					std::launch::async,
					[&]()
					{
						return
							manager.set_value(
								L"QLOGICAE_ASYNC_KEY",
								L"ASYNC_VALUE"
							);
					}
				);

		ASSERT_TRUE(
			result.get()
		);

		ASSERT_EQ(
			manager.get_value(
				L"QLOGICAE_ASYNC_KEY"
			),
			L"ASYNC_VALUE"
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_HandleStress_When_RepeatedlyInvoked
	)
	{
		for (
			std::size_t
				iteration = 0;
			iteration < 10000;
			iteration++
		)
		{
			ASSERT_TRUE(
				manager.set_value(
					L"QLOGICAE_STRESS_KEY",
					L"VALUE"
				)
			);

			ASSERT_FALSE(
				manager.get_value(
					L"QLOGICAE_STRESS_KEY"
				).empty()
			);
		}
	}

	TEST_P(
		WindowsEnvironmentVariableManagerParameterizedTest,
		Should_ReturnEmpty_When_InvalidKeyProvided
	)
	{
		ASSERT_TRUE(
			manager.get_value(
				GetParam()
			).empty()
		);
	}

	INSTANTIATE_TEST_CASE_P(
		InvalidKeys,
		WindowsEnvironmentVariableManagerParameterizedTest,
		::testing::Values(
			L"",
			L" ",
			L"\0"
		)
	);

	
	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_OverwriteExistingValue_When_SetTwice
	)
	{
		ASSERT_TRUE(
			manager.set_value(
				L"QLOGICAE_OVERWRITE_KEY",
				L"FIRST"
			)
		);

		ASSERT_TRUE(
			manager.set_value(
				L"QLOGICAE_OVERWRITE_KEY",
				L"SECOND"
			)
		);

		ASSERT_EQ(
			manager.get_value(
				L"QLOGICAE_OVERWRITE_KEY"
			),
			L"SECOND"
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_ReturnFalse_When_RemovingMissingKey
	)
	{
		ASSERT_TRUE(
			manager.remove_value(
				L"QLOGICAE_MISSING_REMOVE_KEY"
			)
		);

		ASSERT_TRUE(
			manager.get_value(
				L"QLOGICAE_MISSING_REMOVE_KEY"
			).empty()
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_RejectEmptyValue
	)
	{
		ASSERT_FALSE(
			manager.set_value(
				L"QLOGICAE_EMPTY_VALUE_KEY",
				L""
			)
		);

		ASSERT_TRUE(
			manager.get_value(
				L"QLOGICAE_EMPTY_VALUE_KEY"
			).empty()
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_HandleLargeValue
	)
	{
		std::wstring
			large_value(
				30000,
				L'X'
			);

		ASSERT_TRUE(
			manager.set_value(
				L"QLOGICAE_LARGE_VALUE_KEY",
				large_value
			)
		);

		ASSERT_EQ(
			manager.get_value(
				L"QLOGICAE_LARGE_VALUE_KEY"
			).size(),
			large_value.size()
		);
	}

	TEST_F(
		WindowsEnvironmentVariableManagerTest,
		Should_HandlePointerInputs
	)
	{
		const wchar_t*
			null_wide =
				nullptr;

		const char*
			null_narrow =
				nullptr;

		ASSERT_TRUE(
			manager.get_value(
				std::wstring()
			).empty()
		);

		ASSERT_TRUE(
			manager.get_value(
				std::string()
			).empty()
		);

		ASSERT_FALSE(
			manager.set_value(
				std::wstring(),
				L"VALUE"
			)
		);

		ASSERT_FALSE(
			manager.set_value(
				std::string(),
				std::string(
					"VALUE"
				)
			)
		);
	}
}

#endif
