#pragma once

#include "pch.h"

#include "generator.hpp"

namespace QLogicaeCoreTest
{

    class GeneratorTest : public ::testing::TestWithParam<std::any> {
    protected:
        QLogicaeCore::Generator& generator = QLogicaeCore::Generator::instance();
    };

    TEST_F(GeneratorTest, Should_Expect_ValidUUID_When_GeneratingUUID4) {
        std::string uuid = generator.random_uuid4();
        EXPECT_EQ(uuid.size(), 36);
        EXPECT_NE(uuid.find('-'), std::string::npos);
    }

    TEST_F(GeneratorTest, Should_Expect_ValidSalt_When_GeneratingSalt) {
        auto salt = generator.random_salt();
        EXPECT_EQ(salt.size(), 16);
        bool has_nonzero = false;
        for (auto c : salt) {
            if (c != 0) {
                has_nonzero = true;
                break;
            }
        }
        EXPECT_TRUE(has_nonzero);
    }

    TEST_F(GeneratorTest, Should_Expect_True_When_ProbabilityIsOne) {
        EXPECT_TRUE(generator.random_bool(1.0));
    }

    TEST_F(GeneratorTest, Should_Expect_False_When_ProbabilityIsZero) {
        EXPECT_FALSE(generator.random_bool(0.0));
    }

    TEST_F(GeneratorTest, Should_Expect_Empty_When_StringLengthZero) {
        std::string s = generator.random_string(0);
        EXPECT_TRUE(s.empty());
    }

    TEST_F(GeneratorTest, Should_Expect_Empty_When_CharacterSetIsEmpty) {
        std::string s = generator.random_string(10, "");
        EXPECT_TRUE(s.empty());
    }

    TEST_F(GeneratorTest, Should_Expect_LengthMatch_When_GeneratingString) {
        std::string s = generator.random_string(16);
        EXPECT_EQ(s.length(), 16);
    }

    TEST_F(GeneratorTest, Should_Expect_VectorSizeMatch_When_GeneratingStringVector) {
        auto vec = generator.random_string_vector(8, 4);
        EXPECT_EQ(vec.size(), 8);
        for (auto& str : vec) {
            EXPECT_EQ(str.size(), 4);
        }
    }

    TEST_F(GeneratorTest, Should_Expect_WithinRange_When_RandomInt) {
        int value = generator.random_int(10, 20);
        EXPECT_GE(value, 10);
        EXPECT_LE(value, 20);
    }

    TEST_F(GeneratorTest, Should_Expect_WithinRange_When_RandomDouble) {
        double value = generator.random_double(0.25, 0.75);
        EXPECT_GE(value, 0.25);
        EXPECT_LE(value, 0.75);
    }

    TEST_F(GeneratorTest, Should_Expect_UniqueUUIDs_When_Multithreaded) {
        std::unordered_set<std::string> uuid_set;
        std::mutex mtx;
        std::vector<std::thread> threads;
        for (int i = 0; i < 128; ++i) {
            threads.emplace_back([&]() {
                std::string uuid = generator.random_uuid4();
                std::lock_guard<std::mutex> lock(mtx);
                uuid_set.insert(uuid);
                });
        }
        for (auto& t : threads) t.join();
        EXPECT_EQ(uuid_set.size(), 128);
    }

    TEST_F(GeneratorTest, Should_Expect_QuickExecution_When_StressTestUUID) {
        auto start = std::chrono::steady_clock::now();
        std::vector<std::thread> threads;
        std::atomic<int> counter{ 0 };
        for (int i = 0; i < 1024; ++i) {
            threads.emplace_back([&]() {
                generator.random_uuid4();
                counter.fetch_add(1, std::memory_order_relaxed);
                });
        }
        for (auto& t : threads) t.join();
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_EQ(counter.load(), 1024);
        EXPECT_LE(duration, 2000);
    }

    TEST_F(GeneratorTest, Should_Expect_FastResult_When_SingleUUIDAccess) {
        auto start = std::chrono::high_resolution_clock::now();
        generator.random_uuid4();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        EXPECT_LE(duration, 1000);
    }

    INSTANTIATE_TEST_CASE_P(
        GeneratorTest_Parameterized,
        GeneratorTest,
        ::testing::Values(
            std::any(0),
            std::any(5.0),
            std::any(std::string("abcd")),
            std::any(QLogicaeCore::Constants::ALPHA_NUMERIC_CHARACTERS),
            std::any(QLogicaeCore::Constants::FULL_VISIBLE_ASCII_CHARACTERSET)
        )
    );

    TEST_P(GeneratorTest, Should_Expect_Valid_When_UsingVariousArguments) {
        auto param = GetParam();
        if (param.type() == typeid(std::string)) {
            auto str = std::any_cast<std::string>(param);
            auto res = generator.random_string(4, str);
            EXPECT_EQ(res.length(), 4);
        }
        else if (param.type() == typeid(double)) {
            auto value = std::any_cast<double>(param);
            EXPECT_NO_THROW(generator.random_double(0.0, value));
        }
        else if (param.type() == typeid(size_t)) {
            size_t value = std::any_cast<size_t>(param);
            EXPECT_NO_THROW(generator.random_string_vector(value, 4));
        }
        else if (param.type() == typeid(std::string_view)) {
            std::string_view set = std::any_cast<std::string_view>(param);
            auto res = generator.random_string(5, set);
            EXPECT_EQ(res.size(), 5);
        }
    }

    TEST_F(GeneratorTest, Should_Expect_Abort_When_ForceDeathTest) {
        EXPECT_NO_THROW({
            auto s = generator.random_string(8, "");
            static_cast<void>(s);
        });
    }
}

