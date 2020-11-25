#pragma once

#include "neon_pch.h"

namespace Neon {
    enum class EventType {
        None = 0,
        WindowClosed,
        WindowResized,
        WindowFocused,
        WindowLostFocus,
        WindowMoved,
        AppTick,
        AppUpdate,
        AppRender,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define EVENT_TYPE_DEF(type)                                                 \
    static EventType GetStaticEventType() { return EventType::type; }        \
    EventType GetEventType() const override { return GetStaticEventType(); } \
    std::string GetName() const override { return #type; }

    class Event {
    public:
        bool Handled = false;

        virtual std::string GetName() const = 0;     // { return ""; };
        virtual EventType GetEventType() const = 0;  // { return EventType::None; };
        virtual std::string ToString() const { return GetName(); }
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& event) {
        return os << event.ToString();
    }

    class EventDispatcher {
        template <typename T>
        using EventCallback = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& event)
            : _event(event) {}

        template <typename T>
        bool Dispatch(EventCallback<T> callback) {
            if (_event.GetEventType() == T::GetStaticEventType()) {
                _event.Handled = callback(*(T*)&_event);
            }

            return _event.Handled;
        }

    private:
        Event& _event;
    };
}  // namespace Neon
