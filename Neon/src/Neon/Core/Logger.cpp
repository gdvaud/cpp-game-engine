#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Neon {
    std::shared_ptr<spdlog::logger> Logger::m_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::m_ClientLogger;

    void Logger::Init() {
        spdlog::set_pattern("%^[%8T %3e] [%-5n] [%-8l] %v%$");

        m_CoreLogger = spdlog::stdout_color_mt("NEON");
        m_CoreLogger->set_level(spdlog::level::trace);

        m_ClientLogger = spdlog::stdout_color_mt("CLIENT");
        m_ClientLogger->set_level(spdlog::level::trace);
    }
}  // namespace Neon
