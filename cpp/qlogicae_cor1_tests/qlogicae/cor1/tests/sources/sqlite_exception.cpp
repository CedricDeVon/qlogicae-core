#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteException \
	)

#include "../includes/sqlite_exception.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST(SQLiteExceptionTest,
        Should_HaveDefaultValues_When_DefaultConstructed)
    {
        SQLiteException exception;

        EXPECT_EQ(exception.error_code, 0);
        EXPECT_EQ(exception.extended_code, 0);
        EXPECT_EQ(std::string(exception.what()),
            "SQLiteException");
    }

    TEST(SQLiteExceptionTest,
        Should_SetValues_When_UsingParameterizedConstructor)
    {
        SQLiteException exception(
            std::string("error"),
            10,
            20
        );

        EXPECT_EQ(exception.error_code, 10);
        EXPECT_EQ(exception.extended_code, 20);
        EXPECT_EQ(std::string(exception.what()),
            "error");
    }

    TEST(SQLiteExceptionTest,
        Should_ConstructAsync_When_UsingStdAsync)
    {
        std::future<SQLiteException> future =
            std::async(std::launch::async,
                []()
                {
                    return SQLiteException(
                        std::string("async"),
                        5,
                        6
                    );
                }
            );

        SQLiteException exception =
            future.get();

        EXPECT_EQ(exception.error_code, 5);
        EXPECT_EQ(exception.extended_code, 6);
        EXPECT_EQ(std::string(exception.what()),
            "async");
    }

    TEST(SQLiteExceptionTest,
        Should_HandleMultipleThreads_When_ConcurrentCreation)
    {
        std::mutex mutex;
        std::vector<SQLiteException>
            exceptions;

        std::vector<std::thread> threads;

        for (int index = 0; index < 50; index++)
        {
            threads.emplace_back(
                [&exceptions, &mutex, index]()
                {
                    SQLiteException exception(
                        std::string("thread"),
                        index,
                        index + 1
                    );

                    std::lock_guard<std::mutex> lock(mutex);

                    exceptions.push_back(exception);
                }
            );
        }

        for (std::thread& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(exceptions.size(), 50u);
    }

    TEST(SQLiteExceptionTest,
        Should_CompleteStressTest_When_LargeIteration)
    {
        std::vector<SQLiteException>
            exceptions;

        exceptions.reserve(100000);

        for (int index = 0; index < 100000; index++)
        {
            exceptions.emplace_back(
                std::string("stress"),
                index,
                index
            );
        }

        EXPECT_EQ(exceptions.size(), 100000u);
    }

    TEST(SQLiteExceptionTest,
        Should_ThrowAndCatch_When_UsingExceptionFlow)
    {
        bool caught = false;

        try
        {
            throw SQLiteException(
                std::string("throw"),
                1,
                2
            );
        }
        catch (const SQLiteException&)
        {
            caught = true;
        }

        EXPECT_TRUE(caught);
    }

    TEST(SQLiteExceptionTest,
        Should_RespectEdgeValues_When_MaxIntValuesUsed)
    {
        SQLiteException exception(
            std::string("edge"),
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::min()
        );

        EXPECT_EQ(exception.error_code,
            std::numeric_limits<int>::max());

        EXPECT_EQ(exception.extended_code,
            std::numeric_limits<int>::min());
    }

    TEST_P(SQLiteExceptionParameterizedTest,
        Should_ValidateParameters_When_Constructed)
    {
        SQLiteExceptionParameter param =
            GetParam();

        SQLiteException exception(
            param.message,
            param.error_code,
            param.extended_code
        );

        EXPECT_EQ(exception.error_code,
            param.error_code);

        EXPECT_EQ(exception.extended_code,
            param.extended_code);

        EXPECT_EQ(std::string(exception.what()),
            param.message);
    }

    INSTANTIATE_TEST_CASE_P(
        SQLiteExceptionTests,
        SQLiteExceptionParameterizedTest,
        ::testing::Values(
            SQLiteExceptionParameter{"msg",1,2},
            SQLiteExceptionParameter{"",0,0},
            SQLiteExceptionParameter{"negative",-1,-2},
            SQLiteExceptionParameter{
                std::string(1000,'x'),
                42,
                84
            },
            SQLiteExceptionParameter{
                "edge",
                std::numeric_limits<int>::max(),
                std::numeric_limits<int>::min()
            }
        )
    );

    TEST(SQLiteExceptionTest,
    Should_Construct_Expect_DefaultValues_When_DefaultConstructor)
    {
        SQLiteException exception;
        EXPECT_EQ(exception.error_code, 0);
        EXPECT_EQ(exception.extended_code, 0);
    }

    TEST_P(SQLiteExceptionParameterizedTest,
    Should_Store_Expect_Values_When_ConstructedWithParameters)
    {
        SQLiteExceptionParameter parameter =
            GetParam();

        SQLiteException exception(
            parameter.message,
            parameter.error_code,
            parameter.extended_code
        );

        EXPECT_EQ(exception.error_code, parameter.error_code);
        EXPECT_EQ(exception.extended_code, parameter.extended_code);
        EXPECT_STREQ(exception.what(), parameter.message.c_str());
    }

    INSTANTIATE_TEST_CASE_P(
        SQLiteExceptionCases,
        SQLiteExceptionParameterizedTest,
        ::testing::Values(
            SQLiteExceptionParameter{"error", 1, 2},
            SQLiteExceptionParameter{"edge", -1, -2}
        )
    );  
}

#endif
