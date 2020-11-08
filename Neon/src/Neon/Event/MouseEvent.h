#pragma once

#include "Event.h"

namespace Neon {
    
    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y)
                : _x(x), _y(y) {}
        
        inline float GetX() const {
            return _x;
        }
        
        inline float GetY() const {
            return _y;
        }
        
        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: (" << _x << ", " << _y << ")";
            return ss.str();
        }
        
        // Overrides
        EVENT_TYPE_DEF(MouseMoved);
    
    private:
        float _x, _y;
    };
    
    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
                : _xOffset(xOffset), _yOffset(yOffset) {}
        
        inline float GetXOffset() const {
            return _xOffset;
        }
        
        inline float GetYOffset() const {
            return _yOffset;
        }
        
        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: (" << _xOffset << ", " << _yOffset << ")";
            return ss.str();
        }
        
        // Overrides
        EVENT_TYPE_DEF(MouseScrolled);
    
    private:
        float _xOffset, _yOffset;
    };
    
    class MouseButtonEvent : public Event {
    public:
        inline int GetButtonCode() const {
            return _buttonCode;
        }
    
    protected:
        MouseButtonEvent(int buttonCode) : _buttonCode(buttonCode) {}
        
        int _buttonCode;
    };
    
    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}
        
        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << _buttonCode;
            return ss.str();
        }
        
        // Overrides
        EVENT_TYPE_DEF(MouseButtonPressed);
    };
    
    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}
        
        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << _buttonCode;
            return ss.str();
        }
        
        // Overrides
        EVENT_TYPE_DEF(MouseButtonReleased);
    };
}