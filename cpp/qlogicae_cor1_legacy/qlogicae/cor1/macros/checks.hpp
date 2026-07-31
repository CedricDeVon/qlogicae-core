#pragma once

#if !defined(_MSC_VER)
#error "Error - Compilation via MSVC is required"
#endif

#if _MSVC_LANG < 202002L
#error "Error - Version C++20 or higher is required"
#endif
