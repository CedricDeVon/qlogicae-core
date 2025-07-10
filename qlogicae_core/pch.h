#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00 
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#define WIN32_LEAN_AND_MEAN
#include <boost/asio.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/asio/steady_timer.hpp>

#define NOMINMAX

#include <any>
#include <map>
#include <mutex>
#include <ctime>
#include <regex>
#include <queue>
#include <tuple>
#include <vector>
#include <thread>
#include <future>
#include <string>
#include <memory>
#include <chrono>
#include <limits>
#include <format>
#include <random>
#include <variant>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdint>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <typeindex>
#include <optional>
#include <windows.h>
#include <algorithm>
#include <functional>
#include <shellapi.h>
#include <filesystem>
#include <type_traits>
#include <string_view>
#include <shared_mutex>
#include <unordered_map>
#include <unordered_set>
#include <condition_variable>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
#include <argon2.h>
#include <fmt/os.h>
#include <sodium.h>
#include <fast_io.h>
#include <date/tz.h>
#include <rapidcsv.h>
#include <date/date.h>
#include <fmt/format.h>
#include <toml++/toml.h>
#include <stduuid/uuid.h>
#include <fast_io_device.h>
#include <fast_io_legacy.h>
#include <rapidjson/writer.h>
#include <rapidjson/pointer.h>
#include <rapidjson/document.h>
#include <rapidjson/allocators.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>

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

#include <absl/strings/str_split.h>

#include "framework.h"

#include "globals.hpp"
