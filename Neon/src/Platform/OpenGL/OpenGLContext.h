#pragma once

#include <GLFW/glfw3.h>

#include "Neon/Renderer/GraphicContext.h"

namespace Neon {
    class OpenGLContext : public GraphicContext {
    public:
        OpenGLContext(GLFWwindow *windowHandle);
        
        void Init() override;
        void SwapBuffers() override;
    
    private:
        GLFWwindow *_windowHandle;
    };
}
