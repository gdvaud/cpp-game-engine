#pragma once

#include "neon_pch.h"

#include "spdlog/spdlog.h"

namespace Neon {
    class Logger {
    public:
        static void Init();
        
        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
            return _coreLogger;
        }
        
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
            return _clientLogger;
        }
    
    private:
        static std::shared_ptr<spdlog::logger> _coreLogger;
        static std::shared_ptr<spdlog::logger> _clientLogger;
    };
}

// Core log macros
#define NEO_CORE_TRACE(...)     ::Neon::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define NEO_CORE_DEBUG(...)     ::Neon::Logger::GetCoreLogger()->debug(__VA_ARGS__)
#define NEO_CORE_INFO(...)      ::Neon::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define NEO_CORE_WARN(...)      ::Neon::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define NEO_CORE_ERROR(...)     ::Neon::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define NEO_CORE_CRITICAL(...)  ::Neon::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define NEO_TRACE(...)          ::Neon::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define NEO_DEBUG(...)          ::Neon::Logger::GetClientLogger()->debug(__VA_ARGS__)
#define NEO_INFO(...)           ::Neon::Logger::GetClientLogger()->info(__VA_ARGS__)
#define NEO_WARN(...)           ::Neon::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define NEO_ERROR(...)          ::Neon::Logger::GetClientLogger()->error(__VA_ARGS__)
#define NEO_CRITICAL(...)       ::Neon::Logger::GetClientLogger()->critical(__VA_ARGS__)