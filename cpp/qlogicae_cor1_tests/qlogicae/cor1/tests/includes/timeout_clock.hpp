#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeoutClock \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class TimeoutClockTest: public ::testing::Test
	{
	public:
		std::unique_ptr<TimeoutClock> timeout_clock_instance;

		TimeoutClockTest():
			timeout_clock_instance(std::make_unique<TimeoutClock>())
		{
		}

		void SetUp() override
		{
			timeout_clock_instance->cancel();
			timeout_clock_instance->construct();
			timeout_clock_instance->reset();
		}

		void TearDown() override
		{
			timeout_clock_instance->cancel();
			timeout_clock_instance->destruct();
			timeout_clock_instance->reset();
		}
	};

	class TimeoutClockParameterizedTest:
		public TimeoutClockTest,
		public ::testing::WithParamInterface<int>
	{
	};

	class TimeoutClockImmediateExecutionTest: public TimeoutClockTest
	{
	};

	class TimeoutClockFlagParameterizedTest:
		public TimeoutClockTest,
		public ::testing::WithParamInterface<bool>
	{
	};
}

#endif
