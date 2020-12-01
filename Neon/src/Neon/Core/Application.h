#pragma once

#include <memory>

#include "ImGui/ImGuiLayer.h"
#include "Neon/Core/LayerStack.h"
#include "Neon/Event/ApplicationEvent.h"
#include "Neon/Event/Event.h"
#include "Window.h"

namespace Neon {
    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& event);

        void PushLayer(const Ref<Layer>& layer);
        void PushOverlay(const Ref<Layer>& layer);

        inline Ref<Window> GetWindow() { return m_Window; }

    public:
        static inline Application& Get() { return *s_Instance; }

    private:
        bool OnWindowClosed(WindowClosedEvent& event);
        bool OnWindowResized(WindowResizedEvent& event);

    private:
        bool m_Running = true;
        bool m_Minimized = false;
        float m_LastFrameTime = 0.0f;

        Ref<Window> m_Window;
        Ref<ImGuiLayer> m_ImGuiLayer;
        Ref<LayerStack> m_LayerStack;

    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}  // namespace Neon
