#pragma once

#include <Neon.h>
#include <Neon/EntryPoint.h>

#include "SandboxLayer.h"

class SandboxApp : public Neon::Application {
public:
    SandboxApp();

    ~SandboxApp() override = default;
};