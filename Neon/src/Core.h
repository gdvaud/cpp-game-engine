#pragma once

#define NEO_ASSERT(x, ...) if (!(x)) { NEO_ERROR("Assertion failed : {0}", __VA_ARGS__); throw; }
#define NEO_CORE_ASSERT(x, ...) if (!(x)) { NEO_CORE_ERROR("Assertion failed : {0}", __VA_ARGS__); throw; }

//#define NEO_ASSERT(x, ...)
//#define NEO_CORE_ASSERT(x, ...)
