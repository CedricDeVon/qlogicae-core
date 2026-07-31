#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SingletonManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	enum class TestPlainEnum
	{
		ZERO = 0,
		ONE = 1,
		MAXIMUM = 2
	};

	struct TestPlainStruct
	{
		int value;
	};

	struct NonDefaultConstructible
	{
		explicit NonDefaultConstructible(int) {}
	};

	struct ThrowingConstructor
	{
		ThrowingConstructor()
		{
			throw std::runtime_error("error");
		}
	};

	class TestPlainClass
	{
	public:
		TestPlainClass() = default;

		int value;
	};

	class SingletonManagerTest: public ::testing::Test
	{
	public:
		SingletonManagerTest() = default;

		~SingletonManagerTest() override = default;

		void
			SetUp() override
		{
			SingletonManager::get_this_singleton().construct();
			SingletonManager::get_this_singleton().reset();
		}

		void
			TearDown() override
		{
			SingletonManager::get_this_singleton().destruct();
			SingletonManager::get_this_singleton().reset();
		}
	};

	class SingletonManagerTypeParameterizedTest:
		public ::testing::TestWithParam<int>
	{
	public:
		SingletonManagerTypeParameterizedTest() = default;

		~SingletonManagerTypeParameterizedTest() override = default;

		void
			SetUp() override
		{
			SingletonManager::get_this_singleton().construct();
			SingletonManager::get_this_singleton().reset();
		}

		void
			TearDown() override
		{
			SingletonManager::get_this_singleton().destruct();
			SingletonManager::get_this_singleton().reset();
		}
	};

	class SingletonManagerStructParameterizedTest:
		public ::testing::TestWithParam<int>
	{
	public:
		SingletonManagerStructParameterizedTest() = default;

		~SingletonManagerStructParameterizedTest() override = default;

		void
			SetUp() override
		{
			SingletonManager::get_this_singleton().construct();
			SingletonManager::get_this_singleton().reset();
		}

		void
			TearDown() override
		{
			SingletonManager::get_this_singleton().destruct();
			SingletonManager::get_this_singleton().reset();
		}
	};

	class SingletonManagerClassParameterizedTest:
		public ::testing::TestWithParam<int>
	{
	public:
		SingletonManagerClassParameterizedTest() = default;

		~SingletonManagerClassParameterizedTest() override = default;

		void
			SetUp() override
		{
			SingletonManager::get_this_singleton().construct();
			SingletonManager::get_this_singleton().reset();
		}

		void
			TearDown() override
		{
			SingletonManager::get_this_singleton().destruct();
			SingletonManager::get_this_singleton().reset();
		}
	};

	class SingletonManagerEnumParameterizedTest:
		public ::testing::TestWithParam<TestPlainEnum>
	{
	public:
		SingletonManagerEnumParameterizedTest() = default;

		~SingletonManagerEnumParameterizedTest() override = default;

		void
			SetUp() override
		{
			SingletonManager::get_this_singleton().construct();
			SingletonManager::get_this_singleton().reset();
		}

		void
			TearDown() override
		{
			SingletonManager::get_this_singleton().destruct();
			SingletonManager::get_this_singleton().reset();
		}
	};

	class SingletonManagerMixedTypeParameterizedTest:
		public ::testing::TestWithParam<int>
	{
	public:
		SingletonManagerMixedTypeParameterizedTest() = default;

		~SingletonManagerMixedTypeParameterizedTest() override = default;

		void
			SetUp() override
		{
			SingletonManager::get_this_singleton().construct();
			SingletonManager::get_this_singleton().reset();
		}

		void
			TearDown() override
		{
			SingletonManager::get_this_singleton().destruct();
			SingletonManager::get_this_singleton().reset();
		}
	};

	struct DestructionTracker
	{
		inline static std::atomic<int> destruction_count{0};

		~DestructionTracker()
		{
			++destruction_count;
		}
	};
}

#endif
