#pragma once

#include "Event.h"

namespace Neon {
    
    class KeyEvent : public Event {
    public:
        inline int GetKeyCod() const { return _keyCode; }
    
    protected:
        KeyEvent(int keyCode) : _keyCode(keyCode) {}
        
        int _keyCode;
    };
    
    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keyCode, int repeatCount)
                : KeyEvent(keyCode), _repeatCount(repeatCount) {}
        
        inline int GetRepeatCount() const { return _repeatCount; }
        
        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent:" << _keyCode << " repeats=" << _repeatCount;
            return ss.str();
        }
        
        // Overrides
        EVENT_TYPE_DEF(KeyPressed);
    
    private:
        int _repeatCount;
    };
    
    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keyCode)
                : KeyEvent(keyCode) {}
        
        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent:" << _keyCode;
            return ss.str();
        }
        
        // Overrides
        EVENT_TYPE_DEF(KeyReleased);
    };
}