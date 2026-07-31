#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RegularExpressionManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	struct
		RegularExpressionParameters
	{
		std::string
			value;

		std::string
			pattern;

		bool
			expected_result;
	};

	struct
		UnicodePatternTestParameters
	{
		std::string
			input_value;

		std::string
			pattern;

		bool
			expected_value;
	};

	class
		RegularExpressionManagerTest:
		public ::testing::Test
	{
	public:
		RegularExpressionManagerTest() = default;

		RegularExpressionManager
			regular_expression_manager;

		void
			SetUp() override
		{
			regular_expression_manager.construct();
			regular_expression_manager.reset();
		}

		void
			TearDown() override
		{
			regular_expression_manager.destruct();
			regular_expression_manager.reset();
		}
	};

	class
		RegularExpressionManagerParameterizedTest:
		public RegularExpressionManagerTest,
		public ::testing::WithParamInterface<
		RegularExpressionParameters
		>
	{
	};

	class
		RegularExpressionManagerUnicodeParameterizedTest:
		public RegularExpressionManagerTest,
		public ::testing::WithParamInterface<
		UnicodePatternTestParameters
		>
	{
	};
}

#endif
