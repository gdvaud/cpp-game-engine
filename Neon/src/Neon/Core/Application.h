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

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Ref<Window> GetWindow() { return m_Window; }

    public:
        static inline Application& Get() { return *s_Instance; }

    private:
        bool OnWindowClosed(WindowClosedEvent& event);

    private:
        bool m_Running = true;
        float m_LastFrameTime = 0.0f;

        Ref<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_LayerStack;

    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}  // namespace Neon
