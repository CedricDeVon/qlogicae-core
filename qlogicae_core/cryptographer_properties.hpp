#pragma once

namespace QLogicaeCore
{
    struct CryptographerProperties
    {
        size_t size_t_1 = 0;
        
        size_t size_t_2 = 0;
        
        size_t size_t_3 = 0;
        
        size_t size_t_4 = 0;
        
        uint32_t uint32_t_1 = 0;
        
        uint32_t uint32_t_2 = 0;
        
        uint32_t uint32_t_3 = 0;
        
        uint32_t uint32_t_4 = 0;
    };

    static CryptographerProperties
        default_cryptographer_3_properties
    {
        .size_t_1 = 32,
        
        .size_t_2 = 16,
        
        .uint32_t_1 = 3,
        
        .uint32_t_2 = 1 << 16,
        
        .uint32_t_3 = 2
    };
}
