#include "Application.h"

#include "Neon/Graphic/Window.h"
#include "Neon/Renderer/Renderer.h"
#include "Neon/Renderer/Renderer2D.h"

namespace Neon {
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        NEO_CORE_ASSERT(!s_Instance, "Application already exists");
        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback(NEO_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();
        Renderer2D::Init();

        m_LayerStack = CreateRef<LayerStack>();

        m_ImGuiLayer = CreateRef<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() { s_Instance = nullptr; }

    void Application::Run() {
        while (m_Running) {
            auto time = (float)glfwGetTime();
            TimeStep timeStep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized) {
                for (const auto& layer : *m_LayerStack) layer->OnUpdate(timeStep);

                m_ImGuiLayer->Begin();
                for (const auto& layer : *m_LayerStack) layer->OnImGuiRender();
                m_ImGuiLayer->End();
            }

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowClosedEvent>(NEO_BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizedEvent>(NEO_BIND_EVENT_FN(Application::OnWindowResized));

        for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();) {
            (*--it)->OnEvent(event);
            if (event.Handled) break;
        }
    }

    void Application::PushLayer(const Ref<Layer>& layer) { m_LayerStack->PushLayer(layer); }

    void Application::PushOverlay(const Ref<Layer>& layer) { m_LayerStack->PushOverlay(layer); }

    // == Private ========
    bool Application::OnWindowClosed(WindowClosedEvent& event) {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResized(WindowResizedEvent& event) {
        if (event.GetWidth() == 0 || event.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;
        Renderer::OnWindowResized(event.GetWidth(), event.GetHeight());
        return false;
    }
}  // namespace Neon
