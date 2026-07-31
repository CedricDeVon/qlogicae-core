#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		OnnxApiManager \
	)

#include "onnx_api_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		OnnxApiManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<OnnxApiManagerConfigurations>
    {
    public:		
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3
		);

#ifdef _M_X64
		Ort::Env
			env_ { ORT_LOGGING_LEVEL_WARNING, "default" };

		Ort::Session
			session_ { nullptr };

		Ort::SessionOptions
			session_options_ {};

		std::vector<Ort::Value>
			input_tensors_;

		std::vector<Ort::Value>
			output_tensors_;
#endif

		std::vector<std::string>
			input_names_str_;

		std::vector<const char*>
			input_names_ptrs_;

		std::vector<std::vector<int64_t>>
			input_shapes_;

		std::vector<std::string>
			output_names_str_;

		std::vector<const char*>
			output_names_ptrs_;

		std::vector<const char*>
			input_name_ptrs_runtime_;

		std::vector<std::vector<float>>
			numeric_buffers_;

		std::vector<std::vector<std::string>>
			string_buffers_;

		OnnxApiManager();

		bool
			setup();

		std::unordered_map<std::string, std::vector<std::string>>
			infer_via_strings(
				const std::unordered_map<std::string, std::vector<std::vector<std::string>>>&
					inputs
			);

		bool
			prepare_string_inputs(
				const std::unordered_map<std::string, std::vector<std::vector<std::string>>>&
					inputs
			);

		std::unordered_map<std::string, std::vector<std::string>>
			collect_string_outputs();


		std::vector<int64_t>
			resolve_shape(
				const size_t&
					input_index,
				const size_t&
					batch_size,
				const size_t&
					feature_size
			);

		bool
			run_session();

		template<typename Type> std::unordered_map<std::string, std::span<const Type>>
			infer_via_numerics(
				const std::unordered_map<std::string, std::vector<std::vector<Type>>>&
					inputs
			);

		template<typename Type> bool
			prepare_numeric_inputs(
				const std::unordered_map<std::string, std::vector<std::vector<Type>>>&
					inputs
			);

		template<typename Type> std::unordered_map<std::string, std::span<const Type>>
			collect_numeric_outputs();
    };

	template<typename Type> std::unordered_map<std::string, std::span<const Type>>
		OnnxApiManager
			::infer_via_numerics(
				const std::unordered_map<std::string, std::vector<std::vector<Type>>>&
					inputs
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!inputs.size()
			);

			prepare_numeric_inputs(
				inputs
			);
			run_session();

			return
				collect_numeric_outputs<Type>();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				std::unordered_map<std::string, std::span<const Type>> {}
			);
        }			
	}

	template<typename Type> bool
		OnnxApiManager
			::prepare_numeric_inputs(
				const std::unordered_map<std::string, std::vector<std::vector<Type>>>&
					inputs
			)
	{
		try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				!inputs.size()
			);

#ifdef _M_X64
			input_tensors_.clear();
			input_name_ptrs_runtime_.clear();
			numeric_buffers_.clear();

			for (size_t i = 0; i < input_names_str_.size(); ++i) {
				const auto& name = input_names_str_[i];
				auto it = inputs.find(name);
				if (it == inputs.end())
					return false;

				const auto& batch = it->second;
				if (batch.empty())
					return false;

				size_t batch_size = batch.size();
				if (!batch_size)
				{
					return false;
				}

				size_t feature_size = batch[0].size();
				if (!feature_size)
				{
					return false;
				}

				for (const auto& sample : batch)
					if (sample.size() != feature_size)
						return false;

				size_t total = batch_size * feature_size;
				numeric_buffers_.emplace_back(total);
				auto& buffer = numeric_buffers_.back();

				for (size_t b = 0; b < batch_size; ++b)
					std::copy(batch[b].begin(), batch[b].end(),
						buffer.begin() + b * feature_size);

				std::vector<int64_t> shape = resolve_shape(i, batch_size, feature_size);

				const Ort::MemoryInfo mem_info = Ort::MemoryInfo::CreateCpu(
					OrtArenaAllocator, OrtMemTypeDefault);

				input_tensors_.emplace_back(
					Ort::Value::CreateTensor<Type>(
						mem_info,
						buffer.data(),
						total,
						shape.data(),
						shape.size()
					)
				);

				input_name_ptrs_runtime_.push_back(input_names_ptrs_[i]);
			}
#endif

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }		
	}

	template<typename Type> std::unordered_map<std::string, std::span<const Type>>
		OnnxApiManager
			::collect_numeric_outputs()
	{
		try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			std::unordered_map<std::string, std::span<const Type>> results;

#ifdef _M_X64
			for (size_t i = 0; i < output_tensors_.size(); ++i)
			{
				auto type_info =
					output_tensors_[i].GetTensorTypeAndShapeInfo();

				if (type_info.GetElementType() !=
					Ort::TypeToTensorType<Type>::type)
					return {};

				Type* data = output_tensors_[i].GetTensorMutableData<Type>();
				size_t count = type_info.GetElementCount();

				results[output_names_str_[i]] =
					std::span<const Type>(data, count);
			}
#endif

			return
				results;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				std::unordered_map<std::string, std::span<const Type>> {}
			);
        }		
	}
}

#endif
