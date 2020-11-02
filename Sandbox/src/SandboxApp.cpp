#include "Neon.h"

class SandboxApp : public Neon::Application {
public:
    SandboxApp() {}
    
    ~SandboxApp() {}
};

Neon::Application *Neon::CreateApplication() {
    return new SandboxApp();
}