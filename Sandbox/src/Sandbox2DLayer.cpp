#include "Sandbox2DLayer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2DLayer::Sandbox2DLayer() : Layer("Sandbox2DLayer"), m_CameraController(1980.0f / 1080.0f, 4.0f) {}

void Sandbox2DLayer::OnAttach() {}
void Sandbox2DLayer::OnDetach() {}

void Sandbox2DLayer::OnUpdate(Neon::TimeStep timeStep) {
    m_CameraController.OnUpdate(timeStep);

    Neon::RenderCommand::SetClearColor({0.5f, 0.1f, 0.5f, 1});
    Neon::RenderCommand::Clear();

    Neon::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Neon::Renderer2D::DrawQuad(m_SquarePosition, glm::vec2(m_SquareScale), m_SquareColor);

    Neon::Renderer2D::EndScene();
}
void Sandbox2DLayer::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::DragFloat3("Square position", glm::value_ptr(m_SquarePosition), 0.1f);
    ImGui::DragFloat("Square scale", &m_SquareScale, 0.1f);
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}
void Sandbox2DLayer::OnEvent(Neon::Event& event) { m_CameraController.OnEvent(event); }
