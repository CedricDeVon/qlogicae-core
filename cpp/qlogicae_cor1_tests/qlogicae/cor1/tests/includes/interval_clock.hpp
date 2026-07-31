#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		IntervalClock \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class IntervalClockTest: public ::testing::Test
	{
	public:
		std::unique_ptr<IntervalClock> manager_instance;

		IntervalClockTest():
			manager_instance(std::make_unique<IntervalClock>())
		{
		}

		void SetUp() override
		{
			if(manager_instance->is_running() || manager_instance->thread_1.joinable())
			{
				manager_instance->cancel();
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
			}
			manager_instance->construct();
			manager_instance->reset();
		}

		void TearDown() override
		{
			if(manager_instance->is_running() || manager_instance->thread_1.joinable())
			{
				manager_instance->cancel();
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
			}
			manager_instance->destruct();
			manager_instance->reset();
		}
	};

	class IntervalClockParameterizedTest:
		public IntervalClockTest,
		public ::testing::WithParamInterface<size_t>
	{
	};
}

#endif
