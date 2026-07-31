#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FunctionWrapper \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	struct NonDefaultConstructible
	{
		explicit NonDefaultConstructible(int value): value(value) {}
		int value;
	};

	struct NonDefaultReturnTest
	{
		NonDefaultConstructible run()
		{
			throw std::runtime_error("fail");
		}
	};

	struct FunctionWrapperCallSafelyTest
	{
		int add_value(int value)
		{
			return value + 1;
		}

		int throw_value(int value)
		{
			throw std::runtime_error("fail");
			return value;
		}

		int zero_arg()
		{
			return 42;
		}
	};

	class FunctionWrapperTest:
		public ::testing::Test
	{
	public:
		FunctionWrapper
			manager;

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
