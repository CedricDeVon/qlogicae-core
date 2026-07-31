#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SodiumPackageManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	class SodiumPackageManagerTest:
		public ::testing::Test
	{
	public:
		SodiumPackageManagerTest()
		{
			manager.reset();
		}

		SodiumPackageManager
			manager;
	};

	class SodiumPackageManagerParameterizedTest:
		public SodiumPackageManagerTest,
		public ::testing::WithParamInterface<bool>
	{
	};

	class SodiumPackageManagerParameterizedInvalidTest:
		public SodiumPackageManagerTest,
		public ::testing::WithParamInterface<SodiumPackageManagerConfigurations>
	{
	};
}

#endif
