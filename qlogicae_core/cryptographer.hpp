#pragma once

namespace QLogicaeCore
{
    class Cryptographer
    {
    public:
        Cryptographer() = default;

        ~Cryptographer() = default;

        Cryptographer(
            const Cryptographer& cryptographer
        ) = delete;

        Cryptographer(
            Cryptographer&& cryptographer
        ) noexcept = delete;

        Cryptographer& operator = (
            Cryptographer&& cryptographer
        ) = delete;

        Cryptographer& operator = (
            const Cryptographer& cryptographer
        ) = delete;

    protected:
        mutable std::shared_mutex _mutex;
    };
}
