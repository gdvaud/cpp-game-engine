#include "WindowsInput.h"

#include "Neon/Core/Application.h"

namespace Neon {
    Scope<Input> Input::m_Instance = CreateScope<WindowsInput>();

    bool WindowsInput::IsKeyPressed_Impl(int keyCode) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
        auto state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    bool WindowsInput::IsMouseButtonPressed_Impl(int keyCode) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
        auto state = glfwGetMouseButton(window, keyCode);
        return state == GLFW_PRESS;
    }
    std::pair<float, float> WindowsInput::GetMousePosition_Impl() {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return {(float)xpos, (float)ypos};
    }
    float WindowsInput::GetMouseX_Impl() {
        auto [x, y] = GetMousePosition_Impl();
        return x;
    }
    float WindowsInput::GetMouseY_Impl() {
        auto [x, y] = GetMousePosition_Impl();
        return y;
    }
}  // namespace Neon
