#include "pch.hpp"

#include "qlogicae_cpp_core/includes/function_wrapper.hpp"

namespace QLogicaeCppCoreTest
{
    class DummyObject
    {
    public:
        DummyObject()
        {
        }

        QLogicaeCppCore::Result<int> sync_return(
            QLogicaeCppCore::Result<int>& result,
            int value
        )
        {
            result.set_to_good_status_with_value(value);
            return result;
        }

        QLogicaeCppCore::Result<int> sync_throw(
            QLogicaeCppCore::Result<int>& result,
            int value
        )
        {
            throw std::runtime_error("error");
        }

        QLogicaeCppCore::Result<int> sync_no_value(
            QLogicaeCppCore::Result<int>& result,
            int value
        )
        {
            return result;
        }
    };

    TEST(FunctionWrapperSyncTest,
        ShouldReturnValueWhenCallSafelySucceeds)
    {
        DummyObject object;
        int output =
            QLogicaeCppCore::FunctionWrapper::call_safely<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
            >(
                object,
                &DummyObject::sync_return,
                10
            );
        ASSERT_EQ(output, 10);
    }

    TEST(FunctionWrapperAsyncFutureTest,
        ShouldReturnFutureValueWhenCallAsyncFuture)
    {
        DummyObject object;

        std::future<int> future =
            QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
            >(
                object,
                &DummyObject::sync_return,
                7
            );

        int value = future.get();
        ASSERT_EQ(value, 7);
    }

    TEST(FunctionWrapperAsyncCallbackTest,
        ShouldInvokeCallbackWhenCallAsyncCallback)
    {
        DummyObject object;

        std::atomic<int> store(0);

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            [
                &store
            ](int value)
            {
                store.store(value);
            },
                    object,
                    &DummyObject::sync_return,
                    9
                    );

        int attempt = 0;

        while (attempt < 2000 && store.load() == 0)
        {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(1)
            );
            attempt = attempt + 1;
        }

        ASSERT_EQ(store.load(), 9);
    }

    TEST(FunctionWrapperAsyncResultCallbackTest,
        ShouldInvokeResultCallbackWhenCallAsyncResultCallback)
    {
        DummyObject object;

        std::atomic<int> store(0);

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            [
                &store
            ](QLogicaeCppCore::Result<int>& result)
            {
                int value;
                result.get_value(value);
                store.store(value);
            },
                    object,
                    &DummyObject::sync_return,
                    11
                    );

        int attempt = 0;

        while (attempt < 2000 && store.load() == 0)
        {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(1)
            );
            attempt = attempt + 1;
        }

        ASSERT_EQ(store.load(), 11);
    }

    TEST(FunctionWrapperStressTest,
        ShouldHandleHighConcurrencyWhenAsyncFuture)
    {
        DummyObject object;

        std::atomic<int> counter(0);

        std::vector<std::thread> threads;

        int thread_count = 16;
        int per_thread = 64;

        for (int t = 0; t < thread_count; t = t + 1)
        {
            threads.emplace_back(
                [
                    &object,
                    &counter,
                    per_thread
                ]()
                {
                    for (int i = 0; i < per_thread; i = i + 1)
                    {
                        std::future<int> future =
                            QLogicaeCppCore::FunctionWrapper::call_async<
                            int,
                            DummyObject,
                            QLogicaeCppCore::Result<int>(DummyObject::*)(
                                QLogicaeCppCore::Result<int>&,
                                int
                                )
                            >(
                                object,
                                &DummyObject::sync_return,
                                1
                            );

                        future.get();
                        counter.fetch_add(1);
                    }
                }
            );
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        ASSERT_EQ(counter.load(), thread_count * per_thread);
    }
}
/*
"東京"
*/