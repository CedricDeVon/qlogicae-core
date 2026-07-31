#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsEnvironmentVariableManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		WindowsEnvironmentVariableManagerTest:
		public ::testing::Test
	{
	public:
		WindowsEnvironmentVariableManager
			manager;

		void
			SetUp()
		{
			manager.construct();
			manager.reset();
		}

		void
			TearDown()
		{
			manager.destruct();
			manager.reset();
		}
	};

	class
		WindowsEnvironmentVariableManagerParameterizedTest:
		public WindowsEnvironmentVariableManagerTest,
		public ::testing::WithParamInterface<
		std::wstring
		>
	{
	};
}

#endif
