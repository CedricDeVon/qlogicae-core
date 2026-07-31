#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextPlaceholderManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TextPlaceholderManagerTest: public ::testing::Test
	{
	public:
		TextPlaceholderManager manager;

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

	class TextPlaceholderManagerParameterizedTest:
		public TextPlaceholderManagerTest,
		public ::testing::WithParamInterface<std::tuple<std::string,std::string,bool,bool>>
	{
	};
}

#endif
