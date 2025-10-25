#pragma once

namespace QLogicaeCore
{
    class Cryptographer
    {
    public:
        Cryptographer();

        ~Cryptographer();

        Cryptographer(
            const Cryptographer& instance
        ) = delete;

        Cryptographer(
            Cryptographer&& instance
        ) noexcept = delete;

        Cryptographer& operator = (
            Cryptographer&& instance
        ) = delete;

        Cryptographer& operator = (
            const Cryptographer& instance
        ) = delete;

    protected:
        mutable std::shared_mutex _mutex;
    };
}