#pragma once

#include "utilities.hpp"

#include <array>           
#include <mutex>           
#include <vector>          
#include <string>          
#include <memory>          
#include <cstddef>         
#include <iostream>        
#include <shared_mutex>    
#include <unordered_set>   

namespace QLogicaeCore
{
    class StringMemoryPoolDiagnostics
    {
    public:
        StringMemoryPoolDiagnostics() = default;

        StringMemoryPoolDiagnostics(const StringMemoryPoolDiagnostics&) = delete;

        StringMemoryPoolDiagnostics& operator=(const StringMemoryPoolDiagnostics&) = delete;

        std::atomic<std::size_t> pool_hits{ 0 };
        std::atomic<std::size_t> bytes_used{ 0 };
        std::atomic<std::size_t> pool_misses{ 0 };
        std::atomic<std::size_t> interned_count{ 0 };

        void reset();
    };
}
