#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		OnnxApiManager \
	)

#include "../includes/onnx_api_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
#ifdef _M_X64				
	TEST_F(OnnxApiManagerTest, Should_InferNumericSuccessfully_When_ValidInput)
	{
		std::vector<std::vector<float>> batch;
		batch.push_back(std::vector<float>(128, 0.5f));
		batch.push_back(std::vector<float>(128, 0.7f));

		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;

		auto results = manager.infer_via_numerics<float>(inputs);

		ASSERT_EQ(results.size(), manager.output_names_str_.size());
		for (auto& [name, output_span] : results)
			ASSERT_EQ(output_span.size(), batch.size() * 10);
	}

	TEST_F(OnnxApiManagerTest, Should_HandleEmptyNumericInput_When_BatchIsEmpty)
	{
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = {};
		ASSERT_FALSE(manager.prepare_numeric_inputs(inputs));
	}

	TEST_F(OnnxApiManagerTest, Should_ResolveShapeCorrectly_When_BatchSizeAndFeatureSizeGiven)
	{
		std::vector<int64_t> shape = manager.resolve_shape(0, 2, 128);
		ASSERT_EQ(shape[0], 2);
		ASSERT_GE(shape.back(), 128);
	}

	TEST_F(OnnxApiManagerTest, Should_RunSessionSuccessfully_When_InputsPrepared)
	{
		std::vector<std::vector<float>> batch;
		batch.push_back(std::vector<float>(128, 0.1f));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		manager.prepare_numeric_inputs(inputs);
		ASSERT_NO_THROW(manager.run_session());
	}

	TEST_F(OnnxApiManagerTest, Should_PerformAsyncNumericInference_When_ValidInput)
	{
		std::vector<std::vector<float>> batch;
		batch.push_back(std::vector<float>(128, 0.2f));

		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;

		auto future_result = std::async(
			std::launch::async,
			[&]()
			{
				return manager.infer_via_numerics<float>(inputs);
			}
		);

		auto results = future_result.get();
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_HandleMultithreadedInference_When_MultipleThreads)
	{
		std::vector<std::thread> threads;
		std::atomic<int> completed_threads = 0;

		for (int i = 0; i < 4; ++i)
		{
			threads.emplace_back(
				[&]()
				{
					std::vector<std::vector<float>> batch(1, std::vector<float>(128, 0.3f));
					std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
					inputs[manager.input_names_str_[0]] = batch;
					auto results = manager.infer_via_numerics<float>(inputs);
					ASSERT_EQ(results.size(), manager.output_names_str_.size());
					++completed_threads;
				}
			);
		}

		for (auto& thread : threads)
			thread.join();

		ASSERT_EQ(completed_threads.load(), 4);
	}

	INSTANTIATE_TEST_CASE_P(
		StressTests,
		OnnxApiManagerStressTest,
		::testing::Values(10, 50, 100)
	);

	TEST_P(OnnxApiManagerStressTest, Should_HandleHighLoadNumericInference_When_StressTest)
	{
		size_t batch_count = GetParam();
		std::vector<std::vector<float>> batch(batch_count, std::vector<float>(128, 0.5f));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		auto results = manager.infer_via_numerics<float>(inputs);
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_HandleInvalidInput_When_FeatureSizeMismatch)
	{
		std::vector<std::vector<float>> batch;
		batch.push_back(std::vector<float>(64, 0.1f));
		batch.push_back(std::vector<float>(60, 0.1f));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		ASSERT_FALSE(manager.prepare_numeric_inputs(inputs));
	}

	TEST_F(OnnxApiManagerTest, Should_HandleMaximumFloatValues_When_LargeInput)
	{
		std::vector<std::vector<float>> batch;
		batch.push_back(std::vector<float>(128, std::numeric_limits<float>::max()));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		auto results = manager.infer_via_numerics<float>(inputs);
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_HandleMinimumFloatValues_When_LargeInput)
	{
		std::vector<std::vector<float>> batch;
		batch.push_back(std::vector<float>(128, std::numeric_limits<float>::lowest()));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		auto results = manager.infer_via_numerics<float>(inputs);
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_ThrowException_When_RunSessionWithoutInputs)
	{
		ASSERT_ANY_THROW(manager.run_session());
	}

	TEST_F(OnnxApiManagerTest, Should_HandleZeroFeatureSize_When_EmptyFeatureVector)
	{
		std::vector<std::vector<float>> batch;
		batch.push_back(std::vector<float>{});
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		ASSERT_FALSE(manager.prepare_numeric_inputs(inputs));
	}

	TEST_F(OnnxApiManagerTest, Should_HandleZeroBatchSize_When_NoSamples)
	{
		std::vector<std::vector<float>> batch;
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		ASSERT_FALSE(manager.prepare_numeric_inputs(inputs));
	}

	TEST_F(OnnxApiManagerTest, Should_HandleExtremelyLargeFeatureValues_When_LargeInput)
	{
		std::vector<std::vector<float>> batch;
		batch.push_back(std::vector<float>(128, std::numeric_limits<float>::infinity()));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		auto results = manager.infer_via_numerics<float>(inputs);
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_HandleNanValues_When_InputContainsNan)
	{
		std::vector<std::vector<float>> batch;
		batch.push_back(std::vector<float>(128, std::nanf("")));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		auto results = manager.infer_via_numerics<float>(inputs);
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_PerformAsyncNumericInference_When_ExceptionThrown)
	{
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = {};
		auto future_result = std::async(
			std::launch::async,
			[&]()
			{
				return manager.infer_via_numerics<float>(inputs);
			}
		);
		ASSERT_ANY_THROW(future_result.get());
	}

	TEST_F(OnnxApiManagerTest, Should_HandleMultithreadedInference_When_ThreadsThrow)
	{
		std::vector<std::thread> threads;
		std::atomic<int> completed_threads = 0;

		for (int i = 0; i < 4; ++i)
		{
			threads.emplace_back(
				[&]()
				{
					std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
					inputs[manager.input_names_str_[0]] = {};
					try
					{
						manager.infer_via_numerics<float>(inputs);
					}
					catch (...)
					{
					}
					++completed_threads;
				}
			);
		}

		for (auto& thread : threads)
			thread.join();

		ASSERT_EQ(completed_threads.load(), 4);
	}

	TEST_P(OnnxApiManagerStressTest, Should_HandleExtremelyLargeBatchSizes_When_StressTest)
	{
		size_t batch_count = GetParam() * 1000;
		std::vector<std::vector<float>> batch(batch_count, std::vector<float>(128, 0.5f));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		auto results = manager.infer_via_numerics<float>(inputs);
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_CompleteWithinTimeLimit_When_PerformanceValidation)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		std::vector<std::vector<float>> batch(10, std::vector<float>(128, 0.5f));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		auto results = manager.infer_via_numerics<float>(inputs);
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		ASSERT_LE(duration.count(), 2000);
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_RunSessionMultipleTimes_When_PreparedInputsChange)
	{
		std::vector<std::vector<float>> batch1(1, std::vector<float>(128, 0.5f));
		std::vector<std::vector<float>> batch2(1, std::vector<float>(128, 0.7f));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs1;
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs2;
		inputs1[manager.input_names_str_[0]] = batch1;
		inputs2[manager.input_names_str_[0]] = batch2;
		manager.prepare_numeric_inputs(inputs1);
		auto results1 = manager.infer_via_numerics<float>(inputs1);
		manager.prepare_numeric_inputs(inputs2);
		auto results2 = manager.infer_via_numerics<float>(inputs2);
		ASSERT_EQ(results1.size(), manager.output_names_str_.size());
		ASSERT_EQ(results2.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_HandleNegativeFloatValues_When_LargeInput)
	{
		std::vector<std::vector<float>> batch(2, std::vector<float>(128, -0.5f));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		auto results = manager.infer_via_numerics<float>(inputs);
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_HandleSubnormalFloatValues_When_LargeInput)
	{
		float subnormal = std::numeric_limits<float>::denorm_min();
		std::vector<std::vector<float>> batch(2, std::vector<float>(128, subnormal));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		auto results = manager.infer_via_numerics<float>(inputs);
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}

	TEST_F(OnnxApiManagerTest, Should_EnableCudaAndInfer_When_ConfigurationsEnableCudaTrue)
	{
		manager.configurations.enable_cuda = true;
		manager.setup();
		std::vector<std::vector<float>> batch(2, std::vector<float>(128, 0.5f));
		std::unordered_map<std::string, std::vector<std::vector<float>>> inputs;
		inputs[manager.input_names_str_[0]] = batch;
		auto results = manager.infer_via_numerics<float>(inputs);
		ASSERT_EQ(results.size(), manager.output_names_str_.size());
	}
#endif
}

#endif
