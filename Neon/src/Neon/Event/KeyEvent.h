#pragma once

#include "Event.h"

namespace Neon {

    class KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

    protected:
        KeyEvent(int keyCode) : m_KeyCode(keyCode) {}

        int m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent:" << m_KeyCode << " repeats=" << m_RepeatCount;
            return ss.str();
        }

        // Overrides
        EVENT_TYPE_DEF(KeyPressed);

    private:
        int m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent:" << m_KeyCode;
            return ss.str();
        }

        // Overrides
        EVENT_TYPE_DEF(KeyReleased);
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent:" << m_KeyCode;
            return ss.str();
        }

        // Overrides
        EVENT_TYPE_DEF(KeyTyped);
    };
}  // namespace Neon
