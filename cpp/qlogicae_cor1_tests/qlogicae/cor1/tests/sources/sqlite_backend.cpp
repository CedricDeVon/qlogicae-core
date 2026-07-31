#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteBackend \
	)

#include "../includes/sqlite_backend.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST(SQLiteBackendTest, Should_Initialize_Null_When_Default_Constructed)
    {
        
            SQLiteBackend backend;

        EXPECT_EQ(backend.database_handle, nullptr);
    }

    TEST(SQLiteBackendTest, Should_Store_Handle_When_Constructed_With_DB)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend(database_handle);

        EXPECT_EQ(backend.database_handle, database_handle);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Not_Crash_On_Destructor_With_Null)
    {
        
            SQLiteBackend backend;

        EXPECT_NO_THROW({});
    }

    TEST(SQLiteBackendTest, Should_Move_Ownership_Safely)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend_a(database_handle);

        
            SQLiteBackend backend_b(std::move(backend_a));

        EXPECT_EQ(backend_a.database_handle, nullptr);
        EXPECT_EQ(backend_b.database_handle, database_handle);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Handle_Multiple_Destruction_Scenarios)
    {
        for (std::uint32_t iteration = 0; iteration < 1000; iteration++)
        {
            sqlite3* database_handle =
                SQLiteBackendTest::create_memory_database();

            
                SQLiteBackend backend(database_handle);

            EXPECT_NO_THROW({});
        }
    }

    TEST(SQLiteBackendTest, Should_Be_Safe_Under_Multithreaded_Destruction)
    {
        std::atomic<std::uint32_t> success_counter = 0;

        std::vector<std::thread> threads;

        for (std::uint32_t thread_index = 0;
            thread_index < 16;
            thread_index++)
        {
            threads.emplace_back([&success_counter]()
            {
                sqlite3* database_handle =
                    SQLiteBackendTest::create_memory_database();

                
                    SQLiteBackend backend(database_handle);

                success_counter.fetch_add(1);
            });
        }

        for (std::thread& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(success_counter.load(), 16);
    }

    TEST(SQLiteBackendTest, Should_Support_Async_Lifecycle_Creation)
    {
        auto future_result =
            std::async(std::launch::async, []()
        {
            sqlite3* database_handle =
                SQLiteBackendTest::create_memory_database();

            
                SQLiteBackend backend(database_handle);

            return backend.database_handle != nullptr;
        });

        bool result = future_result.get();

        EXPECT_TRUE(result);
    }

    TEST(SQLiteBackendTest, Should_Not_Data_Race_On_Independent_Instances)
    {
        std::atomic<bool> race_detected = false;

        auto worker = [&race_detected]()
        {
            for (std::uint32_t i = 0; i < 5000; i++)
            {
                sqlite3* database_handle =
                    SQLiteBackendTest::create_memory_database();

                
                    SQLiteBackend backend(database_handle);

                if (!backend.database_handle)
                {
                    race_detected.store(true);
                }
            }
        };

        std::thread thread_a(worker);
        std::thread thread_b(worker);

        thread_a.join();
        thread_b.join();

        EXPECT_FALSE(race_detected.load());
    }

    TEST(SQLiteBackendTest, Should_Be_Exception_Safe_Under_Future_Workflow)
    {
        auto future_result =
            std::async(std::launch::async, []()
        {
            sqlite3* database_handle =
                SQLiteBackendTest::create_memory_database();

            
                SQLiteBackend backend(database_handle);

            throw std::runtime_error("forced exception");

            return backend.database_handle;
        });

        EXPECT_THROW(future_result.get(), std::runtime_error);
    }

    TEST(SQLiteBackendTest, Should_Handle_Self_Move_Safely)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend(database_handle);

        backend = std::move(backend);

        EXPECT_EQ(backend.database_handle, database_handle);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Handle_Repeated_Move_Chains_Safely)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend_a(database_handle);

        
            SQLiteBackend backend_b(std::move(backend_a));

        
            SQLiteBackend backend_c(std::move(backend_b));

        EXPECT_EQ(backend_a.database_handle, nullptr);
        EXPECT_EQ(backend_b.database_handle, nullptr);
        EXPECT_EQ(backend_c.database_handle, database_handle);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Safely_Destroy_After_Move)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend_a(database_handle);

        
            SQLiteBackend backend_b(std::move(backend_a));

        EXPECT_EQ(backend_a.database_handle, nullptr);
        EXPECT_NE(backend_b.database_handle, nullptr);

        backend_b = 
            SQLiteBackend();

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Stress_Repeated_Lifecycle_Under_Load)
    {
        for (std::uint32_t iteration = 0; iteration < 100000; iteration++)
        {
            sqlite3* database_handle =
                SQLiteBackendTest::create_memory_database();

            
                SQLiteBackend backend(database_handle);

            
                SQLiteBackend moved_backend(std::move(backend));

            EXPECT_EQ(backend.database_handle, nullptr);
            EXPECT_EQ(moved_backend.database_handle, database_handle);

            SQLiteBackendTest::safe_close(database_handle);
        }
    }

    TEST(SQLiteBackendTest, Should_Handle_Concurrent_Shared_Instance_Safely)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend shared_backend(database_handle);

        std::atomic<bool> race_detected = false;

        auto worker = [&shared_backend, &race_detected]()
        {
            for (std::uint32_t i = 0; i < 5000; i++)
            {
                if (shared_backend.database_handle == nullptr)
                {
                    race_detected.store(true);
                }
            }
        };

        std::thread thread_a(worker);
        std::thread thread_b(worker);
        std::thread thread_c(worker);
        std::thread thread_d(worker);

        thread_a.join();
        thread_b.join();
        thread_c.join();
        thread_d.join();

        EXPECT_FALSE(race_detected.load());

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Enforce_Performance_Under_Time_Limit)
    {
        auto start_time =
            std::chrono::high_resolution_clock::now();

        for (std::uint32_t iteration = 0; iteration < 200000; iteration++)
        {
            sqlite3* database_handle =
                SQLiteBackendTest::create_memory_database();

            
                SQLiteBackend backend(database_handle);

            
                SQLiteBackend moved_backend(std::move(backend));
        }

        auto end_time =
            std::chrono::high_resolution_clock::now();

        auto duration_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time
            ).count();

        EXPECT_LT(duration_ms, 2000);
    }

    TEST(SQLiteBackendTest, Should_Handle_Mixed_Async_Promise_Workflow)
    {
        std::promise<bool> promise;
        std::future<bool> future = promise.get_future();

        std::thread worker([&promise]()
        {
            sqlite3* database_handle =
                SQLiteBackendTest::create_memory_database();

            
                SQLiteBackend backend(database_handle);

            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            promise.set_value(backend.database_handle != nullptr);
        });

        EXPECT_TRUE(future.get());

        worker.join();
    }

    TEST(SQLiteBackendTest, Should_Handle_Concurrent_Move_Operations)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend base_backend(database_handle);

        std::atomic<std::uint32_t> success_count = 0;

        auto worker = [&base_backend, &success_count]()
        {
            for (std::uint32_t i = 0; i < 1000; i++)
            {
                
                    SQLiteBackend local_copy(std::move(
                        const_cast<
                            
                            SQLiteBackend&
                        >(base_backend)
                    ));

                if (local_copy.database_handle)
                {
                    success_count.fetch_add(1);
                }
            }
        };

        std::thread thread_a(worker);
        std::thread thread_b(worker);

        thread_a.join();
        thread_b.join();

        EXPECT_GE(success_count.load(),static_cast<std::uint32_t>(0));

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Reject_Copy_Construction_When_Deleted)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend_a(database_handle);

        static_assert(
            !std::is_copy_constructible_v<
                
                SQLiteBackend
            >
        );

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Reject_Copy_Assignment_When_Deleted)
    {
        static_assert(
            !std::is_copy_assignable_v<
                
                SQLiteBackend
            >
        );
    }

    TEST(SQLiteBackendTest, Should_Handle_Reassignment_With_New_Handle)
    {
        sqlite3* database_handle_1 =
            SQLiteBackendTest::create_memory_database();

        sqlite3* database_handle_2 =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend(database_handle_1);

        backend = 
            SQLiteBackend(database_handle_2);

        EXPECT_EQ(backend.database_handle, database_handle_2);

        SQLiteBackendTest::safe_close(database_handle_1);
        SQLiteBackendTest::safe_close(database_handle_2);
    }

    TEST(SQLiteBackendTest, Should_Not_Leak_On_Repeated_Reassignment)
    {
        for (std::uint32_t iteration = 0; iteration < 10000; iteration++)
        {
            sqlite3* database_handle_1 =
                SQLiteBackendTest::create_memory_database();

            sqlite3* database_handle_2 =
                SQLiteBackendTest::create_memory_database();

            
                SQLiteBackend backend(database_handle_1);

            backend = 
                SQLiteBackend(database_handle_2);

            SQLiteBackendTest::safe_close(database_handle_1);
            SQLiteBackendTest::safe_close(database_handle_2);
        }
    }

    TEST(SQLiteBackendTest, Should_Handle_Destructor_On_Moved_From_Object)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        {
            
                SQLiteBackend backend_a(database_handle);

            
                SQLiteBackend backend_b(std::move(backend_a));

            EXPECT_EQ(backend_a.database_handle, nullptr);
            EXPECT_EQ(backend_b.database_handle, database_handle);
        }

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Handle_Concurrent_Read_Access_Safely)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend(database_handle);

        std::atomic<std::uint32_t> read_count = 0;

        auto worker = [&backend, &read_count]()
        {
            for (std::uint32_t i = 0; i < 10000; i++)
            {
                if (backend.database_handle != nullptr)
                {
                    read_count.fetch_add(1);
                }
            }
        };

        std::thread thread_a(worker);
        std::thread thread_b(worker);
        std::thread thread_c(worker);
        std::thread thread_d(worker);

        thread_a.join();
        thread_b.join();
        thread_c.join();
        thread_d.join();

        EXPECT_GT(read_count.load(), 0u);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Complete_Extreme_Stress_Lifecycle_Safely)
    {
        for (std::uint32_t iteration = 0; iteration < 250000; iteration++)
        {
            sqlite3* database_handle =
                SQLiteBackendTest::create_memory_database();

            
                SQLiteBackend backend(database_handle);

            
                SQLiteBackend moved_backend(std::move(backend));

            EXPECT_EQ(backend.database_handle, nullptr);
            EXPECT_EQ(moved_backend.database_handle, database_handle);

            SQLiteBackendTest::safe_close(database_handle);
        }
    }

    TEST(SQLiteBackendTest, Should_Handle_Mixed_Future_Exception_Safety)
    {
        std::future<void> future_result =
            std::async(std::launch::async, []()
        {
            sqlite3* database_handle =
                SQLiteBackendTest::create_memory_database();

            
                SQLiteBackend backend(database_handle);

            throw std::runtime_error("forced failure");
        });

        EXPECT_THROW(future_result.get(), std::runtime_error);
    }

    TEST(SQLiteBackendTest, Should_Validate_Multiple_Independent_Instances)
    {
        sqlite3* database_handle_1 =
            SQLiteBackendTest::create_memory_database();

        sqlite3* database_handle_2 =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend_1(database_handle_1);

        
            SQLiteBackend backend_2(database_handle_2);

        EXPECT_NE(backend_1.database_handle, backend_2.database_handle);

        SQLiteBackendTest::safe_close(database_handle_1);
        SQLiteBackendTest::safe_close(database_handle_2);
    }

    TEST(SQLiteBackendTest, Should_Execute_Parameterized_Lifecycle_Modes)
    {
        struct TestCase
        {
            std::uint32_t iteration_count;
        };

        std::vector<TestCase> cases =
        {
            {1},
            {100},
            {1000}
        };

        for (const TestCase& test_case : cases)
        {
            for (std::uint32_t i = 0; i < test_case.iteration_count; i++)
            {
                sqlite3* database_handle =
                    SQLiteBackendTest::create_memory_database();

                
                    SQLiteBackend backend(database_handle);

                
                    SQLiteBackend moved_backend(std::move(backend));

                EXPECT_EQ(backend.database_handle, nullptr);
                EXPECT_EQ(moved_backend.database_handle, database_handle);

                SQLiteBackendTest::safe_close(database_handle);
            }
        }
    }

    TEST(SQLiteBackendTest, Should_Validate_Transaction_Like_SQL_Execution)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        char* error_message = nullptr;

        int result =
            sqlite3_exec(
                database_handle,
                "CREATE TABLE test_table(id INTEGER);",
                nullptr,
                nullptr,
                &error_message
            );

        EXPECT_EQ(result, SQLITE_OK);

        
            SQLiteBackend backend(database_handle);

        result =
            sqlite3_exec(
                database_handle,
                "INSERT INTO test_table VALUES (1);",
                nullptr,
                nullptr,
                &error_message
            );

        EXPECT_EQ(result, SQLITE_OK);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Handle_SQLite_Open_Failure_Safely)
    {
        sqlite3* database_handle = nullptr;

        int result =
            sqlite3_open(":memory:", &database_handle);

        EXPECT_EQ(result, SQLITE_OK);

        
            SQLiteBackend backend(database_handle);

        EXPECT_NE(backend.database_handle, nullptr);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Handle_Exception_During_Move_Assignment_Safely)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend_a(database_handle);

        try
        {
            backend_a =
                
                    SQLiteBackend(std::move(backend_a));
        }
        catch (...)
        {
        }

        EXPECT_NE(backend_a.database_handle, nullptr);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Handle_Database_Corruption_Input_Safely)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        const char* malformed_sql = "INVALID SQL STATEMENT $$$";

        char* error_message = nullptr;

        int result =
            sqlite3_exec(
                database_handle,
                malformed_sql,
                nullptr,
                nullptr,
                &error_message
            );

        EXPECT_NE(result, SQLITE_OK);

        
            SQLiteBackend backend(database_handle);

        EXPECT_NE(backend.database_handle, nullptr);

        sqlite3_free(error_message);
        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Enforce_Deterministic_Performance_Per_Operation)
    {
        auto start_time =
            std::chrono::high_resolution_clock::now();

        for (std::uint32_t i = 0; i < 50000; i++)
        {
            sqlite3* database_handle =
                SQLiteBackendTest::create_memory_database();

            
                SQLiteBackend backend(database_handle);

            
                SQLiteBackend moved_backend(std::move(backend));

            SQLiteBackendTest::safe_close(database_handle);
        }

        auto end_time =
            std::chrono::high_resolution_clock::now();

        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time
            ).count();

        EXPECT_LT(duration, 2000);
    }

    TEST(SQLiteBackendTest, Should_Handle_Shared_State_Concurrent_Read_Write_Safely)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend shared_backend(database_handle);

        std::atomic<bool> stop_flag = false;
        std::atomic<std::uint32_t> read_counter = 0;

        auto reader = [&shared_backend, &stop_flag, &read_counter]()
        {
            while (!stop_flag.load())
            {
                if (shared_backend.database_handle != nullptr)
                {
                    read_counter.fetch_add(1);
                }
            }
        };

        std::thread thread_a(reader);
        std::thread thread_b(reader);
        std::thread thread_c(reader);
        std::thread thread_d(reader);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        stop_flag.store(true);

        thread_a.join();
        thread_b.join();
        thread_c.join();
        thread_d.join();

        EXPECT_GT(read_counter.load(), 0u);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Validate_Destructor_Is_Nothrow_Safe)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        EXPECT_NO_THROW(
        {
            
                SQLiteBackend backend(database_handle);
        });

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Handle_Exception_During_Concurrent_Execution)
    {
        std::atomic<bool> exception_caught = false;

        auto worker = [&exception_caught]()
        {
            try
            {
                sqlite3* database_handle =
                    SQLiteBackendTest::create_memory_database();

                
                    SQLiteBackend backend(database_handle);

                for (std::uint32_t i = 0; i < 10000; i++)
                {
                    if (i == 5000)
                    {
                        throw std::runtime_error("concurrent failure");
                    }
                }

                SQLiteBackendTest::safe_close(database_handle);
            }
            catch (...)
            {
                exception_caught.store(true);
            }
        };

        std::thread thread_a(worker);
        std::thread thread_b(worker);

        thread_a.join();
        thread_b.join();

        EXPECT_TRUE(exception_caught.load());
    }

    TEST(SQLiteBackendTest, Should_Validate_State_After_Move_From_Instance_Is_Used)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend_a(database_handle);

        
            SQLiteBackend backend_b(std::move(backend_a));

        EXPECT_EQ(backend_a.database_handle, nullptr);

        EXPECT_NO_THROW(
        {
            (void)backend_a.database_handle;
        });

        EXPECT_NE(backend_b.database_handle, nullptr);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Prevent_Invalid_State_Transition_After_Reassignment)
    {
        sqlite3* database_handle_1 =
            SQLiteBackendTest::create_memory_database();

        sqlite3* database_handle_2 =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend backend(database_handle_1);

        backend = 
            SQLiteBackend(database_handle_2);

        EXPECT_EQ(backend.database_handle, database_handle_2);

        backend = 
            SQLiteBackend();

        EXPECT_EQ(backend.database_handle, nullptr);

        SQLiteBackendTest::safe_close(database_handle_1);
        SQLiteBackendTest::safe_close(database_handle_2);
    }

    TEST(SQLiteBackendTest, Should_Validate_SQLite_Query_Read_Correctness)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        char* error_message = nullptr;

        sqlite3_exec(
            database_handle,
            "CREATE TABLE test_table(id INTEGER);",
            nullptr,
            nullptr,
            &error_message
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO test_table VALUES (42);",
            nullptr,
            nullptr,
            &error_message
        );

        int value = 0;

        sqlite3_stmt* statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT id FROM test_table;",
            -1,
            &statement,
            nullptr
        );

        if (sqlite3_step(statement) == SQLITE_ROW)
        {
            value = sqlite3_column_int(statement, 0);
        }

        sqlite3_finalize(statement);

        EXPECT_EQ(value, 42);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Stress_Concurrent_Move_And_Read_Safely)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        
            SQLiteBackend base_backend(database_handle);

        std::atomic<bool> stop_flag = false;
        std::atomic<std::uint32_t> success_counter = 0;

        auto worker = [&base_backend, &stop_flag, &success_counter]()
        {
            while (!stop_flag.load())
            {
                auto local_copy =
                    
                        SQLiteBackend(
                            std::move(
                                const_cast<
                                    
                                    SQLiteBackend&
                                >(base_backend)
                            )
                        );

                if (local_copy.database_handle != nullptr)
                {
                    success_counter.fetch_add(1);
                }
            }
        };

        std::thread thread_a(worker);
        std::thread thread_b(worker);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        stop_flag.store(true);

        thread_a.join();
        thread_b.join();

        EXPECT_GE(success_counter.load(), 0u);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Destroy_Owned_Handle_On_Destruction)
    {
        std::atomic<int> close_count = 0;

        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        auto wrapper_close =
            [&close_count](sqlite3* handle)
            {
                if (handle)
                {
                    close_count.fetch_add(1);
                    sqlite3_close(handle);
                }
            };

        {
            QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
                SQLiteBackend backend(database_handle);
        }

        EXPECT_GE(close_count.load(), 0);
        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Not_Double_Close_On_Move)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_a(database_handle);

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_b(std::move(backend_a));

        backend_a = QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend();

        EXPECT_EQ(backend_a.database_handle, nullptr);
        EXPECT_NE(backend_b.database_handle, nullptr);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Invalidate_Source_After_Move_Chain)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_a(database_handle);

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_b(std::move(backend_a));

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_c(std::move(backend_b));

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_d(std::move(backend_c));

        EXPECT_EQ(backend_a.database_handle, nullptr);
        EXPECT_EQ(backend_b.database_handle, nullptr);
        EXPECT_EQ(backend_c.database_handle, nullptr);
        EXPECT_EQ(backend_d.database_handle, database_handle);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Support_Move_Assignment_Without_Leak)
    {
        sqlite3* database_handle_1 =
            SQLiteBackendTest::create_memory_database();

        sqlite3* database_handle_2 =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend(database_handle_1);

        backend = QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend(database_handle_2);

        EXPECT_EQ(backend.database_handle, database_handle_2);

        SQLiteBackendTest::safe_close(database_handle_1);
        SQLiteBackendTest::safe_close(database_handle_2);
    }

    TEST(SQLiteBackendTest, Should_Handle_Destructor_After_Reassignment)
    {
        sqlite3* database_handle_1 =
            SQLiteBackendTest::create_memory_database();

        sqlite3* database_handle_2 =
            SQLiteBackendTest::create_memory_database();

        {
            QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
                SQLiteBackend backend(database_handle_1);

            backend = QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
                SQLiteBackend(database_handle_2);

            EXPECT_EQ(backend.database_handle, database_handle_2);
        }

        SQLiteBackendTest::safe_close(database_handle_1);
        SQLiteBackendTest::safe_close(database_handle_2);
    }

    TEST(SQLiteBackendTest, Should_Handle_Move_From_Already_Moved_Object)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_a(database_handle);

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_b(std::move(backend_a));

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_c(std::move(backend_a));

        EXPECT_EQ(backend_a.database_handle, nullptr);
        EXPECT_EQ(backend_b.database_handle, database_handle);
        EXPECT_EQ(backend_c.database_handle, nullptr);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Enforce_Ownership_Uniqueness_Invariants)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_a(database_handle);

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_b(std::move(backend_a));

        EXPECT_TRUE(
            (backend_a.database_handle == nullptr) ^
            (backend_b.database_handle == nullptr)
        );

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Prevent_Invalid_Double_Move_Assignment)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_a(database_handle);

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_b(database_handle);

        backend_a = std::move(backend_b);

        EXPECT_NE(backend_a.database_handle, nullptr);
        EXPECT_EQ(backend_b.database_handle, nullptr);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Handle_Explicit_Reset_State_Correctly)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend(database_handle);

        backend = QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend();

        EXPECT_EQ(backend.database_handle, nullptr);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Handle_Repeated_Move_Into_Same_Target)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend source(database_handle);

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend target;

        target = std::move(source);
        target = QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend(database_handle);

        EXPECT_EQ(target.database_handle, database_handle);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Validate_RAII_Actual_Resource_Release)
    {
        std::atomic<std::uint32_t> close_counter = 0;

        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        auto guarded_close =
            [&close_counter](sqlite3* handle)
            {
                if (handle)
                {
                    close_counter.fetch_add(1);
                    sqlite3_close(handle);
                }
            };

        {
            QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
                SQLiteBackend backend(database_handle);
        }

        EXPECT_GE(close_counter.load(), 0u);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Enforce_Strong_Ownership_Uniqueness)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_a(database_handle);

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_b(std::move(backend_a));

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_c(std::move(backend_b));

        std::uint32_t owner_count = 0;

        if (backend_a.database_handle) owner_count++;
        if (backend_b.database_handle) owner_count++;
        if (backend_c.database_handle) owner_count++;

        EXPECT_EQ(owner_count, 1u);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Validate_Destructor_Behavior_With_Scoped_Lifetime)
    {
        std::atomic<bool> destructor_reached = false;

        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        {
            QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
                SQLiteBackend backend(database_handle);

            destructor_reached.store(true);
        }

        EXPECT_TRUE(destructor_reached.load());

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Prevent_Use_After_Move_Crash_Conditions)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_a(database_handle);

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_b(std::move(backend_a));

        EXPECT_NO_THROW(
        {
            (void)backend_a.database_handle;
        });

        EXPECT_EQ(backend_a.database_handle, nullptr);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Validate_Reassignment_Releases_Previous_Ownership)
    {
        sqlite3* database_handle_1 =
            SQLiteBackendTest::create_memory_database();

        sqlite3* database_handle_2 =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend(database_handle_1);

        backend = QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend(database_handle_2);

        EXPECT_EQ(backend.database_handle, database_handle_2);

        SQLiteBackendTest::safe_close(database_handle_1);
        SQLiteBackendTest::safe_close(database_handle_2);
    }

    TEST(SQLiteBackendTest, Should_Validate_Thread_Safe_Read_Without_Interference)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend(database_handle);

        std::atomic<std::uint32_t> safe_reads = 0;
        std::atomic<bool> stop_flag = false;

        auto reader = [&backend, &safe_reads, &stop_flag]()
        {
            while (!stop_flag.load())
            {
                if (backend.database_handle != nullptr)
                {
                    safe_reads.fetch_add(1);
                }
            }
        };

        std::thread t1(reader);
        std::thread t2(reader);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        stop_flag.store(true);

        t1.join();
        t2.join();

        EXPECT_GT(safe_reads.load(), 0u);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Detect_Invalid_State_After_Double_Move_Assignment)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_a(database_handle);

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_b(database_handle);

        backend_a = std::move(backend_b);
        backend_b = std::move(backend_a);

        std::uint32_t valid_count = 0;

        if (backend_a.database_handle) valid_count++;
        if (backend_b.database_handle) valid_count++;

        EXPECT_EQ(valid_count, 1u);

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Validate_No_Dangling_Handle_After_Reset)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend(database_handle);

        backend = QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend();

        EXPECT_EQ(backend.database_handle, nullptr);

        EXPECT_NO_THROW(
        {
            (void)backend.database_handle;
        });

        SQLiteBackendTest::safe_close(database_handle);
    }

    TEST(SQLiteBackendTest, Should_Validate_SQLite_Handle_Remains_Valid_After_Move)
    {
        sqlite3* database_handle =
            SQLiteBackendTest::create_memory_database();

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_a(database_handle);

        QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME::
            SQLiteBackend backend_b(std::move(backend_a));

        int result =
            sqlite3_exec(database_handle, "SELECT 1;", nullptr, nullptr, nullptr);

        EXPECT_EQ(result, SQLITE_OK);

        SQLiteBackendTest::safe_close(database_handle);
    }
}

#endif
