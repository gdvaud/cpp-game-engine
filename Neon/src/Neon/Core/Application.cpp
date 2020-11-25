#include "Application.h"

namespace Neon {
    Application* Application::_instance = nullptr;

    void Application::InitScene() {
        //////////////////////////
        /// Triangle model
        {
            // === Model format
            // clang-format off
            float vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            };
            uint32_t indices[3] = {0, 1, 2};
            // clang-format on
            BufferLayout layout = {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float4, "a_Color"},
            };

            // === Model storage
            _triangleVertexArray = VertexArray::Create();

            Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
            vertexBuffer->SetLayout(layout);
            _triangleVertexArray->AddVertexBuffer(vertexBuffer);

            _triangleVertexArray->SetIndexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        }
        //////////////////////////

        //////////////////////////
        /// Square model
        {
            // === Model format
            // clang-format off
            float vertices[3 * 4] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
            };
            uint32_t indices[6] = {
                0, 1, 2,
                0, 2, 3,
            };
            // clang-format on
            BufferLayout layout = {
                {ShaderDataType::Float3, "a_Position"},
            };

            // === Shader

            // === Model storage
            _squareVertexArray = VertexArray::Create();

            Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
            vertexBuffer->SetLayout(layout);
            _squareVertexArray->AddVertexBuffer(vertexBuffer);

            _squareVertexArray->SetIndexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        }
        //////////////////////////

        //////////////////////////
        /// Vertex Color Shader
        {
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
            _vertexColorShader = std::make_unique<Shader>(vertexStr, fragmentStr);
        }
        //////////////////////////

        //////////////////////////
        /// Blue Color Shader
        {
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
                    color = vec4(0, 0, 1, 1);
                }
            )";
            _blueColorShader = std::make_unique<Shader>(vertexStr, fragmentStr);
        }
        //////////////////////////
    }

    Application::Application() {
        NEO_CORE_ASSERT(!_instance, "Application already exists");
        _instance = this;

        _window = std::unique_ptr<Window>(Window::Create());
        _window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        _layerStack = LayerStack();

        _imGuiLayer = new ImGuiLayer();
        PushOverlay(_imGuiLayer);

        InitScene();
    }

    Application::~Application() {
    }

    void Application::Run() {
        while (_running) {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            _blueColorShader->Bind();
            _squareVertexArray->Bind();
            glDrawElements(GL_TRIANGLES, _squareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            _vertexColorShader->Bind();
            _triangleVertexArray->Bind();
            glDrawElements(GL_TRIANGLES, _triangleVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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
