#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextEncodingEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TextEncodingEnumManagerTest:
		public ::testing::Test
	{
	public:
		TextEncodingEnumManager manager;

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

	class TextEncodingEnumManagerParameterizedTest:
		public TextEncodingEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,TextEncoding>>
	{
	};

	class TextEncodingEnumManagerEnumToStringParameterizedTest:
		public TextEncodingEnumManagerTest,
		public ::testing::WithParamInterface<TextEncoding>
	{
	};
}

#endif
