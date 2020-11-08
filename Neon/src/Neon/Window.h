#pragma once

#include "neon_pch.h"

#include "Neon/Event/Event.h"

namespace Neon {
    struct WindowSettings {
        std::string Title;
        uint16_t Width;
        uint16_t Height;
        
        WindowSettings(const std::string &_title = "Hazel Engine",
                       unsigned int _width = 1280,
                       unsigned int _height = 720)
                : Title(_title), Width(_width), Height(_height) {}
    };
    
    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        
        static Window *Create(const WindowSettings &settings = WindowSettings());
        
        virtual ~Window() = 0;
        
        virtual void OnUpdate() = 0;
        
        // Window attributes
        virtual uint16_t GetWidth() const = 0;
        
        virtual uint16_t GetHeight() const = 0;
        
        virtual void SetEventCallback(std::function<bool(Event &)> callback) = 0;
        
        virtual void SetVSync(bool enabled) = 0;
        
        virtual bool IsVSync() = 0;
    };
}