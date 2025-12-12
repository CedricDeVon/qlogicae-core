#include "pch.hpp"

#include "../includes/time_delay_clock.hpp"

namespace QLogicaeCppCore
{
    TimeDelayClock::TimeDelayClock()
    {
        Result<bool> result;

        construct(result);
    }

    TimeDelayClock::~TimeDelayClock()
    {
        Result<bool> result;

        destruct(result);
    }

    void TimeDelayClock::construct(
        Result<bool>& result
    )
    {
        cycles_per_microsecond = 0.0;

        result.set_to_good_status_with_value(
            true
        );
    }

    void TimeDelayClock::destruct(
        Result<bool>& result
    )
    {        
        result.set_to_good_status_with_value(
            true
        );
    }

    void TimeDelayClock::calibrate(
        Result<bool>& result
    )
    {
        static std::atomic<bool> calibrated = false;
        static std::atomic<double> cached_frequency = 0.0;

        if (calibrated.load())
        {
            cycles_per_microsecond = cached_frequency;
            result.set_to_good_status_with_value(
                true
            );

            return;
        }

        LARGE_INTEGER frequency;
        LARGE_INTEGER start;
        LARGE_INTEGER end;

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        unsigned long long tsc_start = __rdtsc();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        unsigned long long tsc_end = __rdtsc();

        QueryPerformanceCounter(&end);

        const double elapsed_seconds =
            static_cast<double>(end.QuadPart - start.QuadPart) /
            static_cast<double>(frequency.QuadPart);

        const double cpu_frequency_hz =
            (tsc_end - tsc_start) / elapsed_seconds;

        cycles_per_microsecond = cpu_frequency_hz / 1'000'000.0;
        cached_frequency = cycles_per_microsecond;
        calibrated.store(true);

        result.set_to_good_status_with_value(
            true
        );
    }

    void TimeDelayClock::query_performance_counter(
        Result<bool>& result,
        const double& microseconds
    )
    {
        if (microseconds <= 0.0 || microseconds > 1e12)
        {
            result.set_to_bad_status_with_value(
                false
            );

            return;
        }

        LARGE_INTEGER frequency;
        LARGE_INTEGER start;
        LARGE_INTEGER current;

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        double elapsed = 0.0;

        do
        {
            QueryPerformanceCounter(&current);
            elapsed = (current.QuadPart - start.QuadPart) *
                1'000'000.0 / frequency.QuadPart;
        } while (elapsed < microseconds);

        result.set_to_good_status_with_value(
            true
        );
    }

    void TimeDelayClock::real_time_stamp_counter(
        Result<bool>& result,
        const double& microseconds
    )
    {
        if (microseconds <= 0.0 || microseconds > 1e12)
        {
            result.set_to_bad_status_with_value(
                false
            );

            return;
        }

        if (cycles_per_microsecond == 0.0)
        {
            calibrate(result);
        }

        unsigned __int64 start = __rdtsc();
        unsigned __int64 target =
            static_cast<unsigned __int64>(
                microseconds * cycles_per_microsecond);

        while ((__rdtsc() - start) < target)
        {
            _mm_pause();
        }

        result.set_to_good_status_with_value(
            true
        );
    }

    void TimeDelayClock::in_nanoseconds(
        Result<bool>& result,
        const double& value
    )
    {
        in_microseconds(result, value / 1'000.0);
    }

    void TimeDelayClock::in_microseconds(
        Result<bool>& result,
        const double& value
    )
    {
        if (value <= 0.0 || value > 1e12)
        {
            result.set_to_bad_status_with_value(
                false
            );

            return;
        }

        LARGE_INTEGER frequency;
        LARGE_INTEGER start;
        LARGE_INTEGER current;

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        double elapsed = 0.0;
        while (elapsed < value)
        {
            QueryPerformanceCounter(&current);
            elapsed = static_cast<double>(
                current.QuadPart - start.QuadPart
                ) * 1'000'000.0 / static_cast<double>(frequency.QuadPart);
        }

        result.set_to_good_status_with_value(
            true
        );
    }

    void TimeDelayClock::in_milliseconds(
        Result<bool>& result,
        const double& value
    )
    {
        in_microseconds(result, value * 1'000.0);
    }

    void TimeDelayClock::in_seconds(
        Result<bool>& result,
        const double& value
    )
    {
        in_microseconds(result, value * 1'000'000.0);
    }

    void TimeDelayClock::in_minutes(
        Result<bool>& result,
        const double& value
    )
    {
        in_seconds(result, value * 60.0);
    }

    void TimeDelayClock::in_hours(
        Result<bool>& result,
        const double& value
    )
    {
        in_minutes(result, value * 60.0);
    }

    void TimeDelayClock::in_days(
        Result<bool>& result,
        const double& value
    )
    {
        in_hours(result, value * 24.0);
    }

    void TimeDelayClock::in_months(
        Result<bool>& result,
        const double& value
    )
    {
        in_days(result, value * 30.44);
    }

    void TimeDelayClock::in_years(
        Result<bool>& result,
        const double& value
    )
    {
        in_days(result, value * 365.25);
    }
}
