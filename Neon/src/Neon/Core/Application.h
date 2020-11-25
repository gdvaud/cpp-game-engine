#pragma once

#include "neon_pch.h"

#include "Window.h"
#include "Neon/Event/Event.h"
#include "Neon/Event/ApplicationEvent.h"

#include "Neon/Core/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Neon/Renderer/Shader.h"
#include "Neon/Renderer/Buffer.h"

namespace Neon {
    class Application {
    public:
        Application();
        virtual ~Application();
        
        void Run();
        void OnEvent(Event &event);
        
        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);
        
        inline Window &GetWindow() { return *_window; }
    
    public:
        static inline Application &Get() { return *_instance; }
    private:
        bool OnWindowClosed(WindowClosedEvent &event);
        
        bool _running = true;
        
        std::unique_ptr<Window> _window;
        ImGuiLayer *_imGuiLayer;
        LayerStack _layerStack;
    
        uint32_t _vertexArray;
        std::unique_ptr<Shader> _shader;
        std::unique_ptr<VertexBuffer> _vertexBuffer;
        std::unique_ptr<IndexBuffer> _indexBuffer;
    private:
        static Application *_instance;
    };
    
    Application *CreateApplication();
}
