#pragma once

#include "Neon/Core/Base.h"
#include "Neon/Core/Logger.h"

#ifdef NEO_ENABLE_ASSERTS
    #define NEO_INTERNAL_ASSERT_IMPL(type, check, msg) { if (!(check)) { NEO##type##ERROR(msg); __debugbreak(); throw; } }
    
    #define NEO_ASSERT(check, msg) NEO_INTERNAL_ASSERT_IMPL(_, check, msg)
    #define NEO_CORE_ASSERT(check, msg) NEO_INTERNAL_ASSERT_IMPL(_CORE_, check, msg)
#else
    #define NEO_ASSERT(...)
    #define NEO_CORE_ASSERT(...)
#endif
