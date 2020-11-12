#include "neon_pch.h"
#include "Application.h"

namespace Neon {
    
    Application::Application() {
        _window = std::unique_ptr<Window>(Window::Create());
        _window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent, this));
    }
    
    Application::~Application() {}
    
    void Application::Run() {
        while (_running) {
            for (auto layer : _layerStack)
                layer->OnUpdate();
            
            _window->OnUpdate();
        }
    }
    
    void Application::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClosed, this));
        
        for (auto it = _layerStack.end(); it != _layerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.Handled)
                break;
        }
    }
    
    void Application::PushLayer(Layer *layer) {
        _layerStack.PushLayer(layer);
    }
    
    void Application::PushOverlay(Layer *layer) {
        _layerStack.PushOverlay(layer);
    }
    
    // == Private ========
    bool Application::OnWindowClosed(WindowClosedEvent &event) {
        _running = false;
        return true;
    }
}