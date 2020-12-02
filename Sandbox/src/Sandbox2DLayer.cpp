#include "Sandbox2DLayer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2DLayer::Sandbox2DLayer() : Layer("Sandbox2DLayer"), m_CameraController(1980.0f / 1080.0f, 4.0f) {}

void Sandbox2DLayer::OnAttach() {
    // TODO: Remove
    m_ShaderLibrary.Load("FlatColor", "Sandbox/assets/shaders/FlatColor.glsl");

    // TODO: Remove
    uint32_t indices[6] = {
        0, 1, 2, 0, 2, 3,
    };
    // clang-format off
    float vertices[4 * 3] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
    };
    // clang-format on
    Neon::BufferLayout layout = {
        {Neon::ShaderDataType::Float3, "a_Position"},
    };

    Neon::Ref<Neon::VertexBuffer> vertexBuffer =
        Neon::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
    vertexBuffer->SetLayout(layout);

    Neon::Ref<Neon::IndexBuffer> indexBuffer =
        Neon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

    m_SquareVA = Neon::VertexArray::Create();
    m_SquareVA->AddVertexBuffer(vertexBuffer);
    m_SquareVA->SetIndexBuffer(indexBuffer);
}
void Sandbox2DLayer::OnDetach() { m_SquareVA.reset(); }

void Sandbox2DLayer::OnUpdate(Neon::TimeStep timeStep) {
    m_CameraController.OnUpdate(timeStep);

    Neon::RenderCommand::SetClearColor({0.5f, 0.1f, 0.5f, 1});
    Neon::RenderCommand::Clear();

    Neon::Renderer::BeginScene(m_CameraController.GetCamera());

    // TOOD: Replace by 2D Renderer
    auto flat = m_ShaderLibrary.Get("FlatColor");
    flat->SetFloat4("u_Color", m_SquareColor);
    Neon::Renderer::Submit(
        m_SquareVA, m_ShaderLibrary.Get("FlatColor"),
        glm::translate(glm::mat4(1.0f), m_SquarePosition) * glm::scale(glm::mat4(1.0f), glm::vec3(m_SquareScale)));

    Neon::Renderer::EndScene();
}
void Sandbox2DLayer::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::DragFloat3("Square position", glm::value_ptr(m_SquarePosition), 0.1f);
    ImGui::DragFloat("Square scale", &m_SquareScale, 0.1f);
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}
void Sandbox2DLayer::OnEvent(Neon::Event& event) { m_CameraController.OnEvent(event); }
