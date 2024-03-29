#pragma once

#include <Neon.h>

class Sandbox3DLayer : public Neon::Layer {
public:
    Sandbox3DLayer();

    void OnUpdate(Neon::TimeStep timeStep) override;
    void OnImGuiRender() override;
    void OnEvent(Neon::Event& event) override;

private:
    void InitModels();
    void InitShaders();

private:
    Neon::OrthographicCameraController m_CameraController;

    Neon::ShaderLibrary m_ShaderLibrary;
    Neon::Ref<Neon::Texture2D> m_Texture;

    Neon::Ref<Neon::VertexArray> m_TriangleVertexArray;
    Neon::Ref<Neon::VertexArray> m_SquareVertexArray;
};