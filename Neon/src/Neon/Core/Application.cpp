#include "Application.h"

namespace Neon {
    Application *Application::_instance = nullptr;
    
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case Neon::ShaderDataType::Float:
            case Neon::ShaderDataType::Float2:
            case Neon::ShaderDataType::Float3:
            case Neon::ShaderDataType::Float4:
            case Neon::ShaderDataType::Mat3:
            case Neon::ShaderDataType::Mat4: return GL_FLOAT;
            case Neon::ShaderDataType::Int:
            case Neon::ShaderDataType::Int2:
            case Neon::ShaderDataType::Int3:
            case Neon::ShaderDataType::Int4: return GL_INT;
            case Neon::ShaderDataType::Bool: return GL_BOOL;
        }
        
        NEO_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
    
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
        
        float vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        };
        
        _vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        
        {
            BufferLayout layout = {
                    {ShaderDataType::Float3, "a_Position"},
                    {ShaderDataType::Float4, "a_Color"}
            };
            
            _vertexBuffer->SetLayout(layout);
        }
        
        uint32_t index = 0;
        const auto &layout = _vertexBuffer->GetLayout();
        for (const auto &element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *) element.Offset);
            index++;
        }
        
        uint32_t indices[3] = {0, 1, 2};
        _indexBuffer.reset(IndexBuffer::Create(indices, 3));
        
        // Shaders
        std::string vertexStr = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";
        
        std::string fragmentStr = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main() {
                color = v_Color;
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
