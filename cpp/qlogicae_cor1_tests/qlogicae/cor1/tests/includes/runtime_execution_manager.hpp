#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RuntimeExecutionManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class RuntimeExecutionManagerTest: public ::testing::Test
	{
	public:
		RuntimeExecutionManager
			manager_instance;

		void
			SetUp() override
		{
			manager_instance.construct();
			manager_instance.reset();
		}

		void
			TearDown() override
		{
			manager_instance.destruct();
			manager_instance.reset();
		}
	};

	class RuntimeExecutionManagerParameterizedTest:
		public RuntimeExecutionManagerTest,
		public ::testing::WithParamInterface<double>
	{
	};
}

#endif
