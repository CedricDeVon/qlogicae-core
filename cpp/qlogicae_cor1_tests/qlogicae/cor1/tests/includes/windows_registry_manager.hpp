#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsRegistryManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class WindowsRegistryManagerTest: public ::testing::Test
	{
	protected:
		WindowsRegistryManager manager;

		std::wstring test_sub_key;

	public:
		WindowsRegistryManagerTest()
		{
			test_sub_key = L"Software\\QLogicaeCppCoreTest_" +
				std::to_wstring(GetTickCount64());
			manager.configurations.sub_key = test_sub_key;
		}

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

	class WindowsRegistryManagerInvalidInputTest:
		public WindowsRegistryManagerTest,
		public ::testing::WithParamInterface<std::wstring>
	{
	};
}

#endif
