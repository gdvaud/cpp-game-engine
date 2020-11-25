#pragma once

#include <memory>

#define NEO_ENABLE_ASSERTS

// Macro utilities
#define NEO_EXPAND_MACRO(x) x
#define NEO_STRINGIFY_MACRO(x) #x

namespace Hazel {
    template<typename T>
    using Ref = std::shared_ptr<T>;
}

#include "Neon/Core/Assert.h"
#include "Neon/Core/Logger.h"
