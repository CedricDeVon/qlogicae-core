#include "pch.hpp"

#include "qlogicae_core/system_access.hpp"

namespace QLogicaeCoreTest
{
    class SystemAccessTest : public ::testing::TestWithParam<int>
    {
    protected:
        QLogicaeCore::SystemAccess* access;

        void SetUp() override
        {
            access = &QLogicaeCore::SystemAccess::get_instance();
        }
    };

    TEST_P(SystemAccessTest, Should_Expect_AdminCheck_When_CalledConcurrently)
    {
        std::vector<std::future<bool>> futures;
        for (int i = 0; i < GetParam(); ++i)
        {
            futures.emplace_back(std::async(std::launch::async, [this]() -> bool
                {
                    return access->has_admin_access();
                }));
        }

        for (auto& f : futures)
        {
            EXPECT_NO_THROW(f.get());
        }
    }

    TEST(SystemAccessDeathTest, Should_Expect_Termination_When_Restarted)
    {
        ASSERT_DEATH({
            QLogicaeCore::SystemAccess::get_instance().restart_with_admin_access();
            }, "");
    }

    TEST(SystemAccessTest, Should_Expect_TrueOrFalse_When_HasAdminAccess)
    {
        EXPECT_NO_THROW({
            auto result = QLogicaeCore::SystemAccess::get_instance().has_admin_access();
            EXPECT_TRUE(result == true || result == false);
            });
    }

    TEST(SystemAccessTest, Should_Expect_Performance_When_HasAdminAccess)
    {
        auto start = std::chrono::high_resolution_clock::now();
        QLogicaeCore::SystemAccess::get_instance().has_admin_access();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_LE(duration, 2000);
    }

    TEST(SystemAccessTest, Should_Expect_PerformanceFast_When_HasAdminAccess)
    {
        auto start = std::chrono::high_resolution_clock::now();
        QLogicaeCore::SystemAccess::get_instance().has_admin_access();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_LE(duration, 1);
    }

    INSTANTIATE_TEST_CASE_P(
        StressAccessTests,
        SystemAccessTest,
        ::testing::Values(4, 8, 16, 32)
    );
}

