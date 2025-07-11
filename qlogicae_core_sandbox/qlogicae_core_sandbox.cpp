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

