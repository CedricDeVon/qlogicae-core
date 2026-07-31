#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsEnvironmentVariableEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class WindowsEnvironmentVariableEnumManagerTest:
		public ::testing::Test
	{
	public:
		WindowsEnvironmentVariableEnumManager manager;

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

	class WindowsEnvironmentVariableEnumManagerParameterizedTest:
		public WindowsEnvironmentVariableEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,WindowsEnvironmentVariable>>
	{
	};

	class WindowsEnvironmentVariableEnumManagerEnumToStringParameterizedTest:
		public WindowsEnvironmentVariableEnumManagerTest,
		public ::testing::WithParamInterface<WindowsEnvironmentVariable>
	{
	};
}

#endif
