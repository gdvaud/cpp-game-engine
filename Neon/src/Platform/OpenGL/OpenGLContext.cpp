#include "OpenGLContext.h"

namespace Neon {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
        NEO_CORE_ASSERT(windowHandle, "Window handle is null");
    }
    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NEO_CORE_ASSERT(status, "Failed to initialize Glad");

        NEO_CORE_INFO("OpenGL Info:");
        NEO_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        NEO_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        NEO_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

#ifdef NEO_ENABLE_ASSERTS
        int versionMajor, versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
        NEO_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5),
                        "Neon requires OpenGL version 4.5 or higher");
#endif
    }

    void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }
}  // namespace Neon
