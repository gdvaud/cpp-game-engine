#include "Application.h"

namespace Neon {
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        NEO_CORE_ASSERT(!s_Instance, "Application already exists");
        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_LayerStack = LayerStack();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {
    }

    void Application::Run() {
        while (m_Running) {
            auto time = (float)glfwGetTime();
            TimeStep timeStep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (auto layer : m_LayerStack)
                layer->OnUpdate(timeStep);

            m_ImGuiLayer->Begin();
            for (auto layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushOverlay(layer);
    }

    // == Private ========
    bool Application::OnWindowClosed(WindowClosedEvent& event) {
        m_Running = false;
        return true;
    }
}  // namespace Neon
