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
    struct CharacterPoolBlock
    {
        std::unique_ptr<char[]> data;
        
        std::size_t size;

        CharacterPoolBlock* next;

        explicit CharacterPoolBlock(std::size_t sz)
            :
                data(new char[sz]),
                size(sz),
                next(nullptr)
        {
        
        }
    };
}
