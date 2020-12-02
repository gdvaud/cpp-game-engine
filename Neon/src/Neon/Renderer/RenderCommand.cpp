#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Neon {
    Scope<RendererAPI> RenderCommand::s_RendererApi = CreateScope<OpenGLRendererAPI>();
}
