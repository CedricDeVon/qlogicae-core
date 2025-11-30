#pragma once

#include "qlogicae_core/includes/assembly.hpp"

// System
#include "qlogicae_core/includes/system_access.hpp"

// Results
#include "qlogicae_core/includes/result_status.hpp"
#include "qlogicae_core/includes/result.hpp"
#include "qlogicae_core/includes/abstract_result.hpp"
#include "qlogicae_core/includes/bad_result.hpp"
#include "qlogicae_core/includes/good_result.hpp"

// Core Utilities
#include "qlogicae_core/includes/globals.hpp"
#include "qlogicae_core/includes/utf.hpp"
#include "qlogicae_core/includes/json.hpp"
#include "qlogicae_core/includes/byte_size.hpp"
#include "qlogicae_core/includes/log_level.hpp"
#include "qlogicae_core/includes/time_zone.hpp"
#include "qlogicae_core/includes/file_mode.hpp"
#include "qlogicae_core/includes/time_delay.hpp"
#include "qlogicae_core/includes/json_value.hpp"
#include "qlogicae_core/includes/log_medium.hpp"
#include "qlogicae_core/includes/time_format.hpp"
#include "qlogicae_core/includes/worker_queue.hpp"
#include "qlogicae_core/includes/json_visitor.hpp"
#include "qlogicae_core/includes/encoding_type.hpp"
#include "qlogicae_core/includes/task_priority.hpp"
#include "qlogicae_core/includes/json_value_type.hpp"
#include "qlogicae_core/includes/case_aware_hash.hpp"
#include "qlogicae_core/includes/time_scale_unit.hpp"
#include "qlogicae_core/includes/case_sensitivity.hpp"
#include "qlogicae_core/includes/case_aware_equal.hpp"
#include "qlogicae_core/includes/small_task_object.hpp"
#include "qlogicae_core/includes/vector_string_hash.hpp"
#include "qlogicae_core/includes/json_value_pointer.hpp"
#include "qlogicae_core/includes/vector_string_equal.hpp"
#include "qlogicae_core/includes/environment_variable.hpp"
#include "qlogicae_core/includes/cache_configurations.hpp"
#include "qlogicae_core/includes/network_ping_response.hpp"
#include "qlogicae_core/includes/network_ping_settings.hpp"
#include "qlogicae_core/includes/temperature_unit_type.hpp"
#include "qlogicae_core/includes/rocksdb_configurations.hpp"
#include "qlogicae_core/includes/supported_qlogicae_ide.hpp"
#include "qlogicae_core/includes/outlier_removal_options.hpp"
#include "qlogicae_core/includes/cryptographer_properties.hpp"
#include "qlogicae_core/includes/validation_password_rules.hpp"
#include "qlogicae_core/includes/windows_registry_root_path.hpp"
#include "qlogicae_core/includes/jsonwebtoken_reverse_input.hpp"
#include "qlogicae_core/includes/string_memory_pool_snapshot.hpp"
#include "qlogicae_core/includes/jsonwebtoken_reverse_result.hpp"
#include "qlogicae_core/includes/supported_qlogicae_installer.hpp"
#include "qlogicae_core/includes/jsonwebtoken_transform_input.hpp"
#include "qlogicae_core/includes/value_enum_key_delete_handler.hpp"
#include "qlogicae_core/includes/groq_cloud_client_api_request.hpp"
#include "qlogicae_core/includes/groq_cloud_client_api_response.hpp"
#include "qlogicae_core/includes/qlogicae_visual_studio_2022_build.hpp"
#include "qlogicae_core/includes/groq_cloud_client_api_chat_message.hpp"
#include "qlogicae_core/includes/groq_cloud_client_api_prompt_configurations.hpp"
#include "qlogicae_core/includes/qlogicae_visual_studio_2022_build_architecture.hpp"
#include "qlogicae_core/includes/utilities.hpp"

// Asynchronous
#include "qlogicae_core/includes/thread_pool.hpp"
#include "qlogicae_core/includes/event_dispatcher.hpp"

// Input / Output
#include "qlogicae_core/includes/abstract_file_io.hpp"
#include "qlogicae_core/includes/cli_io.hpp"
#include "qlogicae_core/includes/file_ios.hpp"
#include "qlogicae_core/includes/csv_file_io.hpp"
#include "qlogicae_core/includes/file_uri_io.hpp"
#include "qlogicae_core/includes/xml_file_io.hpp"
#include "qlogicae_core/includes/toml_file_io.hpp"
#include "qlogicae_core/includes/json_file_io.hpp"
#include "qlogicae_core/includes/text_file_io.hpp"
#include "qlogicae_core/includes/binary_file_io.hpp"

// Logger
#include "qlogicae_core/includes/logger.hpp"

// Time
#include "qlogicae_core/includes/time.hpp"
#include "qlogicae_core/includes/timeout.hpp"
#include "qlogicae_core/includes/interval.hpp"

// File System
#include "qlogicae_core/includes/file_system.hpp"

// String Memory Pool
#include "qlogicae_core/includes/string_memory_pool.hpp"
#include "qlogicae_core/includes/string_memory_pool_diagnostics.hpp"
#include "qlogicae_core/includes/string_memory_pool_character_pool.hpp"
#include "qlogicae_core/includes/string_memory_pool_character_pool_block.hpp"

// Strings
#include "qlogicae_core/includes/encoder.hpp"
#include "qlogicae_core/includes/transformer.hpp"
#include "qlogicae_core/includes/string_builder.hpp"
#include "qlogicae_core/includes/regular_expression.hpp"

// Cryptographers
#include "qlogicae_core/includes/cryptographer.hpp"
#include "qlogicae_core/includes/bcrypt_hash_cryptographer.hpp"
#include "qlogicae_core/includes/sha256_hash_cryptographer.hpp"
#include "qlogicae_core/includes/jsonwebtoken_cryptographer.hpp"
#include "qlogicae_core/includes/aes256_cipher_cryptographer.hpp"
#include "qlogicae_core/includes/argon2id_hash_cryptographer.hpp"
#include "qlogicae_core/includes/aes256_signature_cryptographer.hpp"
#include "qlogicae_core/includes/xchacha20_poly1305_cipher_cryptographer.hpp"

// Mathematics
#include "qlogicae_core/includes/statistician.hpp"

// Networks
#include "qlogicae_core/includes/network_ping.hpp"

// Environment Variables
#include "qlogicae_core/includes/dot_env.hpp"

// Windows Registry
#include "qlogicae_core/includes/windows_registry.hpp"

// Miscellaneous
#include "qlogicae_core/includes/generator.hpp"
#include "qlogicae_core/includes/validators.hpp"
#include "qlogicae_core/includes/temperature.hpp"

// Value Extractors
#include "qlogicae_core/includes/placeholder_value_extractor.hpp"
#include "qlogicae_core/includes/dot_env_value_extractor.hpp"
#include "qlogicae_core/includes/windows_registry_value_extractor.hpp"

// Sqlite
#include "qlogicae_core/includes/sqlite.hpp"
#include "qlogicae_core/includes/sqlite_backend.hpp"
#include "qlogicae_core/includes/sqlite_exception.hpp"
#include "qlogicae_core/includes/sqlite_statement_data.hpp"
#include "qlogicae_core/includes/sqlite_row.hpp"
#include "qlogicae_core/includes/sqlite_database.hpp"
#include "qlogicae_core/includes/sqlite_statement.hpp"
#include "qlogicae_core/includes/sqlite_transaction.hpp"

// Gmail
#include "qlogicae_core/includes/gmail_mailer.hpp"

// RocksDB
#include "qlogicae_core/includes/rocksdb_database.hpp"

// Boost Interprocess Cache
#include "qlogicae_core/includes/boost_interprocess_cache_shared_data.hpp"
#include "qlogicae_core/includes/boost_interprocess_cache.hpp"

// QLogicae Application
#include "qlogicae_core/includes/application.hpp"
#include "qlogicae_core/includes/application_cache.hpp"
#include "qlogicae_core/includes/application_logger.hpp"
#include "qlogicae_core/includes/application_file_io.hpp"
#include "qlogicae_core/includes/application_language.hpp"
#include "qlogicae_core/includes/abstract_application.hpp"
#include "qlogicae_core/includes/application_utilities.hpp"
#include "qlogicae_core/includes/application_cryptographer.hpp"
#include "qlogicae_core/includes/application_startup_inputs.hpp"
#include "qlogicae_core/includes/application_windows_registry.hpp"

namespace QLogicaeCore
{

}
