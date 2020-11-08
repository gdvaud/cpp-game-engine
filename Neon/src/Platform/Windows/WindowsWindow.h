#pragma once
#include "neon_pch.h"

#include <GLFW/glfw3.h>
#include "Neon/Window.h"

namespace Neon {
    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowSettings &settings);
        ~WindowsWindow() override;
        
        void OnUpdate() override;
        
        // Window attributes
        uint16_t GetWidth() const override;
        uint16_t GetHeight() const override;
        void SetEventCallback(std::function<bool(Event &)> callback) override;
        void SetVSync(bool enabled) override;
        bool IsVSync() override;
    
    private:
        virtual void Init(const WindowSettings &settings);
        virtual void Shutdown();
    private:
        GLFWwindow *_window;
        
        struct WindowData {
            std::string Title;
            uint16_t Width, Height;
            bool VSync;
            
            EventCallbackFn Callback;
        };
        WindowData _data;
    };
}