#pragma once

#include "framework.hpp"

#include <WinSock2.h>
#include <windows.h>
#include <shlobj.h>
#include <shellapi.h>
#include <boost/asio.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/container/flat_map.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

#include <pcre2.h>
#include <argon2.h>
#include <fmt/os.h>
#include <sodium.h>
#include <sqlite3.h>
#include <fast_io.h>
#include <date/tz.h>
#include <cpr/cpr.h>
#include <rapidcsv.h>
#include <fmt/core.h>
#include <utf8proc.h> 
#include <curl/curl.h>
#include <pugixml.hpp>
#include <nanobench.h>
#include <date/date.h>
#include <fmt/format.h>
#include <fmt/compile.h>
#include <toml++/toml.h>
#include <stduuid/uuid.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>
#include <fast_io_device.h>
#include <fast_io_legacy.h>
#include <nlohmann/json.hpp>
#include <rapidjson/writer.h>
#include <rapidjson/pointer.h>
#include <libxml/xmlschemas.h>
#include <rapidjson/document.h>
#include "absl/strings/ascii.h"
#include <absl/strings/str_cat.h>
#include <rapidjson/allocators.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <absl/strings/str_split.h>
#include <absl/strings/str_replace.h>
#include <rapidjson/ostreamwrapper.h>
#include <concurrentqueue/concurrentqueue.h>

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

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4244)
#endif

#include <jwt-cpp/jwt.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <any>
#include <compare>
#include <variant>
#include <optional>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <source_location>

#include <bit>
#include <limits>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <climits>

#include <regex>
#include <string>
#include <format>
#include <cctype>
#include <cwctype>
#include <charconv>
#include <string_view>

#include <set>
#include <map>
#include <list>
#include <span>
#include <array>
#include <deque>
#include <tuple>
#include <stack>
#include <queue>
#include <vector>
#include <ranges>
#include <iterator>
#include <unordered_set>
#include <unordered_map>

#include <new>
#include <memory>
#include <memory_resource>

#include <mutex>
#include <latch>
#include <thread>
#include <future>
#include <atomic>
#include <barrier>
#include <semaphore>
#include <stop_token>
#include <shared_mutex>
#include <condition_variable>

#include <ratio>
#include <chrono>
#include <random>
#include <numbers>

#include <fstream>
#include <filesystem>

#include <ios>
#include <cstdio>
#include <istream>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <iostream>

#include <cmath>
#include <cerrno>
#include <cassert>
#include <complex>
#include <csignal>
#include <valarray>
#include <stdexcept>

#include <locale>
#include <execution>
#include <algorithm>
#include <functional>

#include <version>

#include <concepts>
#include <coroutine>

#include <cfenv>
#include <cfloat>

#include <ctime>
#include <cstdarg>
#include <csetjmp>
#include <cstring>

#include <windows.h>

namespace QLogicaeCore
{

}
