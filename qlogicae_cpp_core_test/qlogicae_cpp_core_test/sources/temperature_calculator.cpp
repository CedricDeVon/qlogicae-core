#include "pch.hpp"

#include "qlogicae_cpp_core/includes/temperature_calculator.hpp"

namespace QLogicaeCppCoreTest
{
    struct ParameterSet
    {
        double input_value;

        QLogicaeCppCore::TemperatureUnitType from_unit;
        QLogicaeCppCore::TemperatureUnitType to_unit;

        double expected;
    };

    class TemperatureCalculatorTest :
        public ::testing::Test,
        public ::testing::WithParamInterface<ParameterSet>
    {
    public:
        QLogicaeCppCore::TemperatureCalculator calculator;

        QLogicaeCppCore::Result<double> result;

        std::mutex mutex_object;

        std::condition_variable condition;

        std::atomic<int> ready_count;

        QLogicaeCppCore::Result<double> shared_result;

        TemperatureCalculatorTest()
        {
            ready_count = 0;
        }
    };

    TEST_F(
        TemperatureCalculatorTest,
        ShouldConvertCelsiusToCelsius
    )
    {
        double input_value = 25.0;

        calculator.convert(
            result,
            input_value,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS
        );

        double output_value = 0.0;

        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, 25.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldConvertCelsiusToFahrenheit
    )
    {
        double input_value = 0.0;

        calculator.convert(
            result,
            input_value,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS,
            QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
        );

        double output_value = 0.0;

        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, 32.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldConvertCelsiusToKelvin
    )
    {
        double input_value = 0.0;

        calculator.convert(
            result,
            input_value,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS,
            QLogicaeCppCore::TemperatureUnitType::KELVIN
        );

        double output_value = 0.0;

        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, 273.15);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldPassthroughWhenFromUnitIsNone
    )
    {
        double input_value = -10.0;

        calculator.convert(
            result,
            input_value,
            QLogicaeCppCore::TemperatureUnitType::NONE,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS
        );

        double output_value = 0.0;

        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, -10.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldPassthroughWhenToUnitIsNone
    )
    {
        double input_value = 10.0;

        calculator.convert(
            result,
            input_value,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS,
            QLogicaeCppCore::TemperatureUnitType::NONE
        );

        double output_value = 0.0;

        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, 10.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldHandleLargeValuesSafely
    )
    {
        double input_value = 1.0e300;

        ASSERT_NO_THROW(
            calculator.convert(
                result,
                input_value,
                QLogicaeCppCore::TemperatureUnitType::CELSIUS,
                QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
            )
        );
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldHandleSmallValuesSafely
    )
    {
        double input_value = 1.0e-300;

        ASSERT_NO_THROW(
            calculator.convert(
                result,
                input_value,
                QLogicaeCppCore::TemperatureUnitType::KELVIN,
                QLogicaeCppCore::TemperatureUnitType::CELSIUS
            )
        );
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldHandleInvalidEnum
    )
    {
        double input_value = 5.0;

        auto invalid_unit = static_cast<QLogicaeCppCore::TemperatureUnitType>(255);

        calculator.convert(
            result,
            input_value,
            invalid_unit,
            invalid_unit
        );

        double output_value = 0.0;

        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, 5.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldWorkWithAsyncFuture
    )
    {
        double input_value = 100.0;

        auto future_object = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<double> local_result;

                calculator.convert(
                    local_result,
                    input_value,
                    QLogicaeCppCore::TemperatureUnitType::CELSIUS,
                    QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
                );

                double value = 0.0;

                local_result.get_value(value);

                return value;
            }
        );

        double output = future_object.get();

        ASSERT_DOUBLE_EQ(output, 212.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldWorkWithPromise
    )
    {
        std::promise<double> promise_object;

        std::future<double> future_object = promise_object.get_future();

        std::thread worker(
            [&]()
            {
                QLogicaeCppCore::Result<double> local_result;

                calculator.convert(
                    local_result,
                    0.0,
                    QLogicaeCppCore::TemperatureUnitType::CELSIUS,
                    QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
                );

                double value = 0.0;

                local_result.get_value(value);

                promise_object.set_value(value);
            }
        );

        worker.join();

        double output = future_object.get();

        ASSERT_DOUBLE_EQ(output, 32.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldWorkWithMultipleThreads
    )
    {
        std::vector<std::thread> threads;

        int thread_count = 16;

        for (int index = 0; index < thread_count; index++)
        {
            threads.emplace_back(
                [&]()
                {
                    QLogicaeCppCore::Result<double> local_result;

                    calculator.convert(
                        local_result,
                        0.0,
                        QLogicaeCppCore::TemperatureUnitType::CELSIUS,
                        QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
                    );

                    {
                        std::lock_guard<std::mutex> guard(mutex_object);

                        shared_result = local_result;

                        ready_count++;
                    }

                    condition.notify_one();
                }
            );
        }

        {
            std::unique_lock<std::mutex> lock(mutex_object);

            condition.wait(
                lock,
                [&]()
                {
                    return ready_count.load() == thread_count;
                }
            );
        }

        for (auto& thread_item : threads)
        {
            thread_item.join();
        }

        double output_value = 0.0;

        shared_result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, 32.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldHandleHighIterations
    )
    {
        int iteration_count = 10000;

        for (int index = 0; index < iteration_count; index++)
        {
            calculator.convert(
                result,
                static_cast<double>(index),
                QLogicaeCppCore::TemperatureUnitType::CELSIUS,
                QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
            );
        }

        double value = 0.0;

        result.get_value(value);

        ASSERT_TRUE(value > 0.0);
    }

    TEST_P(
        TemperatureCalculatorTest,
        ShouldConvertAccordingToParameters
    )
    {
        auto data = GetParam();

        calculator.convert(
            result,
            data.input_value,
            data.from_unit,
            data.to_unit
        );

        double output = 0.0;

        result.get_value(output);

        ASSERT_NEAR(output, data.expected, 1e-6);
    }

    std::vector<ParameterSet> parameter_data =
    {
        {0.0, QLogicaeCppCore::TemperatureUnitType::CELSIUS,
            QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT, 32.0},
        {0.0, QLogicaeCppCore::TemperatureUnitType::CELSIUS,
            QLogicaeCppCore::TemperatureUnitType::KELVIN, 273.15},
        {32.0, QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS, 0.0}
    };

    INSTANTIATE_TEST_CASE_P(
        TemperatureParameters,
        TemperatureCalculatorTest,
        ::testing::ValuesIn(parameter_data)
    );

    TEST_F(
        TemperatureCalculatorTest,
        ShouldConvertKelvinToCelsius
    )
    {
        double input_value = 273.15;

        calculator.convert(
            result,
            input_value,
            QLogicaeCppCore::TemperatureUnitType::KELVIN,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS
        );

        double output_value = 0.0;
        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, 0.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldConvertKelvinToFahrenheit
    )
    {
        double input_value = 273.15;

        calculator.convert(
            result,
            input_value,
            QLogicaeCppCore::TemperatureUnitType::KELVIN,
            QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
        );

        double output_value = 0.0;
        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, 32.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldConvertFahrenheitToKelvin
    )
    {
        double input_value = 32.0;

        calculator.convert(
            result,
            input_value,
            QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT,
            QLogicaeCppCore::TemperatureUnitType::KELVIN
        );

        double output_value = 0.0;
        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, 273.15);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldHandleNaNInput
    )
    {
        double input_value = std::numeric_limits<double>::quiet_NaN();

        calculator.convert(
            result,
            input_value,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS,
            QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
        );

        double output_value = 0.0;
        result.get_value(output_value);

        ASSERT_TRUE(std::isnan(output_value));
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldHandlePositiveInfinity
    )
    {
        double input_value = std::numeric_limits<double>::infinity();

        ASSERT_NO_THROW(
            calculator.convert(
                result,
                input_value,
                QLogicaeCppCore::TemperatureUnitType::CELSIUS,
                QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
            )
        );
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldHandleNegativeInfinity
    )
    {
        double input_value = -std::numeric_limits<double>::infinity();

        ASSERT_NO_THROW(
            calculator.convert(
                result,
                input_value,
                QLogicaeCppCore::TemperatureUnitType::KELVIN,
                QLogicaeCppCore::TemperatureUnitType::CELSIUS
            )
        );
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldHandleNegativeKelvin
    )
    {
        double input_value = -10.0;

        calculator.convert(
            result,
            input_value,
            QLogicaeCppCore::TemperatureUnitType::KELVIN,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS
        );

        double output_value = 0.0;
        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, -283.15);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldAllowSequentialConversionsWithoutReset
    )
    {
        calculator.convert(
            result,
            0.0,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS,
            QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
        );

        calculator.convert(
            result,
            100.0,
            QLogicaeCppCore::TemperatureUnitType::CELSIUS,
            QLogicaeCppCore::TemperatureUnitType::FAHRENHEIT
        );

        double output_value = 0.0;
        result.get_value(output_value);

        ASSERT_DOUBLE_EQ(output_value, 212.0);
    }

    TEST_F(
        TemperatureCalculatorTest,
        ShouldReturnPassthroughForUnsetResult
    )
    {
        QLogicaeCppCore::Result<double> unset_result;

        double output_value = 0.0;

        ASSERT_NO_THROW(
            unset_result.get_value(output_value)
        );
    }
}
