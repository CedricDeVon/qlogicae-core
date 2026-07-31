#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RuntimeExecutionManager \
	)

#include "../includes/runtime_execution_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
    TEST_F(RuntimeExecutionManagerTest, Should_CalibrateSuccessfully_When_Called)
    {
        ASSERT_TRUE(manager_instance.calibrate());
        ASSERT_GT(manager_instance.cycles_per_microsecond, 0.0);
        ASSERT_TRUE(manager_instance.is_calibrated.load());
    }

    TEST_F(RuntimeExecutionManagerTest, Should_DelayExecutionInMicrosecondsSuccessfully_When_ValidValueProvided)
    {
        ASSERT_TRUE(manager_instance.delay_execution_in_microseconds(100.0));
    }

    TEST_F(RuntimeExecutionManagerTest, Should_ReturnFalse_When_DelayExecutionInMicrosecondsInvalid)
    {
        ASSERT_FALSE(manager_instance.delay_execution_in_microseconds(-10.0));
        ASSERT_FALSE(manager_instance.delay_execution_in_microseconds(1e13));
    }

    TEST_F(RuntimeExecutionManagerTest, Should_DelayExecutionInNanosecondsSuccessfully_When_ValidValueProvided)
    {
        ASSERT_TRUE(manager_instance.delay_execution_in_nanoseconds(10'000.0));
    }

    TEST_F(RuntimeExecutionManagerTest, Should_DelayExecutionThroughAllUnits_When_Called)
    {
		std::vector<std::pair<TimeScaleUnit, double>> units
		{
			{TimeScaleUnit::YEARS, 1.0 / 365.25 / 24.0 / 60.0 / 60.0 / 1000.0},
			{TimeScaleUnit::MONTHS, 1.0 / 30.44 / 24.0 / 60.0 / 60.0 / 1000.0},
			{TimeScaleUnit::WEEKS, 1.0 / 7.0 / 24.0 / 60.0 / 60.0 / 1000.0},
			{TimeScaleUnit::DAYS, 1.0 / 24.0 / 60.0 / 60.0 / 1000.0},
			{TimeScaleUnit::HOURS, 1.0 / 60.0 / 60.0 / 1000.0},
			{TimeScaleUnit::MINUTES, 1.0 / 60.0 / 1000.0},
			{TimeScaleUnit::SECONDS, 1.0 / 1000.0},
			{TimeScaleUnit::MILLISECONDS, 1.0},
			{TimeScaleUnit::MICROSECONDS, 1'000.0},
			{TimeScaleUnit::NANOSECONDS, 1'000'000.0}
		};

        for (const auto& [unit, value] : units)
        {
            ASSERT_TRUE(manager_instance.delay_execution(value, unit));
        }
    }

    TEST_F(RuntimeExecutionManagerTest, Should_ReturnFalseRealTimeStampCounter_When_InvalidValueProvided)
    {
        ASSERT_FALSE(manager_instance.real_time_stamp_counter(-1.0));
        ASSERT_FALSE(manager_instance.real_time_stamp_counter(1e13));
    }

    TEST_F(RuntimeExecutionManagerTest, Should_QueryPerformanceCounterSuccessfully_When_ValidValueProvided)
    {
        ASSERT_TRUE(manager_instance.query_performance_counter(10.0));
    }

    TEST_F(RuntimeExecutionManagerTest, Should_ReturnFalseQueryPerformanceCounter_When_InvalidValueProvided)
    {
        ASSERT_FALSE(manager_instance.query_performance_counter(-1.0));
        ASSERT_FALSE(manager_instance.query_performance_counter(1e13));
    }

    TEST_F(RuntimeExecutionManagerTest, Should_BeThreadSafe_When_MultipleThreadsCalibrate)
    {
        std::vector<std::thread> thread_pool;
        for (int i = 0; i < 8; ++i)
        {
            thread_pool.emplace_back([this]()
            {
                ASSERT_TRUE(manager_instance.calibrate());
            });
        }

        for (auto& thread : thread_pool)
        {
            thread.join();
        }
    }

    TEST_F(RuntimeExecutionManagerTest, Should_BeAsynchronous_When_CalibrationUsingAsync)
    {
        auto future_result = std::async(std::launch::async, [this]()
        {
            return manager_instance.calibrate();
        });

        ASSERT_TRUE(future_result.get());
    }

    TEST_F(RuntimeExecutionManagerTest, Should_HandleExceptionsGracefully_When_InvalidDelayValue)
    {
        ASSERT_NO_THROW(manager_instance.delay_execution_in_microseconds(-50.0));
        ASSERT_NO_THROW(manager_instance.delay_execution_in_nanoseconds(-10.0));
        ASSERT_NO_THROW(manager_instance.real_time_stamp_counter(-100.0));
        ASSERT_NO_THROW(manager_instance.query_performance_counter(-1000.0));
    }

    TEST_F(RuntimeExecutionManagerTest, Should_HandleExtremeEdgeCases_When_Called)
    {
        ASSERT_FALSE(manager_instance.delay_execution_in_microseconds(0.0));
        ASSERT_FALSE(manager_instance.delay_execution_in_microseconds(1e13));
        ASSERT_FALSE(manager_instance.real_time_stamp_counter(0.0));
        ASSERT_FALSE(manager_instance.query_performance_counter(0.0));
    }

    INSTANTIATE_TEST_CASE_P(
        RuntimeExecutionManagerParameterizedDelayTests,
        RuntimeExecutionManagerParameterizedTest,
        ::testing::Values(
            0.001,
            0.1,
            1.0,
            10.0,
            100.0,
            1'000.0
        )
    );

    TEST_P(RuntimeExecutionManagerParameterizedTest, Should_DelayExecutionInMicrosecondsSuccessfully_When_ParameterProvided)
    {
        double delay_value = GetParam();
        ASSERT_TRUE(manager_instance.delay_execution_in_microseconds(delay_value));
    }

    TEST_F(RuntimeExecutionManagerTest, Should_HandleStressTest_When_HighFrequencyCalibrate)
    {
        for (int i = 0; i < 100; ++i)
        {
            ASSERT_TRUE(manager_instance.calibrate());
        }
    }

	TEST_F(RuntimeExecutionManagerTest, Should_HandleAsynchronousDelayExecutionSuccessfully_When_Called)
	{
		auto future_result_microseconds = std::async(std::launch::async, [this]()
		{
			return manager_instance.delay_execution_in_microseconds(100.0);
		});

		auto future_result_nanoseconds = std::async(std::launch::async, [this]()
		{
			return manager_instance.delay_execution_in_nanoseconds(10'000.0);
		});

		ASSERT_TRUE(future_result_microseconds.get());
		ASSERT_TRUE(future_result_nanoseconds.get());
	}

	TEST_F(RuntimeExecutionManagerTest, Should_BeThreadSafeForDelayExecution_When_MultipleThreadsCalled)
	{
		std::vector<std::thread> thread_pool;
		for (int i = 0; i < 8; ++i)
		{
			thread_pool.emplace_back([this]()
			{
				ASSERT_TRUE(manager_instance.delay_execution_in_microseconds(100.0));
				ASSERT_TRUE(manager_instance.delay_execution_in_nanoseconds(10'000.0));
			});
		}

		for (auto& thread : thread_pool)
		{
			thread.join();
		}
	}

	TEST_F(RuntimeExecutionManagerTest, Should_ReturnFalseDelayExecutionInMilliseconds_When_ZeroOrNegative)
	{
		ASSERT_FALSE(manager_instance.delay_execution_in_milliseconds(0.0));
		ASSERT_FALSE(manager_instance.delay_execution_in_milliseconds(-1.0));
	}

	TEST_F(RuntimeExecutionManagerTest, Should_ReturnFalseDelayExecutionInSeconds_When_ZeroOrNegative)
	{
		ASSERT_FALSE(manager_instance.delay_execution_in_seconds(0.0));
		ASSERT_FALSE(manager_instance.delay_execution_in_seconds(-1.0));
	}

	/*
	TEST_F(RuntimeExecutionManagerTest, Should_UseRealTimeStampCounterSuccessfully_When_ValidValueProvided)
	{
		ASSERT_TRUE(manager_instance.real_time_stamp_counter(10.0));
	}
	*/

}

#endif
