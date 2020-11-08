#pragma once

#include "neon_pch.h"

#include "Window.h"
#include "Neon/Event/Event.h"
#include "Neon/Event/ApplicationEvent.h"

namespace Neon {
    class Application {
    public:
        Application();
        virtual ~Application();
    
        void Run();
        void OnEvent(Event& event);
    private:
        bool OnWindowClosed(WindowClosedEvent& event);
        
        std::unique_ptr<Window> _window;
        bool _running = true;
    };
    
    Application* CreateApplication();
}
