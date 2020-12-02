#pragma once

#include "Neon/Core/Application.h"
#include "Neon/Core/Logger.h"

#ifdef NEO_PLATFORM_WINDOWS

static void Test() {
    std::cout << "Test" << std::endl;
}

extern Neon::Application* Neon::CreateApplication();

int main(int argc, char** argv) {
    Neon::Logger::Init();
    NEO_CORE_INFO("Neo Engine is starting");

    NEO_CORE_INFO("Application being created");
    auto app = Neon::CreateApplication();

    NEO_CORE_INFO("Application is running");
    app->Run();
    NEO_CORE_INFO("Application has been closed");

    delete app;
    NEO_CORE_INFO("Neo Engine has stopped");
}

#endif
