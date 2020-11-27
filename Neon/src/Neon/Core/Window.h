#pragma once

#include <functional>
#include <string>

#include "Neon/Event/Event.h"

namespace Neon {
    struct WindowSettings {
        std::string Title;
        uint16_t Width;
        uint16_t Height;

        WindowSettings(const std::string& title = "Hazel Engine",
                       uint16_t width = 1280,
                       uint16_t height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        static Ref<Window> Create(const WindowSettings& settings = WindowSettings());

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
