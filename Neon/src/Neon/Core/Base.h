#pragma once

#include <memory>

#define NEO_ENABLE_ASSERTS

namespace Neon {
    // Reference type definition
    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    
    // Scope type definition
    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}  // namespace Neon

#include "Neon/Core/Assert.h"
#include "Neon/Core/Logger.h"
