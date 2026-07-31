#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TextManagerTest: public ::testing::Test
	{
	public:
		TextManager manager;

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

	class TextManagerConvertTextParameterizedTest:
		public TextManagerTest,
		public ::testing::WithParamInterface<
		std::tuple<std::string,std::string,bool>>
	{
	};

	class TextManagerReplaceParameterizedTest:
		public TextManagerTest,
		public ::testing::WithParamInterface<
		std::tuple<
		std::string,
		std::unordered_map<std::string,std::string>,
		std::string>>
	{
	};

	class TextManagerSplitParameterizedTest:
		public TextManagerTest,
		public ::testing::WithParamInterface<
		std::tuple<std::string,std::string,size_t>>
	{
	};
}

#endif
