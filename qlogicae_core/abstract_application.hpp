#pragma once

#include "result.hpp"

#include <mutex>

namespace QLogicaeCore
{
    class AbstractApplication
    {
    public:
        bool get_is_enabled();

        void get_is_enabled(
            Result<void>& result
        );

        void set_is_enabled(
            const bool& value
        );

        void set_is_enabled(
            Result<void>& result,
            const bool& value
        );

    protected:
        AbstractApplication();

        ~AbstractApplication();

        AbstractApplication(
            const AbstractApplication& instance
        ) = default;

        AbstractApplication(
            AbstractApplication&& instance
        ) noexcept = delete;

        AbstractApplication& operator = (
            AbstractApplication&& instance
        ) = default;

        AbstractApplication& operator = (
            const AbstractApplication& instance
        ) = delete;

        bool _is_enabled;

        std::mutex _mutex;
    };
}
