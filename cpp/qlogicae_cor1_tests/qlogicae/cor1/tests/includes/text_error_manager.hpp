#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextErrorManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TextErrorManagerTest:
		public ::testing::TestWithParam<std::tuple<
		std::string,
		std::string,
		std::string>>
	{
	public:
		TextErrorManagerTest() = default;

		TextErrorManager
			text_error_manager;

		void
			SetUp() override
		{
			text_error_manager.construct();
			text_error_manager.reset();
		}

		void
			TearDown() override
		{
			text_error_manager.destruct();
			text_error_manager.reset();
		}
	};
}

#endif
