#pragma once

#include <neon_pch.h>

#include "ImGui/ImGuiLayer.h"
#include "Neon/Core/LayerStack.h"
#include "Neon/Event/ApplicationEvent.h"
#include "Neon/Event/Event.h"
#include "Neon/Renderer/Buffer.h"
#include "Neon/Renderer/Shader.h"
#include "Neon/Renderer/VertexArray.h"
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

        inline Window& GetWindow() { return *_window; }

    public:
        static inline Application& Get() { return *_instance; }

    private:
        void InitScene();
    private:
        bool OnWindowClosed(WindowClosedEvent& event);

        bool _running = true;

        std::unique_ptr<Window> _window;
        ImGuiLayer* _imGuiLayer;
        LayerStack _layerStack;

        Ref<Shader> _vertexColorShader;
        Ref<Shader> _blueColorShader;

        Ref<VertexArray> _triangleVertexArray;
        Ref<VertexArray> _squareVertexArray;

    private:
        static Application* _instance;
    };

    Application* CreateApplication();
}  // namespace Neon
