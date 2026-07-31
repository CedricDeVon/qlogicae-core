#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ValueExtractorManager \
	)

#include "value_extractor_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	template <typename OutputType> class
		ValueExtractorManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ValueExtractorManagerConfigurations<OutputType>>
	{
	public:
		ValueExtractorManager();

		OutputType
			execute();
	};

	template <typename OutputType> OutputType
		ValueExtractorManager<OutputType>
			::execute()
	{
		try
		{
			if
			(
				this->configurations
					.is_runtime_execution_disabled_for_feature_handling()
			)
			{
				return
					OutputType{};
			}

			boost::unique_lock<boost::mutex>
				mutex_lock;
			if (this->configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						this->feature_handling_mutex_1
					);
			}

			return
				(this->configurations.callback == nullptr) ?
					OutputType{} :
					this->configurations
						.callback();
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			this->QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				OutputType {}
			);
		}
	}

	template <typename OutputType>
		ValueExtractorManager<OutputType>
			::ValueExtractorManager() :
				QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ValueExtractorManagerConfigurations<OutputType>>()
	{
		
	}
}

#endif
