#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Neon {
    RendererAPI* RenderCommand::_rendererAPI = new OpenGLRendererAPI();
}
