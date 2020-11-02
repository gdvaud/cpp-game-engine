#pragma once

#include "Event.h"
#include <sstream>

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
        
        std::string ToString() override {
            std::stringstream ss;
            ss << "WindowResizedEvent {width(" << _width << ") height(" << _height << ")";
            return ss.str();
        }
    
    private:
        uint32_t _width, _height;
    };
    
    class WindowClosedEvent : public Event {
    public:
        WindowClosedEvent() {}
        
        // Overrides
        EVENT_TYPE_DEF(WindowClosed);
    };
}