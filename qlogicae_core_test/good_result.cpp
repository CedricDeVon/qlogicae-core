#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{
    template <typename T, typename M = std::string>
    struct ResultFactory {
        static QLogicaeCore::GoodResult<T, M>* make(std::optional<T> value, std::optional<M> metadata) {
            return new QLogicaeCore::GoodResult<T, M>(value, metadata);
        }
    };

    class GoodResultTest : public ::testing::TestWithParam<std::any> {
    };

    TEST_F(GoodResultTest, Should_Expect_True_When_IsStatusGood) {
        auto* result = ResultFactory<int>::make(10, "meta");
        EXPECT_TRUE(result->is_status_good());
        delete result;
    }

    TEST_F(GoodResultTest, Should_Expect_True_When_HasValue) {
        auto* result = ResultFactory<std::string>::make("ok", "info");
        EXPECT_TRUE(result->has_value());
        delete result;
    }

    TEST_F(GoodResultTest, Should_Expect_True_When_HasMetadata) {
        auto* result = ResultFactory<std::string>::make("ok", "data");
        EXPECT_TRUE(result->has_metadata());
        delete result;
    }

    TEST_F(GoodResultTest, Should_Expect_Equal_When_ValueAccessed) {
        auto* result = ResultFactory<std::string>::make("alpha", "beta");
        EXPECT_EQ(result->get_value().value(), "alpha");
        delete result;
    }

    TEST_F(GoodResultTest, Should_Expect_Equal_When_MetadataAccessed) {
        auto* result = ResultFactory<std::string>::make("gamma", "delta");
        EXPECT_EQ(result->get_metadata().value(), "delta");
        delete result;
    }

    TEST_F(GoodResultTest, Should_Expect_Throw_When_MetadataMissing) {
        auto* result = ResultFactory<std::string>::make("value", std::nullopt);
        EXPECT_THROW({
            auto m = result->get_metadata().value();
            static_cast<void>(m);
            }, std::bad_optional_access);
        delete result;
    }

    TEST_F(GoodResultTest, Should_Expect_Match_When_MultithreadedAccess) {
        auto* result = ResultFactory<int>::make(100, "data");
        std::vector<std::thread> threads;
        for (int i = 0; i < 500; ++i) {
            threads.emplace_back([&]() {
                EXPECT_TRUE(result->has_value());
                EXPECT_TRUE(result->is_status_good());
                });
        }
        for (auto& t : threads) t.join();
        delete result;
    }

    TEST_F(GoodResultTest, Should_Expect_QuickExecution_When_StressTest) {
        auto* result = ResultFactory<int>::make(777, "stress");
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::thread> threads;
        for (int i = 0; i < 10000; ++i) {
            threads.emplace_back([&]() {
                result->has_value();
                });
        }
        for (auto& t : threads) t.join();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_LE(duration, 2000);
        delete result;
    }

    TEST_F(GoodResultTest, Should_Expect_Fast_When_SingleAccess) {
        auto* result = ResultFactory<std::string>::make("text", "meta");
        auto start = std::chrono::high_resolution_clock::now();
        result->has_value();
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        EXPECT_LE(dur, 1000);
        delete result;
    }

    INSTANTIATE_TEST_CASE_P(
        GoodResultTest_Param,
        GoodResultTest,
        ::testing::Values(
            std::any(42),
            std::any(std::string("str")),
            std::any(std::vector<int>{1, 2}),
            std::any(nullptr),
            std::any(true)
        )
    );

    TEST_P(GoodResultTest, Should_Expect_Valid_When_Parameterized) {
        const auto& value_any = GetParam();
        if (value_any.type() == typeid(int)) {
            auto* result = ResultFactory<int>::make(std::any_cast<int>(value_any), "meta");
            EXPECT_TRUE(result->has_value());
            delete result;
        }
        if (value_any.type() == typeid(std::string)) {
            auto* result = ResultFactory<std::string>::make(std::any_cast<std::string>(value_any), "meta");
            EXPECT_TRUE(result->has_value());
            delete result;
        }
    }
}
