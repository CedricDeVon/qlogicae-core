#pragma once

#include "pch.h"

#include "validators.hpp"

namespace QLogicaeCoreTest
{
    TEST(ValidatorsTest,
        Should_Return_Same_Instance_When_Accessed_Multiple_Times)
    {
        QLogicaeCore::Validators& first =
            QLogicaeCore::Validators::instance();

        QLogicaeCore::Validators& second =
            QLogicaeCore::Validators::instance();

        ASSERT_EQ(&first, &second);
    }

    TEST(ValidatorsTest,
        Should_Handle_Many_Accesses_Under_Stress)
    {
        QLogicaeCore::Validators* instances[10000];

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 10000; ++i)
        {
            instances[i] = &QLogicaeCore::Validators::instance();
        }

        for (int i = 1; i < 10000; ++i)
        {
            ASSERT_EQ(instances[i], instances[0]);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;

        ASSERT_LT(std::chrono::duration_cast<std::chrono::seconds>(
            duration).count(), 2);
    }

    TEST(ValidatorsTest,
        Should_Be_Safe_When_Used_From_Multiple_Threads)
    {
        std::atomic<int> match_count = 0;
        QLogicaeCore::Validators* base = &QLogicaeCore::Validators::instance();

        std::vector<std::thread> threads;

        for (int i = 0; i < 20; ++i)
        {
            threads.emplace_back([&match_count, base]()
                {
                    QLogicaeCore::Validators* local =
                        &QLogicaeCore::Validators::instance();

                    if (local == base)
                    {
                        ++match_count;
                    }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        ASSERT_EQ(match_count.load(), 20);
    }

    TEST(ValidatorsTest,
        Should_Not_Throw_When_Called_Repeatly_In_TryCatch)
    {
        ASSERT_NO_THROW({
            for (int i = 0; i < 1000; ++i)
            {
                QLogicaeCore::Validators::instance();
            }
            });
    }
}
