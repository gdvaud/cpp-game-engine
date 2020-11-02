#pragma once

#include <string>
#include "EventDispatcher.h"

namespace Neon {
    enum class EventType {
        None = 0,
        WindowClosed, WindowResized, WindowFocused, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

#define EVENT_TYPE_DEF(type) static EventType GetStaticEventType() { return EventType::type; } \
                             EventType GetEventType() const override { return GetStaticEventType(); } \
                             std::string GetName() const override { return #type; }
    
    class Event {
        friend class EventDispatcher;
    public:
        virtual std::string GetName() const = 0;
        
        virtual EventType GetEventType() const = 0;
        
        virtual std::string ToString() {
            return GetName();
        }
    
    protected:
        bool _handled = false;
    };
}
