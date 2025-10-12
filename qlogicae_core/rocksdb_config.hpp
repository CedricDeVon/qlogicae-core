#pragma once

#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/table.h>
#include <rocksdb/options.h>
#include <rocksdb/iterator.h>
#include <rocksdb/listener.h>
#include <rocksdb/convenience.h>
#include <rocksdb/write_batch.h>
#include <rocksdb/filter_policy.h>
#include <rocksdb/compaction_filter.h>
#include <rocksdb/utilities/checkpoint.h>
#include <rocksdb/utilities/backup_engine.h>
#include <rocksdb/utilities/transaction_db.h>

namespace QLogicaeCore
{
    struct RocksDBConfig
    {
        size_t block_cache_size = 64 * 1024 * 1024;
        size_t write_buffer_size = 64 * 1024 * 1024;
        int max_background_jobs = 4;
    };
}
