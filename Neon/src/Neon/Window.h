#pragma once

#include "neon_pch.h"

#include "Event/Event.h"

namespace Neon {
    struct WindowSettings {
        std::string title;
        uint16_t width;
        uint16_t height;
        
        WindowSettings(const std::string &_title = "Hazel Engine",
                       unsigned int _width = 1280,
                       unsigned int _height = 720)
                : title(_title), width(_width), height(_height) {}
    };
    
    class Window {
    public:
        static Window *Create(const WindowSettings &settings = WindowSettings());
        
        virtual ~Window();
        
        virtual void OnUpdate() = 0;
        
        // Window attributes
        virtual uint16_t GetWidth() const = 0;
        
        virtual uint16_t GetHeight() const = 0;
        
        virtual void SetEventCallback(const std::function<bool(Event &)> callback) = 0;
        
        virtual void SetVSync(bool enabled) = 0;
        
        virtual bool IsVSync() = 0;
    };
}