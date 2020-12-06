#pragma once

#include <Neon.h>

class Sandbox2DLayer : public Neon::Layer {
public:
    Sandbox2DLayer();

    virtual void OnAttach() override;
    virtual void OnUpdate(Neon::TimeStep timeStep) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Neon::Event& event) override;
    virtual void OnDetach() override;

private:
    Neon::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquarePosition = {0.0f, 0.0f, 0.0f};
    float m_SquareScale = 1.0f;
    glm::vec4 m_SquareColor = {0.0f, 0.0f, 0.0f, 1.0f};
};
