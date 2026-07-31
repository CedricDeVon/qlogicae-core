#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RocksDbDatabaseManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		RocksDbDatabaseManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<RocksDbDatabaseManagerConfigurations>
    {
	public:
		std::string
			file_path =
				"data.db";

		bool
			is_feature_thread_safety_handling_enabled =
				true;

		bool
			create_if_missing =
				true;

		int
			max_open_files =
				-1;

		bool
			use_fsync =
				false;

		bool
			use_direct_reads =
				true;

		bool
			use_direct_io_for_flush_and_compaction =
				true;

		int
			max_background_flushes =
				1;

		int
			base_max_background_jobs =
				4;

		rocksdb::CompactionStyle
			compaction_style =
				rocksdb::kCompactionStyleLevel;

		int
			level0_file_num_compaction_trigger =
				10;

		int
			level0_slowdown_writes_trigger =
				20;

		int
			level0_stop_writes_trigger =
				40;

		size_t
			write_buffer_size =
				128 * 1024 * 1024;

		size_t
			base_write_buffer_size =
				64 * 1024 * 1024;

		int
			max_write_buffer_number =
				6;

		int
			min_write_buffer_number_to_merge =
				2;

		size_t
			target_file_size_base =
				64 * 1024 * 1024;

		size_t
			max_bytes_for_level_base =
				512 * 1024 * 1024;

		size_t
			bytes_per_sync =
				1 << 20;

		size_t
			base_block_cache_size =
				64 * 1024 * 1024;

		rocksdb::CompressionType
			compression =
				rocksdb::kNoCompression;

		bool
			write_sync =
				false;

		bool
			write_disable_wal =
				true;

		bool
			no_block_cache =
				true;

		int
			block_restart_interval =
				4;

		size_t
			block_size =
				4 * 1024;

		size_t
			background_threads =
				4;

		double
			new_bloom_filter_policy =
				10;

		RocksDbDatabaseManagerConfigurations();
    };
}

#endif
