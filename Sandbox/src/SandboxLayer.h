#pragma once

#include <Neon.h>

class SandboxLayer : public Neon::Layer {
public:
    SandboxLayer();

    void OnUpdate(Neon::TimeStep timeStep) override;
    void OnImGuiRender() override;
    void OnEvent(Neon::Event& event) override;

private:
    void InitModels();
    void InitShaders();

    void HandleMovement(Neon::TimeStep timeStep);

private:
    Neon::Ref<Neon::OrthographicCamera> m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 3.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 90.0f;

    Neon::Ref<Neon::Shader> m_VertexColorShader;
    Neon::Ref<Neon::Shader> m_BlueColorShader;
    Neon::Ref<Neon::Shader> m_TextureColorShader;

    Neon::Ref<Neon::Texture2D> m_Texture;

    Neon::Ref<Neon::VertexArray> m_TriangleVertexArray;
    Neon::Ref<Neon::VertexArray> m_SquareVertexArray;
};