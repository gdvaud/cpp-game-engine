#include "SandboxLayer.h"

#include <glm/gtc/matrix_transform.hpp>

SandboxLayer::SandboxLayer()
    : Layer("Simple"),
      m_CameraPosition(0.0f) {
    m_Camera = Neon::CreateRef<Neon::OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);

    InitModels();
    InitShaders();
}
void SandboxLayer::InitModels() {
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
        m_TriangleVertexArray = Neon::VertexArray::Create();

        Neon::Ref<Neon::VertexBuffer> vertexBuffer = Neon::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
        vertexBuffer->SetLayout(layout);
        m_TriangleVertexArray->AddVertexBuffer(vertexBuffer);

        m_TriangleVertexArray->SetIndexBuffer(Neon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    }
    //////////////////////////

    //////////////////////////
    /// Square model
    {
        // === Model format
        // clang-format off
        float vertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        };
        uint32_t indices[6] = {
            0, 1, 2,
            0, 2, 3,
        };
        // clang-format on
        Neon::BufferLayout layout = {
            {Neon::ShaderDataType::Float3, "a_Position"},
            {Neon::ShaderDataType::Float2, "a_TexCoord"},
        };
        // === Model storage
        m_SquareVertexArray = Neon::VertexArray::Create();

        Neon::Ref<Neon::VertexBuffer> vertexBuffer = Neon::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
        vertexBuffer->SetLayout(layout);
        m_SquareVertexArray->AddVertexBuffer(vertexBuffer);

        m_SquareVertexArray->SetIndexBuffer(Neon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    }
    //////////////////////////
}
void SandboxLayer::InitShaders() {
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
        m_ShaderLibrary.Load("blue-color",
                             vertexStr, fragmentStr);
    }
    //////////////////////////

    m_ShaderLibrary.Load("vertex-color",
                         "Sandbox/assets/shaders/VertexColor.glsl");

    auto textureShader = m_ShaderLibrary.Load("texture",
                                              "Sandbox/assets/shaders/Texture.glsl");

    m_Texture = Neon::Texture2D::Create("Sandbox/assets/textures/square.png");

    textureShader->Bind();
    textureShader->UploadUniformInt("u_Texture", 0);
}

void SandboxLayer::OnUpdate(Neon::TimeStep timeStep) {
    HandleMovement(timeStep);

    Neon::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Neon::RenderCommand::Clear();

    m_Camera->SetPosition(m_CameraPosition);
    m_Camera->SetRotation(m_CameraRotation);

    Neon::Renderer::BeginScene(m_Camera);

    m_Texture->Bind();
    Neon::Renderer::Submit(m_SquareVertexArray, m_ShaderLibrary.Get("texture"));
    Neon::Renderer::Submit(m_SquareVertexArray, m_ShaderLibrary.Get("blue-color"),
                           glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

    Neon::Renderer::Submit(m_TriangleVertexArray, m_ShaderLibrary.Get("vertex-color"),
                           glm::translate(glm::mat4(1.0f), {-0.75f, 0.f, 0.0f}) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));
    Neon::Renderer::Submit(m_TriangleVertexArray, m_ShaderLibrary.Get("vertex-color"),
                           glm::translate(glm::mat4(1.0f), {0.75f, 0.0f, 0.0f}) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

    Neon::Renderer::EndScene();
}
void SandboxLayer::HandleMovement(Neon::TimeStep timeStep) {
    if (Neon::Input::IsKeyPressed(NEO_KEY_A))
        m_CameraPosition.x -= m_CameraMoveSpeed * timeStep;
    if (Neon::Input::IsKeyPressed(NEO_KEY_D))
        m_CameraPosition.x += m_CameraMoveSpeed * timeStep;

    if (Neon::Input::IsKeyPressed(NEO_KEY_W))
        m_CameraPosition.y += m_CameraMoveSpeed * timeStep;
    if (Neon::Input::IsKeyPressed(NEO_KEY_S))
        m_CameraPosition.y -= m_CameraMoveSpeed * timeStep;

    if (Neon::Input::IsKeyPressed(NEO_KEY_Q))
        m_CameraRotation -= m_CameraRotationSpeed * timeStep;
    if (Neon::Input::IsKeyPressed(NEO_KEY_E))
        m_CameraRotation += m_CameraRotationSpeed * timeStep;
}

void SandboxLayer::OnImGuiRender() {}
void SandboxLayer::OnEvent(Neon::Event& event) {}
