#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EmailSecurityEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class EmailSecurityEnumManagerTest:
		public ::testing::Test
	{
	public:
		EmailSecurityEnumManager manager;

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

	class EmailSecurityEnumManagerParameterizedTest:
		public EmailSecurityEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,EmailSecurity>>
	{
	};

	class EmailSecurityEnumManagerEnumToStringParameterizedTest:
		public EmailSecurityEnumManagerTest,
		public ::testing::WithParamInterface<EmailSecurity>
	{
	};
}

#endif
