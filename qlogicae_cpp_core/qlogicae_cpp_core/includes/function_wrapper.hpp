#pragma once

#include "result.hpp"
#include "utilities.hpp"
#include "instance_manager.hpp"
#include "asynchronous_manager.hpp"

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

        template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
        static std::future<ResultType> call_async(
            InputObjectType& input_object,
            const InputCallback& input_callback,
            const InputCallbackArguments&... input_callback_arguments
        );

        template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
        static void call_async(
            std::future<Result<ResultType>>& promise_result,
            InputObjectType& input_object,
            const InputCallback& input_callback,
            const InputCallbackArguments&... input_callback_arguments
        );

        template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
        static void call_async(
            const std::function<void(ResultType result)>& output_callback,
            InputObjectType& input_object,
            const InputCallback& input_callback,
            const InputCallbackArguments&... input_callback_arguments
        );

        template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
        static void call_async(
            const std::function<void(Result<ResultType>& result)>& output_callback,
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
            (input_object.*input_callback)(result, input_callback_arguments...);
            result.get_value(result_value);

            return result_value;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                exception.what()
            );
        }
    }

    template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
    std::future<ResultType> FunctionWrapper::call_async(
        InputObjectType& input_object,
        const InputCallback& input_callback,
        const InputCallbackArguments&... input_callback_arguments
    )
    {
        Result<bool> result;

        auto promise = std::make_shared<std::promise<ResultType>>();
        std::future<ResultType> future = promise->get_future();

        ASYNCHRONOUS_MANAGER.begin_one_thread(
            result,
            [
                &input_object,
                input_callback,
                promise,
                input_callback_arguments...
            ]() mutable
            {
                try
                {
                    promise->set_value(
                        call_safely<ResultType>(
                            input_object,
                            input_callback,
                            input_callback_arguments...
                        )
                    );                    
                }
                catch (...)
                {
                    promise->set_exception(std::current_exception());
                }
            }
        );

        return future;
    }

    template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
    void FunctionWrapper::call_async(
        std::future<Result<ResultType>>& promise_result,
        InputObjectType& input_object,
        const InputCallback& input_callback,
        const InputCallbackArguments&... input_callback_arguments
    )
    {                
        Result<bool> async_result;

        ASYNCHRONOUS_MANAGER.begin_one_thread(
            async_result,
            [
                &input_object,
                input_callback,
                promise_result,
                input_callback_arguments...
            ]() mutable
            {
                Result<ResultType> wrapper;
                
                try
                {
                    wrapper.set_to_good_status_with_value(
                        call_safely<ResultType>(
                            input_object,
                            input_callback,
                            input_callback_arguments...
                        )
                    );

                    promise_result->set_value(
                        wrapper
                    );
                }
                catch (...)
                {
                    
                }
            }
        );
    }

    template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
    void FunctionWrapper::call_async(
        const std::function<void(ResultType)>& output_callback,
        InputObjectType& input_object,
        const InputCallback& input_callback,
        const InputCallbackArguments&... input_callback_arguments
    )
    {
        Result<bool> result;

        ASYNCHRONOUS_MANAGER.begin_one_thread(
            result,
            [
                &input_object,
                input_callback,
                output_callback,
                input_callback_arguments...
            ]() mutable
            {
                try
                {
                    if (output_callback)
                    {
                        try
                        {
                            output_callback(
                                call_safely<ResultType>(
                                    input_object,
                                    input_callback,
                                    input_callback_arguments...
                                )
                            );
                        }
                        catch (...)
                        {

                        }
                    }                    
                }
                catch (...)
                {
                    
                }
            }
        );
    }

    template <typename ResultType, typename InputObjectType, typename InputCallback, typename... InputCallbackArguments>
    void FunctionWrapper::call_async(
        const std::function<void(Result<ResultType>&)>& output_callback,
        InputObjectType& input_object,
        const InputCallback& input_callback,
        const InputCallbackArguments&... input_callback_arguments
    )
    {
        Result<bool> result;

        ASYNCHRONOUS_MANAGER.begin_one_thread(
            result,
            [
                &input_object,
                input_callback,
                output_callback,
                input_callback_arguments...
            ]() mutable
            {
                Result<ResultType> wrapper;
                
                try
                {
                    wrapper.set_to_good_status_with_value(
                        call_safely<ResultType>(
                            input_object,
                            input_callback,
                            input_callback_arguments...
                        )
                    );
                }
                catch (...)
                {
                    wrapper.set_to_bad_status_without_value();
                }

                try
                {
                    if (output_callback)
                    {
                        try
                        {
                            output_callback(wrapper);
                        }
                        catch (...)
                        {

                        }
                    }
                }
                catch (...)
                {
                    
                }
            }
        );
    }

    inline static FunctionWrapper& FUNCTION_WRAPPER =
        INSTANCE_MANAGER.get_instance<FunctionWrapper>();
}

