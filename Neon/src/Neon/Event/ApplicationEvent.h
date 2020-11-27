#pragma once

#include "Event.h"

namespace Neon {

    class WindowResizedEvent : public Event {
    public:
        WindowResizedEvent(uint32_t width, uint32_t height)
            : m_Width(width), m_Height(height) {}

        // Getters
        inline uint32_t GetWidth() const {
            return m_Width;
        }

        inline uint32_t GetHeight() const {
            return m_Height;
        }

        // Overrides
        EVENT_TYPE_DEF(WindowResized);

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizedEvent {Width(" << m_Width << ") Height(" << m_Height << ")";
            return ss.str();
        }

    private:
        uint32_t m_Width, m_Height;
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

}  // namespace Neon
