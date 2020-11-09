#include "Neon.h"

class SimpleLayer : public Neon::Layer {
public:
    SimpleLayer() : Layer("Simple") {}
    
    void OnUpdate() override {
    
    }
    
    void OnEvent(Neon::Event &event) override {
        NEO_TRACE("{0}", event);
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