#include "neon_pch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Neon {
    
    Application::Application() {
        _window = std::unique_ptr<Window>(Window::Create());
        _window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent, this));
    }
    
    Application::~Application() {}
    
    void Application::Run() {
        while (_running) {
            _window->OnUpdate();
        }
    }
    
    void Application::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClosed, this));
    }
    
    bool Application::OnWindowClosed(WindowClosedEvent &event) {
        _running = false;
        return true;
    }
}