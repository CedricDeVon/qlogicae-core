#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		OnnxApiManager \
	)

#include "../includes/onnx_api_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        
	OnnxApiManager
		::OnnxApiManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<OnnxApiManagerConfigurations>()
    {
        
    }

	bool
		OnnxApiManager
			::setup()
	{
		try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

#ifdef _M_X64
			session_options_.SetIntraOpNumThreads(1);
			session_options_.SetGraphOptimizationLevel(
				ORT_DISABLE_ALL
			);

			#ifdef USE_CUDA
			if (configurations.enable_cuda) {
				OrtCUDAProviderOptions cuda_opts{};
				if (configurations.device_id)
					cuda_opts.device_id = *configurations.device_id;
				session_options_
					.AppendExecutionProvider_CUDA(cuda_opts);
			}
			#endif

			std::wstring wpath(
				configurations.model_path.begin(),
				configurations.model_path.end());

			session_ = Ort::Session(env_, wpath.c_str(),
				session_options_);

			Ort::AllocatorWithDefaultOptions allocator;

			size_t num_inputs = session_.GetInputCount();
			input_names_str_.resize(num_inputs);
			input_names_ptrs_.resize(num_inputs);
			input_shapes_.resize(num_inputs);

			for (size_t i = 0; i < num_inputs; ++i) {

				auto name =
					session_.GetInputNameAllocated(i, allocator);

				input_names_str_[i] = name.get();
				input_names_ptrs_[i] =
					input_names_str_[i].c_str();

				auto info =
					session_.GetInputTypeInfo(i)
					.GetTensorTypeAndShapeInfo();

				input_shapes_[i] = info.GetShape();

				for (auto& d : input_shapes_[i])
					if (d < 0) d = 1;
			}

			size_t num_outputs = session_.GetOutputCount();
			output_names_str_.resize(num_outputs);
			output_names_ptrs_.resize(num_outputs);

			for (size_t i = 0; i < num_outputs; ++i) {

				auto name =
					session_.GetOutputNameAllocated(i,
						allocator);

				output_names_str_[i] = name.get();
				output_names_ptrs_[i] =
					output_names_str_[i].c_str();
			}
#endif

			return true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::unordered_map<std::string, std::vector<std::string>>
		OnnxApiManager
			::infer_via_strings(
				const std::unordered_map<std::string, std::vector<std::vector<std::string>>>&
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

			prepare_string_inputs(inputs);
			run_session();

			return
				collect_string_outputs();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }		
	}

	bool
		OnnxApiManager
			::prepare_string_inputs(
				const std::unordered_map<std::string, std::vector<std::vector<std::string>>>&
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

			Ort::AllocatorWithDefaultOptions allocator;

			for (size_t i = 0; i < input_names_str_.size(); ++i) {
				const auto& name = input_names_str_[i];
				auto it = inputs.find(name);
				if (it == inputs.end())
					return false;

				const auto& batch = it->second;
				size_t batch_size = batch.size();
				size_t feature_size = batch[0].size();

				std::vector<int64_t> shape = resolve_shape(i, batch_size, feature_size);


				Ort::Value input_tensor = Ort::Value::CreateTensor(
					allocator,
					shape.data(),
					shape.size(),
					ONNX_TENSOR_ELEMENT_DATA_TYPE_STRING
				);

				std::vector<const char*> raw_ptrs;
				for (const auto& row : batch)
					for (const auto& str : row)
						raw_ptrs.push_back(str.c_str());

				input_tensor.FillStringTensor(raw_ptrs.data(), raw_ptrs.size());

				input_tensors_.push_back(std::move(input_tensor));
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

	std::unordered_map<std::string, std::vector<std::string>>
		OnnxApiManager
			::collect_string_outputs()
	{
		try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			std::unordered_map<std::string,
			std::vector<std::string>> results;

#ifdef _M_X64
			for (size_t i = 0; i < output_tensors_.size(); ++i) {

				size_t count =
					output_tensors_[i]
					.GetTensorTypeAndShapeInfo()
					.GetElementCount();

				size_t total_length =
					output_tensors_[i].GetStringTensorDataLength();

				std::vector<char> buffer(total_length);
				std::vector<size_t> offsets(count);

				output_tensors_[i].GetStringTensorContent(
					buffer.data(),
					total_length,
					offsets.data(),
					count
				);

				std::vector<std::string> strings(count);
				for (size_t j = 0; j < count; ++j) {
					size_t start = offsets[j];
					size_t end = (j + 1 < count)
						? offsets[j + 1]
						: total_length;
					strings[j] =
						std::string(buffer.data() + start,
							end - start);
				}

				results[output_names_str_[i]] = std::move(strings);
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
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }		
	}

	std::vector<int64_t>
		OnnxApiManager
			::resolve_shape(
				const size_t&
					input_index,
				const size_t&
					batch_size,
				const size_t&
					feature_size
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3,
				input_index < 0 ||
				batch_size < 1 ||
				feature_size < 1
			);

			std::vector<int64_t> shape;

#ifdef _M_X64
				shape =
					input_shapes_[input_index];

			shape[0] = static_cast<int64_t>(batch_size);

			int64_t known_product = 1;
			for (size_t i = 1; i < shape.size(); ++i)
				known_product *= shape[i];

			if (known_product == 0)
				return {};

			if (known_product != static_cast<int64_t>(feature_size))
				shape.back() =
				static_cast<int64_t>(feature_size /
					(known_product /
						shape.back()));
#endif

			return
				shape;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		OnnxApiManager
			::run_session()
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

#ifdef _M_X64			
			output_tensors_ = session_.Run(
				Ort::RunOptions{},
				input_name_ptrs_runtime_.data(),
				input_tensors_.data(),
				input_tensors_.size(),
				output_names_ptrs_.data(),
				output_names_ptrs_.size()
			);
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
}

#endif
