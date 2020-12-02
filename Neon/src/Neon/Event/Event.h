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

    inline std::ostream& operator<<(std::ostream& os, const Event& event) { return os << event.ToString(); }

    class EventDispatcher {
    public:
        EventDispatcher(Event& event) : m_Event(event) {}

        template <typename T, typename F>
        bool Dispatch(const F& callback) {
            if (m_Event.GetEventType() == T::GetStaticEventType()) {
                m_Event.Handled = callback(static_cast<T&>(m_Event));
            }

            return m_Event.Handled;
        }

    private:
        Event& m_Event;
    };
}  // namespace Neon
