#pragma once

#ifdef NDEBUG
#define ensure(expr) expr
#else
#include <cassert>
#define ensure(expr) assert(expr)
#endif