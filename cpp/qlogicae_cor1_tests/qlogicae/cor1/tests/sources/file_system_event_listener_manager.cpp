#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerManager \
	)

#include "../includes/file_system_event_listener_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	    
    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFalse_When_StopWatchingWithoutStart
    )
    {
        auto result = manager.stop_watching();

        EXPECT_FALSE(result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_StartWatchingCalledInitially
    )
    {
        auto start_time =
            std::chrono::steady_clock::now();

        auto result = manager.start_watching();

        auto end_time =
            std::chrono::steady_clock::now();

        auto elapsed =
            std::chrono::duration_cast<
                std::chrono::milliseconds
            >(end_time - start_time);

        EXPECT_TRUE(result);

        EXPECT_LT(elapsed.count(), 2000);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFalse_When_StartWatchingCalledTwice
    )
    {
        auto first_result = manager.start_watching();

        auto second_result = manager.start_watching();

        EXPECT_TRUE(first_result);

        EXPECT_FALSE(second_result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_StopWatchingAfterStart
    )
    {
        auto start_result = manager.start_watching();

        auto stop_result = manager.stop_watching();

        EXPECT_TRUE(start_result);

        EXPECT_TRUE(stop_result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectCreated_When_TranslateAddAction
    )
    {
        auto result =
            manager.translate_action(
                efsw::Actions::Add
            );

        EXPECT_EQ(
            result,
            FileSystemEventListenerAction::CREATED
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectDeleted_When_TranslateDeleteAction
    )
    {
        auto result =
            manager.translate_action(
                efsw::Actions::Delete
            );

        EXPECT_EQ(
            result,
            FileSystemEventListenerAction::DELETED
        );
    }
    
    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectModified_When_TranslateModifiedAction
    )
    {
        auto result =
            manager.translate_action(
                efsw::Actions::Modified
            );

        EXPECT_EQ(
            result,
            FileSystemEventListenerAction::MODIFIED
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectMoved_When_TranslateMovedAction
    )
    {
        auto result =
            manager.translate_action(
                efsw::Actions::Moved
            );

        EXPECT_EQ(
            result,
            FileSystemEventListenerAction::MOVED
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectUnknown_When_TranslateUnknownAction
    )
    {
        auto result =
            manager.translate_action(
                static_cast<efsw::Action>(999)
            );

        EXPECT_EQ(
            result,
            FileSystemEventListenerAction::UNKNOWN
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_PassesFilterWithEmptyOptions
    )
    {
        FileSystemEventListenerManagerOptions options;

        auto result = manager.passes_filter(
            "example.txt",
            options
        );

        EXPECT_TRUE(result);
    }

    TEST_P(
        FileSystemEventListenerManagerParameterizedExtensionTest,
        Should_ExpectTrue_When_ExtensionMatches
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.extensions.insert(GetParam());

        auto path = std::string("sample") + GetParam();

        auto result = manager.passes_filter(
            path,
            options
        );

        EXPECT_TRUE(result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFalse_When_ExtensionDoesNotMatch
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.extensions.insert(".json");

        auto result = manager.passes_filter(
            "sample.txt",
            options
        );

        EXPECT_FALSE(result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFalse_When_NoExtensionExists
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.extensions.insert(".txt");

        auto result = manager.passes_filter(
            "sample",
            options
        );

        EXPECT_FALSE(result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_ExplicitFileMatches
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.explicit_files.insert(
            "folder/sample.txt"
        );

        auto result = manager.passes_filter(
            "folder/sample.txt",
            options
        );

        EXPECT_TRUE(result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFalse_When_ExplicitFileDoesNotMatch
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.explicit_files.insert(
            "folder/other.txt"
        );

        auto result = manager.passes_filter(
            "folder/sample.txt",
            options
        );

        EXPECT_FALSE(result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFalse_When_ResolveFullPathMissingWatch
    )
    {
        std::string output_path;

        auto result = manager.resolve_full_path(
            static_cast<efsw::WatchID>(1),
            "directory",
            "file.txt",
            output_path
        );

        EXPECT_FALSE(result);

        EXPECT_TRUE(output_path.empty());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_ResolveOldPathEmptyFilename
    )
    {
        std::string output_path = "value";

        auto result = manager.resolve_old_path(
            static_cast<efsw::WatchID>(1),
            "directory",
            "",
            output_path
        );

        EXPECT_TRUE(result);

        EXPECT_TRUE(output_path.empty());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFalse_When_ResolveOldPathMissingWatch
    )
    {
        std::string output_path;

        auto result = manager.resolve_old_path(
            static_cast<efsw::WatchID>(100),
            "directory",
            "old.txt",
            output_path
        );

        EXPECT_FALSE(result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_AddListenerCalled
    )
    {
        auto result = manager.add_listener(
            [](const FileSystemEvent&)
            {
            }
        );

        EXPECT_TRUE(result);

        EXPECT_EQ(manager.listeners.size(), 1U);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_NotifyBatchWithSingleListener
    )
    {
        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        std::vector<FileSystemEvent> batch;

        FileSystemEvent event;

        event.path = "file.txt";

        batch.push_back(event);

        auto result = manager.notify_batch(batch);

        EXPECT_TRUE(result);

        EXPECT_EQ(callback_count.load(), 1U);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectAllCallbacks_When_MultipleListenersRegistered
    )
    {
        std::atomic<std::size_t> callback_count(0);

        for (std::size_t index = 0;
             index < 10;
             ++index)
        {
            manager.add_listener(
                [&callback_count](const FileSystemEvent&)
                {
                    callback_count.fetch_add(1);
                }
            );
        }

        std::vector<FileSystemEvent> batch;

        FileSystemEvent event;

        event.path = "sample.txt";

        batch.push_back(event);

        auto result = manager.notify_batch(batch);

        EXPECT_TRUE(result);

        EXPECT_EQ(callback_count.load(), 10U);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectAsyncCompletion_When_NotifyBatchUsingFuture
    )
    {
        std::promise<bool> completion_promise;

        auto completion_future =
            completion_promise.get_future();

        manager.add_listener(
            [&completion_promise](const FileSystemEvent&)
            {
                completion_promise.set_value(true);
            }
        );

        std::vector<FileSystemEvent> batch;

        FileSystemEvent event;

        batch.push_back(event);

        auto future = std::async(
            std::launch::async,
            [&manager = manager, &batch]()
            {
                return manager.notify_batch(batch);
            }
        );

        auto result = future.get();

        EXPECT_TRUE(result);

        EXPECT_TRUE(completion_future.get());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectAtomicConsistency_When_ConcurrentListenersAdded
    )
    {
        constexpr std::size_t thread_count = 8;

        constexpr std::size_t listener_count = 100;

        std::vector<std::thread> threads;

        for (std::size_t thread_index = 0;
             thread_index < thread_count;
             ++thread_index)
        {
            threads.emplace_back(
                [this]()
                {
                    for (std::size_t index = 0;
                         index < listener_count;
                         ++index)
                    {
                        manager.add_listener(
                            [](const FileSystemEvent&)
                            {
                            }
                        );
                    }
                }
            );
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(
            manager.listeners.size(),
            thread_count * listener_count
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectQueueProgress_When_StressDispatchLoop
    )
    {
        manager.is_running.store(true);

        constexpr std::size_t event_count = 1000;

        for (std::size_t index = 0;
             index < event_count;
             ++index)
        {
            auto& slot = manager.ring_buffer[
                index % manager.queue_capacity
            ];

            slot.event.sequence = index;

            slot.event.path = "stress.txt";

            slot.is_ready.store(true);
        }

        manager.write_index.store(event_count);

        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        auto dispatch_future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );

        manager.is_running.store(false);

        auto result = dispatch_future.get();

        EXPECT_TRUE(result);

        EXPECT_EQ(callback_count.load(), event_count);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectNoThrow_When_HandlingUnknownWatchIdentifier
    )
    {
        EXPECT_NO_THROW(
            manager.handleFileAction(
                static_cast<efsw::WatchID>(999),
                "directory",
                "file.txt",
                efsw::Actions::Add,
                ""
            )
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectRingBufferWrite_When_HandleFileActionValid
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(1, context);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(1),
            "subdirectory",
            "sample.txt",
            efsw::Actions::Add,
            ""
        );

        auto write_count = manager.write_index.load();

        EXPECT_EQ(write_count, 1U);

        auto& slot = manager.ring_buffer[0];

        EXPECT_TRUE(slot.is_ready.load());

        EXPECT_EQ(
            slot.event.action,
            FileSystemEventListenerAction::CREATED
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectNoWrite_When_FilterRejectsPath
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        context.options.extensions.insert(".json");

        manager.watch_registry.emplace(1, context);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(1),
            "subdirectory",
            "sample.txt",
            efsw::Actions::Add,
            ""
        );

        EXPECT_EQ(manager.write_index.load(), 0U);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectMoveAssignment_When_EventSlotMoved
    )
    {
        FileSystemEventListenerSlot source_slot;

        source_slot.event.path = "source.txt";

        source_slot.is_ready.store(true);

        FileSystemEventListenerSlot destination_slot;

        destination_slot = std::move(source_slot);

        EXPECT_TRUE(destination_slot.is_ready.load());

        EXPECT_EQ(
            destination_slot.event.path,
            "source.txt"
        );

        EXPECT_FALSE(source_slot.is_ready.load());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectMoveConstruction_When_EventSlotMoved
    )
    {
        FileSystemEventListenerSlot source_slot;

        source_slot.event.path = "constructed.txt";

        source_slot.is_ready.store(true);

        FileSystemEventListenerSlot destination_slot(
            std::move(source_slot)
        );

        EXPECT_TRUE(destination_slot.is_ready.load());

        EXPECT_EQ(
            destination_slot.event.path,
            "constructed.txt"
        );

        EXPECT_FALSE(source_slot.is_ready.load());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectNoThrow_When_NotifyBatchEmpty
    )
    {
        std::vector<FileSystemEvent> batch;

        EXPECT_NO_THROW(
            manager.notify_batch(batch)
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectSequenceIncrement_When_MultipleActionsHandled
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(5, context);

        for (std::size_t index = 0;
             index < 50;
             ++index)
        {
            manager.handleFileAction(
                static_cast<efsw::WatchID>(5),
                "directory",
                "sample.txt",
                efsw::Actions::Modified,
                ""
            );
        }

        EXPECT_EQ(
            manager.sequence_counter.load(),
            50U
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectConcurrentDispatch_When_MultiThreadedNotify
    )
    {
        constexpr std::size_t thread_count = 4;

        constexpr std::size_t iteration_count = 100;

        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        std::vector<std::thread> threads;

        for (std::size_t thread_index = 0;
             thread_index < thread_count;
             ++thread_index)
        {
            threads.emplace_back(
                [this]()
                {
                    for (std::size_t index = 0;
                         index < iteration_count;
                         ++index)
                    {
                        std::vector<FileSystemEvent> batch;

                        FileSystemEvent event;

                        event.path = "parallel.txt";

                        batch.push_back(event);

                        manager.notify_batch(batch);
                    }
                }
            );
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(
            callback_count.load(),
            thread_count * iteration_count
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFastCompletion_When_PerformanceValidated
    )
    {
        auto start_time =
            std::chrono::steady_clock::now();

        for (std::size_t index = 0;
             index < 10000;
             ++index)
        {
            FileSystemEventListenerManagerOptions options;

            manager.passes_filter(
                "performance.txt",
                options
            );
        }

        auto end_time =
            std::chrono::steady_clock::now();

        auto elapsed =
            std::chrono::duration_cast<
                std::chrono::milliseconds
            >(end_time - start_time);

        EXPECT_LT(elapsed.count(), 2000);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectNoThrow_When_ListenerThrowsException
    )
    {
        manager.add_listener(
            [](const FileSystemEvent&)
            {
                throw std::runtime_error("failure");
            }
        );

        std::vector<FileSystemEvent> batch;

        FileSystemEvent event;

        batch.push_back(event);

        EXPECT_ANY_THROW(
            manager.notify_batch(batch)
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectMaximumQueueCapacity_When_BufferFilled
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(9, context);

        for (std::size_t index = 0;
             index < manager.queue_capacity;
             ++index)
        {
            manager.handleFileAction(
                static_cast<efsw::WatchID>(9),
                "directory",
                "sample.txt",
                efsw::Actions::Modified,
                ""
            );
        }

        EXPECT_EQ(
            manager.write_index.load(),
            manager.queue_capacity
        );
    }

    INSTANTIATE_TEST_CASE_P(
        FileSystemEventListenerManagerExtensions,
        FileSystemEventListenerManagerParameterizedExtensionTest,
        testing::Values(
            std::string(".txt"),
            std::string(".json"),
            std::string(".xml"),
            std::string(".yaml")
        )
    );

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_ResolveFullPathSuccessful
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(1, context);

        std::string output_path;

        auto result = manager.resolve_full_path(
            static_cast<efsw::WatchID>(1),
            "subdirectory",
            "file.txt",
            output_path
        );

        EXPECT_TRUE(result);

        EXPECT_EQ(
            output_path,
            "root/subdirectory/file.txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_ResolveOldPathSuccessful
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(2, context);

        std::string output_path;

        auto result = manager.resolve_old_path(
            static_cast<efsw::WatchID>(2),
            "archive",
            "old.txt",
            output_path
        );

        EXPECT_TRUE(result);

        EXPECT_EQ(
            output_path,
            "root/archive/old.txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectOverwrite_When_RingBufferSlotAlreadyReady
    )
    {
        auto& slot = manager.ring_buffer[0];

        slot.is_ready.store(true);

        manager.write_index.store(0);

        manager.read_index.store(0);

        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(1, context);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(1),
            "directory",
            "overwrite.txt",
            efsw::Actions::Add,
            ""
        );

        EXPECT_EQ(manager.read_index.load(), 1U);

        EXPECT_TRUE(slot.is_ready.load());

        EXPECT_EQ(
            slot.event.path,
            "root/directory/overwrite.txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectWraparound_When_QueueIndexExceedsCapacity
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(3, context);

        manager.write_index.store(
            manager.queue_capacity - 1
        );

        manager.handleFileAction(
            static_cast<efsw::WatchID>(3),
            "directory",
            "wrap.txt",
            efsw::Actions::Modified,
            ""
        );

        manager.handleFileAction(
            static_cast<efsw::WatchID>(3),
            "directory",
            "wrapped.txt",
            efsw::Actions::Modified,
            ""
        );

        auto& slot = manager.ring_buffer[0];

        EXPECT_TRUE(slot.is_ready.load());

        EXPECT_EQ(
            slot.event.path,
            "root/directory/wrapped.txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectCompleteDispatch_When_BatchBoundaryEquals256
    )
    {
        manager.is_running.store(true);

        constexpr std::size_t event_count = 256;

        for (std::size_t index = 0;
             index < event_count;
             ++index)
        {
            auto& slot = manager.ring_buffer[index];

            slot.event.sequence = index;

            slot.event.path = "boundary.txt";

            slot.is_ready.store(true);
        }

        manager.write_index.store(event_count);

        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());

        EXPECT_EQ(callback_count.load(), event_count);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_NotifyBatchWithoutListeners
    )
    {
        std::vector<FileSystemEvent> batch;

        FileSystemEvent event;

        event.path = "empty.txt";

        batch.push_back(event);

        auto result = manager.notify_batch(batch);

        EXPECT_TRUE(result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectAllEventsProcessed_When_MultipleBatchEvents
    )
    {
        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        std::vector<FileSystemEvent> batch;

        for (std::size_t index = 0;
             index < 32;
             ++index)
        {
            FileSystemEvent event;

            event.sequence = index;

            batch.push_back(event);
        }

        auto result = manager.notify_batch(batch);

        EXPECT_TRUE(result);

        EXPECT_EQ(callback_count.load(), 32U);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectOldPathPopulated_When_MovedActionHandled
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(4, context);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(4),
            "directory",
            "new.txt",
            efsw::Actions::Moved,
            "old.txt"
        );

        auto& slot = manager.ring_buffer[0];

        EXPECT_EQ(
            slot.event.old_path,
            "root/directory/old.txt"
        );

        EXPECT_EQ(
            slot.event.path,
            "root/directory/new.txt"
        );

        EXPECT_EQ(
            slot.event.action,
            FileSystemEventListenerAction::MOVED
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectGracefulShutdown_When_StopDuringDispatch
    )
    {
        manager.is_running.store(true);

        for (std::size_t index = 0;
             index < 128;
             ++index)
        {
            auto& slot = manager.ring_buffer[index];

            slot.event.sequence = index;

            slot.is_ready.store(true);
        }

        manager.write_index.store(128);

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(5)
        );

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectYieldBranchExecution_When_DispatchLoopIdle
    )
    {
        manager.is_running.store(true);

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectExplicitFilePriority_When_ExtensionMismatch
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.extensions.insert(".json");

        options.explicit_files.insert(
            "priority.txt"
        );

        auto result = manager.passes_filter(
            "priority.txt",
            options
        );

        EXPECT_TRUE(result);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectPathGenerated_When_EmptyFilenameHandled
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(10, context);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(10),
            "directory",
            "",
            efsw::Actions::Add,
            ""
        );

        auto& slot = manager.ring_buffer[0];

        EXPECT_EQ(
            slot.event.path,
            "root/directory/"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectUnicodePathHandled_When_PathContainsUnicode
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "根";

        manager.watch_registry.emplace(11,context);

        std::string output_path;

        auto result = manager.resolve_full_path(
            static_cast<efsw::WatchID>(11),
            "資料",
            "測試.txt",
            output_path
        );

        EXPECT_TRUE(result);

        EXPECT_EQ(
            output_path,
            "根/資料/測試.txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectOverwriteHandling_When_QueueExceedsCapacity
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(12, context);

        constexpr std::size_t extra_events = 32;

        auto total_events =
            manager.queue_capacity + extra_events;

        for (std::size_t index = 0;
             index < total_events;
             ++index)
        {
            manager.handleFileAction(
                static_cast<efsw::WatchID>(12),
                "directory",
                std::to_string(index) + ".txt",
                efsw::Actions::Modified,
                ""
            );
        }

        EXPECT_EQ(
            manager.write_index.load(),
            total_events
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectConcurrentWrites_When_HandleFileActionStress
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(13, context);

        constexpr std::size_t thread_count = 8;

        constexpr std::size_t iteration_count = 500;

        std::vector<std::thread> threads;

        for (std::size_t thread_index = 0;
             thread_index < thread_count;
             ++thread_index)
        {
            threads.emplace_back(
                [this]()
                {
                    for (std::size_t index = 0;
                         index < iteration_count;
                         ++index)
                    {
                        manager.handleFileAction(
                            static_cast<efsw::WatchID>(13),
                            "directory",
                            "stress.txt",
                            efsw::Actions::Modified,
                            ""
                        );
                    }
                }
            );
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(
            manager.write_index.load(),
            thread_count * iteration_count
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectExceptionPropagation_When_DispatchLoopListenerThrows
    )
    {
        manager.is_running.store(true);

        auto& slot = manager.ring_buffer[0];

        slot.event.sequence = 1;

        slot.is_ready.store(true);

        manager.write_index.store(1);

        manager.add_listener(
            [](const FileSystemEvent&)
            {
                throw std::runtime_error("dispatch");
            }
        );

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        EXPECT_ANY_THROW(
            future.get()
        );

        manager.is_running.store(false);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectPartialBatchDispatch_When_EventCountBelow256
    )
    {
        manager.is_running.store(true);

        constexpr std::size_t event_count = 64;

        for (std::size_t index = 0;
             index < event_count;
             ++index)
        {
            auto& slot = manager.ring_buffer[index];

            slot.event.sequence = index;

            slot.is_ready.store(true);
        }

        manager.write_index.store(event_count);

        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());

        EXPECT_EQ(callback_count.load(), event_count);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectMultipleDispatchIterations_When_EventCountExceeds256
    )
    {
        manager.is_running.store(true);

        constexpr std::size_t event_count = 600;

        for (std::size_t index = 0;
             index < event_count;
             ++index)
        {
            auto& slot = manager.ring_buffer[
                index % manager.queue_capacity
            ];

            slot.event.sequence = index;

            slot.is_ready.store(true);
        }

        manager.write_index.store(event_count);

        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(20)
        );

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());

        EXPECT_EQ(callback_count.load(), event_count);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectSlotReset_When_DispatchConsumesEvents
    )
    {
        manager.is_running.store(true);

        auto& slot = manager.ring_buffer[0];

        slot.event.sequence = 1;

        slot.is_ready.store(true);

        manager.write_index.store(1);

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());

        EXPECT_FALSE(slot.is_ready.load());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectReadIndexAdvance_When_DispatchProcessesEvents
    )
    {
        manager.is_running.store(true);

        constexpr std::size_t event_count = 20;

        for (std::size_t index = 0;
             index < event_count;
             ++index)
        {
            auto& slot = manager.ring_buffer[index];

            slot.event.sequence = index;

            slot.is_ready.store(true);
        }

        manager.write_index.store(event_count);

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());

        EXPECT_EQ(
            manager.read_index.load(),
            event_count
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectOrderingPreserved_When_NotifyBatchDispatches
    )
    {
        std::vector<uint64_t> received;

        manager.add_listener(
            [&received](const FileSystemEvent& event)
            {
                received.push_back(event.sequence);
            }
        );

        std::vector<FileSystemEvent> batch;

        for (std::size_t index = 0;
             index < 16;
             ++index)
        {
            FileSystemEvent event;

            event.sequence = index;

            batch.push_back(event);
        }

        EXPECT_TRUE(manager.notify_batch(batch));

        for (std::size_t index = 0;
             index < 16;
             ++index)
        {
            EXPECT_EQ(received[index], index);
        }
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectDuplicateCallbacks_When_SameListenerAddedTwice
    )
    {
        std::atomic<std::size_t> callback_count(0);

        auto listener =
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            };

        manager.add_listener(listener);

        manager.add_listener(listener);

        std::vector<FileSystemEvent> batch;

        batch.emplace_back();

        EXPECT_TRUE(manager.notify_batch(batch));

        EXPECT_EQ(callback_count.load(), 2U);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectSafeConcurrentMutation_When_AddListenerDuringNotify
    )
    {
        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        std::thread add_thread(
            [this]()
            {
                for (std::size_t index = 0;
                     index < 100;
                     ++index)
                {
                    manager.add_listener(
                        [](const FileSystemEvent&)
                        {
                        }
                    );
                }
            }
        );

        for (std::size_t index = 0;
             index < 100;
             ++index)
        {
            std::vector<FileSystemEvent> batch;

            batch.emplace_back();

            manager.notify_batch(batch);
        }

        add_thread.join();

        EXPECT_GE(callback_count.load(), 100U);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectPathResolution_When_DirectoryEmpty
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "";

        manager.watch_registry.emplace(30, context);

        std::string output_path;

        auto result = manager.resolve_full_path(
            static_cast<efsw::WatchID>(30),
            "subdirectory",
            "file.txt",
            output_path
        );

        EXPECT_TRUE(result);

        EXPECT_EQ(
            output_path,
            "/subdirectory/file.txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectPathResolution_When_RelativePathEmpty
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(31, context);

        std::string output_path;

        auto result = manager.resolve_full_path(
            static_cast<efsw::WatchID>(31),
            "",
            "file.txt",
            output_path
        );

        EXPECT_TRUE(result);

        EXPECT_EQ(
            output_path,
            "root/file.txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectOldPathResolution_When_DirectoryEmpty
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "";

        manager.watch_registry.emplace(32, context);

        std::string output_path;

        auto result = manager.resolve_old_path(
            static_cast<efsw::WatchID>(32),
            "archive",
            "old.txt",
            output_path
        );

        EXPECT_TRUE(result);

        EXPECT_EQ(
            output_path,
            "/archive/old.txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_AnyExtensionMatches
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.extensions.insert(".json");

        options.extensions.insert(".txt");

        EXPECT_TRUE(
            manager.passes_filter(
                "sample.txt",
                options
            )
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFalse_When_ExtensionCaseMismatch
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.extensions.insert(".TXT");

        EXPECT_FALSE(
            manager.passes_filter(
                "sample.txt",
                options
            )
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectTrue_When_ExplicitFileExistsWithoutExtension
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.explicit_files.insert("README");

        EXPECT_TRUE(
            manager.passes_filter(
                "README",
                options
            )
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectLastExtensionUsed_When_PathContainsMultipleDots
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.extensions.insert(".gz");

        EXPECT_TRUE(
            manager.passes_filter(
                "archive.tar.gz",
                options
            )
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectDeletedAction_When_HandleDeleteEvent
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(40, context);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(40),
            "directory",
            "deleted.txt",
            efsw::Actions::Delete,
            ""
        );

        auto& slot = manager.ring_buffer[0];

        EXPECT_EQ(
            slot.event.action,
            FileSystemEventListenerAction::DELETED
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectUnknownAction_When_HandleUnknownEvent
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(41, context);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(41),
            "directory",
            "unknown.txt",
            static_cast<efsw::Action>(999),
            ""
        );

        auto& slot = manager.ring_buffer[0];

        EXPECT_EQ(
            slot.event.action,
            FileSystemEventListenerAction::UNKNOWN
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectEmptyOldPath_When_MovedOldFilenameEmpty
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(42, context);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(42),
            "directory",
            "new.txt",
            efsw::Actions::Moved,
            ""
        );

        auto& slot = manager.ring_buffer[0];

        EXPECT_TRUE(slot.event.old_path.empty());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectPathGenerated_When_InvalidPathCombinationProvided
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(43, context);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(43),
            "",
            "",
            efsw::Actions::Add,
            ""
        );

        auto& slot = manager.ring_buffer[0];

        EXPECT_EQ(
            slot.event.path,
            "root/"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectMonotonicSequence_When_HandleFileActionConcurrent
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(44, context);

        constexpr std::size_t thread_count = 8;

        constexpr std::size_t iteration_count = 250;

        std::vector<std::thread> threads;

        for (std::size_t thread_index = 0;
             thread_index < thread_count;
             ++thread_index)
        {
            threads.emplace_back(
                [this]()
                {
                    for (std::size_t index = 0;
                         index < iteration_count;
                         ++index)
                    {
                        manager.handleFileAction(
                            static_cast<efsw::WatchID>(44),
                            "directory",
                            "file.txt",
                            efsw::Actions::Modified,
                            ""
                        );
                    }
                }
            );
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(
            manager.sequence_counter.load(),
            thread_count * iteration_count
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectSlotReusable_When_DispatchConsumesSlot
    )
    {
        manager.is_running.store(true);

        auto& slot = manager.ring_buffer[0];

        slot.event.sequence = 1;

        slot.is_ready.store(true);

        manager.write_index.store(1);

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());

        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(45, context);

        manager.write_index.store(0);

        manager.read_index.store(0);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(45),
            "directory",
            "reuse.txt",
            efsw::Actions::Add,
            ""
        );

        EXPECT_TRUE(slot.is_ready.load());

        EXPECT_EQ(
            slot.event.path,
            "root/directory/reuse.txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFalse_When_StopWatchingCalledAfterSuccessfulStop
    )
    {
        EXPECT_TRUE(manager.start_watching());

        EXPECT_TRUE(manager.stop_watching());

        EXPECT_FALSE(manager.stop_watching());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectRestartPossible_When_StartAfterStop
    )
    {
        EXPECT_TRUE(manager.start_watching());

        EXPECT_TRUE(manager.stop_watching());

        EXPECT_TRUE(manager.start_watching());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectDispatchOfReadySlot_When_ReadEqualsWrite
    )
    {
        manager.is_running.store(true);

        manager.read_index.store(1);

        manager.write_index.store(1);

        auto& slot = manager.ring_buffer[1];

        slot.event.sequence = 1;

        slot.is_ready.store(true);

        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());

        EXPECT_EQ(callback_count.load(),0U);

        EXPECT_TRUE(slot.is_ready.load());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectListenerMutationSafe_When_ListenerAddsListener
    )
    {
        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [this, &callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);

                manager.add_listener(
                    [](const FileSystemEvent&)
                    {
                    }
                );
            }
        );

        std::vector<FileSystemEvent> batch;

        batch.emplace_back();

        EXPECT_TRUE(manager.notify_batch(batch));

        EXPECT_EQ(callback_count.load(), 1U);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectExceptionPropagation_When_OnlyOneListenerThrows
    )
    {
        manager.add_listener(
            [](const FileSystemEvent&)
            {
            }
        );

        manager.add_listener(
            [](const FileSystemEvent&)
            {
                throw std::runtime_error("failure");
            }
        );

        std::vector<FileSystemEvent> batch;

        batch.emplace_back();

        EXPECT_ANY_THROW(
            manager.notify_batch(batch)
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectLatestContextUsed_When_WatchRegistryOverwritten
    )
    {
        FileSystemEventListenerWatchContext first_context;

        first_context.directory = "old";

        FileSystemEventListenerWatchContext second_context;

        second_context.directory = "new";

        manager.watch_registry.insert_or_assign(
            50,
            second_context
        );

        manager.watch_registry.insert_or_assign(
            50,
            first_context
        );

        std::string output_path;

        auto result = manager.resolve_full_path(
            static_cast<efsw::WatchID>(50),
            "directory",
            "file.txt",
            output_path
        );

        EXPECT_TRUE(result);

        EXPECT_EQ(
            output_path,
            "old/directory/file.txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectOverwriteSemantics_When_QueueOverflowOccurs
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(51, context);

        auto total =
            manager.queue_capacity * 2;

        for (std::size_t index = 0;
             index < total;
             ++index)
        {
            manager.handleFileAction(
                static_cast<efsw::WatchID>(51),
                "directory",
                std::to_string(index) + ".txt",
                efsw::Actions::Modified,
                ""
            );
        }

        auto latest_slot_index =
            (total - 1) % manager.queue_capacity;

        auto& slot =
            manager.ring_buffer[latest_slot_index];

        EXPECT_TRUE(slot.is_ready.load());

        EXPECT_EQ(
            slot.event.path,
            "root/directory/" +
            std::to_string(total - 1) +
            ".txt"
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectNoDuplicateDispatch_When_BatchSplitAt256Boundary
    )
    {
        manager.is_running.store(true);

        constexpr std::size_t event_count = 512;

        for (std::size_t index = 0;
             index < event_count;
             ++index)
        {
            auto& slot =
                manager.ring_buffer[index % manager.queue_capacity];

            slot.event.sequence = index;

            slot.is_ready.store(true);
        }

        manager.write_index.store(event_count);

        std::atomic<std::size_t> callback_count(0);

        std::vector<uint64_t> seen;

        std::mutex m;

        manager.add_listener(
            [&callback_count, &seen, &m](const FileSystemEvent& e)
            {
                std::lock_guard<std::mutex> lock(m);

                seen.push_back(e.sequence);

                callback_count.fetch_add(1);
            }
        );

        auto future =
            std::async(
                std::launch::async,
                [this]()
                {
                    return manager.dispatch_loop();
                }
            );

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());

        EXPECT_EQ(callback_count.load(), event_count);

        std::sort(seen.begin(), seen.end());

        seen.erase(
            std::unique(seen.begin(), seen.end()),
            seen.end()
        );

        EXPECT_EQ(seen.size(), event_count);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectNotifyBatchStopsOnListenerException
    )
    {
        std::vector<std::size_t> order;

        manager.add_listener(
            [&order](const FileSystemEvent&)
            {
                order.push_back(1);
            }
        );

        manager.add_listener(
            [&order](const FileSystemEvent&)
            {
                order.push_back(2);
                throw std::runtime_error("fail");
            }
        );

        manager.add_listener(
            [&order](const FileSystemEvent&)
            {
                order.push_back(3);
            }
        );

        std::vector<FileSystemEvent> batch(1);

        EXPECT_ANY_THROW(manager.notify_batch(batch));

        EXPECT_EQ(order.size(), 2U);
        EXPECT_EQ(order[0], 1U);
        EXPECT_EQ(order[1], 2U);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectStartStopRestartThreadLifecycle
    )
    {
        EXPECT_TRUE(manager.start_watching());

        EXPECT_TRUE(manager.stop_watching());

        EXPECT_TRUE(manager.start_watching());

        EXPECT_TRUE(manager.stop_watching());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectDoubleStopSafeBehavior
    )
    {
        EXPECT_TRUE(manager.start_watching());

        EXPECT_TRUE(manager.stop_watching());

        EXPECT_FALSE(manager.stop_watching());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectOldestSlotOverwritten_When_BufferWrapsMultipleTimes
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(1, context);

        constexpr std::size_t cycles = 3;

        for (std::size_t c = 0; c < cycles; ++c)
        {
            for (std::size_t i = 0;
                 i < manager.queue_capacity;
                 ++i)
            {
                manager.handleFileAction(
                    static_cast<efsw::WatchID>(1),
                    "dir",
                    std::to_string(c * 1000 + i),
                    efsw::Actions::Modified,
                    ""
                );
            }
        }

        auto& slot =
            manager.ring_buffer[
                (manager.write_index.load() - 1) %
                manager.queue_capacity
            ];

        EXPECT_TRUE(slot.is_ready.load());

        EXPECT_NE(slot.event.path, "");
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectStrictMonotonicSequenceUnderConcurrency
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(2, context);

        constexpr std::size_t threads = 8;
        constexpr std::size_t per = 200;

        std::vector<std::thread> t;

        for (std::size_t i = 0; i < threads; ++i)
        {
            t.emplace_back(
                [this]()
                {
                    for (std::size_t j = 0; j < per; ++j)
                    {
                        manager.handleFileAction(
                            static_cast<efsw::WatchID>(2),
                            "dir",
                            "file.txt",
                            efsw::Actions::Modified,
                            ""
                        );
                    }
                }
            );
        }

        for (auto& th : t) th.join();

        EXPECT_EQ(
            manager.sequence_counter.load(),
            threads * per
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectNoDispatchAfterStopDuringActiveLoop
    )
    {
        manager.is_running.store(true);

        for (std::size_t i = 0; i < 128; ++i)
        {
            auto& slot = manager.ring_buffer[i];

            slot.event.sequence = i;

            slot.is_ready.store(true);
        }

        manager.write_index.store(128);

        std::atomic<bool> stopped(false);

        manager.add_listener(
            [&stopped](const FileSystemEvent&)
            {
                if (stopped.load())
                    FAIL();
            }
        );

        auto future =
            std::async(
                std::launch::async,
                [this]()
                {
                    return manager.dispatch_loop();
                }
            );

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        stopped.store(true);

        manager.is_running.store(false);

        EXPECT_TRUE(future.get());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectMovedEdgeCase_When_OldPathMissingButNewValid
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(3, context);

        manager.handleFileAction(
            static_cast<efsw::WatchID>(3),
            "dir",
            "",
            efsw::Actions::Moved,
            "old.txt"
        );

        auto& slot = manager.ring_buffer[0];

        EXPECT_EQ(slot.event.path, "root/dir/");
        EXPECT_NE(slot.event.old_path, "");
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFilterNormalization_ForTrailingSlashAndCase
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.extensions.insert(".txt");

        EXPECT_FALSE(
            manager.passes_filter("file.txt/", options)
        );

        EXPECT_TRUE(
            manager.passes_filter("file.txt", options)
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectUnicodeExtensionMatch_When_Normalized
    )
    {
        FileSystemEventListenerManagerOptions options;

        options.extensions.insert(".txt");

        EXPECT_TRUE(
            manager.passes_filter(
                "文件.txt",
                options
            )
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectRingBufferReuseAfterFullCycle
    )
    {
        FileSystemEventListenerWatchContext context;

        context.directory = "root";

        manager.watch_registry.emplace(4, context);

        for (std::size_t i = 0;
             i < manager.queue_capacity * 2;
             ++i)
        {
            manager.handleFileAction(
                static_cast<efsw::WatchID>(4),
                "dir",
                "x.txt",
                efsw::Actions::Modified,
                ""
            );
        }

        EXPECT_EQ(
            manager.write_index.load(),
            manager.queue_capacity * 2
        );
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectDispatchPartitioning_When_BatchExceeds256
    )
    {
        manager.is_running.store(true);

        constexpr std::size_t event_count = 600;

        for (std::size_t index = 0; index < event_count; ++index)
        {
            auto& slot = manager.ring_buffer[index % manager.queue_capacity];

            slot.event.sequence = index;
            slot.event.path = "p";
            slot.is_ready.store(true);
        }

        manager.write_index.store(event_count);

        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        manager.is_running.store(false);

        auto result = future.get();

        EXPECT_TRUE(result);

        EXPECT_EQ(callback_count.load(), event_count);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectNoDuplicateDispatch_When_MultipleIterationsRun
    )
    {
        manager.is_running.store(true);

        constexpr std::size_t event_count = 300;

        std::unordered_set<uint64_t> seen;

        for (std::size_t index = 0; index < event_count; ++index)
        {
            auto& slot = manager.ring_buffer[index % manager.queue_capacity];

            slot.event.sequence = index;
            slot.is_ready.store(true);
        }

        manager.write_index.store(event_count);

        std::mutex mtx;

        manager.add_listener(
            [&](const FileSystemEvent& event)
            {
                std::lock_guard<std::mutex> lock(mtx);
                seen.insert(event.sequence);
            }
        );

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        manager.is_running.store(false);

        future.get();

        EXPECT_EQ(seen.size(), event_count);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectExact256Boundary_When_DispatchSlicesBatch
    )
    {
        manager.is_running.store(true);

        constexpr std::size_t event_count = 512;

        for (std::size_t index = 0; index < event_count; ++index)
        {
            auto& slot = manager.ring_buffer[index];

            slot.event.sequence = index;
            slot.is_ready.store(true);
        }

        manager.write_index.store(event_count);

        std::atomic<std::size_t> callback_count(0);

        manager.add_listener(
            [&callback_count](const FileSystemEvent&)
            {
                callback_count.fetch_add(1);
            }
        );

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        manager.is_running.store(false);

        future.get();

        EXPECT_EQ(callback_count.load(), event_count);
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectFIFOConsistency_When_RingBufferWrapsMultipleCycles
    )
    {
        constexpr std::size_t cycles = 3;

        constexpr std::size_t total = cycles * 200;

        manager.is_running.store(true);

        for (std::size_t index = 0; index < total; ++index)
        {
            auto& slot = manager.ring_buffer[index % manager.queue_capacity];

            slot.event.sequence = index;
            slot.is_ready.store(true);
        }

        manager.write_index.store(total);

        std::vector<uint64_t> order;
        std::mutex mtx;

        manager.add_listener(
            [&](const FileSystemEvent& event)
            {
                std::lock_guard<std::mutex> lock(mtx);
                order.push_back(event.sequence);
            }
        );

        auto future = std::async(
            std::launch::async,
            [this]()
            {
                return manager.dispatch_loop();
            }
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        manager.is_running.store(false);

        future.get();

        EXPECT_EQ(order.size(), total);

        for (std::size_t i = 1; i < order.size(); ++i)
        {
            EXPECT_EQ(order[i], order[i - 1] + 1);
        }
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectStartStopCycle_When_WatchingRestarted
    )
    {
        EXPECT_TRUE(manager.start_watching());

        EXPECT_TRUE(manager.stop_watching());

        EXPECT_TRUE(manager.start_watching());

        EXPECT_TRUE(manager.stop_watching());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectIdempotentStop_When_StopCalledMultipleTimes
    )
    {
        EXPECT_TRUE(manager.start_watching());

        EXPECT_TRUE(manager.stop_watching());

        EXPECT_FALSE(manager.stop_watching());
    }

    TEST_F(
        FileSystemEventListenerManagerTest,
        Should_ExpectSequenceMonotonic_When_ConcurrentHandleFileActionStress
    )
    {
        constexpr std::size_t threads = 8;
        constexpr std::size_t per_thread = 200;

        FileSystemEventListenerWatchContext context;
        context.directory = "root";
        manager.watch_registry.emplace(1, context);

        std::vector<std::thread> pool;

        for (std::size_t t = 0; t < threads; ++t)
        {
            pool.emplace_back(
                [this]()
                {
                    for (std::size_t i = 0; i < per_thread; ++i)
                    {
                        manager.handleFileAction(
                            static_cast<efsw::WatchID>(1),
                            "d",
                            "f.txt",
                            efsw::Actions::Modified,
                            ""
                        );
                    }
                }
            );
        }

        for (auto& th : pool)
        {
            th.join();
        }

        EXPECT_EQ(manager.sequence_counter.load(), threads * per_thread);
    }
}

#endif
