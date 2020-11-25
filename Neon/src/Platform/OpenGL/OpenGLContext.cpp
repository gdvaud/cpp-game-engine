#include "OpenGLContext.h"

namespace Neon {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : _windowHandle(windowHandle) {
        NEO_CORE_ASSERT(windowHandle, "Window handle is null");
    }
    void OpenGLContext::Init() {
        glfwMakeContextCurrent(_windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NEO_CORE_ASSERT(status, "Failed to initialize Glad");
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(_windowHandle);
    }
}  // namespace Neon
