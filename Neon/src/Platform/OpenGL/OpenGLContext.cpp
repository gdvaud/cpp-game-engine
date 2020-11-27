#include "OpenGLContext.h"

namespace Neon {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle) {
        NEO_CORE_ASSERT(windowHandle, "Window handle is null");
    }
    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NEO_CORE_ASSERT(status, "Failed to initialize Glad");
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}  // namespace Neon
