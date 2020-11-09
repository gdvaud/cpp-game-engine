#pragma once

#include "neon_pch.h"

#include "Window.h"
#include "Neon/LayerStack.h"
#include "Neon/Event/Event.h"
#include "Neon/Event/ApplicationEvent.h"

namespace Neon {
    class Application {
    public:
        Application();
        virtual ~Application();
    
        void Run();
        void OnEvent(Event& event);
    
        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);
    private:
        bool OnWindowClosed(WindowClosedEvent& event);
        
        std::unique_ptr<Window> _window;
        bool _running = true;
        
        LayerStack _layerStack;
    };
    
    Application* CreateApplication();
}
