#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomValueGenerationManager \
	)

#include "../includes/random_value_generation_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(RandomValueGenerationManagerTest,
		Should_GenerateNonEmptySalt_When_Called)
	{
		std::array<unsigned char, 16>
			result =
				random_value_manager_instance
					.generate_random_salt();

		EXPECT_FALSE(
			std::all_of(
				result.begin(),
				result.end(),
				[](unsigned char value) { return value == 0; }
			)
		);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_ReturnFalse_When_BufferIsNull)
	{
		bool
			result =
				random_value_manager_instance
					.generate_random_bytes(
						nullptr,
						10
					);

		EXPECT_FALSE(result);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_ReturnFalse_WhenSizeIsZero)
	{
		std::vector<unsigned char>
			buffer(10);

		bool
			result =
				random_value_manager_instance
					.generate_random_bytes(
						buffer.data(),
						0
					);

		EXPECT_FALSE(result);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_FillBufferWithRandomBytes_When_ValidInput)
	{
		std::vector<unsigned char>
			buffer(32, 0);

		bool
			result =
				random_value_manager_instance
					.generate_random_bytes(
						buffer.data(),
						buffer.size()
					);

		EXPECT_TRUE(result);
		EXPECT_FALSE(
			std::all_of(
				buffer.begin(),
				buffer.end(),
				[](unsigned char value) { return value == 0; }
			)
		);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_BeThreadSafe_When_MultipleThreadsGenerateSalt)
	{
		std::vector<std::thread>
			threads;
		std::vector<std::array<unsigned char, 16>>
			results(16);

		for (int index = 0; index < 16; ++index)
		{
			threads.emplace_back([&results, index, this]()
			{
				results[index] =
					random_value_manager_instance
						.generate_random_salt();
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		for (auto& array_result : results)
		{
			EXPECT_FALSE(
				std::all_of(
					array_result.begin(),
					array_result.end(),
					[](unsigned char value) { return value == 0; }
				)
			);
		}
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_GenerateRandomBytes_Asynchronously_When_ValidInput)
	{
		std::vector<unsigned char>
			buffer(64, 0);

		auto
			future_result =
				std::async(
					std::launch::async,
					[this, &buffer]()
					{
						return random_value_manager_instance
							.generate_random_bytes(
								buffer.data(),
								buffer.size()
							);
					}
				);

		EXPECT_TRUE(future_result.get());
		EXPECT_FALSE(
			std::all_of(
				buffer.begin(),
				buffer.end(),
				[](unsigned char value) { return value == 0; }
			)
		);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_HandleEmptySaltGeneration_When_ForcedEdgeCase)
	{
		random_value_manager_instance.configurations
			.is_feature_edge_case_handling_enabled = true;

		std::array<unsigned char, 16>
			result =
				random_value_manager_instance
					.generate_random_salt();

		EXPECT_TRUE(result.empty() == false);
	}

	TEST_P(RandomValueGenerationManagerParameterizedTest,
		Should_GenerateRandomBytes_ForVariousSizes)
	{
		size_t
			size = GetParam();

		std::vector<unsigned char>
			buffer(size, 0);

		bool
			result =
				random_value_manager_instance
					.generate_random_bytes(
						buffer.data(),
						buffer.size()
					);

		if (size != 0)
		{
			EXPECT_TRUE(result);
		}
		else
		{
			EXPECT_FALSE(result);
		}
	}

	INSTANTIATE_TEST_CASE_P(
		VariousSizes,
		RandomValueGenerationManagerParameterizedTest,
		::testing::Values(
			0,
			1,
			16,
			32,
			64,
			128,
			256,
			512
		)
	);

	TEST_F(RandomValueGenerationManagerTest,
		Should_CompleteStressTest_UnderConcurrency)
	{
		std::vector<std::thread>
			threads;
		std::atomic<int>
			counter{0};

		for (int index = 0; index < 64; ++index)
		{
			threads.emplace_back([this, &counter]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					std::array<unsigned char, 16>
						result =
							random_value_manager_instance
								.generate_random_salt();
					if (!std::all_of(result.begin(), result.end(),
						[](unsigned char value) { return value == 0; }))
					{
						counter.fetch_add(1, std::memory_order_relaxed);
					}
				}
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		EXPECT_EQ(counter, 64 * 1000);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_GenerateRandomBytesWithPromise_When_ValidInput)
	{
		std::vector<unsigned char>
			buffer(64, 0);

		std::promise<bool>
			promise_result;
		std::future<bool>
			future_result = promise_result.get_future();

		std::thread(
			[this, &buffer, &promise_result]()
			{
				bool
					result =
						random_value_manager_instance
							.generate_random_bytes(
								buffer.data(),
								buffer.size()
							);
				promise_result.set_value(result);
			}
		).detach();

		EXPECT_TRUE(future_result.get());
		EXPECT_FALSE(
			std::all_of(
				buffer.begin(),
				buffer.end(),
				[](unsigned char value) { return value == 0; }
			)
		);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_GenerateRandomSaltWithPromise_When_Called)
	{
		std::promise<std::array<unsigned char, 16>>
			promise_salt;
		std::future<std::array<unsigned char, 16>>
			future_salt = promise_salt.get_future();

		std::thread(
			[this, &promise_salt]()
			{
				std::array<unsigned char, 16>
					result =
						random_value_manager_instance
							.generate_random_salt();
				promise_salt.set_value(result);
			}
		).detach();

		std::array<unsigned char, 16>
			result = future_salt.get();

		EXPECT_FALSE(
			std::all_of(
				result.begin(),
				result.end(),
				[](unsigned char value) { return value == 0; }
			)
		);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_BeThreadSafeUnderConcurrentByteGeneration)
	{
		std::vector<std::thread>
			threads;
		std::atomic<int>
			counter{0};

		for (int index = 0; index < 32; ++index)
		{
			threads.emplace_back([this, &counter]()
			{
				for (int i = 0; i < 500; ++i)
				{
					std::vector<unsigned char>
						buffer(32, 0);
					bool
						result =
							random_value_manager_instance
								.generate_random_bytes(
									buffer.data(),
									buffer.size()
								);
					if (result &&
						!std::all_of(
							buffer.begin(),
							buffer.end(),
							[](unsigned char value){ return value == 0; }
						))
					{
						counter.fetch_add(1, std::memory_order_relaxed);
					}
				}
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		EXPECT_EQ(counter, 32 * 500);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_ReturnEmptySalt_When_RuntimeExecutionDisabled)
	{
		random_value_manager_instance.configurations
			.is_feature_runtime_execution_handling_enabled = true;

		std::array<unsigned char, 16>
			result =
				random_value_manager_instance
					.generate_random_salt();

		EXPECT_TRUE(result.empty() == false);
		random_value_manager_instance.configurations
			.is_feature_runtime_execution_handling_enabled = false;
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_ReturnFalse_When_RuntimeExecutionDisabledForBytes)
	{
		random_value_manager_instance.configurations
			.is_feature_runtime_execution_handling_enabled = false;

		std::vector<unsigned char>
			buffer(16, 0);

		bool
			result =
				random_value_manager_instance
					.generate_random_bytes(
						buffer.data(),
						buffer.size()
					);

		EXPECT_FALSE(result);
		random_value_manager_instance.configurations
			.is_feature_runtime_execution_handling_enabled = false;
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_HandleExtremeLargeBuffer_When_GeneratingBytes)
	{
		size_t
			large_size = 1'000'000;

		std::vector<unsigned char>
			buffer(large_size, 0);

		bool
			result =
				random_value_manager_instance
					.generate_random_bytes(
						buffer.data(),
						buffer.size()
					);

		EXPECT_TRUE(result);
		EXPECT_FALSE(
			std::all_of(
				buffer.begin(),
				buffer.end(),
				[](unsigned char value) { return value == 0; }
			)
		);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_BeThreadSafeForSaltGenerationUnderStress)
	{
		std::vector<std::thread>
			threads;
		std::atomic<int>
			counter{0};

		for (int index = 0; index < 32; ++index)
		{
			threads.emplace_back([this, &counter]()
			{
				for (int i = 0; i < 500; ++i)
				{
					std::array<unsigned char, 16>
						result =
							random_value_manager_instance
								.generate_random_salt();
					if (!std::all_of(result.begin(), result.end(),
						[](unsigned char value){ return value == 0; }))
					{
						counter.fetch_add(1, std::memory_order_relaxed);
					}
				}
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		EXPECT_EQ(counter, 32 * 500);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_ReturnFalse_When_BufferIsEmptyButEdgeCaseEnabled)
	{
		random_value_manager_instance.configurations
			.is_feature_edge_case_handling_enabled = true;

		std::vector<unsigned char>
			buffer(0);

		bool
			result =
				random_value_manager_instance
					.generate_random_bytes(
						buffer.data(),
						buffer.size()
					);

		EXPECT_FALSE(result);
		random_value_manager_instance.configurations
			.is_feature_edge_case_handling_enabled = false;
	}

	TEST_F(RandomValueGenerationManagerTest,
	Should_GenerateUniqueSalts_When_CalledMultipleTimes)
	{
		std::array<unsigned char, 16>
		salt_one =
		random_value_manager_instance
		.generate_random_salt();
		std::array<unsigned char, 16>
		salt_two =
		random_value_manager_instance
		.generate_random_salt();

			EXPECT_NE(salt_one, salt_two);
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_CompleteHighConcurrencyAsyncStressTest)
	{
		std::vector<std::future<bool>>
			futures;
		for (int index = 0; index < 32; ++index)
		{
			futures.emplace_back(
				std::async(std::launch::async, [this]()
				{
					for (int i = 0; i < 500; ++i)
					{
						std::vector<unsigned char> buffer(32, 0);
						if (!random_value_manager_instance.generate_random_bytes(buffer.data(), buffer.size()))
							return false;
						if (std::all_of(buffer.begin(), buffer.end(),
							[](unsigned char value){ return value == 0; }))
							return false;
					}
					return true;
				})
			);
		}

		for (auto& future_result : futures)
		{
			EXPECT_TRUE(future_result.get());
		}
	}

	TEST_F(RandomValueGenerationManagerTest,
		Should_HandleCombinedEdgeCaseAndRuntimeDisabledFlags)
	{
		random_value_manager_instance.configurations
			.is_feature_edge_case_handling_enabled = false;
		random_value_manager_instance.configurations
			.is_feature_runtime_execution_handling_enabled = false;

		std::vector<unsigned char>
			buffer(16, 0);
		bool
			result_bytes =
				random_value_manager_instance
					.generate_random_bytes(
						buffer.data(),
						buffer.size()
					);
		std::array<unsigned char, 16>
			result_salt =
				random_value_manager_instance
					.generate_random_salt();

		EXPECT_FALSE(result_bytes);
		EXPECT_TRUE(result_salt.empty() == false);

		random_value_manager_instance.configurations
			.is_feature_edge_case_handling_enabled = false;
		random_value_manager_instance.configurations
			.is_feature_runtime_execution_handling_enabled = false;
	}

	TEST_P(RandomValueGenerationManagerParameterizedTest,
		Should_HandleMaximumSizeBuffersForRandomBytes)
	{
		size_t
			size = GetParam();
		if (size > 1'000'000)
			size = 1'000'000;

		std::vector<unsigned char>
			buffer(size, 0);

		bool
			result =
				random_value_manager_instance
					.generate_random_bytes(
						buffer.data(),
						buffer.size()
					);

		if (size != 0)
		{
			EXPECT_TRUE(result);
			EXPECT_FALSE(
				std::all_of(
					buffer.begin(),
					buffer.end(),
					[](unsigned char value) { return value == 0; }
				)
			);
		}
		else
		{
			EXPECT_FALSE(result);
		}		
	}

	INSTANTIATE_TEST_CASE_P(
		LargeSizes,
		RandomValueGenerationManagerParameterizedTest,
		::testing::Values(
			1'000'000,
			2'000'000
		)
	);
}

#endif
