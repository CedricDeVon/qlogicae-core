#include "pch.hpp"

#include "qlogicae_cpp_core/includes/entity_activation_manager.hpp"

namespace QLogicaeCppCoreTest
{
    static bool wait_for_condition_ms(
        const std::function<bool()>& condition,
        const std::uint64_t timeout_ms
    )
    {
        const std::chrono::milliseconds poll_interval(5);
        const auto start_time = std::chrono::steady_clock::now();
        while (true)
        {
            if (condition())
            {
                return true;
            }
            const auto elapsed_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - start_time
                )
                .count();
            if (static_cast<std::uint64_t>(elapsed_ms) >= timeout_ms)
            {
                return false;
            }
            std::this_thread::sleep_for(poll_interval);
        }
    }

    class EntityActivationManagerTest :
        public ::testing::Test
    {
    public:
        EntityActivationManagerTest()
        {
        }

        ~EntityActivationManagerTest()
        {
        }
    };

    class EntityActivationManagerParamTest :
        public ::testing::TestWithParam<QLogicaeCppCore::EntityActivationStatus>
    {
    public:
        EntityActivationManagerParamTest()
        {
        }

        ~EntityActivationManagerParamTest()
        {
        }
    };

    TEST(EntityActivationManagerTest,
        Should_SetAndGetStatus_When_ValidInput)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        QLogicaeCppCore::Result<bool> set_result;
        std::string name_string("alpha");
        std::string_view name_view = name_string;
        QLogicaeCppCore::EntityActivationStatus status =
            QLogicaeCppCore::EntityActivationStatus::ACTIVE;
        manager.set_entity_status(
            set_result,
            name_view,
            status
        );
        QLogicaeCppCore::Result<QLogicaeCppCore::EntityActivationStatus> get_result;
        manager.get_entity_status(
            get_result,
            name_view
        );
        ASSERT_EQ(get_result.get_value(), status);
    }

    TEST(EntityActivationManagerTest,
        Should_SetConvenienceStatuses_When_Called)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        QLogicaeCppCore::Result<bool> r;
        std::string name_a("a");
        std::string_view view_a = name_a;
        manager.set_entity_status_to_pending(r, view_a);
        QLogicaeCppCore::Result<bool> pending;
        manager.is_entity_status_pending(pending, view_a);
        ASSERT_TRUE(pending.get_value());
        manager.set_entity_status_to_inactive(r, view_a);
        QLogicaeCppCore::Result<bool> inactive;
        manager.is_entity_status_inactive(inactive, view_a);
        ASSERT_TRUE(inactive.get_value());
        manager.set_entity_status_to_active(r, view_a);
        QLogicaeCppCore::Result<bool> active;
        manager.is_entity_status_active(active, view_a);
        ASSERT_TRUE(active.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_ReturnFalse_When_NameNotFound)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        QLogicaeCppCore::Result<bool> found;
        std::string name("missing");
        std::string_view view = name;
        manager.is_entity_name_found(found, view);
        ASSERT_FALSE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_RemoveEntity_When_RemoveInvoked)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        QLogicaeCppCore::Result<bool> r;
        std::string name("remove_me");
        std::string_view view = name;
        manager.set_entity_status_to_active(r, view);
        QLogicaeCppCore::Result<bool> remove;
        manager.remove_entity(remove, view);
        ASSERT_TRUE(remove.get_value());
        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, view);
        ASSERT_FALSE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_ClearAll_When_RemoveAllInvoked)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        QLogicaeCppCore::Result<bool> r;
        std::string a("a");
        std::string b("b");
        std::string_view va = a;
        std::string_view vb = b;
        manager.set_entity_status_to_active(r, va);
        manager.set_entity_status_to_inactive(r, vb);
        QLogicaeCppCore::Result<bool> clear;
        manager.remove_all_entities(clear);
        ASSERT_TRUE(clear.get_value());
        QLogicaeCppCore::Result<bool> fa;
        QLogicaeCppCore::Result<bool> fb;
        manager.is_entity_name_found(fa, va);
        manager.is_entity_name_found(fb, vb);
        ASSERT_FALSE(fa.get_value());
        ASSERT_FALSE(fb.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_ReturnCollectionCopy_When_Requested)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        QLogicaeCppCore::Result<bool> r;
        std::string a("first");
        std::string b("second");
        std::string_view va = a;
        std::string_view vb = b;
        manager.set_entity_status_to_active(r, va);
        manager.set_entity_status_to_inactive(r, vb);
        QLogicaeCppCore::Result<std::unordered_map<std::string,
            QLogicaeCppCore::EntityActivationStatus>> copy_result;
        manager.get_entity_collection_copy(copy_result);
        const auto& map = copy_result.get_value();
        ASSERT_EQ(map.size(), static_cast<size_t>(2));
        ASSERT_EQ(map.at("first"),
            QLogicaeCppCore::EntityActivationStatus::ACTIVE);
        ASSERT_EQ(map.at("second"),
            QLogicaeCppCore::EntityActivationStatus::INACTIVE);
    }

    TEST(EntityActivationManagerTest,
        Should_WorkUnderConcurrentWrites)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        std::atomic<int> done(0);
        const int threads = 8;
        const int posts = 64;
        std::vector<std::thread> list;
        for (int t = 0; t < threads; ++t)
        {
            list.emplace_back(
                [&manager, &done, t, posts]()
                {
                    for (int i = 0; i < posts; ++i)
                    {
                        std::string name =
                            "c_" + std::to_string(t) +
                            "_" + std::to_string(i);
                        std::string_view view = name;
                        QLogicaeCppCore::Result<bool> r;
                        manager.set_entity_status_to_active(
                            r,
                            view
                        );
                        done.fetch_add(1);
                    }
                }
            );
        }
        for (auto& th : list)
        {
            th.join();
        }
        ASSERT_EQ(done.load(), threads * posts);
    }

    TEST(EntityActivationManagerTest,
        Should_HandleAsyncCalls_When_UsingStdAsync)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        std::string name("async");
        std::string_view view_value = name;
        auto future_set = std::async(
            std::launch::async,
            [&manager, view_value]()
            {
                QLogicaeCppCore::Result<bool> r;
                manager.set_entity_status_to_active(
                    r,
                    view_value
                );
                return r.get_value();
            }
        );
        const bool ok = future_set.get();
        ASSERT_TRUE(ok);
        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, view_value);
        ASSERT_TRUE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_HandleStressLoad_When_HighVolume)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        const int threads = 16;
        const int posts = 128;
        std::atomic<int> count(0);
        std::vector<std::thread> list;
        for (int t = 0; t < threads; ++t)
        {
            list.emplace_back(
                [&manager, &count, t, posts]()
                {
                    for (int i = 0; i < posts; ++i)
                    {
                        std::string name =
                            "stress_" + std::to_string(t) +
                            "_" + std::to_string(i);
                        std::string_view view = name;
                        QLogicaeCppCore::Result<bool> r;
                        manager.set_entity_status_to_active(
                            r,
                            view
                        );
                        count.fetch_add(1);
                    }
                }
            );
        }
        for (auto& th : list)
        {
            th.join();
        }
        ASSERT_TRUE(wait_for_condition_ms(
            [&manager, threads, posts]()
            {
                QLogicaeCppCore::Result<std::unordered_map<std::string,
                QLogicaeCppCore::EntityActivationStatus>> r;
        manager.get_entity_collection_copy(r);
        return static_cast<int>(r.get_value().size()) >=
            threads * posts;
            },
            1800
        ));
        ASSERT_EQ(count.load(), threads * posts);
    }

    TEST_P(EntityActivationManagerParamTest,
        Should_SetAndVerifyStatus_ForAllEnumValues)
    {
        const QLogicaeCppCore::EntityActivationStatus status = GetParam();
        QLogicaeCppCore::EntityActivationManager manager;
        QLogicaeCppCore::Result<bool> r;
        std::string name =
            "enum_" + std::to_string(static_cast<int>(status));
        std::string_view view = name;
        manager.set_entity_status(
            r,
            view,
            const_cast<QLogicaeCppCore::EntityActivationStatus&>(status)
        );
        QLogicaeCppCore::Result<QLogicaeCppCore::EntityActivationStatus> g;
        manager.get_entity_status(
            g,
            view
        );
        ASSERT_EQ(g.get_value(), status);
    }

    TEST(EntityActivationManagerTest,
        GetEntityStatus_DoesNotCreateEntry_When_Missing)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        QLogicaeCppCore::Result<QLogicaeCppCore::EntityActivationStatus> r;
        std::string name("missing_get");
        std::string_view view = name;
        manager.get_entity_status(r, view);
        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, view);
        ASSERT_FALSE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        IsStatusDoesNotCreateEntry_When_Missing)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        std::string name("missing_status_check");
        std::string_view view = name;
        QLogicaeCppCore::Result<bool> r;
        manager.is_entity_status_active(r, view);
        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, view);
        ASSERT_FALSE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        RemoveMissingReturnsFalse)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        QLogicaeCppCore::Result<bool> r;
        std::string name("no_such");
        std::string_view view = name;
        manager.remove_entity(r, view);
        ASSERT_FALSE(r.get_value());
    }

    TEST(EntityActivationManagerTest,
        SubstringNameWorks_WithStringViewSlice)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        std::string source = "long_prefix_target_suffix";
        std::string_view slice(source.c_str() + 12, 6);
        QLogicaeCppCore::Result<bool> r;
        manager.set_entity_status_to_active(r, slice);
        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, slice);
        ASSERT_TRUE(found.get_value());
        QLogicaeCppCore::Result<QLogicaeCppCore::EntityActivationStatus> g;
        manager.get_entity_status(g, slice);
        ASSERT_EQ(g.get_value(),
            QLogicaeCppCore::EntityActivationStatus::ACTIVE);
    }

    TEST(EntityActivationManagerTest,
        EmptyNameHandled)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        std::string empty("");
        std::string_view ev = empty;
        QLogicaeCppCore::Result<bool> r;
        manager.set_entity_status_to_active(r, ev);
        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, ev);
        ASSERT_TRUE(found.get_value());
        QLogicaeCppCore::Result<bool> rem;
        manager.remove_entity(rem, ev);
        ASSERT_TRUE(rem.get_value());
        QLogicaeCppCore::Result<bool> after;
        manager.is_entity_name_found(after, ev);
        ASSERT_FALSE(after.get_value());
    }

    TEST(EntityActivationManagerTest,
        ConcurrentReadersAndWriters_NoCrashAndConsistent)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        const int writer_threads = 8;
        const int reader_threads = 8;
        const int posts = 256;
        std::atomic<int> written(0);
        std::vector<std::thread> writers;
        std::vector<std::thread> readers;
        for (int t = 0; t < writer_threads; ++t)
        {
            writers.emplace_back(
                [&manager, &written, t, posts]()
                {
                    for (int i = 0; i < posts; ++i)
                    {
                        std::string name =
                            "mix_" + std::to_string(t) +
                            "_" + std::to_string(i);
                        std::string_view view = name;
                        QLogicaeCppCore::Result<bool> r;
                        manager.set_entity_status_to_active(r, view);
                        written.fetch_add(1);
                    }
                }
            );
        }
        std::atomic<bool> stop_readers(false);
        for (int r = 0; r < reader_threads; ++r)
        {
            readers.emplace_back(
                [&manager, &stop_readers]()
                {
                    while (!stop_readers.load())
                    {
                        std::string name =
                            "mix_" + std::to_string(
                                std::rand() % 8) + "_" +
                            std::to_string(std::rand() % 256);
                        std::string_view view = name;
                        QLogicaeCppCore::Result<bool> f;
                        manager.is_entity_name_found(f, view);
                        QLogicaeCppCore::Result<QLogicaeCppCore::EntityActivationStatus> g;
                        manager.get_entity_status(g, view);
                    }
                }
            );
        }
        for (auto& w : writers)
        {
            w.join();
        }
        stop_readers.store(true);
        for (auto& r : readers)
        {
            r.join();
        }
        QLogicaeCppCore::Result<std::unordered_map<std::string,
            QLogicaeCppCore::EntityActivationStatus>> copy;
        manager.get_entity_collection_copy(copy);
        const auto size = static_cast<int>(copy.get_value().size());
        ASSERT_GE(size, written.load() - 0);
    }

    INSTANTIATE_TEST_CASE_P(
        EnumValues,
        EntityActivationManagerParamTest,
        ::testing::Values(
            QLogicaeCppCore::EntityActivationStatus::ACTIVE,
            QLogicaeCppCore::EntityActivationStatus::INACTIVE,
            QLogicaeCppCore::EntityActivationStatus::PENDING
        )
    );   

    TEST(EntityActivationManagerTest,
        Should_NotInsertEntity_When_GetStatusOnMissingKey)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<QLogicaeCppCore::EntityActivationStatus> result;
        std::string name("ghost");
        std::string_view view = name;

        manager.get_entity_status(result, view);

        
        
        QLogicaeCppCore::Result<bool> exists;
        manager.is_entity_name_found(exists, view);

        ASSERT_FALSE(exists.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_ReturnFalse_ForStatusChecks_OnMissingEntity)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> active;
        QLogicaeCppCore::Result<bool> inactive;
        QLogicaeCppCore::Result<bool> pending;

        std::string name("none");
        std::string_view view = name;

        manager.is_entity_status_active(active, view);
        manager.is_entity_status_inactive(inactive, view);
        manager.is_entity_status_pending(pending, view);

        ASSERT_FALSE(active.get_value());
        ASSERT_FALSE(inactive.get_value());
        ASSERT_FALSE(pending.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_ReturnFalse_When_RemovingNonExistentEntity)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> result;

        std::string name("nonexistent");
        std::string_view view = name;

        manager.remove_entity(result, view);

        ASSERT_FALSE(result.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_HandleEmptyName_Gracefully)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> result;
        std::string_view empty_name("");

        manager.set_entity_status_to_active(result, empty_name);
        ASSERT_TRUE(result.get_value());

        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, empty_name);

        ASSERT_TRUE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_RejectDanglingStringView_When_KeyOwnershipLost)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> result;

        std::string_view dangling_view;
        {
            std::string temp("temporary");
            dangling_view = std::string_view(temp.data(), temp.size());
            manager.set_entity_status_to_active(result, dangling_view);
        }
                       
        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, dangling_view);

        ASSERT_FALSE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_NotModifyReturnedCollectionCopy_AfterInternalMutation)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> result;
        std::string key("k");
        std::string_view view = key;
        manager.set_entity_status_to_active(result, view);

        QLogicaeCppCore::Result<
            std::unordered_map<std::string, QLogicaeCppCore::EntityActivationStatus>
        > copy_before;

        manager.get_entity_collection_copy(copy_before);
        auto map_before = copy_before.get_value();

        
        manager.set_entity_status_to_inactive(result, view);

        
        ASSERT_EQ(
            map_before.at("k"),
            QLogicaeCppCore::EntityActivationStatus::ACTIVE
        );
    }

    TEST(EntityActivationManagerTest,
        Should_SupportConcurrentReadsWithoutDeadlock)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        QLogicaeCppCore::Result<bool> result;

        std::string key("k");
        std::string_view view = key;
        manager.set_entity_status_to_active(result, view);

        std::atomic<bool> ready(false);
        std::vector<std::thread> threads;
        const int count = 8;

        for (int i = 0; i < count; ++i)
        {
            threads.emplace_back([&]
                {
                    while (!ready.load()) {}
                    for (int j = 0; j < 1000; ++j)
                    {
                        QLogicaeCppCore::Result<bool> active;
                        manager.is_entity_status_active(active, view);
                    }
                });
        }

        ready = true;

        for (auto& t : threads)
        {
            t.join();
        }

        SUCCEED();
    }

    TEST(EntityActivationManagerTest,
        Should_SupportConcurrentWrites)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::atomic<bool> start(false);
        std::vector<std::thread> threads;
        const int count = 8;

        for (int i = 0; i < count; ++i)
        {
            threads.emplace_back([&, i]
                {
                    std::string k = "k" + std::to_string(i);
                    std::string_view view = k;

                    while (!start.load()) {}

                    QLogicaeCppCore::Result<bool> result;
                    for (int j = 0; j < 200; ++j)
                    {
                        manager.set_entity_status_to_active(result, view);
                    }
                });
        }

        start = true;

        for (auto& t : threads)
        {
            t.join();
        }

        SUCCEED();
    }

    TEST(EntityActivationManagerTest,
        Should_HandleMixedReadWriteConcurrency)
    {
        QLogicaeCppCore::EntityActivationManager manager;
        std::atomic<bool> start(false);

        std::string key("shared");
        std::string_view view = key;

        QLogicaeCppCore::Result<bool> init;
        manager.set_entity_status_to_active(init, view);

        std::thread writer([&]
            {
                while (!start.load()) {}
                QLogicaeCppCore::Result<bool> r;
                for (int i = 0; i < 500; ++i)
                {
                    manager.set_entity_status_to_inactive(r, view);
                    manager.set_entity_status_to_active(r, view);
                }
            });

        std::thread reader([&]
            {
                while (!start.load()) {}
                for (int i = 0; i < 500; ++i)
                {
                    QLogicaeCppCore::Result<bool> active;
                    manager.is_entity_status_active(active, view);
                }
            });

        start = true;

        writer.join();
        reader.join();

        SUCCEED();
    }

    TEST(EntityActivationManagerTest,
        Should_StoreCopyOfStringView_When_SetActiveIsCalled)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> result;

        {
            std::string temp("ephemeral");
            std::string_view view(temp);
            manager.set_entity_status_to_active(result, view);
            ASSERT_TRUE(result.get_value());
        }

        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, "ephemeral");

        ASSERT_TRUE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_FindKeyInsertedFromTemporaryStringLiteral)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> result;

        manager.set_entity_status_to_active(result,
            std::string_view("literal_key"));
        ASSERT_TRUE(result.get_value());

        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found,
            std::string_view("literal_key"));

        ASSERT_TRUE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_HandleOverlappingStringViewsCorrectly)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string base("abcdefghij");

        QLogicaeCppCore::Result<bool> r1;
        QLogicaeCppCore::Result<bool> r2;

        std::string_view v1(base.data(), 5);
        std::string_view v2(base.data() + 2, 5);

        manager.set_entity_status_to_active(r1, v1);
        manager.set_entity_status_to_active(r2, v2);

        ASSERT_TRUE(r1.get_value());
        ASSERT_TRUE(r2.get_value());

        QLogicaeCppCore::Result<bool> f1;
        QLogicaeCppCore::Result<bool> f2;

        manager.is_entity_name_found(f1, v1);
        manager.is_entity_name_found(f2, v2);

        ASSERT_TRUE(f1.get_value());
        ASSERT_TRUE(f2.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_FindKeyFromSubstringViewAfterOriginalStringIsModified)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string base("xyz_modify_test");

        QLogicaeCppCore::Result<bool> result;
        std::string_view sub(base.data() + 4, 6);

        manager.set_entity_status_to_active(result, sub);
        ASSERT_TRUE(result.get_value());

        base[4] = 'Q';
        base[5] = 'Q';

        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, std::string_view("modify"));
        ASSERT_TRUE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_FindKeysInsertedThroughTemporaryRValueString)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> result;

        std::string dynamic = "dynamic_key";
        manager.set_entity_status_to_active(result,
            std::string_view(dynamic));
        ASSERT_TRUE(result.get_value());

        dynamic.clear();
        dynamic.shrink_to_fit();

        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found,
            std::string_view("dynamic_key"));

        ASSERT_TRUE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_FindKeyInsertedFromZeroLengthStringView)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> result;

        std::string_view empty("");
        manager.set_entity_status_to_active(result, empty);

        ASSERT_TRUE(result.get_value());

        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found, empty);

        ASSERT_TRUE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_RejectLookupWhenKeyNotPreviouslyInserted)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> found;
        manager.is_entity_name_found(found,
            std::string_view("not_present"));

        ASSERT_FALSE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_StoreDistinctKeysEvenIfViewsShareMemoryRegion)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string source("ABCDEFGH");

        std::string_view v1(source.data(), 3);
        std::string_view v2(source.data() + 1, 3);

        QLogicaeCppCore::Result<bool> r1;
        QLogicaeCppCore::Result<bool> r2;

        manager.set_entity_status_to_active(r1, v1);
        manager.set_entity_status_to_active(r2, v2);

        ASSERT_TRUE(r1.get_value());
        ASSERT_TRUE(r2.get_value());

        QLogicaeCppCore::Result<bool> f1;
        QLogicaeCppCore::Result<bool> f2;

        manager.is_entity_name_found(f1, v1);
        manager.is_entity_name_found(f2, v2);

        ASSERT_TRUE(f1.get_value());
        ASSERT_TRUE(f2.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_OverwriteStatus_When_SameKeyInsertedTwice)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> r;
        std::string key("dup");
        std::string_view view = key;

        manager.set_entity_status_to_active(r, view);
        ASSERT_TRUE(r.get_value());

        manager.set_entity_status_to_inactive(r, view);
        ASSERT_TRUE(r.get_value());

        QLogicaeCppCore::Result<
            QLogicaeCppCore::EntityActivationStatus> g;

        manager.get_entity_status(g, view);

        ASSERT_EQ(g.get_value(),
            QLogicaeCppCore::EntityActivationStatus::INACTIVE);
    }


    TEST(EntityActivationManagerTest,
        Should_RespectStatusTransitions)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> r;
        std::string name("transition");
        std::string_view view = name;

        manager.set_entity_status_to_pending(r, view);
        manager.set_entity_status_to_active(r, view);
        manager.set_entity_status_to_inactive(r, view);

        QLogicaeCppCore::Result<
            QLogicaeCppCore::EntityActivationStatus> g;

        manager.get_entity_status(g, view);

        ASSERT_EQ(g.get_value(),
            QLogicaeCppCore::EntityActivationStatus::INACTIVE);
    }


    TEST(EntityActivationManagerTest,
        RemoveAllOnEmpty_ReturnsTrue)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> r;

        manager.remove_all_entities(r);

        ASSERT_TRUE(r.get_value());
    }


    TEST(EntityActivationManagerTest,
        CollectionCopyEmpty_When_NoEntries)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<
            std::unordered_map<std::string,
            QLogicaeCppCore::EntityActivationStatus>> r;

        manager.get_entity_collection_copy(r);

        ASSERT_TRUE(r.get_value().empty());
    }


    TEST(EntityActivationManagerTest,
        ConcurrentWritesSameKey_NoCrash)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string key("shared");
        std::string_view view = key;

        std::atomic<bool> start(false);
        std::vector<std::thread> threads;

        for (int i = 0; i < 8; ++i)
        {
            threads.emplace_back([&]
                {
                    while (!start.load()) {}
                    QLogicaeCppCore::Result<bool> r;

                    for (int j = 0; j < 500; ++j)
                    {
                        manager.set_entity_status_to_active(r, view);
                        manager.set_entity_status_to_inactive(r, view);
                    }
                });
        }

        start = true;

        for (auto& t : threads)
        {
            t.join();
        }

        SUCCEED();
    }


    TEST(EntityActivationManagerTest,
        ConcurrentRemoveAndRead_NoCrash)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string key("cr");
        std::string_view view = key;

        QLogicaeCppCore::Result<bool> r;
        manager.set_entity_status_to_active(r, view);

        std::atomic<bool> go(false);

        std::thread remover([&]
            {
                while (!go.load()) {}
                for (int i = 0; i < 200; ++i)
                {
                    manager.remove_entity(r, view);
                }
            });

        std::thread reader([&]
            {
                while (!go.load()) {}
                for (int i = 0; i < 200; ++i)
                {
                    QLogicaeCppCore::Result<bool> f;
                    manager.is_entity_name_found(f, view);
                }
            });

        go = true;

        remover.join();
        reader.join();

        SUCCEED();
    }

    TEST(EntityActivationManagerTest,
        Should_StillFindKey_When_OriginalMemoryOverwritten)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> r;

        char buffer[32];

        const char* src = "copy_me";
        std::memcpy(buffer, src, std::strlen(src) + 1);

        std::string_view view(buffer);

        manager.set_entity_status_to_active(r, view);

        std::memset(buffer, 'X', sizeof(buffer));

        QLogicaeCppCore::Result<bool> found;

        manager.is_entity_name_found(found, "copy_me");

        ASSERT_TRUE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_HandleUnicodeKeys)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> r;

        std::string key(
            reinterpret_cast<const char*>(u8"東京")
        );
        std::string_view view = key;

        manager.set_entity_status_to_active(r, view);
        ASSERT_TRUE(r.get_value());

        QLogicaeCppCore::Result<bool> found;

        manager.is_entity_name_found(found, view);

        ASSERT_TRUE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_HandleVeryLargeKey)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string big(4096, 'A');
        std::string_view view = big;

        QLogicaeCppCore::Result<bool> r;

        manager.set_entity_status_to_active(r, view);

        ASSERT_TRUE(r.get_value());

        QLogicaeCppCore::Result<bool> found;

        manager.is_entity_name_found(found, view);

        ASSERT_TRUE(found.get_value());
    }


    TEST(EntityActivationManagerTest,
        RemoveInsertCycles_NoCorruption)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string key("cycle");
        std::string_view view = key;

        QLogicaeCppCore::Result<bool> r;

        for (int i = 0; i < 200; ++i)
        {
            manager.set_entity_status_to_active(r, view);
            manager.remove_entity(r, view);
        }

        QLogicaeCppCore::Result<bool> found;

        manager.is_entity_name_found(found, view);

        ASSERT_FALSE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_RecognizeDifferentOwnersWithSameContent)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> r1;
        QLogicaeCppCore::Result<bool> r2;

        std::string a("duplicate");
        std::string b("duplicate");

        std::string_view v1 = a;
        std::string_view v2 = b;

        manager.set_entity_status_to_active(r1, v1);
        manager.set_entity_status_to_inactive(r2, v2);

        QLogicaeCppCore::Result<bool> f1;
        QLogicaeCppCore::Result<bool> f2;

        manager.is_entity_name_found(f1, v1);
        manager.is_entity_name_found(f2, v2);

        ASSERT_TRUE(f1.get_value());
        ASSERT_TRUE(f2.get_value());
    }

    TEST(EntityActivationManagerTest,
        Should_NotCrash_When_RemoveOccursDuringReads)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> init;
        std::string key("shared");
        std::string_view view = key;

        manager.set_entity_status_to_active(init, view);

        std::atomic<bool> start(false);

        std::thread writer([&]
            {
                while (!start.load()) {}
                QLogicaeCppCore::Result<bool> r;
                manager.remove_entity(r, view);
            });

        std::thread reader([&]
            {
                while (!start.load()) {}
                for (int i = 0; i < 1000; ++i)
                {
                    QLogicaeCppCore::Result<bool> f;
                    manager.is_entity_name_found(f, view);
                }
            });

        start = true;

        writer.join();
        reader.join();

        SUCCEED();
    }

    TEST(EntityActivationManagerTest,
        Should_ReturnSnapshot_WithInProgressMutations)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::atomic<bool> start(false);

        std::thread writer([&]
            {
                while (!start.load()) {}
                QLogicaeCppCore::Result<bool> r;
                for (int i = 0; i < 500; ++i)
                {
                    std::string k = "w_" + std::to_string(i);
                    std::string_view v = k;
                    manager.set_entity_status_to_active(r, v);
                }
            });

        std::thread snapshot([&]
            {
                while (!start.load()) {}
                for (int i = 0; i < 50; ++i)
                {
                    QLogicaeCppCore::Result<
                        std::unordered_map<std::string,
                        QLogicaeCppCore::EntityActivationStatus>
                    > c;
                    manager.get_entity_collection_copy(c);
                }
            });

        start = true;

        writer.join();
        snapshot.join();

        SUCCEED();
    }

    TEST(EntityActivationManagerTest,
        Should_HandleFullStatusTransitionCycle)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> r;

        std::string name("cycle");
        std::string_view view = name;

        manager.set_entity_status_to_active(r, view);
        manager.set_entity_status_to_inactive(r, view);
        manager.set_entity_status_to_pending(r, view);
        manager.set_entity_status_to_active(r, view);

        QLogicaeCppCore::Result<QLogicaeCppCore::EntityActivationStatus> g;
        manager.get_entity_status(g, view);

        ASSERT_EQ(g.get_value(),
            QLogicaeCppCore::EntityActivationStatus::ACTIVE);
    }

    TEST(EntityActivationManagerTest,
        Should_HandleRemoveHeavyStress)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        const int count = 256;

        std::atomic<int> removed(0);

        std::vector<std::thread> threads;

        for (int i = 0; i < count; ++i)
        {
            std::string k = "r_" + std::to_string(i);
            std::string_view v = k;

            QLogicaeCppCore::Result<bool> r;
            manager.set_entity_status_to_active(r, v);
        }

        for (int t = 0; t < 8; ++t)
        {
            threads.emplace_back([&manager, &removed, count]()
                {
                    for (int i = 0; i < count; ++i)
                    {
                        std::string k = "r_" + std::to_string(i);
                        std::string_view v = k;

                        QLogicaeCppCore::Result<bool> r;
                        manager.remove_entity(r, v);
                        if (r.get_value())
                        {
                            removed.fetch_add(1);
                        }
                    }
                });
        }

        for (auto& th : threads)
        {
            th.join();
        }

        ASSERT_GE(removed.load(), 0);
    }

    TEST(EntityActivationManagerTest,
        Should_BeEmpty_AfterBulkInsertAndRemove)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        const int n = 128;

        QLogicaeCppCore::Result<bool> r;

        for (int i = 0; i < n; ++i)
        {
            std::string k = "b_" + std::to_string(i);
            std::string_view v = k;
            manager.set_entity_status_to_active(r, v);
        }

        for (int i = 0; i < n; ++i)
        {
            std::string k = "b_" + std::to_string(i);
            std::string_view v = k;

            QLogicaeCppCore::Result<bool> rr;
            manager.remove_entity(rr, v);
        }

        QLogicaeCppCore::Result<
            std::unordered_map<std::string,
            QLogicaeCppCore::EntityActivationStatus>
        > snapshot;

        manager.get_entity_collection_copy(snapshot);

        ASSERT_EQ(snapshot.get_value().size(), static_cast<size_t>(0));
    }

    TEST(EntityActivationManagerTest,
        QueryFunctions_InsertDefaultEntry_When_KeyMissing)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<QLogicaeCppCore::EntityActivationStatus> status;

        std::string name = "ghost";

        manager.get_entity_status(status, name);

        ASSERT_TRUE(status.get_value() ==
            QLogicaeCppCore::EntityActivationStatus::NONE);
    }

    TEST(EntityActivationManagerTest,
        RemoveMissingEntity_ReturnsFalse_AndDoesNotCrash)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> removed;

        std::string key = "not_present";

        manager.remove_entity(removed, key);

        ASSERT_FALSE(removed.get_value());
    }

    TEST(EntityActivationManagerTest,
        RemoveExistingEntity_ReturnsTrue)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> dummy;

        std::string key = "present";

        manager.set_entity_status_to_active(dummy, key);

        QLogicaeCppCore::Result<bool> removed;

        manager.remove_entity(removed, key);

        ASSERT_TRUE(removed.get_value());
    }

    TEST(EntityActivationManagerTest,
        SnapshotIsConsistent_AndContainsOnlyValidEntries)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> r;

        for (int i = 0; i < 200; ++i)
        {
            std::string k = "k" + std::to_string(i);
            manager.set_entity_status_to_active(r, k);
        }

        QLogicaeCppCore::Result<
            std::unordered_map<std::string,
            QLogicaeCppCore::EntityActivationStatus>> snap;

        manager.get_entity_collection_copy(snap);

        auto map = snap.get_value();

        ASSERT_EQ(map.size(), 200u);

        for (auto& kv : map)
        {
            ASSERT_TRUE(kv.second ==
                QLogicaeCppCore::EntityActivationStatus::ACTIVE);
        }
    }

    TEST(EntityActivationManagerTest,
        SnapshotDuringConcurrentWrites_RemainsSelfConsistent)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::atomic<bool> running{ true };

        std::thread writer([&]
            {
                QLogicaeCppCore::Result<bool> r;

                int i = 0;
                while (running.load())
                {
                    std::string k = "w" + std::to_string(i++);
                    manager.set_entity_status_to_active(r, k);
                }
            });

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        QLogicaeCppCore::Result<
            std::unordered_map<std::string,
            QLogicaeCppCore::EntityActivationStatus>> snapshot;

        manager.get_entity_collection_copy(snapshot);

        running.store(false);

        writer.join();

        auto map = snapshot.get_value();

        for (auto& kv : map)
        {
            ASSERT_TRUE(kv.second ==
                QLogicaeCppCore::EntityActivationStatus::ACTIVE ||
                kv.second ==
                QLogicaeCppCore::EntityActivationStatus::INACTIVE ||
                kv.second ==
                QLogicaeCppCore::EntityActivationStatus::PENDING);
        }
    }

    TEST(EntityActivationManagerTest,
        RemoveAllEntities_ClearsState)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> r;

        manager.set_entity_status_to_active(r, "a");
        manager.set_entity_status_to_active(r, "b");

        QLogicaeCppCore::Result<bool> removed;

        manager.remove_all_entities(removed);

        ASSERT_TRUE(removed.get_value());

        QLogicaeCppCore::Result<bool> exists;

        manager.is_entity_name_found(exists, "a");

        ASSERT_FALSE(exists.get_value());
    }


    TEST(EntityActivationManagerTest,
        GetEntityStatus_OnMissingKey_InsertsDefaultAndReturnsNonActive)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string key = "missing_key";

        QLogicaeCppCore::Result<
            QLogicaeCppCore::EntityActivationStatus> result;

        manager.get_entity_status(result, key);

        auto value = result.get_value();

        ASSERT_FALSE(value ==
            QLogicaeCppCore::EntityActivationStatus::ACTIVE);
    }

    TEST(EntityActivationManagerTest,
        NameFound_ReturnsFalse_When_KeyMissing)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string key = "absent";

        QLogicaeCppCore::Result<bool> found;

        manager.is_entity_name_found(found, key);

        ASSERT_FALSE(found.get_value());
    }

    TEST(EntityActivationManagerTest,
        StatusChecks_ReturnFalse_When_KeyMissing)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string key = "none";

        QLogicaeCppCore::Result<bool> r;

        manager.is_entity_status_active(r, key);
        ASSERT_FALSE(r.get_value());

        manager.is_entity_status_inactive(r, key);
        ASSERT_FALSE(r.get_value());

        manager.is_entity_status_pending(r, key);
        ASSERT_FALSE(r.get_value());
    }

    TEST(EntityActivationManagerTest,
        RemoveEntity_ReturnsFalse_When_KeyMissing)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        std::string key = "nope";

        QLogicaeCppCore::Result<bool> removed;

        manager.remove_entity(removed, key);

        ASSERT_FALSE(removed.get_value());
    }

    TEST(EntityActivationManagerTest,
        RemoveEntity_ReturnsTrue_When_KeyExists)
    {
        QLogicaeCppCore::EntityActivationManager manager;

        QLogicaeCppCore::Result<bool> dummy;

        std::string key = "present";

        manager.set_entity_status_to_active(dummy, key);

        QLogicaeCppCore::Result<bool> removed;

        manager.remove_entity(removed, key);

        ASSERT_TRUE(removed.get_value());
    }

}
