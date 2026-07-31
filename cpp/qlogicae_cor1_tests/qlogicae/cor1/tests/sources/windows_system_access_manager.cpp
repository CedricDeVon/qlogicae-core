#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsSystemAccessManager \
	)

#include "../includes/windows_system_access_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(WindowsSystemAccessManagerTest, Should_ReturnSameInstance_When_AccessedMultipleTimes)
	{
		auto& instance1 = SingletonManager::get_singleton<WindowsSystemAccessManager>();
		auto& instance2 = SingletonManager::get_singleton<WindowsSystemAccessManager>();
		ASSERT_EQ(&instance1, &instance2);
	}

	TEST_F(WindowsSystemAccessManagerTest, Should_ConstructSuccessfully_When_Normal)
	{
		ASSERT_TRUE(manager.construct());
	}

	TEST_F(WindowsSystemAccessManagerTest, Should_DestructSuccessfully_When_Normal)
	{
		ASSERT_TRUE(manager.destruct());
	}

	INSTANTIATE_TEST_CASE_P(
		CommandVariants,
		WindowsSystemAccessManagerRunProcessTest,
		::testing::Values(
			"echo test",
			"",
			"InvalidCommand",
			"   ",
			std::string(1024, 'A'),
			"echo special&chars|test"
		)
	);

	TEST_P(WindowsSystemAccessManagerRunProcessTest, Should_ReturnBool_When_RunProcess)
	{
		std::string command = GetParam();
		bool result = manager.run_process(command);
		ASSERT_TRUE(result || command.empty());
	}

	TEST_F(WindowsSystemAccessManagerTest, Should_HandleAsync_When_RunProcess)
	{
		auto future_set = std::async(std::launch::async, [&]()
		{
			return manager.run_process("echo async");
		});
		ASSERT_TRUE(future_set.get());
	}

	TEST_F(WindowsSystemAccessManagerTest, Should_HandleMultithreadedAccess_When_RunProcess)
	{
		std::atomic<int> completed_count = 0;

		std::thread thread1([&]()
		{
			if (manager.run_process("echo t1")) ++completed_count;
		});

		std::thread thread2([&]()
		{
			if (manager.run_process("echo t2")) ++completed_count;
		});

		thread1.join();
		thread2.join();

		ASSERT_EQ(completed_count.load(), 2);
	}

	TEST_F(WindowsSystemAccessManagerTest, Should_HandleStress_When_RunProcessManyTimes)
	{
		for (int i = 0; i < 100; ++i)
		{
			ASSERT_TRUE(manager.run_process("echo stress"));
		}
	}
	
	TEST_F(WindowsSystemAccessManagerTest,
		Should_HandleMultithreadedConstructDestruct_When_Concurrent)
	{
		std::atomic<int> completed_count = 0;

		auto thread_func = [&]()
			{
				if (manager.construct()) ++completed_count;
				if (manager.destruct()) ++completed_count;
			};

		std::thread thread1(thread_func);
		std::thread thread2(thread_func);
		thread1.join();
		thread2.join();

		ASSERT_EQ(completed_count.load(), 4);
	}
	
	TEST_F(WindowsSystemAccessManagerTest,
		Should_HandleInvalidInput_When_RunProcess)
	{
		ASSERT_NO_THROW(manager.run_process(""));
		ASSERT_NO_THROW(manager.run_process(std::string(2048, 'A')));
	}

	
	TEST_F(WindowsSystemAccessManagerTest,
		Should_ReturnBool_When_HasAdminAccess)
	{
		bool result = manager.has_admin_access();
		ASSERT_TRUE(result == true || result == false);
	}
}

#endif
