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
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            _window->OnUpdate();
        }
    }
}