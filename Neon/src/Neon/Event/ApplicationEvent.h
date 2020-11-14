#pragma once

#include "Event.h"

namespace Neon {
    
    class WindowResizedEvent : public Event {
    public:
        WindowResizedEvent(uint32_t width, uint32_t height)
                : _width(width), _height(height) {}
        
        // Getters
        inline uint32_t getWidth() const {
            return _width;
        }
        
        inline uint32_t getHeight() const {
            return _height;
        }
        
        // Overrides
        EVENT_TYPE_DEF(WindowResized);
        
        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizedEvent {Width(" << _width << ") Height(" << _height << ")";
            return ss.str();
        }
    
    private:
        uint32_t _width, _height;
    };
    
    class WindowClosedEvent : public Event {
    public:
        WindowClosedEvent() = default;
        
        // Overrides
        EVENT_TYPE_DEF(WindowClosed);
    };
    
    class AppTickEvent : public Event {
    public:
        AppTickEvent() = default;
        
        // Overrides
        EVENT_TYPE_DEF(AppTick);
    };
    
    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() = default;
        
        // Overrides
        EVENT_TYPE_DEF(AppUpdate);
    };
    
    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() = default;
        
        // Overrides
        EVENT_TYPE_DEF(AppRender);
    };
    
}