#pragma once

namespace QLogicaeCore
{
    struct RocksDBConfig
    {
        size_t block_cache_size = 64 * 1024 * 1024;
        size_t write_buffer_size = 64 * 1024 * 1024;
        int max_background_jobs = 4;
    };
}
