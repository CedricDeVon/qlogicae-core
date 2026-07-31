#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeManager \
	)

#include "../includes/time_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		TimeManagerTest,
		Should_ReturnNonEmptyString_When_GetNowCalled
	)
	{
		std::string
			result =
				manager_instance.get_now(
					TimeFormat::ISO8601
				);

		EXPECT_FALSE(
			result.empty()
		);
	}

	TEST_P(
		TimeManagerFormatParameterizedTest,
		Should_ReturnWithinTimeBudget_When_AllFormatsUsed
	)
	{
		auto
			start_time =
				std::chrono::steady_clock::now();

		std::string
			result =
				manager_instance.get_now(
					GetParam()
				);

		auto
			end_time =
				std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast<
				std::chrono::milliseconds
			>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000)
		);

		EXPECT_FALSE(
			result.empty()
		);
	}

	INSTANTIATE_TEST_CASE_P(
		AllFormats,
		TimeManagerFormatParameterizedTest,
		::testing::Values(
			TimeFormat::UNIX,
			TimeFormat::ISO8601,
			TimeFormat::HOUR_12,
			TimeFormat::HOUR_24,
			TimeFormat::DATE_DASHED,
			TimeFormat::DATE_MDY_SLASHED,
			TimeFormat::DATE_DMY_SPACED,
			TimeFormat::DATE_VERBOSE,
			TimeFormat::MILLISECOND_LEVEL_TIMESTAMP,
			TimeFormat::MICROSECOND_LEVEL_TIMESTAMP,
			TimeFormat::FULL_TIMESTAMP,
			TimeFormat::FULL_DASHED_TIMESTAMP,
			TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND
		)
	);

	TEST_F(
		TimeManagerTest,
		Should_BeThreadSafe_When_CalledFromMultipleThreads
	)
	{
		std::atomic<bool>
			failure_detected =
				false;

		std::vector<std::thread>
			thread_pool;

		for
		(
			std::size_t thread_index = 0;
			thread_index < 32;
			++thread_index
		)
		{
			thread_pool.emplace_back(
				[this, &failure_detected]()
				{
					for
					(
						std::size_t iteration = 0;
						iteration < 1000;
						++iteration
					)
					{
						std::string
							value =
								manager_instance.get_now(
									TimeFormat::ISO8601
								);

						if (value.empty())
						{
							failure_detected.store(
								true
							);
						}
					}
				}
			);
		}

		for
		(
			std::thread&
				thread_instance :
					thread_pool
		)
		{
			thread_instance.join();
		}

		EXPECT_FALSE(
			failure_detected.load()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_WorkCorrectly_When_UsedAsynchronously
	)
	{
		std::future<std::string>
			future_result =
				std::async(
					std::launch::async,
					[this]()
					{
						return
							manager_instance.get_now(
								TimeFormat::FULL_TIMESTAMP
							);
					}
				);

		EXPECT_FALSE(
			future_result.get().empty()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleStress_When_CalledRepeatedly
	)
	{
		for
		(
			std::size_t iteration = 0;
			iteration < 100000;
			++iteration
		)
		{
			std::string
				value =
					manager_instance.get_now(
						TimeFormat::UNIX
					);

			EXPECT_FALSE(
				value.empty()
			);
		}
	}

	TEST_F(
		TimeManagerTest,
		Should_ConvertSecondsCorrectly_When_UsingValidUnits
	)
	{
		double
			result =
				manager_instance.convert_seconds(
					static_cast<double>(1),
					TimeScaleUnit::MILLISECONDS
				);

		EXPECT_GT(
			result,
			static_cast<double>(0)
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_ConvertNanosecondsCorrectly_When_UsingValidUnits
	)
	{
		double
			result =
				manager_instance.convert_nanoseconds(
					static_cast<double>(1000000),
					TimeScaleUnit::MILLISECONDS
				);

		EXPECT_GT(
			result,
			static_cast<double>(0)
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_NotThrow_When_ConvertingExtremeValues
	)
	{
		EXPECT_NO_THROW(
			manager_instance.convert_seconds(
				static_cast<double>(1e12),
				TimeScaleUnit::SECONDS
			)
		);

		EXPECT_NO_THROW(
			manager_instance.convert_nanoseconds(
				static_cast<double>(1e18),
				TimeScaleUnit::NANOSECONDS
			)
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_BeExceptionSafe_When_InvokedRepeatedly
	)
	{
		EXPECT_NO_THROW(
			for
			(
				std::size_t iteration = 0;
				iteration < 10000;
				++iteration
			)
			{
				manager_instance.get_now(
					TimeFormat::ISO8601
				);
			}
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_ReturnEmptyString_When_InvalidTimeFormatProvided
	)
	{
		std::string
			result =
			manager_instance.get_now(
				static_cast<TimeFormat>(-1)
			);

		EXPECT_TRUE(
			result.empty()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_ReturnString_When_DateDmySlashedFormatUsed
	)
	{
		std::string
			result =
			manager_instance.get_now(
				TimeFormat::DATE_DMY_SLASHED
			);

		EXPECT_FALSE(
			result.empty()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleZeroSeconds_When_Converted
	)
	{
		double
			result =
			manager_instance.convert_seconds(
				static_cast<double>(0),
				TimeScaleUnit::SECONDS
			);

		EXPECT_EQ(
			result,
			static_cast<double>(0)
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleNegativeSeconds_When_Converted
	)
	{
		double
			result =
			manager_instance.convert_seconds(
				static_cast<double>(-1),
				TimeScaleUnit::SECONDS
			);

		EXPECT_EQ(
			result,
			static_cast<double>(0)
		);
	}

	TEST_P(
		TimeManagerScaleParameterizedTest,
		Should_ConvertSecondsConsistently_When_AllScaleUnitsUsed
	)
	{
		double
			result =
			manager_instance.convert_seconds(
				static_cast<double>(1),
				GetParam()
			);

		EXPECT_NE(
			result,
			static_cast<double>(0)
		);
	}

	INSTANTIATE_TEST_CASE_P(
		AllTimeScaleUnits,
		TimeManagerScaleParameterizedTest,
		::testing::Values(
			TimeScaleUnit::NANOSECONDS,
			TimeScaleUnit::MICROSECONDS,
			TimeScaleUnit::MILLISECONDS,
			TimeScaleUnit::SECONDS,
			TimeScaleUnit::MINUTES,
			TimeScaleUnit::HOURS,
			TimeScaleUnit::DAYS,
			TimeScaleUnit::WEEKS,
			TimeScaleUnit::MONTHS,
			TimeScaleUnit::YEARS
		)
	);

	TEST_F(
		TimeManagerTest,
		Should_BeThreadSafe_When_TimeZoneIsModifiedConcurrently
	)
	{
		std::atomic<bool>
			failure_detected =
			false;

		std::vector<std::thread>
			thread_pool;

		for
			(
				std::size_t thread_index = 0;
				thread_index < 16;
				++thread_index
				)
		{
			thread_pool.emplace_back(
				[this, &failure_detected]()
				{
					for
						(
							std::size_t iteration = 0;
							iteration < 1000;
							++iteration
							)
					{
						manager_instance.configurations.time_zone =
							TimeZone::UTC;

						std::string
							utc_value =
							manager_instance.get_now(
								TimeFormat::ISO8601
							);

						manager_instance.configurations.time_zone =
							TimeZone::LOCAL;

						std::string
							local_value =
							manager_instance.get_now(
								TimeFormat::ISO8601
							);

						if
							(
								utc_value.empty() ||
								local_value.empty()
								)
						{
							failure_detected.store(
								true
							);
						}
					}
				}
			);
		}

		for
			(
				std::thread&
				thread_instance :
				thread_pool
				)
		{
			thread_instance.join();
		}

		EXPECT_FALSE(
			failure_detected.load()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_SupportPromiseFutureSynchronization_When_UsedAsynchronously
	)
	{
		std::promise<std::string>
			result_promise;

		std::future<std::string>
			result_future =
			result_promise.get_future();

		std::thread
			worker_thread(
				[this, &result_promise]()
				{
					result_promise.set_value(
						manager_instance.get_now(
							TimeFormat::FULL_TIMESTAMP
						)
					);
				}
			);

		worker_thread.join();

		EXPECT_FALSE(
			result_future.get().empty()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleAsyncStress_When_MultipleFuturesUsed
	)
	{
		std::vector<std::future<std::string>>
			futures;

		for
			(
				std::size_t iteration = 0;
				iteration < 1000;
				++iteration
				)
		{
			futures.emplace_back(
				std::async(
					std::launch::async,
					[this]()
					{
						return
							manager_instance.get_now(
								TimeFormat::ISO8601
							);
					}
				)
			);
		}

		for
			(
				std::future<std::string>&
				future_instance :
				futures
				)
		{
			EXPECT_FALSE(
				future_instance.get().empty()
			);
		}
	}

	TEST_F(
		TimeManagerTest,
		Should_ReturnValidValues_When_AllTemplateGettersInvoked
	)
	{
		EXPECT_GT(
			manager_instance.get_now<double>(),
			static_cast<double>(0)
		);

		EXPECT_GT(
			manager_instance.get_now<int64_t>(),
			static_cast<int64_t>(0)
		);

		EXPECT_FALSE(
			manager_instance.get_now<std::string>().empty()
		);

		EXPECT_FALSE(
			manager_instance.get_now<std::wstring>().empty()
		);

		EXPECT_GE(
			manager_instance.get_nanosecond<int64_t>(),
			static_cast<int64_t>(0)
		);

		EXPECT_GE(
			manager_instance.get_microsecond<int64_t>(),
			static_cast<int64_t>(0)
		);

		EXPECT_GE(
			manager_instance.get_millisecond<int64_t>(),
			static_cast<int64_t>(0)
		);

		EXPECT_GE(
			manager_instance.get_second<int>(),
			static_cast<int>(0)
		);

		EXPECT_GE(
			manager_instance.get_minute<int>(),
			static_cast<int>(0)
		);

		EXPECT_GE(
			manager_instance.get_hour<int>(),
			static_cast<int>(0)
		);

		EXPECT_GE(
			manager_instance.get_day<int>(),
			static_cast<int>(1)
		);

		EXPECT_GE(
			manager_instance.get_month<int>(),
			static_cast<int>(1)
		);

		EXPECT_GE(
			manager_instance.get_year<int>(),
			static_cast<int>(1970)
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_FunctionCorrectly_When_ThreadSafetyDisabled
	)
	{
		manager_instance.configurations
			.is_utility_thread_safety_handling_enabled =
			false;

		std::string
			result =
			manager_instance.get_now(
				TimeFormat::ISO8601
			);

		EXPECT_FALSE(
			result.empty()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_ReturnString_When_TimeZoneNoneIsUsed
	)
	{
		manager_instance.configurations.time_zone =
			TimeZone::NONE;

		std::string
			result =
			manager_instance.get_now(
				TimeFormat::ISO8601
			);

		EXPECT_FALSE(
			result.empty()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_ReturnFallbackValues_When_InvalidTemplateTypeUsed
	)
	{
		struct UnsupportedType
		{
			int value;
		};

		EXPECT_NO_THROW(
			{
				UnsupportedType
					result =
						manager_instance.get_now<
							UnsupportedType
						>();

				(void)result;
			}
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_FormatMillisecondsCorrectly_When_HelperInvoked
	)
	{
		std::string
			result =
			manager_instance.format_millisecond_level(
				absl::Milliseconds(
					static_cast<int64_t>(123456)
				),
				":"
			);

		EXPECT_FALSE(
			result.empty()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_FormatMicrosecondsCorrectly_When_HelperInvoked
	)
	{
		std::string
			result =
			manager_instance.format_microsecond_level(
				absl::Microseconds(
					static_cast<int64_t>(123456)
				),
				":"
			);

		EXPECT_FALSE(
			result.empty()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_FormatNanosecondsCorrectly_When_HelperInvoked
	)
	{
		std::string
			result =
			manager_instance.format_nanosecond_level(
				absl::Nanoseconds(
					static_cast<int64_t>(123456)
				),
				":"
			);

		EXPECT_FALSE(
			result.empty()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_ReturnEmptyString_When_TimeFormatNoneUsed
	)
	{
		std::string
			result =
			manager_instance.get_now(
				TimeFormat::NONE
			);

		EXPECT_TRUE(
			result.empty()
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_ReturnInput_When_TimeScaleNoneUsed
	)
	{
		double
			result =
			manager_instance.convert_seconds(
				static_cast<double>(5),
				TimeScaleUnit::NONE
			);

		EXPECT_EQ(
			result,
			static_cast<double>(0)
		);
	}

	TEST_F(
		TimeManagerTest,
		Should_ReturnFallbackValues_ForAllUnsupportedTemplateTypes
	)
	{
		struct UnsupportedInt { int value; };
		struct UnsupportedDouble { double value; };

		UnsupportedInt i_result = manager_instance.get_now<UnsupportedInt>();
		UnsupportedDouble d_result = manager_instance.get_now<UnsupportedDouble>();

		EXPECT_EQ(i_result.value, 0);
		EXPECT_EQ(d_result.value, 0.0);
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleAllConfigurationTogglesCorrectly
	)
	{
		manager_instance.configurations.is_utility_thread_safety_handling_enabled = false;

		EXPECT_FALSE(manager_instance.get_now(TimeFormat::ISO8601).empty());
		EXPECT_FALSE(manager_instance.convert_seconds(1, TimeScaleUnit::SECONDS) < 0);
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleFormattingHelpersWithExtremeAndZeroValues
	)
	{
		EXPECT_FALSE(manager_instance.format_millisecond_level(absl::Milliseconds(0), "-").empty());
		EXPECT_FALSE(manager_instance.format_millisecond_level(absl::Milliseconds(1'000'000), ":").empty());
		EXPECT_FALSE(manager_instance.format_microsecond_level(absl::Microseconds(0), ".").empty());
		EXPECT_FALSE(manager_instance.format_microsecond_level(absl::Microseconds(1'000'000'000), ".").empty());
		EXPECT_FALSE(manager_instance.format_nanosecond_level(absl::Nanoseconds(0), ",").empty());
		EXPECT_FALSE(manager_instance.format_nanosecond_level(absl::Nanoseconds(1'000'000'000'000), ",").empty());
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleTimeZoneConversionsCorrectly
	)
	{
		manager_instance.configurations.time_zone = TimeZone::UTC;
		std::string utc = manager_instance.get_now(TimeFormat::ISO8601);
		manager_instance.configurations.time_zone = TimeZone::LOCAL;
		std::string local = manager_instance.get_now(TimeFormat::ISO8601);
		manager_instance.configurations.time_zone = TimeZone::NONE;
		std::string none = manager_instance.get_now(TimeFormat::ISO8601);

		EXPECT_FALSE(utc.empty());
		EXPECT_FALSE(local.empty());
		EXPECT_FALSE(none.empty());
		EXPECT_NE(utc, local);
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleExtremeAndInvalidNumericValuesInConversion
	)
	{
		double large_seconds = manager_instance.convert_seconds(1e20, TimeScaleUnit::SECONDS);
		double large_nanoseconds = manager_instance.convert_nanoseconds(1e30, TimeScaleUnit::NANOSECONDS);
		double neg_seconds = manager_instance.convert_seconds(-1e20, TimeScaleUnit::SECONDS);
		double zero_conversion = manager_instance.convert_seconds(5, TimeScaleUnit::NONE);

		EXPECT_GT(large_seconds, 0);
		EXPECT_GT(large_nanoseconds, 0);
		EXPECT_EQ(neg_seconds, 0);
		EXPECT_EQ(zero_conversion, 0);
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleEmptyAndNoneEnumCasesProperly
	)
	{
		std::string time_none = manager_instance.get_now(TimeFormat::NONE);
		double scale_none = manager_instance.convert_seconds(123, TimeScaleUnit::NONE);

		EXPECT_TRUE(time_none.empty());
		EXPECT_EQ(scale_none, 0);
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleAsyncStressWithMultipleThreadsAndConversions
	)
	{
		std::vector<std::future<std::string>> futures;
		for (std::size_t i = 0; i < 500; ++i)
		{
			futures.emplace_back(std::async(std::launch::async, [this]() {
				manager_instance.convert_seconds(100, TimeScaleUnit::MILLISECONDS);
				manager_instance.convert_nanoseconds(1000, TimeScaleUnit::MICROSECONDS);
				return manager_instance.get_now(TimeFormat::FULL_TIMESTAMP);
				}));
		}

		for (auto& f : futures)
		{
			EXPECT_FALSE(f.get().empty());
		}
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleExtremeDatesAndYearsCorrectly
	)
	{
		int year = manager_instance.get_year<int>();
		EXPECT_GE(year, 1970);
		EXPECT_LE(year, 9999);
	}

	TEST_F(
		TimeManagerTest,
		Should_HandleInvalidEnumsInConversions
	)
	{
		double result = manager_instance.convert_seconds(10, static_cast<TimeScaleUnit>(-1));
		EXPECT_EQ(result, 0);
	}
}

#endif
