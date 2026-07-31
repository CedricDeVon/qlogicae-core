#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsRegistryRootPathEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class WindowsRegistryRootPathEnumManagerTest:
		public ::testing::Test
	{
	public:
		WindowsRegistryRootPathEnumManager manager;

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

	class WindowsRegistryRootPathEnumManagerParameterizedTest:
		public WindowsRegistryRootPathEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,WindowsRegistryRootPath>>
	{
	};

	class WindowsRegistryRootPathEnumManagerEnumToStringParameterizedTest:
		public WindowsRegistryRootPathEnumManagerTest,
		public ::testing::WithParamInterface<WindowsRegistryRootPath>
	{
	};
}

#endif
