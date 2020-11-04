#pragma once

#include "neon_pch.h"

#include "Event.h"

namespace Neon {
    class EventDispatcher {
    public:
        EventDispatcher(Event &event)
                : _event(event) {}
        
        template<typename T>
        bool Dispatch(std::function<bool(T &)> callback) {
            if (_event.GetEventType() == T::GetStaticEventType()) {
                _event._handled = callback(_event);
            }
            
            return _event._handled;
        }
    
    private:
        Event &_event;
    };
    
}
