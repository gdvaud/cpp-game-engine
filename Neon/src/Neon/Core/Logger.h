#pragma once

// clang-format off
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
// clang-format on

namespace Neon {
    class Logger {
    public:
        static void Init();

        inline static Ref<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
        inline static Ref<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }

    private:
        static Ref<spdlog::logger> m_CoreLogger;
        static Ref<spdlog::logger> m_ClientLogger;
    };
}  // namespace Neon

// Core log macros
#define NEO_CORE_TRACE(...)    ::Neon::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define NEO_CORE_DEBUG(...)    ::Neon::Logger::GetCoreLogger()->debug(__VA_ARGS__)
#define NEO_CORE_INFO(...)     ::Neon::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define NEO_CORE_WARN(...)     ::Neon::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define NEO_CORE_ERROR(...)    ::Neon::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define NEO_CORE_CRITICAL(...) ::Neon::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define NEO_TRACE(...)    ::Neon::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define NEO_DEBUG(...)    ::Neon::Logger::GetClientLogger()->debug(__VA_ARGS__)
#define NEO_INFO(...)     ::Neon::Logger::GetClientLogger()->info(__VA_ARGS__)
#define NEO_WARN(...)     ::Neon::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define NEO_ERROR(...)    ::Neon::Logger::GetClientLogger()->error(__VA_ARGS__)
#define NEO_CRITICAL(...) ::Neon::Logger::GetClientLogger()->critical(__VA_ARGS__)
