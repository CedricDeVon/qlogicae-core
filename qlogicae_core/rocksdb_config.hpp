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
        bool create_if_missing = true;
        int max_open_files = -1;
        bool use_fsync = false;
        bool use_direct_reads = true;
        bool use_direct_io_for_flush_and_compaction = true;
        int max_background_flushes = 1;
        int base_max_background_jobs = 4;

        rocksdb::CompactionStyle compaction_style = rocksdb::kCompactionStyleLevel;
        int level0_file_num_compaction_trigger = 10;
        int level0_slowdown_writes_trigger = 20;
        int level0_stop_writes_trigger = 40;

        size_t write_buffer_size = 128 * 1024 * 1024;
        size_t base_write_buffer_size = 64 * 1024 * 1024;
        int max_write_buffer_number = 6;
        int min_write_buffer_number_to_merge = 2;
        size_t target_file_size_base = 64 * 1024 * 1024;
        size_t max_bytes_for_level_base = 512 * 1024 * 1024;
        size_t bytes_per_sync = 1 << 20;
        size_t base_block_cache_size = 64 * 1024 * 1024;

        rocksdb::CompressionType compression = rocksdb::kNoCompression;

        bool write_sync = false;
        bool write_disable_wal = true;

        bool no_block_cache = true;
        int block_restart_interval = 4;
        size_t block_size = 4 * 1024;

        size_t background_threads = 4;
        size_t new_bloom_filter_policy = 10;
    };
}
