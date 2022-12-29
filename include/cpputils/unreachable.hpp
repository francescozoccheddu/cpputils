#pragma once

namespace cpputils
{

#ifdef NDEBUG
#ifdef __GNUC__
    [[noreturn]] inline __attribute__((always_inline)) void unreachable() { __builtin_unreachable(); }
#elif defined(_MSC_VER) 
    [[noreturn]] __forceinline void unreachable() { __assume(false); }
#else
#include <cstdlib>
    [[noreturn]] inline void unreachable() { std::abort(); }
#endif
#else
#include <cassert>
    [[noreturn]] inline void unreachable() { assert(false); }
#endif

}