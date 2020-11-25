#pragma once

#include <string>
#include <functional>

#include "Neon/Event/Event.h"

namespace Neon {
    struct WindowSettings {
        std::string Title;
        uint16_t Width;
        uint16_t Height;

        WindowSettings(const std::string& _title = "Hazel Engine",
                       uint16_t _width = 1280,
                       uint16_t _height = 720)
            : Title(_title), Width(_width), Height(_height) {}
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        static Window* Create(const WindowSettings& settings = WindowSettings());

        virtual ~Window() {}
        virtual void OnUpdate() = 0;

        // Window attributes
        virtual void* GetNativeWindow() const = 0;
        virtual uint16_t GetWidth() const = 0;
        virtual uint16_t GetHeight() const = 0;
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() = 0;
    };
}  // namespace Neon
