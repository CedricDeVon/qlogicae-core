#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		AsynchronousManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class AsynchronousManagerTest:
		public ::testing::Test
	{
	public:
		AsynchronousManager
			manager;

		void
			SetUp() override
		{
			manager.construct();
		}

		void
			TearDown() override
		{
			manager.destruct();
		}
	};

	class AsynchronousManagerConfigurationTest:
		public ::testing::TestWithParam<bool>
	{
	public:
		AsynchronousManager
			manager;

		void
			SetUp() override
		{
			manager.construct();
		}

		void
			TearDown() override
		{
			manager.destruct();
		}
	};
}

#endif
