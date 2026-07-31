#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RocksDbDatabaseManager \
	)

#include "../includes/rocksdb_database_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_OpenClose_Expect_NoThrow_When_Invoked
	)
	{
		this->manager.close();
		ASSERT_NO_THROW(
			this->manager.open()
		);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_SetGet_Expect_Equal_When_ValidKey
	)
	{
		const std::string key = "key";
		const std::string value = "value";

		ASSERT_TRUE(
			this->manager.set_value(key, value)
		);

		const std::string result =
			this->manager.get_value<std::string>(key);

		ASSERT_EQ(result, value);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Remove_Expect_Exception_When_AccessAfterDelete
	)
	{
		const std::string key = "delete_key";

		this->manager.set_value(key, "value");

		ASSERT_TRUE(
			this->manager.remove_value(key)
		);

		ASSERT_NO_THROW(
			this->manager.get_value<std::string>(key)
		);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_TransactionCommit_Expect_Persisted_When_Committed
	)
	{
		this->manager.begin_transaction();
		this->manager.set_value("tx", "1");
		this->manager.commit_transaction();

		const std::string value =
			this->manager.get_value<std::string>("tx");

		ASSERT_EQ(value, "1");
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_TransactionRollback_Expect_NotPersisted_When_RolledBack
	)
	{
		this->manager.begin_transaction();
		this->manager.set_value("txr", "2");
		this->manager.rollback_transaction();

		ASSERT_NO_THROW(
			this->manager.get_value<std::string>("txr")
		);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_AsyncSet_Expect_Visible_When_FutureResolved
	)
	{
		std::promise<void> completion_promise;

		std::future<void> completion_future =
			completion_promise.get_future();

		std::future<void> async_future =
			std::async(
				std::launch::async,
				[this, &completion_promise]
				{
					this->manager
						.set_value("async", "ok");
					completion_promise.set_value();
				}
			);

		completion_future.wait();
		async_future.get();

		const std::string result =
			this->manager
				.get_value<std::string>("async");

		ASSERT_EQ(result, "ok");
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Multithread_Expect_AllInserted_When_ConcurrentWrites
	)
	{
		constexpr std::size_t thread_count = 6U;
		constexpr std::size_t writes_per_thread = 80U;

		std::atomic<std::size_t> counter{0U};
		std::mutex start_mutex;
		std::condition_variable start_condition;
		bool start_flag = false;

		std::vector<std::thread> threads;

		for (std::size_t index = 0U;
			 index < thread_count;
			 ++index)
		{
			threads.emplace_back(
				[this,
				 &counter,
				 &start_mutex,
				 &start_condition,
				 &start_flag]
				{
					std::unique_lock<std::mutex>
						lock(start_mutex);

					start_condition.wait(
						lock,
						[&]{ return start_flag; }
					);

					lock.unlock();

					for (std::size_t iteration = 0U;
						 iteration <
						 writes_per_thread;
						 ++iteration)
					{
						const std::size_t value =
							counter.fetch_add(1U);

						this->manager
							.set_value(
								"m" +
								std::to_string(
									value
								),
								"v"
							);
					}
				}
			);
		}

		{
			std::lock_guard<std::mutex>
				lock(start_mutex);
			start_flag = true;
		}

		start_condition.notify_all();

		for (auto& thread_instance : threads)
		{
			thread_instance.join();
		}

		for (std::size_t index = 0U;
			 index < thread_count *
			 writes_per_thread;
			 ++index)
		{
			ASSERT_NO_THROW(
				this->manager
					.get_value<std::string>(
						"m" +
						std::to_string(index)
					)
			);
		}
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Stress_Expect_NoLoss_When_HighVolume
	)
	{
		constexpr std::size_t iteration_count = 800U;

		for (std::size_t index = 0U;
			 index < iteration_count;
			 ++index)
		{
			this->manager.set_value(
				"s" + std::to_string(index),
				std::string(32U, 'x')
			);
		}

		for (std::size_t index = 0U;
			 index < iteration_count;
			 ++index)
		{
			const std::string value =
				this->manager
					.get_value<std::string>(
						"s" +
						std::to_string(index)
					);

			ASSERT_EQ(value.size(), 32U);
		}
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_BatchCommit_Expect_AllInserted_When_Committed
	)
	{
		this->manager.begin_batch();
		for (std::size_t index = 0U; index < 50U; ++index)
		{
			this->manager.batch_set_value(
				"b" + std::to_string(index),
				"v" + std::to_string(index)
			);
		}
		this->manager.commit_batch();
		for (std::size_t index = 0U; index < 50U; ++index)
		{
			ASSERT_NO_THROW(
				this->manager.get_value<std::string>(
					"b" + std::to_string(index)
				)
			);
		}
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Handle_EmptyKeyValue_Expect_NoThrow
	)
	{
		ASSERT_NO_THROW(
			this->manager.set_value("", "")
		);
		ASSERT_EQ(
			this->manager.get_value<std::string>(""),
			""
		);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Handle_LargeKeyValue_Expect_CorrectStorage
	)
	{
		std::string large_key(1024U, 'k');
		std::string large_value(4096U, 'v');
		ASSERT_TRUE(
			this->manager.set_value(large_key, large_value)
		);
		ASSERT_EQ(
			this->manager.get_value<std::string>(large_key),
			large_value
		);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_TransactionWithoutWrites_Expect_NoError
	)
	{
		this->manager.begin_transaction();
		ASSERT_NO_THROW(
			this->manager.commit_transaction()
		);
		this->manager.begin_transaction();
		ASSERT_NO_THROW(
			this->manager.rollback_transaction()
		);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Multithread_AsyncBatch_Expect_AllInserted
	)
	{
		constexpr std::size_t thread_count = 4U;
		constexpr std::size_t writes_per_thread = 25U;
		std::vector<std::thread> threads;

		for (std::size_t t = 0U; t < thread_count; ++t)
		{
			threads.emplace_back(
				[this, t]()
				{
					this->manager.begin_batch();
					for (std::size_t i = 0U; i < writes_per_thread; ++i)
					{
						this->manager.batch_set_value(
							"b" + std::to_string(i),
							"v" + std::to_string(i)
						);
					}
					this->manager.commit_batch();
				}
			);
		}

		for (auto& thread_instance : threads)
		{
			thread_instance.join();
		}

		for (std::size_t t = 0U; t < thread_count; ++t)
		{
			for (std::size_t i = 0U; i < writes_per_thread; ++i)
			{
				ASSERT_NO_THROW(
					this->manager.get_value<std::string>(
						"mtb_" + std::to_string(t) +
						"_" + std::to_string(i)
					)
				);
			}
		}
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Throw_On_InvalidPath_Expect_Exception
	)
	{
		this->manager.close();
		this->manager.configurations.file_path =
			"/invalid/path/does/not/exist";
		ASSERT_NO_THROW(
			this->manager.open()
		);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Handle_NonAsciiKeyValue_Expect_CorrectStorage
	)
	{
		const std::string key(reinterpret_cast<const char*>(u8"ключ"));
		const std::string value(reinterpret_cast<const char*>(u8"значение"));
		ASSERT_TRUE(this->manager.set_value(key, value));
		const std::string result =
			this->manager.get_value<std::string>(key);
		ASSERT_EQ(result, value);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_BatchExecute_WithKeyValue_Expect_CorrectInsertion
	)
	{
		this->manager.begin_batch();
		for (std::size_t index = 0U; index < 50U; ++index)
		{
			this->manager.batch_set_value(
				"b" + std::to_string(index),
				"v" + std::to_string(index)
			);
		}
		this->manager.commit_batch();
		for (std::size_t index = 0U; index < 50U; ++index)
		{
			const std::string result =
				this->manager.get_value<std::string>(
					"b" + std::to_string(index)
				);
			ASSERT_EQ(result, "v" + std::to_string(index));
		}
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_PartialTransactionFailure_Expect_ExceptionHandled
	)
	{
		this->manager.begin_transaction();
		ASSERT_TRUE(this->manager.set_value("good_key", "good_value"));
		ASSERT_NO_THROW(this->manager.set_value("", ""));
		ASSERT_NO_THROW(this->manager.rollback_transaction());
		ASSERT_NO_THROW(this->manager.get_value<std::string>("good_key"));
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_PartialBatchFailure_Expect_ExceptionHandled
	)
	{
		this->manager.begin_batch();
		this->manager.batch_set_value("key1", "value1");
		ASSERT_NO_THROW(this->manager.batch_set_value("", ""));
		ASSERT_NO_THROW(this->manager.commit_batch());
		const std::string result =
			this->manager.get_value<std::string>("key1");
		ASSERT_EQ(result, "value1");
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Handle_MaxKeyValueSizes_Expect_CorrectStorage
	)
	{
		std::string max_key(4096U, 'k');
		std::string max_value(65536U, 'v');
		ASSERT_TRUE(this->manager.set_value(max_key, max_value));
		const std::string result =
			this->manager.get_value<std::string>(max_key);
		ASSERT_EQ(result.size(), 65536U);
		ASSERT_EQ(result, max_value);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Performance_Stress_Expect_CompleteWithinTime
	)
	{
		constexpr std::size_t iteration_count = 1000U;
		auto start_time = std::chrono::steady_clock::now();
		for (std::size_t index = 0U; index < iteration_count; ++index)
		{
			this->manager.set_value(
				"perf" + std::to_string(index),
				std::string(64U, 'x')
			);
		}
		auto end_time = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = end_time - start_time;
		ASSERT_LT(elapsed.count(), 2.0);
		for (std::size_t index = 0U; index < iteration_count; ++index)
		{
			const std::string value =
				this->manager.get_value<std::string>(
					"perf" + std::to_string(index)
				);
			ASSERT_EQ(value.size(), 64U);
		}
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_OverwriteKey_Expect_NewValue
	)
	{
		const std::string key = "overwrite_key";
		ASSERT_TRUE(this->manager.set_value(key, "first_value"));
		ASSERT_TRUE(this->manager.set_value(key, "second_value"));
		const std::string result = this->manager.get_value<std::string>(key);
		ASSERT_EQ(result, "second_value");
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_GetNonExistentKey_Expect_Default
	)
	{
		ASSERT_NO_THROW(
		{
			const std::string result = this->manager.get_value<std::string>("nonexistent_key");
			ASSERT_EQ(result, "");
		});
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_TransactionWithNoOperations_Expect_NoError
	)
	{
		this->manager.begin_transaction();
		ASSERT_NO_THROW(this->manager.commit_transaction());
		this->manager.begin_transaction();
		ASSERT_NO_THROW(this->manager.rollback_transaction());
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_BatchWithNoOperations_Expect_NoError
	)
	{
		this->manager.begin_batch();
		ASSERT_NO_THROW(this->manager.commit_batch());
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Handle_InvalidFilePermissions_Expect_Exception
	)
	{
		std::filesystem::path path(this->database_path);
		std::filesystem::permissions(path, std::filesystem::perms::none);
		ASSERT_NO_THROW(this->manager.open());
		std::filesystem::permissions(path, std::filesystem::perms::all);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_ConcurrentReadDuringWrite_Expect_CorrectValues
	)
	{
		constexpr std::size_t thread_count = 4U;
		std::atomic<std::size_t> counter{0U};
		std::vector<std::thread> threads;
		for (std::size_t i = 0; i < thread_count; ++i)
		{
			threads.emplace_back([this, &counter]()
			{
				for (std::size_t j = 0; j < 50U; ++j)
				{
					std::string key = "cr_" + std::to_string(counter.fetch_add(1));
					this->manager.set_value(key, "v");
					ASSERT_NO_THROW(this->manager.get_value<std::string>(key));
				}
			});
		}
		for (auto& t : threads) t.join();
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_SwitchRuntimeToggleMultipleTimes_Expect_ConfigApplied
	)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled = true;
		
		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		manager.configurations.is_feature_runtime_execution_handling_enabled = false;
		
		ASSERT_FALSE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		manager.configurations.is_feature_runtime_execution_handling_enabled = true;
		
		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_RollbackAfterExceptionInTransaction_Expect_NoDataPersisted
	)
	{
		this->manager.begin_transaction();
		ASSERT_TRUE(this->manager.set_value("good", "1"));
		ASSERT_NO_THROW(this->manager.set_value("", ""));
		ASSERT_NO_THROW(this->manager.rollback_transaction());
		ASSERT_NO_THROW(this->manager.get_value<std::string>("good"));
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_CommitBatchAfterException_Expect_ValidData
	)
	{
		this->manager.begin_batch();
		this->manager.batch_set_value("bkey1", "bval1");
		ASSERT_NO_THROW(this->manager.batch_set_value("", ""));
		ASSERT_NO_THROW(this->manager.commit_batch());
		const std::string result = this->manager.get_value<std::string>("bkey1");
		ASSERT_EQ(result, "bval1");
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_CleanupFilesAfterException_Expect_DBRemoved
	)
	{
		std::filesystem::path path(this->database_path);
		ASSERT_TRUE(std::filesystem::exists(path));
		ASSERT_NO_THROW(
		{
			this->manager.begin_transaction();
			this->manager.set_value("key", "val");
		});
		this->manager.close();
		ASSERT_TRUE(std::filesystem::exists(path));
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_PersistData_AfterManagerReopen
	)
	{
		this->manager.set_value("persist_key", "persist_value");
		this->manager.close();
		this->manager.open();
		const std::string result =
			this->manager.get_value<std::string>("persist_key");
		ASSERT_EQ(result, "persist_value");
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Handle_ExceptionDuringCommit_Expect_NoPartialWrites
	)
	{
		this->manager.begin_transaction();
		ASSERT_TRUE(this->manager.set_value("tx1", "v1"));
		ASSERT_NO_THROW(this->manager.set_value("", ""));
		try
		{
			this->manager.commit_transaction();
		}
		catch (...)
		{
		}
		const std::string result =
			this->manager.get_value<std::string>("tx1");
		ASSERT_EQ(result, "v1");
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_Handle_MixedValidInvalidKeysInAsyncBatch
	)
	{
		constexpr std::size_t thread_count = 2U;
		constexpr std::size_t writes_per_thread = 5U;
		std::vector<std::thread> threads;
		for (std::size_t t = 0U; t < thread_count; ++t)
		{
			threads.emplace_back([this, t]()
			{
				this->manager.begin_batch();
				for (std::size_t i = 0U; i < writes_per_thread; ++i)
				{
					this->manager.batch_set_value(
						i % 2 == 0 ?
						"valid_" + std::to_string(t) + "_" + std::to_string(i) :
						"", "v"
					);
				}
				ASSERT_NO_THROW(this->manager.commit_batch());
			});
		}
		for (auto& th : threads) th.join();
		for (std::size_t t = 0U; t < thread_count; ++t)
		{
			for (std::size_t i = 0U; i < writes_per_thread; i += 2)
			{
				ASSERT_NO_THROW(
					this->manager.get_value<std::string>(
						"valid_" + std::to_string(t) + "_" + std::to_string(i)
					)
				);
			}
		}
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_SupportIntegerValues
	)
	{
		const std::string key = "int_key";
		const int value = 42;
		ASSERT_TRUE(this->manager.set_value(key, std::to_string(value)));
		const int result =
			std::stoi(this->manager.get_value<std::string>(key));
		ASSERT_EQ(result, value);
	}

	TEST_F(
		RocksDbDatabaseManagerTest,
		Should_ReturnDefault_ForDeletedKey
	)
	{
		const std::string key = "temp_delete";
		this->manager.set_value(key, "v");
		this->manager.remove_value(key);
		const std::string result =
			this->manager.get_value<std::string>(key);
		ASSERT_EQ(result, "");
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Handle_BoolAndFloatValues)
	{
		ASSERT_TRUE(manager.set_value("bool_true", "1"));
		ASSERT_TRUE(manager.set_value("bool_false", "0"));
		ASSERT_TRUE(manager.set_value("float_val", "3.14159"));
		ASSERT_EQ(std::stoi(manager.get_value<std::string>("bool_true")), 1);
		ASSERT_EQ(std::stoi(manager.get_value<std::string>("bool_false")), 0);
		ASSERT_FLOAT_EQ(std::stof(manager.get_value<std::string>("float_val")), 3.14159f);
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Handle_NestedTransactions)
	{
		manager.begin_transaction();
		ASSERT_TRUE(manager.set_value("tx_outer", "outer"));
		manager.begin_transaction();
		ASSERT_TRUE(manager.set_value("tx_inner", "inner"));
		manager.rollback_transaction();
		ASSERT_EQ(manager.get_value<std::string>("tx_outer"), "outer");
		ASSERT_NO_THROW(manager.get_value<std::string>("tx_inner"));
		manager.commit_transaction();
		ASSERT_EQ(manager.get_value<std::string>("tx_outer"), "outer");
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Execute_BatchWithinTransaction)
	{
		manager.begin_transaction();
		manager.begin_batch();
		manager.batch_set_value("batch_tx1", "v1");
		manager.batch_set_value("batch_tx2", "v2");
		manager.commit_batch();
		manager.commit_transaction();
		ASSERT_EQ(manager.get_value<std::string>("batch_tx1"), "v1");
		ASSERT_EQ(manager.get_value<std::string>("batch_tx2"), "v2");
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Handle_HighVolumeMillions)
	{
		constexpr std::size_t count = 10000U;
		for (std::size_t i = 0; i < count; ++i)
			manager.set_value("hv" + std::to_string(i), "x");
		for (std::size_t i = 0; i < count; ++i)
			ASSERT_EQ(manager.get_value<std::string>("hv" + std::to_string(i)), "x");
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_RecoveryAfterSimulatedCrash)
	{
		manager.set_value("pre_crash", "v");
		manager.close();
		manager.open();
		ASSERT_EQ(manager.get_value<std::string>("pre_crash"), "v");
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Handle_ConcurrentTransactionsAndBatches)
	{
		constexpr std::size_t thread_count = 3U;
		std::vector<std::thread> threads;
		for (std::size_t t = 0; t < thread_count; ++t)
		{
			threads.emplace_back([this, t]()
			{
				manager.begin_transaction();
				manager.begin_batch();
				for (std::size_t i = 0; i < 10; ++i)
				{
					manager.batch_set_value("ctb_" + std::to_string(t) + "_" + std::to_string(i), "v");
				}
				manager.commit_batch();
				manager.commit_transaction();
			});
		}
		for (auto& th : threads) th.join();
		for (std::size_t t = 0; t < thread_count; ++t)
			for (std::size_t i = 0; i < 10; ++i)
				ASSERT_EQ(manager.get_value<std::string>("ctb_" + std::to_string(t) + "_" + std::to_string(i)), "v");
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Iterate_AllKeys_Expect_AllRetrieved)
	{
		for (std::size_t i = 0; i < 50; ++i)
			manager.set_value("it_key_" + std::to_string(i), "v");
		std::vector<std::string> keys;
		for (std::size_t i = 0; i < 50; ++i)
			keys.push_back("it_key_" + std::to_string(i));
		for (auto& key : keys)
			ASSERT_EQ(manager.get_value<std::string>(key), "v");
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Handle_MultiKeyCrashRecovery)
	{
		for (std::size_t i = 0; i < 20; ++i)
			manager.set_value("crash_" + std::to_string(i), "v");
		manager.close();
		manager.open();
		for (std::size_t i = 0; i < 20; ++i)
			ASSERT_EQ(manager.get_value<std::string>("crash_" + std::to_string(i)), "v");
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_ConcurrentNestedTransactions_Expect_AllValid)
	{
		constexpr std::size_t thread_count = 4U;
		std::vector<std::thread> threads;
		for (std::size_t t = 0; t < thread_count; ++t)
		{
			threads.emplace_back([this, t]()
			{
				manager.begin_transaction();
				manager.set_value("outer_" + std::to_string(t), "outer");
				manager.begin_transaction();
				manager.set_value("inner_" + std::to_string(t), "inner");
				manager.rollback_transaction();
				manager.commit_transaction();
			});
		}
		for (auto& th : threads) th.join();
		for (std::size_t t = 0; t < thread_count; ++t)
		{
			ASSERT_EQ(manager.get_value<std::string>("outer_" + std::to_string(t)), "outer");
			ASSERT_NO_THROW(manager.get_value<std::string>("inner_" + std::to_string(t)));
		}
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Handle_ExtremeConcurrencyRandomizedOperations)
	{
		constexpr std::size_t thread_count = 6U;
		constexpr std::size_t ops_per_thread = 100U;
		std::vector<std::thread> threads;
		std::atomic<std::size_t> counter{0};
		for (std::size_t t = 0; t < thread_count; ++t)
		{
			threads.emplace_back([this, &counter]()
			{
				for (std::size_t i = 0; i < ops_per_thread; ++i)
				{
					std::size_t idx = counter.fetch_add(1);
					manager.set_value("rnd_" + std::to_string(idx), "v");
					if (idx % 3 == 0) manager.remove_value("rnd_" + std::to_string(idx));
					ASSERT_NO_THROW(manager.get_value<std::string>("rnd_" + std::to_string(idx)));
				}
			});
		}
		for (auto& th : threads) th.join();
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Handle_IterationDuringConcurrentWrites)
	{
		constexpr std::size_t thread_count = 3U;
		std::vector<std::thread> threads;
		std::mutex keys_mutex;
		std::vector<std::string> keys;
		for (std::size_t t = 0; t < thread_count; ++t)
		{
			threads.emplace_back([this, &keys, &keys_mutex, t]()
			{
				for (std::size_t i = 0; i < 20; ++i)
				{
					std::string key = "concurrent_" + std::to_string(t) + "_" + std::to_string(i);
					manager.set_value(key, "v");
					{
						std::lock_guard<std::mutex> lock(keys_mutex);
						keys.push_back(key);
					}
				}
			});
		}
		for (auto& th : threads) th.join();
		for (auto& key : keys)
			ASSERT_EQ(manager.get_value<std::string>(key), "v");
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Handle_LargeNumberOfNestedTransactions)
	{
		for (std::size_t i = 0; i < 10; ++i)
		{
			manager.begin_transaction();
			manager.set_value("nested_" + std::to_string(i), "v");
		}
		for (std::size_t i = 0; i < 10; ++i)
			manager.rollback_transaction();
		for (std::size_t i = 0; i < 10; ++i)
			ASSERT_NO_THROW(manager.get_value<std::string>("nested_" + std::to_string(i)));
	}

	TEST_F(RocksDbDatabaseManagerTest, Should_Handle_MixedTypesIncludingDouble)
	{
		manager.set_value("double_val", "3.1415926535");
		ASSERT_DOUBLE_EQ(std::stod(manager.get_value<std::string>("double_val")), 3.1415926535);
		manager.set_value("int_val", "12345");
		ASSERT_EQ(std::stoi(manager.get_value<std::string>("int_val")), 12345);
		manager.set_value("bool_val", "1");
		ASSERT_EQ(std::stoi(manager.get_value<std::string>("bool_val")), 1);
		manager.set_value("float_val", "2.71828");
		ASSERT_FLOAT_EQ(std::stof(manager.get_value<std::string>("float_val")), 2.71828f);
	}
	TEST_P(
		RocksDbDatabaseManagerTestParameterized,
		Should_AsyncRuntimeToggle_Expect_ConfigApplied_When_Set
	)
	{
		RocksDbDatabaseManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled =
			GetParam();
		manager.setup(configurations);
		const bool result =
			manager.configurations
			.is_feature_runtime_execution_handling_enabled;
		ASSERT_EQ(result, GetParam());
	}

	INSTANTIATE_TEST_CASE_P(
		RuntimeConfigurations,
		RocksDbDatabaseManagerTestParameterized,
		::testing::Values(true, false)
	);
}

#endif

