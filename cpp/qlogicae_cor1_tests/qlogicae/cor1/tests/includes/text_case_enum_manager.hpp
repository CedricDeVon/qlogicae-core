#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextCaseEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TextCaseEnumManagerTest:
		public ::testing::Test
	{
	public:
		TextCaseEnumManager manager;

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

	class TextCaseEnumManagerParameterizedTest:
		public TextCaseEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,TextCase>>
	{
	};

	class TextCaseEnumManagerEnumToStringParameterizedTest:
		public TextCaseEnumManagerTest,
		public ::testing::WithParamInterface<TextCase>
	{
	};
}

#endif
