#pragma once

#include "pch.h"

using namespace QLogicaeCore;

int main() {
    StringMemoryPool<> pool(CaseSensitivity::INSENSITIVE);

    std::string_view input1 = "Hello";
    std::string_view input2 = "hello";
    std::string_view input3 = "WORLD";

    const std::string* interned1 = pool.get_internal(input1);
    const std::string* interned2 = pool.get_internal(input2);
    const std::string* interned3 = pool.get_internal(input3);

    std::cout << "interned1: " << *interned1 << ", address: " << static_cast<const void*>(interned1->data()) << "\n";
    std::cout << "interned2: " << *interned2 << ", address: " << static_cast<const void*>(interned2->data()) << "\n";
    std::cout << "interned3: " << *interned3 << ", address: " << static_cast<const void*>(interned3->data()) << "\n";

    std::cout << "\nSame pointer for input1 and input2? "
        << (interned1 == interned2 ? "YES" : "NO") << "\n";

    // Async example
    auto future = pool.get_internal_async("WORLD");
    const std::string* async_result = future.get();
    std::cout << "Async interned: " << *async_result << ", address: " << static_cast<const void*>(async_result->data()) << "\n";

    // Show diagnostics
    auto snapshot = pool.get_diagnostics_snapshot();
    std::cout << "\n--- Diagnostics ---\n"
        << "Hits: " << snapshot.pool_hits << "\n"
        << "Misses: " << snapshot.pool_misses << "\n"
        << "Interned Count: " << snapshot.interned_count << "\n"
        << "Bytes Used: " << snapshot.bytes_used << "\n";

    return 0;
}


/*



Write C++ Gtest test cases.

Follow these additional requirements:
- Use only C++20 features.
- One file per tested class
- Use 'INSTANTIATE_TEST_CASE_P'
- Comprehensive Asynchrnonous testing
- Comprehensive Multithreading testing
- Comprehensive Stress Tests
- Comprehensive Throwing Exceptions testing
- Comprehensive Edge Case testing
- Comprehensive Parameterized Tests for all tests
- Comprehensive Performance Testing (2 seconds)

Follow these code styling rules:
- Always follow 80 characters per line.
- If tests exist, Test Suite Name Format: [ClassName][Test].
- If tests exist, Test Name Format: [Should]_[Expect]_[When].
- Avoid Comments at all times.
- Avoid using declared namespaces.
- Avoid using the 'using' c++ keyword.
- Always use full names for variables. Make sure to use no abbreviations.
- Make sure that loop, method opening and closing brackets must follow C# styling
- Write your code in chat

Re-evaluate if test suite is comprehensive and complete



*/
