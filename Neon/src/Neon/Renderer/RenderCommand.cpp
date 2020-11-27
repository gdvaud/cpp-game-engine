#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Neon {
    RendererAPI* RenderCommand::m_RendererApi = new OpenGLRendererAPI();
}
