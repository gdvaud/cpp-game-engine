#pragma once

#include "neon_pch.h"

#include "Window.h"

namespace Neon {
    class Application {
    public:
        Application();
        virtual ~Application();
    
        void Run();

    private:
        std::unique_ptr<Window> _window;
        bool _running;
    };
    
    Application* CreateApplication();
}
