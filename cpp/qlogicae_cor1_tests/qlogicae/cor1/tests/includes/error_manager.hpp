#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ErrorManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class ErrorManagerTest:
		public ::testing::Test
	{
	public:
		ErrorManager manager;

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

	class ErrorManagerParameterizedTest:
		public ::testing::TestWithParam<bool>
	{
	public:
		ErrorManager manager;

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

	class ErrorManagerConfigurationMatrixTest:
		public ::testing::TestWithParam<
		std::tuple<bool,bool>
		>
	{
	public:
		ErrorManager manager;

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

	class ErrorManagerFullParameterizedTest:
		public ::testing::TestWithParam<std::tuple<
		bool,
		bool,
		bool,
		bool,
		bool,
		bool
		>>
	{
	public:
		ErrorManager manager;

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
