#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{
    template <typename T, typename M = std::string>
    struct ResultFactoryBad {
        static QLogicaeCore::BadResult<T, M>* make(std::optional<T> value, std::optional<M> metadata) {
            return new QLogicaeCore::BadResult<T, M>(value, metadata);
        }
    };

    class BadResultTest : public ::testing::TestWithParam<std::any> {
    };

    TEST_F(BadResultTest, Should_Expect_False_When_IsStatusBad) {
        auto* result = ResultFactoryBad<int>::make(-1, "error");
        EXPECT_FALSE(result->is_status_good());
        delete result;
    }

    TEST_F(BadResultTest, Should_Expect_True_When_HasValue) {
        auto* result = ResultFactoryBad<std::string>::make("data", "bad");
        EXPECT_TRUE(result->has_value());
        delete result;
    }

    TEST_F(BadResultTest, Should_Expect_True_When_HasMetadata) {
        auto* result = ResultFactoryBad<std::string>::make("val", "msg");
        EXPECT_TRUE(result->has_metadata());
        delete result;
    }

    TEST_F(BadResultTest, Should_Expect_Match_When_ValuePresent) {
        auto* result = ResultFactoryBad<int>::make(123, "fail");
        EXPECT_EQ(result->get_value().value(), 123);
        delete result;
    }

    TEST_F(BadResultTest, Should_Expect_Match_When_MetadataPresent) {
        auto* result = ResultFactoryBad<int>::make(321, "oops");
        EXPECT_EQ(result->get_metadata().value(), "oops");
        delete result;
    }

    TEST_F(BadResultTest, Should_Expect_Throw_When_ValueMissing) {
        auto* result = ResultFactoryBad<int>::make(std::nullopt, "meta");
        EXPECT_THROW({
            auto val = result->get_value().value();
            static_cast<void>(val);
            }, std::bad_optional_access);
        delete result;
    }

    TEST_F(BadResultTest, Should_Expect_Valid_When_Multithreaded) {
        auto* result = ResultFactoryBad<int>::make(404, "bad");
        std::vector<std::thread> threads;
        for (int i = 0; i < 500; ++i) {
            threads.emplace_back([&]() {
                EXPECT_FALSE(result->is_status_good());
                });
        }
        for (auto& t : threads) t.join();
        delete result;
    }

    TEST_F(BadResultTest, Should_Expect_Quick_When_StressTest) {
        auto* result = ResultFactoryBad<int>::make(-999, "fail");
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::thread> threads;
        for (int i = 0; i < 10000; ++i) {
            threads.emplace_back([&]() {
                result->has_metadata();
                });
        }
        for (auto& t : threads) t.join();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_LE(duration, 2000);
        delete result;
    }

    TEST_F(BadResultTest, Should_Expect_Fast_When_SingleOperation) {
        auto* result = ResultFactoryBad<std::string>::make("broken", "bad");
        auto start = std::chrono::high_resolution_clock::now();
        result->get_metadata();
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        EXPECT_LE(dur, 1000);
        delete result;
    }

    INSTANTIATE_TEST_CASE_P(
        BadResultTest_Param,
        BadResultTest,
        ::testing::Values(
            std::any(0),
            std::any(std::string("bad")),
            std::any(std::vector<double>{1.1, 2.2}),
            std::any(false)
        )
    );

    TEST_P(BadResultTest, Should_Expect_Correct_When_Parameterized) {
        const auto& value_any = GetParam();
        if (value_any.type() == typeid(int)) {
            auto* result = ResultFactoryBad<int>::make(std::any_cast<int>(value_any), "meta");
            EXPECT_FALSE(result->is_status_good());
            delete result;
        }
        if (value_any.type() == typeid(std::string)) {
            auto* result = ResultFactoryBad<std::string>::make(std::any_cast<std::string>(value_any), "meta");
            EXPECT_FALSE(result->is_status_good());
            delete result;
        }
    }
}
