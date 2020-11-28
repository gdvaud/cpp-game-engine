#include "SandboxApp.h"

Neon::Application* Neon::CreateApplication() {
    return new SandboxApp();
}

SandboxApp::SandboxApp() {
    PushLayer(Neon::CreateRef<SandboxLayer>());
}
