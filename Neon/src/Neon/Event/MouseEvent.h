#pragma once

#include "Event.h"

namespace Neon {

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : m_X(x), m_Y(y) {}

        inline float GetX() const { return m_X; }

        inline float GetY() const { return m_Y; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: (" << m_X << ", " << m_Y << ")";
            return ss.str();
        }

        // Overrides
        EVENT_TYPE_DEF(MouseMoved);

    private:
        float m_X, m_Y;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

        inline float GetXOffset() const { return m_XOffset; }

        inline float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: (" << m_XOffset << ", " << m_YOffset << ")";
            return ss.str();
        }

        // Overrides
        EVENT_TYPE_DEF(MouseScrolled);

    private:
        float m_XOffset, m_YOffset;
    };

    class MouseButtonEvent : public Event {
    public:
        inline int GetButtonCode() const { return m_ButtonCode; }

    protected:
        MouseButtonEvent(int buttonCode) : m_ButtonCode(buttonCode) {}

        int m_ButtonCode;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_ButtonCode;
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
            ss << "MouseButtonReleasedEvent: " << m_ButtonCode;
            return ss.str();
        }

        // Overrides
        EVENT_TYPE_DEF(MouseButtonReleased);
    };
}  // namespace Neon
