#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		GmailApiManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		GmailApiManagerTest:
		public ::testing::Test
	{
	public:
		GmailApiManagerTest()
		{

		}

		GmailApiManager
			manager;

		GmailApiManagerConfigurations
			valid_configurations;
	};

	class
		GmailApiManagerParameterizedInvalidTest:
		public GmailApiManagerTest,
		public ::testing::WithParamInterface<std::string>
	{
	};
}

#endif
