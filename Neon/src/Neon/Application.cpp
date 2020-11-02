#include "Application.h"

#include <iostream>

namespace Neon {
    Application::Application() {}
    
    Application::~Application() {}
    
    void Application::Run() {
        std::cout << "Hello Neon Engine" << std::endl;
    }
}