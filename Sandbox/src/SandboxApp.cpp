#include <Neon.h>
#include <imgui.h>

class SimpleLayer : public Neon::Layer {
public:
    SimpleLayer() : Layer("Simple") {}
    
    void OnUpdate() override {
    }
    
    void OnImGuiRender() override {
        ImGui::Begin("Test window");
        ImGui::Text("Hello Sandbox app");
        ImGui::End();
    }
    
    void OnEvent(Neon::Event &event) override {
    }
};

class SandboxApp : public Neon::Application {
public:
    SandboxApp() {
        PushLayer(new SimpleLayer());
    }
    
    ~SandboxApp() {}
};

Neon::Application *Neon::CreateApplication() {
    return new SandboxApp();
}