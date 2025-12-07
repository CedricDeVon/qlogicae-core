#pragma once

#include "result.hpp"
#include "instance_manager.hpp"

#include <stdexcept>
#include <functional>
#include <forward_list>

namespace QLogicaeCppCore
{
    class FunctionWrapper
    {
    public:
        FunctionWrapper();

        ~FunctionWrapper();

        FunctionWrapper(
            const FunctionWrapper& instance
        ) = delete;

        FunctionWrapper(
            FunctionWrapper&& instance
        ) noexcept = delete;

        FunctionWrapper& operator = (
            FunctionWrapper&& instance
        ) = delete;

        FunctionWrapper& operator = (
            const FunctionWrapper& instance
        ) = delete;

        template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
        static ResultType call_safely(
            InputObjectType& input_object,
            const InputCallback& input_callback,
            const InputCallbackArguments&... input_callback_arguments
        );        
    };

    template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
    ResultType FunctionWrapper::call_safely(
        InputObjectType& input_object,
        const InputCallback& input_callback,
        const InputCallbackArguments&... input_callback_arguments
    )
    {        
        ResultType result_value;
        QLogicaeCppCore::Result<ResultType> result;

        try
        {
            (input_object->*input_callback)(result, input_callback_arguments...);
            result.get_value(result_value);

            return result_value;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                exception.what()
            );

            return result_value;
        }
    }

    inline static FunctionWrapper& FUNCTION_WRAPPER =
        INSTANCE_MANAGER.get_instance<FunctionWrapper>();
}



/*
        template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
        static std::future<ResultType> call_async(
            InputObjectType& input_object,
            const InputCallback& input_callback,
            const InputCallbackArguments&... input_callback_arguments
        );

        template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
        static std::future<Result<ResultType>> call_async(
            InputObjectType& input_object,
            const InputCallback& input_callback,
            const InputCallbackArguments&... input_callback_arguments
        );

        template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
        static void call_async(
            const std::function<void(const ResultType& result)> output_callback,
            InputObjectType& input_object,
            const InputCallback& input_callback,
            const InputCallbackArguments&... input_callback_arguments
        );

        template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
        static void call_async(
            const std::function<void(Result<ResultType>& result)> output_callback,
            InputObjectType& input_object,
            const InputCallback& input_callback,
            const InputCallbackArguments&... input_callback_arguments
        );

* 
* 
        template <typename ResultType, typename InputCallback, typename... InputCallbackArguments>
        static ResultType call_safely(
            const InputCallback& input_callback,
            const InputCallbackArguments&... input_callback_arguments
        );

    template <typename ResultType, typename InputCallback, typename... InputCallbackArguments>
    ResultType FunctionWrapper::call_safely(
        const InputCallback& input_callback,
        const InputCallbackArguments&... input_callback_arguments
    )
    {
        ResultType result_value;
        QLogicaeCppCore::Result<ResultType> result;

        try
        {
            callback(result, arguments...);
            result.get_value(result_value);

            return result_value;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                exception.what()
            );

            return result_value;
        }
    }

        */

