#include "Application.h"

#include "Neon/Renderer/RenderCommand.h"
#include "Neon/Renderer/Renderer.h"

namespace Neon {
    Application* Application::_instance = nullptr;

    Application::Application() {
        NEO_CORE_ASSERT(!_instance, "Application already exists");
        _instance = this;

        _window = std::unique_ptr<Window>(Window::Create());
        _window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        _layerStack = LayerStack();

        _imGuiLayer = new ImGuiLayer();
        PushOverlay(_imGuiLayer);
    }

    Application::~Application() {
    }

    void Application::Run() {
        while (_running) {
            for (auto layer : _layerStack)
                layer->OnUpdate();

            _imGuiLayer->Begin();
            for (auto layer : _layerStack)
                layer->OnImGuiRender();
            _imGuiLayer->End();

            _window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

        for (auto it = _layerStack.end(); it != _layerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer) {
        _layerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer) {
        _layerStack.PushOverlay(layer);
    }

    // == Private ========
    bool Application::OnWindowClosed(WindowClosedEvent& event) {
        _running = false;
        return true;
    }
}  // namespace Neon
