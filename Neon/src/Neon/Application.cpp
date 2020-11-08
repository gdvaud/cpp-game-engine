#include "neon_pch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Neon {
    Application::Application() {
        _window = std::unique_ptr<Window>(Window::Create());
    }
    
    Application::~Application() {}
    
    void Application::Run() {
        while (_running) {
            _window->OnUpdate();
        }
    }
}