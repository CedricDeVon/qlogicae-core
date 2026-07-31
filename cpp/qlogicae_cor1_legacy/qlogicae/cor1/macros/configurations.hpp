#pragma once

// 3rd Party Package Imports

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FollyVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FollyVcpkgImports__IS_COMPILATION_ENABLED 1

	#ifdef _M_X64
		#include <folly/init/Init.h> 
		#include <folly/synchronization/MicroSpinLock.h> 

	#endif

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RapidCsvVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RapidCsvVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <rapidcsv.h>

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CurlVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__CurlVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <curl/curl.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			XlntVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__XlntVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <xlnt/xlnt.hpp> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LibOqsVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__LibOqsVcpkgImports__IS_COMPILATION_ENABLED 1

	#ifndef ORT_DISABLE_SCHEMA_VALIDATION
		#define ORT_DISABLE_SCHEMA_VALIDATION 1
	#endif

	#include <oqs/oqs.h>

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EfswVcpkgImports \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__EfswVcpkgImports__IS_COMPILATION_ENABLED 1

#ifndef ORT_DISABLE_SCHEMA_VALIDATION
#define ORT_DISABLE_SCHEMA_VALIDATION 1
#endif

#include <efsw/efsw.hpp>

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			JwtCppVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__JwtCppVcpkgImports__IS_COMPILATION_ENABLED 1

	#ifdef _MSC_VER
		#pragma warning(push)
		#pragma warning(disable : 4244 4267)
	#endif

		#include <jwt-cpp/jwt.h>

	#ifdef _MSC_VER
		#pragma warning(pop)
	#endif

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			OnnxRuntimeVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__OnnxRuntimeVcpkgImports__IS_COMPILATION_ENABLED 1

	#ifdef _M_X64
		#include <onnxruntime/onnxruntime_cxx_api.h> 

	#endif
#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RocksDbVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RocksDbVcpkgImports__IS_COMPILATION_ENABLED 1

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

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			NanobenchVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__NanobenchVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <nanobench.h>

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SodiumVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SodiumVcpkgImports__IS_COMPILATION_ENABLED 1

	#ifndef SALT_LEN
		#define SALT_LEN crypto_pwhash_SALTBYTES

	#endif

	#include <sodium.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Sqlite3VcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Sqlite3VcpkgImports__IS_COMPILATION_ENABLED 1

	#include <sqlite3.h>

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TomlPlusPlusVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TomlPlusPlusVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <toml++/toml.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			PugixmlVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__PugixmlVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <pugixml.hpp> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Pcre2VcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Pcre2VcpkgImports__IS_COMPILATION_ENABLED 1

	#ifndef PCRE2_CODE_UNIT_WIDTH
		#define PCRE2_CODE_UNIT_WIDTH 8
	#endif

	#include <pcre2.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Argon2VcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Argon2VcpkgImports__IS_COMPILATION_ENABLED 1

	#include <argon2.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CppCodecVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__CppCodecVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <cppcodec/base32_rfc4648.hpp> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FastIoVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FastIoVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <fast_io.h> 
	#include <fast_io_device.h> 
	#include <fast_io_legacy.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RapidJsonVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RapidJsonVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <rapidjson/writer.h> 
	#include <rapidjson/pointer.h> 
	#include <rapidjson/document.h> 
	#include <rapidjson/allocators.h> 
	#include <rapidjson/prettywriter.h> 
	#include <rapidjson/stringbuffer.h> 
	#include <rapidjson/ostreamwrapper.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AbslVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__AbslVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <absl/time/time.h> 
	#include <absl/time/clock.h> 
	#include <absl/strings/ascii.h> 
	#include <absl/strings/str_cat.h> 
	#include <absl/strings/str_join.h> 
	#include <absl/strings/str_split.h> 
	#include <absl/strings/str_replace.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			BoostVcpkgImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__BoostVcpkgImports__IS_COMPILATION_ENABLED 1

	#include <boost/asio.hpp> 
	#include <boost/locale.hpp> 
	#include <boost/uuid/uuid.hpp> 
	#include <boost/uuid/uuid_io.hpp> 
	#include <boost/thread/mutex.hpp> 
	#include <boost/thread/locks.hpp> 
	#include <boost/thread/mutex.hpp> 
	#include <boost/locale/boundary.hpp> 
	#include <boost/thread/shared_mutex.hpp> 
	#include <boost/uuid/uuid_generators.hpp> 
	#include <boost/uuid/string_generator.hpp> 
	#include <boost/thread/recursive_mutex.hpp> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			YamlCppVcpkgImports \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__YamlCppVcpkgImports__IS_COMPILATION_ENABLED 1

#pragma warning(push)
#pragma warning(disable : 4244 4251 4275)

#include <yaml-cpp/yaml.h>

#pragma warning(pop)

#else
#endif

// Recommended STD Imports

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			StdImports \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__StdImports__IS_COMPILATION_ENABLED 1

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

	#include <codecvt>

	#include <immintrin.h>

	#include <winsock2.h>
	#include <ws2tcpip.h>

	#include <windows.h>
	#include <winnt.h>

	#include <shellapi.h>
	#include <shlobj.h>

	#include <aclapi.h>

#else
#endif

// Helper Definitions

#ifndef NOMINMAX
	#define NOMINMAX

#endif

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN

#endif

#ifndef HASH_LEN
	#define HASH_LEN 32

#endif

#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0A00

#endif


// Enums

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AbstractEnum \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__AbstractEnum__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CharacterDomain \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__CharacterDomain__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			DilithiumCryptographyAlgorithm \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__DilithiumCryptographyAlgorithm__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EmailBody \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__EmailBody__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EmailSecurity \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__EmailSecurity__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EntityActivationStatus \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__EntityActivationStatus__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerAction \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerAction__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerMetadataFlags \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerMetadataFlags__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerSource \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerSource__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			KyberCryptographyAlgorithm \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__KyberCryptographyAlgorithm__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogFormat \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__LogFormat__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogLevel \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__LogLevel__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogMedium \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__LogMedium__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogOutput \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__LogOutput__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ResultsStatus \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ResultsStatus__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TemperatureUnit \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TemperatureUnit__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextCase \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextCase__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextEncoding \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextEncoding__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeFormat \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TimeFormat__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeScaleUnit \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TimeScaleUnit__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeZone \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TimeZone__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Uuid \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Uuid__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsEnvironmentVariable \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsEnvironmentVariable__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsRegistryRootPath \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsRegistryRootPath__IS_COMPILATION_ENABLED 1

#else
#endif

// Core

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AbstractConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__AbstractConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SingletonManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SingletonManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SingletonManager \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SingletonManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ErrorManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ErrorManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ErrorManager \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ErrorManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AbstractClass \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__AbstractClass__IS_COMPILATION_ENABLED 1

#else
#endif

// Helpers


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Assembly \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__Assembly__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileEntity \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileEntity__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEntity \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEntity__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEvent \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEvent__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerManagerOptions \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerManagerOptions__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerSlot \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerSlot__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerWatchContext \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerWatchContext__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FunctionWrapper \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FunctionWrapper__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			GmailApiManagerResponse \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__GmailApiManagerResponse__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			IntervalClock \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__IntervalClock__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Json \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Json__IS_COMPILATION_ENABLED 1

#else
#endif



#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			JsonKeyHashHandler \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__JsonKeyHashHandler__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			JsonKeyIndexHashHandler \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__JsonKeyIndexHashHandler__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			KeyIndexHashHandler \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__KeyIndexHashHandler__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			NetworkPingManagerResponse \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__NetworkPingManagerResponse__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			PairHashOperator \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__PairHashOperator__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RegularKeyDeleteHandler \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RegularKeyDeleteHandler__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RestApiManagerResponse \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RestApiManagerResponse__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Results \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Results__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RuntimeBenchmarker \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RuntimeBenchmarker__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RuntimeBenchmarkerEpochIterationPair \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RuntimeBenchmarkerEpochIterationPair__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RuntimeBenchmarkerTestCase \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RuntimeBenchmarkerTestCase__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RuntimeBenchmarkerTestSuite \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RuntimeBenchmarkerTestSuite__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SQLiteBackend \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SQLiteBackend__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SQLiteException \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SQLiteException__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SQLiteRow \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SQLiteRow__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SQLiteStatement \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SQLiteStatement__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SQLiteStatementData \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SQLiteStatementData__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SQLiteTransaction \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SQLiteTransaction__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			StateManagerItem \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__StateManagerItem__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeoutClock \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TimeoutClock__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ValidMutexLock \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ValidMutexLock__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ValueEnumKeyDeleteHandler \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ValueEnumKeyDeleteHandler__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			VectorStringHashHandler \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__VectorStringHashHandler__IS_COMPILATION_ENABLED 1

#else
#endif

// Configurations

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AccountSessionsManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__AccountSessionsManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Aes256CipherCryptographyManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Aes256CipherCryptographyManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Argon2idHashCryptographyManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Argon2idHashCryptographyManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AsynchronousBatchManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__AsynchronousBatchManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AsynchronousManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__AsynchronousManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			BcryptHashCryptographyManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__BcryptHashCryptographyManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			BinaryFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__BinaryFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CharacterDomainEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__CharacterDomainEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CharacterDomainManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__CharacterDomainManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ConfigurationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ConfigurationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ConsoleIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ConsoleIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ConsoleLogManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ConsoleLogManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CryptographyMigrationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__CryptographyMigrationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CsvFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__CsvFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CurlPackageManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__CurlPackageManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			DilithiumCryptographyAlgorithmEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__DilithiumCryptographyAlgorithmEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			DilithiumCryptographyManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__DilithiumCryptographyManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EdscaSignatureCryptographyManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__EdscaSignatureCryptographyManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EmailBodyEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__EmailBodyEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EmailSecurityEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__EmailSecurityEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EntityActivationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__EntityActivationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EntityActivationStatusEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__EntityActivationStatusEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__EnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ExcelFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ExcelFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileLogManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileLogManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEntityEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEntityEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerActionEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerActionEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerMetadataFlagsEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerMetadataFlagsEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerSourceEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerSourceEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemAliasEntityPathManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemAliasEntityPathManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FunctionWrapperConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FunctionWrapperConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			GmailApiManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__GmailApiManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			IntervalClockConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__IntervalClockConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			JsonwebtokenCryptographyManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__JsonwebtokenCryptographyManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			JsonFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__JsonFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			JsonTextManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__JsonTextManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			KyberCryptographyAlgorithmEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__KyberCryptographyAlgorithmEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			KyberCryptographyManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__KyberCryptographyManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogFormatEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__LogFormatEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogLevelEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__LogLevelEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__LogManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogMediumEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__LogMediumEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogOutputEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__LogOutputEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			MutexManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__MutexManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Neo4jApiManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Neo4jApiManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			NetworkPingManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__NetworkPingManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			OnnxApiManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__OnnxApiManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			PdfFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__PdfFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Python3ApiManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Python3ApiManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeCacheManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeCacheManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeDatabaseManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeDatabaseManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeLoggingManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeLoggingManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeCryptographyManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeCryptographyManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeApplicationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeApplicationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeConsoleApplicationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeConsoleApplicationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeDesktopApplicationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeDesktopApplicationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeFileSystemManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeFileSystemManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeServiceApplicationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeServiceApplicationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomCharacterGenerationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RandomCharacterGenerationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomEnumGenerationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RandomEnumGenerationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomNumberGenerationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RandomNumberGenerationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomSeedGenerationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RandomSeedGenerationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomStringGenerationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RandomStringGenerationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomValueGenerationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RandomValueGenerationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RegularExpressionManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RegularExpressionManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RestApiManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RestApiManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ResultsStatusEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ResultsStatusEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RocksdbDatabaseManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RocksdbDatabaseManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RuntimeBenchmarkerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RuntimeBenchmarkerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RuntimeExecutionManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__RuntimeExecutionManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ServiceApplicationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ServiceApplicationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Sha256HashCryptographyManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Sha256HashCryptographyManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SodiumPackageManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SodiumPackageManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SQLiteDatabaseManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SQLiteDatabaseManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			StateManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__StateManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SupabaseApiManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__SupabaseApiManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TemperatureManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TemperatureManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TemperatureUnitEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TemperatureUnitEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextCaseEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextCaseEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextCaseManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextCaseManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextEncodingEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextEncodingEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextEncodingManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextEncodingManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextErrorManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextErrorManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextKeyPathManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextKeyPathManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextLogManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextLogManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextPlaceholderManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TextPlaceholderManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeoutClockConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TimeoutClockConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeFormatEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TimeFormatEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TimeManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeScaleUnitEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TimeScaleUnitEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeZoneEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TimeZoneEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TomlFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__TomlFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			UriFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__UriFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			UuidEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__UuidEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			UuidManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__UuidManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ValidationManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ValidationManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ValueExtractorManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__ValueExtractorManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsEnvironmentVariableEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsEnvironmentVariableEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsEnvironmentVariableManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsEnvironmentVariableManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsRegistryManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsRegistryManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsRegistryRootPathEnumManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsRegistryRootPathEnumManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsSystemAccessManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsSystemAccessManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WordFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__WordFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Xchacha20Poly1305CipherCryptographyManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Xchacha20Poly1305CipherCryptographyManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			XmlFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__XmlFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			YamlFileIoManagerConfigurations \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__YamlFileIoManagerConfigurations__IS_COMPILATION_ENABLED 1

#else
#endif



// Managers


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AccountSessionsManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__AccountSessionsManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Aes256CipherCryptographyManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__Aes256CipherCryptographyManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Argon2idHashCryptographyManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__Argon2idHashCryptographyManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AsynchronousBatchManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__AsynchronousBatchManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AsynchronousManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__AsynchronousManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			BcryptHashCryptographyManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__BcryptHashCryptographyManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			BinaryFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__BinaryFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CharacterDomainEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__CharacterDomainEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CharacterDomainManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__CharacterDomainManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ConfigurationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__ConfigurationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ConsoleIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__ConsoleIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ConsoleLogManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__ConsoleLogManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CryptographyMigrationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__CryptographyMigrationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CsvFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__CsvFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CurlPackageManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__CurlPackageManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			DilithiumCryptographyAlgorithmEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__DilithiumCryptographyAlgorithmEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			DilithiumCryptographyManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__DilithiumCryptographyManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EdscaSignatureCryptographyManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__EdscaSignatureCryptographyManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EmailBodyEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__EmailBodyEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EmailSecurityEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__EmailSecurityEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EntityActivationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__EntityActivationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EntityActivationStatusEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__EntityActivationStatusEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__EnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ExcelFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__ExcelFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileLogManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__FileLogManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEntityEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEntityEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerActionEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerActionEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerMetadataFlagsEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerMetadataFlagsEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemEventListenerSourceEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemEventListenerSourceEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemAliasEntityPathManager \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemAliasEntityPathManager__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FileSystemManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__FileSystemManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			GmailApiManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__GmailApiManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			JsonwebtokenCryptographyManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__JsonwebtokenCryptographyManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			JsonFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__JsonFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			JsonTextManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__JsonTextManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			KyberCryptographyAlgorithmEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__KyberCryptographyAlgorithmEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			KyberCryptographyManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__KyberCryptographyManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogFormatEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__LogFormatEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogLevelEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__LogLevelEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogMediumEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__LogMediumEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			LogOutputEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__LogOutputEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			MutexManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__MutexManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Neo4jApiManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__Neo4jApiManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			NetworkPingManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__NetworkPingManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			OnnxApiManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__OnnxApiManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			PdfFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__PdfFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Python3ApiManager \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__Python3ApiManager__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeCacheManager \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeCacheManager__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeDatabaseManager \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeDatabaseManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeLoggingManager \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeLoggingManager__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeCryptographyManager \
		) \
	)
	#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeCryptographyManager__IS_COMPILATION_ENABLED 1

#else
#endif



#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeApplicationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeApplicationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeConsoleApplicationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeConsoleApplicationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeDesktopApplicationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeDesktopApplicationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeFileSystemManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeFileSystemManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			QLogicaeServiceApplicationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__QLogicaeServiceApplicationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomCharacterGenerationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__RandomCharacterGenerationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomEnumGenerationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__RandomEnumGenerationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomNumberGenerationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__RandomNumberGenerationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomSeedGenerationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__RandomSeedGenerationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomStringGenerationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__RandomStringGenerationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RandomValueGenerationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__RandomValueGenerationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RegularExpressionManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__RegularExpressionManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RestApiManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__RestApiManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ResultsStatusEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__ResultsStatusEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RocksdbDatabaseManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__RocksdbDatabaseManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			RuntimeExecutionManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__RuntimeExecutionManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ServiceApplicationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__ServiceApplicationManager__IS_COMPILATION_ENABLED 1

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Sha256HashCryptographyManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__Sha256HashCryptographyManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SodiumPackageManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__SodiumPackageManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SQLiteDatabaseManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__SQLiteDatabaseManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			StateManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__StateManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SupabaseApiManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__SupabaseApiManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TemperatureManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TemperatureManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TemperatureUnitEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TemperatureUnitEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextCaseEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TextCaseEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextCaseManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TextCaseManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextEncodingEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TextEncodingEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextEncodingManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TextEncodingManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextErrorManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TextErrorManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TextFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextKeyPathManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TextKeyPathManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextLogManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TextLogManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TextManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TextPlaceholderManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TextPlaceholderManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeFormatEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TimeFormatEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TimeManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeScaleUnitEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TimeScaleUnitEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TimeZoneEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TimeZoneEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			TomlFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__TomlFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			UriFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__UriFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			UuidEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__UuidEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			UuidManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__UuidManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ValidationManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__ValidationManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			ValueExtractorManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__ValueExtractorManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsEnvironmentVariableEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsEnvironmentVariableEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsEnvironmentVariableManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsEnvironmentVariableManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsRegistryManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsRegistryManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsRegistryRootPathEnumManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsRegistryRootPathEnumManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WindowsSystemAccessManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__WindowsSystemAccessManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			WordFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__WordFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Xchacha20Poly1305CipherCryptographyManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__Xchacha20Poly1305CipherCryptographyManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			XmlFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__XmlFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			YamlFileIoManager \
		) \
	)
#define QLOGICAE_COR1__BASE__HPP_CPP__YamlFileIoManager__IS_COMPILATION_ENABLED 1

#else
#endif








#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CurlVcpkgImports \
		) \
	)
	

	#include <curl/curl.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FastIoVcpkgImports \
		) \
	)
	

	#include <fast_io_device.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			FollyVcpkgImports \
		) \
	)
	

	#ifdef _M_X64
		#include <folly/init/Init.h> 
		#include <folly/synchronization/MicroSpinLock.h> 

	#endif

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			SodiumVcpkgImports \
		) \
	)
	

	#ifndef SALT_LEN
		#define SALT_LEN crypto_pwhash_SALTBYTES

	#endif

	#include <sodium.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			Pcre2VcpkgImports \
		) \
	)
	

	#ifndef PCRE2_CODE_UNIT_WIDTH
		#define PCRE2_CODE_UNIT_WIDTH 8
	#endif

	#include <pcre2.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			EfswVcpkgImports \
		) \
	)
	

	#ifndef ORT_DISABLE_SCHEMA_VALIDATION
	#define ORT_DISABLE_SCHEMA_VALIDATION 1
	#endif

	#include <efsw/efsw.hpp>

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			CppCodecVcpkgImports \
		) \
	)
	

	#include <cppcodec/base32_rfc4648.hpp> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			AbslVcpkgImports \
		) \
	)
	

	#include <absl/time/time.h> 
	#include <absl/time/clock.h> 
	#include <absl/strings/ascii.h> 
	#include <absl/strings/str_cat.h> 
	#include <absl/strings/str_join.h> 
	#include <absl/strings/str_split.h> 
	#include <absl/strings/str_replace.h> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			BoostVcpkgImports \
		) \
	)
	

	#include <boost/thread/mutex.hpp> 
	#include <boost/thread/locks.hpp> 
	#include <boost/thread/shared_mutex.hpp> 
	#include <boost/thread/recursive_mutex.hpp> 

#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
		QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
			StdImports \
		) \
	)
	

	#include <random>
	#include <iostream>
	#include <shlobj.h>
	#include <unordered_set>
	#include <unordered_map>

#else
#endif


#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            AsynchronousBatchManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            AsynchronousBatchManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            AsynchronousManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            AsynchronousManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            CharacterDomain \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            CharacterDomainEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            CharacterDomainEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            CharacterDomainManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            CharacterDomainManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ConfigurationManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ConfigurationManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ConsoleIoManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ConsoleIoManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            CurlPackageManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            CurlPackageManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            EntityActivationManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            EntityActivationManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            EntityActivationStatus \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            EntityActivationStatusEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            EntityActivationStatusEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            EnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            EnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileEntity \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemAliasEntityPathManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemAliasEntityPathManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEntity \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEntityEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEntityEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEvent \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerAction \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerActionEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerActionEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerManagerOptions \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerMetadataFlags \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerMetadataFlagsEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerMetadataFlagsEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerSlot \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerSource \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerSourceEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerSourceEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemEventListenerWatchContext \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FileSystemManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FunctionWrapper \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            FunctionWrapperConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            IntervalClock \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            IntervalClockConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            KeyIndexHashHandler \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            MutexManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            MutexManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            PairHashOperator \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomCharacterGenerationManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomCharacterGenerationManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomEnumGenerationManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomEnumGenerationManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomNumberGenerationManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomNumberGenerationManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomSeedGenerationManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomSeedGenerationManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomStringGenerationManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomStringGenerationManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomValueGenerationManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RandomValueGenerationManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RegularExpressionManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RegularExpressionManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RegularKeyDeleteHandler \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            Results \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ResultsStatus \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ResultsStatusEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ResultsStatusEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RuntimeExecutionManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            RuntimeExecutionManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            SodiumPackageManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            SodiumPackageManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextCase \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextCaseEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextCaseEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextCaseManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextCaseManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextEncoding \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextEncodingEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextEncodingEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextEncodingManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextEncodingManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextErrorManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextErrorManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextKeyPathManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextKeyPathManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextPlaceholderManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TextPlaceholderManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeFormat \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeFormatEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeFormatEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeScaleUnit \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeScaleUnitEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeScaleUnitEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeZone \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeZoneEnumManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeZoneEnumManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeoutClock \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            TimeoutClockConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ValidMutexLock \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ValidationManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ValidationManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ValueEnumKeyDeleteHandler \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ValueExtractorManager \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            ValueExtractorManagerConfigurations \
        ) \
    )


#else
#endif

#if QLOGICAE_COR1__BASE__HPP_CPP__COMPILATION_CONDITIONS_TEMPLATE( \
        QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_ENABLED_TEMPLATE( \
            VectorStringHashHandler \
        ) \
    )


#else
#endif

