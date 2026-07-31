#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextLogManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TextLogManagerTest:
		public ::testing::Test
	{
	public:
		TextLogManagerTest()
		{
		}

		TextLogManager text_log_manager_instance;
	};

	class TextLogManagerParameterizedTest:
		public TextLogManagerTest,
		public ::testing::WithParamInterface<LogFormat>
	{
	public:
		TextLogManagerParameterizedTest()
		{
		}
	};

	class TextLogManagerTimeFormatTest: public TextLogManagerTest,
		public ::testing::WithParamInterface<TimeFormat>
	{
	public:
		TextLogManagerTimeFormatTest() {}
	};
}

#endif
