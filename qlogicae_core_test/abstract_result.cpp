#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{
    class AbstractResultTest : public ::testing::TestWithParam<std::tuple<std::any, std::any>> {
    protected:
        template <typename T, typename M>
        QLogicaeCore::AbstractResult<T, M>* create_result(bool state, std::optional<T> value, std::optional<M> meta) {
            struct TestableResult : public QLogicaeCore::AbstractResult<T, M> {
                TestableResult(bool s, std::optional<T> v, std::optional<M> m)
                    : QLogicaeCore::AbstractResult<T, M>(s, std::move(v), std::move(m)) {}
            };
            return new TestableResult(state, std::move(value), std::move(meta));
        }
    };

    TEST_F(AbstractResultTest, Should_Expect_True_When_HasValuePresent) {
        auto* result = create_result<int, std::string>(true, 42, "info");
        EXPECT_TRUE(result->has_value());
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_False_When_ValueMissing) {
        auto* result = create_result<int, std::string>(true, std::nullopt, "meta");
        EXPECT_FALSE(result->has_value());
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_True_When_HasMetadataPresent) {
        auto* result = create_result<int, std::string>(true, 77, "log");
        EXPECT_TRUE(result->has_metadata());
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_False_When_MetadataMissing) {
        auto* result = create_result<int, std::string>(true, 77, std::nullopt);
        EXPECT_FALSE(result->has_metadata());
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_False_When_StatusIsBad) {
        auto* result = create_result<int, std::string>(false, 12, "error");
        EXPECT_FALSE(result->is_status_good());
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_CorrectValue_When_ValueSet) {
        auto* result = create_result<std::string, std::string>(true, "success", "ok");
        EXPECT_EQ(result->get_value().value(), "success");
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_CorrectMetadata_When_MetadataSet) {
        auto* result = create_result<std::string, std::string>(true, "value", "meta");
        EXPECT_EQ(result->get_metadata().value(), "meta");
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_Throw_When_DereferencingEmptyValue) {
        auto* result = create_result<int, std::string>(true, std::nullopt, "info");
        EXPECT_THROW({
            auto v = result->get_value().value();
            static_cast<void>(v);
            }, std::bad_optional_access);
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_Throw_When_DereferencingEmptyMetadata) {
        auto* result = create_result<int, std::string>(true, 5, std::nullopt);
        EXPECT_THROW({
            auto m = result->get_metadata().value();
            static_cast<void>(m);
            }, std::bad_optional_access);
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_Success_When_MultithreadedAccess) {
        auto* result = create_result<int, std::string>(true, 100, "info");
        std::vector<std::thread> threads;
        for (int i = 0; i < 100; ++i) {
            threads.emplace_back([&]() {
                EXPECT_TRUE(result->has_value());
                EXPECT_TRUE(result->has_metadata());
                EXPECT_EQ(result->get_value().value(), 100);
                });
        }
        for (auto& t : threads) t.join();
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_FinishWithinTwoSeconds_When_StressTest) {
        auto* result = create_result<int, std::string>(true, 999, "stress");
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::thread> threads;
        for (int i = 0; i < 10000; ++i) {
            threads.emplace_back([&]() {
                result->has_value();
                result->has_metadata();
                });
        }
        for (auto& t : threads) t.join();

        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_LE(dur, 2000);
        delete result;
    }

    TEST_F(AbstractResultTest, Should_Expect_FinishWithinOneMillisecond_When_SingleAccess) {
        auto* result = create_result<int, std::string>(true, 1, "quick");
        auto start = std::chrono::high_resolution_clock::now();
        result->has_value();
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        EXPECT_LE(dur, 1000);
        delete result;
    }

    INSTANTIATE_TEST_CASE_P(
        AbstractResultTest_Param,
        AbstractResultTest,
        ::testing::Values(
            std::make_tuple(std::any(1), std::any(std::string("meta"))),
            std::make_tuple(std::any(std::string("value")), std::any(3.14)),
            std::make_tuple(std::any(std::vector<int>{1, 2, 3}), std::any(nullptr)),
            std::make_tuple(std::any(std::tuple<int, double>{1, 2.2}), std::any(std::monostate{})),
            std::make_tuple(std::any(std::variant<int, std::string>{"hi"}), std::any(std::string("json")))
        )
    );

    TEST_P(AbstractResultTest, Should_Expect_ValidConstruction_When_Parameterized) {
        const auto& [value_any, meta_any] = GetParam();
        if (value_any.has_value() && meta_any.has_value()) {
            if (value_any.type() == typeid(int) && meta_any.type() == typeid(std::string)) {
                auto* result = create_result<int, std::string>(true, std::any_cast<int>(value_any), std::any_cast<std::string>(meta_any));
                EXPECT_TRUE(result->has_value());
                EXPECT_TRUE(result->has_metadata());
                delete result;
            }
        }
    }
}
