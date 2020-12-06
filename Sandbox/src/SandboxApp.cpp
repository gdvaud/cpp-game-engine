#include "SandboxApp.h"

#include "Sandbox2DLayer.h"
#include "Sandbox3DLayer.h"

Neon::Application* Neon::CreateApplication() { return new SandboxApp(); }

SandboxApp::SandboxApp() {
//    PushLayer(Neon::CreateRef<Sandbox3DLayer>());
    PushLayer(Neon::CreateRef<Sandbox2DLayer>());
}
