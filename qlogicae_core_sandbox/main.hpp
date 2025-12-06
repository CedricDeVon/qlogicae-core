#pragma once

#include "qlogicae_core_sandbox/includes/application.hpp"

#include "qlogicae_core/includes/all.hpp"

#include <nanobench.h>

#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

#include <nanobench.h>
#include <rocksdb/db.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <unordered_map>
#include <boost/container/vector.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/unordered/unordered_map.hpp>
#include "absl/container/inlined_vector.h"
#include "absl/container/flat_hash_map.h"
#include <boost/container/list.hpp>
#include <absl/container/inlined_vector.h>


#include <string>

#include <boost/container/vector.hpp>
#include <boost/container/list.hpp>
#include <boost/unordered_map.hpp>
#include <boost/container/string.hpp>

#include <absl/container/inlined_vector.h>
#include <absl/container/flat_hash_map.h>
#include <absl/strings/str_cat.h>

#include <boost/lexical_cast.hpp>

int main(int, char**);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int
)
{
    return main(__argc, __argv);
}

namespace QLogicaeCoreSandbox
{

}
