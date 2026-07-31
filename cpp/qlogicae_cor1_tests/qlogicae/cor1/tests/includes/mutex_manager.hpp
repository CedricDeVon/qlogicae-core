#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		MutexManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	struct MutexManagerParameterizedTestData
	{
		bool construct_first;
	};

	struct MutexLockCombinationTestData
	{
		std::string mutex_type_name;

		bool construct_first;
	};

	struct FailingMutex
	{
		FailingMutex() { throw std::runtime_error("Constructor failure"); }
		void lock() {}
		void unlock() {}
	};

	class MutexManagerTest: public ::testing::Test
	{
	public:
		MutexManager mutex_manager_instance;

		void
			SetUp() override
		{
			mutex_manager_instance.construct();
			mutex_manager_instance.reset();
		}

		void
			TearDown() override
		{
			mutex_manager_instance.destruct();
			mutex_manager_instance.reset();
		}
	};

	class MutexManagerParameterizedTest:
		public MutexManagerTest,
		public ::testing::WithParamInterface<MutexManagerParameterizedTestData>
	{
	};

	class MutexManagerLockMutexTest:
		public ::testing::Test,
		public ::testing::WithParamInterface<MutexLockCombinationTestData>
	{
	public:
		MutexManager mutex_manager_instance;

		void* test_pointer;

		MutexManagerLockMutexTest()
			: test_pointer(this)
		{
		}

		void
			SetUp() override
		{
			mutex_manager_instance.construct();
			mutex_manager_instance.reset();
		}

		void
			TearDown() override
		{
			mutex_manager_instance.destruct();
			mutex_manager_instance.reset();
		}
	};

	class MutexManagerBoostTest: public ::testing::Test
	{
	public:
		MutexManager manager;
		void* test_ptr = reinterpret_cast<void*>(uintptr_t(0xDEADBEEF));

		void
			SetUp() override
		{
			manager.construct();
			manager.reset();
		}

		void
			TearDown() override
		{
			manager.destruct();
			manager.reset();
		}
	};

	class MutexManagerMicroSpinTest: public ::testing::Test
	{
	public:
		MutexManager manager;

		void
			SetUp() override
		{
			manager.construct();
			manager.reset();
		}

		void
			TearDown() override
		{
			manager.destruct();
			manager.reset();
		}
	};
}

#endif
