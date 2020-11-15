#pragma once

#include "neon_pch.h"

#include "Neon/Input.h"

namespace Neon {
    class WindowsInput : public Input {
    protected:
        bool IsKeyPressed_Impl(int keyCode) override;
        bool IsMouseButtonPressed_Impl(int keyCode) override;
        std::pair<float, float> GetMousePosition_Impl() override;
        float GetMouseX_Impl() override;
        float GetMouseY_Impl() override;
    };
}
