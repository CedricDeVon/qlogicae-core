#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Results \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
    class ResultsTest: public ::testing::Test
    {
    public:
        ResultsTest()
        {
        }

    protected:
        Results<std::string> result_string_instance;
        Results<void> result_void_instance;
    };

    class ResultsStringParamTest: public ::testing::TestWithParam<std::string>
    {
    public:
        ResultsStringParamTest()
        {
        }

    protected:
        Results<std::string> parameter_result;
    };

    class ThrowOnCopy
    {
    public:
        ThrowOnCopy()
        {
        }
        ThrowOnCopy(const ThrowOnCopy&)
        {
            throw std::runtime_error("copy_failure");
        }
        ThrowOnCopy(ThrowOnCopy&&) noexcept = default;
        ThrowOnCopy& operator=(const ThrowOnCopy&) = default;
        ThrowOnCopy& operator=(ThrowOnCopy&&) noexcept = default;
        bool operator==(const ThrowOnCopy&) const
        {
            return true;
        }
    };

    class ThrowOnMove
    {
    public:
        ThrowOnMove()
        {
        }
        ThrowOnMove(const ThrowOnMove&) = default;
        ThrowOnMove(ThrowOnMove&&)
        {
            throw std::runtime_error("move_failure");
        }
        ThrowOnMove& operator=(const ThrowOnMove&) = default;
        ThrowOnMove& operator=(ThrowOnMove&&)
        {
            throw std::runtime_error("move_assign_failure");
        }
        bool operator==(const ThrowOnMove&) const
        {
            return true;
        }
    };

    struct NonCopyNonMove {
        NonCopyNonMove() = default;
        NonCopyNonMove(const NonCopyNonMove&) = delete;
        NonCopyNonMove(NonCopyNonMove&&) = delete;
    };

    static_assert(!std::is_copy_constructible_v<NonCopyNonMove>);
    static_assert(!std::is_move_constructible_v<NonCopyNonMove>);
}

#endif
