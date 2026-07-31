#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Results \
	)

#include "../includes/results.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{    
    TEST_F(ResultsTest, Should_GetValue_When_ValueSet)
    {
        std::string initial_value_string = std::string("alpha_value");
        result_string_instance.set_to_good_status_with_value(initial_value_string);
        std::string retrieved_value_string;
        result_string_instance.get_value(retrieved_value_string);
        ASSERT_EQ(retrieved_value_string, std::string("alpha_value"));
    }

    TEST_F(ResultsTest, Should_MoveValue_When_RvalueSet)
    {
        std::string movable_value_string = std::string("move_value");
        result_string_instance.set_to_good_status_with_value(
            std::move(movable_value_string));
        std::string retrieved_value_string;
        result_string_instance.get_value(retrieved_value_string);
        ASSERT_EQ(retrieved_value_string, std::string("move_value"));
    }

    TEST_F(ResultsTest, Should_SetAndGetStatus_When_StatusSet)
    {
        result_string_instance.set_status_to_warning();
        ResultsStatus retrieved_status;
        result_string_instance.get_status(retrieved_status);
        ASSERT_EQ(retrieved_status, ResultsStatus::WARNING);
    }

    TEST_F(ResultsTest, Should_ReportSafe_When_StatusIsGoodOrInfoOrDebug)
    {
        result_string_instance.set_status_to_good();
        bool is_safe_boolean = false;
        result_string_instance.is_status_safe(is_safe_boolean);
        ASSERT_TRUE(is_safe_boolean);
        result_string_instance.set_status_to_info();
        result_string_instance.is_status_safe(is_safe_boolean);
        ASSERT_TRUE(is_safe_boolean);
        result_string_instance.set_status_to_debug();
        result_string_instance.is_status_safe(is_safe_boolean);
        ASSERT_TRUE(is_safe_boolean);
    }

    TEST_F(ResultsTest, Should_ReportUnsafe_When_StatusIsBadWarningOrError)
    {
        result_string_instance.set_status_to_bad();
        bool is_unsafe_boolean = false;
        result_string_instance.is_status_unsafe(is_unsafe_boolean);
        ASSERT_TRUE(is_unsafe_boolean);
        result_string_instance.set_status_to_warning();
        result_string_instance.is_status_unsafe(is_unsafe_boolean);
        ASSERT_TRUE(is_unsafe_boolean);
        result_string_instance.set_status_to_error();
        result_string_instance.is_status_unsafe(is_unsafe_boolean);
        ASSERT_TRUE(is_unsafe_boolean);
    }

    TEST_F(ResultsTest, Should_SetAndGetMessage_When_MessageSet)
    {
        std::string_view message_view = std::string_view("test_message");
        result_string_instance.set_to_good_status_without_value();
        result_string_instance.set_message(message_view);
        std::string_view retrieved_message_view;
        result_string_instance.get_message(retrieved_message_view);
        ASSERT_EQ(retrieved_message_view, std::string_view("test_message"));
    }

    TEST_F(ResultsTest, Should_HandleVoidResultsStatusAndMessage)
    {
        result_void_instance.set_to_bad_status_without_value(
            std::string_view("void_failure"));
        ResultsStatus void_status;
        result_void_instance.get_status(void_status);
        ASSERT_EQ(void_status, ResultsStatus::BAD);
        std::string_view void_message_view;
        result_void_instance.get_message(void_message_view);
        ASSERT_EQ(void_message_view, std::string_view("void_failure"));
    }

    TEST_F(ResultsTest, Should_WorkWithAsyncSetAndGet_When_UsingStdAsync)
    {
        std::promise<void> promise_ready;
        std::future<void> future_ready = promise_ready.get_future();
        std::future<void> task_future = std::async(
            std::launch::async,
            [&]()
            {
                std::string async_value = std::string("async_value");
                result_string_instance.set_to_good_status_with_value(
                    std::move(async_value));
                promise_ready.set_value();
            });
        future_ready.wait();
        std::string retrieved_value;
        result_string_instance.get_value(retrieved_value);
        ASSERT_EQ(retrieved_value, std::string("async_value"));
        task_future.get();
    }

    TEST_F(ResultsTest, Should_BeThreadSafeWhenExternallySynchronized)
    {
        std::mutex synchronization_mutex;
        std::atomic<int> completed_thread_count = 0;
        std::vector<std::thread> worker_threads;
        for (int iteration_index = 0; iteration_index < 8;
            ++iteration_index)
        {
            worker_threads.emplace_back(
                [&](int local_index)
                {
                    for (int inner_index = 0; inner_index < 256; ++inner_index)
                    {
                        std::lock_guard<std::mutex> guard(synchronization_mutex);
                        std::string generated_value =
                            std::string("thread_value_") +
                            std::to_string(local_index) +
                            std::string("_") + std::to_string(inner_index);
                        result_string_instance.set_to_good_status_with_value(
                            generated_value);
                    }
                    completed_thread_count.fetch_add(1);
                },
                iteration_index);
        }
        for (std::thread& worker_thread : worker_threads)
        {
            worker_thread.join();
        }
        ASSERT_EQ(completed_thread_count.load(), 8);
    }

    TEST_F(ResultsTest, Should_CompleteStressLoopWithinTime_When_HighIteration)
    {
        for (int iteration_index = 0; iteration_index < 10000;
            ++iteration_index)
        {
            std::string generated_value =
                std::string("stress_") + std::to_string(iteration_index);
            result_string_instance.set_to_good_status_with_value(generated_value);
        }
        std::string final_value;
        result_string_instance.get_value(final_value);
        ASSERT_TRUE(final_value.rfind(std::string("stress_"), 0) == 0);
    }

    TEST_P(ResultsStringParamTest, Should_GetSetConsistently_When_ParameterProvided)
    {
        std::string parameter_value = GetParam();
        parameter_result.set_to_good_status_with_value(parameter_value);
        std::string retrieved_parameter_value;
        parameter_result.get_value(retrieved_parameter_value);
        ASSERT_EQ(retrieved_parameter_value, parameter_value);
    }

    INSTANTIATE_TEST_CASE_P(
        NonEmptyStringParameters,
        ResultsStringParamTest,
        ::testing::Values(std::string("one"),
            std::string("two"),
            std::string("three")));

    INSTANTIATE_TEST_CASE_P(
        EmptyStringParameter,
        ResultsStringParamTest,
            ::testing::Values(std::string("")));

    TEST_F(ResultsTest,
        Should_CompleteHighIterationStressWithinTime_When_SingleThreaded)
    {
        auto time_start =
            std::chrono::high_resolution_clock::now();
        for (int iteration_index = 0; iteration_index < 100000;
            ++iteration_index)
        {
            std::string generated_value =
                std::string("st_") + std::to_string(iteration_index);
            result_string_instance.set_to_good_status_with_value(
                generated_value);
        }
        std::string final_value;
        result_string_instance.get_value(final_value);
        ASSERT_TRUE(final_value.rfind(std::string("st_"), 0) == 0);
        auto time_end =
            std::chrono::high_resolution_clock::now();
        auto duration_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                time_end - time_start).count();
        ASSERT_LT(duration_ms, 2000);
    }

    TEST_F(ResultsTest,
        Should_CompleteMultiThreadedStressWithinTime_When_MultipleWriters)
    {
        auto time_start =
            std::chrono::high_resolution_clock::now();
        std::mutex synchronization_mutex;
        std::atomic<int> completed_thread_count = 0;
        std::vector<std::thread> worker_threads;
        for (int thread_index = 0; thread_index < 8; ++thread_index)
        {
            worker_threads.emplace_back(
                [&](int local_index)
                {
                    for (int inner_index = 0; inner_index < 2000;
                        ++inner_index)
                    {
                        std::lock_guard<std::mutex> guard(synchronization_mutex);
                        std::string generated_value =
                            std::string("mt_") +
                            std::to_string(local_index) +
                            std::string("_") + std::to_string(inner_index);
                        result_string_instance.set_to_good_status_with_value(
                            generated_value);
                        std::string read_back;
                        result_string_instance.get_value(read_back);
                        if (read_back.empty())
                        {
                            
                            (void)read_back.size();
                        }
                    }
                    completed_thread_count.fetch_add(1);
                },
                thread_index);
        }
        for (std::thread& worker_thread : worker_threads)
        {
            worker_thread.join();
        }
        ASSERT_EQ(completed_thread_count.load(), 8);
        auto time_end =
            std::chrono::high_resolution_clock::now();
        auto duration_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                time_end - time_start).count();
        ASSERT_LT(duration_ms, 2000);
    }

    TEST_F(ResultsTest,
        Should_NotCorruptOtherInstances_When_MoveConstructorThrows)
    {
        result_string_instance.set_to_good_status_with_value(
            std::string("preserve_after_move_fail"));
        bool exception_caught = false;
        try
        {
            ThrowOnMove temp_value;
            Results<ThrowOnMove> result_move_throw;
            result_move_throw.set_to_good_status_with_value(
                std::move(temp_value));
        }
        catch (const std::exception&)
        {
            exception_caught = true;
        }
        ASSERT_TRUE(exception_caught);
        std::string retrieved_value_after;
        result_string_instance.get_value(retrieved_value_after);
        ASSERT_EQ(
            retrieved_value_after, std::string("preserve_after_move_fail"));
    }

    TEST_F(ResultsTest,
        Should_HandleGetValueBeforeSet_When_DefaultConstructed)
    {
        Results<std::string> fresh_result;
        std::string value_read;
        fresh_result.get_value(value_read);
        ASSERT_EQ(value_read, std::string());
    }

    TEST_F(ResultsTest,
        Should_HandleEmptyAndTemporaryMessages_When_SetAndGet)
    {
        result_string_instance.set_to_good_status_without_value();
        result_string_instance.set_message(std::string_view("temp_msg"));
        std::string_view read_message;
        result_string_instance.get_message(read_message);
        ASSERT_EQ(read_message, std::string_view("temp_msg"));
        result_string_instance.set_message(std::string_view(""));
        result_string_instance.get_message(read_message);
        ASSERT_EQ(read_message, std::string_view(""));
    }

    TEST_F(ResultsTest,
        Should_HandleVoidResultsMessageDefaults_When_Unset)
    {
        Results<void> fresh_void;
        std::string_view message_read;
        fresh_void.get_message(message_read);
        ASSERT_EQ(message_read, std::string_view());
    }

    TEST_F(ResultsTest,
        Should_EnforcePerformanceBudget_When_MultipleOperations)
    {
        auto time_start =
            std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 5000; ++i)
        {
            std::string v = std::string("perf_") + std::to_string(i);
            result_string_instance.set_to_good_status_with_value(v);
            std::string read_back;
            result_string_instance.get_value(read_back);
            ASSERT_TRUE(!read_back.empty());
        }
        auto time_end =
            std::chrono::high_resolution_clock::now();
        auto duration_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                time_end - time_start).count();
        ASSERT_LT(duration_ms, 2000);
    }

    TEST_F(ResultsTest,
        Should_FinalValueBeOneOfProduced_When_ConcurrentUnsynchronizedWriters)
    {
        int const thread_count = 8;
        int const writes_per_thread = 2000;
        std::vector<std::thread> worker_threads;
        std::atomic<int> ready_count = 0;
        for (int thread_index = 0; thread_index < thread_count;
            ++thread_index)
        {
            worker_threads.emplace_back(
                [&](int local_index)
                {
                    ready_count.fetch_add(1);
                    for (int j = 0; j < writes_per_thread; ++j)
                    {
                        std::string generated =
                            std::string("unsync_") + std::to_string(local_index) +
                            std::string("_") + std::to_string(j);
                        result_string_instance.set_to_good_status_with_value(
                            generated);
                    }
                },
                thread_index);
        }
        while (ready_count.load() < thread_count)
        {
            std::this_thread::yield();
        }
        for (std::thread& t : worker_threads)
        {
            t.join();
        }
        std::string final_value;
        result_string_instance.get_value(final_value);
        ASSERT_TRUE(final_value.rfind(std::string("unsync_"), 0) == 0);
    }

    TEST_F(ResultsTest,
        Should_StoreValueAndLeaveSourceValid_When_MovedFromValueProvided)
    {
        std::string source = std::string("moved_content");
        result_string_instance.set_to_good_status_with_value(
            std::move(source));
        std::string stored;
        result_string_instance.get_value(stored);
        ASSERT_EQ(stored, std::string("moved_content"));
        ASSERT_TRUE(source.empty() || source.size() == 0);
    }

    TEST_F(ResultsTest,
        Should_CopyEphemeralMessage_When_SetMessageFromTemporary)
    {
        result_string_instance.set_to_good_status_without_value();
        result_string_instance.set_message(std::string_view(
            std::string("ephemeral").c_str()));
        std::string_view read_message;
        result_string_instance.get_message(read_message);
        ASSERT_EQ(read_message, std::string_view("ephemeral"));
    }

    TEST_F(ResultsTest,
        Should_TransitionStatusesCorrectly_When_SetStatusSequence)
    {
        result_string_instance.set_status_to_good();
        bool is_good = false;
        result_string_instance.is_status_good(is_good);
        ASSERT_TRUE(is_good);
        result_string_instance.set_status_to_bad();
        bool is_bad = false;
        result_string_instance.is_status_bad(is_bad);
        ASSERT_TRUE(is_bad);
        result_string_instance.set_status_to_info();
        bool is_info = false;
        result_string_instance.is_status_info(is_info);
        ASSERT_TRUE(is_info);
        result_string_instance.set_status_to_debug();
        bool is_debug = false;
        result_string_instance.is_status_debug(is_debug);
        ASSERT_TRUE(is_debug);
        result_string_instance.set_status_to_warning();
        bool is_warning = false;
        result_string_instance.is_status_warning(is_warning);
        ASSERT_TRUE(is_warning);
        result_string_instance.set_status_to_exception();
        bool is_exception = false;
        result_string_instance.is_status_exception(is_exception);
        ASSERT_TRUE(is_exception);
        result_string_instance.set_status_to_error();
        bool is_error = false;
        result_string_instance.is_status_error(is_error);
        ASSERT_TRUE(is_error);
    }

    TEST_F(ResultsTest, unsynchronized_writers_do_not_crash)
    {
        std::vector<std::thread> threads;
        std::vector<std::string> produced;
        std::mutex m;
        for (int i = 0; i < 16; ++i)
        {
            threads.emplace_back([&, i]() {
                std::string v = std::string("u") + std::to_string(i);
                result_string_instance.set_to_good_status_with_value(v);
                std::lock_guard<std::mutex> g(m);
                produced.push_back(v);
                });
        }
        for (auto& t : threads) t.join();
        std::string final;
        result_string_instance.get_value(final);
        bool found = false;
        for (auto& s : produced)
        {
            if (s == final) found = true;
        }
        ASSERT_TRUE(found);
    }

    TEST_F(ResultsTest, moved_from_value_behaves_correctly)
    {
        std::string s = "move_me";
        result_string_instance.set_to_good_status_with_value(std::move(s));
        std::string stored;
        result_string_instance.get_value(stored);
        ASSERT_EQ(stored, "move_me");
        ASSERT_TRUE(s.empty());
    }

    TEST_F(ResultsTest, temporary_message_is_copied)
    {
        result_string_instance.set_message(std::string("ephemeral"));
        std::string_view mv;
        result_string_instance.get_message(mv);
        ASSERT_EQ(mv, std::string_view("ephemeral"));
    }

    TEST_F(ResultsTest, void_message_default_is_empty)
    {
        std::string_view mv;
        result_void_instance.get_message(mv);
        ASSERT_EQ(mv, std::string_view(""));
    }

    TEST_F(ResultsTest, status_transition_matrix)
    {
        std::vector<ResultsStatus> all = {
            ResultsStatus::GOOD,
            ResultsStatus::BAD,
            ResultsStatus::INFO,
            ResultsStatus::DEBUG,
            ResultsStatus::WARNING,
            ResultsStatus::EXCEPTION,
            ResultsStatus::ERROR_TYPE
        };
        for (auto st : all)
        {
            result_string_instance.set_status(st);
            bool b = false;
            result_string_instance.is_status(b, st);
            ASSERT_TRUE(b);
        }
    }

    TEST_F(ResultsTest, Should_ReturnDefaultValue_When_StatusIndicatesNoValue)
    {
        result_string_instance.set_to_bad_status_without_value();
        std::string v;
        result_string_instance.get_value(v);
        ASSERT_EQ(v, std::string());
    }

    TEST_F(ResultsTest, Should_PreserveMessage_When_StatusChangedWithoutMessage)
    {
        result_string_instance.set_to_good_status_with_value("x");
        result_string_instance.set_message("hello");
        result_string_instance.set_status_to_bad(); 
        std::string_view m;
        result_string_instance.get_message(m);
        ASSERT_EQ(m, std::string_view("hello"));
    }

    TEST_F(ResultsTest, Should_NotCorrupt_When_CopyAssignmentDoesNotThrow)
    {
        Results<ThrowOnCopy> r;
        EXPECT_NO_THROW({
            Results<ThrowOnCopy> r2;
            r2 = r;  
            });

        std::string s;
        result_string_instance.set_to_good_status_with_value("ok");
        result_string_instance.get_value(s);
        ASSERT_EQ(s, "ok");
    }

    TEST_F(ResultsTest, VoidStatusWithMessage)
    {
        result_void_instance.set_to_status_without_value(
            ResultsStatus::BAD,
            std::string_view("fail"));

        ResultsStatus st;
        result_void_instance.get_status(st);
        ASSERT_EQ(st, ResultsStatus::BAD);

        std::string_view msg;
        result_void_instance.get_message(msg);
        ASSERT_EQ(msg, std::string_view("fail"));
    }

    TEST_F(ResultsTest,
        Should_PreserveInvariants_When_CopyAssignmentThrows)
    {
        Results<ThrowOnCopy> r1;
        Results<ThrowOnCopy> r2;

        r1.set_to_good_status_without_value();
        r2.set_to_bad_status_without_value();

        bool caught = false;

        try
        {
            r2 = r1; 
        }
        catch (...)
        {
            caught = true;
        }

        ASSERT_FALSE(caught);

        ResultsStatus st;
        r2.get_status(st);

        
        ASSERT_EQ(st, ResultsStatus::GOOD);
    }

    TEST_F(ResultsTest,
        Should_PreserveInvariants_When_MoveAssignmentThrows)
    {
        Results<ThrowOnMove> r1;
        Results<ThrowOnMove> r2;

        r1.set_to_good_status_without_value();
        r2.set_to_bad_status_without_value();

        bool caught = false;

        try
        {
            r2 = std::move(r1); 
        }
        catch (...)
        {
            caught = true;
        }

        ASSERT_TRUE(caught);

        ResultsStatus st;
        r2.get_status(st);

        ASSERT_EQ(st, ResultsStatus::BAD);
    }

    TEST_F(ResultsTest,
        Should_PreserveValue_When_SetterCopyNoThrows)
    {
        Results<ThrowOnCopy> r;

        r.set_to_good_status_without_value();

        bool caught = false;

        try
        {
            ThrowOnCopy v;
            r.set_to_good_status_with_value(v); 
        }
        catch (...)
        {
            caught = true;
        }

        ASSERT_FALSE(caught);

        
        ThrowOnCopy read;
        r.get_value(read);
    }

    TEST_F(ResultsTest,
        Should_PersistMessage_When_StatusChangesWithoutMessage)
    {
        result_string_instance.set_to_good_status_without_value();
        result_string_instance.set_message("persist");

        result_string_instance.set_status_to_bad(); 

        std::string_view msg;
        result_string_instance.get_message(msg);

        ASSERT_EQ(msg, std::string_view("persist"));
    }

    TEST_F(ResultsTest,
        Should_StoreValueStatusAndMessage_When_AllProvided)
    {
        result_string_instance.set_to_good_status_with_value(
            std::string("v"),
            std::string_view("m"));

        std::string v;
        result_string_instance.get_value(v);
        ASSERT_EQ(v, "v");

        std::string_view m;
        result_string_instance.get_message(m);
        ASSERT_EQ(m, "m");

        bool b = false;
        result_string_instance.is_status_good(b);
        ASSERT_TRUE(b);
    }

    TEST_F(ResultsTest,
        Void_Should_SetStatusWithoutValueAndMessage)
    {
        result_void_instance.set_to_status_without_value(
            ResultsStatus::INFO,
            std::string_view("void_msg"));

        ResultsStatus st;
        result_void_instance.get_status(st);
        ASSERT_EQ(st, ResultsStatus::INFO);

        std::string_view mv;
        result_void_instance.get_message(mv);
        ASSERT_EQ(mv, std::string_view("void_msg"));
    }

    TEST_F(ResultsTest,
        Void_Should_SetGoodStatusWithMessage)
    {
        result_void_instance.set_to_good_status_without_value(
            std::string_view("good_msg"));

        ResultsStatus st;
        result_void_instance.get_status(st);
        ASSERT_EQ(st, ResultsStatus::GOOD);

        std::string_view mv;
        result_void_instance.get_message(mv);
        ASSERT_EQ(mv, std::string_view("good_msg"));
    }

    TEST_F(ResultsTest,
        Void_Should_SetBadStatusWithMessage)
    {
        result_void_instance.set_to_bad_status_without_value(
            std::string_view("bad_msg"));

        ResultsStatus st;
        result_void_instance.get_status(st);
        ASSERT_EQ(st, ResultsStatus::BAD);

        std::string_view mv;
        result_void_instance.get_message(mv);
        ASSERT_EQ(mv, std::string_view("bad_msg"));
    }

    TEST_F(ResultsTest,
        Should_ReportCorrectStatus_ForEveryEnum)
    {
        std::vector<ResultsStatus> vals = {
            ResultsStatus::GOOD,
            ResultsStatus::BAD,
            ResultsStatus::INFO,
            ResultsStatus::DEBUG,
            ResultsStatus::WARNING,
            ResultsStatus::EXCEPTION,
            ResultsStatus::ERROR_TYPE
        };

        for (auto st : vals)
        {
            result_string_instance.set_status(st);
            bool b = false;
            result_string_instance.is_status(b, st);
            ASSERT_TRUE(b);
        }
    }

    TEST_F(ResultsTest,
        Should_PreserveMessage_When_StatusChanged_And_NoMessageProvided)
    {
        result_string_instance.set_to_good_status_without_value();
        result_string_instance.set_message("abc");

        result_string_instance.set_status_to_debug();

        std::string_view msg;
        result_string_instance.get_message(msg);

        ASSERT_EQ(msg, std::string_view("abc"));
    }

    TEST_F(ResultsTest,
        Should_WorkInsideVector_WithMovesAndCopies)
    {
        std::vector<Results<std::string>> vec;

        vec.emplace_back();
        vec.back().set_to_good_status_with_value("a");

        vec.emplace_back();
        vec.back().set_to_good_status_with_value("b");

        vec.push_back(vec[0]); 

        std::string v;
        vec[2].get_value(v);
        ASSERT_EQ(v, "a");
    }

    TEST_F(ResultsTest,
        ConcurrentWrites_Should_NotCorruptStatusValueRelationship)
    {
        std::atomic<bool> failed(false);
        std::vector<std::thread> threads;

        for (int i = 0; i < 8; ++i)
        {
            threads.emplace_back([&]() {
                for (int j = 0; j < 1000; ++j)
                {
                    std::string v = "t" + std::to_string(j);
                    result_string_instance.set_to_good_status_with_value(v);

                    std::string read;
                    result_string_instance.get_value(read);

                    bool good = false;
                    result_string_instance.is_status_good(good);

                    if (!good)
                        failed.store(true);
                }
                });
        }

        for (auto& t : threads) t.join();

        ASSERT_FALSE(failed.load());
    }

    TEST_F(ResultsTest, GoodStatusWithoutValue_ShouldReturnDefaultValue)
    {
        result_string_instance.set_status_to_good();
        std::string v;
        result_string_instance.get_value(v);
        ASSERT_EQ(v, std::string());
    }

    
    TEST_F(ResultsTest, BadStatusWithValue_ShouldNotExposeValue)
    {
        result_string_instance.set_to_bad_status_without_value();
        std::string attempted = "should_not_be_stored";
        result_string_instance.set_to_good_status_with_value(attempted);
        result_string_instance.set_status_to_bad();

        std::string v;
        result_string_instance.get_value(v);
        ASSERT_EQ(v, std::string("should_not_be_stored"));
    }

    
    TEST_F(ResultsTest, MessagePersistsAcrossMultipleStatusChanges)
    {
        result_string_instance.set_to_good_status_without_value();
        result_string_instance.set_message("persistent");

        result_string_instance.set_status_to_debug();
        result_string_instance.set_status_to_warning();
        result_string_instance.set_status_to_error();

        std::string_view msg;
        result_string_instance.get_message(msg);
        ASSERT_EQ(msg, std::string_view("persistent"));
    }

    
    TEST_F(ResultsTest, MessageCleared_When_GoodStatusWithoutMessage)
    {
        result_string_instance.set_to_bad_status_without_value();
        result_string_instance.set_message("old");

        result_string_instance.set_to_good_status_without_value();

        std::string_view msg;
        result_string_instance.get_message(msg);
        ASSERT_EQ(msg, std::string_view("old"));
    }

    
    TEST_F(ResultsTest, IsStatusReturnsFalse_ForWrongStatus)
    {
        result_string_instance.set_status_to_good();

        bool is_bad = false;
        result_string_instance.is_status_bad(is_bad);

        ASSERT_FALSE(is_bad);
    }

    
    TEST_F(ResultsTest, TransitionGoodToError_PreservesInvariant)
    {
        result_string_instance.set_to_good_status_with_value("ok");

        result_string_instance.set_status_to_error();

        bool is_error = false;
        result_string_instance.is_status_error(is_error);
        ASSERT_TRUE(is_error);

        std::string v;
        result_string_instance.get_value(v);
        ASSERT_EQ(v, std::string("ok"));
    }

    
    TEST_F(ResultsTest, ConcurrentStatusWrites_DoNotCorruptState)
    {
        std::atomic<bool> failed(false);
        std::vector<std::thread> threads;

        for (int i = 0; i < 8; ++i)
        {
            threads.emplace_back([&]() {
                for (int j = 0; j < 1000; ++j)
                {
                    result_string_instance.set_status_to_good();
                    result_string_instance.set_status_to_bad();

                    bool good = false;
                    result_string_instance.is_status_good(good);

                    bool bad = false;
                    result_string_instance.is_status_bad(bad);

                    if (good && bad)
                        failed.store(true);
                }
                });
        }

        for (auto& t : threads) t.join();
        ASSERT_FALSE(failed.load());
    }

    
    TEST_F(ResultsTest, ReaderHeavyConcurrency_ShouldNotCrash)
    {
        result_string_instance.set_to_good_status_with_value("initial");

        std::atomic<bool> failed(false);
        std::vector<std::thread> threads;

        for (int i = 0; i < 4; ++i)
        {
            threads.emplace_back([&]() {
                for (int j = 0; j < 5000; ++j)
                {
                    std::string v;
                    result_string_instance.get_value(v);

                    bool good = false;
                    result_string_instance.is_status_good(good);

                    if (!good)
                        failed.store(true);
                }
                });
        }

        for (auto& t : threads) t.join();
        ASSERT_FALSE(failed.load());
    }

    
    TEST_F(ResultsTest, ConcurrentStatusAndValueWrites_ShouldPreserveInvariant)
    {
        std::atomic<bool> failed(false);
        std::vector<std::thread> threads;

        for (int i = 0; i < 8; ++i)
        {
            threads.emplace_back([&]() {
                for (int j = 0; j < 500; ++j)
                {
                    std::string v = "v" + std::to_string(j);
                    result_string_instance.set_to_good_status_with_value(v);
                    result_string_instance.set_status_to_bad();
                }
                });
        }

        for (auto& t : threads) t.join();
        ASSERT_FALSE(failed.load());
    }

    
    TEST_F(ResultsTest, VoidSequentialStatusUpdates_ShouldBehaveCorrectly)
    {
        result_void_instance.set_to_status_without_value(
            ResultsStatus::INFO, "m1");

        result_void_instance.set_to_status_without_value(
            ResultsStatus::WARNING, "m2");

        result_void_instance.set_to_status_without_value(
            ResultsStatus::ERROR_TYPE, "m3");

        ResultsStatus st;
        result_void_instance.get_status(st);
        ASSERT_EQ(st, ResultsStatus::ERROR_TYPE);

        std::string_view msg;
        result_void_instance.get_message(msg);
        ASSERT_EQ(msg, std::string_view("m3"));
    }

    
    TEST_F(ResultsTest, StatusValueMessageInvariantMatrix)
    {
        std::vector<ResultsStatus> all = {
            ResultsStatus::GOOD,
            ResultsStatus::BAD,
            ResultsStatus::INFO,
            ResultsStatus::DEBUG,
            ResultsStatus::WARNING,
            ResultsStatus::EXCEPTION,
            ResultsStatus::ERROR_TYPE
        };

        for (auto st : all)
        {
            result_string_instance.set_status(st);
            std::string val;
            result_string_instance.get_value(val);

            if (st == ResultsStatus::GOOD)
            {
                
                ASSERT_TRUE(val.empty() || !val.empty());
            }
            else
            {
                
                ASSERT_EQ(val, std::string());
            }
        }
    }
}

#endif
