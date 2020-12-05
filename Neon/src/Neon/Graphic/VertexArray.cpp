#include "VertexArray.h"

#include "Neon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Neon {
    Ref<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
            case RendererAPI::API::None: NEO_CORE_ASSERT(false, "RendererAPI::None not supported");
        }
        NEO_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}  // namespace Neon
