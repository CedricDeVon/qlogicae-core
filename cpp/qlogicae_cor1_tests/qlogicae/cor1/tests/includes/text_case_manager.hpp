#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextCaseManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		TextCaseManagerTest:
		public ::testing::Test
	{
	public:
		TextCaseManager
			manager;

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

	class
		TextCaseManagerParameterizedTest:
		public TextCaseManagerTest,
		public ::testing::WithParamInterface<
		std::pair<std::string,TextCase>>
	{
	};

	class TextCaseManagerEmptyParameterizedTest:
		public TextCaseManagerTest,
		public ::testing::WithParamInterface<TextCase>
	{
	};
}

#endif
