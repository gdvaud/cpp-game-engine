#include "Application.h"

#include "Core.h"

namespace Neon {
    Application *Application::_instance = nullptr;
    
    Application::Application() {
        NEO_CORE_ASSERT(!_instance, "Application already exists");
        _instance = this;
        
        _window = std::unique_ptr<Window>(Window::Create());
        _window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        
        _layerStack = LayerStack();
        
        _imGuiLayer = new ImGuiLayer();
        PushOverlay(_imGuiLayer);
        
        // Temporary
        glCreateVertexArrays(1, &_vertexArray);
        glBindVertexArray(_vertexArray);
        
        float vertices[3 * 3] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f,
        };
        
        _vertexBuffer.reset(VertexBuffer::Create(vertices, 9));
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        
        uint32_t indices[3] = {0, 1, 2};
        _indexBuffer.reset(IndexBuffer::Create(indices, 3));
        
        // Shaders
        std::string vertexStr = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main() {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";
        
        std::string fragmentStr = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main() {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )";
        
        _shader = std::make_unique<Shader>(vertexStr, fragmentStr);
    }
    
    Application::~Application() {
    }
    
    void Application::Run() {
        while (_running) {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            _shader->Bind();
            glBindVertexArray(_vertexArray);
            glDrawElements(GL_TRIANGLES, _indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
            
            for (auto layer : _layerStack)
                layer->OnUpdate();
            
            _imGuiLayer->Begin();
            for (auto layer : _layerStack)
                layer->OnImGuiRender();
            _imGuiLayer->End();
            
            _window->OnUpdate();
        }
    }
    
    void Application::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
        
        for (auto it = _layerStack.end(); it != _layerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.Handled)
                break;
        }
    }
    
    void Application::PushLayer(Layer *layer) {
        _layerStack.PushLayer(layer);
    }
    
    void Application::PushOverlay(Layer *layer) {
        _layerStack.PushOverlay(layer);
    }
    
    // == Private ========
    bool Application::OnWindowClosed(WindowClosedEvent &event) {
        _running = false;
        return true;
    }
}