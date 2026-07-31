#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FunctionWrapper \
	)

#include "function_wrapper_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	class
		FunctionWrapper :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FunctionWrapperConfigurations>
	{
	public:
		FunctionWrapper();

		template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments> ResultType
		call_function(
			InputObjectType&
				input_object,
			const InputCallback&
				input_callback,
			const InputCallbackArguments&...
				input_callback_arguments
		);
	};

	template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments> ResultType
		FunctionWrapper::call_function(
			InputObjectType&
				input_object,
			const InputCallback&
				input_callback,
			const InputCallbackArguments&...
				input_callback_arguments
		)
	{
		try
		{		
			QLOGICAE_COR1__BASE__HPP_CPP__THREAD_SAFETY_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1
			);

			if constexpr (std::is_pointer_v<InputObjectType>)
			{
				if (!input_object)
				{
					if constexpr (std::is_default_constructible_v<ResultType>)
					{
						return
							ResultType{};
					}
					else
					{
						SingletonManager
							::get_singleton<ErrorManager>().handle_error_outputs("");
					}
				}
				return (input_object->*input_callback)(input_callback_arguments...);
			}
			else
			{
				return (input_object.*input_callback)(input_callback_arguments...);
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			if constexpr (std::is_default_constructible_v<ResultType>)
			{
				QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
				(
					ResultType {}
				);
			}
			else
			{
				throw;
			}
		}
	}
}

#endif
