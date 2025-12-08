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

    TEST(FunctionWrapper,
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

    TEST(FunctionWrapper,
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

    TEST(FunctionWrapper,
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

    TEST(FunctionWrapper,
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

    TEST(FunctionWrapper,
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
    
    TEST(FunctionWrapper,
        ShouldPropagateExceptionThroughFuture)
    {
        DummyObject object;

        std::future<int> fut =
            QLogicaeCppCore::FunctionWrapper::call_async<
                int,
                DummyObject,
                QLogicaeCppCore::Result<int>(DummyObject::*)(
                    QLogicaeCppCore::Result<int>&,
                    int
                )
            >(
                object,
                &DummyObject::sync_throw,
                4
            );

        ASSERT_THROW(fut.get(), std::runtime_error);
    }

    TEST(FunctionWrapper,
        ShouldNotInvokeCallbackWhenExceptionOccurs)
    {
        DummyObject object;

        std::atomic<bool> invoked(false);

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
            )
        >(
            [&](int)
            {
                invoked.store(true);
            },
            object,
            &DummyObject::sync_throw,
            2
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        ASSERT_FALSE(invoked.load());
    }

    TEST(FunctionWrapper,
        ShouldDeliverBadResultWhenExceptionOccurs)
    {
        DummyObject object;

        std::atomic<bool> bad(false);

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
            )
        >(
            [&](QLogicaeCppCore::Result<int>& r)
            {
                if (r.get_status() != QLogicaeCppCore::ResultStatus::GOOD)
                {
                    bad.store(true);
                }
            },
            object,
            &DummyObject::sync_throw,
            8
        );

        for (int i = 0; i < 2000 && !bad.load(); ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        ASSERT_TRUE(bad.load());
    }
    
    TEST(FunctionWrapper,
        ShouldSwallowExceptionFromValueCallback)
    {
        DummyObject object;

        std::atomic<bool> crashed(false);

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            [&](int)
            {
                throw std::runtime_error("callback");
            },
            object,
            &DummyObject::sync_return,
            5
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        ASSERT_FALSE(crashed.load());
    }

    TEST(FunctionWrapper,
        ShouldSwallowExceptionFromResultCallback)
    {
        DummyObject object;

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            [&](QLogicaeCppCore::Result<int>&)
            {
                throw std::runtime_error("callback result");
            },
            object,
            &DummyObject::sync_return,
            6
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        SUCCEED();
    }

    TEST(FunctionWrapper,
        ShouldHandleEmptyResultCallback)
    {
        DummyObject object;

        std::function<void(QLogicaeCppCore::Result<int>&)> cb;

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            cb,
            object,
            &DummyObject::sync_return,
            9
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        SUCCEED();
    }

    TEST(FunctionWrapper,
        ShouldHandleEmptyValueCallback)
    {
        DummyObject object;

        std::function<void(int)> cb;

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            cb,
            object,
            &DummyObject::sync_return,
            8
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        SUCCEED();
    }

    TEST(FunctionWrapper,
        ShouldNotBlockWhenStartingAsync)
    {
        DummyObject object;

        auto start = std::chrono::high_resolution_clock::now();

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            [&](int) {},
            object,
            &DummyObject::sync_return,
            10
        );

        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        ASSERT_LT(elapsed.count(), 2000); 
    }

    TEST(FunctionWrapper,
        ShouldHandleHighConcurrencyForValueCallbacks)
    {
        DummyObject object;

        std::atomic<int> counter(0);

        const int threads = 8;
        const int per = 40;

        std::vector<std::thread> pool;

        for (int t = 0; t < threads; t++)
        {
            pool.emplace_back([&]()
                {
                    for (int i = 0; i < per; i++)
                    {
                        QLogicaeCppCore::FunctionWrapper::call_async<
                            int,
                            DummyObject,
                            QLogicaeCppCore::Result<int>(DummyObject::*)(
                                QLogicaeCppCore::Result<int>&,
                                int
                                )
                        >(
                            [&](int) { counter.fetch_add(1); },
                            object,
                            &DummyObject::sync_return,
                            1
                        );
                    }
                });
        }

        for (auto& th : pool) th.join();

        ASSERT_EQ(counter.load(), threads * per);
    }

    TEST(FunctionWrapper,
        ShouldHandleHighConcurrencyForResultCallbacks)
    {
        DummyObject object;

        std::atomic<int> counter(0);

        const int threads = 8;
        const int per = 40;

        std::vector<std::thread> pool;

        for (int t = 0; t < threads; t++)
        {
            pool.emplace_back([&]()
                {
                    for (int i = 0; i < per; i++)
                    {
                        QLogicaeCppCore::FunctionWrapper::call_async<
                            int,
                            DummyObject,
                            QLogicaeCppCore::Result<int>(DummyObject::*)(
                                QLogicaeCppCore::Result<int>&,
                                int
                                )
                        >(
                            [&](QLogicaeCppCore::Result<int>&) {
                                counter.fetch_add(1);
                            },
                            object,
                            &DummyObject::sync_return,
                            1
                        );
                    }
                });
        }

        for (auto& th : pool) th.join();

        ASSERT_EQ(counter.load(), threads * per);
    }

    TEST(FunctionWrapper,
        ShouldInvokeResultCallbackWithGoodStatusWhenSourceSucceeds)
    {
        DummyObject object;

        std::atomic<bool> good(false);

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            [&](QLogicaeCppCore::Result<int>& r)
            {
                if (r.get_status() == QLogicaeCppCore::ResultStatus::GOOD)
                {
                    good.store(true);
                }
            },
            object,
            &DummyObject::sync_return,
            12
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        ASSERT_TRUE(good.load());
    }

    TEST(FunctionWrapper,
        ShouldInvokeResultCallbackWithBadStatusWhenCallSafelyCatchesException)
    {
        DummyObject object;

        std::atomic<bool> bad(false);

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            [&](QLogicaeCppCore::Result<int>& r)
            {
                if (r.get_status() != QLogicaeCppCore::ResultStatus::GOOD)
                {
                    bad.store(true);
                }
            },
            object,
            &DummyObject::sync_throw,
            3
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        ASSERT_TRUE(bad.load());
    }

    TEST(FunctionWrapper,
        ShouldNotInvokeEmptyValueCallback)
    {
        DummyObject object;

        std::function<void(int)> cb;

        std::atomic<bool> invoked(false);

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            cb,
            object,
            &DummyObject::sync_return,
            4
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        ASSERT_FALSE(invoked.load());
    }

    TEST(FunctionWrapper,
        ShouldNotInvokeEmptyResultCallback)
    {
        DummyObject object;

        std::function<void(QLogicaeCppCore::Result<int>&)> cb;

        std::atomic<bool> invoked(false);

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            cb,
            object,
            &DummyObject::sync_return,
            4
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        ASSERT_FALSE(invoked.load());
    }

    TEST(FunctionWrapper,
        ShouldSwallowExceptionFromResultWrapperCallback)
    {
        DummyObject object;

        QLogicaeCppCore::FunctionWrapper::call_async<
            int,
            DummyObject,
            QLogicaeCppCore::Result<int>(DummyObject::*)(
                QLogicaeCppCore::Result<int>&,
                int
                )
        >(
            [&](QLogicaeCppCore::Result<int>&)
            {
                throw std::runtime_error("callback crash");
            },
            object,
            &DummyObject::sync_return,
            7
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        SUCCEED();
    }
}
