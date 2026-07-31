#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextEncodingManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TextEncodingManagerTest: public ::testing::Test
	{
	public:
		TextEncodingManager encoding_manager;

		void
			SetUp() override
		{
			encoding_manager.construct();
			encoding_manager.reset();
		}

		void
			TearDown() override
		{
			encoding_manager.destruct();
			encoding_manager.reset();
		}
	};

	class TextEncodingManagerParameterizedTest:
		public TextEncodingManagerTest,
		public ::testing::WithParamInterface<std::tuple<std::string,
		TextEncoding,TextEncoding,std::string>>
	{
	};
}

#endif
