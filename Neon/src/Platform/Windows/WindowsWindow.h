#pragma once

#include "Neon/Graphic/GraphicContext.h"
#include "Neon/Graphic/Window.h"
#include "neon_windows_pch.h"

namespace Neon {
    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowSettings& settings);
        ~WindowsWindow() override;

        void OnUpdate() override;

        // Window attributes
        virtual void* GetNativeWindow() const { return m_Window; }
        inline uint16_t GetWidth() const override;
        inline uint16_t GetHeight() const override;
        void SetEventCallback(const EventCallbackFn& callback) override;
        void SetVSync(bool enabled) override;
        bool IsVSync() override;

    private:
        virtual void Init(const WindowSettings& settings);
        virtual void InitEvents();
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;
        Scope<GraphicContext> m_Context;

        struct WindowData {
            std::string Title;
            uint16_t Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
    };
}  // namespace Neon
