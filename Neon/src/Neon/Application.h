#pragma once

namespace Neon {
    class Application {
    public:
        Application();
        virtual ~Application();
    
        void Run();
    };
    
    Application* CreateApplication();
}
