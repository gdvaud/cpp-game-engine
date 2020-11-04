#include "Application.h"

#include "neon_pch.h"

namespace Neon {
    Application::Application() {}
    
    Application::~Application() {}
    
    void Application::Run() {
        std::cout << "Hello Neon Engine" << std::endl;
    }
}