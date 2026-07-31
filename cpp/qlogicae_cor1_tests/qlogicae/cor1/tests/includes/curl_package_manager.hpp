#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CurlPackageManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class CurlPackageManagerTest:
		public ::testing::Test
	{
	public:
		CurlPackageManagerTest()
		{
			manager.reset();
		}

		CurlPackageManager
			manager;
	};

	class CurlPackageManagerParameterizedTest:
		public CurlPackageManagerTest,
		public ::testing::WithParamInterface<bool>
	{
	};

	class CurlPackageManagerParameterizedInvalidTest:
		public CurlPackageManagerTest,
		public ::testing::WithParamInterface<CurlPackageManagerConfigurations>
	{
	};
}

#endif
