#pragma once

#include "neon_pch.h"

namespace Neon {
    enum class EventType {
        None = 0,
        WindowClosed, WindowResized, WindowFocused, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

#define BIND_EVENT_FN(x, y) std::bind(&x, y, std::placeholders::_1)
#define EVENT_TYPE_DEF(type) static EventType GetStaticEventType() { return EventType::type; } \
                             EventType GetEventType() const override { return GetStaticEventType(); } \
                             std::string GetName() const override { return #type; }
    
    class Event {
        friend class EventDispatcher;
    
    public:
        virtual std::string GetName() const = 0;
        
        virtual EventType GetEventType() const = 0;
        
        virtual std::string ToString() const {
            return GetName();
        }
    
    protected:
        bool _handled = false;
    };
    
    class EventDispatcher {
        template<typename T>
        using EventCallback = std::function<bool(T &)>;
    public:
        EventDispatcher(Event &event)
                : _event(event) {}
        
        template<typename T>
        bool Dispatch(EventCallback<T> callback) {
            if (_event.GetEventType() == T::GetStaticEventType()) {
                _event._handled = callback(*(T *) &_event);
            }
            
            return _event._handled;
        }
    
    private:
        Event &_event;
    };
}
