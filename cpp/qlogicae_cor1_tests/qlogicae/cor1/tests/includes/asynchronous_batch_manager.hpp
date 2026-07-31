#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		AsynchronousBatchManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		AsynchronousBatchManagerTest:
		public ::testing::Test
	{
	public:
		AsynchronousBatchManagerTest()
		{
		}

		AsynchronousBatchManager
			asynchronous_batch_manager;

		std::unordered_map<std::string,std::function<std::any()>>
			create_single_value_batch()
		{
			std::unordered_map
				<
				std::string,
				std::function<std::any()>
				>
				values;

			values["task"] =
				[]
				()
			{
				return
					std::any(5);
			};

			return
				values;
		}

		void
			SetUp() override
		{
			asynchronous_batch_manager.construct();
		}

		void
			TearDown() override
		{
			asynchronous_batch_manager.destruct();
		}
	};

	class
		AsynchronousBatchManagerParameterizedTest:
		public
		::testing::TestWithParam<int>
	{
	public:
		AsynchronousBatchManager
			asynchronous_batch_manager;

		void
			SetUp() override
		{
			asynchronous_batch_manager.construct();
		}

		void
			TearDown() override
		{
			asynchronous_batch_manager.destruct();
		}
	};
}

#endif
