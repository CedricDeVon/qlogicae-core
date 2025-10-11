#include "pch.hpp"

#include "string_builder.hpp"

namespace QLogicaeCoreTest
{
    class StringBuilderTest : public testing::TestWithParam<std::string>
    {
    protected:
        QLogicaeCore::StringBuilder string_builder;
    };

    struct MemoryTrackingStats
    {
        std::size_t total_allocated = 0;
        std::size_t total_deallocated = 0;
    };

    class TrackingMemoryResource : public std::pmr::memory_resource
    {
    public:
        explicit TrackingMemoryResource(MemoryTrackingStats* stats)
            : stats_pointer(stats) {
        }
    protected:
        void* do_allocate(std::size_t size, std::size_t alignment) override
        {
            stats_pointer->total_allocated += size;
            return ::operator new(size, std::align_val_t(alignment));
        }

        void do_deallocate(
            void* pointer, std::size_t size, std::size_t alignment) override
        {
            stats_pointer->total_deallocated += size;
            ::operator delete(pointer, std::align_val_t(alignment));
        }

        bool do_is_equal(
            const std::pmr::memory_resource& other) const noexcept override
        {
            return this == &other;
        }

    private:
        MemoryTrackingStats* stats_pointer;
    };

    class StringBuilderMemoryTrackingTest : public testing::Test
    {
    protected:
        MemoryTrackingStats stats;
        TrackingMemoryResource resource;
        QLogicaeCore::StringBuilder builder;

        StringBuilderMemoryTrackingTest()
            : resource(&stats), builder(&resource) {
        }

        void TearDown() override
        {
            std::cout << "[Memory] Allocated: "
                << stats.total_allocated
                << " bytes, Deallocated: "
                << stats.total_deallocated
                << " bytes" << std::endl;
        }
    };

    TEST(StringBuilderEdgeTest, Should_Insert_AtPositionZero_When_Empty)
    {
        QLogicaeCore::StringBuilder builder;
        builder.insert("start", 0);
        EXPECT_EQ(std::string(builder.to_string()), "start");
    }

    TEST(StringBuilderEdgeTest, Should_Insert_AtVeryLargePosition_Safely)
    {
        QLogicaeCore::StringBuilder builder;
        builder.append("abc");
        builder.insert("xyz", 999999);
        EXPECT_EQ(std::string(builder.to_string()), "abcxyz");
    }

    TEST(StringBuilderEdgeTest, Should_Handle_NullChar_InputCorrectly)
    {
        QLogicaeCore::StringBuilder builder;
        std::string input = "abc\0def";
        builder.append(input);
        EXPECT_EQ(builder.get_size(), input.size());
    }

    TEST(StringBuilderEdgeTest, Should_Ignore_InvalidUtf8_Trim)
    {
        QLogicaeCore::StringBuilder builder;
        std::string input = "abc";
        builder.append(input);
        builder.left_and_right_trim();
        EXPECT_TRUE(builder.get_size() >= 3);
    }

    TEST(StringBuilderEdgeTest, Should_NotThrow_When_InvalidInsertArgs)
    {
        QLogicaeCore::StringBuilder builder;
        EXPECT_NO_THROW(builder.insert("safe", 100000));
    }

    TEST(StringBuilderEdgeTest, Should_MaintainAllocator_When_UsingToPmrString)
    {
        QLogicaeCore::StringBuilder builder;
        builder.append("check");
        const std::pmr::string& result = builder.to_pmr_string();
        EXPECT_EQ(std::string(result), "check");
    }

    TEST(StringBuilderStateTest, Should_AllowReuse_AfterTakeStringCall)
    {
        QLogicaeCore::StringBuilder builder;
        builder.append("abc");
        std::string taken = builder.take_string();
        EXPECT_TRUE(builder.is_empty());

        builder.append("def");
        EXPECT_EQ(std::string(builder.to_string()), "def");
    }

    TEST_F(StringBuilderMemoryTrackingTest, Should_TrackMemoryUsage)
    {
        builder.append("abc");
        builder.append("def");
        builder.insert("xyz", 2);
        builder.take_pmr_string();
    }

    TEST_P(StringBuilderTest, Should_Append_Text_When_GivenValidString)
    {
        std::string text = GetParam();
        string_builder.append(text);
        EXPECT_EQ(string_builder.get_size(), text.size());
    }

    TEST_P(StringBuilderTest, Should_Prepend_Text_When_GivenValidString)
    {
        std::string text = GetParam();
        string_builder.prepend(text);
        EXPECT_EQ(string_builder.get_size(), text.size());
    }

    TEST_P(StringBuilderTest, Should_Insert_Text_When_GivenValidPosition)
    {
        std::string text = GetParam();
        string_builder.append("123456");
        string_builder.insert(text, 3);
        EXPECT_EQ(string_builder.get_size(), text.size() + 6);
    }

    TEST_P(StringBuilderTest, Should_Handle_AsyncAppend_When_CalledConcurrently)
    {
        auto future = string_builder.async_append(GetParam());
        auto status = future.wait_for(std::chrono::seconds(2));
        EXPECT_EQ(status, std::future_status::ready);
        SUCCEED();
    }

    TEST_P(StringBuilderTest, Should_Clear_Buffer_When_ClearCalled)
    {
        string_builder.append(GetParam());
        string_builder.clear();
        EXPECT_TRUE(string_builder.is_empty());
    }

    TEST_P(StringBuilderTest, Should_LeftTrim_Whitespace_When_Called)
    {
        string_builder.append("   abc");
        string_builder.left_trim();
        EXPECT_EQ(std::string(string_builder.to_string()), "abc");
    }

    TEST_P(StringBuilderTest, Should_RightTrim_Whitespace_When_Called)
    {
        string_builder.append("abc   ");
        string_builder.right_trim();
        EXPECT_EQ(std::string(string_builder.to_string()), "abc");
    }

    TEST_P(StringBuilderTest,
        Should_Trim_Whitespace_When_LeftAndRightTrimCalled)
    {
        string_builder.append("   abc   ");
        string_builder.left_and_right_trim();
        EXPECT_EQ(std::string(string_builder.to_string()), "abc");
    }

    TEST_P(StringBuilderTest, Should_AsyncToString_Return_CorrectString)
    {
        std::string text = GetParam();
        string_builder.append(text);
        auto future = string_builder.async_to_string();
        auto result = future.get();
        EXPECT_EQ(std::string(result), text);
    }

    TEST_P(StringBuilderTest, Should_AsyncTakeString_EmptyBufferAfterCall)
    {
        std::string text = GetParam();
        string_builder.append(text);
        auto result = string_builder.async_take_string().get();
        EXPECT_TRUE(string_builder.is_empty());
        EXPECT_EQ(std::string(result), text);
    }

    TEST_P(StringBuilderTest, Should_Handle_StressAppend_When_CalledManyTimes)
    {
        for (int index = 0; index < 100000; ++index)
        {
            string_builder.append("a");
        }
        EXPECT_EQ(string_builder.get_size(), 100000);
    }

    TEST_P(StringBuilderTest,
        Should_Handle_ConcurrentInsertions_When_MultipleThreadsUsed)
    {
        std::vector<std::thread> thread_list;
        for (int index = 0; index < 10; ++index)
        {
            thread_list.emplace_back([this]()
                {
                    for (int iteration = 0; iteration < 1000; ++iteration)
                    {
                        string_builder.append("x");
                    }
                });
        }
        for (std::thread& thread_reference : thread_list)
        {
            thread_reference.join();
        }
        EXPECT_EQ(string_builder.get_size(), 10000);
    }

    TEST_P(StringBuilderTest, Should_Return_PmrString_When_ToPmrStringCalled)
    {
        std::string text = GetParam();
        string_builder.append(text);
        const std::pmr::string& result = string_builder.to_pmr_string();
        EXPECT_EQ(std::string(result), text);
    }

    TEST_P(StringBuilderTest, Should_Take_PmrString_And_ClearBuffer)
    {
        std::string text = GetParam();
        string_builder.append(text);
        std::pmr::string result = string_builder.take_pmr_string();
        EXPECT_TRUE(string_builder.is_empty());
        EXPECT_EQ(std::string(result), text);
    }

    TEST_P(StringBuilderTest, Should_ReserveCapacity_And_RetainContent)
    {
        std::string text = GetParam();
        string_builder.append(text);
        string_builder.reserve_capacity(2048);
        EXPECT_EQ(std::string(string_builder.to_string()), text);
    }

    TEST_P(StringBuilderTest, Should_ShrinkToFit_And_RetainContent)
    {
        std::string text = GetParam();
        string_builder.append(text);
        string_builder.shrink_to_fit();
        EXPECT_EQ(std::string(string_builder.to_string()), text);
    }

    TEST_P(StringBuilderTest, Should_AsyncPrepend_ReturnAfterExecution)
    {
        auto future = string_builder.async_prepend(GetParam());
        auto status = future.wait_for(std::chrono::seconds(2));
        EXPECT_EQ(status, std::future_status::ready);
        SUCCEED();
    }

    TEST_P(StringBuilderTest, Should_AsyncInsert_AtPositionZero)
    {
        string_builder.append("world");
        auto future = string_builder.async_insert("hello ", 0);
        auto status = future.wait_for(std::chrono::seconds(2));
        EXPECT_EQ(status, std::future_status::ready);
        EXPECT_EQ(std::string(string_builder.to_string()).substr(0, 5), "hello");
    }

    TEST_P(StringBuilderTest, Should_AsyncClear_ClearTheBuffer)
    {
        string_builder.append("data");
        auto future = string_builder.async_clear();
        future.wait();
        EXPECT_TRUE(string_builder.is_empty());
    }

    INSTANTIATE_TEST_CASE_P(
        StringBuilderParameterTests,
        StringBuilderTest,
        testing::Values(
            "",
            "a",
            "abc",
            std::string(1024, 'x'),
            "   spaced   ",
            "\t\nabc\r"
        )
    );
}
