#pragma once

#include "../includes/assembly.hpp"

// System
#include "../includes/system_access.hpp"

// Results
#include "../includes/result_status.hpp"
#include "../includes/result.hpp"
#include "../includes/abstract_result.hpp"
#include "../includes/bad_result.hpp"
#include "../includes/good_result.hpp"

// Core Utilities
#include "../includes/globals.hpp"
#include "../includes/utf.hpp"
#include "../includes/json.hpp"
#include "../includes/byte_size.hpp"
#include "../includes/log_level.hpp"
#include "../includes/time_zone.hpp"
#include "../includes/file_mode.hpp"
#include "../includes/time_delay.hpp"
#include "../includes/json_value.hpp"
#include "../includes/log_medium.hpp"
#include "../includes/time_format.hpp"
#include "../includes/worker_queue.hpp"
#include "../includes/json_visitor.hpp"
#include "../includes/encoding_type.hpp"
#include "../includes/task_priority.hpp"
#include "../includes/json_value_type.hpp"
#include "../includes/case_aware_hash.hpp"
#include "../includes/time_scale_unit.hpp"
#include "../includes/case_sensitivity.hpp"
#include "../includes/case_aware_equal.hpp"
#include "../includes/small_task_object.hpp"
#include "../includes/vector_string_hash.hpp"
#include "../includes/json_value_pointer.hpp"
#include "../includes/vector_string_equal.hpp"
#include "../includes/environment_variable.hpp"
#include "../includes/cache_configurations.hpp"
#include "../includes/network_ping_response.hpp"
#include "../includes/network_ping_settings.hpp"
#include "../includes/temperature_unit_type.hpp"
#include "../includes/rocksdb_configurations.hpp"
#include "../includes/supported_qlogicae_ide.hpp"
#include "../includes/outlier_removal_options.hpp"
#include "../includes/cryptographer_properties.hpp"
#include "../includes/validation_password_rules.hpp"
#include "../includes/windows_registry_root_path.hpp"
#include "../includes/jsonwebtoken_reverse_input.hpp"
#include "../includes/string_memory_pool_snapshot.hpp"
#include "../includes/jsonwebtoken_reverse_result.hpp"
#include "../includes/supported_qlogicae_installer.hpp"
#include "../includes/jsonwebtoken_transform_input.hpp"
#include "../includes/value_enum_key_delete_handler.hpp"
#include "../includes/groq_cloud_client_api_request.hpp"
#include "../includes/groq_cloud_client_api_response.hpp"
#include "../includes/qlogicae_visual_studio_2022_build.hpp"
#include "../includes/groq_cloud_client_api_chat_message.hpp"
#include "../includes/groq_cloud_client_api_prompt_configurations.hpp"
#include "../includes/qlogicae_visual_studio_2022_build_architecture.hpp"
#include "../includes/utilities.hpp"

// Asynchronous
#include "../includes/thread_pool.hpp"
#include "../includes/event_dispatcher.hpp"

// Input / Output
#include "../includes/abstract_file_io.hpp"
#include "../includes/cli_io.hpp"
#include "../includes/file_ios.hpp"
#include "../includes/csv_file_io.hpp"
#include "../includes/file_uri_io.hpp"
#include "../includes/xml_file_io.hpp"
#include "../includes/toml_file_io.hpp"
#include "../includes/json_file_io.hpp"
#include "../includes/text_file_io.hpp"
#include "../includes/binary_file_io.hpp"

// Logger
#include "../includes/logger.hpp"

// Time
#include "../includes/time.hpp"
#include "../includes/timeout.hpp"
#include "../includes/interval.hpp"

// String Memory Pool
#include "../includes/string_memory_pool.hpp"
#include "../includes/string_memory_pool_diagnostics.hpp"
#include "../includes/string_memory_pool_character_pool.hpp"
#include "../includes/string_memory_pool_character_pool_block.hpp"

// Strings
#include "../includes/encoder.hpp"
#include "../includes/transformer.hpp"
#include "../includes/string_builder.hpp"
#include "../includes/regular_expression.hpp"

// Cryptographers
#include "../includes/cryptographer.hpp"
#include "../includes/bcrypt_hash_cryptographer.hpp"
#include "../includes/sha256_hash_cryptographer.hpp"
#include "../includes/jsonwebtoken_cryptographer.hpp"
#include "../includes/aes256_cipher_cryptographer.hpp"
#include "../includes/argon2id_hash_cryptographer.hpp"
#include "../includes/aes256_signature_cryptographer.hpp"
#include "../includes/xchacha20_poly1305_cipher_cryptographer.hpp"

// Mathematics
#include "../includes/statistician.hpp"

// Networks
#include "../includes/network_ping.hpp"

// Environment Variables
#include "../includes/dot_env.hpp"

// Windows Registry
#include "../includes/windows_registry.hpp"

// Miscellaneous
#include "../includes/generator.hpp"
#include "../includes/validators.hpp"
#include "../includes/temperature.hpp"

// Value Extractors
#include "../includes/placeholder_value_extractor.hpp"
#include "../includes/dot_env_value_extractor.hpp"
#include "../includes/windows_registry_value_extractor.hpp"

// Sqlite
#include "../includes/sqlite.hpp"
#include "../includes/sqlite_backend.hpp"
#include "../includes/sqlite_exception.hpp"
#include "../includes/sqlite_statement_data.hpp"
#include "../includes/sqlite_row.hpp"
#include "../includes/sqlite_database.hpp"
#include "../includes/sqlite_statement.hpp"
#include "../includes/sqlite_transaction.hpp"

// Gmail
#include "../includes/gmail_mailer.hpp"

// RocksDB
#include "../includes/rocksdb_database.hpp"

// Boost Interprocess Cache
#include "../includes/boost_interprocess_cache_shared_data.hpp"
#include "../includes/boost_interprocess_cache.hpp"

// QLogicae Application
#include "../includes/application.hpp"
#include "../includes/application_cache.hpp"
#include "../includes/application_logger.hpp"
#include "../includes/application_file_io.hpp"
#include "../includes/application_language.hpp"
#include "../includes/abstract_application.hpp"
#include "../includes/application_utilities.hpp"
#include "../includes/application_cryptographer.hpp"
#include "../includes/application_startup_inputs.hpp"
#include "../includes/application_windows_registry.hpp"

namespace QLogicaeCore
{

}
