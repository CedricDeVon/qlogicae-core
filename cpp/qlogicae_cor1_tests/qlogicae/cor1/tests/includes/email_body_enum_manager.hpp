#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EmailBodyEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class EmailBodyEnumManagerTest:
		public ::testing::Test
	{
	public:
		EmailBodyEnumManager manager;

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

	class EmailBodyEnumManagerParameterizedTest:
		public EmailBodyEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,EmailBody>>
	{
	};

	class EmailBodyEnumManagerEnumToStringParameterizedTest:
		public EmailBodyEnumManagerTest,
		public ::testing::WithParamInterface<EmailBody>
	{
	};
}

#endif
