#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ResultsStatusEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	class ResultsStatusEnumManagerTest:
		public ::testing::Test
	{
	public:
		ResultsStatusEnumManager manager;

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

	class ResultsStatusEnumManagerParameterizedTest:
		public ResultsStatusEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,ResultsStatus>>
	{
	};

	class ResultsStatusEnumManagerEnumToStringParameterizedTest:
		public ResultsStatusEnumManagerTest,
		public ::testing::WithParamInterface<ResultsStatus>
	{
	};
}

#endif
