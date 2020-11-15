#pragma once

#include "Neon/Window.h"

namespace Neon {
    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowSettings &settings);
        ~WindowsWindow() override;
        
        void OnUpdate() override;
        
        // Window attributes
        virtual void *GetNativeWindow() const { return _window; }
        inline uint16_t GetWidth() const override;
        inline uint16_t GetHeight() const override;
        void SetEventCallback(const EventCallbackFn &callback) override;
        void SetVSync(bool enabled) override;
        bool IsVSync() override;
    
    private:
        virtual void Init(const WindowSettings &settings);
        virtual void InitEvents();
        virtual void Shutdown();
    private:
        GLFWwindow *_window;
        
        struct WindowData {
            std::string Title;
            uint16_t Width, Height;
            bool VSync;
            
            EventCallbackFn EventCallback;
        };
        WindowData _data;
    };
}
