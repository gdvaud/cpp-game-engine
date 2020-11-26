#pragma once

#include <Neon.h>

class SimpleLayer : public Neon::Layer {
public:
    SimpleLayer();

    void OnUpdate(Neon::TimeStep timeStep) override;
    void OnImGuiRender() override;
    void OnEvent(Neon::Event& event) override;

private:
    void InitModels();
    void InitShaders();

    void HandleMovement(Neon::TimeStep timeStep);

private:
    Neon::OrthographicCamera _camera;

    glm::vec3 _cameraPosition;
    float _cameraMoveSpeed = 3.0f;

    float _cameraRotation = 0.0f;
    float _cameraRotationSpeed = 90.0f;

    Neon::Ref<Neon::Shader> _vertexColorShader;
    Neon::Ref<Neon::Shader> _blueColorShader;

    Neon::Ref<Neon::VertexArray> _triangleVertexArray;
    Neon::Ref<Neon::VertexArray> _squareVertexArray;
};

class SandboxApp : public Neon::Application {
public:
    SandboxApp() {
        PushLayer(new SimpleLayer());
    }

    ~SandboxApp() {}
};
