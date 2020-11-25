#pragma once

#include <Neon.h>

class SimpleLayer : public Neon::Layer {
public:
    SimpleLayer();

    void OnUpdate() override;
    void OnImGuiRender() override;
    void OnEvent(Neon::Event& event) override;

private:
    void InitModels();
    void InitShaders();

private:
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
