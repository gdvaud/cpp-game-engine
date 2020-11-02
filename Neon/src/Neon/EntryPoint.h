#pragma once

#ifdef NEON_PLATFORM_WINDOWS

#include "Logger.h"

extern Neon::Application *Neon::CreateApplication();

int main(int argc, char **argv) {
    Neon::Logger::Init();
    NEO_CORE_INFO("Neo Engine is starting");
    
    NEO_CORE_INFO("Application being created");
    auto app = Neon::CreateApplication();
    
    NEO_CORE_INFO("Application is running");
    app->Run();
    NEO_CORE_INFO("Application is closing");
    
    delete app;
    NEO_CORE_INFO("Application has been closed");
    
    NEO_CORE_INFO("Neo Engine has stopped");
}

#endif