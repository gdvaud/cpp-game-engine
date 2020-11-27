#include "SandboxApp.h"

#include <Neon.h>

#include <glm/gtc/matrix_transform.hpp>

Neon::Application* Neon::CreateApplication() {
    return new SandboxApp();
}

SimpleLayer::SimpleLayer()
    : Layer("Simple"),
      _camera(-1.6f, 1.6f, -0.9f, 0.9f),
      _cameraPosition(0.0f) {
    InitModels();
    InitShaders();
}
void SimpleLayer::InitModels() {
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
        Neon::BufferLayout layout = {
            {Neon::ShaderDataType::Float3, "a_Position"},
            {Neon::ShaderDataType::Float4, "a_Color"},
        };

        // === Model storage
        _triangleVertexArray = Neon::VertexArray::Create();

        Neon::Ref<Neon::VertexBuffer> vertexBuffer = Neon::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
        vertexBuffer->SetLayout(layout);
        _triangleVertexArray->AddVertexBuffer(vertexBuffer);

        _triangleVertexArray->SetIndexBuffer(Neon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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
        Neon::BufferLayout layout = {
            {Neon::ShaderDataType::Float3, "a_Position"},
        };

        // === Shader

        // === Model storage
        _squareVertexArray = Neon::VertexArray::Create();

        Neon::Ref<Neon::VertexBuffer> vertexBuffer = Neon::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
        vertexBuffer->SetLayout(layout);
        _squareVertexArray->AddVertexBuffer(vertexBuffer);

        _squareVertexArray->SetIndexBuffer(Neon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    }
    //////////////////////////
}
void SimpleLayer::InitShaders() {
    //////////////////////////
    /// Vertex Color Shader
    {
        std::string vertexStr = R"(
                #version 330 core

                layout(location = 0) in vec3 a_Position;
                layout(location = 1) in vec4 a_Color;

                uniform mat4 u_ViewProjection;
                uniform mat4 u_Transform;

                out vec3 v_Position;
                out vec4 v_Color;

                void main() {
                    v_Position = a_Position;
                    v_Color = a_Color;
                    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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
        _vertexColorShader = Neon::Shader::Create(vertexStr, fragmentStr);
    }
    //////////////////////////

    //////////////////////////
    /// Blue Color Shader
    {
        std::string vertexStr = R"(
                #version 330 core

                layout(location = 0) in vec3 a_Position;

                uniform mat4 u_ViewProjection;
                uniform mat4 u_Transform;

                out vec3 v_Position;

                void main() {
                    v_Position = a_Position;
                    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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
        _blueColorShader = Neon::Shader::Create(vertexStr, fragmentStr);
    }
    //////////////////////////
}

void SimpleLayer::OnUpdate(Neon::TimeStep timeStep) {
    HandleMovement(timeStep);

    Neon::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Neon::RenderCommand::Clear();

    _camera.SetPosition(_cameraPosition);
    _camera.SetRotation(_cameraRotation);

    Neon::Renderer::BeginScene(_camera);

    Neon::Renderer::Submit(_squareVertexArray, _blueColorShader);
    Neon::Renderer::Submit(_triangleVertexArray, _vertexColorShader, glm::translate(glm::mat4(1.0f), {-0.5f, 0.f, 0.0f}));
    Neon::Renderer::Submit(_triangleVertexArray, _vertexColorShader, glm::translate(glm::mat4(1.0f), {0.5f, 0.0f, 0.0f}));

    Neon::Renderer::EndScene();
}
void SimpleLayer::HandleMovement(Neon::TimeStep timeStep) {
    if (Neon::Input::IsKeyPressed(NEO_KEY_A))
        _cameraPosition.x += _cameraMoveSpeed * timeStep;
    if (Neon::Input::IsKeyPressed(NEO_KEY_D))
        _cameraPosition.x -= _cameraMoveSpeed * timeStep;

    if (Neon::Input::IsKeyPressed(NEO_KEY_W))
        _cameraPosition.y -= _cameraMoveSpeed * timeStep;
    if (Neon::Input::IsKeyPressed(NEO_KEY_S))
        _cameraPosition.y += _cameraMoveSpeed * timeStep;

    if (Neon::Input::IsKeyPressed(NEO_KEY_Q))
        _cameraRotation -= _cameraRotationSpeed * timeStep;
    if (Neon::Input::IsKeyPressed(NEO_KEY_E))
        _cameraRotation += _cameraRotationSpeed * timeStep;
}

void SimpleLayer::OnImGuiRender() {}
void SimpleLayer::OnEvent(Neon::Event& event) {}
