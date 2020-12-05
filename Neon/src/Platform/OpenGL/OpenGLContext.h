#pragma once

#include "Neon/Graphics/GraphicContext.h"

struct GLFWwindow;

namespace Neon {
    class OpenGLContext : public GraphicContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };
}  // namespace Neon
