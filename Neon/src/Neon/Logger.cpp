#include "Logger.h"

#include "neon_pch.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Neon {
    std::shared_ptr<spdlog::logger> Logger::_coreLogger;
    std::shared_ptr<spdlog::logger> Logger::_clientLogger;
    
    void Logger::Init() {
        spdlog::set_pattern("%^[%8T %3e] [%-5n] [%-8l] %v%$");
        
        _coreLogger = spdlog::stdout_color_mt("NEON");
        _coreLogger->set_level(spdlog::level::trace);
        
        _clientLogger = spdlog::stdout_color_mt("CLIENT");
        _clientLogger->set_level(spdlog::level::trace);
    }
}