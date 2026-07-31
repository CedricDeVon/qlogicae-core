#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteStatementData \
	)

#include "../includes/sqlite_statement_data.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
    TEST_F(SQLiteStatementDataTest,
    Should_Initialize_Null_When_Default_Constructed)
    {
        SQLiteStatementData data;

        EXPECT_EQ(data.statement_handle, nullptr);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Hold_Handle_When_Constructed_With_Statement)
    {
        sqlite3_stmt* stmt =
            prepare_statement("SELECT 1");

        SQLiteStatementData data(stmt);

        EXPECT_NE(data.statement_handle, nullptr);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Finalize_Without_Crash_When_Destroyed)
    {
        sqlite3_stmt* stmt =
            prepare_statement("SELECT 1");

        EXPECT_NO_THROW(
        {
            SQLiteStatementData data(stmt);
        });
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Support_Multiple_Independent_Instances)
    {
        sqlite3_stmt* stmt1 =
            prepare_statement("SELECT 1");

        sqlite3_stmt* stmt2 =
            prepare_statement("SELECT 2");

        SQLiteStatementData data1(stmt1);
        SQLiteStatementData data2(stmt2);

        EXPECT_NE(data1.statement_handle,
                  data2.statement_handle);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Be_Safe_With_Null_Statement)
    {
        EXPECT_NO_THROW(
        {
            SQLiteStatementData data(nullptr);
        });
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Finalize_In_Multithreaded_Destruction)
    {
        std::atomic<int> completed_count{0};

        auto worker = [&]()
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            {
                SQLiteStatementData data(stmt);
            }

            completed_count++;
        };

        std::thread thread1(worker);
        std::thread thread2(worker);
        std::thread thread3(worker);

        thread1.join();
        thread2.join();
        thread3.join();

        EXPECT_EQ(completed_count.load(), 3);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Work_With_Async_Finalization)
    {
        sqlite3_stmt* stmt =
            prepare_statement("SELECT 1");

        std::future<void> future_result =
            std::async(std::launch::async,
            [stmt]()
            {
                SQLiteStatementData data(stmt);
            });

        EXPECT_NO_THROW(
        {
            future_result.get();
        });
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Complete_Stress_Test_Within_Time_Limit)
    {
        for (int index = 0; index < 1000; index++)
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            SQLiteStatementData data(stmt);
        }

        SUCCEED();
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Handle_Repeated_Creation_And_Destruction)
    {
        for (int index = 0; index < 500; index++)
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            SQLiteStatementData data(stmt);
        }

        SUCCEED();
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Not_Throw_On_Empty_Statement_Preparation)
    {
        sqlite3_stmt* stmt =
            prepare_statement("");

        EXPECT_NO_THROW(
        {
            SQLiteStatementData data(stmt);
        });
    }

    TEST_P(SQLiteStatementDataParamTest,
    Should_Handle_Various_SQL_Statements)
    {
        sqlite3_stmt* stmt =
            prepare_statement(GetParam());

        EXPECT_NO_THROW(
        {
            SQLiteStatementData data(stmt);
        });
    }

    INSTANTIATE_TEST_CASE_P(
        SQLiteStatementDataTestCases,
        SQLiteStatementDataParamTest,
        ::testing::Values(
            "SELECT 1",
            "SELECT 1 + 1",
            "SELECT sqlite_version()",
            ""
        )
    );

    TEST_F(SQLiteStatementDataThreadTest,
    Should_Synchronize_Multiple_Threads_Correctly)
    {
        std::atomic<int> counter{0};

        auto thread_function = [&]()
        {
            std::unique_lock<std::mutex> lock(mutex);
            condition_variable.wait(lock,
            [&]()
            {
                return ready;
            });

            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            SQLiteStatementData data(stmt);

            counter++;
        };

        std::thread thread1(thread_function);
        std::thread thread2(thread_function);

        {
            std::lock_guard<std::mutex> lock(mutex);
            ready = true;
        }

        condition_variable.notify_all();

        thread1.join();
        thread2.join();

        EXPECT_EQ(counter.load(), 2);
    }
    
    TEST_F(SQLiteStatementDataTest,
    Should_Handle_Empty_SQL_As_Failure_Path)
    {
        sqlite3_stmt* stmt = prepare_statement("");
        EXPECT_NO_THROW(SQLiteStatementData data(stmt));
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Handle_Invalid_SQL_Failure_Path)
    {
        sqlite3_stmt* stmt = prepare_statement("INVALID SQL !!!!");
        EXPECT_NO_THROW(SQLiteStatementData data(stmt));
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Not_Crash_On_Destructor_With_Null)
    {
        EXPECT_NO_THROW(
        {
            SQLiteStatementData data(nullptr);
        });
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Finalize_Once_On_Destruction)
    {
        sqlite3_stmt* stmt = prepare_statement("SELECT 1");
        EXPECT_NO_THROW(SQLiteStatementData data(stmt));
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Work_In_Multithreaded_Destruction)
    {
        std::atomic<int> counter{0};

        auto worker = [&]()
        {
            sqlite3_stmt* stmt = prepare_statement("SELECT 1");
            SQLiteStatementData data(stmt);
            counter++;
        };

        std::thread t1(worker);
        std::thread t2(worker);
        std::thread t3(worker);

        t1.join();
        t2.join();
        t3.join();

        EXPECT_EQ(counter.load(), 3);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Be_Safe_In_Concurrent_Creation)
    {
        std::atomic<int> counter{0};

        auto worker = [&]()
        {
            for (int i = 0; i < 100; i++)
            {
                sqlite3_stmt* stmt = prepare_statement("SELECT 1");
                SQLiteStatementData data(stmt);
            }
            counter++;
        };

        std::thread t1(worker);
        std::thread t2(worker);

        t1.join();
        t2.join();

        EXPECT_EQ(counter.load(), 2);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Meet_Stress_Time_Constraint)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 5000; i++)
        {
            sqlite3_stmt* stmt = prepare_statement("SELECT 1");
            SQLiteStatementData data(stmt);
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start
        ).count();

        EXPECT_LT(duration, 2000);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Handle_Future_Finalization)
    {
        sqlite3_stmt* stmt = prepare_statement("SELECT 1");

        std::future<void> result =
            std::async(std::launch::async,
            [stmt]()
            {
                SQLiteStatementData data(stmt);
            });

        EXPECT_NO_THROW(result.get());
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Handle_Promise_Based_Workflow)
    {
        std::promise<bool> promise;
        std::future<bool> future = promise.get_future();

        std::thread worker([&]()
        {
            sqlite3_stmt* stmt = prepare_statement("SELECT 1");
            SQLiteStatementData data(stmt);
            promise.set_value(true);
        });

        EXPECT_TRUE(future.get());
        worker.join();
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Support_Vector_Container_Movement)
    {
        std::vector<SQLiteStatementData> container;

        for (int i = 0; i < 100; i++)
        {
            sqlite3_stmt* stmt = prepare_statement("SELECT 1");
            container.emplace_back(stmt);
        }

        EXPECT_EQ(container.size(), 100);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Support_Map_Container_Insertion)
    {
        std::map<int, SQLiteStatementData> container;

        for (int i = 0; i < 50; i++)
        {
            sqlite3_stmt* stmt = prepare_statement("SELECT 1");
            container.emplace(i, SQLiteStatementData(stmt));
        }

        EXPECT_EQ(container.size(), 50);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Handle_Move_Construction)
    {
        sqlite3_stmt* stmt = prepare_statement("SELECT 1");

        SQLiteStatementData original(stmt);
        SQLiteStatementData moved(std::move(original));

        EXPECT_NO_THROW((void)moved.statement_handle);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Handle_Move_Assignment)
    {
        sqlite3_stmt* stmt1 = prepare_statement("SELECT 1");
        sqlite3_stmt* stmt2 = prepare_statement("SELECT 2");

        SQLiteStatementData first(stmt1);
        SQLiteStatementData second(stmt2);

        second = std::move(first);

        EXPECT_NO_THROW((void)second.statement_handle);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Survive_Repeated_Allocation_And_Destruction)
    {
        for (int i = 0; i < 2000; i++)
        {
            sqlite3_stmt* stmt = prepare_statement("SELECT 1");
            SQLiteStatementData data(stmt);
        }

        SUCCEED();
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Complete_Under_Stress_Limit_With_Multithreading)
    {
        auto start = std::chrono::steady_clock::now();

        std::vector<std::thread> threads;

        for (int t = 0; t < 4; t++)
        {
            threads.emplace_back([&]()
            {
                for (int i = 0; i < 1000; i++)
                {
                    sqlite3_stmt* stmt = prepare_statement("SELECT 1");
                    SQLiteStatementData data(stmt);
                }
            });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        auto end = std::chrono::steady_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start
        ).count();

        EXPECT_LT(duration, 2000);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Not_Allow_Copy_Construction)
    {
        static_assert(
            !std::is_copy_constructible_v<
                SQLiteStatementData
            >,
            "Copy construction must be deleted"
        );
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Not_Allow_Copy_Assignment)
    {
        static_assert(
            !std::is_copy_assignable_v<
                SQLiteStatementData
            >,
            "Copy assignment must be deleted"
        );
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Move_Transfer_Ownership_And_Null_Source)
    {
        sqlite3_stmt* stmt =
            prepare_statement("SELECT 1");

        SQLiteStatementData original(stmt);

        SQLiteStatementData moved(
            std::move(original)
        );

        EXPECT_NE(
            moved.statement_handle,
            nullptr
        );

        EXPECT_EQ(
            original.statement_handle,
            nullptr
        );
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Move_Assignment_Transfer_Ownership_And_Null_Source)
    {
        sqlite3_stmt* stmt1 =
            prepare_statement("SELECT 1");

        sqlite3_stmt* stmt2 =
            prepare_statement("SELECT 2");

        SQLiteStatementData first(stmt1);
        SQLiteStatementData second(stmt2);

        second =
            std::move(first);

        EXPECT_NE(
            second.statement_handle,
            nullptr
        );

        EXPECT_EQ(
            first.statement_handle,
            nullptr
        );
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Not_Double_Finalize_Under_Container_Reallocation)
    {
        std::vector<SQLiteStatementData> container;

        container.reserve(1);

        for (int index = 0; index < 1000; index++)
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            container.emplace_back(stmt);
        }

        SUCCEED();
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Ensure_Single_Ownership_After_Move_In_Container)
    {
        std::vector<SQLiteStatementData> container;

        sqlite3_stmt* stmt =
            prepare_statement("SELECT 1");

        container.emplace_back(stmt);

        SQLiteStatementData moved =
            std::move(container.front());

        EXPECT_EQ(
            container.front().statement_handle,
            nullptr
        );

        EXPECT_NE(
            moved.statement_handle,
            nullptr
        );
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Be_Safe_Under_Concurrent_Move_And_Destruction)
    {
        std::atomic<int> completed{0};

        auto worker = [&]()
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            SQLiteStatementData data(stmt);

            SQLiteStatementData moved(
                std::move(data)
            );

            completed++;
        };

        std::thread thread1(worker);
        std::thread thread2(worker);
        std::thread thread3(worker);
        std::thread thread4(worker);

        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();

        EXPECT_EQ(
            completed.load(),
            4
        );
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Maintain_Integrity_Under_Heavy_Move_Stress)
    {
        std::vector<SQLiteStatementData> container;

        for (int index = 0; index < 2000; index++)
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            container.emplace_back(stmt);
        }

        for (int index = 0; index < 2000; index++)
        {
            container.emplace_back(
                std::move(container[index % container.size()])
            );
        }

        SUCCEED();
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Always_Have_Single_Owner_Per_Handle_In_Threaded_Moves)
    {
        std::atomic<int> counter{0};

        auto worker = [&]()
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            SQLiteStatementData data(stmt);

            SQLiteStatementData moved(
                std::move(data)
            );

            if (moved.statement_handle != nullptr)
            {
                counter++;
            }
        };

        std::vector<std::thread> threads;

        for (int index = 0; index < 8; index++)
        {
            threads.emplace_back(worker);
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(
            counter.load(),
            8
        );
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Enforce_Single_Finalize_Under_Linear_Ownership_Chain)
    {
        sqlite3_stmt* stmt =
            prepare_statement("SELECT 1");

        SQLiteStatementData first(stmt);
        SQLiteStatementData second(std::move(first));
        SQLiteStatementData third(std::move(second));

        EXPECT_EQ(first.statement_handle, nullptr);
        EXPECT_EQ(second.statement_handle, nullptr);
        EXPECT_NE(third.statement_handle, nullptr);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Enforce_Strict_Ownership_Uniqueness_Across_Multiple_Moves)
    {
        std::vector<SQLiteStatementData> container;

        sqlite3_stmt* stmt =
            prepare_statement("SELECT 1");

        container.emplace_back(stmt);

        SQLiteStatementData a(std::move(container[0]));
        SQLiteStatementData b(std::move(a));
        SQLiteStatementData c(std::move(b));

        EXPECT_EQ(container[0].statement_handle, nullptr);
        EXPECT_EQ(a.statement_handle, nullptr);
        EXPECT_EQ(b.statement_handle, nullptr);
        EXPECT_NE(c.statement_handle, nullptr);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Remain_Safe_When_Destructing_Moved_From_Objects)
    {
        sqlite3_stmt* stmt =
            prepare_statement("SELECT 1");

        SQLiteStatementData first(stmt);
        SQLiteStatementData second(std::move(first));

        EXPECT_NO_THROW(
        {
            SQLiteStatementData temp(std::move(first));
        });

        EXPECT_NO_THROW(
        {
            SQLiteStatementData temp2(std::move(second));
        });
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Be_Safe_Under_Concurrent_Destruction_Race)
    {
        std::atomic<int> counter{0};

        auto worker = [&]()
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            SQLiteStatementData data(stmt);

            std::this_thread::sleep_for(
                std::chrono::microseconds(10)
            );

            counter++;
        };

        std::vector<std::thread> threads;

        for (int i = 0; i < 16; i++)
        {
            threads.emplace_back(worker);
        }

        for (auto& t : threads)
        {
            t.join();
        }

        EXPECT_EQ(counter.load(), 16);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Maintain_Invariant_No_Double_Finalize_Under_Adversarial_Moves)
    {
        sqlite3_stmt* stmt =
            prepare_statement("SELECT 1");

        SQLiteStatementData root(stmt);

        std::vector<SQLiteStatementData> chain;

        chain.reserve(64);

        chain.emplace_back(std::move(root));

        for (int i = 0; i < 63; i++)
        {
            chain.emplace_back(std::move(chain.back()));
        }

        int null_count = 0;
        int valid_count = 0;

        for (auto& item : chain)
        {
            if (item.statement_handle == nullptr)
            {
                null_count++;
            }
            else
            {
                valid_count++;
            }
        }

        EXPECT_EQ(valid_count, 1);
        EXPECT_EQ(null_count, 63);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Validate_Object_Level_Concurrency_Safety_With_Simultaneous_Moves)
    {
        std::atomic<int> success{0};

        auto worker = [&]()
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            SQLiteStatementData data(stmt);

            SQLiteStatementData moved(std::move(data));

            SQLiteStatementData moved_again(std::move(moved));

            if (moved_again.statement_handle != nullptr)
            {
                success++;
            }
        };

        std::vector<std::thread> threads;

        for (int i = 0; i < 8; i++)
        {
            threads.emplace_back(worker);
        }

        for (auto& t : threads)
        {
            t.join();
        }

        EXPECT_EQ(success.load(), 8);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Sustain_Integrity_Under_Concurrent_Mixed_Move_And_Destruction)
    {
        std::atomic<int> completed{0};

        std::vector<SQLiteStatementData> shared;

        for (int i = 0; i < 32; i++)
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            shared.emplace_back(stmt);
        }

        auto worker = [&]()
        {
            for (int i = 0; i < 100; i++)
            {
                int index = i % shared.size();

                SQLiteStatementData local(
                    std::move(shared[index])
                );

                SQLiteStatementData copy(
                    std::move(local)
                );
            }

            completed++;
        };

        std::vector<std::thread> threads;

        for (int i = 0; i < 4; i++)
        {
            threads.emplace_back(worker);
        }

        for (auto& t : threads)
        {
            t.join();
        }

        EXPECT_EQ(completed.load(), 4);
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Enforce_Finalize_Safety_Under_Repeated_Adversarial_Lifecycle)
    {
        for (int i = 0; i < 2000; i++)
        {
            sqlite3_stmt* stmt =
                prepare_statement("SELECT 1");

            SQLiteStatementData a(stmt);
            SQLiteStatementData b(std::move(a));
            SQLiteStatementData c(std::move(b));
            SQLiteStatementData d(std::move(c));

            EXPECT_EQ(a.statement_handle, nullptr);
            EXPECT_EQ(b.statement_handle, nullptr);
            EXPECT_EQ(c.statement_handle, nullptr);
            EXPECT_NE(d.statement_handle, nullptr);
        }

        SUCCEED();
    }

    TEST_F(SQLiteStatementDataTest,
    Should_Validate_Thread_Safe_Finalization_Under_Parallel_Destruction_Bursts)
    {
        std::atomic<int> completed{0};

        auto worker = [&]()
        {
            for (int i = 0; i < 500; i++)
            {
                sqlite3_stmt* stmt =
                    prepare_statement("SELECT 1");

                SQLiteStatementData data(stmt);
            }

            completed++;
        };

        std::vector<std::thread> threads;

        for (int i = 0; i < 8; i++)
        {
            threads.emplace_back(worker);
        }

        for (auto& t : threads)
        {
            t.join();
        }

        EXPECT_EQ(completed.load(), 8);
    }
}

#endif
